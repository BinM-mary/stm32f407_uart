#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "main.h"


void *malloc(size_t size)
{
    return mem_malloc(size);
}

void free(void* p)
{
    mem_free(p);
}
