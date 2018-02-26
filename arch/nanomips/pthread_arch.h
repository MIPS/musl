static inline struct pthread *__pthread_self()
{
	register char *tp __asm__("$3");
	__asm__ __volatile__ ("rdhwr %0, $29" : "=r" (tp) );
	return (struct pthread *) (tp - sizeof(struct pthread));
}

// Use variant I.
#define TLS_ABOVE_TP
// The TP points to the end of the TCB.
#define TP_ADJ(p) ((char *)(p) + sizeof(struct pthread))

#define MC_PC pc
