#include "esp8266.h"

const u8* wifi_ssid = "wifi_405";
const u8* wifi_key = "keil.405";

const u8* connect_mode = "TCP";
const u8* connect_ip = "192.168.1.103";
const u8* connect_port = "8082";

void ESP8266_init(void)
{
	u8 waitCnt=0;
	u8* tmp;
	u8* tmp2;
	while(ESP8266_SendData("AT","OK",0,20))
	{
		//循环直到ESP8266有响应
		ESP8266_quit_trans();
		ESP8266_SendData("AT+CIPMODE=0","OK",200,200);	//判断是否有响应
		printf("没有检测到模块\r\n");
		printf("重新连接....\r\n");
		delay_ms(800);
	}
	
	printf("连接成功！\r\n");
	printf("设置模式...\r\n");
	
	if(!ESP8266_SendData("AT+CWMODE=3\r\n","OK",200,20))
	{
		printf("设置模式成功！\r\n");
	}
	
//	sprintf((char*)tmp,"AT+CWJAP=\"%s\",\"%s\"\r\n",wifi_ssid,wifi_key);
	while(ESP8266_SendData("AT+CWJAP=\"wifi_405\",\"keil.405\"\r\n","WIFI GOT IP",200,100))
	{
		waitCnt++;
		printf("正在连接wifi....\r\n");
		if(waitCnt>10)
		{
			printf("wifi连接失败！\r\n");
			return;
		}
	}
	
//	sprintf((char*)tmp2,"AT+CIPSTART=\"%s\",\"%s\",%s\r\n",connect_mode,connect_ip,connect_port);
	ESP8266_SendData("AT+CIPSTART=\"TCP\",\"192.168.1.103\",8082\r\n","OK",200,200);
	ESP8266_SendData("AT+CIPMODE=1\r\n","OK",20,20);
	ESP8266_SendData("AT+CIPSEND\r\n",">",20,20);
	
}

u8 ESP8266_SendData(u8* dat, u8* ack, u8 num, u16 waitTime)
{
	u8 ret=0;
	u16 i;
	g_USART2_Rx_Sta=0;
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
				if(ESP8266_check_cmd(ack))	//检查从8266发回来的内容中是否有想要的回应
				{
					printf("ack: %s\r\n",ack);
				}
				g_USART2_Rx_Sta=0;
				break;
			}
		}
		if(waitTime==0)
		{
			ret=1;	//返回1表示没有收到想要的回应
		}
	}
	return ret;
}


u8* ESP8266_check_cmd(u8* cmd)
{
	char *strx=NULL;
	if(g_USART2_Rx_Sta&0x8000)	//接收到数据
	{
		g_USART2_receive_buffer[g_USART2_Rx_Sta&0x7FFF]=0;	//添加结束符（？
		strx=strstr((const char*)g_USART2_receive_buffer,(const char*)cmd);
	}
	return (u8*)strx;
}

u8 ESP8266_quit_trans(void)
{
	while(USART_GetFlagStatus(HT_USART0,USART_FLAG_TXC)==0);
	USART_SendData(HT_USART0,'+');
	delay_ms(10);
	
	while(USART_GetFlagStatus(HT_USART0,USART_FLAG_TXC)==0);
	USART_SendData(HT_USART0,'+');
	delay_ms(10);
	
	while(USART_GetFlagStatus(HT_USART0,USART_FLAG_TXC)==0);
	USART_SendData(HT_USART0,'+');
	delay_ms(10);
	
	delay_ms(500);
	return ESP8266_SendData("AT","OK",0,20);	//退出透传成功，此句应返回非0值
}

