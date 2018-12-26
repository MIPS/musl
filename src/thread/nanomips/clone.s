.linkrelax
.module pic1
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
	move  $a2, $a4
	move  $a3, $a5
	move  $a4, $a6
	li    $t4, 220	# __NR_clone
	syscall32

	beqzc $a0, 1f
	jrc   $ra

1:	lw    $t0, 0($sp)
	lw    $a0, 4($sp)
	jrc   $t0
