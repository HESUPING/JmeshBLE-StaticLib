#ifndef GENERIC_ONPOWERUP_SERVER__H
#define GENERIC_ONPOWERUP_SERVER__H
#include <stdint.h>
#include "mesh_env.h"
#include "mesh_model.h"
enum 
{
	GENERIC_POWER_ON = 0x00,
	GENERIC_POWER_OFF = 0x01,
	GENERIC_POWER_RESTORE = 0x02,
};

typedef struct
{
	mesh_elmt_t *elmt_buf;
	model_base_t *model;

}generic_onpowerup_server_t;


uint32_t generic_onpowerup_server_init(generic_onpowerup_server_t *server);
#endif


