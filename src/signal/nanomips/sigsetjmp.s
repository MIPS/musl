.set noreorder
.global sigsetjmp
.global __sigsetjmp
.type sigsetjmp,@function
.type __sigsetjmp,@function
sigsetjmp:
__sigsetjmp:
	aluipc  $gp, %pcrel_hi(_gp)
	beqzc   $a1, 1f

	sw      $ra, 104($4)
	sw      $s0, 124($4)
	lw      $t9, %call16(setjmp)($gp)

	move    $s0, $a0
	jalrc   $t9

	move    $a1, $a0
	move    $a0, $s0
	lw      $ra, 104($4)
	lw      $s0, 124($4)

.hidden __sigsetjmp_tail
	lw      $t9, %call16(__sigsetjmp_tail)($gp)
	jrc     $t9

1:	lw      $t9, %call16(setjmp)($gp)
	jrc     $t9
