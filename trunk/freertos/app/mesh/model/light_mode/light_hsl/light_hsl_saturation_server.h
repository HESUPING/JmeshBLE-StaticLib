#ifndef LIGHT_HSL_SATURATION_SERVERT
#define LIGHT_HSL_SATURATION_SERVERT



typedef struct
{
	void *inst;
	uint16_t target_hsl_saturation;
	uint8_t trans_time;
	uint8_t timer_index;
}light_hsl_saturation_delay_parma_t;




typedef struct
{ 
	TimerHandle_t Timer[GENERIC_TIMER_MAX];
	light_hsl_saturation_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
	TimerHandle_t trans_timer;
	uint16_t mask;
}light_hsl_saturation_delay_timer_t;




typedef struct
{
	model_server_base_t model;
	light_hsl_server_t *light_hsl_server;
	generic_valid_field_queue_t hsl_saturation_queue;
	light_hsl_saturation_delay_timer_t delay_timer;
	user_mesh_callback cb;
	uint32_t trans_tick_start;
	uint8_t server_state;
}light_hsl_saturation_server_t;



#endif