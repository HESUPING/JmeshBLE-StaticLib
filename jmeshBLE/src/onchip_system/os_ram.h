#ifndef OS_RAM_H
#define OS_RAM_H
#include"stdio.h"

#define OS_RAM_SIZE 100
#if(OS_RAM_SIZE>0xffff)
    #error OS_RAM_SIZE!>0xffff
#endif

void os_ram_init(void);
void os_ram_free(void* ptr);
void* os_ram_malloc(unsigned short size);

#endif // OS_MALLOC_H
