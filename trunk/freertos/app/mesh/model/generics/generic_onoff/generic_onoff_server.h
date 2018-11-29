#ifndef GENERIC_ONOFF_SERVER_H_
#define GENERIC_ONOFF_SERVER_H_
#include <stdint.h>
#include "mesh_model.h"
#include "mesh_env.h"
#include "osapp_config.h"
#include "generic_common.h"
#include "model_servers_events_api.h"

#define GENERCI_ONOFF_BOUND_HANDLER_MAX 5




typedef void(*user_generic_onoff_server_cb)(access_pdu_tx_t *,uint8_t);


typedef struct
{
	void *inst;
	uint8_t onoff;
}ger_onoff_server_bound_data_t;


typedef struct
{
	uint8_t type;
	mesh_state_bound_cb_t handler;
	void *inst;
	uint16_t peer_level_state_min;
	uint16_t peer_level_state_max;
	uint16_t peer_level_state;
}ger_onoff_server_state_info_t;

//generic onoff server
typedef struct
{
	void *inst;
	uint8_t targe;
	uint8_t trans_time;
	uint8_t timer_index;
}ger_onoff_delay_parma_t;


typedef struct
{ 
	TimerHandle_t Timer[GENERIC_TIMER_MAX];
	ger_onoff_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
	TimerHandle_t trans_timer;
	uint16_t mask;
}ger_onoff_delay_timer_t;

typedef struct
{
	mesh_state_bound_cb_t state_bound_cb[GENERCI_ONOFF_BOUND_HANDLER_MAX];
	void *inst[GENERCI_ONOFF_BOUND_HANDLER_MAX];
	uint8_t type[GENERCI_ONOFF_BOUND_HANDLER_MAX];
	ger_onoff_server_state_info_t info;
	uint8_t bound_mask;
	
}ger_onoff_server_bound_inst_t;


typedef struct
{
	uint8_t present_onoff;
	uint8_t target_onoff;
	uint8_t remaining_time;
}generic_onoff_msg_format_t;





typedef struct
{
	model_server_base_t model;
	ger_onoff_server_bound_inst_t state_bound;
	generic_onoff_msg_format_t message_format;	
	generic_valid_field_queue_t onoff_queue;    //messages in 6 sec , judge tid
	ger_onoff_delay_timer_t delay_timer;        //5ms * p_pdu->delay timer
	mesh_model_evt_cb_t cb;
	uint8_t server_state;
}generic_onoff_server_t;



void generic_onoff_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_onoff_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_onoff_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_onoff_status_tx(generic_onoff_server_t *server,uint16_t dst_addr);



uint32_t generic_onoff_server_state_bound_req(generic_onoff_server_t *server,ger_onoff_server_state_info_t *state_info);

uint32_t generic_onoff_server_state_bound_change(generic_onoff_server_t *server,uint8_t type,uint8_t state_type,void *arg);

uint32_t generic_onoff_server_state_bound_event(uint8_t type,uint8_t state_type,void *arg);



#endif


