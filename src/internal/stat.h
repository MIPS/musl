#ifndef _INTERNAL_STAT_H
#define _INTERNAL_STAT_H

#include <sys/sysmacros.h>

static inline void __statx_to_stat(const struct statx *src, struct stat *dst)
{
	dst->st_dev = makedev(src->stx_dev_major, src->stx_dev_minor);
	dst->st_ino = src->stx_ino;
	dst->st_mode = src->stx_mode;
	dst->st_nlink = src->stx_nlink;
	dst->st_uid = src->stx_uid;
	dst->st_gid = src->stx_gid;
	dst->st_rdev = makedev(src->stx_rdev_major, src->stx_rdev_minor);
	dst->st_size = src->stx_size;
	dst->st_atim.tv_sec = src->stx_atime.tv_sec;
	dst->st_atim.tv_nsec = src->stx_atime.tv_nsec;
	dst->st_mtim.tv_sec = src->stx_mtime.tv_sec;
	dst->st_mtim.tv_nsec = src->stx_mtime.tv_nsec;
	dst->st_ctim.tv_sec = src->stx_ctime.tv_sec;
	dst->st_ctim.tv_nsec = src->stx_ctime.tv_nsec;
	dst->st_blksize = src->stx_blksize;
	dst->st_blocks = src->stx_blocks;
}

#endif
