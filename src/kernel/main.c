/* kernel headers */
#include <irq.h>
#include <stdio.h>
#include <schedule.h>
#include <init.h>
#include <memory.h>

/* TODO: ARCH headers */
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>


/* test */
#include <sys_call.h>

/*
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
*/

/* #define PERIPH_BASE           ((unsigned int)0x40000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOA 			((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOD 			((GPIO_TypeDef *) GPIOD_BASE)
*/
#define LED_RED_TURN() 	(GPIOA->ODR ^= 1<<8)
#define LED_GREEN_TURN() (GPIOD->ODR ^= 1<<2)

void * TaskRed(void * arg);
void * TaskGreen(void * arg);

// TASK_STK 	TaskRedStk[128];
// TASK_STK 	TaskGreenStk[128];

TASK_STK * TaskRedStk;
TASK_STK * TaskGreenStk;

TaskTCB TaskRedTcb;
TaskTCB TaskGreenTcb;


uint32_t global_count=0x5a5a5a5a;

int main()
{
	int i;
	uint32_t HeapSize;
	GPIO_InitTypeDef GPIO_InitType;
	GPIO_TypeDef * GPIO_Type;
	
	global_count=0xa5a5a5a5;
	
	IRQ_LOCK();
	
	Schd_Init();
	HeapSize = Mem_Init();
	
	IRQ_Init();
	Init_SysTickIRQ(9000, 1);
	NVIC_SetPriority(PendSV_IRQn, 0xf);
	NVIC_SetPriority(SVCall_IRQn, 0xD);
	IRQ_UNLOCK();
	
  TaskRedStk = Malloc(128);
  TaskGreenStk = Malloc(128);
	
	TaskRedTcb.StkTopPtr = TaskRedStk;
	TaskGreenTcb.StkTopPtr = TaskGreenStk;

	TaskRedTcb.StkSize = 128;
	TaskGreenTcb.StkSize = 128;

	Schd_CreateTask(TaskRed, NULL, &TaskRedTcb);
	Schd_CreateTask(TaskGreen, NULL, &TaskGreenTcb);

	Schd_SetTaskTCBNow(&TaskGreenTcb);
		

/*
	IRQ_Init();
	Init_SysTickIRQ(9000, 1);
	NVIC_SetPriority(PendSV_IRQn, 0xf);
	NVIC_SetPriority(SVCall_IRQn, 0xD);
	*/
		// Enable clock of GPIO-A and GPIO-D
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);
	
	//Enable clock of CRC unit
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	// GPIO output initialization;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitType.GPIO_Speed = GPIO_Speed_50MHz;
	
	// Initialize PA.8
	GPIO_Type = GPIOA;
	GPIO_InitType.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIO_Type, &GPIO_InitType);
	
	// Initialize PD.2
	GPIO_Type = GPIOD;
	GPIO_InitType.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIO_Type, &GPIO_InitType);
	
	OSRun();
	while(1) {
		for(i = 0; i < 500000; i++) {
		}
		LED_GREEN_TURN();
		// LED_RED_TURN();
		/* never come here */
	}

	// i = 3;
	// while(1) {
	// 	for(i = 0; i < 500000; i++) {
	// 	}
	// 	global_count++;
	// 	LED_GREEN_TURN();
	// }
	return 0;
}

void * TaskRed(void * arg)
{
	int i;
	while(1) {
		for(i = 0; i < 1000000; i++) {
		}
		// GPIOA->ODR |= 1<<8;
		// GPIOD->ODR |= 1<<2;
		LED_RED_TURN();
		/* LED_GREEN_TURN();
		for(i = 0; i < 500000; i++) {
		}
		LED_GREEN_TURN();
		for(i = 0; i < 250000; i++) {
		}
		LED_GREEN_TURN();
		*/
		// LED_GREEN_TURN();
		
	}
}

void * TaskGreen(void * arg)
{
	int i;
	while(1) {
		for(i = 0; i < 500000; i++) {
		}
		LED_GREEN_TURN();
	}
}
