#include "board.h"
#include "stm32f4xx.h"
#include <stm32f4xx_conf.h>

void board_lowlevel_init(void)
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}