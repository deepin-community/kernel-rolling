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
#ifndef _GF_IRQ_E3K_
#define _GF_IRQ_E3K_

#include "../gf_irq.h"


#define INTR_EN_REG  0x8508
#define ADV_INTR_EN_REG 0x854c
#define INTR_SHADOW_REG  0x8574
#define ADV_SHADOW_REG  0x8578

typedef enum _BIU_INTR_BIT
{
    VSYNC1_INT  = 0x1,
    VSYNC2_INT  = 0x4,
    VSYNC3_INT  = 0x8,
    VSYNC4_INT  = 0x10,
    DP1_INT     = 0x80,
    DP2_INT     = 0x100,
    DP3_INT     = 0x10000,
    DP4_INT     = 0x20000,
    HDCODEC_INT_1020 = 0x200000,
    HDCP_INT   = 0x400000,
    VIP1_INT    = 0x1000000,
    HDCODEC_INT = 0x4000000,
    VIP2_INT    = 0x8000000,
    VIP3_INT    = 0x10000000,
    VIP4_INT    = 0x40000000,
}BIU_INTR_BIT;

typedef enum _CSP_INTR_BIT
{
    FE_HANG_VD0_INT  = 0x1,
    BE_HANG_VD0_INT  = 0x2,
    FE_ERROR_VD0_INT = 0x4,
    BE_ERROR_VD0_INT = 0x8,
    FE_HANG_VD1_INT  = 0x10,
    BE_HANG_VD1_INT  = 0x20,
    FE_ERROR_VD1_INT = 0x40,
    BE_ERROR_VD1_INT = 0x80,
    ENGINE_FENCE_INT = 0x8000000,
}CSP_INTR_BIT;

typedef struct _intr_info
{
    unsigned int biu_intr_bits;
    unsigned int csp_intr_bits;
}intr_info_t;

#endif
