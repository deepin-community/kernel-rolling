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
#ifndef __QUEUE_H_
#define __QUEUE_H_


#define QUEUE_SUCCESS 0
#define QUEUE_FAIL    1
#define QUEUE_FULL    2
#define QUEUE_EMPTY   3



typedef struct
{
    int  entry_num;
    int  entry_size;
    int  data_size;
    int  entry_inuse;
    int  start;
//    int  end;

    struct os_spinlock *lock;
    char *entrys;
}queue_t;

extern int  queue_init(queue_t *queue, int entry_num, int entry_size);
extern void queue_fini(queue_t *queue);
extern int  queue_add_entry(queue_t *queue, void *data);
extern int  queue_get_first_entry_and_free(queue_t *queue, void *data);
extern int  queue_get_entry(queue_t *queue, int num, void *data);
extern int  queue_get_first_entry(queue_t *queue, void *data);
extern int  queue_free_entry(queue_t *queue, int num);
extern void queue_query_info(queue_t *queue, int *start, int *inuse_num);

#endif /* __QUEUE_H_*/

