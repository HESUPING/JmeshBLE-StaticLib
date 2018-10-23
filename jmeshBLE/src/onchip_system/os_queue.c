#include "os_queue.h"
#include "stdlib.h"
#include "string.h"

void os_queue_init(os_queue_t* q)
{
    q->head=0;
    q->item_num=0;
}
void os_queue_push(os_queue_t* q,void* item)
{
    if(os_queue_is_full(q)){
        os_queue_pop(q);
    }
    memcpy(q->zone + ((q->head + q->item_num) % q->queue_size) * os_queue_item_align_size(q->item_size), item, q->item_size);
    q->item_num++;
}
void* os_queue_pop(os_queue_t* q)
{
    void* item;
    if(os_queue_is_empty(q)){
        return NULL;
    }
    item=q->zone + q->head*os_queue_item_align_size(q->item_size);
    q->head=(q->head+1)%q->queue_size;
    q->item_num--;
    return item;
}
/*
void os_queue_push2(os_queue_t* q, void* item)
{
    if (os_queue_is_full(q)){
        os_queue_pop2(q);
    }

    memcpy(q->zone + ((q->head + q->item_num) % q->queue_size) * os_queue_item_align_size(q->item_size), &item, sizeof(void*));
    q->item_num++;
}

void* os_queue_pop2(os_queue_t* q)
{
    void* item;
    if (os_queue_is_empty(q)){
        return NULL;
    }
    memcpy(&item, q->zone + q->head*os_queue_item_align_size(q->item_size), sizeof(void*));
    q->item_num--;
    return item;
}
*/

int os_queue_is_in(os_queue_t* q,void* item)
{
    return NULL!=os_queue_query(q,(os_queue_query_t)memcmp,item);
}
int os_queue_is_empty(os_queue_t* q)
{
    return q->item_num==0;
}
int os_queue_is_full(os_queue_t* q)
{
    return q->item_num==q->queue_size;
}
void* os_queue_query(os_queue_t* q,os_queue_query_t query,void* query_param)
{
    int i;
    void* item;
    for(i=0;i<q->item_num;i++){
        item=q->zone + ((q->head + i) % q->queue_size) * os_queue_item_align_size(q->item_size);
        if(0==query(item, query_param,q->item_size)){
            return item;
        }
    }
    return NULL;
}




#ifdef JMESH_TEST
#ifdef JMESH_TEST_OS_QUEUE

OS_QUEUE_CREATE(test_q1,3,1);
OS_QUEUE_CREATE(test_q2,4,10);
OS_QUEUE_CREATE(test_q3,49,250);

void os_queue_test(void)
{
    int i;
    unsigned char buffer[50];
    unsigned char* ptr1;
    unsigned char *ptr2,*ptr3;

    printf("_____________________os_queue test start________________\n");
    printf("_____________________queue init\n");

    os_queue_init(test_q1);
    os_queue_init(test_q2);
    os_queue_init(test_q3);

    for(i=0;i<50;i++){
        buffer[i]=i;
    }
    printf("\nis_in(0):%d,%d,%d\n",os_queue_is_in(test_q1,buffer),os_queue_is_in(test_q2,buffer),os_queue_is_in(test_q3,buffer));
    printf("is_empty :%d,%d,%d\n",os_queue_is_empty(test_q1),os_queue_is_empty(test_q2),os_queue_is_empty(test_q3));
    printf("is_full  :%d,%d,%d\n",os_queue_is_full(test_q1),os_queue_is_full(test_q2),os_queue_is_full(test_q3));
    printf("_____________________queue push 100 times\n");
    for(i=1;i<=100;i++){
        buffer[0]=i;
        os_queue_push(test_q1,buffer);
        os_queue_push(test_q2,buffer);
        os_queue_push(test_q3,buffer);
    }
    buffer[0]=95;
    printf("\nis_in(95):%d,%d,%d\n",os_queue_is_in(test_q1,buffer),os_queue_is_in(test_q2,buffer),os_queue_is_in(test_q3,buffer));
    printf("is_empty :%d,%d,%d\n",os_queue_is_empty(test_q1),os_queue_is_empty(test_q2),os_queue_is_empty(test_q3));
    printf("is_full  :%d,%d,%d\n",os_queue_is_full(test_q1),os_queue_is_full(test_q2),os_queue_is_full(test_q3));
    printf("_____________________queue pop 95 times\n");
    for(i=0;i<95;i++){
        os_queue_pop(test_q1);
        os_queue_pop(test_q2);
        os_queue_pop(test_q3);
    }
    printf("\nis_in(95):%d,%d,%d\n",os_queue_is_in(test_q1,buffer),os_queue_is_in(test_q2,buffer),os_queue_is_in(test_q3,buffer));
    printf("is_empty :%d,%d,%d\n",os_queue_is_empty(test_q1),os_queue_is_empty(test_q2),os_queue_is_empty(test_q3));
    printf("is_full  :%d,%d,%d\n",os_queue_is_full(test_q1),os_queue_is_full(test_q2),os_queue_is_full(test_q3));
    printf("_____________________queue push 5 times\n");
    for(i=0;i<5;i++){
        ptr1=os_queue_pop(test_q1);
        ptr2=os_queue_pop(test_q2);
        ptr3=os_queue_pop(test_q3);
        printf("%d,%d,%d,%d,%d\n",ptr1,ptr2,ptr3,(unsigned char)ptr3[0],(unsigned char)ptr3[1]);
    }
    printf("\nis_in(95):%d,%d,%d\n",os_queue_is_in(test_q1,buffer),os_queue_is_in(test_q2,buffer),os_queue_is_in(test_q3,buffer));
    printf("is_empty :%d,%d,%d\n",os_queue_is_empty(test_q1),os_queue_is_empty(test_q2),os_queue_is_empty(test_q3));
    printf("is_full  :%d,%d,%d\n",os_queue_is_full(test_q1),os_queue_is_full(test_q2),os_queue_is_full(test_q3));

    printf("_____________________os_queue test end________________\n");
}
#endif
#endif // JMESH_TEST

