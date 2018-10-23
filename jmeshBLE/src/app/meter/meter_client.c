#include"meter_server.h"
#include"meter_client.h"
#include"meter_client_callback.h"
#include"../../access/jmesh_access.h"
#include"../../access/jmesh_access_callback.h"
#include"../app_include.h"
#include"stdio.h"

JMESH_VENDOR_MODEL_CREATE_START(meter_client,JMESH_MODEL_COMPANY_ID,METER_CLIENT_MODEL_ID,5)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_CLIENT_ADDR_STATUS,meter_client_addr_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_CLIENT_ENERGY_STATUS,meter_client_energy_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_CLIENT_VOLTAGE_STATUS,meter_client_voltage_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_CLIENT_PDU_STATUS,meter_client_pdu_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_CLIENT_SCENE_STATUS,meter_client_scene_status_handler)
JMESH_MODEL_CREATE_END(meter_client)


void meter_client_init(void){
    jmesh_element_add_model(&element_app,&meter_client);
}
void meter_client_addr_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void meter_client_energy_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void meter_client_voltage_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void meter_client_pdu_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void meter_client_scene_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
 //   meter_client_scene_status_callback(data[0],data[1],data+2);
}



void meter_client_addr_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data){

    jmesh_access_send(dst,netkey_index,appkey_index,&meter_client,message_opcode_meter_server_addr_get,len,data);
}
void meter_client_energy_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data){

    jmesh_access_send(dst,netkey_index,appkey_index,&meter_client,message_opcode_meter_server_energy_get,len,data);
}
void meter_client_voltage_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data){

    jmesh_access_send(dst,netkey_index,appkey_index,&meter_client,message_opcode_meter_server_voltage_get,len,data);
}
void meter_client_pdu_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned short len,unsigned char* data){

    jmesh_access_send(dst,netkey_index,appkey_index,&meter_client,message_opcode_meter_server_pdu_get,len,data);
}
void meter_client_build_scene(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id,unsigned short len,unsigned char* data)
{

}
void meter_client_use_scene(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id)
{

}
