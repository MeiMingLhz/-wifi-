/**********************************************
	* @author		MzMyLhz
	* @version	
	* @data			
	* @brief		This is the file of Main function
**********************************************/


/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "ht32f5xxxx_01.h"
#include "delay.h"
#include "clk_conf.h"
#include "led.h"
#include "myUsart.h"
#include "delay.h"
#include "bftm.h"
#include "mpu6050.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/



/*

*/

/* <Private function prototype> -------------------------------------------------------------------------------*/

/* </Private function prototype> ------------------------------------------------------------------------------*/

/* <Global variables> -----------------------------------------------------------------------------------------*/


/* </Global variables> ----------------------------------------------------------------------------------------*/

/* <Global functions> -----------------------------------------------------------------------------------------*/
/**********************************************
	* @brief		Main function
	* @param		None
	* @retval		None
**********************************************/

int main(void)
{
	short ax, ay, az;
	u16 cnt = 0;
	usart_init();
	CLK_Config();
	LED_GPIO_Init();
	printf("init  success!\r\n");
	
	if(MPU6050_init()==MPU6050_INIT_SUCCESS)
	{
		printf("MPU6050 init success!\r\n");
	}
	else
	{
		printf("MPU6050 init error!\r\n");
	}

	while(1)
	{
		if(MPU6050_get_accelerometer(&ax,&ay,&az)==0)
		{
			printf("%f %f %f\r\n",ax/16384.0,ay/16384.0,az/16384.0);
		}
		
	}
	
	return 0;
}

/* </Global functions> ----------------------------------------------------------------------------------------*/


