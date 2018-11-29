#ifndef LIGHT_CTL_COMMON__H
#define LIGHT_CTL_COMMON__H


typedef struct
{
	uint16_t ctl_lightness;
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}attribute((packed))msg_light_ctl_set_t;


typedef struct
{
	uint16_t ctl_lightness;
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
	uint8_t tid;
}attribute((packed))msg_light_ctl_lite_set_t;


typedef struct
{
	uint16_t ctl_lightness;
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}attribute((packed))msg_light_ctl_set_unacknowledged_t;


typedef struct
{
	uint16_t ctl_lightness;
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
	uint8_t tid;
}attribute((packed))msg_light_ctl_lite_set_unacknowledged_t;

typedef struct
{
	uint16_t present_ctl_lightness;
	uint16_t present_ctl_temperature;
	uint16_t target_ctl_lightness;
	uint16_t target_ctl_temperature;
	uint8_t remaining_time;
}attribute((packed))msg_light_ctl_status_t;

typedef struct
{
	uint16_t present_ctl_lightness;
	uint16_t present_ctl_temperature;
}attribute((packed))msg_light_ctl_lite_status_t;

typedef struct
{
	uint8_t status_code;
	uint16_t range_min;
	uint16_t range_max;
}attribute((packed))msg_light_ctl_temperature_range_status_t;

typedef struct
{
	uint16_t range_min;
	uint16_t range_max;
}attribute((packed))msg_light_ctl_temperature_range_set_t;

typedef struct
{
	uint16_t present_ctl_temperature;
	uint16_t present_ctl_delta_uv;
	uint16_t target_ctl_temperature;
	uint16_t target_ctl_delta_uv;
	uint8_t remaining_time;
}attribute((packed))msg_light_ctl_temperature_status_t;

typedef struct
{
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
	uint8_t tid;
	uint8_t transition_time;
	uint8_t delay;
}attribute((packed))msg_light_ctl_temperature_set_t;

typedef struct
{
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
	uint8_t tid;
}attribute((packed))msg_light_ctl_temperature_lite_set_t;

typedef struct
{
	uint16_t ctl_lightness;
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
}attribute((packed))msg_light_ctl_default_set_t;


typedef struct
{
	uint16_t ctl_lightness;
	uint16_t ctl_temperature;
	uint16_t ctl_delta_uv;
}attribute((packed))msg_light_ctl_default_status_t;
#endif

