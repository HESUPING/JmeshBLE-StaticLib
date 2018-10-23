#ifndef JMESH_DEVICE_H
#define JMESH_DEVICE_H
#include"jmesh_types.h"
#include"jmesh_config.h"
typedef struct st_jmesh_device{
    unsigned short addr;
    unsigned char element_num;
    jmesh_mac_t mac;
    jmesh_key_t devkey;
}jmesh_device_t;

void jmesh_device_init(void);
jmesh_device_t* jmesh_device_get_by_addr(unsigned short addr);
jmesh_device_t* jmesh_device_get_by_mac(unsigned char* mac);
unsigned char* jmesh_device_get_devkey(unsigned short addr);
int jmesh_device_new(unsigned short addr,unsigned char element_num,unsigned char* mac,unsigned char* devkey);
int jmesh_device_del(unsigned short addr);
int jmesh_device_clear(void);
#endif // JMESH_DEVICE_H
