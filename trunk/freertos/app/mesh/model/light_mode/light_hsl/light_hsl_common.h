#ifndef LIGHT_HSL_COMMON__H
#define LIGHT_HSL_COMMON__H
typedef struct
{
	uint16_t hsl_lightness;
	uint16_t hsl_hue;
	uint16_t hsl_saturation;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))msg_light_hsl_set_t;


typedef struct
{
	uint16_t hsl_lightness;
	uint16_t hsl_hue;
	uint16_t hsl_saturation;
	uint8_t tid;
}__attribute((packed))msg_light_hsl_lite_set_t;

typedef struct
{
	uint16_t hsl_lightness;
	uint16_t hsl_hue;
	uint16_t hsl_saturation;
	uint8_t remaining_time;
}__attribute((packed))msg_light_hsl_status_t;

typedef struct
{
	uint16_t hsl_lightness;
	uint16_t hsl_hue;
	uint16_t hsl_saturation;
}__attribute((packed))msg_light_hsl_lite_status_t;


typedef struct
{
	uint16_t hsl_lightness_target;
	uint16_t hsl_hue_target;
	uint16_t hsl_saturation_target;
	uint8_t remaining_time;
}__attribute((packed))msg_light_hsl_target_status_t;

typedef struct
{
	uint16_t hsl_lightness_target;
	uint16_t hsl_hue_target;
	uint16_t hsl_saturation_target;
}__attribute((packed))msg_light_hsl_lite_target_status_t;

typedef struct
{
	uint16_t hue;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))msg_light_hsl_hue_set_t;

typedef struct
{
	uint16_t hue;
	uint8_t tid;
}__attribute((packed))msg_light_hsl_lite_hue_set_t;

typedef struct
{
	uint16_t present_hue;
	uint16_t target_hue;
	uint8_t remaining_time;

}__attribute((packed))msg_light_hsl_hue_status_t;


typedef struct
{
	uint16_t present_hue;

}__attribute((packed))msg_light_hsl_hue_lite_status_t;

typedef struct
{
	uint16_t saturation;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))msg_light_hsl_saturation_set_t;

typedef struct
{
	uint16_t saturation;
	uint8_t tid;
}__attribute((packed))msg_light_hsl_saturation_lite_set_t;

typedef struct
{
	uint16_t present_saturation;
	uint16_t target_saturation;
	uint8_t remaining_time;
}__attribute((packed))msg_light_hsl_saturation_status_t;


typedef struct
{
	uint16_t present_saturation;
}__attribute((packed))msg_light_hsl_saturation_lite_status_t;

typedef struct
{
	uint16_t lightness;
	uint16_t hue;
	uint16_t saturation;
}__attribute((packed))msg_light_hsl_default_set_t;

typedef struct
{
	uint16_t lightness;
	uint16_t hue;
	uint16_t saturation;
}__attribute((packed))msg_light_hsl_default_status_t;


typedef struct
{
	uint16_t hue_range_min;
	uint16_t hue_range_max;
	uint16_t saturation_range_min;
	uint16_t saturation_range_max;
}__attribute((packed))msg_light_hsl_range_set_t;



typedef struct
{
	uint8_t status_code;
	uint16_t hue_range_min;
	uint16_t hue_range_max;
	uint16_t saturation_range_min;
	uint16_t saturation_range_max;
}__attribute((packed))msg_light_hsl_range_status_t;
#endif
