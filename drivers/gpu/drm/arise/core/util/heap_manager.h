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
#ifndef __HEAP_MANAGER_H__
#define __HEAP_MANAGER_H__

#include "core_errno.h"
#include "list.h"

typedef struct _list_node
{
    struct list_head list_item;
    unsigned long long    size;               // Available Size, this node occupied space
    unsigned long long    offset;             // Actual offset from start of heap
    unsigned long long    aligned_offset;         // Aligned offset, offset that will be used
    unsigned long long    aligned_size;           // Aligned size, the size that will be used
} list_node_t;

typedef struct _list_head
{
    struct list_head list;
    unsigned long long     size;
    int                    num;
    int                    order;
} list_head_t;

typedef struct _heap
{
    int                   id;
    unsigned long long    size;
    unsigned long long    start;
    unsigned int          alignment;
    list_head_t     free;
    list_head_t     inuse;

    struct os_mutex *lock;
} heap_t;


int  heap_init(heap_t *heap, int id, unsigned long long start, unsigned long long size, unsigned int alignment);
void heap_destroy(heap_t *heap);
list_node_t * heap_allocate(heap_t *heap, unsigned int size, unsigned int alignment, unsigned int direction);
void heap_release(heap_t *heap, list_node_t *list_node);
void heap_dump(heap_t *heap);

#endif

