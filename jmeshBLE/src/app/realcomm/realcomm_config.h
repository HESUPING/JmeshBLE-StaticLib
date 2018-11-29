#ifndef REALCOMM_CONFIG_H
#define REALCOMM_CONFIG_H
#include"../../access/jmesh_model.h"


#define MESSAGE_REALCOMM_CONFIG_CLIENT_STATUS           {0xc0,0x06,0x01}/**< data: addr*/
#define MESSAGE_REALCOMM_CONFIG_SERVER_STATUS           {0xc0,0x06,0x02}/**< data:baud+parity */
JMESH_MESSAGE_CREATE(MESSAGE_REALCOMM_CONFIG_CLIENT_STATUS,message_realcomm_config_client_status);
JMESH_MESSAGE_CREATE(MESSAGE_REALCOMM_CONFIG_SERVER_STATUS,message_realcomm_config_server_status);


JMESH_MODEL_NAME(realcomm_config);

#define REALCOMM_CONFIG_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define REALCOMM_CONFIG_MODEL_ID   0x0006

enum{
    REALCOMM_PARITY_EVEN=0,
    REALCOMM_PARITY_ODD=1,
    REALCOMM_PARITY_NONE=2,
};
void realcomm_config_init(void);
void realcomm_config_client(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short addr);
void realcomm_config_server(unsigned short dst,unsigned short nid,unsigned short aid,unsigned char baud,unsigned char parity);



#endif
