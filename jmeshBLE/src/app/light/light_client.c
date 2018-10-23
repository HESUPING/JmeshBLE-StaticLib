#include"light_server.h"
#include"light_client.h"
#include"light_client_callback.h"
#include"../../driver/jmesh_system.h"
#include"light_client.h"
#include"../../access/jmesh_access.h"
#include"../../access/jmesh_access_callback.h"
#include"stdio.h"

static void light_client_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void light_client_config_button_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void light_client_get_button_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);


JMESH_VENDOR_MODEL_CREATE_START(light_client,LIGHT_CLIENT_COMPANY_ID,LIGHT_CLIENT_MODEL_ID,3)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_CLIENT_STATUS,light_client_status_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_CLIENT_CONFIG_BUTTON,light_client_config_button_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_CLIENT_GET_BUTTON,light_client_get_button_handler)
JMESH_MODEL_CREATE_END(light_client)


void light_client_init(void){
    jmesh_element_add_model(&element_app,&light_client);
    light_client_button_init();
}

static void light_client_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    light_client_status_callback(data[0],data+1);
}


static void light_client_config_button_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    light_config_client_button_t config_button;
    if(len<5){
        return;
    }
    memcpy(&config_button,data,len);
    if(config_button.type==0){
        if(config_button.pwm.nums+5==len){
            light_client_config_button_callback(src,nid,aid,&config_button);
        }
    }
    if(config_button.type==1){
        if(len==5){
            light_client_config_button_callback(src,nid,aid,&config_button);
        }
    }

}
static void light_client_get_button_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    if(len!=2){
        return;
    }
    light_client_get_button_callback(src,nid,aid,data[0],data[1]);

}


void light_client_control(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char pwm_nums,unsigned char* pwm_value){
    unsigned char buff[9];
    unsigned char len=0;
    int i;

    if(pwm_nums>5){
        pwm_nums=5;
    }
    buff[len++]=pwm_nums;
    for(i=0;i<pwm_nums;i++){
        buff[len++]=pwm_value[i];
    }
    jmesh_mutex_lock();
    jmesh_access_send(dst,netkey_index,appkey_index,&light_client,message_light_server_control,len,buff);
    jmesh_mutex_unlock();
}
void light_client_rgb_set(unsigned char red_pwm,unsigned char gree_pwm,unsigned char blue_pwm)
{

}

void light_client_scene(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char scene_id){

    jmesh_mutex_lock();
    jmesh_access_send(dst,netkey_index,appkey_index,&light_client,message_light_server_scene,1,&scene_id);
    jmesh_mutex_unlock();
}
void light_client_blink(unsigned short dst,unsigned short nid,unsigned short aid,unsigned char last_s,unsigned char delay_steps,unsigned char on_steps,unsigned char off_steps)
{
    unsigned char blink_para[4];

    blink_para[0]=last_s;
    blink_para[1]=delay_steps;
    blink_para[2]=on_steps;
    blink_para[3]=off_steps;

    jmesh_mutex_lock();
    jmesh_access_send(dst,nid,aid,&light_client,message_light_server_blink,4,blink_para);
    jmesh_mutex_unlock();
}




