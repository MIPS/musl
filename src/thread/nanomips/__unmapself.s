.set noreorder
.global __unmapself
.type   __unmapself,@function
__unmapself:
	li   $11, 215		# munmap
	syscall
	li   $a0, 0
	li   $11, 93		# exit
	syscall
