#ifndef REALCOMM_CLIENT_H
#define REALCOMM_CLIENT_H
#include"../../access/jmesh_model.h"
#include"realcomm_client_callback.h"
#define MESSAGE_REALCOMM_CLIENT_CONFIG            {0xc0,0x05,0x02}/**< data:addr */

JMESH_MESSAGE_CREATE(MESSAGE_REALCOMM_CLIENT_CONFIG,message_realcomm_client_config);


JMESH_MODEL_NAME(realcomm_client);

#define REALCOMM_CLIENT_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define REALCOMM_CLIENT_MODEL_ID   0x0005


void realcomm_client_init(void);
void realcomm_client_init(void);

#endif
