#ifndef LIGHT_SERVER_H
#define LIGHT_SERVER_H
#include"../../access/jmesh_model.h"


#define MESSAGE_LIGHT_SERVER_CONTROL            {0xc0,0x01,0x01}
#define MESSAGE_LIGHT_SERVER_CONFIG_SCENE       {0xc0,0x01,0x02}
#define MESSAGE_LIGHT_SERVER_GET_SCENE          {0xc0,0x01,0x03}
#define MESSAGE_LIGHT_SERVER_SCENE              {0xc0,0x01,0x04}
#define MESSAGE_LIGHT_SERVER_BLINK              {0xc0,0x01,0x05}

JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_SERVER_CONTROL,          message_light_server_control);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_SERVER_CONFIG_SCENE,     message_light_server_config_scene);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_SERVER_GET_SCENE,        message_light_server_get_scene);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_SERVER_SCENE,            message_light_server_scene);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_SERVER_BLINK,            message_light_server_blink);

JMESH_MODEL_NAME(light_server);

#define LIGHT_SERVER_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define LIGHT_SERVER_MODEL_ID   0x0001




void light_server_init(void);
#endif // LIGHT_SERVER_H
