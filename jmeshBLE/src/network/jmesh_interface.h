#ifndef JMESH_INTERFACE_H
#define JMESH_INTERFACE_H

#include"jmesh_filter.h"
#include"../jmesh/jmesh_pdu.h"
#include"../bearer/adv/jmesh_adv.h"
#include"../bearer/gatt/jmesh_gatt.h"
#include"../bearer/gatt/jmesh_proxy.h"
#include"jmesh_filter.h"

#define JMESH_INTERFACE_SIZE (JMESH_GATT_SIZE+2)
#define JMESH_INTERFACE_ADV (JMESH_INTERFACE_SIZE-2)
#define JMESH_INTERFACE_LOCAL (JMESH_INTERFACE_SIZE-1)


void jmesh_interface_init(void);

void jmesh_interface_set_filter_type(unsigned char interface,unsigned char type);
void jmesh_interface_add_filter_addr(unsigned char interface,unsigned short addr);
void jmesh_interface_remove_filter_addr(unsigned char interface,unsigned short addr);
int jmesh_interface_filter_status(unsigned char interface,unsigned char length,unsigned char* buffer);

jmesh_filter_t* jmesh_interface_get_filter(unsigned char interface);
int jmesh_interface_get_filter_num(unsigned char interface);
int jmesh_interface_get_filter_type(unsigned char interface);
int jmesh_interface_filtering(unsigned char interface,unsigned short addr);

void jmesh_interface_read(unsigned char interface,jmesh_pdu_t* pdu);
void jmesh_interface_recv(unsigned char interface,jmesh_pdu_t* pdu);

int jmesh_interface_recv_handler(jmesh_pdu_t* pdu);
int jmesh_interface_send_handler(jmesh_pdu_t* pdu);
void jmesh_interface_broadcast(jmesh_pdu_t* pdu);
void jmesh_interface_send(unsigned char interface,jmesh_pdu_t* pdu);


#endif // JMESH_INTERFACE_H
