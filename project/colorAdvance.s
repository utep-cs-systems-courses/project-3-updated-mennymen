	.arch msp430g2553
	.p2align 1,0

	.global colorAdvance
colorAdvance:
	sub #4, r1		; Making space for two auto-variables
	call #ballColorAdvance
	mov r12, 0(r1)		; Put what is in r12 to 0(r1)
	mov #0, 2(r1)		; 2(r1) = 0, just added this to have two auto-variables
	cmp 2(r1), 0(r1)	; compare 0(r1) - 2(r1), if the result is negative, jump to if
	jn if

	jmp else
	
if:	
	mov #5, &ballColorState	; ballColorState = 5
	jmp end
	
else:
	sub #1, &ballColorState ; ballColorState -= 1
	
end:
	add #4, r1		; Reset the stack pointer
	pop r0
