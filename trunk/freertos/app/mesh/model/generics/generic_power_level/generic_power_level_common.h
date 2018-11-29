#ifndef GENERIC_POWER_LEVEL_COMMON__H
#define GENERIC_POWER_LEVEL_COMMON__H

typedef struct
{
	uint16_t power;
	uint8_t tid;
}__attribute((packed))generic_msg_power_level_default_t;

typedef struct
{
	uint16_t power;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))generic_msg_power_level_set_t;


typedef struct
{
	uint16_t present_power;
	uint16_t target_power;
	uint8_t remaining_time;
}__attribute((packed))generic_msg_power_level_status_t;


typedef struct
{
	uint16_t power;
}__attribute((packed))generic_msg_power_last_status_t;

typedef struct
{
	uint16_t power;
}__attribute((packed))generic_msg_power_default_set_t;

typedef struct
{
	uint16_t power;
}__attribute((packed))generic_msg_power_default_status_t;


typedef struct
{
	uint16_t min;
	uint16_t max;
}__attribute((packed))generic_msg_power_range_set_t;


typedef struct
{
	uint8_t status_code;
	uint16_t min;
	uint16_t max;
}__attribute((packed))generic_msg_power_range_set_t;
#endif


