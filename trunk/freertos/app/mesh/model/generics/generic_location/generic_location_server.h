#ifndef GENERIC_LOCATION_SERVER__H
#define GENERIC_LOCATION_SERVER__H
#include <stdint.h>
#include "mesh_env.h"
#include "mesh_model.h"
typedef struct
{
	mesh_elmt_t *elmt_buf;
	model_base_t *model;
}generic_location_server_t;


uint32_t generic_location_server_init(generic_location_server_t *server);
#endif


