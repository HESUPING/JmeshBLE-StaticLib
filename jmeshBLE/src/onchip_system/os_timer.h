#ifndef OS_TIMER_H
#define OS_TIMER_H

#include"os_core.h"
#include"os_time.h"

typedef struct st_os_timer os_timer_t;

struct st_os_timer{
    os_time_t interval;
    os_time_t start;
};

void os_timer_set(os_timer_t* t,os_time_t interval_ms);
int os_timer_is_flow(os_timer_t* t);
void os_timer_reset(os_timer_t* t);
void os_timer_restart(os_timer_t* t);
void os_timer_trigger(os_timer_t* t);
os_time_t os_timer_remain(os_timer_t* t);
#endif // _OS_STIMER_H
