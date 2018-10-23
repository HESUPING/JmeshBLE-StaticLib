#ifndef METER_CLIENT_H
#define METER_CLIENT_H
#include"../../access/jmesh_model.h"

#define  METER_CLIENT_MODEL_ID   0X04

#define MESSAGE_OPCODE_METER_CLIENT_ADDR_STATUS          {0xc0,0x03,0x00}
#define MESSAGE_OPCODE_METER_CLIENT_ENERGY_STATUS        {0xc0,0x03,0x01}
#define MESSAGE_OPCODE_METER_CLIENT_VOLTAGE_STATUS       {0xc0,0x03,0x02}
#define MESSAGE_OPCODE_METER_CLIENT_PDU_STATUS           {0xc0,0x03,0x03}
#define MESSAGE_OPCODE_METER_CLIENT_SCENE_STATUS         {0xc0,0x03,0x04}

JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_CLIENT_ADDR_STATUS,      message_opcode_meter_client_addr_status);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_CLIENT_ENERGY_STATUS,     message_opcode_meter_client_energy_status);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_CLIENT_VOLTAGE_STATUS,    message_opcode_meter_client_voltage_status);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_CLIENT_PDU_STATUS,        message_opcode_meter_client_pdu_status);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_CLIENT_SCENE_STATUS,      message_opcode_meter_client_scene_status);
JMESH_MODEL_NAME(meter_client);

void meter_client_init(void);
void meter_client_addr_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_client_energy_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_client_voltage_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_client_pdu_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_client_scene_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

void meter_client_addr_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data);
void meter_client_energy_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data);
void meter_client_voltage_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data);
void meter_client_pdu_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data);
void meter_client_build_scene(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id,unsigned short len,unsigned char* data);
void meter_client_use_scene(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id);


#endif // LIGHT_CLIENT_H
