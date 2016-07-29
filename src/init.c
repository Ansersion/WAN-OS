#include "init.h"
#include "stm32f10x_usart.h"
#include <irq.h>
#include <schedule.h>
#include <core_header.h>

int InitUsart(int baud_rate, 	int word_len, 	int stop_bit, 
              int parity,       int flow_ctrl,  uint32_t mode) 
{
	USART_InitTypeDef USART_InitType;

	USART_InitType.USART_BaudRate= baud_rate;

	if(PMT_USART_WORD_LEN_8 == word_len) {
		USART_InitType.USART_WordLength = USART_WordLength_8b;
	} else if(PMT_USART_WORD_LEN_9 == word_len) {
		USART_InitType.USART_WordLength = USART_WordLength_9b;
	} else {
		// default: word length = 8 bits;
		USART_InitType.USART_WordLength = USART_WordLength_8b;
	}

	if(PMT_USART_STOP_BIT_1 == stop_bit) {
		USART_InitType.USART_StopBits = USART_StopBits_1;
	} else if(PMT_USART_STOP_BIT_0_5 == stop_bit) {
		USART_InitType.USART_StopBits = USART_StopBits_0_5;
	} else if(PMT_USART_STOP_BIT_2 == stop_bit) {
		USART_InitType.USART_StopBits = USART_StopBits_2;
	} else if(PMT_USART_STOP_BIT_1_5 == stop_bit) {
		USART_InitType.USART_StopBits = USART_StopBits_1_5;
	} else {
		// default: stop bits = 1 bit;
		USART_InitType.USART_StopBits = USART_StopBits_1;
	}

	if(PMT_USART_PARITY_NONE == parity) {
		USART_InitType.USART_Parity = USART_Parity_No;
	} else if(PMT_USART_PARITY_ODD == parity) {
		USART_InitType.USART_Parity = USART_Parity_Odd;
	} else if(PMT_USART_PARITY_EVEN == parity) {
		USART_InitType.USART_Parity = USART_Parity_Even;
	} else {
		// default: parity = none;
		USART_InitType.USART_Parity = USART_Parity_No;
	}

	if(PMT_USART_FLOW_CTRL_None == flow_ctrl) {
		USART_InitType.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	} else if(PMT_USART_FLOW_CTRL_RTS == flow_ctrl) {
		USART_InitType.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	} else if(PMT_USART_FLOW_CTRL_CTS == flow_ctrl) {
		USART_InitType.USART_HardwareFlowControl = USART_HardwareFlowControl_CTS;
	} else if(PMT_USART_FLOW_CTRL_RTS_CTS == flow_ctrl) {
		USART_InitType.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
	} else {
		// default: stop bits = 1 bit;
		USART_InitType.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	}

	USART_InitType.USART_Mode = 0;
	if(MSK_USART_RECV_ENABLE | mode) {
		USART_InitType.USART_Mode |= USART_Mode_Rx;
	}
	if(MSK_USART_SEND_ENABLE | mode) {
		USART_InitType.USART_Mode |= USART_Mode_Tx;
	}

	return 0;
}

void OSRun()
{
	IRQ_LOCK();
	TaskTCB * tmp = Schd_GetTaskTCBNow();
	tmp->StkTopPtr += 8;
	__set_PSP((uint32_t)(tmp->StkTopPtr));
	// Schd_Schdule();
	Schd_TaskCtxSw();
	IRQ_UNLOCK();
}
