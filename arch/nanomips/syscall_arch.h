#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) 0, __SYSCALL_LL_E((x))

__attribute__((visibility("hidden")))
long (__syscall)(long, ...);

#define SYSCALL_RLIM_INFINITY (-1UL/2)

#include <sys/stat.h>
#define __NEED_int64_t
#define __NEED_uint64_t
#define __NEED_uint32_t
#define __NEED_uint16_t
#include <bits/alltypes.h>

#include <sys/sysmacros.h>

struct statx_timestamp {
	int64_t tv_sec;		/* Seconds since the Epoch (UNIX time) */
	uint32_t tv_nsec;	/* Nanoseconds since tv_sec */
	uint32_t __reserved;
};

struct statx {
	uint32_t stx_mask;		/* Mask of bits indicating filled fields */
	uint32_t stx_blksize;		/* Block size for filesystem I/O */
	uint64_t stx_attributes;	/* Extra file attribute indicators */
	uint32_t stx_nlink;		/* Number of hard links */
	uint32_t stx_uid;		/* User ID of owner */
	uint32_t stx_gid;		/* Group ID of owner */
	uint16_t stx_mode;		/* File type and mode */
	uint16_t __spare0[1];
	uint64_t stx_ino;		/* Inode number */
	uint64_t stx_size;		/* Total size in bytes */
	uint64_t stx_blocks;		/* Number of 512B blocks allocated */
	uint64_t stx_attributes_mask;	/* Mask to show what's supported in stx_attributes */

	/* The following fields are file timestamps */
	struct statx_timestamp stx_atime;	/* Last access */
	struct statx_timestamp stx_btime;	/* Creation */
	struct statx_timestamp stx_ctime;	/* Last status change */
	struct statx_timestamp stx_mtime;	/* Last modification */

	/* If this file represents a device, then the next two
	   fields contain the ID of the device */
	uint32_t stx_rdev_major;	/* Major ID */
	uint32_t stx_rdev_minor;	/* Minor ID */

	/* The next two fields contain the ID of the device
	   containing the filesystem where the file resides */
	uint32_t stx_dev_major;		/* Major ID */
	uint32_t stx_dev_minor;		/* Minor ID */

	uint64_t __spare2[14];		/* Spare space for future expansion */
};

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

static inline long __syscall0(long n)
{
	return (__syscall)(n);
}

static inline long __syscall1(long n, long a)
{
	return (__syscall)(n, a);
}

static inline long __syscall2(long n, long a, long b)
{
	return (__syscall)(n, a, b);
}

static inline long __syscall3(long n, long a, long b, long c)
{
	return (__syscall)(n, a, b, c);
}

static inline long __syscall4(long n, long a, long b, long c, long d)
{
	return (__syscall)(n, a, b, c, d);
}

static inline long __syscall5(long n, long a, long b, long c, long d, long e)
{
	return (__syscall)(n, a, b, c, d, e);
}

static inline long __syscall6(long n, long a, long b, long c, long d, long e, long f)
{
	return (__syscall)(n, a, b, c, d, e, f);
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"

#define SYSCALL_FADVISE_6_ARG
