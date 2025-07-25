#include "main.h"
#include "board.h"
#include "uart.h"
#include "shell.h"
#include "ringbuffer8.h"
//#define LOG_TAG    "main"
#include "elog.h"

static uint8_t uart_buffer[128]; // 环形缓冲区
static ringbuffer8_t uart_rx_buffer = NULL;
static Shell shell;
static char shellBuffer[512];

static signed short _shell_write(char *data, unsigned short len)
{
	for (unsigned short i = 0; i < len; i++)
	{
		uart_senddata(data[i]);
	}
	return len;
}

// 回调函数，如果环形缓冲区没满的话，将数据存入
static void usart_receive(uint8_t data)
{
	if (uart_rx_buffer && !rb8_full(uart_rx_buffer))
	{
		rb8_put(uart_rx_buffer, data);
	}
}

int main(void)
{
	mem_init();

	board_lowlevel_init();
	elog_init();
	
	uart_receive_callback_register(usart_receive);

	uart_rx_buffer = rb8_new(uart_buffer, sizeof(uart_buffer)); // 创建环形缓冲区

	shell.write = _shell_write;

	shellInit(&shell, shellBuffer, sizeof(shellBuffer));
	elog_start();
	
	uint8_t data;
	while (1)
	{
		//日志
		
		if (!rb8_empty(uart_rx_buffer)) // 若非空
		{
			if (rb8_get(uart_rx_buffer, &data)) // 读入数据
			{
				log_a("Hello EasyLogger!\r\n");
				shellHandler(&shell, data);
			}
		}
	}
}

