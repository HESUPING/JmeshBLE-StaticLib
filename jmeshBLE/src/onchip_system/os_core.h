#ifndef OS_CORE_H
#define OS_CORE_H
#include"stdio.h"
#include"stdarg.h"

typedef struct st_os_pt os_pt_t;
typedef const void* os_data_t;
typedef unsigned char os_event_t;
typedef struct st_os_event_data os_event_data_t;
typedef struct st_os_task os_task_t;
typedef int(*os_app_t)(os_pt_t* pt,os_event_t,os_data_t);

#define RAM_ALIGN_OCTECTS 4

#define OS_EVENT_SIZE  32

#define OS_TICKS_FREQUENCY 50

#define OS_WAITING 0
#define OS_YIELDED 1
#define OS_EXITED  2

#define OS_TASK_STATE_NONE        0
#define OS_TASK_STATE_HOLD        1
#define OS_TASK_STATE_IDLE        2
#define OS_TASK_STATE_ACTIVE      3

#ifndef NULL
#define NULL 0
#endif

#define OS_EVENT_NONE            0xf0
#define OS_EVENT_INIT            0xf1
#define OS_EVENT_POLL            0xf2
#define OS_EVENT_EXIT            0xf3
#define OS_EVENT_TIMER           0xf4

#define OS_ERR_OK                0
#define OS_ERR_EVENT_FULL        -1
#define OS_ERR_CALLER_FULL       -2

#define OS_PT_INIT(pt) (pt)->lc=0

#define OS_TASK_NAME(name) extern os_task_t name
#define OS_THREAD(name_args) int name_args

#define OS_TASK(name,event,data)                                                 \
    OS_THREAD(os_task_##name(os_pt_t* _pt,os_event_t event,os_data_t data));   \
    os_task_t name={NULL,os_task_##name};                                        \
    OS_THREAD(os_task_##name(os_pt_t* _pt,os_event_t event,os_data_t data))

#define OS_START()              PT_START(_pt)
#define OS_YIELD()              PT_YIELD(_pt)
#define OS_YIELD_UNTIL(cond)    PT_YIELD_UNTIL(_pt,cond)
#define OS_WAIT_UNTIL(cond)     PT_WAIT_UNTIL(_pt,cond)
#define OS_WAIT_WHILE(cond)     PT_WAIT_WHILE(_pt,cond)
#define OS_WAIT_THREAD(thread)  PT_WAIT_THREAD(_pt,thread)
#define OS_RESTART()            PT_RESTART(_pt)
#define OS_EXIT()               PT_EXIT(_pt)
#define OS_END()                PT_END(_pt)

#define PT_START(pt) {char os_yield_flag=1;if(os_yield_flag==1);switch((pt)->lc){case 0:

#define PT_YIELD(pt)                            \
    do{                                         \
        os_yield_flag=0;                        \
        (pt)->lc=__LINE__;case(__LINE__):       \
        if(os_yield_flag==0){                   \
            return OS_YIELDED;                  \
        }                                       \
    }while(0)

#define PT_YIELD_UNTIL(pt,cond)                 \
    do {                                        \
        os_yield_flag = 0;				        \
        (pt)->lc=__LINE__;case(__LINE__):       \
        if((os_yield_flag == 0) || !(cond)) {   \
            return OS_YIELDED;                  \
        }                                       \
    }while(0)


#define PT_WAIT_UNTIL(pt,cond)                  \
    do{                                         \
        (pt)->lc=__LINE__;case __LINE__:        \
        if(!(cond))                             \
            return OS_YIELDED;                  \
    }while(0);

#define PT_WAIT_WHILE(pt,cond)  PT_WAIT_UNTIL(pt,!(cond))

#define PT_WAIT_THREAD(pt,thread) PT_WAIT_WHILE(pt, ((thread)<OS_EXITED))

#define PT_RESTART(pt)                          \
    do{                                         \
        (pt)->lc=0;                             \
        return OS_WAITING;                      \
    }while(0)

#define PT_EXIT(pt)                             \
    do{                                         \
        (pt)->lc=0;                             \
        return OS_EXITED;                       \
    }while(0)

#define PT_END(pt) }(pt)->lc=0;os_yield_flag=0;return OS_EXITED;}


typedef int(*os_event_handler_t)(os_data_t data);


struct st_os_pt{
    unsigned short lc;
};
struct st_os_task{
    os_task_t* next;
    os_app_t app;
    os_pt_t pt;
    unsigned char state;
    unsigned char poll_flag;
};
struct st_os_event_data{
  os_event_t event;
  os_data_t data;
  os_task_t *t;
};

void os_init(void);
void os_task_start(os_task_t* task,os_data_t data);
void os_task_exit(os_task_t* task);

void os_task_poll(os_task_t* t);

void os_do_poll(void);
void os_do_event(void);

int os_event_post(os_task_t* task,os_event_t event,os_data_t data);
os_event_t os_event_alloc(void);

extern os_task_t *os_task_list;
extern os_task_t *os_task_current;

#endif // MESH_SYS_H

