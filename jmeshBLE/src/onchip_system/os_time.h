#ifndef OS_TIME_H
#define OS_TIME_H

#include"os_core.h"
typedef unsigned long os_time_t;

/*
    this function must be called with OS_TICKS_FREQUENCY in timer interrupter
*/
void os_time_interrupt(void);

os_time_t os_time_ticks(void);
os_time_t os_time_ticks_to_ms(os_time_t time);
os_time_t os_time_ms_to_ticks(os_time_t time);
void os_time_wait(os_time_t i);
void os_time_set_seconds(unsigned long sec);
unsigned long os_time_get_seconds(void);



#endif // OS_TIME_H
