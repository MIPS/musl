.set noreorder

.section .init
.global _init
.type _init,@function
.align 2
_init:
	save 32,$ra,$gp

.section .fini
.global _fini
.type _fini,@function
.align 2
_fini:
	save 32,$ra,$gp
