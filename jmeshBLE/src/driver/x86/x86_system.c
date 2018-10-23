#include"../jmesh_driver_config.h"
#if(JMESH_DRIVER_X86)

#include"../jmesh_system.h"
#include"stdio.h"
#include"windows.h"

void jmesh_mutex_lock()
{

}
void jmesh_mutex_unlock()
{

}
void jmesh_system_timer_start(unsigned short interval_ms,void(*handler)(void))
{
    static int i=1;
    SetTimer(NULL,i++,interval_ms,(TIMERPROC)handler);
}
void jmesh_thread_start(void(*handler)(void)){
    CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)handler,NULL,0,NULL);
}


void jmesh_random_init(int seed)
{
    srand(seed);
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

