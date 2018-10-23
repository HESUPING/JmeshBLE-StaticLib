#ifndef JMESH_PROVISIONING_SERVER_H
#define JMESH_PROVISIONING_SERVER_H
#include"stdint.h"


void network_light_indicate_init();

extern  uint16_t gatt_provisioning_server_handlers(uint8_t* dat, uint8_t* dat_out);



#endif // JMESH_PROVISIONING_SERVER_H
