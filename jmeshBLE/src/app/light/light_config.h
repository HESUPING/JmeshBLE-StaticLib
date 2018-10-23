#ifndef LIGHT_CONFIG_H
#define LIGHT_CONFIG_H
#include"../../access/jmesh_model.h"



#include"../../access/jmesh_model.h"


#define MESSAGE_LIGHT_CONFIG_CLIENT_BUTTON_STATUS   {0xc0,0x03,0x01}
#define MESSAGE_LIGHT_CONFIG_SERVER_SCENE_STATUS    {0xc0,0x03,0x02}

JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_CONFIG_CLIENT_BUTTON_STATUS, message_light_config_client_button_status);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_CONFIG_SERVER_SCENE_STATUS,  message_light_config_server_scene_status);


JMESH_MODEL_NAME(light_config);

#define LIGHT_CONFIG_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define LIGHT_CONFIG_MODEL_ID   0x0003


#define JMESH_LIGHT_PWM_MAX_NUM 6
typedef struct st_light_config_client_button{
    unsigned short type:1;//0=pwm,1=scene
    unsigned short dst:15;
    unsigned short aid:12;
    unsigned short value:1;
    unsigned short button_id:3;
    union{
        struct{
            unsigned char nums;
            unsigned char value[JMESH_LIGHT_PWM_MAX_NUM];
        }pwm;
        struct{
            unsigned char id;
        }scene;
    };
}light_config_client_button_t;

typedef struct st_light_config_server_scene{
    unsigned char scene_id:4;
    unsigned char pwm_nums:4;
    unsigned char value[JMESH_LIGHT_PWM_MAX_NUM];
}light_config_server_scene_t;


void light_config_init(void);

void light_config_client_button_bind_pwm(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short addr,
                                         unsigned char button_id,unsigned char value,unsigned char pwm_nums,unsigned char* pwm_value);
void light_config_client_button_bind_scene(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short addr,
                                           unsigned char button_id,unsigned char value,unsigned char scene_id);

void light_config_server_scene_set(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id,unsigned char pwm_nums,unsigned char* pwm_value);

void light_config_client_button_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char button_id,unsigned char value);
void light_config_server_scene_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id);

#endif // LIGHT_CLIENT_H
