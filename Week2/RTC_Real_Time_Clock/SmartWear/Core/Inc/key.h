#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"
#include "gpio.h"

/* �궨��:��ȡ������Ӧ���Ŵ�ʱ�ĵ�ƽ״̬ */
#define KEY_UP  HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)  
#define KEY2    !(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin))

/* �����ֵ */
#define KEY_UP_PRES 1
#define KEY2_PRES   2

/* �������� */
uint8_t KEY_Scan(void);

#endif
