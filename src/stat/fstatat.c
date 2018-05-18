#define _GNU_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"
#include "stat.h"
#undef fstatat64

int fstatat(int fd, const char *restrict path, struct stat *restrict buf, int flag)
{
#if defined(SYS_fstatat)
	return syscall(SYS_fstatat, fd, path, buf, flag);
#else
	struct statx bufx;
	int result;

	result = syscall(SYS_statx, fd, path, flag | AT_STATX_SYNC_AS_STAT,
			 STATX_BASIC_STATS, &bufx);
	if (!result)
		__statx_to_stat(&bufx, buf);
	return result;
#endif
}

LFS64(fstatat);
