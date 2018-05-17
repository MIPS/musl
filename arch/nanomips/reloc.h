#include <endian.h>

#define ISA_SUFFIX "r6"

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ENDIAN_SUFFIX ""
#else
#define ENDIAN_SUFFIX "eb"
#endif

#ifdef __mips_soft_float
#define FP_SUFFIX "-sf"
#else
#define FP_SUFFIX ""
#endif

#define LDSO_ARCH "nanomips" ISA_SUFFIX ENDIAN_SUFFIX FP_SUFFIX

#define NO_LEGACY_INITFINI

#define TPOFF_K 0

#define REL_SYMBOLIC    R_NANOMIPS_32
#define REL_GOT         R_NANOMIPS_GLOBAL
#define REL_PLT         R_NANOMIPS_JUMP_SLOT
#define REL_RELATIVE    R_NANOMIPS_RELATIVE
#define REL_COPY        R_NANOMIPS_COPY
#define REL_DTPMOD      R_NANOMIPS_TLS_DTPMOD
#define REL_DTPOFF      R_NANOMIPS_TLS_DTPREL
#define REL_TPOFF       R_NANOMIPS_TLS_TPREL

#define CRTJMP(pc,sp) __asm__ __volatile__( \
	"move $sp,%1 ; jrc %0" : : "r"(pc), "r"(sp) : "memory" )

#define GETFUNCSYM(fp, sym, got) __asm__ ( \
	".hidden " #sym "\n" \
	"	lapc %0, " #sym " \n" \
	: "=r"(*(fp)) : : "memory" )
