#ifndef JMESH_LOWER_H
#define JMESH_LOWER_H
#include"../jmesh/jmesh_pdu.h"



#define JMESH_LOWER_UNSEGMENT_PDU_OFFSET    ((int)(&((jmesh_pdu_t*)0)->network.access.pdu))
#define JMESH_LOWER_SEGMENT_PDU_OFFSET      ((int)(&((jmesh_pdu_t*)0)->network.access.segment.pdu))

int jmesh_lower_send(unsigned short netkey_index,unsigned short length,jmesh_pdu_t* pdu);
int jmesh_lower_recv(unsigned short netkey_index,jmesh_pdu_t* pdu);

#endif // JMESH_LOWER_H
