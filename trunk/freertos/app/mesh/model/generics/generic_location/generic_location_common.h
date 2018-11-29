#ifndef GENERIC_LOCATION_COMMON__H
#define	GENERIC_LOCATION_COMMON__H
#include <stdint.h>
#include <math.h>


typedef struct
{
	int32_t global_latitude;
	int32_t global_longitude;
	int16_t global_altitude;
}generic_loc_msg_global_set_t;

typedef struct
{
	int32_t global_latitude;
	int32_t global_longitude;
	int16_t global_altitude;
}generic_loc_msg_global_status_t;



typedef struct
{
	uint16_t local_north;
	uint16_t local_east;
	uint16_t local_altitude;
	uint8_t floor_num;
	uint16_t uncertainty;
}generic_loc_msg_local_set_t;

typedef struct
{
	uint16_t local_north;
	uint16_t local_east;
	uint16_t local_altitude;
	uint8_t floor_num;
	uint16_t uncertainty;
}generic_loc_msg_local_status_t;
#endif


