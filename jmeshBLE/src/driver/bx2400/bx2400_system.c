#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"osapp_config.h"
#include"../jmesh_system.h"
#include"stdio.h"
#include "log.h"

void jmesh_mutex_lock(void)
{

}
void jmesh_mutex_unlock(void)
{

}
void jmesh_system_timer_start(unsigned short interval_ms,void(*handler)(void))
{
    void *jmesh_system_timer;

    jmesh_system_timer=xTimerCreate("Jmesh System Timer",interval_ms/portTICK_RATE_MS,pdTRUE,(void *)0,(TimerCallbackFunction_t)handler);

    if(NULL==jmesh_system_timer)
    {
        LOG(LOG_LVL_INFO,"\njmesh system timer start fail!!!\n");
        return;
    }
    else
    {
        LOG(LOG_LVL_INFO,"\njmesh system timer start success\n");
    }
    xTimerStart(jmesh_system_timer,0);
}
void jmesh_thread_start(void(*handler)(void)){
    xTaskCreate((TaskFunction_t)handler,"Jmesh Thread",1600,NULL,4,NULL);
}


void jmesh_random_init(int seed)
{
//    srand(seed);
}
int jmesh_random_get(int min,int max){
    int r;
    if(min>=max){
        return min;
    }
    r=rand();
    r=min+r%(max-min);
    return r;
}
#endif

