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
#include "vidsch_dfs_e3k.h"
#include "vidsch.h"
#include "vidschi.h"
#include "chip_include_e3k.h"
#include "vidsch_engine_e3k.h"
#include "register_e3k.h"

#define GFX_ENGINE_MASK (1 << RB_INDEX_GFXL | 1 << RB_INDEX_GFXH)

static unsigned char vidsch_cacl_available_gpc_bit(adapter_t * adapter)
{
    unsigned char bits = 0;

    if(adapter->hw_caps.chip_slice_mask &0xF00) bits |=0x10;
    if(adapter->hw_caps.chip_slice_mask &0x0F0) bits |=0x20;
    if(adapter->hw_caps.chip_slice_mask &0x00F) bits |=0x40;

    return bits;
}

int vidsch_power_clock_on_off_e3k(vidsch_mgr_t *sch_mgr, unsigned int off)
{
    adapter_t * adapter = sch_mgr->adapter;
    vidschedule_t *schedule = adapter->schedule;
    unsigned char used_gpc_mask_bit = vidsch_cacl_available_gpc_bit(adapter);
    unsigned long flags = 0;

    flags = gf_spin_lock_irqsave(schedule->power_status_lock);
    //power_trace("[CG] used_gpc_mask_bit:%x\n", used_gpc_mask_bit);

    if(off)
    {
        switch(sch_mgr->engine_index)
        {
            case RB_INDEX_GFXL:
            case RB_INDEX_GFXH:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 0, 0x8F);
                break;
            case RB_INDEX_VCP0:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 0, 0xF7);
                break;
            case RB_INDEX_VCP1:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 0, 0xFB);
                break;
            case RB_INDEX_VPP:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 0, 0xFD);
                break;
            default:
                  break;
        }
        power_trace("[CG] engine %d do cg power off,  CR01:%x\n", sch_mgr->engine_index, read_reg_e3k(adapter->mmio, CR_C, 0x01));
    }
    else
    {
        switch(sch_mgr->engine_index)
        {
            case RB_INDEX_GFXL:
            case RB_INDEX_GFXH:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, (0x70 & used_gpc_mask_bit), 0x8F);
                break;
            case RB_INDEX_VCP0:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 8, 0xF7);
                break;
            case RB_INDEX_VCP1:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 4, 0xFB);
                break;
            case RB_INDEX_VPP:
                write_reg_e3k(adapter->mmio, CR_C, 0x01, 2, 0xFD);
                break;
            default:
                  break;
        }
        power_trace("[CG] engine %d do cg power on,  CR01:%x\n", sch_mgr->engine_index, read_reg_e3k(adapter->mmio, CR_C, 0x01));
    }

    gf_spin_unlock_irqrestore(schedule->power_status_lock, flags);

    return S_OK;
}

int vidsch_power_clock_on_off_vcp(vidsch_mgr_t *sch_mgr, unsigned int off)
{
    adapter_t * adapter = sch_mgr->adapter;
    vidschedule_t *schedule = adapter->schedule;
    unsigned long flags = 0;

    flags = gf_spin_lock_irqsave(schedule->power_status_lock);
    //power_trace("[CG] used_gpc_mask_bit:%x\n", used_gpc_mask_bit);

    if(off)
    {
        write_reg_e3k(adapter->mmio, CR_C, 0x01, 0, 0xF7);//VCP0
        if(adapter->chip_id < CHIP_ARISE1020)//CHIP_ARISE1020 only has one vcp core
        {
            write_reg_e3k(adapter->mmio, CR_C, 0x01, 0, 0xFB);//VCP1
        }
        power_trace("[CG] engine %d do cg power off,  CR01:%x\n", sch_mgr->engine_index, read_reg_e3k(adapter->mmio, CR_C, 0x01));
    }
    else
    {
        write_reg_e3k(adapter->mmio, CR_C, 0x01, 8, 0xF7);//VCP0
        if(adapter->chip_id < CHIP_ARISE1020)//CHIP_ARISE1020 only has one vcp core
        {
            write_reg_e3k(adapter->mmio, CR_C, 0x01, 4, 0xFB);//VCP1
        }
        power_trace("[CG] engine %d do cg power on,  CR01:%x\n", sch_mgr->engine_index, read_reg_e3k(adapter->mmio, CR_C, 0x01));
    }

    gf_spin_unlock_irqrestore(schedule->power_status_lock, flags);

    return S_OK;
}

void vidsch_power_tuning_e3k(adapter_t *adapter, unsigned int gfx_only)
{
    vidschedule_t *schedule = adapter->schedule;
    vidsch_mgr_t  *sch_mgr = NULL;
    int engine_index;
    unsigned int engine_mask = gfx_only ? GFX_ENGINE_MASK : ALL_ENGINE_MASK;

    if (!adapter->pwm_level.EnableClockGating)
    {
        return;
    }

    for (engine_index = adapter->active_engine_count-1; engine_index >= 0; engine_index--)
    {
        int ret = S_OK;
        unsigned long flags=0;

        if ((engine_mask & (1<<engine_index)) == 0) continue;

        sch_mgr = adapter->sch_mgr[engine_index];

        if (sch_mgr == NULL)  continue;

        vidsch_update_engine_idle_status(adapter, (1 << engine_index));
        if (sch_mgr->completely_idle)
        {
            flags = gf_spin_lock_irqsave(sch_mgr->power_status_lock);
            if (sch_mgr->chip_func->power_clock &&
                sch_mgr->engine_dvfs_power_on &&
                vidsch_is_fence_back(sch_mgr->adapter, sch_mgr->engine_index, sch_mgr->last_send_fence_id))
            {
                if(ret == S_OK)
                {
                   //gf_info("power off: last_send_fence_id=%d. \n", sch_mgr->last_send_fence_id);
                   sch_mgr->chip_func->power_clock(sch_mgr, TRUE);
                   sch_mgr->engine_dvfs_power_on = FALSE;
                }
            }
            gf_spin_unlock_irqrestore(sch_mgr->power_status_lock, flags);
        }
    }
}


