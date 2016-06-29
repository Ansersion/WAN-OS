.text
.global 	IRQ_LOCK, IRQ_UNLOCK
.code 		16
.syntax 	unified
.align

IRQ_LOCK:
	CPSID 	I
	BX 		LR

IRQ_UNLOCK:
	CPSIE 	I
	BX 		LR

.end
