#include "led.h"

void LED_GPIO_Init(void)
{
	AFIO_GPxConfig(GPIO_PC,AFIO_PIN_14,AFIO_MODE_DEFAULT);	//设置PC14为默认复用
	AFIO_GPxConfig(GPIO_PC,AFIO_PIN_15,AFIO_MODE_DEFAULT);
	
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_14,GPIO_DIR_OUT);	//设置PC14方向：输出
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_15,GPIO_DIR_OUT);	//设置PC14方向：输出
	
	
}

void LED_Set(void)
{
	GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_14,SET);
}

void LED_Reset(void)
{
	GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_14,RESET);
}

