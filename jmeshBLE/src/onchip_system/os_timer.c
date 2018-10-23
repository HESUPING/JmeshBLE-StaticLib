#include"os_timer.h"


void os_timer_set(os_timer_t* t,os_time_t interval_ms)
{
    t->interval=os_time_ms_to_ticks(interval_ms);
    t->start=os_time_ticks();
}
int os_timer_is_flow(os_timer_t* t)
{
    return (os_time_ticks()-t->start)>t->interval;
}
void os_timer_reset(os_timer_t* t)
{
    t->start+=t->interval;
}
void os_timer_restart(os_timer_t* t)
{
    t->start=os_time_ticks();
}

void os_timer_trigger(os_timer_t* t)
{
    t->start=os_time_ticks()-t->interval;
}

