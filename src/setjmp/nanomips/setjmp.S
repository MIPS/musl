.set noreorder
.global __setjmp
.global _setjmp
.global setjmp
.type __setjmp,@function
.type _setjmp,@function
.type setjmp,@function
__setjmp:
_setjmp:
setjmp:
	sw      $ra,  0($a0)
	sw      $sp,  4($a0)
	swm     $s0,  8($a0), 8
	sw      $fp, 40($a0)
	sw      $gp, 44($a0)
#ifndef __mips_soft_float
	swc1    $20, 56($a0)
	swc1    $21, 60($a0)
	swc1    $22, 64($a0)
	swc1    $23, 68($a0)
	swc1    $24, 72($a0)
	swc1    $25, 76($a0)
	swc1    $26, 80($a0)
	swc1    $27, 84($a0)
	swc1    $28, 88($a0)
	swc1    $29, 92($a0)
	swc1    $30, 96($a0)
	swc1    $31, 100($a0)
#endif
	li      $a0, 0
	jrc     $ra
