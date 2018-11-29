#ifndef JMESH_GATT_H
#define JMESH_GATT_H

#include"../../onchip_system/os_timer_event.h"



#define JMESH_GATT_ID_INVALID       0xff
#define JMESH_GATT_CONNECT_S        5
#define JMESH_GATT_ACTIVE_S         10
#define JMESH_GATT_SIZE             10

#define JMESH_GATT_CONNECT_LIMIT 6
#define JMESH_GATT_CONNECT_INTERVAL_S 5
#define JMESH_ROUTE_REMOVE_INTERVAL_S 60


#define JMESH_SVC_UUID {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x03,0xff,0x00,0x00}

typedef struct st_jmesh_pdu jmesh_pdu_t;

typedef struct st_jmesh_gatt{
    unsigned char mac[6];
    unsigned char id;
    union{
        unsigned char flag;
        struct{
            unsigned char is_valid:1;
            unsigned char is_ready:1;
            unsigned char is_server:1;
        };
    };
    unsigned short mtu;
    unsigned short svc_instance;
    jmesh_pdu_t* recv_cache;
    os_timer_event_t drop_timer;
}jmesh_gatt_t;

void jmesh_gatt_init(void);
void jmesh_gatt_disconnect(jmesh_gatt_t* gatt);
int jmesh_gatt_ready_num(void);

jmesh_gatt_t* jmesh_gatt_get_by_mac(unsigned char* mac);
jmesh_gatt_t* jmesh_gatt_get_by_id(unsigned char id);
jmesh_gatt_t* jmesh_gatt_get_by_interface(unsigned char interface);
unsigned char jmesh_gatt_get_interface(jmesh_gatt_t* gatt);
jmesh_gatt_t* jmesh_gatt_next(jmesh_gatt_t* gatt);
int jmesh_gatt_is_ready(jmesh_gatt_t* gatt);

void jmesh_gatt_connected(unsigned char* mac,unsigned char id,unsigned char is_server);
void jmesh_gatt_disconnected(unsigned char connect_id);
void jmesh_gatt_set_mtu(unsigned char connect_id, unsigned short mtu);
void jmesh_gatt_set_svc_instance(unsigned char connect_id,unsigned short instance);
void jmesh_gatt_recv(unsigned char connect_id,unsigned short instance,unsigned short length,unsigned char* data);

void jmesh_gatt_send(jmesh_gatt_t* gatt,unsigned short instance,unsigned char length,unsigned char* data);


#endif // JMESH_GATT_H
