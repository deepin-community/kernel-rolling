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

#ifndef _CBIOS_DP_H_
#define _CBIOS_DP_H_

#include "../CBiosDeviceShare.h"
#include "../Monitor/CBiosDPMonitor.h"
#include "../Monitor/CBiosHDMIMonitor.h"
#include "../../Hw/HwBlock/CBiosPHY_DP.h"

typedef struct _CBIOS_DP_PORT_PARAMS
{
    CBIOS_BOOL   bDualMode;          // 1 (yes), connect to HDMI/DVI via a connector

    DP_EPHY_MODE DPEphyMode;
    CBIOS_BOOL   bRunCTS;
}CBIOS_DP_PORT_PARAMS, *PCBIOS_DP_PORT_PARAMS;

typedef struct _CBIOS_DP_CONTEXT
{
    CBIOS_DEVICE_COMMON         Common;
    CBIOS_DP_PORT_PARAMS        DPPortParams;

    // monitor contexts
    CBIOS_DP_MONITOR_CONTEXT    DPMonitorContext;
    CBIOS_HDMI_MONITOR_CONTEXT  HDMIMonitorContext;
}CBIOS_DP_CONTEXT, *PCBIOS_DP_CONTEXT;


PCBIOS_DEVICE_COMMON cbDPPort_Init(PCBIOS_VOID pvcbe, PVCP_INFO pVCP, CBIOS_ACTIVE_TYPE DeviceType);
CBIOS_VOID cbDPPort_DeInit(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
CBIOS_BOOL cbDPPort_IsDeviceInDpMode(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
PCBIOS_VOID cbDPPort_GetDPMonitorContext(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
PCBIOS_VOID cbDPPort_GetHDMIMonitorContext(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
CBIOS_STATUS cbDPPort_Isr(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DP_ISR_PARA pDPIsrPara);
CBIOS_BOOL cbDPPort_WorkThreadMainFunc(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DP_WORKTHREAD_PARA pDPWorkThreadPara);
CBIOS_STATUS cbDPPort_SetNotifications(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DP_NOTIFICATIONS pDPNotifications);
CBIOS_STATUS  cbDPPort_GetInt(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DP_INT_PARA  pDPIntPara);
CBIOS_STATUS  cbDPPort_HandleIrq(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DP_HANDLE_IRQ_PARA pDPHandleIrqPara);
CBIOS_STATUS cbDPPort_GetCustomizedTiming(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DP_CUSTOMIZED_TIMING pDPCustomizedTiming);
#endif
