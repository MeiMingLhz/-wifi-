/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.3.27
	* @brief		全局变量头文件
**********************************************/
#ifndef G_VAL_H
#define G_VAL_H

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32f5xxxx_01.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/

/* <Global variables> -----------------------------------------------------------------------------------------*/
extern vu32 g_delayCount;

extern u8 g_Tx_Buffer[128];
extern u8 g_USART1_receive_buffer[128];
extern u16 g_USART1_Rx_Sta;
extern u16 g_USART2_Rx_Sta;
extern u8 g_USART2_receive_buffer[256];

extern bool gIsTxFinished;

extern uc8  *gURTx_Ptr;
extern vu32 gURTx_Length;
extern u8  *gURRx_Ptr;
extern vu32 gURRx_Length;
/* </Global variables> ----------------------------------------------------------------------------------------*/

#endif //! G_VAL_H

