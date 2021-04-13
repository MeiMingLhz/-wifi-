#include "led.h"

void LED_GPIO_Init(void)
{
	AFIO_GPxConfig(GPIO_PC,AFIO_PIN_14,AFIO_MODE_DEFAULT);	//����PC14ΪĬ�ϸ���
	AFIO_GPxConfig(GPIO_PC,AFIO_PIN_15,AFIO_MODE_DEFAULT);
	
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_14,GPIO_DIR_OUT);	//����PC14�������
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_15,GPIO_DIR_OUT);	//����PC14�������
	
	
}

void LED_Set(void)
{
	GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_14,SET);
}

void LED_Reset(void)
{
	GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_14,RESET);
}

