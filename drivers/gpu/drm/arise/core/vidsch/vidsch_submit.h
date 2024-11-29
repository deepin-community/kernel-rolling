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
#ifndef __VIDSCH_SUBMIT_H__
#define __VIDSCH_SUBMIT_H__

extern int  vidschi_prepare_and_submit_dma(vidsch_mgr_t *sch_mgr, task_dma_t *task_dma);
extern void vidschi_fake_submit_dma(vidsch_mgr_t *sch_mgr, task_dma_t *task_dma, int discard);

extern void vidschi_release_allocated_tasks(vidsch_mgr_t *sch_mgr);
extern task_desc_t *vidschi_uncompleted_task_exceed_wait_time(vidsch_mgr_t *sch_mgr, unsigned long long max_wait_time);

extern void vidschi_set_dma_task_submitted(vidsch_mgr_t *sch_mgr, task_desc_t *task);
extern void vidschi_set_dma_task_fake_submitted(vidsch_mgr_t *sch_mgr, task_desc_t *task);
extern void vidschi_set_uncompleted_task_dropped(vidsch_mgr_t *sch_mgr, unsigned long long dropped_task);

#endif

