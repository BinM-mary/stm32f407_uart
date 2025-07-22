#include "main.h"
#include "board.h"
#include "uart.h"
#include "shell.h"

static volatile uint8_t uart_rx_buffer;
static Shell shell;
static char shellBuffer[512];

static signed short _shell_read(char *data, unsigned short len)
{
	if(uart_rx_buffer)
	{
		*data = uart_rx_buffer;
		uart_rx_buffer = 0;
		return 1;
	}
	return 0;
}

static signed short _shell_write(char *data, unsigned short len)
{
	for(unsigned short i = 0; i < len; i++)
	{
		uart_senddata(data[i]);
	}
	return len;
}

static void usart_receive(uint8_t data)
{
	uart_rx_buffer = data; // Store received data
}

int main(void)
{
	board_lowlevel_init();
	uart_init();
	uart_receive_callback_register(usart_receive);

	shell.read = _shell_read;
	shell.write = _shell_write;
	shellInit(&shell, shellBuffer, sizeof(shellBuffer));
	while(1)
	{
		shellTask(&shell);
	}
}
