#ifndef GENERIC_ONOFF_CLIENT_API__H
#define GENERIC_ONOFF_CLIENT_API__H
#include <stdint.h>
#include "mesh_model.h"
#include "mesh_env.h"

enum GENERIC_ONOFF_CLIENT_EVENT_TYPE
{
	GENERIC_ONOFF_STATUS  = 0x01,
	GENERIC_ONOFF_DEFAULT_STATUS  = 0x02,
	GENERIC_ONOFF_SET,
	GENERIC_ONOFF_SET_UNACKNOWLEGED,
};


void generic_onoff_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);


#endif 


