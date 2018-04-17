#include <string.h>

typedef unsigned long reg_t;
typedef struct
{
  reg_t B0:8, B1:8, B2:8, B3:8;
} bits_t;

typedef union
{
  reg_t v;
  bits_t b;
} bitfields_t;

#define DO_BYTE(a, i)   \
  a[i] = bw.b.B##i;     \
  len--;                \
  if(!len) return ret;  \

#define PREFETCH(addr)  __builtin_prefetch (addr, 0, 1);

/* Typical observed latency in cycles in fetching from DRAM.  */
#define LATENCY_CYCLES 63
/* This is the approximate observed lenght of the inner loop for both
   mips32 and nanoMIPS32. Review and customize for 64-bit as necessary.  */
#define BLOCK_CYCLES 20
/* Pre-fetch look ahead = ceil (latency / block-cycles)  */
#define PREF_AHEAD (LATENCY_CYCLES / BLOCK_CYCLES	       \
		      + ((LATENCY_CYCLES % BLOCK_CYCLES) == 0 ? 0 : 1))

/* Pre-fetch performance is subject to correct cache-line size.  */
#define CACHE_LINE 32

#define WORDS_PER_BLOCK (CACHE_LINE / sizeof (reg_t))

/* This code is called when aligning a pointer, there are remaining bytes
   after doing word compares, or architecture does not have some form
   of unaligned support.  */
static inline void * __attribute__ ((always_inline))
do_bytes (void *a, const void *b, unsigned long len, void *ret)
{
  unsigned char *x = (unsigned char *) a;
  unsigned char *y = (unsigned char *) b;
  unsigned long i;
  /* 'len' might be zero here, so preloading the first two values
     before the loop may access unallocated memory.  */
  for (i = 0; i < len; i++) {
    *x = *y;
    x++;
    y++;
  }
  return ret;
}

/* This code is called to copy only remaining bytes within word or doubleword */
static inline void * __attribute__ ((always_inline))
do_bytes_remaining (void *a, const void *b, unsigned long len, void *ret)
{
  unsigned char *x = (unsigned char *) a;
  if(len > 0) {
    bitfields_t bw;
    bw.v = *((reg_t*) b);
    DO_BYTE(x, 0);
    DO_BYTE(x, 1);
    DO_BYTE(x, 2);
    DO_BYTE(x, 3);
  }
    return ret;
}

/* for MIPS GCC, there are no unaligned builtins - so this struct forces
   the compiler to treat the pointer access as unaligned.  */
struct ulw
{
  reg_t uli;
} __attribute__ ((packed));

/* first pointer is not aligned while second pointer is.  */
static void *
unaligned_words (struct ulw *a, const reg_t * b,
		 unsigned long words, unsigned long bytes, void *ret)
{
  unsigned long i, words_by_8, words_by_1;
  words_by_1 = words % WORDS_PER_BLOCK;
  words_by_8 = words / WORDS_PER_BLOCK;
  for (; words_by_8 > 0; words_by_8--) {
    /* Do an extra pre-fetch for possible trailing bytes.  */
    if(words_by_8 >= PREF_AHEAD - 1)
      PREFETCH (b + WORDS_PER_BLOCK * PREF_AHEAD);
    reg_t y0 = b[0], y1 = b[1], y2 = b[2], y3 = b[3];
    reg_t y4 = b[4], y5 = b[5], y6 = b[6], y7 = b[7];
    a[0].uli = y0;
    a[1].uli = y1;
    a[2].uli = y2;
    a[3].uli = y3;
    a[4].uli = y4;
    a[5].uli = y5;
    a[6].uli = y6;
    a[7].uli = y7;
    a += WORDS_PER_BLOCK;
    b += WORDS_PER_BLOCK;
  }
  /* do remaining words.  */
  for (i = 0; i < words_by_1; i++) {
    a->uli = *b;
    a += 1;
    b += 1;
  }
  /* mop up any remaining bytes.  */
  return do_bytes_remaining (a, b, bytes, ret);
}

/* both pointers are aligned, or first isn't and HW support for unaligned.  */
static void *
aligned_words (reg_t * a, const reg_t * b,
	       unsigned long words, unsigned long bytes, void *ret)
{
  unsigned long i, words_by_8, words_by_1;
  words_by_1 = words % WORDS_PER_BLOCK;
  words_by_8 = words / WORDS_PER_BLOCK;
  for (; words_by_8 > 0; words_by_8--) {
    /* Do an extra pre-fetch for possible trailing bytes.  */
    if(words_by_8 >= PREF_AHEAD - 1)
      PREFETCH (b + WORDS_PER_BLOCK * PREF_AHEAD);
    reg_t x0 = b[0], x1 = b[1], x2 = b[2], x3 = b[3];
    reg_t x4 = b[4], x5 = b[5], x6 = b[6], x7 = b[7];
    a[0] = x0;
    a[1] = x1;
    a[2] = x2;
    a[3] = x3;
    a[4] = x4;
    a[5] = x5;
    a[6] = x6;
    a[7] = x7;
    a += WORDS_PER_BLOCK;
    b += WORDS_PER_BLOCK;
  }
  /* do remaining words.  */
  for (i = 0; i < words_by_1; i++) {
    *a = *b;
    a += 1;
    b += 1;
  }
  /* mop up any remaining bytes.  */
  return do_bytes_remaining (a, b, bytes, ret);
}

void *
memcpy (void *a, const void *b, size_t len)
{
  unsigned long bytes, words;
  void *ret = a;
  /* shouldn't hit that often.  */
  if (len < sizeof (reg_t) * 4) {
    return do_bytes (a, b, len, a);
  }
  /* Align the second pointer to word/dword alignment.
     Note that the pointer is only 32-bits for o32/n32 ABIs. For
     n32, loads are done as 64-bit while address remains 32-bit.   */
  bytes = ((unsigned long) b) % sizeof (reg_t);

  /* Start a pre-fetch ahead of time.  */
  PREFETCH ((unsigned long*)b - bytes + CACHE_LINE * (PREF_AHEAD - 1));

  if (bytes) {
    bytes = sizeof (reg_t) - bytes;
    if (bytes > len)
      bytes = len;
    do_bytes (a, b, bytes, ret);
    if (len == bytes)
      return ret;
    len -= bytes;
    a = (void *) (((unsigned char *) a) + bytes);
    b = (const void *) (((unsigned char *) b) + bytes);
  }
  /* Second pointer now aligned.  */
  words = len / sizeof (reg_t);
  bytes = len % sizeof (reg_t);
  if (((unsigned long) a) % sizeof (reg_t) == 0) {
    return aligned_words (a, b, words, bytes, ret);
  }
  /* need to use unaligned instructions on first pointer.  */
  return unaligned_words (a, b, words, bytes, ret);
}
