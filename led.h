#ifndef LED_H
#define LED_H

#include "ht32f5xxxx_01.h"

/*
	*HT32F52352���Գ���LED
	*LED->PC14
*/

/*
	*��������LED_GPIO_Init
	*�����βΣ���
	*��������ֵ����
	*�������ܣ�����LEDģ���GPIO��ʼ����ʹ�ܽ����������
*/
void LED_GPIO_Init(void);


/*
	*��������LED_Set
	*�����βΣ���
	*��������ֵ����
	*�������ܣ�LED��������ߵ�ƽ
*/
void LED_Set(void);


/*
	*��������LED_Reset
	*�����βΣ���
	*��������ֵ����
	*�������ܣ�LED��������͵�ƽ
*/
void LED_Reset(void);


#endif //!LED_H


