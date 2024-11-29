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
#ifndef __GF_WB_H_
#define __GF_WB_H_

#include "gf_capture_drv.h"

#define GF_WB_ENABLE               (0x1 << 0)
#define GF_WB_DISABLE              (0x1 << 1)
#define GF_WB_SET_MODE             (0x1 << 2)
#define GF_WB_SET_BUFFER           (0x1 << 3)
#define GF_WB_QUERY_CAPS           (0x1 << 4)
#define GF_WB_SET_BYPASS_MODE      (0x1 << 5)
#define GF_WB_SET_DOWNSCALER_MODE  (0x1 << 6)
#define GF_WB_SET_VSYNC_OFF        (0x1 << 7)

#define GF_WB_MODE_SETTING_S   (0x1 << 0)
#define GF_WB_MODE_BYPASS_S    (0x1 << 1)
#define GF_WB_VSYNC_OFF_S      (0x1 << 2)


#define GF_CAPTURE_WB_INTERFACE

typedef struct
{
    unsigned int src_x;
    unsigned int src_y;
    unsigned int out_fmt;
    unsigned int work_mode;
    unsigned int dst_x;
    unsigned int dst_y;
    unsigned int double_buf;
}gf_wb_mode_set_t;

typedef struct
{
    gf_capture_t *mcapture;
    unsigned char iga;
    void (*cb)(gf_capture_id_t id, void *data, unsigned int flags);
    void *cb_data;
    gf_wb_mode_set_t mode_set;
    unsigned int wb_status;
    struct work_struct wb_work;
}wb_spec_info_t;


typedef struct
{
    unsigned int op_flags;
    unsigned char iga_idx;
    union{
        gf_wb_mode_set_t mode;

        struct
        {
            unsigned int src_x;
            unsigned int src_y;
            unsigned int refreshrate;
            unsigned int capture_fmt;
        }input_mode;

        struct
        {
            unsigned long long fb_addr;
        }fb;
    };
}gf_wb_set_t;

void disp_register_wb_capture(disp_info_t *disp_info);
void disp_unregister_wb_capture(disp_info_t *disp_info);

#endif
