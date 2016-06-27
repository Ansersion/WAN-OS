.text
.global 	_irq_vectors
.code 		16
.syntax 	unified
.align

.equ 		_MSP_TOP, 	0x20005000

_irq_vectors:
	.word 	_MSP_TOP
	.word 	IRQ_Reset, 	IRQ_Nmi, 	IRQ_HardFault, 	IRQ_MemManage
	.word 	IRQ_BusFault, 	IRQ_UsageFault, IRQ_NULL_7, 	IRQ_NULL_8
	.word 	IRQ_NULL_9, 	IRQ_NULL_10, 	IRQ_SVC, 	IRQ_DebugMon
	.word 	IRQ_NULL_13, 	IRQ_PendSV, 	IRQ_SysTick
