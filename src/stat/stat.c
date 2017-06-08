#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"

int stat(const char *restrict path, struct stat *restrict buf)
{
#ifdef SYS_statx
	return syscall(SYS_statx, AT_FDCWD, path, AT_STATX_SYNC_AS_STAT,
			STATX_BASIC_STATS, buf);
#elif defined(SYS_stat)
	return syscall(SYS_stat, path, buf);
#else
	return syscall(SYS_fstatat, AT_FDCWD, path, buf, 0);
#endif
}

LFS64(stat);
