static inline struct pthread *__pthread_self()
{
	register char *tp __asm__("$3");
	__asm__ __volatile__ ("rdhwr %0, $29" : "=r" (tp) );
	return (pthread_t)(tp - 0x7000 - sizeof(struct pthread));
}

#define TLS_ABOVE_TP
#define TP_ADJ(p) ((char *)(p) + sizeof(struct pthread) + 0x7000)

#define DTP_OFFSET 0x8000

#define MC_PC pc
