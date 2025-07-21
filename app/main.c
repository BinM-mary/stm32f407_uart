#include "main.h"
#include "board.h"
#include "uart.h"

static volatile uint8_t uart_rx_buffer;

static void uart_rx_callback(uint8_t data)
{
	uart_senddata(data); // Echo the received data
}

int main(void)
{
	board_lowlevel_init();
	uart_init();
	uart_receive_callback_register(uart_rx_callback);
	while(1);
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
    {
        uart_rx_buffer = USART_ReceiveData(USART1);
        if(uart_rx_callback)
        {
            uart_rx_callback(uart_rx_buffer);
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE); //清除中断标志
    }
}