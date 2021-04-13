/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.3.30
	* @brief		USART�����ļ�
**********************************************/

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "myUsart.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/

/*
	*USART1-->TX:PA4;RX:PA5
	*USART0-->TX:PA2;RX:PA3���˿�������ESP8266ͨ��
*/

void usart_init(void)
{
	USART_InitTypeDef USART_InitStructure = {0};
	CKCU_PeripClockConfig_TypeDef CKCUClk = {{0}};
	CKCUClk.Bit.AFIO = 1;
	CKCUClk.Bit.USART1 = 1;		//����USART1ʱ��
	CKCUClk.Bit.USART0 = 1;
	CKCUClk.Bit.PA = 1;
	CKCU_PeripClockConfig(CKCUClk,ENABLE);
	
	GPIO_PullResistorConfig(HT_GPIOA,GPIO_PIN_5,GPIO_PR_UP);			//RX��һ����������
	GPIO_PullResistorConfig(HT_GPIOA,GPIO_PIN_3,GPIO_PR_UP);			//RX��һ����������
	
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_2,AFIO_MODE_6);
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_3,AFIO_MODE_6);
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_4,AFIO_MODE_6);								//����PA4����ģʽΪAF6��������USR1_TX
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_5,AFIO_MODE_6);								//����PA5����ģʽΪAF6��������USR1_RX
	
	USART_InitStructure.USART_BaudRate = 115200;									//�����ʣ�115200
	USART_InitStructure.USART_Parity = USART_PARITY_NO;						//��żУ�飺��
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;						//ģʽ������
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;				//ֹͣλ��1λ
	USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;		//�ֳ���8Bit 
	
	USART_Init(HT_USART1,&USART_InitStructure);
	USART_Init(HT_USART0,&USART_InitStructure);
	
	NVIC_EnableIRQ(USART0_IRQn);
	NVIC_EnableIRQ(USART1_IRQn);
	
	NVIC_SetPriority(USART1_IRQn,1);
	NVIC_SetPriority(USART0_IRQn,0);
	
	USART_IntConfig(HT_USART0,USART_INT_RXDR,ENABLE);							//�������ǿ��ж�
	USART_IntConfig(HT_USART1,USART_INT_RXDR,ENABLE);
//	USART_IntConfig(HT_USART0,USART_INT_TXDE,ENABLE);
	
	USART_TxCmd(COM1_PORT,ENABLE);		//ʹ��TX�˿�
	USART_RxCmd(COM1_PORT,ENABLE);		//ʹ��RX�˿�
	
	USART_TxCmd(HT_USART0,ENABLE);
	USART_RxCmd(HT_USART0,ENABLE);
}

