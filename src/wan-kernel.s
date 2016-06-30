.EQU 	RCC_BASE,                            0x40021000
.EQU 	RCC_CR,                              (RCC_BASE + 0x00)
.EQU 	RCC_CFGR,                            (RCC_BASE + 0x04)
.EQU 	RCC_CIR,                             (RCC_BASE + 0x08)
.EQU 	RCC_APB2RSTR,                        (RCC_BASE + 0x0C)
.EQU 	RCC_APB1RSTR,                        (RCC_BASE + 0x10)
.EQU 	RCC_AHBENR,                          (RCC_BASE + 0x14)
.EQU 	RCC_APB2ENR,                         (RCC_BASE + 0x18)
.EQU 	RCC_APB1ENR,                         (RCC_BASE + 0x1C)
.EQU 	RCC_BDCR,                            (RCC_BASE + 0x20)
.EQU 	RCC_CSR,                             (RCC_BASE + 0x24)

.EQU 	GPIOC_BASE,                          0x40010800
.EQU 	GPIOC_CRL,                           (GPIOC_BASE + 0x00)
.EQU 	GPIOC_CRH,                           (GPIOC_BASE + 0x04)
.EQU 	GPIOC_IDR,                           (GPIOC_BASE + 0x08)
.EQU 	GPIOC_ODR,                           (GPIOC_BASE + 0x0C)
.EQU 	GPIOC_BSRR,                          (GPIOC_BASE + 0x10)
.EQU 	GPIOC_BRR,                           (GPIOC_BASE + 0x14)
.EQU 	GPIOC_LCKR,                          (GPIOC_BASE + 0x18)

.EQU 	MSP_TOP,			0x20005000              
.EQU 	PSP_TOP, 			0x20004E00              

.EQU 	DelayTime,			13000000
.EQU 	CLRPEND0,  			0xE000E280
.EQU 	FLASH_ACR, 			0x40022000


.EQU            	Bit0,                     0x00000001
.EQU            	Bit1,                     0x00000002
.EQU            	Bit2,                     0x00000004
.EQU            	Bit3,                     0x00000008
.EQU            	Bit4,                     0x00000010
.EQU            	Bit5,                     0x00000020
.EQU            	Bit6,                     0x00000040
.EQU            	Bit7,                     0x00000080
.EQU            	Bit8,                     0x00000100
.EQU            	Bit9,                     0x00000200
.EQU            	Bit10,                    0x00000400
.EQU            	Bit11,                    0x00000800
.EQU            	Bit12,                    0x00001000
.EQU            	Bit13,                    0x00002000
.EQU            	Bit14,                    0x00004000
.EQU            	Bit15,                    0x00008000
.EQU            	Bit16,                    0x00010000
.EQU            	Bit17,                    0x00020000
.EQU            	Bit18,                    0x00040000
.EQU            	Bit19,                    0x00080000
.EQU            	Bit20,                    0x00100000
.EQU            	Bit21,                    0x00200000
.EQU            	Bit22,                    0x00400000
.EQU            	Bit23,                    0x00800000
.EQU            	Bit24,                    0x01000000
.EQU            	Bit25,                    0x02000000
.EQU            	Bit26,                    0x04000000
.EQU            	Bit27,                    0x08000000
.EQU            	Bit28,                    0x10000000
.EQU            	Bit29,                    0x20000000
.EQU            	Bit30,                    0x40000000
.EQU            	Bit31,                    0x80000000

.equ 		_wan_ram, 	0x20008000
.equ 		_max_ram, 	0x20010000

	
.text
.global 	_start
.code 		16
.syntax 	unified

_start:
				CPSID	I
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
				mov 	lr, #0
				
				ldr 	r0, =CLRPEND0
				ldr 	r1, [r0]
				orr 	r1, #0xFFFFFFFF
				str 	r1, [r0]

				bl 		main

halt_loop:
				b 		halt_loop

                .END
