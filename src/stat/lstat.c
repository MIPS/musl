#define _GNU_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include "libc.h"
#include "stat.h"
#undef lstat64

int lstat(const char *restrict path, struct stat *restrict buf)
{
#ifdef SYS_lstat
	return syscall(SYS_lstat, path, buf);
#else
	return syscall(SYS_fstatat, AT_FDCWD, path, buf, AT_SYMLINK_NOFOLLOW);
#endif
}

LFS64(lstat);
