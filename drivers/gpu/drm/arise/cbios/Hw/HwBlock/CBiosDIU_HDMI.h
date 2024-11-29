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

#ifndef _CBIOS_DIU_HDMI_H_
#define _CBIOS_DIU_HDMI_H_

#include "../../Device/CBiosDeviceShare.h"

#define  HDMI_MODU_NUM 4

#define HDMI_DELAY_FOR_HDCP                 58 //58 TMDS clocks of the horizontal blanking interval is required for content protection re-synchronization
#define HDMI_GUARD_BAND_PERIOD              2  // each Guard Band is 2 TMDS clocks
#define HDMI_LEADING_GUARD_BAND_PERIOD      HDMI_GUARD_BAND_PERIOD
#define HDMI_TRAILING_GUARD_BAND_PERIOD     HDMI_GUARD_BAND_PERIOD
#define HDMI_PREAMBLE_PERIOD                8  // each Preamble is 8 TMDS clocks
#define HDMI_MIN_CTL_PERIOD                 (HDMI_PREAMBLE_PERIOD + 4)

#define HDCP_HW_PROCESS_PERIOD              7

CBIOS_VOID cbDIU_HDMI_WriteFIFO(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE DeviceType, CBIOS_U8 FIFOIndex, CBIOS_U8 *pDataBuff, CBIOS_U32 BuffLen);
CBIOS_VOID cbDIU_HDMI_ReadFIFO(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE DeviceType, CBIOS_U8 FIFOIndex, CBIOS_U8 *pDataBuff, CBIOS_U32 BuffLen);
CBIOS_VOID cbDIU_HDMI_SendInfoFrame(PCBIOS_VOID pvcbe, CBIOS_U32 HDMIMaxPacketNum, CBIOS_ACTIVE_TYPE Device, CBIOS_U8 Length);
CBIOS_VOID cbDIU_HDMI_SetHDCPDelay(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bHDCPCapable);
CBIOS_VOID cbDIU_HDMI_SetHVSync(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_U8 HVPolarity);
CBIOS_VOID cbDIU_HDMI_SetColorDepth(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_U8 ColorDepth);
CBIOS_VOID cbDIU_HDMI_SetPixelFormat(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_U32 OutputSignal);
CBIOS_VOID cbDIU_HDMI_SetModuleMode(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bHDMIMode);
CBIOS_VOID cbDIU_HDMI_SelectSource(PCBIOS_VOID pvcbe, CBIOS_MODULE *pHDMIModule, CBIOS_MODULE *pNextModule);
CBIOS_VOID cbDIU_HDMI_ModuleOnOff(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bTurnOn);
CBIOS_VOID cbDIU_HDMI_SetCTSN(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_MODULE_INDEX HDACModuleIndex,CBIOS_U32 StreamFormat);
CBIOS_VOID cbDIU_HDMI_ConfigScrambling(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bEnableScrambling);
CBIOS_VOID cbDIU_HDMI_EnableReadRequest(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bEnableRR);
CBIOS_VOID cbDIU_HDMI_EnableYCbCr420(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bEnable420);
CBIOS_VOID cbDIU_HDMI_EnableClkLane(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex, CBIOS_BOOL bEnableClkLane);
CBIOS_VOID cbDIU_HDMI_DisableVideoAudio(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex);
CBIOS_VOID cbDIU_HDMI_EnableVideoAudio(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex);
CBIOS_BOOL cbDIU_HDMI_IsOn(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDMIModuleIndex);

#endif
