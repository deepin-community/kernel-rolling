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

#include "CBiosChipShare.h"
#include "CBiosCRT.h"

static CBIOS_BOOL cbCRTPort_DeviceDetect(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon, CBIOS_BOOL bHardcodeDetected, CBIOS_U32 FullDetect)
{
    PCBIOS_CRT_CONTEXT pCrtContext = container_of(pDevCommon, PCBIOS_CRT_CONTEXT, Common);
    CBIOS_BOOL         bConnected = CBIOS_FALSE;

    if ((pDevCommon == CBIOS_NULL) || (!(pDevCommon->DeviceType & CBIOS_TYPE_CRT)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return bConnected;
    }

    if ((!bConnected) && (pCrtContext->Common.SupportMonitorType & CBIOS_MONITOR_TYPE_CRT))
    {
        bConnected = cbCRTMonitor_Detect(pcbe, &pCrtContext->CRTMonitorContext, bHardcodeDetected, FullDetect);
    }

    return bConnected;
}

static CBIOS_VOID cbCRTPort_OnOff(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon, CBIOS_BOOL bOn)
{
    PCBIOS_CRT_CONTEXT pCrtContext = container_of(pDevCommon, PCBIOS_CRT_CONTEXT, Common);
    CBIOS_U32          IGAIndex = CBIOS_MODULE_INDEX_INVALID;

    if ((pDevCommon == CBIOS_NULL) || (!(pDevCommon->DeviceType & CBIOS_TYPE_CRT)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, INFO), "Invalid Para, will skip CRT ON_OFF!\n", FUNCTION_NAME));
        return;
    }

    IGAIndex = pDevCommon->DispSource.ModuleList.IGAModule.Index;

    cbCRTMonitor_OnOff(pcbe, &pCrtContext->CRTMonitorContext, bOn, (CBIOS_U8)IGAIndex);

    pDevCommon->PowerState = (bOn)? CBIOS_PM_ON : CBIOS_PM_OFF;

    cbDebugPrint((MAKE_LEVEL(GENERIC, INFO),"%s: status = %s.\n", FUNCTION_NAME, (bOn)? "On" : "Off"));
}

static CBIOS_VOID cbCRTPort_SetMode(PCBIOS_EXTENSION_COMMON pcbe, PCBIOS_DEVICE_COMMON pDevCommon, PCBIOS_DISP_MODE_PARAMS pModeParams)
{
    PCBIOS_CRT_CONTEXT pCrtContext = container_of(pDevCommon, PCBIOS_CRT_CONTEXT, Common);
    CBIOS_MONITOR_TYPE MonitorType = CBIOS_MONITOR_TYPE_NONE;

    if ((pDevCommon == CBIOS_NULL) || (!(pDevCommon->DeviceType & CBIOS_TYPE_CRT)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return ;
    }

    MonitorType = pDevCommon->CurrentMonitorType;

    if (MonitorType == CBIOS_MONITOR_TYPE_CRT)
    {
        cbCRTMonitor_SetMode(pcbe, &pCrtContext->CRTMonitorContext, pModeParams);
    }
}

PCBIOS_DEVICE_COMMON cbCRTPort_Init(PCBIOS_VOID pvcbe, PVCP_INFO pVCP, CBIOS_ACTIVE_TYPE DeviceType)
{
    PCBIOS_EXTENSION_COMMON pcbe          = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CRT_CONTEXT      pCrtContext   = CBIOS_NULL;
    PCBIOS_DEVICE_COMMON    pDeviceCommon = CBIOS_NULL;

    if(DeviceType & ~CBIOS_TYPE_CRT)
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR),"%s: unsupported device type!!!\n", FUNCTION_NAME));
        return CBIOS_NULL;
    }

    pCrtContext = cb_AllocateNonpagedPool(sizeof(CBIOS_CRT_CONTEXT));

    if(pCrtContext == CBIOS_NULL)
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR),"%s: pCrtContext allocate error!!!\n", FUNCTION_NAME));
        return CBIOS_NULL;
    }

    pDeviceCommon = &pCrtContext->Common;
    pDeviceCommon->DeviceType = DeviceType;
    pDeviceCommon->SupportMonitorType = cbGetSupportMonitorType(pcbe, DeviceType);
    pDeviceCommon->I2CBus = pVCP->CRTCharByte & I2CBUSMASK;
    pDeviceCommon->HPDPin = pVCP->CRTInterruptPort & HPDPORT_MASK;
    pDeviceCommon->CurrentMonitorType = CBIOS_MONITOR_TYPE_NONE;
    pDeviceCommon->PowerState = CBIOS_PM_INVALID;

    cbInitialModuleList(&pDeviceCommon->DispSource.ModuleList);

    pDeviceCommon->pfncbDeviceDetect = (PFN_cbDeviceDetect)cbCRTPort_DeviceDetect;
    pDeviceCommon->pfncbDeviceOnOff = (PFN_cbDeviceOnOff)cbCRTPort_OnOff;
    pDeviceCommon->pfncbDeviceSetMode = (PFN_cbDeviceSetMode)cbCRTPort_SetMode;

    pCrtContext->CRTMonitorContext.pDevCommon = pDeviceCommon;

    return pDeviceCommon;
}

CBIOS_VOID cbCRTPort_DeInit(PCBIOS_VOID pvcbe, PCBIOS_DEVICE_COMMON pDevCommon)
{
    PCBIOS_CRT_CONTEXT pCrtContext = container_of(pDevCommon, PCBIOS_CRT_CONTEXT, Common);

    if ((pDevCommon == CBIOS_NULL) || (!(pDevCommon->DeviceType & CBIOS_TYPE_CRT)))
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: the 2nd param is invalid!\n", FUNCTION_NAME));
        return;
    }

    cb_FreePool(pCrtContext);
    pCrtContext = CBIOS_NULL;

}
