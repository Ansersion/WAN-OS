	IMPORT  IRQ_PendSV_C
	
	EXPORT	IRQ_LOCK
	EXPORT 	IRQ_UNLOCK
	EXPORT 	PendSV_Handler
	EXPORT 	SVC_Handler
	
; NVIC_INT_CTRL	EQU			0xE000ED04	; Address of NVIC Interruptions Control Register
; NVIC_PENDSVSET	EQU			0x10000000	; Enable PendSV
; NVIC_SYSPRI14   EQU     	0xE000ED22  ; System priority register (priority 14).
; NVIC_PENDSV_PRI EQU         0xFF        ; PendSV priority value (lowest).
	
	PRESERVE8 ; align 8

	AREA    |.text|, CODE, READONLY 
	THUMB 

IRQ_LOCK
	CPSID	I	
	BX	LR

IRQ_UNLOCK
	CPSIE	I	
	BX	LR 

; IRQ_SVC
SVC_Handler
	TST 	LR, #0x4
	ITE 	EQ
	MRSEQ 	R0, MSP
	MRSNE 	R0, PSP
	LDR 	R1, [R0,#24]
	LDR 	R2, [R0]
	LDRB 	R0, [R1,#-2]
	MOV 	R1, R2
	PUSH 	{LR}
	BL 	IRQ_SVC_C
	POP 	{LR}
	BX 		LR

; IRQ_PendSV
PendSV_Handler
	cpsid 	I
	mrs 	r0, psp

	sub 	r0, r0, #0x20
	msr 	psp, r0
	stm 	r0, {r4-r11}

	push 	{lr}
	bl 		IRQ_PendSV_C
	pop 	{lr}

	mrs 	r0, psp
	ldm 	r0!, {r4-r11}

	msr 	psp, r0
	orr 	lr, lr, #0x04
	cpsie 	I
	bx 		lr

	align 4
	end
