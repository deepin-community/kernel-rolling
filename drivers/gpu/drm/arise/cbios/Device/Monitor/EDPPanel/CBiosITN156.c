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
#include "../../../Hw/HwCallback/CBiosCallbacksHw.h"
#include "../CBiosEDPPanel.h"

// eDP panel pre-initialization, if something must be done before detecting, do here, and set ITN156_Panel_Desc.EDPPreCaps.IsNeedPreInit = CBIOS_TRUE.
CBIOS_STATUS INT156_PreInit(PCBIOS_VOID pvcbe)
{
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    // use cbRequestGPIO to request GPIO
    // use cbSetGPIODirectionOutput to set GPIO direction

    return Status;
}


// eDP panel initialization
CBIOS_STATUS INT156_Init(PCBIOS_VOID pvcbe)
{
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    // use cbRequestGPIO to request GPIO
    // use cbSetGPIODirectionOutput to set GPIO direction

    return Status;
}


CBIOS_STATUS INT156_DeInit(PCBIOS_VOID pvcbe)
{
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    // use cbFreeGPIO to free GPIO

    return Status;
}


// set panel backlight
CBIOS_STATUS INT156_SetBacklight(PCBIOS_VOID pvcbe, CBIOS_U32 BacklightValue)
{
    CBIOS_U16 PwmFrequencyCounter = 0xff;    //frequency = 27Mhz / PwmFrequencyCounter:about 105khz
    CBIOS_U16 DutyCycle           = (CBIOS_U16)BacklightValue;    // 0 ~ 255 means:0% ~ 100%
    CBIOS_U32 RegValue            = 0;

    RegValue = 0;    // PWM pulse value is mm346c[15:0]
    cbWriteRegisterU32WithMask(pvcbe, CBIOS_REGISTER_MMIO, 0x8180, RegValue, 0);

    //set PWM frequency counter
    RegValue = PwmFrequencyCounter << 16;    //mm346c[31:16]:PwmFrequencyCounter
    cbWriteRegisterU32WithMask(pvcbe, CBIOS_REGISTER_MMIO, 0x346C, RegValue, 0x0000FFFF);

    //duty cycle
    RegValue = 8 << 4;    // mm3470[7:4] = 4'b1000: pwm_duty = {8'b0, mm346c[15:8]}
    cbWriteRegisterU32WithMask(pvcbe, CBIOS_REGISTER_MMIO, 0x3470, RegValue, 0xFFFFFF0F);

    RegValue = ((CBIOS_U16)DutyCycle) << 8;//mm346c[15:0] : PWM pulse value
    cbWriteRegisterU32WithMask(pvcbe, CBIOS_REGISTER_MMIO, 0x346C, RegValue, 0xFFFF0000);

    RegValue = cbReadRegisterU32(pvcbe, CBIOS_REGISTER_MMIO, 0x3470);
    if(!(RegValue & 0x1))    //if pwm is not enabled, enable it. mm346c[0]:enable/disable pwm
    {
        RegValue = 0x1;
        cbWriteRegisterU32WithMask(pvcbe, CBIOS_REGISTER_MMIO, 0x3470, RegValue, 0xFFFFFFFE);
    }

    return CBIOS_OK;
}

// get panel backlight
CBIOS_STATUS INT156_GetBacklight(PCBIOS_VOID pvcbe, CBIOS_U32 *pBacklightValue)
{
    CBIOS_U16 DutyCycle     = 0;
    CBIOS_U32 RegValue      = 0;

    RegValue = cbReadRegisterU32(pvcbe, CBIOS_REGISTER_MMIO, 0x346C);

    DutyCycle = (CBIOS_U16)(RegValue & 0xFFFF);    //mm346c[15:0]

    //reflect it to 0~255
    *pBacklightValue = (CBIOS_U8)(DutyCycle >> 8);

    return CBIOS_OK;
}

// eDP panel power & diaplay onoff
CBIOS_STATUS INT156_OnOff(PCBIOS_VOID pvcbe, CBIOS_BOOL bTurnOn)
{
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    // use cbWriteGPIO to write GPIO
    // use cbDelayMilliSeconds to delay

    if(bTurnOn)
    {
        INT156_SetBacklight(pvcbe, 255);   //set max backlight when turn on
    }
    else
    {
        INT156_SetBacklight(pvcbe, 0);   //set min backlight when turn off
    }

    return Status;
}


CBIOS_EDP_PANEL_DESC ITN156_Panel_Desc =
{
    /*.VersionNum = */CBIOS_EDP_VERSION,
    /*.MonitorID = */"SDC4852",
    /*.EDPPreCaps =*/
    {
        /*.IsNeedPreInit = */CBIOS_TRUE,
        /*.pFnEDPPanelPreInit =*/ INT156_PreInit,
    },
    /*.EDPCaps = */
    {
        /*.LinkSpeed = */2700000,
        /*.LaneNum = */4,
        /*.BacklightMax = */255,
        /*.BacklightMin = */0,
        /*.Flags = */0,//backlight control = 0, use hard code link para
    },
    /*.pFnEDPPanelInit = */INT156_Init,
    /*.pFnEDPPanelDeInit = */INT156_DeInit,
    /*.pFnEDPPanelOnOff = */INT156_OnOff,
    /*.pFnEDPPanelSetBacklight = */INT156_SetBacklight,
    /*.pFnEDPPanelGetBacklight = */INT156_GetBacklight,
};


