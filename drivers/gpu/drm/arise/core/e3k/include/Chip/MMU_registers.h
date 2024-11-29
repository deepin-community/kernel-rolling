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
#ifndef _MMU_REGISTERS_H
#define _MMU_REGISTERS_H

#ifndef        MMU_BLOCKBASE_INF
    #define    MMU_BLOCKBASE_INF
    #define    BLOCK_MMU_VERSION 1
    #define    BLOCK_MMU_TIMESTAMP "2017/8/17 15:52:06"
    #define    MMU_BLOCK                                                  0x12
    #define    MMU_REG_START                                              0x0
    #define    MMU_REG_END                                                0x1000
    #define    MMU_REG_LIMIT                                              0x1000
#endif

#define        Reg_Mmu_Ttbr_Offset                                        0x0

typedef union
{
    unsigned int uint;
    struct
    {
        unsigned int Valid                     : 1;
        unsigned int Ns                        : 1;
        unsigned int Snoop                     : 1;
        unsigned int Segment                   : 1;
        unsigned int Addr                      : 24;
        unsigned int Reserved                  : 4;
    } reg;
} Reg_Ttbr;

typedef struct _Group_Mmu_Ttbr
{
    Reg_Ttbr                         reg_Ttbr;
} Reg_Mmu_Ttbr_Group;

typedef struct _Mmu_regs
{
    Reg_Mmu_Ttbr_Group               reg_Mmu_Ttbr[4096];
} Mmu_regs;

#endif
