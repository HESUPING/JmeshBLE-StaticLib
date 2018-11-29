#ifndef GENERIC_DEFAULT_TRANSITION_TIME
#define	GENERIC_DEFAULT_TRANSITION_TIME

#include <stdint.h>
#include "mesh_env.h"
#include "mesh_model.h"

typedef struct
{
	model_server_base_t model;
	uint8_t trans_time;
}ger_default_trans_time_server_t;

void generic_default_transition_time_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_default_transition_time_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void generic_default_transition_time_unacknowledge_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);

//user interface
uint8_t user_generic_default_transition_time_get(ger_default_trans_time_server_t *server);

#endif


