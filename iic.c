/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.4.10
	* @brief		iic驱动实现函数
**********************************************/

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "iic.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/

/*
	*tips:
	*	SCL->PC10
	*	SDA->PC11
*/

void my_iic_init(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUInit = {{0}};
	CKCUInit.Bit.IIC_PORT=1;
	CKCUInit.Bit.AFIO=1;
	CKCU_PeripClockConfig(CKCUInit,ENABLE);
	
	AFIO_GPxConfig(IIC_AFPORT,IIC_AFPIN_SCL|IIC_AFPIN_SDA,IIC_AFMODE);
	
	GPIO_PullResistorConfig(IIC_HTPORT,IIC_PIN_SCL|IIC_PIN_SDA,GPIO_PR_DISABLE);
	GPIO_DriveConfig(IIC_HTPORT,IIC_PIN_SCL|IIC_PIN_SDA,GPIO_DV_8MA);
	GPIO_DirectionConfig(IIC_HTPORT,IIC_PIN_SCL|IIC_PIN_SDA,GPIO_DIR_OUT);
	
	GPIO_SetOutBits(IIC_HTPORT,IIC_PIN_SCL|IIC_PIN_SDA);
}

void my_iic_stop(void)
{
	IIC_SDA_OUT();
	IIC_SDA_0();
	IIC_SCL_0();
	
	delay_us(3);
	IIC_SDA_0();
	IIC_SCL_1();
	delay_us(3);
}

void my_iic_start(void)
{
	IIC_SDA_IN_DISABLE();
	IIC_SDA_OUT();
	IIC_SDA_1();
	IIC_SCL_1();
	delay_us(2);
	
	IIC_SDA_0();
	delay_us(2);
	
	IIC_SCL_0();
}

void my_iic_ack(void)
{
	IIC_SCL_0();
	IIC_SDA_IN_DISABLE();
	IIC_SDA_OUT();
	IIC_SDA_0();
	delay_us(2);
	
	IIC_SCL_1();
	delay_us(2);
	
	IIC_SCL_0();
}

void my_iic_nack(void)
{
	IIC_SCL_0();
	IIC_SDA_OUT();
	IIC_SDA_1();
	delay_us(2);
	
	IIC_SCL_1();
	delay_us(2);
	
	IIC_SCL_0();
}

void my_iic_send_byte(u8 txd)
{
	u8 i;
	IIC_SDA_IN_DISABLE();
	IIC_SDA_OUT();
	IIC_SCL_0();
	for(i=0; i<8; i++)
	{
		//高位优先
		if(txd&0x80)
		{
			//高位为1，数据线输出1
			IIC_SDA_1();
		}
		else
		{
			IIC_SDA_0();
		}
		txd<<=1;
		{
			//发送完一位，时钟跳变一次
			IIC_SCL_1();
			delay_us(2);
			IIC_SCL_0();
			delay_us(2);
		}
	}
}

u8 my_iic_read_byte(u8 needAck)
{
	u8 i, receive=0;
	IIC_SDA_IN();
	IIC_SDA_IN_ENABLE();
	
	for(i=0; i<8; i++)
	{
		IIC_SCL_0();
		delay_us(2);
		
		IIC_SCL_1();
		delay_us(2);
		
		receive<<=1;
		if(IIC_SDA_READ_BIT())	//收到1
		{
			receive++;
		}

		delay_us(2);
	}
	
	if(!needAck)
	{
		my_iic_nack();
	}
	else
	{
		my_iic_ack();
	}
	return receive;
}


