#ifndef LIGHT_CLIENT_CALLBACK
#define LIGHT_CLIENT_CALLBACK
#include"light_config.h"


#define LIGHT_CLIENT_BUTTON_SIZE 2

void light_client_button_init(void);
void light_hard_init(void);
void light_client_status_callback(unsigned char pwm_nums,unsigned char* pwm_values);
void light_client_config_button_callback(unsigned short src,unsigned short nid,unsigned short aid,light_config_client_button_t* button);
void light_client_get_button_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char button_id,unsigned char value);
void light_client_button_callback(unsigned char button_id,unsigned char value);

#endif // LIGHT_CLIENT_CALLBACK
