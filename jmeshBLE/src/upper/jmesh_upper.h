#ifndef JMESH_UPPER_H
#define JMESH_UPPER_H
#include"../jmesh/jmesh_types.h"
#include"../jmesh/jmesh_pdu.h"
#include"../foundation/state/jmesh_appkey.h"
#include"../lower/jmesh_lower.h"
#include"../lower/jmesh_segment.h"

#define JMESH_UPPER_DEFAULT_MIC_SIZE JMESH_MIC32_SIZE

/**< a full unsegment pdu  3 opcode + 8 data +4 MIC,order suggest not bigger than 8*/
#define JMESH_UPPER_UNSEGMENT_MAX_LENGTH (JMESH_LOWER_ACCESS_UNSEGMENT_PDU_SIZE-JMESH_UPPER_DEFAULT_MIC_SIZE)
#define JMESH_CONTORL_UNSEGMENT_MAX_LENGTH 7

int jmesh_upper_recv(unsigned short netkey_index,unsigned short length,jmesh_pdu_t* pdu);

int jmesh_upper_access_send(jmesh_pdu_t* pdu);
int jmesh_upper_config_send(jmesh_pdu_t* pdu);
int jmesh_upper_control_send(unsigned short src,unsigned short dst,unsigned short netkey_index,unsigned short length,unsigned char* data);




//void jmesh_upper_send(jmesh_appkey_t* appkey,jmesh_model_t* model,jmesh_message_t* message,unsigned short length,unsigned char* data);



#endif // JMESH_UPPER_H
