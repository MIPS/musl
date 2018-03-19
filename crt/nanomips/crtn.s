.set noreorder

.section .init
	restore.jrc 32,$ra,$gp

.section .fini
	restore.jrc 32,$ra,$gp
