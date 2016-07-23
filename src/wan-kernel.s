.EQU 	MSP_TOP,		0x20008000              
.EQU 	_RAM_ADDR, 		0x20000000

.text
.global 	_start, JMP_MAIN
.code 		16
.syntax 	unified

_start:
				@ Stack has been destroyed, so
				@ invoking IRQ_LOCK is dangerous
				CPSID	I 	@ IRQ_LOCK
				ldr 	r0, =MSP_TOP
				msr		msp,	r0
				mov 	r0, #0
				msr 	control, r0
				
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

				bl 		main

halt_loop:
				b 		halt_loop

                .END
