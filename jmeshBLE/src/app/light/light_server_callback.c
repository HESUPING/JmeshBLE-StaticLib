#include"light_server.h"
#include"light_client.h"
#include"light_config.h"
#include"light_server_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"../../access/jmesh_access.h"
#include"../../driver/jmesh_gpio.h"
#include"../../driver/jmesh_pwm.h"
#include"../../onchip_system/os_timer.h"
#include"../../onchip_system/os_timer_event.h"
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
		if(pwm_nums == 1)   
		{
				jmesh_gpio_set(JMESH_LED1, pwm_value[0]);			
			  jmesh_gpio_set(POWER_LIGHT, pwm_value[0]);

		}

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
os_timer_event_t light_blink;
struct light_blink_time_st{
		unsigned char last_s;
		unsigned char delays_ms;
		unsigned char on_ms;
		unsigned char off_ms;
}blink_time;
void light_blink_timer_handler(void* argv)
{
		static unsigned short count = 0;
		count++;
		if(blink_time.on_ms == 0)
		{
				jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_HIGH);
				os_timer_event_remove(&light_blink);
				return;
		}			
		if(blink_time.off_ms == 0) 
		{
				jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_LOW);
				os_timer_event_remove(&light_blink);
				return;
		}
		os_timer_event_restart(&light_blink);	
		if(count < blink_time.on_ms)
		{
			    jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_HIGH);

		}else {
					jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_LOW);
		}
		if(count == blink_time.on_ms +blink_time.off_ms) count = 0;
		
}
void light_server_blink_callback(unsigned char last_s,unsigned char delays_ms,unsigned char on_100ms,unsigned char off100_ms)
{
		os_timer_event_set(&light_blink, 100, light_blink_timer_handler, NULL);			
		blink_time.last_s =	last_s;
		blink_time.delays_ms = delays_ms;
		blink_time.off_ms  = off100_ms;
		blink_time.on_ms   = on_100ms;

    ;
}
