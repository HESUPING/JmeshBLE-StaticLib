#ifndef OS_QUEUE_H
#define OS_QUEUE_H
#include"os_core.h"

typedef struct st_os_queue{
    unsigned char queue_size;
    unsigned char item_size;
    unsigned char item_num;
    unsigned char head;
    unsigned char* zone;
}os_queue_t;

#define os_queue_item_align_size(item_size) (((item_size+RAM_ALIGN_OCTECTS-1)/RAM_ALIGN_OCTECTS)*RAM_ALIGN_OCTECTS)

#define OS_QUEUE_CREATE(name,item_size,queue_size)                            \
    static unsigned char queue_##name##_zone[os_queue_item_align_size(item_size)*queue_size];                          \
    static os_queue_t queue_##name={queue_size, item_size, 0, 0, queue_##name##_zone};     \
    os_queue_t* name=&queue_##name;


#define OS_QUEUE_NAME(name) extern os_queue_t* name;

//0=match
typedef int(*os_queue_query_t)(void* item1,void* query_param,unsigned int len);
void os_queue_init(os_queue_t* q);
void os_queue_push(os_queue_t* q,void* item);
void* os_queue_pop(os_queue_t* q);
int os_queue_is_in(os_queue_t* q,void* item);
int os_queue_is_empty(os_queue_t* q);
int os_queue_is_full(os_queue_t* q);
void* os_queue_query(os_queue_t* q,os_queue_query_t query,void* query_param);


#ifdef JMESH_TEST
#ifdef JMESH_TEST_OS_QUEUE
void os_queue_test(void);
#endif // JMESH_TEST_OS_QUEUE
#endif // JMESH_TEST

#endif // QUEUE_H
