#ifndef METER_SERVER_H
#define METER_SERVER_H
#include"../../access/jmesh_model.h"

#define METER_SERVER_MODEL_ID  3
#define MESSAGE_OPCODE_METER_SERVER_ADDR_GET     {0xc0,0x02,0x00}
#define MESSAGE_OPCODE_METER_SERVER_ENERGY_GET   {0xc0,0x02,0x01}
#define MESSAGE_OPCODE_METER_SERVER_VOLTAGE_GET  {0xc0,0x02,0x02}
#define MESSAGE_OPCODE_METER_SERVER_PDU_GET      {0xc0,0x02,0x03}
#define MESSAGE_OPCODE_METER_SERVER_BUILD_SCENE  {0xc0,0x02,0x04}
#define MESSAGE_OPCODE_METER_SERVER_USE_SCENE    {0xc0,0x02,0x05}

JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_SERVER_ADDR_GET, message_opcode_meter_server_addr_get);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_SERVER_ENERGY_GET,  message_opcode_meter_server_energy_get);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_SERVER_VOLTAGE_GET, message_opcode_meter_server_voltage_get);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_SERVER_PDU_GET,  message_opcode_meter_server_pdu_get);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_SERVER_BUILD_SCENE, message_opcode_meter_server_build_scene);
JMESH_MESSAGE_CREATE(MESSAGE_OPCODE_METER_SERVER_USE_SCENE,  message_opcode_meter_server_use_scene);
JMESH_MODEL_NAME(meter_server);

void meter_server_init(void);

void meter_server_addr_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_server_energy_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_server_voltage_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_server_pdu_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_server_build_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void meter_server_use_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
int protocol_645_timed_handler(unsigned char* data, unsigned short len);

#endif //


