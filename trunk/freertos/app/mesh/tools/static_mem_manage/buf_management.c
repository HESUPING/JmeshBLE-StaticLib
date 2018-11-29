#include <stdbool.h>
#include "buf_management.h"
#include "log.h"

#include "osapp_config.h"
#ifdef OSAPP_MESH


static bool array_buf_hdl_sanity_check(buf_management_t *buf_hdl,uint8_t *ptr);

uint16_t array_buf_idx_get(buf_management_t *buf_hdl,void *ptr)
{
    BX_ASSERT(array_buf_hdl_sanity_check(buf_hdl,ptr));
    return ((uint8_t *)ptr-buf_hdl->buf)/buf_hdl->element_size;
}

void *array_buf_alloc_idx(buf_management_t *buf_hdl,uint16_t idx)
{
    BX_ASSERT(buf_hdl->ref_cnt[idx]==0);
    ++buf_hdl->ref_cnt[idx];
    --buf_hdl->remaining_size;
    return &buf_hdl->buf[idx*buf_hdl->element_size];
}

void *array_buf_calloc_idx(buf_management_t *buf_hdl,uint16_t idx)
{
    void *ptr = array_buf_alloc_idx(buf_hdl,idx);
    if(ptr)
    {
        memset(ptr,0,buf_hdl->element_size);
    }
    return ptr;
}

void *array_buf_alloc(buf_management_t *buf_hdl)
{
    uint16_t i;
    for(i=0;i<buf_hdl->buf_length;++i)
    {
        if(buf_hdl->ref_cnt[i]==0)
        {
            return array_buf_alloc_idx(buf_hdl,i);
        }
    }
    return NULL;
}

void *array_buf_calloc(buf_management_t *buf_hdl)
{
    void *ptr = array_buf_alloc(buf_hdl);
    if(ptr)
    {
        memset(ptr,0,buf_hdl->element_size);
    }
    return ptr;
}

void array_buf_retain(buf_management_t *buf_hdl,void *ptr)
{
    BX_ASSERT(array_buf_hdl_sanity_check(buf_hdl,(uint8_t *)ptr));
    uint16_t i = ((uint8_t *)ptr-buf_hdl->buf)/buf_hdl->element_size;
    BX_ASSERT(buf_hdl->ref_cnt[i]);
    ++buf_hdl->ref_cnt[i];
}

static bool array_buf_hdl_sanity_check(buf_management_t *buf_hdl,uint8_t *ptr)
{
    if((ptr-buf_hdl->buf)%buf_hdl->element_size)
    {
        return false;
    }
    if(ptr<buf_hdl->buf || ptr>= &buf_hdl->buf[buf_hdl->buf_length*buf_hdl->element_size])
    {
        return false;
    }
    return true;
}

uint16_t array_buf_available_size(buf_management_t *buf_hdl)
{
    return buf_hdl->remaining_size;
}

uint16_t array_buf_element_size(buf_management_t *buf_hdl)
{
    return buf_hdl->element_size;
}

// check the element handle is in the array buf
bool array_buf_is_elem_handle_valid(buf_management_t *buf_hdl,void *elem_hdl)
{
    bool state = false;

    if(array_buf_hdl_sanity_check(buf_hdl,elem_hdl))// addr in buf range
    {
        uint16_t i = ((uint8_t *)elem_hdl-buf_hdl->buf)/buf_hdl->element_size;
        if( buf_hdl->ref_cnt[i] ) state = true;
    }
    return state;
}

void array_buf_release(buf_management_t *buf_hdl,void *ptr)
{
    BX_ASSERT(array_buf_hdl_sanity_check(buf_hdl,ptr));
    uint16_t i = ((uint8_t *)ptr-buf_hdl->buf)/buf_hdl->element_size;
    BX_ASSERT(buf_hdl->ref_cnt[i]);
    if(--buf_hdl->ref_cnt[i]==0)
    {
        ++buf_hdl->remaining_size;
    }
}

#endif /* OSAPP_MESH */
