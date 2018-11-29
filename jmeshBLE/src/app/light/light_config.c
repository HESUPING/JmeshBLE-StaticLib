#include"light_server.h"
#include"light_client.h"
#include"light_config.h"
#include"light_config_callback.h"
#include"../../driver/jmesh_system.h"
#include"../../access/jmesh_access.h"
#include"../../access/jmesh_access_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"stdio.h"

static void light_config_client_button_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void light_config_server_scene_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

JMESH_VENDOR_MODEL_CREATE_START(light_config,LIGHT_CONFIG_COMPANY_ID,LIGHT_CONFIG_MODEL_ID,2)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_CONFIG_CLIENT_BUTTON_STATUS,light_config_client_button_status_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_CONFIG_SERVER_SCENE_STATUS, light_config_server_scene_status_handler)
JMESH_MODEL_CREATE_END(light_config)

static void light_config_client_button_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    light_config_client_button_t config_button;
    if(len<5){
        return;
    }
    memcpy(&config_button,data,len);
    if(config_button.type==0){
        if(config_button.pwm.nums+5==len){
            light_config_client_button_status_callback(src,&config_button);
        }
    }
    if(config_button.type==1){
        if(len==5){
            light_config_client_button_status_callback(src,&config_button);
        }
    }
}
static void light_config_server_scene_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    light_config_server_scene_t config_scene;
    if(len<=1){
        return;
    }
    memcpy(&config_scene,data,len);
    if(config_scene.pwm_nums+1==len){
        light_config_server_scene_status_callback(src,&config_scene);
    }
}

void light_config_init(void){
    jmesh_element_add_model(&element_app,&light_config);	
}



void light_config_client_button_bind_pwm(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short addr,unsigned char button_id,unsigned char value,unsigned char pwm_nums,unsigned char* pwm_value)
{
    light_config_client_button_t button;
    if(button_id>7||pwm_nums>JMESH_LIGHT_PWM_MAX_NUM){
        return;
    }

    button.dst=addr;
    button.aid=aid;
    button.type=0;
    button.button_id=button_id;
    button.value=value;
    button.pwm.nums=pwm_nums;
    memcpy(button.pwm.value,pwm_value,pwm_nums);

    jmesh_mutex_lock();
    jmesh_access_send(dst,nid,aid,&light_config,message_light_client_config_button,5+pwm_nums,(unsigned char*)&button);
    jmesh_mutex_unlock();
}
void light_config_client_button_bind_scene(unsigned short dst,unsigned short nid,unsigned short aid,unsigned short addr,unsigned char button_id,unsigned char value,unsigned char scene_id)
{
    light_config_client_button_t button;
    if(button_id>7){
        return;
    }

    button.dst=addr;
    button.aid=aid;
    button.type=1;
    button.button_id=button_id;
    button.value=value;
    button.scene.id=scene_id;

    jmesh_mutex_lock();
    jmesh_access_send(dst,nid,aid,&light_config,message_light_client_config_button,5,(unsigned char*)&button);
    jmesh_mutex_unlock();

}

void light_config_server_scene_set(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id,unsigned char pwm_nums,unsigned char* pwm_value)
{
    light_config_server_scene_t scene;
    if(pwm_nums>JMESH_LIGHT_PWM_MAX_NUM){
        return;
    }
    scene.scene_id=scene_id;
    scene.pwm_nums=pwm_nums;
    memcpy(scene.value,pwm_value,pwm_nums);

    jmesh_mutex_lock();
    jmesh_access_send(dst,netkey_index,appkey_index,&light_config,message_light_server_config_scene,pwm_nums+1,(unsigned char*)&scene);
    jmesh_mutex_unlock();
}

void light_config_client_button_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char button_id,unsigned char value)
{
    unsigned char buff[2];
    buff[0]=button_id;
    buff[1]=value;
    jmesh_mutex_lock();
    jmesh_access_send(dst,netkey_index,appkey_index,&light_config,message_light_client_get_button,2,buff);
    jmesh_mutex_unlock();

}
void light_config_server_scene_get(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id)
{
    jmesh_mutex_lock();
    jmesh_access_send(dst,netkey_index,appkey_index,&light_config,message_light_server_get_scene,1,&scene_id);
    jmesh_mutex_unlock();
}
