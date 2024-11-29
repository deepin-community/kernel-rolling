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
#ifndef  _GF_ATOMIC_H_
#define _GF_ATOMIC_H_

#include "gf_disp.h"
#include "gf_cbios.h"

#if DRM_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)

struct drm_atomic_state* gf_atomic_state_alloc(struct drm_device *dev);

void gf_atomic_state_clear(struct drm_atomic_state *s);

void gf_atomic_state_free(struct drm_atomic_state *s);

struct drm_crtc_state* gf_crtc_duplicate_state(struct drm_crtc *crtc);

void gf_crtc_destroy_state(struct drm_crtc *crtc, struct drm_crtc_state *s);
#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
    int gf_crtc_helper_check(struct drm_crtc *crtc, struct drm_atomic_state *state);
#else
    int gf_crtc_helper_check(struct drm_crtc *crtc, struct drm_crtc_state *state);
#endif

struct drm_connector_state* gf_connector_duplicate_state(struct drm_connector *connector);

int gf_connector_atomic_set_property(struct drm_connector *connector,
                                     struct drm_connector_state *state,
                                     struct drm_property *property,
                                     uint64_t val);

int gf_connector_atomic_get_property(struct drm_connector *connector,
                                     const struct drm_connector_state *state,
                                     struct drm_property *property,
                                     uint64_t *val);

void gf_connector_destroy_state(struct drm_connector *connector, struct drm_connector_state *state);

void gf_atomic_helper_commit_tail(struct drm_atomic_state *old_state);

#endif

#endif
