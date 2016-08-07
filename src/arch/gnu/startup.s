.EQU 	_MSP_TOP,		0x20008000              
@ .EQU 	_RAM_ADDR, 		0x20000000

.text
.global 	_start, _irq_vectors
.code 		16
.syntax 	unified

_start:
				@ Stack has been destroyed, so
				@ invoking IRQ_LOCK is dangerous
				CPSID	I 	@ IRQ_LOCK

				ldr 	r0, 	=_MSP_TOP
				msr 	msp, 	r0

				mov 	r0, 	#0
				msr 	control, 	r0

				mov 	r0, 	#0x01000000
				msr 	psr,  	r0

				mov 	r0, 	#0x0
				msr 	psp,  	r0
				
				mov 	r0, #0
				mov 	r1, #0
				mov 	r2, #0
				mov 	r3, #0
				mov 	r4, #0
				mov 	r5, #0
				mov 	r6, #0
				mov 	r7, #0
				mov 	r8, #0
				mov 	r9, #0
				mov 	r10, #0
				mov 	r11, #0
				mov 	r12, #0
				mov 	lr, #0xfffffff9

				bl 		main

halt_loop:
				b 		halt_loop

@ irq vectors
.align 		9

_irq_vectors:
	.word _MSP_TOP
	.word _start+1 			@ '+1' is used to avoid UsageFault
	.word IRQ_Nmi 	
	.word IRQ_HardFault 
	.word IRQ_MemManage
	.word IRQ_BusFault 	
	.word IRQ_UsageFault 
	.word IRQ_NULL_7 	
	.word IRQ_NULL_8
	.word IRQ_NULL_9 	
	.word IRQ_NULL_10 	
	.word IRQ_SVC 	
	.word IRQ_DebugMon
	.word IRQ_NULL_13 	
	.word IRQ_PendSV 	
	.word IRQ_SysTick
	@ .word _RAM_ADDR+_start+1 			@ '+1' is used to avoid UsageFault
	@ .word _RAM_ADDR+IRQ_Nmi 	
	@ .word _RAM_ADDR+IRQ_HardFault 
	@ .word _RAM_ADDR+IRQ_MemManage
	@ .word _RAM_ADDR+IRQ_BusFault 	
	@ .word _RAM_ADDR+IRQ_UsageFault 
	@ .word _RAM_ADDR+IRQ_NULL_7 	
	@ .word _RAM_ADDR+IRQ_NULL_8
	@ .word _RAM_ADDR+IRQ_NULL_9 	
	@ .word _RAM_ADDR+IRQ_NULL_10 	
	@ .word _RAM_ADDR+IRQ_SVC 	
	@ .word _RAM_ADDR+IRQ_DebugMon
	@ .word _RAM_ADDR+IRQ_NULL_13 	
	@ .word _RAM_ADDR+IRQ_PendSV 	
	@ .word _RAM_ADDR+IRQ_SysTick

	.end
