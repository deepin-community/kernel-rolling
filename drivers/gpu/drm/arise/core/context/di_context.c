/*
 * Copyright © 2021 Glenfly Tech Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */
#include "gf_adapter.h"
#include "global.h"
#include "context.h"

struct di_mgr
{
    adapter_t          *adapter;

    struct os_spinlock *lock;

    unsigned int       ctx_bitmap;
    unsigned int       free_start;

    unsigned int       max_ctx;
    unsigned int       ctx_inuse_num;  /* for debug*/
};


/* deinterlace dev manager */

int cm_create_di_mgr(adapter_t *adapter)
{
    struct di_mgr *dmgr = NULL;

    if(adapter->dmgr != NULL) return S_OK;

    dmgr = gf_calloc(sizeof(struct di_mgr));

    dmgr->adapter        = adapter;
    dmgr->lock           = gf_create_spinlock(0);
    dmgr->ctx_bitmap     = 0x0;

    dmgr->ctx_inuse_num  = 0;
    dmgr->max_ctx        = 4; // Elite2000 VPP Di: fd_index max number
    dmgr->free_start     = 0;

    adapter->dmgr = dmgr;

    return S_OK;
}

void cm_destroy_di_mgr(adapter_t *adapter)
{
    struct di_mgr *dmgr = adapter->dmgr;

    if(dmgr == NULL) return;

    adapter->dmgr = NULL;

    dmgr->ctx_bitmap     = 0xFFFFFFFF;
    dmgr->max_ctx        = 0;

    if(dmgr->lock != NULL)
    {
        gf_destroy_spinlock(dmgr->lock);

        dmgr->lock = NULL;
    }

    gf_free(dmgr);
}

di_context_t *cm_create_di_context(gpu_device_t *device, gf_create_di_context_t *create)
{
    adapter_t     *adapter = device->adapter;
    struct di_mgr *dmgr    = adapter->dmgr;
    di_context_t  *context = NULL;

    int idx = 0;

    gf_spin_lock(dmgr->lock);

    idx = gf_find_next_zero_bit(&dmgr->ctx_bitmap, dmgr->max_ctx, dmgr->free_start);

    if(idx < dmgr->max_ctx)
    {
        gf_set_bit(idx, &dmgr->ctx_bitmap);
        dmgr->free_start = (idx + 1) % dmgr->max_ctx;
    }

    gf_spin_unlock(dmgr->lock);

    if(idx < dmgr->max_ctx)
    {
        context = gf_calloc(sizeof(di_context_t));

        context->device    = device;
        context->hw_idx    = idx;
        context->handle    = add_handle(&adapter->hdl_mgr, HDL_TYPE_DI_CONTEXT, context);
        context->stream_id = create->stream_id;

        //gf_info("create DI: :%x, idx: %d.\n", context->handle, context->hw_idx);

        cm_device_lock(device);

        list_add(&context->list_node, &device->di_context_list);

        cm_device_unlock(device);
    }

    return context;
}

void cm_destroy_di_context(gpu_device_t *device, di_context_t *context)
{
    adapter_t     *adapter = device->adapter;
    struct di_mgr *dmgr    = adapter->dmgr;

    if(context->hw_idx < dmgr->max_ctx)
    {
        gf_spin_lock(dmgr->lock);

        gf_clear_bit(context->hw_idx, &dmgr->ctx_bitmap);

        dmgr->ctx_inuse_num--;

        gf_spin_unlock(dmgr->lock);
    }

    //gf_info("destroy DI: :%x, idx: %d.\n", context->handle, context->hw_idx);

    remove_handle(&adapter->hdl_mgr, context->handle);

    cm_device_lock(device);

    list_del(&context->list_node);

    cm_device_unlock(device);

    gf_free(context);
}


