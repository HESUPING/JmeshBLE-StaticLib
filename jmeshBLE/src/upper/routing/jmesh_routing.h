#ifndef JMESH_ROUTING_H
#define JMESH_ROUTING_H
#include"../../jmesh/jmesh_pdu.h"
typedef struct st_jmesh_route_request{
    //unsigned char opcode;
    unsigned char element_num;
    unsigned char dest[2];
    unsigned char init_ttl;//distance=init_ttl-network.ttl
}jmesh_route_request_t;
typedef jmesh_route_request_t jmesh_route_response_t;


typedef struct st_jmesh_route_remove{
    //unsigned char opcode;
    unsigned char element_num;
    unsigned char init_ttl;
    unsigned char dest_addr[2];
    unsigned char dest_seq[3];
}jmesh_route_remove_t;

typedef struct st_jmesh_route_exchange_info{
    unsigned char addr[2];
    unsigned char element_num;
    unsigned char distance;
    unsigned char seq[3];
    unsigned char :7;
    unsigned char is_update:1;
}jmesh_route_exchange_info_t;

typedef struct st_jmesh_route_exchange{
    //unsigned char opcode;
    unsigned char num:6;
    unsigned char SAR:2;
    jmesh_route_exchange_info_t info[1];
}jmesh_route_exchange_t;

typedef union un_jmesh_route_pdu{
    //unsigned char opcode;
    jmesh_route_request_t request;
    jmesh_route_response_t response;
    jmesh_route_remove_t remove;
    jmesh_route_exchange_t exchange;
}jmesh_route_pdu_t;


void jmesh_route_request_process(jmesh_pdu_t* pdu);
void jmesh_route_response_process(jmesh_pdu_t* pdu);
void jmesh_route_remove_process(jmesh_pdu_t* pdu);
void jmesh_route_exchange_process(jmesh_pdu_t* pdu);


void jmesh_route_request(unsigned short dest);
void jmesh_route_remove(unsigned short dest,unsigned short dest_seq);

void jmesh_route_exchange(void);
void jmesh_route_heartbeat(void);

void routing_test(void);




#endif

