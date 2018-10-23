#ifndef REALCOMM_SERVER_H
#define REALCOMM_SERVER_H
#include"../../access/jmesh_model.h"


#define MESSAGE_REALCOMM_SERVER_CONFIG               {0xc0,0x04,0x01}/**< data:baud+parity */
#define MESSAGE_REALCOMM_SERVER_TRANS                {0xc0,0x04,0x02}/**< data:trans value */
JMESH_MESSAGE_CREATE(MESSAGE_REALCOMM_SERVER_CONFIG,         message_realcomm_server_config);
JMESH_MESSAGE_CREATE(MESSAGE_REALCOMM_SERVER_TRANS,          message_realcomm_server_trans);

JMESH_MODEL_NAME(realcomm_server);

#define REALCOMM_SERVER_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define REALCOMM_SERVER_MODEL_ID   0x0004
void realcomm_server_init(void);
#endif
