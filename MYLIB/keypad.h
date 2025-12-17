#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "stm32f1xx_hal.h"



/* ========= 接口函数 ========= */
void Keypad_Init(void);
uint8_t Key_Scan(void);

#endif
