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

#define PERIPH_BASE           ((unsigned int)0x40000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOA 			((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOD 			((GPIO_TypeDef *) GPIOD_BASE)
#define LED_RED_TURN() 	(GPIOA->ODR ^= 1<<8)
#define LED_GREEN_TURN() (GPIOD->ODR ^= 1<<2)


void main()
{
	int i;
	// int count;
	// IRQ_Init();
	Init_SysTickIRQ(9000, 1);
	i = 3;
	while(--i > 0) {
		while((USART1->SR&0X40)==0);
		USART1_SEND('f');
		while((USART1->SR&0X40)==0);
		USART1_SEND('\r');
		while((USART1->SR&0X40)==0);
		USART1_SEND('\n');
	}
	IRQ_LOCK();
	while(--i > 0) {
		while((USART1->SR&0X40)==0);
		USART1_SEND('g');
		while((USART1->SR&0X40)==0);
		USART1_SEND('\r');
		while((USART1->SR&0X40)==0);
		USART1_SEND('\n');
	}

	// count = 3;
	// while(count--) {
	// 	for(i = 0; i < 5000000; i++) {
	// 	}
	// 	LED_RED_TURN();
	// }
	while(1) {
		for(i = 0; i < 500000; i++) {
		}
		LED_RED_TURN();
		// while((USART1->SR&0X40)==0);
		// USART1_SEND('a');
		// while((USART1->SR&0X40)==0);
		// USART1_SEND('\r');
		// while((USART1->SR&0X40)==0);
		// USART1_SEND('\n');
		// LED_GREEN_TURN();
	}
}

