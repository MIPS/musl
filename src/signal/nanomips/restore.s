.set    noreorder
.global __restore
.global __restore_rt
.type   __restore,@function
.type   __restore_rt,@function
__restore:
__restore_rt:
	li $11, 139	# __NR_rt_sigreturn
	syscall
