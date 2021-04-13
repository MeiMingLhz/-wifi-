#include "myDelay.h"

void Delay_Init(void)
{
	SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);			//设定systick的时钟源为STCLK = 8MHz/8 = 1MHz
	SYSTICK_SetReloadValue(SystemCoreClock/8/1000000);	//设定systick的重装填值，刚好计数1us
	SYSTICK_IntConfig(ENABLE);												//开启systick中断
}

void Delay_Us(vu32 delayTime)
{
	SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
	SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
	
	g_delayCount = delayTime;
	while(g_delayCount!=0);
	
	SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);
	SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
}

void Delay_Ms(vu32 delayTime)
{
	vu32 i;
	for(i=0;i<delayTime;i++)
	{
		Delay_Us(1000);
	}
}

void TimingDelay(void)
{
	if(g_delayCount!=0)
	{
		g_delayCount--;
	}
}

