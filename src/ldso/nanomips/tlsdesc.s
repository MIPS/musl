.hidden __tls_get_new

.global __tlsdesc_dynamic
.hidden __tlsdesc_dynamic
.type __tlsdesc_dynamic,@function
__tlsdesc_dynamic:
	save          16, $ra, $s0-$s2
	lw            $s1, 4($a0)      # a
	lw            $s1, 0($s1)      # a->modidx
	rdhwr         $s0, $29         # tp
	lw            $s0, 4($s0)      # dtv
	lw            $s2, 0($s0)      # dtv[0]
	bltc          $s2, $s1, 1f
	lwx           $s2, $s1($s0)    # dtv[a->modidx]
	lw            $s1, 4($a0)      # a
	lw            $s1, 4($s1)      # a->offset
	addu          $a0, $s2, $s1
2:	restore.jrc   16, $ra, $s0-$s2
1:	save          64, $r2-$r15
	save          16, $r24-$r25
	balc          __tls_get_new
	restore       16, $r24-$r25
	restore       64, $r2-$r15
	bc 2b
