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
	mrs 	r0, psp

	@ store r0-r11
	sub 	r0, r0, #0x20
	stm 	r0, {r4-r11}

	@ change PSP to point the new "Schd_TaskTCB"
	bl 		IRQ_PendSV_C

	@ restore r0-r11
	mrs 	r0, psp

	@ restore r4-r11 
	ldm 	r0!, {r4-r11}
	msr 	psp, r0
	orr 	lr, lr, #0x04
	bx 		lr

.align

.end
