/**********************************************
	* @author		MzMyLhz
	* @version	v1
	* @data			2021.3.28
	* @brief		BFTMÇý¶¯ÎÄ¼þ
**********************************************/

/* <Includes> ------------------------------------------------------------------------------------------------*/
#include "bftm.h"
/* </Includes> ------------------------------------------------------------------------------------------------*/


void BFTM_Init(void)
{
	NVIC_EnableIRQ(BFTM0_IRQn);
	
	BFTM_SetCompare(HT_BFTM0,SystemCoreClock/200);
	BFTM_SetCounter(HT_BFTM0,0);
	
	BFTM_IntConfig(HT_BFTM0,ENABLE);
	BFTM_EnaCmd(HT_BFTM0,DISABLE);
}

