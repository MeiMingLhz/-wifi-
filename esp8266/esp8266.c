#include "esp8266.h"

void ESP8266_SendData(u8* dat, u8* ack, u8 num, u8 waitTime)
{
	int i;
	for(i=0; i<((num)&0x3FFF); i++)
	{
		USART_SendData(HT_USART0,dat[i]);
		while(USART_GetFlagStatus(HT_USART0,USART_FLAG_TXC)==RESET);
	}
	
	if(ack&&waitTime)
	{
		while(--waitTime)
		{
			delay_ms(10);
			if(g_USART2_Rx_Sta&0x8000)
			{
				for(i=0; i<((g_USART2_Rx_Sta&0x3FFF)); i++)
				{
					USART_SendData(HT_USART1,g_USART2_receive_buffer[i]);
					while(USART_GetFlagStatus(HT_USART1,USART_FLAG_TXC)==RESET);
				}
				g_USART2_Rx_Sta=0;
				break;
			}
		}
	}
}



