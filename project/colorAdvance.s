	.arch msp430g2553
	.p2align 1,0

	.extern ballColorState

	.global colorAdvance
colorAdvance:
	sub #2, r1
	call #ballColorAdvance
	mov r12, 0(r1)
	cmp #0, 0(r1)
	jn if

	jmp else
	
if:	
	mov #5, &ballColorState
	jmp end
	
else:
	sub #1, &ballColorState
	
end:
	add #2, r1
	pop r0
