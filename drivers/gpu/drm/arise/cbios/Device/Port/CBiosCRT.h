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

#ifndef _CBIOS_CRT_H_
#define _CBIOS_CRT_H_

#include "../Monitor/CBiosCRTMonitor.h"

typedef struct _CBIOS_CRT_CONTEXT
{
    CBIOS_DEVICE_COMMON        Common;

    // monitor contexts
    CBIOS_CRT_MONITOR_CONTEXT  CRTMonitorContext;
}CBIOS_CRT_CONTEXT, *PCBIOS_CRT_CONTEXT;

PCBIOS_DEVICE_COMMON cbCRTPort_Init(PCBIOS_VOID pvcbe, PVCP_INFO pVCP, CBIOS_ACTIVE_TYPE DeviceType);
CBIOS_VOID cbCRTPort_DeInit(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
#endif
