#define _GNU_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"
#undef stat64

int stat(const char *restrict path, struct stat *restrict buf)
{
#if defined(SYS_stat)
	return syscall(SYS_stat, path, buf);
#elif defined(SYS_fstatat)
	return syscall(SYS_fstatat, AT_FDCWD, path, buf, 0);
#else
	return syscall(SYS_statx, AT_FDCWD, path, AT_STATX_SYNC_AS_STAT,
			STATX_BASIC_STATS, buf);
#endif
}

LFS64(stat);
