#include <stm32f10x_usart.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_adc.h>

#include <adc.h>

void ADC_Configuration(void)
{
	ADC_InitTypeDef  ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN; 
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;  //����ģʽ 
    ADC_InitStructure.ADC_ScanConvMode      =DISABLE;      //������ͨ��ģʽ 
    ADC_InitStructure.ADC_ContinuousConvMode =ENABLE;      //����ת�� 
    ADC_InitStructure.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None; //ת������������ 
    ADC_InitStructure.ADC_DataAlign         =ADC_DataAlign_Right;   //�Ҷ��� 
    ADC_InitStructure.ADC_NbrOfChannel      =1;       //ɨ��ͨ���� 
    ADC_Init(ADC1,&ADC_InitStructure); 
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 1,ADC_SampleTime_1Cycles5); //ͨ��X,����ʱ��Ϊ
	ADC_Cmd(ADC1,ENABLE);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

uint16_t GetAdc(void)
{
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET); 
	return ADC_GetConversionValue(ADC1);
}
