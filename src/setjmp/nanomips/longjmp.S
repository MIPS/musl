.set noreorder
.global _longjmp
.global longjmp
.type _longjmp,@function
.type longjmp,@function
_longjmp:
longjmp:
#ifndef __mips_soft_float
	lwc1    $20, 56($a0)
	lwc1    $21, 60($a0)
	lwc1    $22, 64($a0)
	lwc1    $23, 68($a0)
	lwc1    $24, 72($a0)
	lwc1    $25, 76($a0)
	lwc1    $26, 80($a0)
	lwc1    $27, 84($a0)
	lwc1    $28, 88($a0)
	lwc1    $29, 92($a0)
	lwc1    $30, 96($a0)
	lwc1    $31, 100($a0)
#endif
	lw      $ra,  0($a0)
	lw      $sp,  4($a0)
	lwm     $s0,  8($a0), 8
	lw      $fp, 40($a0)
	lw      $gp, 44($a0)

	move    $a0, $a1
	bnezc   $a0, 1f
	addiu   $a0, $a0, 1
1:
	jrc     $ra
