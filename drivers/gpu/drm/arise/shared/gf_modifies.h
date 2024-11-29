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
#ifndef __GF_MODIFIES_H_
#define __GF_MODIFIES_H_

/*this piece code should be place in drm/drm-fourcc.h in kernel/mesa*/

#ifdef KERNEL_BUILD
#include <drm/drm_fourcc.h>
#else
// for usermode code, libdrm will provide the include path through its cflags
#include <drm_fourcc.h>
#endif

/*here just for compatiable for drm linear mod*/
/* GF Linear mode define as same as system define, can be shared with other app/vendors */

#ifndef DRM_FORMAT_MOD_VENDOR_NONE
#define DRM_FORMAT_MOD_VENDOR_NONE    0
#endif

#ifndef DRM_FORMAT_MOD_NONE
#define DRM_FORMAT_MOD_NONE    0
#endif

#ifndef DRM_FORMAT_RESERVED
#define DRM_FORMAT_RESERVED    ((1ULL << 56) - 1)
#endif

#ifndef DRM_FORMAT_MOD_INVALID
#define DRM_FORMAT_MOD_INVALID    fourcc_mod_code(NONE, DRM_FORMAT_RESERVED)
#endif

/*
 * Linear Layout
 *
 * Just plain linear layout. Note that this is different from no specifying any
 * modifier (e.g. not setting DRM_MODE_FB_MODIFIERS in the DRM_ADDFB2 ioctl),
 * which tells the driver to also take driver-internal information into account
 * and so might actually result in a tiled framebuffer.
 */
#ifndef DRM_FORMAT_MOD_LINEAR
#define DRM_FORMAT_MOD_LINEAR    fourcc_mod_code(NONE, 0)
#endif


#define DRM_FORMAT_MOD_VENDOR_GF 0x19
/*usage  for display specially requirement*/
#define DRM_FORMAT_MOD_GF_DISPLAY               fourcc_mod_code(GF, 1)
#define DRM_FORMAT_MOD_GF_LINEAR                DRM_FORMAT_MOD_LINEAR
#define DRM_FORMAT_MOD_GF_TILED                 fourcc_mod_code(GF, 3)
#define DRM_FORMAT_MOD_GF_COMPRESS              fourcc_mod_code(GF, 4)
#define DRM_FORMAT_MOD_GF_TILED_COMPRESS        fourcc_mod_code(GF, 5)


#define DRM_FORMAT_MOD_GF_LOCAL                 fourcc_mod_code(GF, 6)
#define DRM_FORMAT_MOD_GF_PCIE                  fourcc_mod_code(GF, 7)

#define DRM_FORMAT_MOD_GF_RB_ALT                fourcc_mod_code(GF, 8)

#define DRM_FORMAT_MOD_GF_INVALID               DRM_FORMAT_MOD_INVALID
#endif

