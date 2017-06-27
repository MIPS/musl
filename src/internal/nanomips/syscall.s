.set    noreorder
.global __syscall
.hidden __syscall
.type   __syscall,@function
__syscall:

	# syscall number in a7
	move    $a7, $a0

	# syscall arguments from a1-a5
	# a6 is not used as an argument to syscall
	move    $a0, $a1
	move    $a1, $a2
	move    $a2, $a3
	move    $a3, $a4
	move    $a4, $a5
	move    $a5, $a6

	syscall32

	# don't negate the error code in va0
	jrc     $ra
