.linkrelax
.module pic1
.set noreorder
.global dlsym
.hidden __dlsym
.type dlsym,@function
dlsym:
	move   $a2, $ra
	bc     __dlsym
