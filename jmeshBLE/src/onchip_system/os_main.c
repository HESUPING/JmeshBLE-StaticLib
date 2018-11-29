#include"os_core.h"
#include"os_time.h"
#include"os_timer_event.h"
#include"os_callback.h"
#include"../jmesh/jmesh_task.h"
#include"../driver/jmesh_system.h"
#include"../jmesh/jmesh_print.h"
extern void touch_test(void);
os_timer_event_t test_timer;
void test_timer_handler(void* argv)
{	
		os_timer_event_restart(&test_timer);
		static unsigned char on_off = 1;
		on_off ^= 1;
		jmesh_gpio_set(JMESH_LED1, on_off);
//		test_client_result(4,200);
}
void os_main(void)
{
    jmesh_system_timer_start(1000/OS_TICKS_FREQUENCY,os_time_interrupt);	
    os_init();
    os_task_start(&os_timer_event, NULL);
    os_task_start(&jmesh_task, NULL);
    os_start_callback();
    os_inited_callback();
//    os_timer_event_set(&test_timer, 1000, test_timer_handler, NULL);	
//		test_client_start(4,200,6,100,1,20);
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
