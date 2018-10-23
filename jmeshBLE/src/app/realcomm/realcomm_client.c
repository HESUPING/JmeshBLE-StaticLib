#include"realcomm_client.h"
#include"realcomm_server.h"
#include"realcomm_config.h"
#include"../../jmesh/jmesh_types.h"
#include"../../access/jmesh_access.h"


static void realcomm_client_config(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);


JMESH_VENDOR_MODEL_CREATE_START(realcomm_client,REALCOMM_CLIENT_COMPANY_ID,REALCOMM_CLIENT_MODEL_ID,1)
    JMESH_MESSAGE_ADD(MESSAGE_REALCOMM_CLIENT_CONFIG,realcomm_client_config)
JMESH_MODEL_CREATE_END(realcomm_client)


void realcomm_client_init(void){
    jmesh_element_add_model(&element_app,&realcomm_client);
    realcomm_client_init_callback();
}

static void realcomm_client_config(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    unsigned short addr;
    if(len==2){
        JMESH_BIG_ENDIAN_PICK2(addr,data);
        if(1==realcomm_client_config_callback(addr,nid,aid)){
            jmesh_access_send(src,nid,aid,&realcomm_client,message_realcomm_config_client_status,2,data);
        }
    }
}

