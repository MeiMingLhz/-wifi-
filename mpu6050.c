/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.4.11
	* @brief		mpu6050�����ļ�
**********************************************/
#include "mpu6050.h"

u8 MPU6050_init(void)
{
	u8 res;
	my_iic_init();
	
	//1.����PWR_MGMT_1�Ĵ�����DEVICE_RESETλΪ1����λMPU6050
	MPU6050_write_byte(MPU_PWR_MGMT1_REG,0x80);	
	delay_ms(200);
	
	//2.���ڸ�λ��SLEEPλΪ1����ʾ��˯�ߣ�����Ҫ���㡣DEVICE_RESET�ᱻӲ�����㣬���ù�
	MPU6050_write_byte(MPU_PWR_MGMT1_REG,0x00);
	
	//3.���ü��ٶȴ����������̷�Χ����2g
	MPU6050_set_afs(MPU_ACERL_2G);
	
	MPU6050_write_byte(MPU_SAMPLE_RATE_REG,((1000/50)-1));	//���ò�����Ϊ50
	MPU6050_write_byte(MPU_CFG_REG,4);		//���ֵ�ͨ�˲���Ƶ��Ϊ����Ƶ�ʵ�һ��
	
	//4.һЩ�����Ĺرղ���
	MPU6050_write_byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU6050_write_byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU6050_write_byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU6050_write_byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	
	//5.��ȡ�豸ID
	res = MPU6050_read_byte(MPU_DEVICE_ID_REG);
	printf("res = %x\r\n",res);
	
	if(res==MPU6050_ADDRESS)
	{
		MPU6050_write_byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU6050_write_byte(MPU_PWR_MGMT2_REG,0X07);	//���ü��ٶȼƹ����������ǲ�����
		MPU6050_write_byte(MPU_SAMPLE_RATE_REG,((1000/50)-1));	//���ò�����Ϊ50
	}
	else
	{
		return MPU6050_INIT_ERROR;
	}
	
	return MPU6050_INIT_SUCCESS;
	
}

u8 MPU6050_write_byte(u8 regAddr, u8 txd)
{	
	//1.������ʼ�ź�
	my_iic_start();
	
	//2.����7λ��ַ+R/Wλ
	my_iic_send_byte((MPU6050_ADDRESS<<1)|0);	//��8λΪ0����ʾдָ��
	
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		my_iic_stop();
		return MPU6050_NO_ACK;
	}
	
	//������˵��оƬ�л�Ӧ�ˣ�������Ҫ�ɵľ��Ƿ���RA���Ĵ�����ַ��
	my_iic_send_byte(regAddr);
	MPU6050_wait_ack();
	
	//�������Ƿ���DATA	
	my_iic_send_byte(txd);
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		//��ʾû���յ���ȷ��Ӧ���źţ��������򷵻�һ���������
		my_iic_stop();
		return MPU6050_NO_ACK;
	}
	my_iic_stop();
	return MPU6050_ACK_OK;
}

u8 MPU6050_read_byte(u8 regAddr)
{
	u8 receive;
	//1.����S�ź�
	my_iic_start();
		
	//2.����AD+W����ΪҪ��д��Ҫ���ʵĵ�ַ�������ȷ���Wָ�
	my_iic_send_byte((MPU6050_ADDRESS<<1)|0);	//AD+W
	
	//3.�ȴ���Ӧ
	MPU6050_wait_ack();
	
	//4.����RA
	my_iic_send_byte(regAddr);
	MPU6050_wait_ack();
	
	//5.����S�ź�
	my_iic_start();
	
	//6.����AD+R�ź�
	my_iic_send_byte((MPU6050_ADDRESS<<1)|1);
	MPU6050_wait_ack();
	
	//7.�����ݲ�����NACK
	receive = my_iic_read_byte(0);
	
	//8.����S�ź�
	my_iic_stop();
	
	return receive;
}

u8 MPU6050_read_byte_cont(u8 regAddr, u8 read_length, u8 *buffer)
{
	u8 receive;
	//1.����S�ź�
	my_iic_start();
		
	//2.����AD+W����ΪҪ��д��Ҫ���ʵĵ�ַ�������ȷ���Wָ�
	my_iic_send_byte((MPU6050_ADDRESS<<1)|0);	//AD+W
	
	//3.�ȴ���Ӧ
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		printf("����AD+W���޻��ţ�\r\n");
		return 0;
	}
	
	//4.����RA
	my_iic_send_byte(regAddr);
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		printf("����RA���޻��ţ�\r\n");
		return 0;
	}
	
	
	//5.����S�ź�
	my_iic_start();
	
	//6.����AD+R�ź�
	my_iic_send_byte((MPU6050_ADDRESS<<1)|1);
	if(MPU6050_wait_ack()==MPU6050_NO_ACK)
	{
		printf("����AD+R���޻��ţ�\r\n");
		return 0;
	}
	
	
	//7.ѭ����ȡ�����һ�����ݷ���nack�������ķ���ack
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
	
	//8.����S�ź�
	my_iic_stop();
	
	return 0;
}

u8 MPU6050_get_accelerometer(short *ax, short *ay, short *az)
{
	u8 buf[6], res;
	res = MPU6050_read_byte_cont(MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		//�ɹ���ȡ������
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
		return 0;
	}
	else
	{
		printf("�޷����ؼ��ٶ����ݣ�\r\n");
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
		//�������Ӧ����SCLΪ1������£�SDAӦ�ñ��ӻ�������
		//���ﲻ�϶�ȡSDA��ֵ�������ۼӣ��������ĳ��ֵ��˵��ģ��Ӧ���Ǽ���
		waitCnt++;
		if(waitCnt>250)
		{
			my_iic_stop();	//����ͨ�Ž�����ֹͣ
			printf("MPU6050 no success\r\n");
			return MPU6050_NO_ACK;
		}
	}
	//������˵���л�Ӧ�ˣ�ʱ�����ͣ���ʾ�ɹ��յ��ظ���׼�������ʱ��
	IIC_SCL_0();
	return MPU6050_ACK_OK;
}


