#include <clk.h>

void InitClk(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	if(RCC_WaitForHSEStartUp() != SUCCESS) {
		RCC_DeInit();
		return;
	}
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	FLASH_SetLatency(FLASH_Latency_2);  
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	// RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div1);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
	RCC_PLLCmd(ENABLE); 
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
	}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while (RCC_GetSYSCLKSource() != 0x08) {
	}

}
