.set noreorder
.global __clone
.type   __clone,@function
__clone:
	# Save function pointer and argument pointer on new thread stack
	and   $a1, $a1, -8
	subu  $a1, $a1, 16
	sw    $a0, 0($a1)
	sw    $a3, 4($a1)

	# Shuffle (fn,sp,fl,arg,ptid,tls,ctid) to (fl,sp,ptid,tls,ctid)
	move  $a0, $a2
	move  $a2, $8
	move  $a3, $9
	move  $8, $10
	li    $11, 220
	syscall

	beqzc $a0, 1f
	jrc   $ra

1:	lw    $t9, 0($sp)
	lw    $a0, 4($sp)
	jrc   $t9
