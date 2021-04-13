#ifndef LED_H
#define LED_H

#include "ht32f5xxxx_01.h"

/*
	*HT32F52352测试程序：LED
	*LED->PC14
*/

/*
	*函数名：LED_GPIO_Init
	*函数形参：无
	*函数返回值：无
	*函数功能：进行LED模块的GPIO初始化，使管脚能正常输出
*/
void LED_GPIO_Init(void);


/*
	*函数名：LED_Set
	*函数形参：无
	*函数返回值：无
	*函数功能：LED引脚输出高电平
*/
void LED_Set(void);


/*
	*函数名：LED_Reset
	*函数形参：无
	*函数返回值：无
	*函数功能：LED引脚输出低电平
*/
void LED_Reset(void);


#endif //!LED_H


