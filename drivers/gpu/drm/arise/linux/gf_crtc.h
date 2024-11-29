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
#ifndef  _GF_CRTC_H_
#define _GF_CRTC_H_

#include "gf_disp.h"
#include "gf_cbios.h"

void gf_crtc_destroy(struct drm_crtc *crtc);
void gf_crtc_dpms_onoff_helper(struct drm_crtc *crtc, int dpms_on);

#if DRM_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)

void  gf_crtc_helper_set_mode(struct drm_crtc *crtc);

void  gf_crtc_helper_enable(struct drm_crtc *crtc);

void  gf_crtc_helper_disable(struct drm_crtc *crtc);
#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
void  gf_crtc_atomic_disable(struct drm_crtc *crtc, struct drm_atomic_state *state);

void  gf_crtc_atomic_enable(struct drm_crtc *crtc, struct drm_atomic_state *state);

void gf_crtc_atomic_begin(struct drm_crtc *crtc, struct drm_atomic_state *state);

void gf_crtc_atomic_flush(struct drm_crtc *crtc, struct drm_atomic_state *state);
#else
void  gf_crtc_atomic_disable(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state);

void  gf_crtc_atomic_enable(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state);

void gf_crtc_atomic_begin(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state);

void gf_crtc_atomic_flush(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state);
#endif

static inline u32 drm_get_crtc_index(struct drm_crtc *crtc)
{
    return crtc->index;
}

static inline struct drm_framebuffer *drm_get_crtc_primary_fb(struct drm_crtc *crtc)
{
    return crtc->primary->fb;
}

static inline void drm_set_crtc_primary_fb(struct drm_crtc *crtc, struct drm_framebuffer *fb)
{
    crtc->primary->fb = fb;
}

#else

int gf_crtc_cursor_set(struct drm_crtc *crtc,
                 struct drm_file *file,
                 uint32_t handle,
                 uint32_t width, uint32_t height);

int gf_crtc_cursor_move(struct drm_crtc *crtc, int x, int y);
#ifdef PHYTIUM_2000
int gf_crtc_gamma_set(struct drm_crtc *crtc, u16 *red, u16 *green,
                 u16 *blue, uint32_t size);
#else
void gf_crtc_gamma_set(struct drm_crtc *crtc, u16 *red, u16 *green,
                 u16 *blue, uint32_t start, uint32_t size);
#endif

int gf_crtc_helper_set_config(struct drm_mode_set *set);

void  gf_crtc_prepare(struct drm_crtc *crtc);

void  gf_crtc_commit(struct drm_crtc *crtc);

bool  gf_crtc_mode_fixup(struct drm_crtc *crtc,
               const struct drm_display_mode *mode,
               struct drm_display_mode *adjusted_mode);

int  gf_crtc_mode_set(struct drm_crtc *crtc, struct drm_display_mode *mode,
            struct drm_display_mode *adjusted_mode, int x, int y,
            struct drm_framebuffer *old_fb);

int  gf_crtc_mode_set_base(struct drm_crtc *crtc, int x, int y,
                 struct drm_framebuffer *old_fb);

void gf_crtc_disable(struct drm_crtc *crtc);

int gf_crtc_page_flip(struct drm_crtc *crtc, struct drm_framebuffer *fb, struct drm_pending_vblank_event *event, uint32_t flags);

static inline u32 drm_get_crtc_index(struct drm_crtc *crtc)
{
    return to_gf_crtc(crtc)->pipe;
}
static inline struct drm_framebuffer *drm_get_crtc_primary_fb(struct drm_crtc *crtc)
{
    return crtc->primary->fb;
}

static inline void drm_set_crtc_primary_fb(struct drm_crtc *crtc, struct drm_framebuffer *fb)
{
    crtc->primary->fb = fb;
}
#endif

#if DRM_VERSION_CODE >= KERNEL_VERSION(4, 4, 0)
typedef unsigned int pipe_t;
#else
typedef int pipe_t;
#endif

#endif
