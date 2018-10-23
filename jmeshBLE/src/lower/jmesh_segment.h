#ifndef JMESH_SEGMENT_H
#define JMESH_SEGMENT_H

#define JMESH_SEGMENT_CACHE_SIZE 5
#define JMESH_LOWER_ACCESS_UNSEGMENT_PDU_SIZE 15
#define JMESH_SEGMENT_ACCESS_MESSAGE_SIZE 12

#define JMESH_LOWER_UNSEGMENT_PDU_SIZE 11
#define JMESH_LOWER_SEGMENT_MESSAGE_SIZE 8

#define JMESH_UNSEGMENT_MESSAGE_SIZE(ctl) (ctl ? JMESH_LOWER_UNSEGMENT_PDU_SIZE :JMESH_LOWER_ACCESS_UNSEGMENT_PDU_SIZE)
#define JMESH_SEGMENT_MESSAGE_SIZE(ctl)  (ctl ? JMESH_LOWER_SEGMENT_MESSAGE_SIZE :JMESH_SEGMENT_ACCESS_MESSAGE_SIZE)

#define JMESH_SEGMENT_RETRANSMIT_COUNT 0

#define JMESH_RESEGMENT_INCOMPLETE_S 10


#define jmesh_lower_init_segment_head(head,segN,seqZero) \
do{                                             \
        head[0]=0;                              \
        head[0]|=(unsigned char)(seqZero>>6);   \
        head[1]=0;                              \
        head[1]|=(unsigned char)(seqZero<<2);   \
        head[2]=segN;                           \
}while(0)

#define jmesh_lower_set_segment_segO(head,segO) \
do{                                             \
    head[2]|=(segO<<5);                         \
    head[1]|=segO>>3;                           \
}while(0)

#define jmesh_lower_set_segment_SZMIC(head,SZMIC)   do{head[0]|=(SZMIC<<7);}while(0)

#define jmesh_lower_get_segment_segO(head) ((head[2]>>5)|((head[1]&0x03)<<3))
#define jmesh_lower_get_segment_segN(head) (head[2]&0x1f)
#define jmesh_lower_get_segment_seqZero(head)   ((head[1]>>2)|(((unsigned short)(head[0]&0x7f))<<6))
#define jmesh_lower_get_segment_SZMIC(head) (head[0]>>7)

void jmesh_segment_init(void);
int jmesh_segment_send(unsigned short netkey_index,unsigned short length,jmesh_pdu_t* pdu);
int jmesh_resegment_recv(unsigned short netkey_index,jmesh_pdu_t* pdu);
int jmesh_segment_recv_ack(jmesh_pdu_t* pdu);

#endif // JMESH_SEGMENT_H
