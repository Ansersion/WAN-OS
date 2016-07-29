#include "irq.h"
#include <stdio.h>
#include "stm32f10x_usart.h"
#include <schedule.h>
#include <init.h>


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

// #define PERIPH_BASE           ((unsigned int)0x40000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOA 			((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOD 			((GPIO_TypeDef *) GPIOD_BASE)
#define LED_RED_TURN() 	(GPIOA->ODR ^= 1<<8)
#define LED_GREEN_TURN() (GPIOD->ODR ^= 1<<2)

void * TaskRed(void * arg);
void * TaskGreen(void * arg);

TASK_STK 	TaskRedStk[128];
TASK_STK 	TaskGreenStk[128];

TaskTCB TaskRedTcb;
TaskTCB TaskGreenTcb;


unsigned char global_count=0;

int main()
{
	int i;

	Schd_Init();
	TaskRedTcb.StkTopPtr = TaskRedStk;
	TaskGreenTcb.StkTopPtr = TaskGreenStk;

	TaskRedTcb.StkSize = 128;
	TaskGreenTcb.StkSize = 128;

	// Schd_CreateTask(TaskRed, NULL, &TaskRedTcb);
	// Schd_CreateTask(TaskGreen, NULL, &TaskGreenTcb);

	Schd_SetTaskTCBNow(&TaskGreenTcb);

	IRQ_Init();
	Init_SysTickIRQ(9000, 1);
	// IRQ_UNLOCK();
	
	// OSRun();
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
		for(i = 0; i < 250000; i++) {
		}
		// GPIOA->ODR |= 1<<8;
		GPIOD->ODR |= 1<<2;
		// LED_RED_TURN();
	}
}

void * TaskGreen(void * arg)
{
	int i;
	while(1) {
		for(i = 0; i < 500000; i++) {
		}
		// GPIOA->ODR &= ~(1<<8);
		GPIOD->ODR &= ~(1<<2);
		// LED_GREEN_TURN();
	}
}
