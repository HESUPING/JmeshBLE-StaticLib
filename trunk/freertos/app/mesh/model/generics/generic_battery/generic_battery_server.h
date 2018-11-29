#ifndef GENERIC_BATTERY_SERVER__H
#define GENERIC_BATTERY_SERVER__H
#include <stdint.h>
#include "mesh_env.h"
#include "mesh_model.h"
#include "generic_power_level_common.h"

typedef struct
{
	uint8_t ger_bat_f_pres : 2;
	uint8_t ger_bat_f_ind : 2;
	uint8_t ger_bat_f_chr : 2;
	uint8_t ger_bat_f_ser : 2;

}generic_battery_flag;


typedef struct
{
	mesh_elmt_t *elmt_buf;
	model_base_t *model;
	uint32_t time_discharge;
	uint32_t time_charge;
	uint8_t generic_battery_level;
	generic_battery_flag flag;
	
}generic_battery_server_t;

void generic_battery_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size);

uint32_t generic_battery_server_init(generic_battery_server_t *server);
#endif


