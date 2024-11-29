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
#include "vidmm.h"
#include "vidmmi.h"
#include "vidsch.h"
#include "perfevent.h"

void vidmm_get_map_allocation_info(adapter_t *adapter, vidmm_allocation_t *allocation, gf_map_argu_t *argu)
{
    vidmm_mgr_t     *mm_mgr  = adapter->mm_mgr;
    vidmm_segment_t *segment = &mm_mgr->segment[allocation->segment_id];

    argu->size = allocation->size;

    if (allocation->pages_mem)
    {
        argu->memory = allocation->pages_mem;
        argu->flags.mem_type = GF_SYSTEM_RAM;
        argu->offset = 0;

        if (segment->flags.support_snoop)
        {
            argu->flags.cache_type = GF_MEM_WRITE_BACK;
        }
        else if (allocation->flag.cacheable)
        {
            argu->flags.cache_type = GF_MEM_WRITE_BACK;
        }
        else if (segment->flags.support_manual_flush && (allocation->segment_id != 0))
        {
            argu->flags.cache_type = GF_MEM_WRITE_BACK;
        }
        else
        {
            argu->flags.cache_type = GF_MEM_WRITE_COMBINED;
        }
    }
    else if (segment->flags.system_phys_mem_reserved)
    {
        if(segment->flags.support_snoop || segment->flags.support_manual_flush)
        {
            argu->flags.cache_type = GF_MEM_WRITE_BACK;
        }
        else
        {
            argu->flags.cache_type = GF_MEM_WRITE_COMBINED;
        }

        argu->flags.mem_type   = GF_SYSTEM_IO;
        argu->phys_addr        = allocation->phys_addr - segment->gpu_vm_start + segment->phys_addr_start;
    }
    else
    {
        if(segment->flags.support_snoop)
        {
            argu->flags.cache_type = GF_MEM_WRITE_BACK;
        }
        else if(segment->flags.support_manual_flush && (allocation->segment_id != 0))
        {
            argu->flags.cache_type = GF_MEM_WRITE_BACK;
        }
        else
        {
            argu->flags.cache_type = GF_MEM_WRITE_COMBINED;
        }

        argu->flags.mem_type   = GF_SYSTEM_IO;
        argu->phys_addr        = allocation->phys_addr + adapter->vidmm_bus_addr;

        if(argu->phys_addr >= (adapter->vidmm_bus_addr + adapter->Visible_vram_size))
        {
            gf_warning("vidmm_get_map_allocation_info map invisable allocation!!!");
        }
    }
}
