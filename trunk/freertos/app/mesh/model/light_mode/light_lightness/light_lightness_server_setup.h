#ifndef LIGHT_LIGHTNESS_SERVER_SETUP__H
#define	LIGHT_LIGHTNESS_SERVER_SETUP__H

#include "mesh_env.h"
#include "mesh_model.h"
#include "light_lightness_server.h"

enum LIGHT_LIGHTNESS_STATUS_CODE
{
	ST_LIGHT_SUCCESS  = 0x0,
	ST_LIGHT_MIN_INVALID = 0x1,
	ST_LIGHT_MAX_INVALID = 0x02,
};

typedef struct
{
	model_server_base_t model;
	light_lightness_server_t *light_lightness_server;
}light_lightness_setup_server_t;

#endif




