#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"


int cmd_mem(int argc, char *argv[])
{
    int size = atoi(argv[1]);
    uint8_t* p =  malloc(size);
    shellPrint(shellGetCurrent(), "Allocated %d bytes at 0x%p\n", size, p);
    free(p);
    return 0;
}
