#ifndef LIGHT_CLIENT_H
#define LIGHT_CLIENT_H
#include"../../access/jmesh_model.h"





#define MESSAGE_LIGHT_CLIENT_STATUS                 {0xc0,0x02,0x01}
#define MESSAGE_LIGHT_CLIENT_CONFIG_BUTTON          {0xc0,0x02,0x02}
#define MESSAGE_LIGHT_CLIENT_GET_BUTTON             {0xc0,0x02,0x03}

JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_CLIENT_STATUS,       message_light_client_status);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_CLIENT_CONFIG_BUTTON,message_light_client_config_button);
JMESH_MESSAGE_CREATE(MESSAGE_LIGHT_CLIENT_GET_BUTTON,   message_light_client_get_button);


JMESH_MODEL_NAME(light_client);

#define LIGHT_CLIENT_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define LIGHT_CLIENT_MODEL_ID   0x0002


typedef struct st_jmesh_light_config{
    unsigned short dst;
    unsigned short aid:12;
    unsigned short type:4;//0=control,1=use scene
    union{
        struct{
            unsigned char pwm_nums;
            unsigned char pwm_value[3];
        }control;
        struct{
            unsigned char scene_id;
        }use_scene;
    };
}jmesh_light_client_config_t;

void light_client_init(void);
void light_client_control(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char pwm_nums,unsigned char* pwm_value);
void light_client_scene(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id);
void light_client_blink(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char last_s,unsigned char delays_step,unsigned char on_step,unsigned char off_step);


#endif // LIGHT_CLIENT_H
