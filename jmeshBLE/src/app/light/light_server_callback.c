#include"light_server.h"
#include"light_client.h"
#include"light_config.h"
#include"light_server_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"../../access/jmesh_access.h"
#include"../../driver/jmesh_gpio.h"
#include"../../driver/jmesh_pwm.h"
static light_config_server_scene_t server_scene[LIGHT_SERVER_SCENE_SIZE];

void light_hard_init(void)
{
//		jmesh_gpio_init(20,JMESH_GPIO_MODE_OUTPUT);
//		jmesh_gpio_init(21,JMESH_GPIO_MODE_OUTPUT);
//		jmesh_gpio_init(22,JMESH_GPIO_MODE_OUTPUT);
}
void light_server_scene_init(void)
{
    memset(server_scene,0,sizeof(server_scene));
    //save read
}
void light_server_control_callback(unsigned char pwm_nums,unsigned char* pwm_value){
		
    print_info("light server control callback %x\n",pwm_value[0]);
		if(pwm_nums == 3)
		{
				jmesh_pwm_start(20,JMESH_PWM_CHANNEL_0, pwm_value[0], 0xff-pwm_value[0]);
				jmesh_pwm_start(21,JMESH_PWM_CHANNEL_1, pwm_value[1], 0xff-pwm_value[1]);
				jmesh_pwm_start(22,JMESH_PWM_CHANNEL_2, pwm_value[2], 0xff-pwm_value[2]);			
		}
}
void light_server_rgb_control_callback()
{

		jmesh_pwm_start(20,JMESH_PWM_CHANNEL_0, 1000, 0);
		jmesh_pwm_start(21,JMESH_PWM_CHANNEL_1, 1000,0);
		jmesh_pwm_start(22,JMESH_PWM_CHANNEL_2, 1000,0);
}

void light_server_config_scene_callback(unsigned short src,unsigned short nid,unsigned short aid,light_config_server_scene_t* scene)
{
    if(scene->scene_id<LIGHT_SERVER_SCENE_SIZE){
        server_scene[scene->scene_id]=*scene;
        //save write
        print_info("light server config scene %d\n",scene->scene_id);
        jmesh_access_send(src,nid,aid,&light_server,message_light_config_server_scene_status,scene->pwm_nums+1,(unsigned char*)&server_scene[scene->scene_id]);
    }
}
void light_server_get_scene_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char scene_id)
{
    if(scene_id<LIGHT_SERVER_SCENE_SIZE){

        print_info("light server get scene %d\n",scene_id);
        jmesh_access_send(src,nid,aid,&light_server,message_light_config_server_scene_status,server_scene[scene_id].pwm_nums+1,(unsigned char*)&server_scene[scene_id]);
    }
}
void light_server_scene_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char scene_id)
{
    if(scene_id<LIGHT_SERVER_SCENE_SIZE){

        print_info("light server scene %d\n",scene_id);
        light_server_control_callback(server_scene[scene_id].pwm_nums,server_scene[scene_id].value);
    }
}
void light_server_blink_callback(unsigned char last_s,unsigned char delays_ms,unsigned char on_ms,unsigned char off_ms)
{
    ;
}
