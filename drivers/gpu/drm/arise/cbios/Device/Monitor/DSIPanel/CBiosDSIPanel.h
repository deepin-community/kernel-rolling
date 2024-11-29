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

#ifndef _CBIOS_DSI_PANEL_H_
#define _CBIOS_DSI_PANEL_H_


#include "../../CBiosShare.h"
#include "../../../Callback/CBiosCallbacks.h"
#include "../../../Hw/HwCallback/CBiosCallbacksHw.h"


typedef struct _GPIO_PORT
{
    CBIOS_GPIO_TYPE GPIOType;
    CBIOS_U32 GPIOIndex;
}GPIO_PORT, *PGPIO_PORT;

typedef enum _CBIOS_DSI_MODE
{
    CBIOS_DSI_VIDEOMODE = 0x01,
    CBIOS_DSI_CMDMODE = 0x02
}CBIOS_DSI_MODE;

typedef enum _CBIOS_DSI_SYNC_PACKET_TYPE
{
    CBIOS_DSI_SYNC_PULSE = 0x01,
    CBIOS_DSI_SYNC_EVENT = 0x02,
}CBIOS_DSI_SYNC_PACKET_TYPE;

typedef enum _CBIOS_DSI_TE_TYPE
{
    CBIOS_DSI_TE_TRIGGER = 0x01,
    CBIOS_DSI_TE_PAD     = 0x02,
}CBIOS_DSI_TE_TYPE;

typedef enum _CBIOS_DSI_CLK_LANE_MODE
{
    CBIOS_DSI_CLK_LANE_SOFTWARE_CTL = 0x01,
    CBIOS_DSI_CLK_LANE_HARDWARE_CTL = 0x02,
}CBIOS_DSI_CLK_LANE_MODE;

typedef struct _CBIOS_DSI_CONFIG
{
    CBIOS_DSI_MODE                DSIMode;                 /* 1: video mode; 2: command mode */
    CBIOS_DSI_CLK_LANE_MODE       ClkLaneMode;             /* 1: software control; 2: hardware control */
    CBIOS_DSI_SYNC_PACKET_TYPE    SyncPacketType;          /* 1: sync pulse; 2: sync event */
    CBIOS_DSI_TE_TYPE             TEType;                  /* 1: trigger; 2: pad */
    CBIOS_U32                     TurnAroundTimeout;       /* unit: tBClk */
    CBIOS_U32                     HS_TXTimeout;            /* unit: tBClk */
    CBIOS_U32                     LP_RXTimeout;            /* unit: tBClk */
    CBIOS_U32                     DMAThreshold;
    CBIOS_U32                     BacklightMax;
    CBIOS_U32                     BacklightMin;

    union
    {
        CBIOS_U32                 ConfigFlags;
        struct
        {
            CBIOS_U32             isEnableEoTp      :1;
            CBIOS_U32             isHFPEnterLP      :1;
            CBIOS_U32             isHSAEnterLP      :1;
            CBIOS_U32             isHBPEnterLP      :1;
            CBIOS_U32             isBLCtrlSupport   :1;
            CBIOS_U32             isDualChannel     :1;
            CBIOS_U32             Reserved          :26;
        };
    };
}CBIOS_DSI_CONFIG, *PCBIOS_DSI_CONFIG;

typedef struct _CBIOS_DSI_TIMING
{
    CBIOS_U32    XResolution;
    CBIOS_U32    YResolution;
    CBIOS_U32    DCLK;
    CBIOS_U32    HorTotal;
    CBIOS_U32    HorDisEnd;
    CBIOS_U32    HorBStart;
    CBIOS_U32    HorBEnd;
    CBIOS_U32    HorSyncStart;
    CBIOS_U32    HorSyncEnd;
    CBIOS_U32    VerTotal;
    CBIOS_U32    VerDisEnd;
    CBIOS_U32    VerBStart;
    CBIOS_U32    VerBEnd;
    CBIOS_U32    VerSyncStart;
    CBIOS_U32    VerSyncEnd;
    CBIOS_U32    HVPolarity;
}CBIOS_DSI_TIMING, *PCBIOS_DSI_TIMING;

typedef struct _CBIOS_DSI_PANEL_TABLE
{
    CBIOS_U32           LaneNum;
    CBIOS_U32           OutBpp;
    CBIOS_DSI_TIMING    PanelTiming;
} CBIOS_DSI_PANEL_TABLE, *PCBIOS_DSI_PANEL_TABLE;

