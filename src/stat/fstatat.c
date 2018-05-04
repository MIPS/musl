#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"

int fstatat(int fd, const char *restrict path, struct stat *restrict buf, int flag)
{
#if defined(SYS_fstatat)
	return syscall(SYS_fstatat, fd, path, buf, flag);
#else
	return syscall(SYS_statx, fd, path, flag | AT_STATX_SYNC_AS_STAT,
			STATX_BASIC_STATS, buf);
#endif
}

LFS64(fstatat);
