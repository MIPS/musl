.set noreorder

.section .init
	lw $gp,24($sp)
	lw $ra,28($sp)
	addu $sp,$sp,32
	jrc $ra

.section .fini
	lw $gp,24($sp)
	lw $ra,28($sp)
	addu $sp,$sp,32
	jrc $ra
