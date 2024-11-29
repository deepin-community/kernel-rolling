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
#ifndef __ERRNO_H_
#define __ERRNO_H_

#define S_OK                0x00000000
#define E_OUTOFMEMORY       0x80000002
#define E_NOIMPL            0x80004001
#define E_INVALIDARG        0x80070057
#define E_NOINTERFACE       0x80004002
#define E_POINTER           0x80004003
#define E_UNEXPECTED        0x8000FFFF
#define E_FAIL              0x10004005
#define E_UNSWIZZLING_APERTURE_UNSUPPORTED  0x10004006
/*page out allocation but allocation still used by GPU hw*/
#define E_PAGEOUT_ALLOCATION_BUSY  0x10004007
#define E_INSUFFICIENT_DMA_BUFFER   0xFFFF0001


#endif

