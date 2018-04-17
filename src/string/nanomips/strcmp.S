.align 2
.global	strcmp
.type strcmp,@function
strcmp:
	or	$t0, $a0, $a1
	andi	$t0, $t0, 0x3
	bne	$t0, $zero, .Lbyteloop

/* Both strings are 4 byte aligned at this point.  */

	li	$t8, 0x01010101
#if !defined(__mips_dsp)
	li	$t9, 0x7f7f7f7f
#endif

#ifdef __mips_dsp
# define STRCMP32(OFFSET) \
	lw	$a2, OFFSET($a0); \
	lw	$a3, OFFSET($a1); \
	subu_s.qb $t0, $t8, $a2; \
	bne	$a2, $a3, .Lworddiff; \
	bne	$t0, $zero, .Lreturnzero
#else  /* !__mips_dsp */
# define STRCMP32(OFFSET) \
	lw	$a2, OFFSET($a0); \
	lw	$a3, OFFSET($a1); \
	subu	$t0, $a2, $t8; \
	nor	$t1, $a2, $t9; \
	and	$t1, $t0, $t1; \
	bne	$a2, $a3, .Lworddiff; \
	bne	$t1, $zero, .Lreturnzero
#endif /* __mips_dsp */
.Lwordloop:
	STRCMP32(0)
	STRCMP32(4)
	STRCMP32(8)
	STRCMP32(12)
	STRCMP32(16)
	STRCMP32(20)
	STRCMP32(24)
	lw	$a2, 28($a0)
	lw	$a3, 28($a1)
#ifndef __mips_dsp
	subu	$t0, $a2, $t8
	nor	$t1, $a2, $t9
#else
	subu_s.qb $t0, $t8, $a2
#endif
#ifndef __mips_dsp
	and	$t1, $t0, $t1
#endif
	bnec	$a2, $a3, .Lworddiff
	addiu	$a0, $a0, 32
	bne	$t1, $zero, .Lreturnzero
	addiu	$a1, $a1, 32
	b	.Lwordloop

.Lreturnzero:
	move	$a0, $zero
	jr	$ra

.Lworddiff:
	xor	$t0, $a2, $a3
	or	$t0, $t0, $t1
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# if defined(__nanomips__) && !defined(__nanomips_subset)
	byterevw $t0, $t0
# else /* ! __nanomips__ */
	wsbh	$t0, $t0
	rotr	$t0, $t0, 16
# endif /* __nanomips__ */
#endif /* LITTLE_ENDIAN */
	clz	$t1, $t0
	or	$t0, $t1, 24	/* Only care about multiples of 8.  */
	xor 	$t1, $t1, $t0	/* {0,8,16,24} => {24,16,8,0}  */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	sllv	$a2,$a2,$t1
	sllv	$a3,$a3,$t1
#else
	srlv	$a2,$a2,$t1
	srlv	$a3,$a3,$t1
#endif
	subu	$a0, $a2, $a3
	jr	$ra

#define BYTECMP01(OFFSET) \
	lbu	$a3, OFFSET($a1); \
	beq	$a2, $zero, .Lbexit01; \
	lbu	$t8, OFFSET+1($a0); \
	bne	$a2, $a3, .Lbexit01

#define BYTECMP89(OFFSET) \
	lbu	$t9, OFFSET($a1); \
	beq	$t8, $zero, .Lbexit89; \
	lbu	$a2, OFFSET+1($a0); \
	bne	$t8, $t9, .Lbexit89

.Lbyteloop:
	lbu	$a2, 0($a0)
	BYTECMP01(0)
	BYTECMP89(1)
	BYTECMP01(2)
	BYTECMP89(3)
	BYTECMP01(4)
	BYTECMP89(5)
	BYTECMP01(6)
	lbu	$t9, 7($a1)
	beq	$t8, $zero, .Lbexit89
	addiu	$a0, $a0, 8
	bne	$t8, $t9, .Lbexit89
	addiu	$a1, $a1, 8
	b	.Lbyteloop

.Lbexit01:
	subu	$a0, $a2, $a3
	jr	$ra
.Lbexit89:
	subu	$a0, $t8, $t9
	jr	$ra
