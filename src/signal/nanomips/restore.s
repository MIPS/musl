.set    noreorder
.global __restore
.global __restore_rt
.type   __restore,@function
.type   __restore_rt,@function
__restore:
__restore_rt:
	li $a7, 139	# __NR_rt_sigreturn
	syscall32
