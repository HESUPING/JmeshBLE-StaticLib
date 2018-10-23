#include"stdio.h"
#include"light_server.h"
#include"light_client.h"
#include"light_config.h"
#include"light_server_callback.h"
#include"light_client_callback.h"
#include"../../access/jmesh_access.h"
#include"../../jmesh/jmesh_print.h"

static void light_server_control_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void light_server_config_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* scene);
static void light_server_get_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void light_server_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
static void light_server_blink_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

JMESH_VENDOR_MODEL_CREATE_START(light_server,LIGHT_SERVER_COMPANY_ID,LIGHT_SERVER_MODEL_ID,5)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_SERVER_CONTROL,             light_server_control_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_SERVER_CONFIG_SCENE,        light_server_config_scene_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_SERVER_GET_SCENE,           light_server_get_scene_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_SERVER_SCENE,               light_server_scene_handler)
    JMESH_MESSAGE_ADD(MESSAGE_LIGHT_SERVER_BLINK,               light_server_blink_handler)
JMESH_MODEL_CREATE_END(light_server)

void light_server_init(void){
    jmesh_element_add_model(&element_app,&light_server);
    light_server_scene_init();
		light_hard_init();
}

static void light_server_control_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    if(len==data[0]+1){
        light_server_control_callback(data[0],data+1);
        jmesh_access_send(src,nid,aid,&light_server,message_light_client_status,len,data);
    }
    else{
        print_error("data format error\n");
    }
}
static void light_server_config_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    light_config_server_scene_t* scene = (light_config_server_scene_t*)data;
    if(len<2){
        return;
    }
    if(scene->pwm_nums+1!=len){
        return;
    }

    light_server_config_scene_callback(src,nid,aid,scene);
}

static void light_server_get_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    if(len==1){
        light_server_get_scene_callback(src,nid,aid,data[0]);
    }
    else{
        print_error("data format error\n");
    }
}

static void light_server_scene_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    if(len==1){
        light_server_scene_callback(src,aid,nid,data[0]);
    }
    else{
        print_error("data format error\n");
    }
}

static void light_server_blink_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    if(len==4)
    light_server_blink_callback(data[0],data[1],data[2],data[3]);
}
