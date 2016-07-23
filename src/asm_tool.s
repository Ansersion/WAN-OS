.text
.global 	IRQ_LOCK, IRQ_UNLOCK, IRQ_PendSV
.code 		16
.syntax 	unified
.align

IRQ_LOCK:
	CPSID 	I
	BX 		LR

IRQ_UNLOCK:
	CPSIE 	I
	BX 		LR

IRQ_PendSV:
	cpsid 	I
	mrs 	r0, psp

@ save r4-r11 to stack
	sub 	r0, r0, #0x20
	msr 	psp, r0
	stm 	r0, {r4, r11}

@ set next task "stack-top-pointer" to psp
	push 	{lr}
	bl 		IRQ_PendSV_C
	pop 	{lr}

@ restore r4-r11
	mrs 	r0, psp
	ldm 	r0!, {r4-r11}

@ exit
	msr 	psp, r0
	orr 	lr, lr, #0x04
	cpsie 	I
	bx 	lr

.end
