#define a_ll a_ll
static inline int a_ll(volatile int *p)
{
	int v;
	__asm__ __volatile__ (
		"ll %0, %1"
		: "=r"(v) : "ZC"(*p));
	return v;
}

#define a_sc a_sc
static inline int a_sc(volatile int *p, int v)
{
	int r;
	__asm__ __volatile__ (
		"sc %0, %1"
		: "=r"(r), "=ZC"(*p) : "0"(v) : "memory");
	return r;
}

#define a_barrier a_barrier
static inline void a_barrier()
{
	__asm__ __volatile__ ("sync" : : : "memory");
}

#define a_pre_llsc a_barrier
#define a_post_llsc a_barrier
