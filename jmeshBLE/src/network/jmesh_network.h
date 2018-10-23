#ifndef JMESH_NETWORK_H
#define JMESH_NETWORK_H
#include"../jmesh/jmesh_types.h"
#include"../jmesh/jmesh_pdu.h"


#define JMESH_NETWORK_PDU_MIN_LEN 15
#define JMESH_NETWORK_PDU_MAX_LEN 29


#define JMESH_NETWORK_CIPHER_PDU_CACHE_SIZE 2
#define JMESH_NETWORK_CIPHER_PDU_CACHE_NUM 20

#define JMESH_NETWORK_PLAIN_PDU_CACHE_SIZE 4
#define JMESH_NETWORK_PLAIN_PDU_CACHE_NUM 20

#define JMESH_NETWORK_CIPHER_CACHE_OFFSET        2/**< first 2 octets because pdu is obfuscated */
#define JMESH_NETWORK_PLAIN_CACHE_OFFSET        5/**< seq(lower 2 octets) + src */



#define JMESH_LOWER_UNSEGMENT_PDU_OFFSET    ((int)(&((jmesh_pdu_t*)0)->network.access.pdu))
#define JMESH_LOWER_SEGMENT_PDU_OFFSET      ((int)(&((jmesh_pdu_t*)0)->network.access.segment.pdu))

#define JMESH_NETWORK_DST_PDU_OFFSET        ((int)(&((jmesh_pdu_t*)0)->network.DST))
#define JMESH_NETWORK_IVI_PDU_OFFSET        2
#define JMESH_NETWORK_CTL_PDU_OFFSET        3

#define JMESH_NETWORK_PDU_HEAD_SIZE (JMESH_NETWORK_DST_PDU_OFFSET-JMESH_NETWORK_IVI_PDU_OFFSET)



void jmesh_network_init(void);
int jmesh_network_send(unsigned short netkey_index,jmesh_pdu_t* pdu);
int jmesh_network_recv(jmesh_pdu_t* pdu);
#endif // JMESH_NETWORK_H
