#ifndef LIGHT_HSL_SERVER__H
#define LIGHT_HSL_SERVER__H

typedef struct
{
	void *inst;
	uint16_t target_hsl_lightness;
	uint16_t target_hsl_hue;
	uint16_t target_hsl_saturation;
	uint8_t trans_time;
	uint8_t timer_index;
}light_hsl_delay_parma_t;

typedef struct
{ 
	TimerHandle_t Timer[GENERIC_TIMER_MAX];
	light_hsl_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
	TimerHandle_t trans_timer;
	uint16_t mask;
}light_hsl_delay_timer_t;


typedef struct
{
	uint16_t present_hsl_lightness;
	uint16_t present_hsl_hue;
	uint16_t present_hsl_saturation;
	uint16_t target_hsl_lightness;
	uint16_t target_hsl_hue;
	uint16_t target_hsl_saturation;

	uint16_t default_hsl_lightness;
	uint16_t default_hsl_hue;
	uint16_t default_hsl_saturation;

	uint8_t status_code;
	uint16_t hue_range_min;
	uint16_t hue_range_max;
	uint16_t saturation_range_min;
	uint16_t saturation_range_max;
}light_hsl_msg_format_t;


typedef struct
{
	model_server_base_t model;
	light_hsl_msg_format_t msg_format;
	generic_valid_field_queue_t hsl_queue;
	light_hsl_delay_timer_t delay_timer;
	user_mesh_callback cb;
	uint32_t trans_tick_start;
	uint8_t server_state;
}light_hsl_server_t;

#endif
