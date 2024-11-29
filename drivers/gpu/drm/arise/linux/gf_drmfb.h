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
#ifndef  _GF_DRMFB_H_
#define _GF_DRMFB_H_

#include "gf_disp.h"
#include "gf_gem.h"
#include "gf_gem_priv.h"
#if DRM_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
#include <drm/drm_framebuffer.h>
#endif

struct drm_gf_framebuffer
{
    struct drm_framebuffer base;
    struct drm_gf_gem_object *obj;
};
#define to_gfb(fb) container_of((fb), struct drm_gf_framebuffer, base)

struct drm_framebuffer *
gf_fb_create(struct drm_device *dev,
                              struct drm_file *file_priv,
                              #if DRM_VERSION_CODE >= KERNEL_VERSION(4, 5, 0)  || defined (PHYTIUM_2000)
                              const struct drm_mode_fb_cmd2 *mode_cmd
                              #else
                              struct drm_mode_fb_cmd2 *mode_cmd
                              #endif
                              );

void gf_cleanup_fb(struct drm_plane *plane,  struct drm_plane_state *old_state);

struct drm_gf_framebuffer*
__gf_framebuffer_create(struct drm_device *dev,
                        struct drm_mode_fb_cmd2 *mode_cmd,
                        struct drm_gf_gem_object *obj);
#endif
