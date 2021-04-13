/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.4.10
	* @brief		iic通信实现函数
**********************************************/
#ifndef IIC_H
#define IIC_H

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "ht32f5xxxx_01.h"
#include "delay.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/

#define IIC_PORT PC
#define IIC_HTPORT HT_GPIOC
#define IIC_AFPORT STRCAT2(GPIO_, IIC_PORT)

#define IIC_PIN_SCL GPIO_PIN_10
#define IIC_PIN_SDA GPIO_PIN_11

#define IIC_AFPIN_SCL AFIO_PIN_10
#define IIC_AFPIN_SDA AFIO_PIN_11

#define IIC_AFMODE AFIO_MODE_DEFAULT

#define IIC_SDA_OUT() GPIO_DirectionConfig(IIC_HTPORT,IIC_PIN_SDA,GPIO_DIR_OUT)
#define IIC_SDA_IN()	GPIO_DirectionConfig(IIC_HTPORT,IIC_PIN_SDA,GPIO_DIR_IN)

#define IIC_SDA_IN_ENABLE() GPIO_InputConfig(IIC_HTPORT,IIC_PIN_SDA,ENABLE)
#define IIC_SDA_IN_DISABLE() GPIO_InputConfig(IIC_HTPORT,IIC_PIN_SDA,DISABLE)

#define IIC_SDA_READ_BIT()	GPIO_ReadInBit(IIC_HTPORT,IIC_PIN_SDA)

#define IIC_SCL_0() GPIO_ClearOutBits(IIC_HTPORT,IIC_PIN_SCL)
#define IIC_SDA_0()	GPIO_ClearOutBits(IIC_HTPORT,IIC_PIN_SDA)

#define IIC_SCL_1() GPIO_SetOutBits(IIC_HTPORT,IIC_PIN_SCL)
#define IIC_SDA_1() GPIO_SetOutBits(IIC_HTPORT,IIC_PIN_SDA)

/**********************************************
	* @brief		iic init function
	* @param		None
	* @retval		None
**********************************************/
void my_iic_init(void);

/**********************************************
	* @brief		iic send start signal
	* @param		None
	* @retval		None
**********************************************/
void my_iic_start(void);

/**********************************************
	* @brief		iic send stop signal
	* @param		None
	* @retval		None
**********************************************/
void my_iic_stop(void);

/**********************************************
	* @brief		iic send ack signal
	* @param		None
	* @retval		None
**********************************************/
void my_iic_ack(void);

/**********************************************
	* @brief		iic send nack signal
	* @param		None
	* @retval		None
**********************************************/
void my_iic_nack(void);

/**********************************************
	* @brief		iic send a byte data
	* @param		txd, the data need to send
	* @retval		None
**********************************************/
void my_iic_send_byte(u8 txd);

/**********************************************
	* @brief		iic read a byte data
	* @param		needAck,if need an ack signal, 1
											else 0
	* @retval		receive data
**********************************************/
u8 my_iic_read_byte(u8 needAck);

#endif /* IIC_H */



