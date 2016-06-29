#include "printf_to_serial.h"
#include "stm32f10x_usart.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
        set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
	 /* Place your implementation of fputc here */
	 /* e.g. write a character to the USART */
	 USART_SendData(USART1, (unsigned char) ch);
	  /* Loop until the end of transmission */
	  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		    {}
	   return ch;
}


#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	// USART1->DR = (u8) ch;      
	// USART1->DR = (u8)ch;
	USART1_SEND(ch);
	return ch;
}
#endif
