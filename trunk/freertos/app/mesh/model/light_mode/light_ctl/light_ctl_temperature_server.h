#ifndef LIGHT_CTL_TEMPERATURE_SERVER__H
#define LIGHT_CTL_TEMPERATURE_SERVER__H

typedef struct
{
	uint16_t present_ctl_temperature;
	uint16_t target_ctl_temperature;
	uint16_t present_ctl_delta_uv;
	uint16_t target_ctl_delta_uv;
}light_ctl_temperature_sever_msg_format_t;

typedef struct
{
	void *inst;
	uint16_t target_ctl_temperature;
	uint16_t target_ctl_delta_uv;
	uint8_t trans_time;
	uint8_t timer_index;
}light_ctl_temperature_delay_parma_t;


typedef struct
{ 
	TimerHandle_t Timer[GENERIC_TIMER_MAX];
	light_ctl_temperature_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
	TimerHandle_t trans_timer;
	uint16_t mask;
}light_ctl_temperature_delay_timer_t;

typedef struct
{
	model_server_base_t model;
	light_ctl_temperature_sever_msg_format_t msg_format; 
	generic_valid_field_queue_t ctl_temp_queue;
	light_ctl_delay_timer_t delay_timer;
	light_ctl_temperature_delay_timer_t cb;
	uint32_t trans_tick_start;
	uint8_t server_state;
}light_ctl_temperature_server_t;

#endif

