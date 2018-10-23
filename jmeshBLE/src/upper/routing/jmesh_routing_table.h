#ifndef JMESH_ROUTING_TABLE_H
#define JMESH_ROUTING_TABLE_H

#include"../../jmesh/jmesh_pdu.h"

#define JMESH_ROUTE_TABLE_SIZE 100
#define JMESH_ROUTE_UPDATE_RECORD_SIZE 10
#define JMESH_ROUTE_SCHEDULE_INTERVAL_S 1
#define JMESH_ROUTE_LIFETIME_S 120
#define JMESH_ROUTE_DISTANCE_LIMIT 7

#define JMESH_ROUTE_VALUE_LIMIT 5

#define JMESH_ROUTE_REQUEST_INTERVAL_S 30

#define JMESH_ROUTE_EXCHANGE_INTERVAL_MINUTE 10

typedef struct st_jmesh_route{
    unsigned short addr;

    unsigned char gate_interface:4;
    unsigned char element_num:4;
    unsigned char distance:6;
    unsigned char is_valid:1;
    unsigned char is_used:1;

    unsigned long seq:24;
    unsigned long lifetime:8;
}jmesh_route_t;



void jmesh_route_init(void);

int jmesh_route_add(unsigned char interface,unsigned short addr,unsigned char element_num,unsigned char distance,unsigned long seq);

int jmesh_route_flush_seq(unsigned char interface,unsigned short addr,unsigned long seq);

void jmesh_route_del(unsigned short addr,unsigned long seq);
void jmesh_route_del_gate(unsigned char interface);
void jmesh_route_del_node(unsigned short addr);

jmesh_route_t* jmesh_route_get(unsigned short addr);
jmesh_route_t* jmesh_route_next(jmesh_route_t* route);

jmesh_route_t* jmesh_route_record_next(jmesh_route_t* route);
void jmesh_route_del_record(jmesh_route_t *route);
int jmesh_get_route_record_num(void);

void jmesh_routing_send(unsigned short dst,jmesh_pdu_t* pdu);



#endif // JMESH_ROUTING_TABLE_H
