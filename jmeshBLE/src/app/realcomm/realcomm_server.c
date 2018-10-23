#include"realcomm_client.h"
#include"realcomm_server.h"
#include"realcomm_config.h"
#include"realcomm_server_callback.h"
#include"../../jmesh/jmesh_types.h"
#include"../../access/jmesh_access.h"


static void realcomm_server_config_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void realcomm_server_trans_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);



JMESH_VENDOR_MODEL_CREATE_START(realcomm_server,REALCOMM_SERVER_COMPANY_ID,REALCOMM_SERVER_MODEL_ID,2)
    JMESH_MESSAGE_ADD(MESSAGE_REALCOMM_SERVER_CONFIG,realcomm_server_config_handler)
    JMESH_MESSAGE_ADD(MESSAGE_REALCOMM_SERVER_TRANS,realcomm_server_trans_handler)
JMESH_MODEL_CREATE_END(realcomm_server)


void realcomm_server_init(void){
    jmesh_element_add_model(&element_app,&realcomm_server);
    realcomm_server_init_callback();
}

static void realcomm_server_config_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short baud = 0;
		unsigned char  parity = 0 ;
    if(len==3){
				JMESH_BIG_ENDIAN_PICK2(baud,data);
				parity = data[2];
        if(1==realcomm_server_config_callback(baud,parity)){
            jmesh_access_send(src,nid,aid,&realcomm_server,message_realcomm_config_server_status,len,data);
        }
    }
}
static void realcomm_server_trans_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    realcomm_server_trans_callback(len,data);
}
