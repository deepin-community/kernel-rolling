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
#include "vidsch.h"
#include "vidschi.h"

/* must called sch_mgr->engine_lock locked */
void vidschi_engine_dvfs_power_on(vidsch_mgr_t *sch_mgr)
{
    adapter_t *adapter = sch_mgr->adapter;

    if (!adapter->pwm_level.EnableClockGating)
    {
        return;
    }

    if(!sch_mgr->engine_dvfs_power_on)
    {
        if(!list_empty(&sch_mgr->submitted_task_list) || sch_mgr->last_send_fence_id != sch_mgr->returned_fence_id)
        {
            if(sch_mgr->chip_func->power_clock)
            {
                sch_mgr->chip_func->power_clock(sch_mgr, FALSE);

                sch_mgr->engine_dvfs_power_on = TRUE;
            }
        }
    }

    return;
}

void vidschi_try_power_tuning(adapter_t *adapter, unsigned int gfx_only)
{
    vidschedule_t *schedule = adapter->schedule;

    if (!adapter->pwm_level.EnableClockGating)
    {
        return;
    }

    if(schedule->chip_func->power_tuning)
    {
        schedule->chip_func->power_tuning(adapter, gfx_only);
    }
    return;
}


