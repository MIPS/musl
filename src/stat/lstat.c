#define _GNU_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"
#include "stat.h"
#undef lstat64

int lstat(const char *restrict path, struct stat *restrict buf)
{
#if defined(SYS_lstat)
	return syscall(SYS_lstat, path, buf);
#elif defined(SYS_fstatat)
	return syscall(SYS_fstatat, AT_FDCWD, path, buf, AT_SYMLINK_NOFOLLOW);
#else
	struct statx bufx;
	int result;

	result = syscall(SYS_statx, AT_FDCWD, path,
			AT_SYMLINK_NOFOLLOW | AT_STATX_SYNC_AS_STAT,
			STATX_BASIC_STATS, &bufx);
	if (!result)
		__statx_to_stat(&bufx, buf);
	return result;
#endif
}

LFS64(lstat);
