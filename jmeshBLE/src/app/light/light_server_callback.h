#ifndef LIGHT_SERVER_CALLBACK_H
#define LIGHT_SERVER_CALLBACK_H
#include"light_server.h"
#include"light_config.h"


#define LIGHT_SERVER_SCENE_SIZE 2

void light_server_scene_init(void);
void light_server_control_callback(unsigned char pwm_nums,unsigned char* pwm_value);
void light_server_config_scene_callback(unsigned short src,unsigned short nid,unsigned short aid,light_config_server_scene_t* scene);
void light_server_get_scene_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char scene_id);
void light_server_scene_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char scene_id);
void light_server_blink_callback(unsigned char last_s,unsigned char delays_ms,unsigned char on_ms,unsigned char off_ms);


#endif // LIGHT_SERVER_CALLBACK_H
