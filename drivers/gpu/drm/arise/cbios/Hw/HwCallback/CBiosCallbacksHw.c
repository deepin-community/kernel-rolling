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

#include "CBiosCallbacksHw.h"
#include "CBiosChipShare.h"


extern CBIOS_CALLBACK_FUNCTIONS FnCallback;

CBIOS_VOID cb_WriteU8(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_UCHAR Value)
{
    if (FnCallback.pFnWriteUchar != CBIOS_NULL)
    {
        ((CALLBACK_cbWriteU8)FnCallback.pFnWriteUchar)(pAdapterContext, RegisterPort, Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

}



CBIOS_VOID cb_WriteU16(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_U16 Value)
{
    if (FnCallback.pFnWriteUshort != CBIOS_NULL)
    {
        ((CALLBACK_cbWriteU16)FnCallback.pFnWriteUshort)(pAdapterContext, RegisterPort, Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

}



CBIOS_VOID cb_WriteU32(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort, CBIOS_U32 Value)
{
    if (FnCallback.pFnWriteUlong != CBIOS_NULL)
    {
        ((CALLBACK_cbWriteU32)FnCallback.pFnWriteUlong)(pAdapterContext, RegisterPort, Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

}



CBIOS_UCHAR cb_ReadU8(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort)
{

    CBIOS_UCHAR ret = 0;

    if(FnCallback.pFnReadUchar != CBIOS_NULL)
    {
        ret = ((CALLBACK_cbReadU8)FnCallback.pFnReadUchar)(pAdapterContext, RegisterPort);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

    return ret;

}



CBIOS_U16 cb_ReadU16(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort)
{

    CBIOS_U16 ret = 0;

    if(FnCallback.pFnReadUshort!= CBIOS_NULL)
    {
        ret = ((CALLBACK_cbReadU16)FnCallback.pFnReadUshort)(pAdapterContext, RegisterPort);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

    return ret;

}


CBIOS_U32 cb_ReadU32(PCBIOS_VOID  pAdapterContext, CBIOS_U32 RegisterPort)
{
    CBIOS_U32 ret = 0;

    if(FnCallback.pFnReadUlong != CBIOS_NULL)
    {
        ret = ((CALLBACK_cbReadU32)FnCallback.pFnReadUlong)(pAdapterContext, RegisterPort);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

    return ret;

}




/*use IO to access VGA registers under NT platforms*/
CBIOS_UCHAR cb_ReadPortUchar(PCBIOS_UCHAR RegisterPort)
{
    CBIOS_UCHAR ret = 0;

    if(FnCallback.pFnReadPortUchar != CBIOS_NULL)
    {
        ret = ((CALLBACK_cbReadPortUchar)FnCallback.pFnReadPortUchar)(RegisterPort);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

    return ret;

}



CBIOS_VOID cb_WritePortUchar(PCBIOS_UCHAR RegisterPort, CBIOS_UCHAR Value)
{

    if (FnCallback.pFnWritePortUchar != CBIOS_NULL)
    {
        ((CALLBACK_cbWritePortUchar)FnCallback.pFnWritePortUchar)(RegisterPort, Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

}



CBIOS_VOID cbWriteRegisterU32(PCBIOS_VOID pvcbe, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex,CBIOS_U32 Value)
{
    PCBIOS_EXTENSION_COMMON pcbe = pvcbe;

    if (FnCallback.pFnWriteRegisterU32 != CBIOS_NULL)
    {
         ((CALLBACK_cbWriteRegisterU32)FnCallback.pFnWriteRegisterU32)(pcbe->pAdapterContext, RegType, RegIndex,Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }
}



CBIOS_VOID cbWriteRegisterU32WithMask(PCBIOS_VOID pvcbe, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex, CBIOS_U32 Value, CBIOS_U32 Mask)
{
    PCBIOS_EXTENSION_COMMON pcbe = pvcbe;
    CBIOS_U32 Temp = 0;

    if ((FnCallback.pFnWriteRegisterU32 != CBIOS_NULL) && (FnCallback.pFnReadRegisterU32 != CBIOS_NULL))
    {
        Temp = ((CALLBACK_cbReadRegisterU32)FnCallback.pFnReadRegisterU32)(pcbe->pAdapterContext, RegType, RegIndex) & Mask;
        Value &= (~Mask);
        Value |= Temp;
        ((CALLBACK_cbWriteRegisterU32)FnCallback.pFnWriteRegisterU32)(pcbe->pAdapterContext, RegType, RegIndex, Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }
}



CBIOS_U32 cbReadRegisterU32(PCBIOS_VOID pvcbe, CBIOS_REGISTER_BLOCK_TYPE RegType, CBIOS_U32 RegIndex)
{
    PCBIOS_EXTENSION_COMMON pcbe = pvcbe;
    CBIOS_U32 Temp = 0;

    if (FnCallback.pFnReadRegisterU32 != CBIOS_NULL)
    {
        Temp = ((CALLBACK_cbReadRegisterU32)FnCallback.pFnReadRegisterU32)(pcbe->pAdapterContext, RegType, RegIndex);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

    return Temp;
}


CBIOS_U32 cbReadGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex)
{
    CBIOS_U32 ret = 0;

    if(FnCallback.pFnGpioGetValue != CBIOS_NULL)
    {
        ret = ((CALLBACK_cbGetSysGPIO)FnCallback.pFnGpioGetValue)(GPIOIndex, (GPIOType << 8) );
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

    return ret;
}



CBIOS_VOID cbWriteGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex, CBIOS_U32 Value)
{

    if (FnCallback.pFnGpioSetValue != CBIOS_NULL)
    {
        ((CALLBACK_cbSetSysGPIO)FnCallback.pFnGpioSetValue)(GPIOIndex, (GPIOType << 8), Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback func is not defined!\n", FUNCTION_NAME));
    }

}


//gpio
CBIOS_STATUS cbRequestGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex)
{
    CBIOS_STATUS Ret = CBIOS_ER_LAST;

    if (FnCallback.pFnGpioRequest != CBIOS_NULL)
    {
        Ret = ((CALLBACK_cbRequestSysGPIO)FnCallback.pFnGpioRequest)(GPIOIndex , (GPIOType << 8) );
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Ret;
}


CBIOS_VOID cbFreeGPIO(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex)
{
    if (FnCallback.pFnGpioFree != CBIOS_NULL)
    {
        ((CALLBACK_cbFreeSysGPIO)FnCallback.pFnGpioFree)(GPIOIndex , (GPIOType << 8) );
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }
}



CBIOS_STATUS cbSetGPIODirectionInput(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex)
{
    CBIOS_STATUS ret = CBIOS_ER_LAST;

    if(FnCallback.pFnGpioDirectionInput != CBIOS_NULL )
    {
        ret = ((CALLBACK_cbSysGPIODirectionInput)FnCallback.pFnGpioDirectionInput)(GPIOIndex , (GPIOType << 8) );
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return ret ;
}



CBIOS_STATUS cbSetGPIODirectionOutput(PCBIOS_VOID pvcbe, CBIOS_GPIO_TYPE GPIOType, CBIOS_U32 GPIOIndex, CBIOS_U32 Value)
{
    CBIOS_STATUS ret = CBIOS_ER_LAST;

    if(FnCallback.pFnGpioDirectionOutput != CBIOS_NULL )
    {
        ret = ((CALLBACK_cbSysGPIODirectionOutput)FnCallback.pFnGpioDirectionOutput)(GPIOIndex , (GPIOType << 8) , Value);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return ret ;
}



//regulator
PCBIOS_VOID cbRegulatorGet(PCBIOS_VOID pvcbe, PCBIOS_CHAR id)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_VOID Regulator = CBIOS_NULL;

    if (FnCallback.pFnRegulatorGet != CBIOS_NULL)
    {
        Regulator = ((CALLBACK_cbRegulatorGet)FnCallback.pFnRegulatorGet)(pcbe->pAdapterContext, id);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Regulator;
}



CBIOS_STATUS   cbRegulatorEnable(PCBIOS_VOID Regulator)
{
    CBIOS_STATUS Ret = CBIOS_ER_LAST;

    if (FnCallback.pFnRegulatorEnable != CBIOS_NULL)
    {
        Ret = ((CALLBACK_cbRegulatorEnable)FnCallback.pFnRegulatorEnable)(Regulator);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Ret;
}



CBIOS_STATUS   cbRegulatorDisable(PCBIOS_VOID Regulator)
{
    CBIOS_STATUS Ret = CBIOS_ER_LAST;

    if (FnCallback.pFnRegulatorDisable != CBIOS_NULL)
    {
        Ret = ((CALLBACK_cbRegulatorDisable)FnCallback.pFnRegulatorDisable)(Regulator);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Ret;
}



CBIOS_S32   cbRegulatorIsEnabled(PCBIOS_VOID Regulator)
{
    CBIOS_S32 Ret = 0;

    if (FnCallback.pFnRegulatorIsEnabled != CBIOS_NULL)
    {
        Ret = ((CALLBACK_cbRegulatorIsEnabled)FnCallback.pFnRegulatorIsEnabled)(Regulator);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Ret;
}



CBIOS_S32   cbRegulatorGetVoltage(PCBIOS_VOID Regulator)
{
    CBIOS_S32 Ret = 0;

    if (FnCallback.pFnRegulatorGetVoltage != CBIOS_NULL)
    {
        Ret = ((CALLBACK_cbRegulatorGetVoltage)FnCallback.pFnRegulatorGetVoltage)(Regulator);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Ret;
}



CBIOS_STATUS   cbRegulatorSetVoltage(PCBIOS_VOID Regulator, CBIOS_S32 min_uV,CBIOS_S32 max_uV)
{
    CBIOS_STATUS Ret = CBIOS_ER_LAST;

    if (FnCallback.pFnRegulatorSetVoltage != CBIOS_NULL)
    {
        Ret = ((CALLBACK_cbRegulatorSetVoltage)FnCallback.pFnRegulatorSetVoltage)(Regulator, min_uV, max_uV);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

    return Ret;
}



CBIOS_VOID  cbRegulatorPut(PCBIOS_VOID Regulator)
{
    if (FnCallback.pFnRegulatorPut != CBIOS_NULL)
    {
        ((CALLBACK_cbRegulatorPut)FnCallback.pFnRegulatorPut)(Regulator);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: callback not defined!\n",FUNCTION_NAME));
    }

}


