#include <stm32f10x_usart.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <usart.h>
#include <misc.h>

void USART1_Configuration(uint32_t bound)
{
	
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	/* USART clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	USART_DeInit(USART1);
	
	/* Usart init£¬9600£¬8bit data bit,1 stop bit, No Parity and flow control, rx tx enable */
	USART_InitStructure.USART_BaudRate               = bound;
	USART_InitStructure.USART_WordLength             = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits               = USART_StopBits_1;
	USART_InitStructure.USART_Parity                 = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl    = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                   = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		
	USART_Cmd(USART1, ENABLE);
}
