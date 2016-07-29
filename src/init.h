#ifndef INIT_H
#define INIT_H

#include <stdint.h>

#define PMT_USART_WORD_LEN_8 		0
#define PMT_USART_WORD_LEN_9 		1

#define PMT_USART_STOP_BIT_1 		0
#define PMT_USART_STOP_BIT_0_5 		1
#define PMT_USART_STOP_BIT_2 		2
#define PMT_USART_STOP_BIT_1_5 		3

#define PMT_USART_PARITY_NONE 		0
#define PMT_USART_PARITY_ODD 		1
#define PMT_USART_PARITY_EVEN 		2

#define PMT_USART_FLOW_CTRL_None 		0
#define PMT_USART_FLOW_CTRL_RTS 		1
#define PMT_USART_FLOW_CTRL_CTS 		2
#define PMT_USART_FLOW_CTRL_RTS_CTS 	3

#define MSK_USART_RECV_ENABLE 			0x01
#define MSK_USART_SEND_ENABLE 			0x02

int InitUsart(int baud_rate, 	int word_len, 	int stop_bit, 
              int parity,       int flow_ctrl,  uint32_t mode);
void OSRun();

#endif
