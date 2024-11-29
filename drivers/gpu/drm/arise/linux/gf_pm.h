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
#ifndef __GF_PM_H__
#define __GF_PM_H__

#include <linux/version.h>

static inline int gf_rpm_get_sync(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    return pm_runtime_get_sync(dev);
#else
    return 0;
#endif
}

static inline int gf_rpm_put_autosuspend(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    return pm_runtime_put_autosuspend(dev);
#else
    return 0;
#endif
}

static inline void gf_rpm_use_autosuspend(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_use_autosuspend(dev);
#endif
}

static inline void gf_rpm_set_autosuspend_delay(struct device *dev, int delay)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_set_autosuspend_delay(dev, delay); //5s
#endif
}

static inline int gf_rpm_set_active(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    return pm_runtime_set_active(dev);
#else
    return 0;
#endif
}

static inline void gf_rpm_allow(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_allow(dev);             //-1
#endif
}

static inline void gf_rpm_forbid(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_forbid(dev);
#endif
}

static inline void gf_rpm_mark_last_busy(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_mark_last_busy(dev);
#endif
}

static inline void gf_rpm_enable(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_enable(dev);
#endif
}

static inline void gf_rpm_disable(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_disable(dev);
#endif
}

static inline int gf_rpm_autosuspend(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    return pm_runtime_autosuspend(dev);
#else
    return 0;
#endif
}

static inline void gf_rpm_get_noresume(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_get_noresume(dev);
#endif
}

static inline void gf_rpm_put_noidle(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 8, 0)
    pm_runtime_put_noidle(dev);
#endif
}

static inline void gf_rpm_set_driver_flags(struct device *dev)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 8, 0)
    dev_pm_set_driver_flags(dev, DPM_FLAG_NO_DIRECT_COMPLETE);
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)
    dev_pm_set_driver_flags(dev, DPM_FLAG_NEVER_SKIP);
#endif
}

#endif
