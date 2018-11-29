#ifndef GENERIC_POWER_LEVEL_SERVER__H
#define GENERIC_POWER_LEVEL_SERVER__H
#include "mesh_env.h"
#include "mesh_model.h"
#include "generic_power_level_common.h"

typedef struct
{
	mesh_elmt_t *elmt_buf;
	model_base_t *model;
	uint16_t generic_power_actual_present;
	uint16_t generic_power_actual_target;
	uint16_t generic_power_last;//used as a default value
	uint16_t generic_power_default;//0 represent generic_power_last as a default value
	uint16_t generic_power_range_min;
	uint16_t generic_power_range_max;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
	
}generic_power_level_server_t;
#endif


