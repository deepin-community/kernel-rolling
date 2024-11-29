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
#include "perfeventi.h"
#include "perfevent.h"
#include "../vidsch/vidsch_engine_e3k.h"


static int perf_direct_get_counter_e3k(adapter_t *adapter, gf_miu_list_item_t *miu_table, unsigned int miu_table_length,int force_read)
{
    gf_assert(0, NULL);
    return 0;
}

static int perf_calculate_engine_usage_e3k(adapter_t * adapter, gf_hwq_info * phwq_info)
{
    unsigned int  engine           = 0;
    hwq_event_mgr_t *hwq_event_mgr = adapter->hwq_event_mgr;
    hwq_event_info  *p_hwq_event   = NULL;
    unsigned int usage             = 0;

    for(engine = 0; engine < adapter->active_engine_count; engine++)
    {

        p_hwq_event   = (hwq_event_info*)(hwq_event_mgr->hwq_event)+engine;
        usage=p_hwq_event->engine_usage;
        //gf_info(" EngineNum=%d usage %d \n", engine, usage);
        if(engine==RB_INDEX_GFXL || engine==RB_INDEX_GFXH)
        {
            if(usage > phwq_info->Usage_3D)
            {
                phwq_info->Usage_3D=usage;
            }
        }

        if(engine==RB_INDEX_VCP0 || engine==RB_INDEX_VCP1)
        {
            if(usage > phwq_info->Usage_VCP)
            {
                phwq_info->Usage_VCP=usage;
            }
        }

        if(engine==RB_INDEX_VPP)
        {
            if(usage > phwq_info->Usage_VPP)
            {
                phwq_info->Usage_VPP=usage;
            }
        }
    }
    return 0;
}


static int perf_calculate_engine_usage_ext_e3k(adapter_t * adapter, gfx_hwq_info_ext *phwq_info_ext)
{
    unsigned int         usage            = 0;
    unsigned int  engine           = 0;
    hwq_event_info       *p_hwq_event;
    hwq_event_mgr_t *hwq_event_mgr = adapter->hwq_event_mgr;

    if( !(adapter->ctl_flags.hwq_event_enable) || !(adapter->hwq_event_mgr) )
    {
        return -1;
    }

    gf_memset(phwq_info_ext,0,sizeof(gfx_hwq_info_ext));
    for(engine = 0; engine < adapter->active_engine_count; engine++)
    {

        p_hwq_event   = (hwq_event_info*)(hwq_event_mgr->hwq_event)+engine;
        usage=p_hwq_event->engine_usage;
        //gf_info(" EngineNum=%d usage %d \n", engine, usage);
        switch(engine)
        {
            case RB_INDEX_GFXL:
                phwq_info_ext->Usage_3D=usage;
                break;
            case RB_INDEX_GFXH:
                phwq_info_ext->Usage_3D_High=usage;
                break;
            case RB_INDEX_VCP0:
                phwq_info_ext->Usage_VCP0=usage;
                break;
            case RB_INDEX_VCP1:
                phwq_info_ext->Usage_VCP1=usage;
                break;
            case RB_INDEX_VPP:
                phwq_info_ext->Usage_VPP=usage;
                break;
            default:
                break;
        }
    }
    return 0;
}


perf_chip_func_t   perf_chip_func =
{
    .direct_get_miu_counter = perf_direct_get_counter_e3k,
    .calculate_engine_usage = perf_calculate_engine_usage_e3k,
    .calculate_engine_usage_ext = perf_calculate_engine_usage_ext_e3k,
};

