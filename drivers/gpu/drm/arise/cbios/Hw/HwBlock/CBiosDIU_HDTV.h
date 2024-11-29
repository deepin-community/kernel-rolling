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

#ifndef _CBIOS_DIU_HDTV_H_
#define _CBIOS_DIU_HDTV_H_

#include "../../Display/CBiosDisplayManager.h"
#include "../../Device/CBiosDeviceShare.h"

#define HDTV_MODU_NUM 4

CBIOS_VOID cbDIU_HDTV_ModuleOnOff(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDTVModuleIndex, CBIOS_BOOL bTurnOn);
CBIOS_VOID cbDIU_HDTV_LBBypass(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDTVModuleIndex, CBIOS_BOOL isBypass);
CBIOS_VOID cbDoHDTVFuncSetting_Arise(PCBIOS_VOID pvcbe, PCBIOS_DISP_MODE_PARAMS pModeParams, CBIOS_U32 IGAIndex, CBIOS_ACTIVE_TYPE ulDevices);
#endif
