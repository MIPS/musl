.set noreorder
.global sigsetjmp
.global __sigsetjmp
.type sigsetjmp,@function
.type __sigsetjmp,@function
sigsetjmp:
__sigsetjmp:
	aluipc  $gp, %pcrel_hi(_gp)
	beqzc   $5, 1f

	sw      $ra, 104($4)
	sw      $16, 104+4+16($4)
	lw      $25, %call16(setjmp)($gp)

	move    $16, $4
	jalrc   $25

	move    $5,$2
	move    $4,$16
	lw      $ra, 104($4)
	lw      $16, 104+4+16($4)

.hidden __sigsetjmp_tail
	lw      $25, %call16(__sigsetjmp_tail)($gp)
	jrc     $25

1:	lw      $25, %call16(setjmp)($gp)
	jrc     $25
