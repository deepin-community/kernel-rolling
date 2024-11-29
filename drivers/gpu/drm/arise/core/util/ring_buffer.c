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
#include "ring_buffer.h"
#include "core_errno.h"
#include "core_import.h"

#define DEBUG_RING_BUFFER 0

#if DEBUG_RING_BUFFER
#define ring_debug gf_info
#else
#define ring_debug(args...)
#endif

int ring_buffer_init(ring_buffer_t *ring, int size, int reserved_size, ring_func_t wrap, void *private_data)
{
    ring->size          = size;
    ring->head          =
    ring->tail          = reserved_size;
    ring->wrap          = wrap;
    ring->left_size     = size - reserved_size;
    ring->private_data  = private_data;
    ring->reserved_size = reserved_size;

    return S_OK;
}

#if DEBUG_RING_BUFFER
static int wrap_print = 0;
#endif

int ring_buffer_get_space(ring_buffer_t *ring, int requested_size)
{
    int space_offset = -1;

    /* ring wrapped, we will skip tail space and reset tail to header and only update head when this time */
    if(ring->tail + requested_size >= ring->size)
    {
        int skip_cnt = ring->size - ring->tail;

        ring_debug("^^ wrap :requ :%08x, tail:%08x, head:%08x, left:%08x.\n", requested_size, ring->tail, ring->head, ring->left_size);
        ring->head = ring->wrap(ring, skip_cnt, ring->private_data);

        ring->tail      = ring->reserved_size;
        ring->left_size = ring->head - ring->tail;

        ring_debug("-- wrap :skip :%08x, tail:%08x, head:%08x, left:%08x.\n", skip_cnt, ring->tail, ring->head, ring->left_size);
    }

    /* if left size not enough, update left size */
    if(ring->left_size < requested_size)
    {
        ring_debug("update ^^ :requ :%08x, tail:%08x, head:%08x, left:%08x.\n", requested_size, ring->tail, ring->head, ring->left_size);
        ring->head = ring->wrap(ring, 0, ring->private_data);
        ring->left_size = ring->size + ring->head - ring->tail - ring->reserved_size;

        ring_debug("update --:skip :%08x, tail:%08x, head:%08x, left:%08x.\n", 0, ring->tail, ring->head, ring->left_size);
    }

#if DEBUG_RING_BUFFER
    if(ring->tail > ring->size - (requested_size * 3))
    {
        wrap_print = 5;
    }
#endif

    if(ring->left_size >= requested_size)
    {
        ring->left_size -= requested_size;

        space_offset = ring->tail;
        ring->tail  += requested_size;
    }
    else
    {
        ring_debug("fail **:requ :%08x, tail:%08x, head:%08x, left:%08x.\n", requested_size, ring->tail, ring->head, ring->left_size);
    }

#if DEBUG_RING_BUFFER
    if(wrap_print > 0)
    {
        wrap_print--;

        ring_debug(" @@ offset:%x, tail:%x.\n", space_offset, ring->tail);
    }
#endif

    return space_offset;
}
