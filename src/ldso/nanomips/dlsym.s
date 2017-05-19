.set noreorder
.global dlsym
.hidden __dlsym
.type dlsym,@function
dlsym:
	aluipc       $gp, %pcrel_hi(_gp)
	move         $6, $ra
	lw           $25, %call16(__dlsym)($gp)
	save         32, $ra
	jalrc        $25
	restore.jrc  32, $ra
