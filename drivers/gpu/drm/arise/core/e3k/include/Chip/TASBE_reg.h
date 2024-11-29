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
#ifndef _TASBE_REG_H
#define _TASBE_REG_H


#ifndef        TASBE_BLOCKBASE_INF
#define    TASBE_BLOCKBASE_INF
#define    BLOCK_TASBE_VERSION 1
#define    BLOCK_TASBE_TIMESTAMP "10/13/2017 10:19:33 AM"
#define    TASBE_BLOCK                                                0x5
#define    TASBE_REG_START                                            0x0
#define    TASBE_REG_END                                              0x8
#define    TASBE_REG_LIMIT                                            0x8
#endif


#define        Reg_Tasbe_Reserved_Offset                                  0x1


typedef enum
{
    TASBE_CTRL_TBR_EN_DISABLE                = 0,
    TASBE_CTRL_TBR_EN_ENABLE                 = 1,
} TASBE_CTRL_TBR_EN;
typedef enum
{
    TASBE_CTRL_TBR_MODE_PER_DRAW             = 0,
    TASBE_CTRL_TBR_MODE_PER_FRAME            = 1,
} TASBE_CTRL_TBR_MODE;
typedef enum
{
    TASBE_CTRL_TILE_SIZE_256X128             = 0,
    TASBE_CTRL_TILE_SIZE_128X128             = 1,
    TASBE_CTRL_TILE_SIZE_128X64              = 2,
    TASBE_CTRL_TILE_SIZE_64X64               = 3,
    TASBE_CTRL_TILE_SIZE_64X32               = 4,
    TASBE_CTRL_TILE_SIZE_32X32               = 5,
    TASBE_CTRL_TILE_SIZE_32X16               = 6,
    TASBE_CTRL_TILE_SIZE_16X16               = 7,
    TASBE_CTRL_TILE_SIZE_16X8                = 8,
    TASBE_CTRL_TILE_SIZE_8X8                 = 9,
} TASBE_CTRL_TILE_SIZE;





typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Reserved                  : 32;
    } reg;
} Reg_Tasbe_Reserved;

typedef struct _Tasbe_regs
{
    struct
    {
        unsigned int Tbr_En                    : 1;
        unsigned int Tbr_Mode                  : 1;
        unsigned int Tile_Size                 : 4;
        unsigned int Attr_Num                  : 6;
        unsigned int Msaa_State                : 3;

        unsigned int Aa_En                     : 1;
        unsigned int Raster_Mode               : 1;
        unsigned int Reserved                  : 15;
    }  reg_Tasbe_Ctrl;
    Reg_Tasbe_Reserved               reg_Tasbe_Reserved[7];
} Tasbe_regs;

#endif
