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

#ifndef _CBIOS_DIU_HDAC_H_
#define _CBIOS_DIU_HDAC_H_

#include "../../Device/CBiosDeviceShare.h"

#define  HDAC_MODU_NUM  2

extern CBIOS_U32 HDAC_REG_PACKET1[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_PACKET2[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_MODE_RESP[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_SW_RESP[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_CHSTATUS_CTRL[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_SUP_PARA[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_SAMP_RATE[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_CONVERT_CAP[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_PIN_WIDGET_CAP[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_PIN_SENSE[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_ELD_BUF[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_CTRL_WRITE[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_READ_SEL[HDAC_MODU_NUM];
extern CBIOS_U32 HDAC_REG_READ_OUT[HDAC_MODU_NUM];

typedef struct _AUDIO_CLOCK_TABLE
{
    CBIOS_U32 StreamFormat;
    CBIOS_U64 AudioPacketClock;
}AUDIO_CLOCK_TABLE,*PAUDIO_CLOCK_TABLE;

typedef union _HDAC_NONSNOOP_SETTING
{
    CBIOS_U16      NonSnoopFlags;
    struct
    {
        CBIOS_U16  bStreamNonSnoop      :1;
        CBIOS_U16  bBDLNonSnoop         :1;
        CBIOS_U16  bCORBNonSnoop        :1;
        CBIOS_U16  bRIRBNonSnoop        :1;
        CBIOS_U16  bDMAPositionNonSnoop :1;
        CBIOS_U16  Reserved             :11;
    };
}HDAC_NONSNOOP_SETTING,*PHDAC_NONSNOOP_SETTING;

CBIOS_VOID cbDIU_HDAC_SetHDACodecPara(PCBIOS_VOID pvcbe, PCBIOS_HDAC_PARA pCbiosHDACPara);
CBIOS_VOID cbDIU_HDAC_SetStatus(PCBIOS_VOID pvcbe);
CBIOS_U32  cbDIU_HDAC_GetChannelNums(PCBIOS_VOID pvcbe, CBIOS_MODULE_INDEX HDACModuleIndex);
CBIOS_VOID cbDIU_HDAC_SetConnectStatus(PCBIOS_VOID pvcbe, PCBIOS_HDAC_PARA pCbiosHDACPara);
#endif
