#include "g_val.h"

vu32 g_delayCount = 0;

u8 g_Tx_Buffer[128];
u8 g_USART1_receive_buffer[128];
u8 g_USART2_receive_buffer[256];
u16 g_USART1_Rx_Sta=0;
u16 g_USART2_Rx_Sta=0;

bool gIsTxFinished = FALSE;

uc8  *gURTx_Ptr;
vu32 gURTx_Length = 0;
u8  *gURRx_Ptr;
vu32 gURRx_Length = 0;


