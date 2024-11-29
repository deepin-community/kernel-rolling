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
#include "queue.h"
#include "core_import.h"

#define calc_cyc_num(num) (num) % queue->entry_num

int queue_init(queue_t *queue, int entry_num, int data_size)
{
    int  size    = (data_size + 7) & ~7;
    void *entrys = gf_calloc(entry_num * size);
    int  status  = QUEUE_SUCCESS;

    if(entrys == NULL)
    {
        return QUEUE_FAIL;
    }

    queue->entrys     = entrys;
    queue->entry_size = size;
    queue->data_size  = data_size;
    queue->entry_num  = entry_num;
    queue->lock       = gf_create_spinlock(0);

    return status;
}

void queue_fini(queue_t *queue)
{
    if(queue->lock)
    {
        gf_destroy_spinlock(queue->lock);
    }

    if(queue->entrys)
    {
        gf_free(queue->entrys);
    }
}

void queue_query_info(queue_t *queue, int *start, int *inuse_num)
{
    unsigned long flags;

    flags = gf_spin_lock_irqsave(queue->lock);

    if(start)
    {
        *start = queue->start;
    }

    if(inuse_num)
    {
        *inuse_num = queue->entry_inuse;
    }

    gf_spin_unlock_irqrestore(queue->lock, flags);
}

int queue_add_entry(queue_t *queue, void *data)
{
    void *entry = NULL;
    int  status = QUEUE_FULL;
    unsigned long flags;

    flags = gf_spin_lock_irqsave(queue->lock);

    if(queue->entry_inuse < queue->entry_num)
    {
        entry = queue->entrys + calc_cyc_num(queue->start + queue->entry_inuse) * queue->entry_size;

        gf_memcpy(entry, data, queue->data_size);

        queue->entry_inuse++;

        status = QUEUE_SUCCESS;
    }
    else
    {
        gf_error("add entry to a full queue. \n");
    }

    gf_spin_unlock_irqrestore(queue->lock, flags);

    return status;
}

int queue_get_first_entry(queue_t *queue, void *data)
{
    int  status = QUEUE_EMPTY;
    void *entry = NULL;
    unsigned long flags;

    flags = gf_spin_lock_irqsave(queue->lock);

    if(queue->entry_inuse > 0)
    {
        entry = queue->entrys + queue->start * queue->entry_size;

        gf_memcpy(data, entry, queue->data_size);

        status = QUEUE_SUCCESS;
    }

    gf_spin_unlock_irqrestore(queue->lock, flags);

    return status;
}

int queue_get_first_entry_and_free(queue_t *queue, void *data)
{
    int  status = QUEUE_EMPTY;
    void *entry = NULL;
    unsigned long flags;

    flags = gf_spin_lock_irqsave(queue->lock);

    if(queue->entry_inuse > 0)
    {
        entry = queue->entrys + queue->start * queue->entry_size;

        queue->start = calc_cyc_num(queue->start + 1);

        queue->entry_inuse--;

        gf_memcpy(data, entry, queue->data_size);

        status = QUEUE_SUCCESS;
    }

    gf_spin_unlock_irqrestore(queue->lock, flags);

    return status;
}

int queue_get_entry(queue_t *queue, int num, void *data)
{
    int  status = QUEUE_SUCCESS;
    int  index  = 0;
    void *entry = NULL;
    unsigned long flags;

    flags = gf_spin_lock_irqsave(queue->lock);

    index = calc_cyc_num(num);
    entry = queue->entrys + queue->entry_size * index;

    gf_memcpy(data, entry, queue->data_size);

    gf_spin_unlock_irqrestore(queue->lock, flags);

    return status;
}

int queue_free_entry(queue_t *queue, int num)
{
    int  i, privous_cnt = 0;
    void *src, *dst;
    unsigned long flags;

    flags = gf_spin_lock_irqsave(queue->lock);

    privous_cnt = calc_cyc_num(num - queue->start);

    for(i = privous_cnt; i > 0; i--)
    {
        src = queue->entrys + calc_cyc_num(queue->start + i - 1 ) * queue->entry_size;
        dst = queue->entrys + calc_cyc_num(queue->start + i     ) * queue->entry_size;

        gf_memcpy(dst, src, queue->data_size);
    }

    queue->start = calc_cyc_num(queue->start + 1);

    queue->entry_inuse--;

    gf_spin_unlock_irqrestore(queue->lock, flags);

    return QUEUE_SUCCESS;
}





