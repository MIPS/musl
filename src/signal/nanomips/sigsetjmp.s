.linkrelax
.module pic1
.set noreorder
.global sigsetjmp
.global __sigsetjmp
.type sigsetjmp,@function
.type __sigsetjmp,@function
sigsetjmp:
__sigsetjmp:
	beqzc   $a1, 1f

	sw      $ra, 104($a0)
	sw      $s0, 124($a0)

	move    $s0, $a0
.hidden ___setjmp
	balc    ___setjmp

	move    $a1, $a0
	move    $a0, $s0
	lw      $ra, 104($a0)
	lw      $s0, 124($a0)

.hidden __sigsetjmp_tail
	bc      __sigsetjmp_tail

.hidden ___setjmp
1:	bc      ___setjmp
