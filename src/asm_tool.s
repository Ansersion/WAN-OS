.text
.global 	SHUTDOWN_IRQ, OPEN_IRQ
.code 		16
.syntax 	unified
.align

SHUTDOWN_IRQ:
	CPSID 	I
	BX 		LR

OPEN_IRQ:
	CPSIE 	I
	BX 		LR

.end
