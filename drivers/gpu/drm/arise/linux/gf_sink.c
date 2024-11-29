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
#include "gf_disp.h"
#include "gf_cbios.h"
#include "gf_sink.h"

#if DRM_VERSION_CODE < KERNEL_VERSION(4, 11, 0)
static inline unsigned int kref_read(const struct kref *kref)
{
    return atomic_read(&kref->refcount);
}
#endif

static void gf_sink_release(struct kref *ref)
{
    struct gf_sink *sink = container_of(ref, struct gf_sink, refcount);

    DRM_DEBUG_DRIVER("sink released: %p\n", sink);

    gf_free(sink);
}

void gf_sink_get(struct gf_sink *sink)
{
    if (sink)
    {
        DRM_DEBUG_DRIVER("get sink: %p, ref: %d \n", sink, kref_read(&sink->refcount));
        kref_get(&sink->refcount);
    }
}

void gf_sink_put(struct gf_sink *sink)
{
    if (sink)
    {
        DRM_DEBUG_DRIVER("put sink: %p, ref: %d \n", sink, kref_read(&sink->refcount));
        kref_put(&sink->refcount, gf_sink_release);
    }
}

bool gf_sink_is_edid_valid(struct gf_sink *sink)
{
    unsigned char edid_header[] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};

    if (!sink)
    {
        return FALSE;
    }

    if (gf_memcmp(sink->edid_data, edid_header, sizeof(edid_header)))
    {
        return FALSE;
    }

    return TRUE;
}

struct gf_sink* gf_sink_create(struct gf_sink_create_data *create_data)
{
    struct gf_sink *sink = gf_calloc(sizeof(*sink));

    if (!sink)
    {
        goto alloc_fail;
    }

    sink->output_type = create_data->output_type;

    kref_init(&sink->refcount);

    DRM_DEBUG_DRIVER("new sink created: %p\n", sink);

    return sink;

alloc_fail:
    return NULL;
}
