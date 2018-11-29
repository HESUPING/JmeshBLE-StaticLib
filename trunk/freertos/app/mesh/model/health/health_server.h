#ifndef HEARTH_SERVER__H
#define HEARTH_SERVER__H
#include "mesh_env.h"
#include "mesh_model.h"
#include "stdint.h"

#define  HEALTH_FAULT_NUM_MAX 20
#define FAST_PERIOD_DIVISOR_MAX  15
typedef void (*health_server_selftest_cb_t)(uint16_t company_id, uint8_t test_id);


typedef void (*health_server_attention_cb_t)(const health_server_t * p_health_server, bool attention_state);

typedef struct
{
	uint8_t fault[HEALTH_FAULT_NUM_MAX];
	uint8_t top;
}health_server_fault_arr_t;

       



typedef struct 
{
	mesh_elmt_t *elmt_buf;
	model_base_t *model;
	uint8_t                         fast_period_divisor;
	publish_period_t 				health_publish_time;
	health_server_selftest_cb_t 	selftest_handler;
	uint8_t previous_test_id;
	uint16_t company_id;
	health_server_fault_arr_t      	 registered_faults;
	health_server_fault_arr_t      	 current_faults;
	health_server_attention_cb_t     attention_handler;    
    uint8_t                          attention_timer;       
}health_server_t;

 


//user interfence
void user_health_server_publish_period_set(health_server_t * p_server);

void user_health_server_attention_set(health_server_t * p_server, uint8_t attention);

uint8_t user_health_server_attention_get(const health_server_t * p_server);

uint32_t health_server_init(health_server_t *p_health_server);
								

      
#endif


