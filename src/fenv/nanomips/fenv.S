#ifndef __mips_soft_float

.set noreorder

.global feclearexcept
.type  feclearexcept,@function
feclearexcept:
	and     $a0, $a0, 0x7c
	cfc1    $t0, $31
	or      $t0, $t0, $a0
	xor     $t0, $t0, $a0
	ctc1    $t0, $31
	li      $a0, 0
	jrc     $ra

.global feraiseexcept
.type  feraiseexcept,@function
feraiseexcept:
	and     $a0, $a0, 0x7c
	cfc1    $t0, $31
	or      $t0, $t0, $a0
	ctc1    $t0, $31
	li      $a0, 0
	jrc     $ra

.global fetestexcept
.type  fetestexcept,@function
fetestexcept:
	and     $a0, $a0, 0x7c
	cfc1    $t0, $31
	and     $a0, $t0, $a0
	jrc     $ra

.global fegetround
.type  fegetround,@function
fegetround:
	cfc1    $a0, $31
	andi    $a0, $a0, 3
	jrc     $ra

.global __fesetround
.type __fesetround,@function
__fesetround:
	cfc1    $t0, $31
	li      $t1, -4
	and     $t0, $t0, $t1
	or      $t0, $t0, $a0
	ctc1    $t0, $31
	li      $a0, 0
	jrc     $ra

.global fegetenv
.type  fegetenv,@function
fegetenv:
	cfc1    $t0, $31
	sw      $t0, 0($a0)
	li      $a0, 0
	jrc     $ra

.global fesetenv
.type  fesetenv,@function
fesetenv:
	addiu   $t0, $a0, 1
	beqzc   $t0, 1f
	lw      $t0, 0($a0)
1:	ctc1    $t0, $31
	li      $a0, 0
	jrc     $ra

#endif
