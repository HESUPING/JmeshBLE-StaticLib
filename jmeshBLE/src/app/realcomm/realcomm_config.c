#include"realcomm_client.h"
#include"realcomm_server.h"
#include"realcomm_config.h"
#include"realcomm_config_callback.h"
#include"../../jmesh/jmesh_types.h"
#include"../../access/jmesh_access.h"


static void realcomm_config_client_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void realcomm_config_server_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);



JMESH_VENDOR_MODEL_CREATE_START(realcomm_config,REALCOMM_CONFIG_COMPANY_ID,REALCOMM_CONFIG_MODEL_ID,2)
    JMESH_MESSAGE_ADD(MESSAGE_REALCOMM_CONFIG_CLIENT_STATUS,realcomm_config_client_status_handler)
    JMESH_MESSAGE_ADD(MESSAGE_REALCOMM_CONFIG_SERVER_STATUS,realcomm_config_server_status_handler)
JMESH_MODEL_CREATE_END(realcomm_config)


void realcomm_config_init(void){
    jmesh_element_add_model(&element_app,&realcomm_config);
}

static void realcomm_config_client_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short addr;
    if(len==2){
        JMESH_BIG_ENDIAN_PICK2(addr,data);
        realcomm_config_client_status_callback(src,nid,aid,addr);
    }
}
static void realcomm_config_server_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short baud;
		unsigned char parity;
    if(len==3){
				JMESH_BIG_ENDIAN_PICK2(baud,data);
				parity = data[2];
        realcomm_config_server_status_callback(src,nid,aid,baud,parity);
    }
}

void realcomm_config_client(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short addr)
{
    unsigned char buff[2];
    JMESH_BIG_ENDIAN_FILL2(addr,buff);
    jmesh_access_send(dst,nid,aid,&realcomm_config,message_realcomm_client_config,2,buff);
}
void realcomm_config_server(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short baud,unsigned char parity)
{
    unsigned char buff[3];
    JMESH_BIG_ENDIAN_FILL2(baud,buff);
    buff[2]=parity;
    jmesh_access_send(dst,nid,aid,&realcomm_config,message_realcomm_server_config,3,buff);
}
