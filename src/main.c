#include "irq.h"
#include <stdio.h>
#include "stm32f10x_usart.h"


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

unsigned char global_count=0;

int main()
{
	int i;
	IRQ_Init();
	Init_SysTickIRQ(9000, 1);
	IRQ_UNLOCK();
	i = 3;
	while(1) {
		for(i = 0; i < 500000; i++) {
		}
		global_count++;
		LED_GREEN_TURN();
	}
	return 0;
}

