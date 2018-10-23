#include"os_core.h"
#include"os_time.h"
#include"os_timer_event.h"
#include"os_callback.h"
#include"../jmesh/jmesh_task.h"
#include"../driver/jmesh_system.h"
#include"../jmesh/jmesh_print.h"
extern void touch_test(void);

void os_main(void)
{
    //os_start_callback();
    os_init();
    os_task_start(&os_timer_event, NULL);
    os_task_start(&jmesh_task, NULL);
    os_start_callback();
    os_inited_callback();
		//		touch_test();
    while(1){
        os_cycle_callback();
        os_do_poll();
        os_do_event();
    }
}
void os_start(void)
{
    jmesh_system_timer_start(1000/OS_TICKS_FREQUENCY,os_time_interrupt);
    jmesh_thread_start(os_main);
}
