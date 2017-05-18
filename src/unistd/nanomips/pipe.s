.set noreorder
.global pipe
.type pipe,@function
pipe:
	aluipc   $gp, %pcrel_hi(_gp)
	li       $2, 4042
	syscall
	beqzc    $7, 1f
	subu     $4, $0, $2
	lw       $25, %call16(__syscall_ret)($gp)
	jrc      $25
1:	sw       $2, 0($4)
	sw       $3, 4($4)
	move     $2, $0
	jrc      $ra
