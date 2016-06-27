#include "irq.h"

typedef struct
{ 
	volatile unsigned int CRL; 
	volatile unsigned int CRH; 
	volatile unsigned int IDR; 
	volatile unsigned int ODR;
	volatile unsigned int BSRR;
	volatile unsigned int BRR;
	volatile unsigned int LCKR;
} GPIO_TypeDef;
#define PERIPH_BASE           ((unsigned int)0x40000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOA 			((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOD 			((GPIO_TypeDef *) GPIOD_BASE)
#define LED_RED_TURN() 	(GPIOA->ODR ^= 1<<8)
#define LED_GREEN_TURN() (GPIOD->ODR ^= 1<<2)

// #define REG_AIRCR 					((uint32_t *)0xE000ED0C)
#define MSK_VECTKEY 				0x05FA0000
#define MSK_GROUP_SUBPRIORITY_0 	0x00000000
#define MSK_GROUP_SUBPRIORITY_1 	0x00000100
#define MSK_GROUP_SUBPRIORITY_2 	0x00000200
#define MSK_GROUP_SUBPRIORITY_3 	0x00000300
#define MSK_GROUP_SUBPRIORITY_4 	0x00000400
#define MSK_GROUP_SUBPRIORITY_5 	0x00000500
#define MSK_GROUP_SUBPRIORITY_6 	0x00000600
#define MSK_GROUP_SUBPRIORITY_7 	0x00000700

#define PMT_EXP_MEM 			4
#define PMT_EXP_BUS 			5
#define PMT_EXP_USAGE 			6
#define PMT_EXP_NULL_7 			7
#define PMT_EXP_NULL_8 			8
#define PMT_EXP_NULL_9 			9
#define PMT_EXP_NULL_10 		10
#define PMT_EXP_SVC 			11
#define PMT_EXP_DEBUG 			12
#define PMT_EXP_NULL_13 		13
#define PMT_EXP_PEND_SV 		14
#define PMT_EXP_SYSTICK 		15

#define REG_EXP_PRI_MEM 			((uint32_t *)0xE000ED18)
#define REG_EXP_PRI_BUS 			((uint32_t *)0xE000ED19)
#define REG_EXP_PRI_USAGE 			((uint32_t *)0xE000ED1A)
#define REG_EXP_PRI_NULL_7 			((uint32_t *)0xE000ED1B)
#define REG_EXP_PRI_NULL_8 			((uint32_t *)0xE000ED1C)
#define REG_EXP_PRI_NULL_9 			((uint32_t *)0xE000ED1D)
#define REG_EXP_PRI_NULL_10 		((uint32_t *)0xE000ED1E)
#define REG_EXP_PRI_SVC 			((uint32_t *)0xE000ED1F)
#define REG_EXP_PRI_DEBUG 			((uint32_t *)0xE000ED20)
#define REG_EXP_PRI_NULL_13 		((uint32_t *)0xE000ED21)
#define REG_EXP_PRI_PEND_SV 		((uint32_t *)0xE000ED22)
#define REG_EXP_PRI_SYSTICK 		((uint32_t *)0xE000ED23)

static uint32_t * IRQ_PriorityRegList[] = {
	0,
	0, 
	0, 
	0, 
	REG_EXP_PRI_MEM, 
	REG_EXP_PRI_BUS, 
	REG_EXP_PRI_USAGE, 
	REG_EXP_PRI_NULL_7, 
	REG_EXP_PRI_NULL_8, 
	REG_EXP_PRI_NULL_9, 
	REG_EXP_PRI_NULL_10,
	REG_EXP_PRI_SVC, 
	REG_EXP_PRI_DEBUG, 
	REG_EXP_PRI_NULL_13,
	REG_EXP_PRI_PEND_SV,
	REG_EXP_PRI_SYSTICK
};

#define PMT_IRQ_PRIORITY_0 			0x00
#define PMT_IRQ_PRIORITY_1 			0x10
#define PMT_IRQ_PRIORITY_2 			0x20
#define PMT_IRQ_PRIORITY_3 			0x30
#define PMT_IRQ_PRIORITY_4 			0x40
#define PMT_IRQ_PRIORITY_5 			0x50
#define PMT_IRQ_PRIORITY_6 			0x60
#define PMT_IRQ_PRIORITY_7 			0x70
#define PMT_IRQ_PRIORITY_8 			0x80
#define PMT_IRQ_PRIORITY_9 			0x90
#define PMT_IRQ_PRIORITY_10 		0xA0
#define PMT_IRQ_PRIORITY_11 		0xB0
#define PMT_IRQ_PRIORITY_12 		0xC0
#define PMT_IRQ_PRIORITY_13 		0xD0
#define PMT_IRQ_PRIORITY_14 		0xE0
#define PMT_IRQ_PRIORITY_15 		0xF0

