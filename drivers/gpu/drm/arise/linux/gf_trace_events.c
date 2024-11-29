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
#include "os_interface.h"
#include "gf.h"

#define CREATE_TRACE_POINTS
#include "gf_trace.h"


/* os interface for trace points */
void gf_fence_back_trace_event(int engine_index, unsigned long long fence_id)
{
    trace_gfx_fence_back(engine_index, fence_id);
}

void gf_task_create_trace_event(int engine_index, unsigned int context,
                                unsigned long long task_id, unsigned int task_type)
{
    trace_gfx_task_create(engine_index, context, task_id, task_type);
}

void gf_task_submit_trace_event(int engine_index, unsigned int context,
                                unsigned long long task_id, unsigned int task_type,
                                unsigned long long fence_id, unsigned int args)
{
    trace_gfx_task_submit(engine_index, context, task_id, task_type, fence_id, args);
}

void gf_begin_section_trace_event(const char* desc)
{
    trace_gfx_begin_section(desc);
}

void gf_end_section_trace_event(int result)
{
    trace_gfx_end_section(result);
}

void gf_counter_trace_event(const char* desc, unsigned long long value)
{
    trace_gfx_counter(desc, value);
}

/* register/unregister probe functions */
void gf_register_trace_events(void)
{

}

void gf_unregister_trace_events(void)
{

}

