#define _GNU_SOURCE
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"
#undef fstat64

void __procfdname(char *, unsigned);

int fstat(int fd, struct stat *st)
{
#if defined(SYS_fstat)
	int ret = __syscall(SYS_fstat, fd, st);
	if (ret != -EBADF || __syscall(SYS_fcntl, fd, F_GETFD) < 0)
		return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
#ifdef SYS_stat
	return syscall(SYS_stat, buf, st);
#else
	return syscall(SYS_fstatat, AT_FDCWD, buf, st, 0);
#endif
#else
	struct statx bufx;
	int result;

	result = syscall(SYS_statx, fd, "",
			AT_EMPTY_PATH | AT_STATX_SYNC_AS_STAT,
			STATX_BASIC_STATS, &bufx);
	if (!result)
		__statx_to_stat(&bufx, st);
	return result;
#endif
}

LFS64(fstat);
