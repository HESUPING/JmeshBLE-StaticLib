#ifndef BUF_MANAGEMENT_H_
#define BUF_MANAGEMENT_H_
#include <stdint.h>
#include <stddef.h>
#include "co_math.h"
typedef struct{
    uint8_t *buf;
    uint8_t *ref_cnt;
    uint16_t element_size;
    uint16_t buf_length;
    uint16_t remaining_size;
}buf_management_t;

 
#define DEF_ARRAY_BUF(buf_hdl,type,size) \
    static __attribute__((aligned(4))) uint8_t _##buf_hdl##_array[(size)*sizeof(type)]; \
    static uint8_t _##buf_hdl##_array_ref_cnt[(size)]; \
    buf_management_t buf_hdl = { \
        .buf = _##buf_hdl##_array, \
        .ref_cnt = _##buf_hdl##_array_ref_cnt, \
        .element_size = sizeof(type), \
        .buf_length = (size), \
        .remaining_size = (size),\
    }

#define FOR_EACH_ALLOCATED_ITEM(buf_hdl,ptr,sentences_block) \
    for(ptr = (void *)(buf_hdl).buf; (uint8_t *)ptr < &(buf_hdl).buf[(buf_hdl).buf_length*(buf_hdl).element_size];ptr = (void *)((uint8_t *)ptr + (buf_hdl).element_size)) \
    { \
        if((buf_hdl).ref_cnt[((uint8_t *)ptr-(buf_hdl).buf)/(buf_hdl).element_size]) \
        { \
           sentences_block; \
        } \
    }

uint16_t array_buf_element_size(buf_management_t *buf_hdl);

uint16_t array_buf_available_size(buf_management_t *buf_hdl);

bool array_buf_is_elem_handle_valid(buf_management_t *buf_hdl,void *elem_hdl);

uint16_t array_buf_idx_get(buf_management_t *buf_hdl,void *ptr);

void *array_buf_alloc_idx(buf_management_t *buf_hdl,uint16_t idx);

void *array_buf_calloc_idx(buf_management_t *buf_hdl,uint16_t idx);

void *array_buf_alloc(buf_management_t *buf_hdl);

void *array_buf_calloc(buf_management_t *buf_hdl);//alloc and memset 0

void array_buf_retain(buf_management_t *buf_hdl,void *ptr);

void array_buf_release(buf_management_t *buf_hdl,void *ptr);


#endif
