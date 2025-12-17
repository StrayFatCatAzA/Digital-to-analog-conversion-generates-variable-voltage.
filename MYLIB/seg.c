#include "seg.h"

/* 逻辑段码：bit0~bit7 -> a b c d e f g dp */
static const uint8_t seg_code[10] =
    {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x6F  // 9
};

static uint8_t seg_buf[4] = {0};
static uint8_t scan_index = 0;

static void SEG_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t on)
{
#if (SEG_TYPE == SEG_COMMON_ANODE)
    HAL_GPIO_WritePin(port, pin, on ? GPIO_PIN_RESET : GPIO_PIN_SET);
#else
    HAL_GPIO_WritePin(port, pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
#endif
}

static void SEG_SetSegment(uint8_t code)
{
    SEG_WritePin(SEG_A_PORT, SEG_A_PIN, code & 0x01);
    SEG_WritePin(SEG_B_PORT, SEG_B_PIN, code & 0x02);
    SEG_WritePin(SEG_C_PORT, SEG_C_PIN, code & 0x04);
    SEG_WritePin(SEG_D_PORT, SEG_D_PIN, code & 0x08);
    SEG_WritePin(SEG_E_PORT, SEG_E_PIN, code & 0x10);
    SEG_WritePin(SEG_F_PORT, SEG_F_PIN, code & 0x20);
    SEG_WritePin(SEG_G_PORT, SEG_G_PIN, code & 0x40);
    SEG_WritePin(SEG_DP_PORT, SEG_DP_PIN, code & 0x80);
}

static void SEG_AllOff(void)
{
    SEG_WritePin(SEG_DIG1_PORT, SEG_DIG1_PIN, 0);
    SEG_WritePin(SEG_DIG2_PORT, SEG_DIG2_PIN, 0);
    SEG_WritePin(SEG_DIG3_PORT, SEG_DIG3_PIN, 0);
    SEG_WritePin(SEG_DIG4_PORT, SEG_DIG4_PIN, 0);
}

static void SEG_Select(uint8_t i)
{
    SEG_AllOff();

    if (i == 0)
        SEG_WritePin(SEG_DIG1_PORT, SEG_DIG1_PIN, 1);
    if (i == 1)
        SEG_WritePin(SEG_DIG2_PORT, SEG_DIG2_PIN, 1);
    if (i == 2)
        SEG_WritePin(SEG_DIG3_PORT, SEG_DIG3_PIN, 1);
    if (i == 3)
        SEG_WritePin(SEG_DIG4_PORT, SEG_DIG4_PIN, 1);
}

void SEG_Scan(void)
{
    uint8_t code = seg_code[seg_buf[scan_index]];

    /* 小数点示例：显示 X.XX */
    if (scan_index == 1)
        code |= 0x80;

    SEG_SetSegment(code);
    SEG_Select(scan_index);

    scan_index = (scan_index + 1) % 4;
}

void SEG_DisplayNumber(uint16_t n)
{
    seg_buf[0] = n / 1000;
    seg_buf[1] = n / 100 % 10;
    seg_buf[2] = n / 10 % 10;
    seg_buf[3] = n % 10;
}

void SEG_DisplayFloat(float v)
{
    int x = (int)(v * 100);
    SEG_DisplayNumber(x);
}
