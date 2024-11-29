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
#ifndef __GF_CAPTURE_DRV_H_
#define __GF_CAPTURE_DRV_H_

#include "gf_capture.h"

#define CAPTURE_INIT_B          (0x1 << 1)
#define CAPTURE_ENABLE_B        (0x1 << 2)
#define CAPTURE_NEED_SKIP_B     (0x1 << 3)

typedef enum _gf_capture_event_t
{
    GF_CAPTURE_EVENT_NONE             = 0,
    GF_CAPTURE_EVENT_PLUG_OUT         = 1,
    GF_CAPTURE_EVENT_PLUG_IN          = 2,
    GF_CAPTURE_EVENT_SIGNAL_OFF       = 3,
    GF_CAPTURE_EVENT_SIGNAL_ON        = 4,
}gf_capture_event_t;

typedef struct _gf_capture_desc
{
    gf_capture_id_t cf_fmt_id;
    char* cf_name;
}gf_capture_desc;

struct gf_capture_type
{
    gf_capture_id_t cf_fmt_id;
    char *cf_name;
    int (*cf_ctl)(disp_info_t *disp_info, struct gf_capture_type *capture, void *params);
    void (*notify_interrupt)(disp_info_t *disp_info, struct gf_capture_type *capture);
    void (*event_handler)(disp_info_t *disp_info, struct gf_capture_type *capture, gf_capture_event_t event);
    unsigned int flags;
    void *priv_info;
    struct gf_capture_type *cf_next;
};

typedef struct gf_capture_type gf_capture_t;

typedef struct _gf_cf_irq_tbl_t
{
    unsigned int irq_mask;
    gf_capture_id_t cf_id;
}gf_cf_irq_tbl_t;


void gf_capture_interrupt_handle(disp_info_t *disp_info, unsigned int itrr);
void gf_capture_handle_event(disp_info_t *disp_info, gf_capture_id_t cf_id, gf_capture_event_t event);
void disp_register_capture(disp_info_t *disp_info, gf_capture_t *capture);
void disp_unregister_capture(disp_info_t *disp_info, gf_capture_t *capture);
gf_capture_t *disp_find_capture(disp_info_t *disp_info, int id);
void disp_capture_init(disp_info_t *disp_info);
void disp_capture_deinit(disp_info_t *disp_info);


#endif
