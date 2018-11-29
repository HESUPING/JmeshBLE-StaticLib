#ifndef LIGHT_LIGHTNESS_SERVER__H
#define LIGHT_LIGHTNESS_SERVER__H

#include "mesh_env.h"
#include "mesh_model.h"

enum INST_PARMA_MASK
{
	LINEAR_QUEUE = 0x0,
	LIGHTNESS_QUEUE ,
	MSG_LIGHT_LIGHTNESS_SET,
	MSG_LIGHT_LIGHTNESS_LINEAR_SET,
};

//generic onoff server
typedef struct
{
	void *inst;
	uint16_t targe_lightness;
	uint8_t trans_time;
	uint8_t timer_index;
}li_lightness_delay_parma_t;

typedef struct
{ 
	TimerHandle_t Timer[GENERIC_TIMER_MAX];
	li_lightness_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
	TimerHandle_t trans_timer;
	uint16_t mask;
}li_lightness_delay_timer_t;

typedef struct
{
	uint16_t pre_lightness_linear;
	uint16_t tar_lightness_linear;
	uint8_t linear_remaining_time;
	
	uint16_t pre_lightness_actual;
	uint16_t tar_lightness_actual;
	uint8_t actual_remaining_time;
	
	uint16_t lightness_last;
	
	uint16_t lightness_default;
	
	uint8_t status_code;
	uint16_t range_min;
	uint16_t range_max;	
}light_lightness_msg_format_t;


typedef struct
{
	model_server_base_t model;
	light_lightness_msg_format_t msg_format;
	generic_valid_field_queue_t linear_queue;
	generic_valid_field_queue_t lightness_queue;
	li_lightness_delay_timer_t delay_timer;
	uint8_t server_state;
}light_lightness_server_t;


#endif