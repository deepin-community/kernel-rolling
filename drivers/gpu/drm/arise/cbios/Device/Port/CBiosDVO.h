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

#ifndef _CBIOS_DVO_H_
#define _CBIOS_DVO_H_

#include "../CBiosDeviceShare.h"

#define SUPPORTDVODEVICE    TX_NONE


//Hardcode DVO SlaveAddress
#define VT1636_SLAVE_ADDRESS      0x80
#define CH7301_SLAVE_ADDRESS      0xEC
#define VT1632_SLAVE_ADDRESS      0x10
#define AD9389_SLAVE_ADDRESS      0x72
#define CH7305_SLAVE_ADDRESS      0xEA

typedef struct _TXRegType
{
    CBIOS_U8 index;
    CBIOS_U8 mask;
    CBIOS_U8 data;
}TXRegType, *PTXRegType;

typedef enum TX_TYPE
{
    TX_NONE     = 0,       //   No transmitter and without LCD function
    TX_VT1636   = 0x01,
    TX_CH7301C  = 0x02,
    TX_VT1632   = 0x04,
    TX_AD9389B  = 0x08,
    TX_CH7305   = 0x10,
} TX_TYPE;

typedef struct _DVO_CARD_ID_PARA
{
    TX_TYPE  DVOCardType;
    CBIOS_U8 DVOCardIDOffset;
    CBIOS_U8 DVOCardIDValue;
} DVO_CARD_ID_PARA;

typedef struct _CBIOS_DVO_CONTEXT
{
    CBIOS_DEVICE_COMMON     Common;
    CBIOS_DVO_DEV_CONFIG    DVODevice;
}CBIOS_DVO_CONTEXT, *PCBIOS_DVO_CONTEXT;

CBIOS_VOID cbDVOPort_GetSupportMonitorType(PCBIOS_VOID pvcbe, PCBIOS_MONITOR_TYPE pMonitorType);
PCBIOS_DEVICE_COMMON cbDVOPort_Init(PCBIOS_VOID pvcbe, PVCP_INFO pVCP, CBIOS_ACTIVE_TYPE DeviceType);
CBIOS_VOID cbDVOPort_DeInit(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon);
#endif
