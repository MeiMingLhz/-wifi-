#include "clk_conf.h"

void CLK_Config(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClk = {{0}};	//�����յ�ʱ�ӿ��ƽṹ�����
	CKCUClk.Bit.PC = 1;			//��ʼ��PC��ʱ��
	CKCUClk.Bit.AFIO = 1;		//����AFIO����
	CKCUClk.Bit.BFTM0=1;
	CKCU_PeripClockConfig(CKCUClk,ENABLE);	//ʱ��ʹ��
}



