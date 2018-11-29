#ifndef LIGHT_HSL_SETUP_SERVER__H
#define LIGHT_HSL_SETUP_SERVER__H
enum LIGHT_CTL_STATUS_CODE
{
	ST_LIGHT_HSL_SUCCESS  = 0x0,
	ST_LIGHT_HSL_MIN_INVALID = 0x1,
	ST_LIGHT_HSL_MAX_INVALID = 0x02,
};

typedef struct
{
	model_server_base_t model;
	light_hsl_server_t *light_hsl_server;
}light_hsl_setup_server_t;


#endif
