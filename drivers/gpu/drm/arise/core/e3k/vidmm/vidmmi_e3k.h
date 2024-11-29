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
#ifndef __VIDMMI_E3K_H__
#define __VIDMMI_E3K_H__

extern void vidmm_query_segment_info_e3k(adapter_t *, vidmm_chip_segment_info_t *);
extern int  vidmm_describe_allocation_e3k(adapter_t*, vidmm_describe_allocation_t*);
extern int  vidmm_build_page_buffer_e3k(adapter_t*, vidmm_private_build_paging_buffer_arg_t*);
extern int  vidmm_query_gart_table_info_e3k(adapter_t*);
extern void vidmm_init_mem_settings_e3k(adapter_t *);
extern void vidmm_init_gart_table_e3k(adapter_t*);
extern void vidmm_deinit_gart_table_e3k(adapter_t*);
extern void vidmm_map_gart_table_e3k(adapter_t*, vidmm_allocation_t *allocation, int snooping);
extern void vidmm_unmap_gart_table_e3k(adapter_t*, vidmm_allocation_t *allocation);
extern void vidmm_gart_table_set_snoop_e3k(adapter_t *adapter, vidmm_allocation_t *allocation, int snooping);
extern void vidmm_update_gart_table_pte_e3k(adapter_t *adapter, struct os_pages_memory *memory, unsigned int *gart_table_L3, unsigned long gpu_va);
extern int  vidmm_get_allocation_info_e3k(adapter_t *adapter, vidmm_get_allocation_info_t *info);
extern int  vidmm_segment_transfer_e3k(adapter_t *adapter, vidmm_segment_memory_t **dst_pointer, vidmm_segment_memory_t *src, int to_local);


#endif

