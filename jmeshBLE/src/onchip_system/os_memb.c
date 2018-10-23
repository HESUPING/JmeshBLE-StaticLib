#include"os_memb.h"

//#define OS_MEMB_IS_USED(cache,index)     BIT_GET(cache->flag[index/8],(index%8))
//#define OS_MEMB_SET_USED(cache,index)    BIT_SET(cache->flag[index/8],(index%8))
//#define OS_MEMB_SET_FREE(cache,index)    BIT_CLR(cache->flag[index/8],(index%8))


void os_memb_init(os_memb_t* m)
{
    int i;
    for(i=0;i<m->nums;i++){
        OS_MEMB_SET_FREE(m,i);
    }
}
void* os_memb_new(os_memb_t* m)
{
    int i;
    for(i=0;i<m->nums;i++){
        if(OS_MEMB_IS_USED(m,i)==0){

            OS_MEMB_SET_USED(m,i);
            return ((unsigned char *)m->buffer+m->size*i);
        }
    }
    return NULL;
}
void* os_memb_get_by_index(os_memb_t* m,int index)
{
    if(m==NULL||index<0||index>=m->nums){
        return NULL;
    }
    return ((unsigned char *)m->buffer+m->size*index);
}
void* os_memb_find(os_memb_t* m,void* finder_param,os_memb_finder_t finder)
{
    int i;
    if(finder==NULL||m==NULL)
        return NULL;
    for(i=0;i<m->nums;i++){
        if(OS_MEMB_IS_USED(m,i)){
            if(0==finder((unsigned char *)m->buffer+i*m->size,finder_param)){
                return (unsigned char *)m->buffer+m->size*i;
            }
        }
    }
    return NULL;
}
void os_memb_free(os_memb_t* m,void* item)
{
    int index=((unsigned char*)item-(unsigned char*)m->buffer)/m->size;
    if(index>=m->nums||index<0)
        return;
    OS_MEMB_SET_FREE(m,index);
}
int os_memb_is_valid(os_memb_t* m,int index)
{
    if (index > m->size)
        return 0;
    return OS_MEMB_IS_USED(m,index);
}

unsigned char os_memb_remains(os_memb_t* m)
{
    unsigned char remain = 0,i;
    for (i =0; i < m->nums; i++){
        if (!OS_MEMB_IS_USED(m, i))
            remain++;
    }
    return remain;
}

#ifdef JMESH_TEST
#ifdef JMESH_TEST_OS_MEMB
OS_MEMB_CREATE(memb_t1,3,1);
OS_MEMB_CREATE(memb_t2,4,10);
OS_MEMB_CREATE(memb_t3,5,100);

static int memb_test_finder(unsigned char* memb,int *value)
{
    return memb[0]!=*value;
}
static void memb_test(os_memb_t* m)
{
    int i,j;
    unsigned char *ptr;
    for(i=0;i<70;i++){
        if(NULL==(ptr=os_memb_new(m))){
            break;
        }
        ptr[0]=i;
    }
    printf("new 70 succeed %d membs,remains %d\n",i,os_memb_remains(m));

    for(j=0;j<i;j+=2){
        ptr=os_memb_get_by_index(m,j);
        os_memb_free(m,ptr);
    }
    printf("free odd index memb,now remains %d\n now find 0-10\n",os_memb_remains(m));
    for(i=0;i<10;i++){
        if(NULL!=(ptr=os_memb_find(m,&i,memb_test_finder))){
            printf("%d,%d\n",ptr,ptr[0]);
        }
        else{
            printf("NULL\n");
        }
    }
    printf("now new 10 membs again\n");
    for(i=0;i<10;i++){
        if(NULL!=(ptr=os_memb_new(m))){
            printf("%d\n",ptr);
        }
    }

}

void os_memb_test(void)
{

    printf("___________________os_memb test start_________________\n");
    printf("now init memb t1[1],t2[10,t3[100]\n");

    os_memb_init(memb_t1);
    os_memb_init(memb_t2);
    os_memb_init(memb_t3);
    printf("__________memb1 test start\n");
    memb_test(memb_t1);
    printf("__________memb2 test start\n");
    memb_test(memb_t2);
    printf("__________memb3 test start\n");
    memb_test(memb_t3);


    printf("\n___________________os_memb test stop_________________\n");
}
#endif // JMESH_TEST_OS_MEMB
#endif // JMESH_TEST
