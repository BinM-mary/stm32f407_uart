#include "uart.h"

static uart_rx_callback_t uart_rx_callback;



static void uart_pin_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitTypeDef));

    // Configure GPIOA for UART TX (PA9) and RX (PA10)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Connect UART pins to AF
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
}

static void uart_lowlevel_init(void)
{
    USART_InitTypeDef USART_InitStruct;
    memset(&USART_InitStruct, 0, sizeof(USART_InitTypeDef));

    // Configure USART1
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    // Initialize USART1
    USART_Init(USART1, &USART_InitStruct);
    
    // Enable USART1
    USART_Cmd(USART1, ENABLE);
}

static void uart_irq_init(void)
{
    // Enable USART1 interrupt
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //接收中断
}

void uart_init(void)
{
    uart_pin_init();
    uart_lowlevel_init();
    uart_irq_init();
}

void uart_senddata(uint8_t data)
{
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //等待发送完成
}

void uart_receive_callback_register(uart_rx_callback_t callback)
{
    uart_rx_callback = callback;
}
