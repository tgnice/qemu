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
#include "config-host.h"
#include "qemu-common.h"
#include "block/block_int.h"
#include "block/hook.h"

/* A sample handlers counter used to provide a unique handler for block_open_hook */
static long int global_handles_count = 0;


/*
 Open hook
 Called by the block engine upon opening an image
 Returns a hook handler that will be used in subsequent block_io_hook() and block_close(), it must not be null
 TODO: verify the behavior with mode snapshot=on
*/
void* block_open_hook(BlockDriverState *bs)
{
    printf("hook> Opening block device %s, file block state %s\n", bs->filename, bs->file?bs->file->filename:"none");
    global_handles_count ++;    // Example: for now create a unique handler
    return (void*)global_handles_count;
}

/*
 Close hook
 Called by the block engine upon closing the image
 handle - is the hook handler returned by block_open_hook()
*/
void block_close_hook(void *handle)
{
    printf("hook> Closing block device handler %ld\n", (long)handle);
}

/*
 I/O hook
 called after a read (is_write=FALSE) or write (is_write=TRUE) operation on the sector 'sector_num' with
 amount of 'nb_sectors'. handle - is the hook handler returned by block_open_hook(). The data is in qiov.
 TODO: verify that async read has completed (all iovecs are ready with data) upon calling the hook.
 TODO: verify that the hook is called on i/o requests from qemu cache
*/
void block_io_hook(void *handle, QEMUIOVector *qiov, int64_t sector_num, int nb_sectors, bool is_write)
{
    printf("hook> handle %ld. %s sector %ld, %d sectors.\n", (long)handle, is_write?"Write":"Read", (long)sector_num, nb_sectors);
    // Access the data example:
    // struct iovec *v = qiov->iov;
    // int i;
    // for(i=0; i < qiov->niov; i++) {
        // We can analyze data in (char*)v->iov_base with legnth v->iov_len here
        // v++;
    // }
}
