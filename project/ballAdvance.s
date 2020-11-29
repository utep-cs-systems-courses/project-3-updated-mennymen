	.arch msp430g2553
	.p2align 1,0
	
	.text
jt:				; jump table
	.word option1		; jt[0]
	.word option2		; jt[1]
	
	
	.global ballSoundUpdateState	
ballSoundUpdateState:
	mov.b r12, r13 		
	cmp #3, r12		; if r12 >= 3
	jhs end

	add.b r13, r13		; r13 = r13*2
	mov jt(r13), r0		; jump to respective option from jump table

option1:
	mov.b #1, r13		; r13 = 1
	jmp end

option2:
	mov.b #0, r13		; r13 = 0
	jmp end

end:
	call #ballSoundAdvance
	mov.b r13, r12		; move what is in r13 to r12 before we pop
	pop r0
