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
#ifndef __GF_VIP_H_
#define __GF_VIP_H_

#include "gf_capture_drv.h"

#define GF_VIP_ENABLE       0
#define GF_VIP_DISABLE      1
#define GF_VIP_SET_MODE     2
#define GF_VIP_SET_BUFFER   3
#define GF_VIP_QUERY_CAPS   4

#define GF_CAPTURE_VIP_INTERFACE

typedef struct
{
    gf_capture_t *mcapture;
    unsigned char fb_num;
    unsigned char vip;
    void (*cb)(gf_capture_id_t id, void *data, unsigned int flags);
    void *cb_data;
    struct work_struct vip_work;
}vip_spec_info_t;

typedef struct
{
    unsigned char vip;
    unsigned int  op;
    union{
        struct
        {
            unsigned int fmt;
            unsigned int chip;
            unsigned int x_res;
            unsigned int y_res;
            unsigned int refs;
        }mode;

        struct
        {
            unsigned char fb_num;
            unsigned char fb_idx;
            unsigned long long fb_addr;
        }fb;

        struct
        {
            unsigned int mode_num;
            gf_vip_mode_t *mode;
        }caps;
    };
}gf_vip_set_t;

void disp_register_vip_capture(disp_info_t *disp_info);
void disp_unregister_vip_capture(disp_info_t *disp_info);

#endif
