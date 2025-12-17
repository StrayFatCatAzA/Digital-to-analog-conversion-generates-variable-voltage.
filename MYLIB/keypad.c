#include "keypad.h"
#include "main.h"

#define KEYPAD_ROW_NUM  4
#define KEYPAD_COL_NUM  4

static GPIO_TypeDef *KEY_ROWs_PROT[KEYPAD_ROW_NUM] = {KEY_ROW1_OUT_GPIO_Port, KEY_ROW2_OUT_GPIO_Port,
                                         KEY_ROW3_OUT_GPIO_Port, KEY_ROW4_OUT_GPIO_Port};

static uint8_t KEY_ROWs_PIN[KEYPAD_ROW_NUM] = {KEY_ROW1_OUT_Pin, KEY_ROW2_OUT_Pin,
                                  KEY_ROW3_OUT_Pin, KEY_ROW4_OUT_Pin};

static GPIO_TypeDef *KEY_COLs_PROT[KEYPAD_COL_NUM] = {KEY_COL1_IN_GPIO_Port, KEY_COL2_IN_GPIO_Port,
                                         KEY_COL3_IN_GPIO_Port, KEY_COL4_IN_GPIO_Port};

static uint8_t KEY_COLs_PIN[KEYPAD_COL_NUM] = {KEY_COL1_IN_Pin, KEY_COL2_IN_Pin,
                                  KEY_COL3_IN_Pin, KEY_COL4_IN_Pin};

/**
 * @brief  键盘初始化
 * @note   GPIO 初始化应由 MX_GPIO_Init() 完成
 */
void Keypad_Init(void)
{
    uint8_t i;

    /* 行默认拉高 */
    for (i = 0; i < KEYPAD_ROW_NUM; i++)
    {
        HAL_GPIO_WritePin(KEY_ROWs_PROT[i],
                          KEY_ROWs_PIN[i],
                          GPIO_PIN_SET);
    }
}

/**
 * @brief  扫描 4x4 矩阵键盘
 * @retval 0: 无按键
 *         1~16: 按键编号
 *
 * 编号规则：
 *  11   12   13   14
 *  21   22   23   24
 *  31   32   33   34
 *  41   42   43   44
 */
uint8_t Key_Scan(void)
{

    uint8_t key[KEYPAD_ROW_NUM][KEYPAD_COL_NUM] = {0};
    uint8_t Answer = 0;

    int i, j;
    for (i = 0; i < KEYPAD_ROW_NUM; i++)
    {
        // 行扫描 拉低该行电平
        HAL_GPIO_WritePin(KEY_ROWs_PROT[i], KEY_ROWs_PIN[i], GPIO_PIN_RESET);
        for (j = 0; j < KEYPAD_COL_NUM; j++)
        {
            HAL_Delay(10);
            if (HAL_GPIO_ReadPin(KEY_COLs_PROT[j], KEY_COLs_PIN[j]) == GPIO_PIN_RESET)
            {
                key[i][j] = 1;
            }
            else
            {
                key[i][j] = 0;
            }
        }
        // 扫描结束 拉高行电平
        HAL_GPIO_WritePin(KEY_ROWs_PROT[i], KEY_ROWs_PIN[i], GPIO_PIN_SET);
    }

    for (i = 0; i < KEYPAD_ROW_NUM; i++)
    {
        for (j = 0; j < KEYPAD_COL_NUM; j++)
        {
            if (key[i][j] == 1)
                Answer = ((i + 1) * 10) + (j + 1);
        }
    }
    return Answer;
}