typedef struct _CBIOS_DSI_CMD_DESC
{
    CBIOS_U32                  DSIIndex;       // 0: DSI-1, 1:DSI-2
    CBIOS_U32                  VirtualCh;      // refer MIPI-DSI spec 4.2.3
    CBIOS_U32                  PacketType;     // 0: short packet, 1: long packet
    CBIOS_U32                  ContentType;    // 0: DCS write cmd, 1: generic write cmd
    CBIOS_U32                  WaitTime;       // unit: ms
    CBIOS_U32                  DataLen;
    PCBIOS_U8                  pDataBuf;
    union
    {
        CBIOS_U32              DSIFlags;
        struct
        {
            CBIOS_U32          bNeedAck        :1;    // 1: the cmd need acknowledge, 0: no need
            CBIOS_U32          bHSModeOnly     :1;    // 1: the cmd can be transferred in hs mode only, 0: both LP and HS mode
            CBIOS_U32          Reserved        :6;
        };
    };
}CBIOS_DSI_CMD_DESC, *PCBIOS_DSI_CMD_DESC;

/*It's for environment initial and can be called only once.*/
typedef CBIOS_STATUS  (*PFN_cbDSIPanel_Init)(PCBIOS_VOID pvcbe);



typedef CBIOS_STATUS  (*PFN_cbDSIPanel_DeInit)(PCBIOS_VOID pvcbe);
typedef CBIOS_STATUS  (*PFN_cbDSIPanel_PowerOnOff)(PCBIOS_VOID  pvcbe, CBIOS_BOOL bTurnOn);
typedef CBIOS_STATUS  (*PFN_cbDSIPanel_SetBacklight)(PCBIOS_VOID pvcbe, CBIOS_U32 BrightnessValue);
typedef CBIOS_STATUS  (*PFN_cbDSIPanel_GetBacklight)(PCBIOS_VOID pvcbe, CBIOS_U32 *pBrightnessValue);
typedef CBIOS_STATUS  (*PFN_cbDSIPanel_SetCabc)(PCBIOS_VOID pvcbe,CBIOS_U32 CabcValue);


typedef struct _CBIOS_DSI_PANEL_DESC
{
    CBIOS_U32                VersionNum;
    CBIOS_DSI_CONFIG         DSIConfig;
    CBIOS_DSI_PANEL_TABLE    DSIPanelTbl;
    CBIOS_U32                PowerOnCmdListSize;
    CBIOS_U32                PowerOffCmdListSize;
    CBIOS_U32                DisplayOnCmdListSize;
    CBIOS_U32                DisplayOffCmdListSize;
    CBIOS_U32                BacklightCmdListSize;
    PCBIOS_DSI_CMD_DESC      pPowerOnCmdList;
    PCBIOS_DSI_CMD_DESC      pPowerOffCmdList;
    PCBIOS_DSI_CMD_DESC      pDisplayOnCmdList;
    PCBIOS_DSI_CMD_DESC      pDisplayOffCmdList;
    PCBIOS_DSI_CMD_DESC      pBacklightCmdList;
    PFN_cbDSIPanel_PowerOnOff pFnDSIPanelOnOff;
    PFN_cbDSIPanel_SetBacklight    pFnDSIPanelSetBacklight;
    PFN_cbDSIPanel_GetBacklight    pFnDSIPanelGetBacklight;
    PFN_cbDSIPanel_SetCabc         pFnDSIPanelSetCABC;
    PFN_cbDSIPanel_Init            pFnDSIPanelInit;
    PFN_cbDSIPanel_DeInit          pFnDSIPanelDeInit;
}CBIOS_DSI_PANEL_DESC, *PCBIOS_DSI_PANEL_DESC;

PCBIOS_DSI_PANEL_DESC cbDSIPanel_GetPanelDescriptor(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbDSIPanel_Init(PCBIOS_VOID pvcbe, PCBIOS_DSI_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbDSIPanel_DeInit(PCBIOS_VOID pvcbe, PCBIOS_DSI_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbDSIPanel_OnOff(PCBIOS_VOID pvcbe, CBIOS_BOOL bTurnOn, PCBIOS_DSI_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbDSIPanel_SetBacklight(PCBIOS_VOID pvcbe, CBIOS_U32 BacklightValue, PCBIOS_DSI_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbDSIPanel_GetBacklight(PCBIOS_VOID pvcbe, CBIOS_U32 *pBacklightValue, PCBIOS_DSI_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbDSIPanel_DisplayOnOff(PCBIOS_VOID pvcbe, CBIOS_BOOL bTurnOn, PCBIOS_DSI_PANEL_DESC pPanelDesc);
CBIOS_STATUS cbDSIPanel_SetCabc(PCBIOS_VOID pvcbe, CBIOS_U32 CabcValue, PCBIOS_DSI_PANEL_DESC pPanelDesc);

#endif
