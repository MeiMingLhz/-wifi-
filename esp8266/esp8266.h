/**********************************************
	* @author		
	* @version	
	* @data			
	* @brief		
**********************************************/
#ifndef ESP8266_H
#define ESP8266_H

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "ht32f5xxxx_01.h"
#include "delay.h"
#include "g_val.h"
#include <string.h>
/* </Includes> ------------------------------------------------------------------------------------------------*/

u8 ESP8266_SendData(u8* dat, u8* ack, u8 num, u16 waitTime);

u8* ESP8266_check_cmd(u8* cmd);

void ESP8266_init(void);

u8 ESP8266_quit_trans(void);

#endif /* ESP8266_H */



