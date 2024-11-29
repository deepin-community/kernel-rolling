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
#ifndef __GF_GEM_DEUBG_H__
#define __GF_GEM_DEUBG_H__
#include "gf_device_debug.h"

typedef struct gf_gem_debug_info {
    gf_device_debug_info_t **parent_dev;  /*in*/
    char                    name[20];    /*in*/
    struct dentry           *root;      /*in*/


    void                    *parent_gem;

    struct dentry          *self_dir;
    struct dentry          *alloc_info;


    struct dentry           *data;
    bool                    is_cpu_accessable;

    struct dentry           *control;
    bool                    mark_unpagable;

    struct dentry           *link;
    struct dentry           *bl; //burst length for compress

    bool                    is_dma_buf_import;
}gf_gem_debug_info_t;



#endif

