#include "clk_conf.h"

void CLK_Config(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClk = {{0}};	//建立空的时钟控制结构体变量
	CKCUClk.Bit.PC = 1;			//初始化PC的时钟
	CKCUClk.Bit.AFIO = 1;		//开启AFIO复用
	CKCUClk.Bit.BFTM0=1;
	CKCU_PeripClockConfig(CKCUClk,ENABLE);	//时钟使能
}



