.set    noreorder

.global __cp_begin
.hidden __cp_begin
.type   __cp_begin,@function
.global __cp_end
.hidden __cp_end
.type   __cp_end,@function
.global __cp_cancel
.hidden __cp_cancel
.type   __cp_cancel,@function
.hidden __cancel
.global __syscall_cp_asm
.hidden __syscall_cp_asm
.type   __syscall_cp_asm,@function
__syscall_cp_asm:
__cp_begin:
	lw      $a0, 0($a0)
	bnezc   $a0, __cp_cancel	# if self->cancel is set

	move    $t0, $a1		# save syscall number
	move    $a0, $a2
	move    $a1, $a3
	move    $a2, $a4
	move    $a3, $a5
	move    $a4, $a6
	move    $a5, $a7
	move    $a7, $t0		# syscall number in a7
	syscall

__cp_end:
	jrc     $ra

__cp_cancel:
	move    $t0, $ra		# save $ra
	.align	2
	balc32  1f
	.gpword .
	.gpword __cancel
1:	lw      $t1, 0($ra)
	subu    $t1, $ra, $t1
	lw      $t9, 4($ra)
	addu    $t9, $t9, $t1
	move    $ra, $t0
	jrc     $t9			# long __cancel()
