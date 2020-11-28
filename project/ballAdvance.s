	.data
ballSound:
	.word 0

	.text
jt:
	.word option1		; jt[0]
	.word option2		; jt[1]
	
	
	.global ballSoundUpdateState	
ballSoundUpdateState:
	mov.b r12, &ballSound
	cmp.b #0, r12
	jn end

	add r12, r12
	mov jt(r12), r0

option1:
	mov.b #1, &ballSound
	jmp end

option2:
	mov.b #0, &ballSound
	jmp end

end:
	mov.b &ballSound, r12
	call #ballSoundAdvance
	pop r0
