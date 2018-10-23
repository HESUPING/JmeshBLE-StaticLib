#include"meter_server.h"
#include"meter_client.h"
#include"meter_server_callback.h"
#include"protocol_645.h"
#include"../../access/jmesh_access.h"
#include"../../jmesh/jmesh_print.h"
#include"../app_include.h"
#include"stdio.h"
#include"stdlib.h"

JMESH_VENDOR_MODEL_CREATE_START(meter_server,JMESH_MODEL_COMPANY_ID,METER_SERVER_MODEL_ID,6)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_SERVER_ADDR_GET,     meter_server_addr_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_SERVER_ENERGY_GET,   meter_server_energy_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_SERVER_VOLTAGE_GET,  meter_server_voltage_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_SERVER_PDU_GET,      meter_server_pdu_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_SERVER_BUILD_SCENE,  meter_server_build_scene_handler)
JMESH_MESSAGE_ADD(MESSAGE_OPCODE_METER_SERVER_USE_SCENE,    meter_server_use_scene_handler)
JMESH_MODEL_CREATE_END(meter_server)

#define MAX_465_BUFFER_SIZE 100
static unsigned char energy_di[4] =  {0x00,0x00,0x00,0x00};
static unsigned char voltage_di[4] = {0x00,0x01,0x01,0x02};
static unsigned char protocol_645_addr[6] = {0};
enum {
		uart_idle_enum,
		protocol_645_addr_get_enum,
		protocol_645_energy_get_enum,
		protocol_645_voltage_get_enum,
		protocol_645_pdu_get_enum,
};

typedef struct {
		unsigned short dst;
		unsigned short nid;
		unsigned short aid;
		unsigned char type;	
		unsigned char  len;
		unsigned char* data;
}access_send_save_t;

static access_send_save_t  access_send_save;


void meter_server_init(void){
    jmesh_element_add_model(&element_app,&meter_server);
}

void meter_server_addr_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		if( len!=0 ) return ;       
    meter_server_addr_get_callback(data,len);
	
	  access_send_save.dst = dst;
	  access_send_save.nid = nid;
	  access_send_save.aid = aid;
		access_send_save.type = protocol_645_addr_get_enum;

//		os_timer_event_set();
//    jmesh_access_send(dst,nid,aid,&meter_server,message_opcode_meter_client_addr_status,len,data);	
}

void meter_server_energy_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		if( len!=0 ) return ;  	
			
    meter_server_energy_get_callback(data,len);
	
	  access_send_save.dst = dst;
	  access_send_save.nid = nid;
	  access_send_save.aid = aid;
		access_send_save.type = protocol_645_energy_get_enum;	
//    jmesh_access_send(dst,nid,aid,&meter_server,message_opcode_meter_client_energy_status,len,data);	
}

void meter_server_voltage_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		if( len!=0 ) return ;  				
    meter_server_voltage_get_callback(data,len);
	
	  access_send_save.dst = dst;
	  access_send_save.nid = nid;
	  access_send_save.aid = aid;
		access_send_save.type = protocol_645_voltage_get_enum;	
//   jmesh_access_send(dst,nid,aid,&meter_server,message_opcode_meter_client_voltage_status,len,data);	
}

void meter_server_pdu_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		meter_server_pdu_get_callback(data,len);
	  access_send_save.dst = dst;
	  access_send_save.nid = nid;
	  access_send_save.aid = aid;
		access_send_save.type = protocol_645_pdu_get_enum;	
//    jmesh_access_send(dst,nid,aid,&meter_server,message_opcode_meter_client_pdu_status,len,data);	
}

void meter_server_build_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){

//        meter_server_build_scene_callback(data[0],data[1],data+2);
}
void meter_server_use_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
//        meter_server_use_scene_callback(data[0]);
}

int protocol_645_timed_handler(unsigned char* data, unsigned short len)
{
    unsigned short offset;
    int ret;
    unsigned char di[4];
    if(0<(ret=protocol_64507_pick(len,data,&offset))){
				switch(access_send_save.type)
				{
					case uart_idle_enum :
						break;
					case protocol_645_addr_get_enum :
						if(*(data+offset+8)==0x93){
								memcpy(access_send_save.data,data+offset+1,6);
								memcpy(protocol_645_addr,data+offset+1,6);
								access_send_save.len = 6;
								jmesh_access_send(access_send_save.dst,
																	access_send_save.nid,
																	access_send_save.aid,
																	&meter_server,
																	message_opcode_meter_client_addr_status,
																	access_send_save.len,
																	access_send_save.data);							
						}
						
						break;
					case protocol_645_energy_get_enum :
						protocol_64507_get_di(ret,data+offset,di);		
						if(0==memcmp(energy_di,di,4))
						{
								access_send_save.len = protocol_64507_get_data(ret,data+offset,MAX_465_BUFFER_SIZE,access_send_save.data);					
								jmesh_access_send(access_send_save.dst,
																	access_send_save.nid,
																	access_send_save.aid,
																	&meter_server,
																	message_opcode_meter_client_energy_status,
																	access_send_save.len,
																	access_send_save.data);													
						}
	
							break;
					case protocol_645_voltage_get_enum :
						protocol_64507_get_di(ret,data+offset,di);	
						if(0==memcmp(voltage_di,di,4))
						{
								access_send_save.len = protocol_64507_get_data(ret,data+offset,MAX_465_BUFFER_SIZE,access_send_save.data);						
								jmesh_access_send(access_send_save.dst,
																	access_send_save.nid,
																	access_send_save.aid,
																	&meter_server,
																	message_opcode_meter_client_voltage_status,
																	access_send_save.len,
																	access_send_save.data);															
						}

							break;
					case protocol_645_pdu_get_enum : 
						protocol_64507_get_di(ret,data+offset,di);
//						if(0==memcmp(cache->data+6,di,4)){
//								if(ret<=out_len){
//										memcpy(out_data,in_data+offset,ret);
//										return ret;
//								}
//								else{
//										return 0;
//								}
//						}						
						break;					
				}

        }
			return 0;
}
	

