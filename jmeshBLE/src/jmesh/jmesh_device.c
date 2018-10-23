#include"jmesh_device.h"
#include"jmesh_save.h"

void jmesh_device_init(void);
jmesh_device_t* jmesh_device_get_by_addr(unsigned short addr);
jmesh_device_t* jmesh_device_get_by_mac(unsigned char* mac);
int jmesh_device_new(unsigned short addr,unsigned char element_num,unsigned char* mac,unsigned char* devkey);
int jmesh_device_del(unsigned short addr);


static jmesh_device_t device_cache[JMESH_DEVICE_MAX_NUM];

void jmesh_device_init(void)
{
    int i;
    for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        device_cache[i].addr=0;
        jmesh_save_buffer_read(JMESH_SAVE_DEVICE,i,sizeof(jmesh_device_t),(unsigned char*)(&device_cache[i]));
    }
}
jmesh_device_t* jmesh_device_get_by_addr(unsigned short addr)
{
    int i;
    for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        if(device_cache[i].addr==addr){
            return &device_cache[i];
        }
    }
    return NULL;
}
jmesh_device_t* jmesh_device_get_by_mac(unsigned char* mac){

    int i;
    for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        if(device_cache[i].addr!=0){
            if(0==memcmp(device_cache[i].mac,mac,JMESH_MAC_SIZE)){
                return &device_cache[i];
            }
        }
    }
    return NULL;
}

unsigned char* jmesh_device_get_devkey(unsigned short addr){

    int i;
    for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        if(device_cache[i].addr==addr){
            return device_cache[i].devkey;
        }
    }
    return NULL;
}
int jmesh_device_new(unsigned short addr,unsigned char element_num,unsigned char* mac,unsigned char* devkey){
    int i;
    for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        if(device_cache[i].addr==addr){
            memcpy(device_cache[i].mac,mac,JMESH_MAC_SIZE);
            memcpy(device_cache[i].devkey,devkey,JMESH_KEY_SIZE);
            device_cache[i].element_num=element_num;
            jmesh_save_buffer_write(JMESH_SAVE_DEVICE,i,sizeof(jmesh_device_t),(unsigned char*)(&device_cache[i]));
            return 0;
        }
    }
     for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        if(0==device_cache[i].addr){
            device_cache[i].addr=addr;
            memcpy(device_cache[i].devkey,devkey,JMESH_KEY_SIZE);
            memcpy(device_cache[i].mac,mac,JMESH_MAC_SIZE);
            jmesh_save_buffer_write(JMESH_SAVE_DEVICE,i,sizeof(jmesh_device_t),(unsigned char*)(&device_cache[i]));
            return 0;
        }
    }
    return -1;
}
int jmesh_device_del(unsigned short addr)
{
    int i;
    for(i=0;i<JMESH_DEVICE_MAX_NUM;i++){
        if(addr==device_cache[i].addr){
            device_cache[i].addr=0;
            jmesh_save_buffer_delete(JMESH_SAVE_DEVICE,i);
            return 0;
        }
    }
    return -1;
}
int jmesh_device_clear(void)
{
    for(int i=0;i<JMESH_DEVICE_MAX_NUM;i++){
            device_cache[i].addr=0;
            jmesh_save_buffer_delete(JMESH_SAVE_DEVICE,i);
            return 0;
    }
    return -1;	
}
