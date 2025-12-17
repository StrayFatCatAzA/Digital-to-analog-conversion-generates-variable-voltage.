#ifndef __SEG_H__
#define __SEG_H__

#include "stm32f1xx_hal.h"

/* ================= 用户配置区 ================= */

/* 数码管类型选择 */
#define SEG_COMMON_CATHODE 0    // 阴极
#define SEG_COMMON_ANODE 1      // 阳极

#define SEG_TYPE SEG_COMMON_ANODE // ← 改这里即可

/* 位选 GPIO（4 位） */
#define SEG_DIG1_PORT GPIOA
#define SEG_DIG1_PIN GPIO_PIN_8
#define SEG_DIG2_PORT GPIOA
#define SEG_DIG2_PIN GPIO_PIN_9
#define SEG_DIG3_PORT GPIOA
#define SEG_DIG3_PIN GPIO_PIN_10
#define SEG_DIG4_PORT GPIOA
#define SEG_DIG4_PIN GPIO_PIN_11

/* 段选 GPIO（a b c d e f g dp） */
#define SEG_A_PORT GPIOB
#define SEG_A_PIN GPIO_PIN_0
#define SEG_B_PORT GPIOB
#define SEG_B_PIN GPIO_PIN_1
#define SEG_C_PORT GPIOB
#define SEG_C_PIN GPIO_PIN_3
#define SEG_D_PORT GPIOB
#define SEG_D_PIN GPIO_PIN_4
#define SEG_E_PORT GPIOB
#define SEG_E_PIN GPIO_PIN_5
#define SEG_F_PORT GPIOB
#define SEG_F_PIN GPIO_PIN_6
#define SEG_G_PORT GPIOB
#define SEG_G_PIN GPIO_PIN_7
#define SEG_DP_PORT GPIOB
#define SEG_DP_PIN GPIO_PIN_8

/* ================= 接口函数 ================= */

void SEG_Init(void);
void SEG_Scan(void); // 1ms 调用
void SEG_DisplayNumber(uint16_t n);
void SEG_DisplayFloat(float val); // 如 3.30

#endif
