#ifndef LIGHT_CTL_SERVER__H
#define LIGHT_CTL_SERVER__H

#include "mesh_env.h"
#include "mesh_model.h"
 
typedef struct
{
	//light ctl status
	uint16_t pre_light_ctl_temperature;
	uint16_t pre_light_ctl_lightness;
	uint16_t tar_light_ctl_lightness;
	uint16_t tar_light_ctl_temperature;
	uint16_t pre_light_ctl_delta_uv;
	uint16_t tar_light_ctl_delta_uv;
	//light ctl default status
	uint16_t light_ctl_lightness_default;
	uint16_t light_ctl_temperature_default;
	uint16_t light_ctl_delta_uv_default;
	//light ctl temperature range status
	uint16_t light_ctl_temp_range_min;
	uint16_t light_ctl_temp_range_max;
	uint8_t light_ctl_temp_range_status_code;
	
}light_ctl_server_msg_format_t;

typedef struct
{
	void *inst;
	uint16_t_t target_ctl_lightness;
	uint16_t_t target_ctl_temperature;
	uint16_t_t target_ctl_delta_uv;
	uint8_t trans_time;
	uint8_t timer_index;
}light_ctl_delay_parma_t;


typedef struct
{ 
	TimerHandle_t Timer[GENERIC_TIMER_MAX];
	light_ctl_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
	TimerHandle_t trans_timer;
	uint16_t mask;
}light_ctl_delay_timer_t;

typedef struct
{
	model_server_base_t model;
	light_ctl_server_msg_format_t msg_format; 
	generic_valid_field_queue_t ctl_queue;
	light_ctl_delay_timer_t delay_timer;
	user_mesh_callback cb;
	uint32_t trans_tick_start;
	uint8_t server_state;
	
}light_ctl_server_t;
#endif
