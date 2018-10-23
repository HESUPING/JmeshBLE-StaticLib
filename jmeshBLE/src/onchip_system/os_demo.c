#include"os_demo.h"
#include"os_ram.h"
#include"os_list.h"
#include"os_timer.h"
/*
OS_TASK_NAME(demo_simple);
OS_TASK_NAME(demo_event_send);
OS_TASK_NAME(demo_event_wait);

OS_TASK(demo_simple,event,data)
{
    OS_START();
    printf("simple demo start");
    while(1){
        OS_YIELD();
        printf("\nsimple demo:");
    }
    OS_END();
}
int test(){
return 0;
}
*/
/*

OS_TASK(demo_event_send,event,data){
    static os_timer_t t;
    OS_START();
    os_timer_set(&t,2000);
    printf("event_send demo start");
    while(1){
        OS_YIELD();
        OS_WAIT_UNTIL(event==OS_EVENT_TIMER||event==OS_EVENT_POLL);
        os_timer_reset(&t);
        os_event_post(&demo_event_wait,3,"hello world!");
        os_event_post(&demo_event_wait,4,"how are you!");
        os_event_post(&demo_event_wait,5,"goodbye!");
    }
    OS_END();
}
struct demo_wait_param{
    os_pt_t pt;
    int a;
    char* data;
};
void demo_caller(os_data_t data)
{
    ((struct demo_wait_param*)data)->a=5;
}
OS_THREAD(demo_thread_wait(struct demo_wait_param* param))
{



    static os_timer_t t;
    PT_START(&param->pt);
    os_timer_set(&t,1000,demo_caller,param);
    while(1){
        PT_YIELD_UNTIL(&param->pt,param->a==5);
        if(param->a>2){
            param->data="thread wait";
            PT_EXIT(&param->pt);
        }
    }
    PT_END(&param->pt);
}

OS_TASK(demo_event_wait,event,data){
    static struct demo_wait_param wait_param;
    OS_START();
    printf("event_wait demo start");
    while(1){
        OS_YIELD_UNTIL(event==3);
        printf("wait_event %d:%s",event,data);

        OS_YIELD_UNTIL(event==4);
        printf("wait_event %d:%s",event,data);

        OS_YIELD_UNTIL(event==5);
        printf("wait_event %d:%s",event,data);

        wait_param.a=0;
        OS_WAIT_THREAD(demo_thread_wait(&wait_param));
        printf("%s",wait_param.data);
    }
    OS_END();
}
#include"../foundation/composition.h"
#include"../app/vendor_model.h"
#include"../access/element.h"
#ifdef os_test

extern void publish_test(void);
int main(){
publish_test();

composition_test();
app_demo_test();
element_test();
    os_init();
    os_task_start(&os_timer,NULL);

    os_task_start(&demo_simple,NULL);
    os_task_start(&demo_event_send,NULL);
    os_task_start(&demo_event_wait,NULL);



    while(1){

        os_do_poll();
        os_do_event();

        Sleep(200);

     //   os_task_poll(&demo_simple);

        os_time_interrupt();

    }
}
#endif
*/

