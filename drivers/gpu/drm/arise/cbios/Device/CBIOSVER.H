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

#define CBIOS_VERSION_MAJOR                     10    /* Branch CBios code */
#define CBIOS_VERSION_BRANCH                    17    /* Big change such as structure modification */
#define CBIOS_VERSION_FEATURE                   22    /* Version Number High Byte */
#define CBIOS_VERSION_MINOR                     0000    /* Version Number Low Byte */ 
#define CBIOS_PREFIX_VERSION_STR             "10.17.22.0000"
#define CBIOS_INTERNAL_PRODUCTVERSION_STR   "42.00.00.00"


#define CBIOS_PREFIX_VERSION            CBIOS_VERSION_MAJOR,CBIOS_VERSION_BRANCH,CBIOS_VERSION_FEATURE,CBIOS_VERSION_MINOR


//
//  These undefines are used to replace with ZXG version specific definitions
//  below, or in the modules that include this header file.
//
#undef VER_PRODUCTNAME_STR
#undef VER_COMPANYNAME_STR
#undef VER_PRODUCTVERSION
#undef VER_PRODUCTVERSION_STR

#define VER_LEGALCOPYRIGHT_YEARS    "2024"
#define VER_LEGALCOPYRIGHT_STR      VER_LEGALCOPYRIGHT_YEARS  " " VER_COMPANYNAME_STR

#define VER_COMPANYNAME_STR         "Glenfly Tech Co., Ltd."
#define CBIOS_EXPORT_DRIVER_FILEDESC_STR      L"Glenfly CBIOS Export Driver"

#ifndef __LINUX__
    #if defined (_WIN64)
            #define CBIOS_EXPORT_DRIVER_NAME              L"arisebios_64.sys"
    #else
            #define CBIOS_EXPORT_DRIVER_NAME              L"arisebios_32.sys"
    #endif
#endif

#define VER_PRODUCTVERSION          CBIOS_PREFIX_VERSION
#define VER_FILEVERSION_STR         CBIOS_PREFIX_VERSION_STR
#define VER_PRODUCTVERSION_STR      CBIOS_PREFIX_VERSION_STR "-" CBIOS_INTERNAL_PRODUCTVERSION_STR

#define VER_PRODUCTNAME_STR         CBIOS_EXPORT_DRIVER_NAME

