#ifndef GENERIC_ONOFF_COMMON__H
#define GENERIC_ONOFF_COMMON__H
#include "stdint.h"
typedef struct
{
	uint8_t onoff;
	uint8_t tid;
	uint8_t trans_time;
	uint8_t delay;
}__attribute((packed))generic_onoff_msg_set_t;

typedef struct
{
	uint8_t onoff;
	uint8_t tid;
}__attribute((packed))generic_onoff_msg_default_set_t;


typedef struct
{
	uint8_t present_onoff;
	uint8_t target_onoff;
	uint8_t remaining_time;
}__attribute((packed))generic_onoff_msg_state_t;

typedef struct
{
	uint8_t present_onoff;
}__attribute((packed))generic_onoff_msg_default_state_t;
#endif


