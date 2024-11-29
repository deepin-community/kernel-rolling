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
#ifndef _H_GF_GEM_OBJECT_H
#define _H_GF_GEM_OBJECT_H
#if DRM_VERSION_CODE >= KERNEL_VERSION(5,5,0)
#include <drm/drm_drv.h>
#else
#include <drm/drmP.h>
#endif
#include <drm/drm_vma_manager.h>
#include <drm/drm_gem.h>
#if DRM_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/dma-resv.h>
#define reservation_object  dma_resv
#else
#include <linux/reservation.h>
#endif
#include <linux/dma-buf.h>
#include "gf_types.h"
#include "gf_gem_debug.h"
#include "gf_version.h"

struct drm_gf_gem_object;

struct drm_gf_gem_object_ops
{
    int (*get_pages)(struct drm_gf_gem_object *);
    void (*put_pages)(struct drm_gf_gem_object *, struct sg_table *);
    void (*release)(struct drm_gf_gem_object *);
};

struct drm_gf_gem_object
{
    struct drm_gem_object base;
    const struct drm_gf_gem_object_ops *ops;

    unsigned int core_handle;
    struct
    {
        struct mutex lock;
        int pages_pin_count;
        struct sg_table *pages;
    } mm;

    gf_open_allocation_t info;
    gf_map_argu_t map_argu;
    gf_vm_area_t *krnl_vma;
    struct reservation_object *resv;
    struct reservation_object __builtin_resv;

    unsigned int prefault_num;
    unsigned int delay_map;

    unsigned int vmap_mem_type;
//debugfs related things
    gf_gem_debug_info_t  debug;
};


static inline struct drm_gf_gem_object* gf_gem_object_get(struct drm_gf_gem_object* obj)
{
#if DRM_VERSION_CODE < KERNEL_VERSION(4,12,0)
    drm_gem_object_reference(&obj->base);
#else
    drm_gem_object_get(&obj->base);
#endif
    return obj;
}

static inline void gf_gem_object_put(struct drm_gf_gem_object* obj)
{
#if DRM_VERSION_CODE < KERNEL_VERSION(4,12,0)
    drm_gem_object_unreference_unlocked(&obj->base);
#elif DRM_VERSION_CODE < KERNEL_VERSION(5,9,0)
     drm_gem_object_put_unlocked(&obj->base);
#else
    drm_gem_object_put(&obj->base);
#endif
}

#undef __CONCAT
#undef CONCAT
#define __CONCAT(x,y) x##y
#define CONCAT(x,y)     __CONCAT(x,y)

extern struct drm_gf_gem_object* CONCAT(gf_krnl_gem_create_object, DRIVER_NAME)(struct pci_dev *dev,
        gf_create_allocation_t *create, gf_device_debug_info_t **ddev);


struct gf_krnl_device_create {
    unsigned int      gpu_device;  //out, virtual device handle
    gf_device_debug_info_t *debug; //out, for debugfs
};

extern int CONCAT(gf_krnl_create_device, DRIVER_NAME)(struct pci_dev *dev,
        struct gf_krnl_device_create *vdev_create);

struct gf_krnl_device_destroy {
    unsigned int      gpu_device;  //in, virtual device handle
    gf_device_debug_info_t *debug; //in, for debugfs
};

extern void CONCAT(gf_krnl_destroy_device,DRIVER_NAME)(struct pci_dev *dev,
        struct gf_krnl_device_destroy *destroy);

extern const struct dma_buf_ops CONCAT(gf_dmabuf_ops,DRIVER_NAME);
#endif

