.text
.global 	_irq_vectors
.code 		16
.syntax 	unified
.align

.equ 		_MSP_TOP, 	0x20010000
.equ 	_RAM_ADDR, 		0x20000000
.align 		9

_irq_vectors:
	.word _MSP_TOP
	.word _RAM_ADDR+_start+1 	  				@ '+1' is used to avoid UsageFault
	.word _RAM_ADDR+IRQ_Nmi 	
	.word _RAM_ADDR+IRQ_HardFault 
	.word _RAM_ADDR+IRQ_MemManage
	.word _RAM_ADDR+IRQ_BusFault 	
	.word _RAM_ADDR+IRQ_UsageFault 
	.word _RAM_ADDR+IRQ_NULL_7 	
	.word _RAM_ADDR+IRQ_NULL_8
	.word _RAM_ADDR+IRQ_NULL_9 	
	.word _RAM_ADDR+IRQ_NULL_10 	
	.word _RAM_ADDR+IRQ_SVC 	
	.word _RAM_ADDR+IRQ_DebugMon
	.word _RAM_ADDR+IRQ_NULL_13 	
	.word _RAM_ADDR+IRQ_PendSV 	
	.word _RAM_ADDR+IRQ_SysTick
