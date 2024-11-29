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
#ifndef __GF_DEUBGFS_H__
#define __GF_DEUBGFS_H__

#include "gf.h"
#include "gf_driver.h"
#include "gf_device_debug.h"

#define DEBUGFS_ESCAPE_CREATE   1
#define DEBUGFS_GF_CREATE      2

#define DEBUGFS_HEAP_NUM        8
#define DEBUGFS_MEMTRACK        (DEBUGFS_HEAP_NUM + 1)

struct gf_debugfs_device;

typedef struct gf_debugfs_node
{
    int                         type;
    void                        *adapter;
    struct gf_debugfs_device   *dev;
    int                         id;
    char                        name[20];
    struct dentry               *node_dentry;
    int                         create_hint;
    int                         min_id;
    struct list_head            list_item;
    unsigned int                hDevice;

}gf_debugfs_node_t;

struct gf_debugfs_device;
typedef struct gf_debugfs_mmio
{
    struct dentry                  *mmio_root;
    struct gf_debugfs_node         regs;
    struct gf_debugfs_node         info;
    struct gf_debugfs_device       *debug_dev;
}gf_debugfs_mmio_t;

typedef struct gf_heap_info
{
    struct gf_debugfs_node         heap[DEBUGFS_HEAP_NUM];
    struct dentry                  *heap_dir;
}gf_heap_info_t;

typedef  struct gf_debugfs_crtcs
{
    struct gf_debugfs_device*  debug_dev;
    struct dentry*             crtcs_root;
    struct gf_debugfs_node*    crtcs_nodes;
    int                        node_num;
}gf_debugfs_crtcs_t;

typedef struct gf_debugfs_device
{
    gf_card_t                      *gf;
    struct list_head                node_list;

    struct dentry                   *device_root;
    struct list_head                device_node_list;

    struct dentry                   *allocation_root;

    gf_heap_info_t                 heap_info;

    struct gf_debugfs_node         info;
    struct gf_debugfs_node         memtrack;
    struct gf_debugfs_node         vidsch;
    struct gf_debugfs_node         displayinfo;
    struct gf_debugfs_node         debugbus;
    struct gf_debugfs_node         umd_trace;
    struct gf_debugfs_node         allocation_trace;
    struct gf_debugfs_node         video_interrupt_info;
    struct dentry                   *debug_root;
    struct os_mutex                 *lock;
    gf_debugfs_mmio_t              mmio;
    gf_debugfs_crtcs_t             crtcs;
}gf_debugfs_device_t;



gf_debugfs_device_t* gf_debugfs_create(gf_card_t *gf, struct dentry *minor_root);
int gf_debugfs_destroy(gf_debugfs_device_t* dev);
gf_device_debug_info_t* gf_debugfs_add_device_node(gf_debugfs_device_t* dev, int id, unsigned int handle);
int gf_debugfs_remove_device_node(gf_debugfs_device_t* dev, gf_device_debug_info_t *dnode);
int gf_debugfs_init(gf_card_t *gf);

static __inline__ struct dentry *gf_debugfs_get_allocation_root(void *debugfs_dev)
{
    gf_debugfs_device_t *dev =  (gf_debugfs_device_t *)debugfs_dev;
    return dev->allocation_root;
}
#endif


