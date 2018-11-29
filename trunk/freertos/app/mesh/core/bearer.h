#ifndef BEARER_H_
#define BEARER_H_
#include <stdint.h>
#include <stdbool.h>
#include "osapp_mesh.h"

#define DATA_OFFSET_IN_BEARER 2
#define BEARER_BUF_SIZE (ADV_DATA_BUF_SIZE - 2) 

uint8_t *bearer_get_data_buffer(mesh_adv_type_t type);
void mesh_flush_beacon_msg_cache(void);
void bearer_tx(uint8_t mesh_ad_type,uint8_t *buf,uint8_t length,void (*callback)());
void bearer_rx(uint8_t ad_type,uint8_t *data,uint8_t data_len);



#endif

