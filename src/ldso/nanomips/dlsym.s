.set noreorder
.global dlsym
.hidden __dlsym
.type dlsym,@function
dlsym:
	aluipc       $gp, %pcrel_hi(_gp)
	move         $a2, $ra
	lw           $t9, %call16(__dlsym)($gp)
	save         32, $ra
	jalrc        $t9
	restore.jrc  32, $ra
