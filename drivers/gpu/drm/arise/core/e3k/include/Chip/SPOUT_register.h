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
#ifndef _SPOUT_REGISTER_H
#define _SPOUT_REGISTER_H


#ifndef        SPOUT_BLOCKBASE_INF
#define    SPOUT_BLOCKBASE_INF
#define    BLOCK_SPOUT_VERSION 1
#define    BLOCK_SPOUT_TIMESTAMP "2018/6/11 22:15:55"
#define    SPOUT_BLOCK                                                0x16
#define    SPOUT_REG_START                                            0x0
#define    SPOUT_REG_END                                              0x20
#define    SPOUT_REG_LIMIT                                            0x20
#endif


#define        Reg_Spout_Cfg_Offset                                       0x0
#define        Reg_Spout_Idx_Ch_Offset                                    0x1
#define        Reg_Pos_Read_Loc_Offset                                    0x2
#define        Reg_Attr_Read_Loc0_Offset                                  0x3
#define        Reg_Attr_Read_Loc1_Offset                                  0x4
#define        Reg_Pos_Read_Id_Offset                                     0x5
#define        Reg_Attr_Read_Id_Offset                                    0x6
#define        Reg_Pos_Def_Value_Offset                                   0x12
#define        Reg_Attr_Def_Value_Offset                                  0x13
#define        Reg_Spout_Reserved_Offset                                  0x1F


typedef enum
{
    SPOUT_CFG_OUT_RAST_EN_DISABLE            = 0,
    SPOUT_CFG_OUT_RAST_EN_ENABLE             = 1,
} SPOUT_CFG_OUT_RAST_EN;
typedef enum
{
    SPOUT_CFG_STO_EN_DISABLED                = 0,
    SPOUT_CFG_STO_EN_ENABLED                 = 1,

} SPOUT_CFG_STO_EN;
typedef enum
{
    SPOUT_CFG_RTARRAY_IDX_OUT_EN_DISABLE     = 0,
    SPOUT_CFG_RTARRAY_IDX_OUT_EN_ENABLE      = 1,

} SPOUT_CFG_RTARRAY_IDX_OUT_EN;
typedef enum
{
    SPOUT_CFG_VIEWPORT_MASK_OUT_EN_DISABLE   = 0,
    SPOUT_CFG_VIEWPORT_MASK_OUT_EN_ENABLE    = 1,

} SPOUT_CFG_VIEWPORT_MASK_OUT_EN;
typedef enum
{
    SPOUT_CFG_CULLCLIP_FLAG_OUT_EN_DISABLE   = 0,
    SPOUT_CFG_CULLCLIP_FLAG_OUT_EN_ENABLE    = 1,

} SPOUT_CFG_CULLCLIP_FLAG_OUT_EN;
typedef enum
{
    SPOUT_CFG_PRIMID_APPEND_EN_DISABLE       = 0,
    SPOUT_CFG_PRIMID_APPEND_EN_ENABLE        = 1,
} SPOUT_CFG_PRIMID_APPEND_EN;
typedef enum
{
    POS_READ_LOC_POS_LOC_SEPARATED           = 0,

    POS_READ_LOC_POS_LOC_SHARED              = 1,

} POS_READ_LOC_POS_LOC;
typedef enum
{
    ATTR_READ_LOC0_ATTR_LOC_SEPARATED        = 0,

    ATTR_READ_LOC0_ATTR_LOC_SHARED           = 1,

} ATTR_READ_LOC0_ATTR_LOC;
typedef enum
{
    ATTR_READ_LOC1_ATTR_LOC_SEPARATED        = 0,

    ATTR_READ_LOC1_ATTR_LOC_SHARED           = 1,

} ATTR_READ_LOC1_ATTR_LOC;
typedef enum
{
    POS_DEF_VALUE_P0_X_DEF_DISABLED          = 0,
    POS_DEF_VALUE_P0_X_DEF_ZERO              = 1,
    POS_DEF_VALUE_P0_X_DEF_FP_ONE            = 2,
    POS_DEF_VALUE_P0_X_DEF_RESERVED          = 3,
} POS_DEF_VALUE_P0_X_DEF;
typedef enum
{
    ATTR_DEF_VALUE_A0_X_DEF_DISABLED         = 0,
    ATTR_DEF_VALUE_A0_X_DEF_ZERO             = 1,
    ATTR_DEF_VALUE_A0_X_DEF_FP_ONE           = 2,
    ATTR_DEF_VALUE_A0_X_DEF_RESERVED         = 3,
} ATTR_DEF_VALUE_A0_X_DEF;





typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Out_Rast_En               : 1;
        unsigned int Sto_En                    : 1;
        unsigned int Out_Size                  : 6;

        unsigned int Shared_Size               : 6;

        unsigned int Vtx_Pos_Size              : 2;


        unsigned int Vtx_Attr_Size             : 6;


        unsigned int Rtarray_Idx_Out_En        : 1;
        unsigned int Viewport_Mask_Out_En      : 1;
        unsigned int Cullclip_Flag_Out_En      : 1;

        unsigned int Vtx_Idx_Id                : 6;


        unsigned int Primid_Append_En          : 1;


    } reg;
} Reg_Spout_Cfg;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Rtarray_Idx_Ch            : 2;
        unsigned int Viewport_Mask_Ch          : 2;
        unsigned int Cullclip_Flag_Ch          : 2;
        unsigned int Reserved                  : 26;
    } reg;
} Reg_Spout_Idx_Ch;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Pos_Loc                   : 2;


        unsigned int Reserved                  : 30;
    } reg;
} Reg_Pos_Read_Loc;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Attr_Loc                  : 32;


    } reg;
} Reg_Attr_Read_Loc0;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Attr_Loc                  : 16;


        unsigned int Reserved                  : 16;
    } reg;
} Reg_Attr_Read_Loc1;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int P0_Addr                   : 6;


        unsigned int P1_Addr                   : 6;
        unsigned int Reserved                  : 20;
    } reg;
} Reg_Pos_Read_Id;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int A0_Addr                   : 6;

        unsigned int A1_Addr                   : 6;
        unsigned int A2_Addr                   : 6;
        unsigned int A3_Addr                   : 6;
        unsigned int Reserved                  : 8;
    } reg;
} Reg_Attr_Read_Id;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int P0_X_Def                  : 2;
        unsigned int P0_Y_Def                  : 2;
        unsigned int P0_Z_Def                  : 2;
        unsigned int P0_W_Def                  : 2;
        unsigned int P1_X_Def                  : 2;
        unsigned int P1_Y_Def                  : 2;
        unsigned int P1_Z_Def                  : 2;
        unsigned int P1_W_Def                  : 2;
        unsigned int Reserved                  : 16;
    } reg;
} Reg_Pos_Def_Value;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int A0_X_Def                  : 2;
        unsigned int A0_Y_Def                  : 2;
        unsigned int A0_Z_Def                  : 2;
        unsigned int A0_W_Def                  : 2;
        unsigned int A1_X_Def                  : 2;
        unsigned int A1_Y_Def                  : 2;
        unsigned int A1_Z_Def                  : 2;
        unsigned int A1_W_Def                  : 2;
        unsigned int A2_X_Def                  : 2;
        unsigned int A2_Y_Def                  : 2;
        unsigned int A2_Z_Def                  : 2;
        unsigned int A2_W_Def                  : 2;
        unsigned int A3_X_Def                  : 2;
        unsigned int A3_Y_Def                  : 2;
        unsigned int A3_Z_Def                  : 2;
        unsigned int A3_W_Def                  : 2;
    } reg;
} Reg_Attr_Def_Value;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Reserved                  : 32;
    } reg;
} Reg_Spout_Reserved;

typedef struct _Spout_regs
{
    Reg_Spout_Cfg                    reg_Spout_Cfg;
    Reg_Spout_Idx_Ch                 reg_Spout_Idx_Ch;
    Reg_Pos_Read_Loc                 reg_Pos_Read_Loc;
    Reg_Attr_Read_Loc0               reg_Attr_Read_Loc0;
    Reg_Attr_Read_Loc1               reg_Attr_Read_Loc1;
    Reg_Pos_Read_Id                  reg_Pos_Read_Id;
    Reg_Attr_Read_Id                 reg_Attr_Read_Id[12];
    Reg_Pos_Def_Value                reg_Pos_Def_Value;
    Reg_Attr_Def_Value               reg_Attr_Def_Value[12];
    Reg_Spout_Reserved               reg_Spout_Reserved;
} Spout_regs;

#endif
