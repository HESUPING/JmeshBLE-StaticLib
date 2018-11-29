#ifndef LIGHT_CTL_SETUP__H
#define LIGHT_CTL_SETUP__H

#include "light_ctl_server.h"
#include "mesh_env.h"
#include "mesh_model.h"


enum LIGHT_CTL_STATUS_CODE
{
	ST_LIGHT_CTL_SUCCESS  = 0x0,
	ST_LIGHT_CTL_MIN_INVALID = 0x1,
	ST_LIGHT_CTL_MAX_INVALID = 0x02,
};
typedef struct
{
	model_server_base_t model;
	light_ctl_server_t *light_ctl_server;
}light_ctl_setup_server_t;
#endif

