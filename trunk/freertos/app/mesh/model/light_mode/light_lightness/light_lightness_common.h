#ifndef LIGHT_LIGHTNESS_COMMON__H
#define LIGHT_LIGHTNESS_COMMON__H

typedef struct
{
	uint16_t lightness;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))light_lightness_set_t;

typedef struct
{
	uint16_t lightness;
	uint8_t tid;
}__attribute((packed))light_lightness_lite_set_t;

typedef struct
{
	uint16_t present_lightness;
	uint16_t target_lightness;
	uint8_t remaining_time;
}__attribute((packed))light_lightness_status_t;

typedef struct
{
	uint16_t present_lightness;
}__attribute((packed))light_lightness_lite_status_t;

typedef struct
{
	uint16_t present_lightness;
	uint16_t target_lightness;
	uint8_t remaining_time;
}__attribute((packed))light_lightness_linear_status_t;
typedef struct
{
	uint16_t present_lightness;
	uint16_t target_lightness;
	uint8_t remaining_time;
}__attribute((packed))light_lightness_linear_lite_status_t;
typedef struct
{
	uint16_t lightness;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))light_lightness_linear_set_t;

typedef struct
{
	uint16_t lightness;
	uint8_t tid;
}__attribute((packed))light_lightness_linear_lite_set_t;

typedef struct
{
	uint16_t lightness;
}__attribute((packed))light_lightness_last_status_t;

typedef struct
{
	uint16_t lightness;
}__attribute((packed))light_lightness_default_set_t;

typedef struct
{
	uint16_t lightness;
}__attribute((packed))light_lightness_default_status_t;

typedef struct
{
	uint16_t range_min;
	uint16_t range_max;
}__attribute((packed))light_lightness_range_set_t;

typedef struct
{
	uint8_t status_code;
	uint16_t range_min;
	uint16_t range_max;
}__attribute((packed))light_lightness_range_status_t;

#endif

