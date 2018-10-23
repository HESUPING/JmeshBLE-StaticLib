
#include"jmesh_save.h"
#include"jmesh_print.h"

#include"../driver/jmesh_save.h"
#include <stdio.h>
#define JMESH_SAVE_DEFINE
#define JMESH_SAVE_CREATE(name,type) [name]=sizeof(type),
#define JMESH_SAVE_BUFFER_CREATE(name,size,type) [name]=sizeof(type),
const unsigned char jmesh_save_length[JMESH_SAVE_SIZE]={

    #include"jmesh_save.h"
};
#undef JMESH_SAVE_DEFINE


int jmesh_save_length_get(signed char name)
{
    if(name>=JMESH_SAVE_SIZE){
        return 0;
    }
    return jmesh_save_length[name];
}

int jmesh_save_read(signed char name,unsigned char length,unsigned char* data)
{
    if(name>=JMESH_SAVE_SIZE||length==0||data==NULL){
        return 0;
    }
    return driver_save_read(name,&length,data);
}
int jmesh_save_write(signed char name,unsigned char length,unsigned char* data)
{
    if(name>=JMESH_SAVE_SIZE||length==0||data==NULL){
        return 0;
    }
    return driver_save_write(name,length,data);
}
int jmesh_save_delete(signed char name)
{
    if(name>=JMESH_SAVE_SIZE){
        return 0;
    }
    return driver_save_delete(name);
}


#ifdef JMESH_TEST
#ifdef JMESH_TEST_SAVE
void jmesh_save_test(void)
{
    jmesh_mac_t mac={0,0,0,0,0,0};
    int  ret,i,j;
    unsigned long seq=0;
    printf("_____jmesh_save test start______\n");
    ret=jmesh_save_read(JMESH_SAVE_MAC,JMESH_MAC_SIZE,mac);
    printf("read mac len=%d,value:%x,%x,%x,%x,%x,%x\n",ret,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    for(i=0;i<JMESH_SEQ_LIST_SIZE;i++){
        ret=jmesh_save_buffer_read(JMESH_SAVE_SEQ_LIST,i,4,(unsigned char*)&seq);
        printf("read %d ret=%d seq=%d\n",i,ret,seq);
    }
    printf("now inc mac[0],mac[5]\n");
    mac[0]++;mac[5]++;
    jmesh_save_write(JMESH_SAVE_MAC,JMESH_MAC_SIZE,mac);
    printf("now update and add seq\n");
    for(j=0;j<=i&&j<JMESH_SEQ_LIST_SIZE;j++){
        seq++;
        jmesh_save_buffer_write(JMESH_SAVE_SEQ_LIST,i,4,(unsigned char*)&seq);
    }
    printf("reread data\n");
    ret=jmesh_save_read(JMESH_SAVE_MAC,JMESH_MAC_SIZE,mac);
    printf("read mac len=%d,value:%x,%x,%x,%x,%x,%x\n",ret,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    for(i=0;i<JMESH_SEQ_LIST_SIZE;i++){
        ret=jmesh_save_buffer_read(JMESH_SAVE_SEQ_LIST,i,4,(unsigned char*)&seq);
        printf("write %d ret=%d seq=%d\n",i,ret,seq);
    }
    printf("please reset to watch result\n");
    printf("_____jmesh_save test end________\n");
}

#endif
#endif
