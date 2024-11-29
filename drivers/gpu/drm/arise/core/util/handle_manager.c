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
#include "handle_manager.h"

#define MAX_HANDLE          (65536 * 4)

int handle_mgr_create(handle_mgr_t *handle_mgr)
{
    long    *table = NULL;

    table = gf_calloc(MAX_HANDLE * sizeof(long));

    if(table == NULL)
    {
        return E_OUTOFMEMORY;
    }

    handle_mgr->max_handle  = MAX_HANDLE;
    handle_mgr->table       = table;
    handle_mgr->left_num    = handle_mgr->max_handle - 1;
    handle_mgr->free_start  = 1;

    handle_mgr->bitmap_lock = gf_create_spinlock(0);
    handle_mgr->bitmap_size = handle_mgr->max_handle >> 3;
    handle_mgr->bitmap      = gf_calloc(handle_mgr->bitmap_size);

    gf_set_bit(0, handle_mgr->bitmap);     // 0 will not used

    return S_OK;
}

void handle_mgr_destroy(handle_mgr_t *handle_mgr)
{
    if(handle_mgr->table)
    {
        gf_free(handle_mgr->table);

        handle_mgr->max_handle = 0;
        handle_mgr->table      = NULL;
    }

    gf_free(handle_mgr->bitmap);

    gf_destroy_spinlock(handle_mgr->bitmap_lock);
}

unsigned int add_handle(handle_mgr_t *handle_mgr, unsigned int type, void *data)
{
    int             index     = 0;
    unsigned int    new_handle = 0;
    long            *table;
    unsigned long   flags;

    flags = gf_spin_lock_irqsave(handle_mgr->bitmap_lock);

    table = handle_mgr->table;

    index = gf_find_next_zero_bit(handle_mgr->bitmap, handle_mgr->max_handle, handle_mgr->free_start);

    if(index < handle_mgr->max_handle)
    {
        gf_set_bit(index, handle_mgr->bitmap);

        handle_mgr->left_num--;
        handle_mgr->free_start = (index + 1) % handle_mgr->max_handle;
        table[index] = (long)data;
        new_handle = index | (type << 24);
    }
    else
    {
        gf_info("no enough handle, left_num %d max_handle:%d.\n", handle_mgr->left_num, handle_mgr->max_handle);
        gf_assert(0, "no enough handle");
    }

    gf_spin_unlock_irqrestore(handle_mgr->bitmap_lock, flags);

    return new_handle;
}

void *get_from_handle_and_validate(handle_mgr_t *handle_mgr, unsigned int handle, unsigned int type)
{
    void *ptr = NULL;

    if((handle & 0xFF000000) == (type << 24))
    {
        ptr = get_from_handle(handle_mgr, handle);
    }

    return ptr;
}

void remove_handle(handle_mgr_t *handle_mgr, unsigned int handle)
{
    long            *table = NULL;
    unsigned int    index  = handle & 0x00FFFFFF;
    unsigned long   flags;

    flags = gf_spin_lock_irqsave(handle_mgr->bitmap_lock);

    table = handle_mgr->table;

    if(index < handle_mgr->max_handle)
    {
        handle_mgr->left_num++;

        gf_clear_bit(index, handle_mgr->bitmap);
        table[index] = 0;
    }
    else
    {
        gf_info("unknow handle: handle: %x, max_handle:%d.\n", handle, handle_mgr->max_handle);
        gf_assert(0, "unknow handle");
    }

    gf_spin_unlock_irqrestore(handle_mgr->bitmap_lock, flags);
}

