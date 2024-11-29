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
#ifndef VIDSCH_DUMP_IMAGE_E3K_H
#define VIDSCH_DUMP_IMAGE_E3K_H
typedef struct _HangDumpFileHeader
{
    unsigned int        nHeaderVersion;
    unsigned int        nDeviceID;
    unsigned int        nSliceMask;
    unsigned int        nHangDumpFileHeaderSizeInByte;
    unsigned int        reserved0[4];

    unsigned long long  nAdapterMemorySizeInByte;
    unsigned long long  nPCIEMemorySizeInByte;          // default 3G

    unsigned long long  nRecordNums;                    // the DMA/Context/Ring Buffer numbers which DUMP file include.

                                                        // DMA
    unsigned long long  nDmaOffset;
    unsigned long long  nSingleDmaSizeInByte;           // nRecordNums*nSingleDmaSizeInByte = 0x40000

                                                        // Context
    unsigned long long  nContextOffset;
    unsigned long long  nSingleContextSizeInByte;       // nRecordNums*nSingleContextSizeInByte = 0x160000

                                                        // Ring Buffer
    unsigned long long  nRingBufferOffset;
    unsigned long long  nSingleRingBufferSizeInByte;    // nRecordNums*nSingleRingBufferSizeInByte

    unsigned long long  nTransferBufferOffsetInFBFile;  // useless, remove it
    unsigned long long  nGartTableL3Offset;
    unsigned long long  nGartTableL2Offset;
    unsigned long long  dummyPageEntry;

    unsigned long long  nBlBufferOffset;
    unsigned long long  reserved1[0x20];
} HangDumpFileHeader;
#endif
