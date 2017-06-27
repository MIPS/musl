.set noreorder
.global __unmapself
.type   __unmapself,@function
__unmapself:
	li   $s7, 215		# munmap
	syscall32
	li   $a0, 0
	li   $s7, 93		# exit
	syscall32
