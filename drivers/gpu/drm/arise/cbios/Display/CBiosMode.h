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

#ifndef _CBIOS_MODE_H_
#define _CBIOS_MODE_H_

#define CBIOS_PROGRESSIVECAP                                   0x01
#define CBIOS_INTERLACECAP                                     0x02
#define CBIOS_PROGRESSIVEVALUE                                 0x01
#define CBIOS_INTERLACEVALUE                                   0x00

#define CBIOS_ADAPTERMODE                                      0
#define CBIOS_DEVICEMODE                                       1

#define CBIOS_ASPECTRATIOCAP4B3                                0x01
#define CBIOS_ASPECTRATIOCAP16B9                               0x02
#define CBIOS_ASPECTRATIOCAP64B27                              0x03
#define CBIOS_ASPECTRATIOCAP256B135                            0x04
#define CBIOS_DEFAULTRATIO                                     0x00

#define CBIOS_NATIVEMODE                                       1
#define CBIOS_NONNATIVEMODE                                    0

#define CBIOS_PERFERREDMODE                                    BIT18
#define CBIOS_NONPERFERREDMODE                                 0

typedef enum _CBIOS_MODE_TIMING_TYPE{  //can extend to support 14 different types
    CBIOS_MODE_NONEDID_TIMING = 0x0000,    //The mode is not from EDID
    CBIOS_MODE_EST_TIMING = 0x0001,
    CBIOS_MODE_STD_TIMING = 0x0002,
    CBIOS_MODE_DTL_TIMING = 0x0004,
    CBIOS_MODE_SVD_TIMING = 0x0008,        //Detailed timing descriptor
    CBIOS_MODE_DTD_TIMING = 0x0010,        //CBIOS_S16 video descriptor
    CBIOS_MODE_DISPLAYID_TYPE1_TIMING = 0x0020
}CBIOS_MODE_TIMING_TYPE, *PCBIOS_MODE_TIMING_TYPE;

typedef struct _CBIOS_MODE_INFO {
    union {
        struct {
#ifdef __BIG_ENDIAN__
            CBIOS_U16 XResolution;
            CBIOS_U16 YResolution;
#else
            CBIOS_U16 YResolution;
            CBIOS_U16 XResolution;
#endif
        };
        CBIOS_U32 XYResolution;
    };
    CBIOS_U16 Refreshrate;
    CBIOS_BOOL Valid;
}CBIOS_MODE_INFO, *PCBIOS_MODE_INFO;

typedef struct _CBIOS_MODE_INFO_EXT {
    union{
        struct{
#ifdef __BIG_ENDIAN__
            union{
                CBIOS_U16 XResolution;
                CBIOS_U16 HActive;
            };
            union{
                CBIOS_U16 YResolution;
                CBIOS_U16 VActive;
            };
#else
            union{
                CBIOS_U16 YResolution;
                CBIOS_U16 VActive;
            };
            union{
                CBIOS_U16 XResolution;
                CBIOS_U16 HActive;
            };
#endif
        };
        CBIOS_U32 XYResolution;
    };
    CBIOS_U16 HBlank;
    CBIOS_U16 HSyncOffset;
    CBIOS_U16 HSyncPulseWidth;
    CBIOS_U16 VBlank;
    CBIOS_U16 VSyncOffset;
    CBIOS_U16 VSyncPulseWidth;
    CBIOS_U16 HImageSize;
    CBIOS_U16 VImageSize;
    CBIOS_U32 PixelClock;
    CBIOS_U16 Refreshrate;
    CBIOS_BOOL Valid;
    CBIOS_U8 InterLaced;
    CBIOS_U8 VSync;
    CBIOS_U8 HSync;
    CBIOS_U8 AspectRatio;    /* 0 means default, 1 means 4:3, 2 means 16:9 */
    CBIOS_U8 IsNativeMode;
}CBIOS_MODE_INFO_EXT, *PCBIOS_MODE_INFO_EXT;

typedef struct _CBios_Equivalent_Device_Mode
{
    CBIOS_U32 XRes;
    CBIOS_U32 YRes;
    CBIOS_U32 RefRateRange[2];
    CBIOS_U32 RefRateToAdd;
}CBiosEquivalentDeviceMode, PCBiosEquivalentDeviceMode;

typedef struct _CBIOS_MODE_FILTER_PARA{
    CBIOS_BOOL bFilterInterlace;
    CBIOS_U32  MaxDclk;
}CBIOS_MODE_FILTER_PARA, *PCBIOS_MODE_FILTER_PARA;


CBIOS_BOOL cbMode_GetHVTiming(PCBIOS_VOID pvcbe,
                              CBIOS_U32 XRes,
                              CBIOS_U32 YRes,
                              CBIOS_U32 Refresh,
                              CBIOS_U32 isInterlace,
                              CBIOS_ACTIVE_TYPE Device,
                              PCBIOS_TIMING_ATTRIB pTiming);
CBIOS_U32 cbMode_GetDefaultModeList(PCBIOS_VOID pvcbe, PCBiosModeInfoExt pModeList, CBIOS_ACTIVE_TYPE Device);
CBIOS_VOID cbMode_GetAdapterModeNum(PCBIOS_VOID pvcbe, CBIOS_U32* AdapterModeNum);
CBIOS_STATUS cbMode_FillAdapterModeList(PCBIOS_VOID pvcbe, PCBiosModeInfoExt pModeList, CBIOS_U32 *pBufferSize);
CBIOS_VOID cbMode_GetFilterPara(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE Device, PCBIOS_MODE_FILTER_PARA pFilter);
CBIOS_U32 cbMode_GetDeviceModeList(PCBIOS_VOID pvcbe,
                                   CBIOS_ACTIVE_TYPE  Device,
                                   PCBiosModeInfoExt pModeList,
                                   CBIOS_U32 *pBufferSize,
                                   PCBIOS_MODE_FILTER_PARA pFilter);

#endif
