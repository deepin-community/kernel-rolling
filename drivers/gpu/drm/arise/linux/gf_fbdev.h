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
#ifndef _H_GF_FBDEV_H
#define _H_GF_FBDEV_H
#include "gf_drmfb.h"
#include "gf_device_debug.h"

#if DRM_VERSION_CODE < KERNEL_VERSION(4, 19, 0)

struct gf_fbdev
{
    unsigned int gpu_device;
    struct drm_fb_helper helper;
    struct drm_gf_framebuffer *fb;
    gf_device_debug_info_t *debug;
};

#define to_gf_fbdev(helper) container_of(helper, struct gf_fbdev, helper)

int gf_fbdev_init(gf_card_t *gf);
int gf_fbdev_deinit(gf_card_t *gf);
void gf_fbdev_set_suspend(gf_card_t *gf, int state);
void gf_fbdev_restore_mode(gf_card_t *gf);
void gf_fbdev_poll_changed(struct drm_device *dev);
#endif

#endif
