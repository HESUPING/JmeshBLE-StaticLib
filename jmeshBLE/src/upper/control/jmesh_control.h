#ifndef JMESH_CONTROL_H
#define JMESH_CONTROL_H

#include"../../jmesh/jmesh_pdu.h"

enum{
    JMESH_CONTROL_LOWER_SEGMENT_ACKNOWLEDGE=0,

    JMESH_CONTROL_FRIEND_POLL=1,
    JMESH_CONTROL_FRIEND_UPDATE=2,
    JMESH_CONTROL_FRIEND_REQUEST=3,
    JMESH_CONTROL_FRIEND_OFFER=4,
    JMESH_CONTROL_FRIEND_CLEAR=5,
    JMESH_CONTROL_FRIEND_CLEAR_CONFIRM=6,
    JMESH_CONTROL_FRIEND_SUBSCRIPTION_LIST_ADD=7,
    JMESH_CONTROL_FRIEND_SUBSCRIPTION_LIST_REMOVE=8,
    JMESH_CONTROL_FRIEND_SUBSCRIPTION_LIST_CONFIRM=9,

    JMESH_CONTROL_HEARTBEAT=0x0a,

    JMESH_CONTROL_ROUTE_REQUEST,
    JMESH_CONTROL_ROUTE_RESPONSE,
    JMESH_CONTROL_ROUTE_REMOVE,
    JMESH_CONTROL_ROUTE_EXCHANGE,
};

int jmesh_control_recv(unsigned short netkey_index,unsigned short length,jmesh_pdu_t* pdu);
int jmesh_control_send(unsigned short src,unsigned short dst,unsigned short netkey_index,unsigned char opcode,unsigned char ttl,unsigned short length,unsigned char* data);
#endif
