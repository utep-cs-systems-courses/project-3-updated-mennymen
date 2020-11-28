	.arch msp430g2553
	.p2align 1,0
	
	.text
jt:
	.word option1		; jt[0]
	.word option2		; jt[1]
	
	
	.global ballSoundUpdateState	
ballSoundUpdateState:
	mov.b r12, r13
	cmp #3, r12
	jhs end

	add.b r13, r13
	mov jt(r13), r0

option1:
	mov.b #1, r13
	jmp end

option2:
	mov.b #0, r13
	jmp end

end:
	call #ballSoundAdvance
	mov.b r13, r12
	pop r0
