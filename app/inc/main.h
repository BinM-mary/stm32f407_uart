#ifndef MAIN_H
#define MAIN_H

// Your code here
#include "stm32f4xx.h"
#include <stm32f4xx_conf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void mem_init(void);
void *mem_malloc(size_t size);
void mem_free(void *ptr);

#endif /* MAIN_H */
