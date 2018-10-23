#ifndef OS_MEMB_H
#define OS_MEMB_H

#include"os_core.h"



typedef int(*os_memb_finder_t)(void* item,void* param);//0=matched,else not
typedef struct st_os_memb{
    unsigned short size;
    unsigned short nums;
    unsigned char* flag;
    void* buffer;
}os_memb_t;

#if(RAM_ALIGN_OCTECTS==2)
    #define OS_MEMB_CACHE_BUFFER_T unsigned short
#else
    #define OS_MEMB_CACHE_BUFFER_T unsigned long
#endif

#define OS_MEMB_CREATE(name, size, nums)\
	static unsigned char os_memb_##name##_flag[(nums+7)/8] ={0};\
    static OS_MEMB_CACHE_BUFFER_T os_memb_##name##_buffer[nums*((size+RAM_ALIGN_OCTECTS-1)/RAM_ALIGN_OCTECTS)];\
    static os_memb_t os_memb_##name={(((size+RAM_ALIGN_OCTECTS-1)/RAM_ALIGN_OCTECTS)*RAM_ALIGN_OCTECTS), nums, os_memb_##name##_flag,os_memb_##name##_buffer};\
    os_memb_t *name=&os_memb_##name;
#define OS_MEMB_NAME(name) extern os_memb_t* name;

#define BIT_CLR(byte,bits) (byte)&=~(1<<(bits))
#define BIT_SET(byte,bits) (byte)|=(1<<(bits))
#define BIT_GET(byte,bits) ((byte)&(1<<(bits)))

#define OS_MEMB_IS_USED(cache,index)     BIT_GET(cache->flag[index/8],(index%8))
#define OS_MEMB_SET_USED(cache,index)    BIT_SET(cache->flag[index/8],(index%8))
#define OS_MEMB_SET_FREE(cache,index)    BIT_CLR(cache->flag[index/8],(index%8))

void os_memb_init(os_memb_t* m);
void* os_memb_new(os_memb_t* m);
void* os_memb_get_by_index(os_memb_t* m,int index);
void* os_memb_find(os_memb_t* m,void* finder_param,os_memb_finder_t finder);
void os_memb_free(os_memb_t* m,void* item);
int os_memb_is_valid(os_memb_t* m,int index);
unsigned char os_memb_remains(os_memb_t* m);

#ifdef JMESH_TEST
#ifdef JMESH_TEST_OS_MEMB
void os_memb_test(void);
#endif // JMESH_TEST_OS_MEMB
#endif // JMESH_TEST


#endif
