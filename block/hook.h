/*
 * Block i/o hooking
 *
 * Copyright PLUSTECH. Inc. 2014
 *
 * Authors:
 *  Igor Royzis   <igorr@swortex.com>
 *  Seo Seunghyun <hefos@plustech.co.kr> , <tgnice@gmail.com>
 * 
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Contributions after 2012-01-13 are licensed under the terms of the
 * GNU GPL, version 2 or (at your option) any later version.
 */
#ifndef QEMU_BLOCK_HOOK_H
#define QEMU_BLOCK_HOOK_H

void* block_open_hook(BlockDriverState *bs);
void block_io_hook(void *handle, QEMUIOVector *qiov, int64_t sector_num, int nb_sectors, bool is_write);
void block_close_hook(void *handle);

#endif /* QEMU_BLOCK_HOOK_H */
