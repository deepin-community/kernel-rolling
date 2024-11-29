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
#ifndef _SPIN_REGISTER_H
#define _SPIN_REGISTER_H


#ifndef        SPIN_BLOCKBASE_INF
    #define    SPIN_BLOCKBASE_INF
    #define    BLOCK_SPIN_VERSION 1
    #define    BLOCK_SPIN_TIMESTAMP "2017/9/27 15:04:28"
    #define    SPIN_BLOCK                                                 0x2
    #define    SPIN_REG_START                                             0x0
    #define    SPIN_REG_END                                               0x8
    #define    SPIN_REG_LIMIT                                             0x8
#endif


#define        Reg_Sp_Dummy1_Offset                                       0x0
#define        Reg_Sp_Dummy2_Offset                                       0x1
#define        Reg_Sp_Reserved_Offset                                     0x2







typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Reserved                  : 32;
    } reg;
} Reg_Sp_Dummy1;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Reserved                  : 32;
    } reg;
} Reg_Sp_Dummy2;

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Reserved                  : 32;
    } reg;
} Reg_Sp_Reserved;

typedef struct _Spin_regs
{
    Reg_Sp_Dummy1                    reg_Sp_Dummy1;
    Reg_Sp_Dummy2                    reg_Sp_Dummy2;
    Reg_Sp_Reserved                  reg_Sp_Reserved[6];
} Spin_regs;

#endif
