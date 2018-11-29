#ifndef GENERIC_LEVEL_SERVER__H
#define	GENERIC_LEVEL_SERVER__H
#include <stdint.h>
#include "mesh_env.h"
#include "mesh_model.h"
#include "generic_common.h"
#define GENERCI_LEVEL_BOUND_HANDLER_MAX 5

enum 
{
	MSG_GENERCI_LEVEL_SET,
	MSG_GENERCI_DELTA_SET,
	MSG_GENERCI_MOVE_SET
};

typedef struct
{
	void *inst;
	uint16_t level;
}ger_level_server_bound_data_t;



typedef struct
{
	uint8_t type;
	mesh_state_bound_cb_t handler;
	void *inst;
	uint16_t peer_level_state_min;
	uint16_t peer_level_state_max;
	uint16_t peer_level_state;
}ger_level_server_state_info_t;


typedef struct
{
	mesh_state_bound_cb_t state_bound_cb[GENERCI_LEVEL_BOUND_HANDLER_MAX];
	void *inst[GENERCI_LEVEL_BOUND_HANDLER_MAX];
	uint8_t type[GENERCI_LEVEL_BOUND_HANDLER_MAX];
	ger_level_server_state_info_t info;
	uint8_t bound_mask;
}ger_level_server_state_inst_t;


typedef struct
{
	uint16_t present_level; 
	uint16_t target_level;
	uint8_t remaining_time;
}generic_level_msg_format_t;



typedef struct
{
    void *inst;
    int32_t target_level;
    uint8_t trans_time;
    uint8_t timer_index;
    uint8_t type;
}ger_level_delay_parma_t;

typedef struct
{
    TimerHandle_t Timer[GENERIC_TIMER_MAX];
    ger_level_delay_parma_t delay_parma[GENERIC_TIMER_MAX];
    TimerHandle_t trans_timer;
    uint16_t mask;
}ger_level_delay_timer_t;

typedef struct
{
	model_server_base_t model;
	ger_level_server_state_inst_t state_bound;
	generic_level_msg_format_t msg_format;
	generic_valid_field_queue_t level_queue;
	generic_valid_field_queue_t delta_queue;
	generic_valid_field_queue_t move_queue;
	ger_level_delay_timer_t delay_timer;
	uint8_t server_state;
	uint16_t upper_limit_level;
	uint16_t lower_limit_level;
}ger_level_server_t;


uint32_t generic_le_server_state_bound_change(ger_level_server_t *server,uint8_t type,uint8_t state_type,void *arg);
uint32_t generic_level_server_state_bound_req(ger_level_server_t *server,ger_level_server_state_info_t *state_info);
uint32_t generic_level_server_state_bound_event(uint8_t type,uint8_t state_type,void *arg);


void generic_level_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_level_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_level_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_delta_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);

void generic_delta_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_move_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_move_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
uint32_t generic_level_server_init(ger_level_server_t *server);
#endif


