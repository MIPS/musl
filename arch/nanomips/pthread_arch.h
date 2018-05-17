static inline struct pthread *__pthread_self()
{
	char *self;
	__asm__ __volatile__ ("rdhwr %0, $29" : "=r" (self) );
	return (struct pthread *) (self - sizeof(struct pthread));
}

// Use variant I.
#define TLS_ABOVE_TP
// The TP points to the end of the TCB.
#define TP_ADJ(p) ((char *)(p) + sizeof(struct pthread))

#define NO_STATIC_TLS_DESC_RESOLVER

#define MC_PC pc
