#include"os_timer_event.h"
#include"os_core.h"
#include"os_list.h"

static os_timer_event_t* timer_event_list=NULL;

static void os_timer_event_add(os_timer_event_t* event);

void os_timer_event_remove(os_timer_event_t* event);
OS_TASK(os_timer_event,event,data)
{
    OS_START();
    os_timer_event_t* e;
    os_time_t now;
    os_time_t expired_time;
    os_list_init((os_list_t)&timer_event_list);

    while(1){
        OS_YIELD();

        expired_time=OS_TIMER_EVENT_MAX_EXPIRED_TIME;
        now=os_time_ticks();

        for(e=timer_event_list;e!=NULL;e=e->next){
            if(os_timer_is_flow(&e->timer)){
                os_timer_event_remove(e);
                if(e->caller!=NULL)
                    e->caller(e->data);

            }
            else if(expired_time>e->timer.start+e->timer.interval-now){
                expired_time=e->timer.start+e->timer.interval-now;
            }
        }
        os_timer_event_schedule(expired_time);
    }
    OS_END();
}

void os_timer_event_set(os_timer_event_t* e,os_time_t interval_ms,os_timer_event_caller_t caller,os_data_t data)
{
    os_timer_set(&e->timer,interval_ms);
    e->caller=caller;
    e->data=data;

    os_timer_event_add(e);
}
static void os_timer_event_add(os_timer_event_t* event)
{
    os_timer_event_t* e;
    for(e=timer_event_list;e!=NULL;e=e->next){
        if(e==event){
            return;
        }
    }
    event->next=timer_event_list;
    timer_event_list=event;
    os_task_poll(&os_timer_event);
}

void os_timer_event_remove(os_timer_event_t* event)
{
    os_timer_event_t* e;
    if(event==timer_event_list){
        timer_event_list=event->next;
    }
    else{
        if(timer_event_list==NULL){
            return;
        }
        for(e=timer_event_list;e->next!=NULL;e=e->next){
            if(e->next==event){
                e->next=event->next;
                break;
            }
        }
    }
    os_task_poll(&os_timer_event);
}

void os_timer_event_reset(os_timer_event_t* e)
{
    os_timer_reset(&e->timer);
    os_timer_event_add(e);
}

void os_timer_event_restart(os_timer_event_t* e)
{
    os_timer_restart(&e->timer);
    os_timer_event_add(e);
}

void os_timer_event_triggger(os_timer_event_t* e)
{
    os_timer_trigger(&e->timer);
    os_task_poll(&os_timer_event);
}
int os_timer_event_is_active(os_timer_event_t* event)
{
    os_timer_event_t* e;
    for(e=timer_event_list;e!=NULL;e=e->next){
        if(e==event){
            return !os_timer_is_flow(&event->timer);
        }
    }
    return 0;
}
