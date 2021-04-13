/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.3.30
	* @brief		USART驱动文件
**********************************************/

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "myUsart.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/

/*
	*USART1-->TX:PA4;RX:PA5
	*USART0-->TX:PA2;RX:PA3，此口用于与ESP8266通信
*/

void usart_init(void)
{
	USART_InitTypeDef USART_InitStructure = {0};
	CKCU_PeripClockConfig_TypeDef CKCUClk = {{0}};
	CKCUClk.Bit.AFIO = 1;
	CKCUClk.Bit.USART1 = 1;		//开启USART1时钟
	CKCUClk.Bit.USART0 = 1;
	CKCUClk.Bit.PA = 1;
	CKCU_PeripClockConfig(CKCUClk,ENABLE);
	
	GPIO_PullResistorConfig(HT_GPIOA,GPIO_PIN_5,GPIO_PR_UP);			//RX接一个上拉电阻
	GPIO_PullResistorConfig(HT_GPIOA,GPIO_PIN_3,GPIO_PR_UP);			//RX接一个上拉电阻
	
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_2,AFIO_MODE_6);
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_3,AFIO_MODE_6);
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_4,AFIO_MODE_6);								//设置PA4复用模式为AF6，即串口USR1_TX
	AFIO_GPxConfig(GPIO_PA,AFIO_PIN_5,AFIO_MODE_6);								//设置PA5复用模式为AF6，即串口USR1_RX
	
	USART_InitStructure.USART_BaudRate = 115200;									//波特率：115200
	USART_InitStructure.USART_Parity = USART_PARITY_NO;						//奇偶校验：无
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;						//模式：正常
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;				//停止位：1位
	USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;		//字长：8Bit 
	
	USART_Init(HT_USART1,&USART_InitStructure);
	USART_Init(HT_USART0,&USART_InitStructure);
	
	NVIC_EnableIRQ(USART0_IRQn);
	NVIC_EnableIRQ(USART1_IRQn);
	
	NVIC_SetPriority(USART1_IRQn,1);
	NVIC_SetPriority(USART0_IRQn,0);
	
	USART_IntConfig(HT_USART0,USART_INT_RXDR,ENABLE);							//接收区非空中断
	USART_IntConfig(HT_USART1,USART_INT_RXDR,ENABLE);
//	USART_IntConfig(HT_USART0,USART_INT_TXDE,ENABLE);
	
	USART_TxCmd(COM1_PORT,ENABLE);		//使能TX端口
	USART_RxCmd(COM1_PORT,ENABLE);		//使能RX端口
	
	USART_TxCmd(HT_USART0,ENABLE);
	USART_RxCmd(HT_USART0,ENABLE);
}

