#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include <stm32f4xx_conf.h>

typedef void (*uart_rx_callback_t)(uint8_t data);

void uart_init(void);
void uart_senddata(uint8_t data);
void uart_receive_callback_register(uart_rx_callback_t callback);
void usart_send_string(const char *str, uint16_t len);

#endif
