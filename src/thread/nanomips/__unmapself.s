.set noreorder
.global __unmapself
.type   __unmapself,@function
__unmapself:
	li   $t4, 215		# munmap
	syscall32
	li   $a0, 0
	li   $t4, 93		# exit
	syscall32