extern void * _irq_vectors;

void IRQ_Reset()
{
	while(1);
}

void IRQ_Nmi()
{
	while(1);
}

void IRQ_HardFault(void)
{
	while(1);
}

void IRQ_MemManage(void)
{
	while(1);
}

void IRQ_BusFault(void)
{
	while(1);
}

void IRQ_UsageFault(void)
{
	while(1);
}

void IRQ_NULL_7(void)
{
}

void IRQ_NULL_8(void)
{
}

void IRQ_NULL_9(void)
{
}

void IRQ_NULL_10(void)
{
}

void IRQ_SVC(void)
{
}

void IRQ_DebugMon(void)
{
}

void IRQ_NULL_13(void)
{
}

void IRQ_PendSV(void)
{
}

void IRQ_SysTick(void)
{
	static uint32_t count = 0;
	if(++count < 100) {
		return;
	}
	count = 0;
	LED_GREEN_TURN();
}

#define PRM_MAX_TICKS 	0xFFFFFF
#define REG_SYSTICK_CTRL 	((uint32_t *)0xE000E010)
#define REG_SYSTICK_LOAD 	((uint32_t *)0xE000E014)
#define REG_SYSTICK_VAL 	((uint32_t *)0xE000E018)
#define REG_SYSTICK_CLBR 	((uint32_t *)0xE000E01C)
#define PRM_SYSTICK_CTRL_CLKSRC_CORE 	0x00000004 /* Flag of using core clock */
#define PRM_SYSTICK_CTRL_TICKINT 		0x00000002 /* Flag of enabling interrupt generation */
#define PRM_SYSTICK_CTRL_ENABLE 		0x00000001 /* Flag of enabling systick to time */
volatile int32_t Init_SysTickIRQ(uint32_t Ticks, uint32_t Priority)
{
	if(Ticks > PRM_MAX_TICKS) {
		return -1;
	}
	IRQ_SetPriority(PMT_EXP_SYSTICK, PMT_IRQ_PRIORITY_1);
	*REG_SYSTICK_LOAD 	= Ticks - 1;
	*REG_SYSTICK_VAL 	= 0;
	*REG_SYSTICK_CTRL 	= PRM_SYSTICK_CTRL_CLKSRC_CORE | 
							PRM_SYSTICK_CTRL_TICKINT |
							PRM_SYSTICK_CTRL_ENABLE;
	return 0;
}

volatile int32_t Init_IRQGroup(uint32_t GroupLimit)
{
	*REG_AIRCR = MSK_VECTKEY | GroupLimit;
	return 0;
}

void IRQ_Init(void)
{
	*REG_IRQ_VTOR = VTOR_RAM | WAN_VTOR_ADDRESS;
}

volatile int32_t IRQ_SetPriority(uint32_t IRQ_Number, uint8_t Priority)
{
	/* */
	if(IRQ_Number < 4 || IRQ_Number > 68) {
		return -1;
	}
	*IRQ_PriorityRegList[IRQ_Number] = Priority;
	return 0;
}

volatile int32_t IRQ_Enalbe(uint32_t IRQ_Number)
{
	return 0;
}

volatile int32_t IRQ_Disable(uint32_t IRQ_Number)
{
	return 0;
}

volatile int32_t IRQ_SetPend(uint32_t IRQ_Number)
{
	return 0;
}

volatile int32_t IRQ_ClrPend(uint32_t IRQ_Number)
{
	if(PMT_EXP_SYSTICK == IRQ_Number) {
		SHUTDOWN_IRQ();
		*REG_ICSR |= MSK_SYSTICK_CLRPEND;
		OPEN_IRQ();
	}
	if(PMT_EXP_PEND_SV == IRQ_Number) {
		SHUTDOWN_IRQ();
		*REG_ICSR |= MSK_PENDSV_CLRPEND;
		OPEN_IRQ();
	}
	return 0;
}

