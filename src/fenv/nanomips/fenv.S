#ifndef __mips_soft_float

.set noreorder

.global feclearexcept
.type  feclearexcept,@function
feclearexcept:
	and     $4, $4, 0x7c
	cfc1    $5, $31
	or      $5, $5, $4
	xor     $5, $5, $4
	ctc1    $5, $31
	li      $2, 0
	jrc     $ra

.global feraiseexcept
.type  feraiseexcept,@function
feraiseexcept:
	and     $4, $4, 0x7c
	cfc1    $5, $31
	or      $5, $5, $4
	ctc1    $5, $31
	li      $2, 0
	jrc     $ra

.global fetestexcept
.type  fetestexcept,@function
fetestexcept:
	and     $4, $4, 0x7c
	cfc1    $2, $31
	and     $2, $2, $4
	jrc     $ra

.global fegetround
.type  fegetround,@function
fegetround:
	cfc1    $2, $31
	andi    $2, $2, 3
	jrc     $ra

.global __fesetround
.type __fesetround,@function
__fesetround:
	cfc1    $5, $31
	li      $6, -4
	and     $5, $5, $6
	or      $5, $5, $4
	ctc1    $5, $31
	li      $2, 0
	jrc     $ra

.global fegetenv
.type  fegetenv,@function
fegetenv:
	cfc1    $5, $31
	sw      $5, 0($4)
	li      $2, 0
	jrc     $ra

.global fesetenv
.type  fesetenv,@function
fesetenv:
	addiu   $5, $4, 1
	beqzc   $5, 1f
	lw      $5, 0($4)
1:	ctc1    $5, $31
	li      $2, 0
	jrc     $ra

#endif
