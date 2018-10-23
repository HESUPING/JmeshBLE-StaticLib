#ifndef LIGHT_CONFIG_CALLBACK_H
#define LIGHT_CONFIG_CALLBACK_H
#include"light_config.h"


void light_config_client_button_status_callback(unsigned short src,light_config_client_button_t* config);
void light_config_server_scene_status_callback(unsigned short src,light_config_server_scene_t* config);



#endif // LIGHT_CONFIG_CALLBACK_H
