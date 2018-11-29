#include"os_time.h"
#include"os_timer_event.h"


static volatile unsigned long seconds=0;
static volatile unsigned short millseconds=0;
static volatile os_time_t ticks = 0;
static os_time_t os_timer_event_expired_time;
/*
    this function must be called each OS_TICKS_MS in timer interrupter
*/
void os_time_interrupt(void)
{
    ticks++;

    if((ticks%OS_TICKS_FREQUENCY)==0){
        seconds++;
    }
    if(ticks==os_timer_event_expired_time){
        os_task_poll(&os_timer_event);
    }
}

void os_timer_event_schedule(os_time_t expired_time)
{
    if(expired_time<=1){
        os_timer_event_expired_time=os_time_ticks()+2;
    }
    else{
        os_timer_event_expired_time=os_time_ticks()+expired_time;
    }
}

os_time_t os_time_ticks(void)
{
    os_time_t t1, t2;

    do {
        t1 = ticks;
        t2 = ticks;
    } while(t1 != t2);

    return t1;
}

os_time_t os_time_ticks_to_ms(os_time_t ticks)
{
    return ticks*(1000/OS_TICKS_FREQUENCY);
}

os_time_t os_time_ms_to_ticks(os_time_t ms)
{
    return (ms*OS_TICKS_FREQUENCY+999)/1000;
}

void os_time_wait(os_time_t i)
{
    os_time_t start;

    start = os_time_ticks();
    while(os_time_ticks() - start < (os_time_t)i);
}

void os_time_set_seconds(unsigned long sec)
{
    do{
        seconds=sec;
    }while(seconds!=sec);
}
unsigned long os_time_get_seconds(void)
{
    unsigned long t1, t2;
    do {
        t1 = seconds;
        t2 = seconds;
    }while(t1 != t2);
  return t1;
}
