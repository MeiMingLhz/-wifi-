/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.4.11
	* @brief		mpu6050驱动文件
**********************************************/
#include "mpu6050.h"

u8 MPU6050_init(void)
{
	u8 res;
	my_iic_init();
	
	//1.设置PWR_MGMT_1寄存器的DEVICE_RESET位为1，复位MPU6050
	MPU6050_write_byte(MPU_PWR_MGMT1_REG,0x80);	
	delay_ms(200);
	
	//2.由于复位后SLEEP位为1，表示在睡眠，故需要清零。DEVICE_RESET会被硬件清零，不用管
	MPU6050_write_byte(MPU_PWR_MGMT1_REG,0x00);
	
	//3.设置加速度传感器满量程范围，±2g
	MPU6050_set_afs(MPU_ACERL_2G);
	
	MPU6050_write_byte(MPU_SAMPLE_RATE_REG,((1000/50)-1));	//设置采样率为50
	MPU6050_write_byte(MPU_CFG_REG,4);		//数字低通滤波器频率为采样频率的一半
	
	//4.一些其他的关闭操作
	MPU6050_write_byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU6050_write_byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU6050_write_byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU6050_write_byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	
	//5.读取设备ID
	res = MPU6050_read_byte(MPU_DEVICE_ID_REG);
	printf("res = %x\r\n",res);
	
	if(res==MPU6050_ADDRESS)
	{
		MPU6050_write_byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU6050_write_byte(MPU_PWR_MGMT2_REG,0X07);	//仅让加速度计工作，陀螺仪不工作
		MPU6050_write_byte(MPU_SAMPLE_RATE_REG,((1000/50)-1));	//设置采样率为50
	}
	else
	{
		return MPU6050_INIT_ERROR;
	}
	
	return MPU6050_INIT_SUCCESS;
	
}

u8 MPU6050_write_byte(u8 regAddr, u8 txd)
{	
	//1.发送起始信号
	my_iic_start();
	
	//2.发送7位地址+R/W位
	my_iic_send_byte((MPU6050_ADDRESS<<1)|0);	//第8位为0，表示写指令
	
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		my_iic_stop();
		return MPU6050_NO_ACK;
	}
	
	//到这里说明芯片有回应了，接下来要干的就是发送RA（寄存器地址）
	my_iic_send_byte(regAddr);
	MPU6050_wait_ack();
	
	//接下来是发送DATA	
	my_iic_send_byte(txd);
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		//表示没有收到正确的应答信号，给主程序返回一个错误代码
		my_iic_stop();
		return MPU6050_NO_ACK;
	}
	my_iic_stop();
	return MPU6050_ACK_OK;
}

u8 MPU6050_read_byte(u8 regAddr)
{
	u8 receive;
	//1.发送S信号
	my_iic_start();
		
	//2.发送AD+W（因为要先写入要访问的地址，所以先发送W指令）
	my_iic_send_byte((MPU6050_ADDRESS<<1)|0);	//AD+W
	
	//3.等待回应
	MPU6050_wait_ack();
	
	//4.发送RA
	my_iic_send_byte(regAddr);
	MPU6050_wait_ack();
	
	//5.发送S信号
	my_iic_start();
	
	//6.发送AD+R信号
	my_iic_send_byte((MPU6050_ADDRESS<<1)|1);
	MPU6050_wait_ack();
	
	//7.读数据并发送NACK
	receive = my_iic_read_byte(0);
	
	//8.发送S信号
	my_iic_stop();
	
	return receive;
}

u8 MPU6050_read_byte_cont(u8 regAddr, u8 read_length, u8 *buffer)
{
	u8 receive;
	//1.发送S信号
	my_iic_start();
		
	//2.发送AD+W（因为要先写入要访问的地址，所以先发送W指令）
	my_iic_send_byte((MPU6050_ADDRESS<<1)|0);	//AD+W
	
	//3.等待回应
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		printf("发送AD+W后无回信！\r\n");
		return 0;
	}
	
	//4.发送RA
	my_iic_send_byte(regAddr);
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		printf("发送RA后无回信！\r\n");
		return 0;
	}
	
	
	//5.发送S信号
	my_iic_start();
	
	//6.发送AD+R信号
	my_iic_send_byte((MPU6050_ADDRESS<<1)|1);
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		printf("发送AD+R后无回信！\r\n");
		return 0;
	}
	
	
	//7.循环读取，最后一个数据发送nack，其他的发送ack
	while(read_length)
	{
		if(read_length==1)
		{
			*buffer = my_iic_read_byte(0);
		}
		else
		{
			*buffer = my_iic_read_byte(1);
		}
		read_length--;
		buffer++;
	}
	
	//8.发送S信号
	my_iic_stop();
	
	return 0;
}

u8 MPU6050_get_accelerometer(short *ax, short *ay, short *az)
{
	u8 buf[6], res;
	res = MPU6050_read_byte_cont(MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		//成功读取到数据
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
		return 0;
	}
	else
	{
		printf("无法读回加速度数据！\r\n");
		return 1;
	}
	
}

u8 MPU6050_set_afs(u8 fsr)
{
	return(MPU6050_write_byte(MPU_ACCEL_CFG_REG,fsr<<3));
}


u8 MPU6050_wait_ack(void)
{
	u8 waitCnt=0;
	IIC_SDA_IN();
	IIC_SDA_IN_ENABLE();
	IIC_SDA_1();
	delay_us(2);
	
	IIC_SCL_1();
	delay_us(2);
	
	while(IIC_SDA_READ_BIT())
	{
		//如果发生应答，在SCL为1的情况下，SDA应该被从机拉到低
		//这里不断读取SDA的值，并且累加，如果超过某个值就说明模块应该是寄了
		waitCnt++;
		if(waitCnt>250)
		{
			my_iic_stop();	//本次通信结束，停止
			printf("MPU6050 no success\r\n");
			return MPU6050_NO_ACK;
		}
	}
	//到这里说明有回应了，时钟拉低，表示成功收到回复，准备下面的时序
	IIC_SCL_0();
	return MPU6050_ACK_OK;
}


