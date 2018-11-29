#ifndef JMESH_PROVISIONING_SERVER_H
#define JMESH_PROVISIONING_SERVER_H
#include"stdint.h"
#include"../gatt/jmesh_gatt.h"

void network_light_indicate_init();

extern  uint16_t gatt_provisioning_server_handlers(uint8_t* dat, uint8_t* dat_out);


int jmesh_provision_recv_handler(jmesh_pdu_t* pdu);
int jmesh_provision_send_handler(jmesh_pdu_t* pdu);

#endif // JMESH_PROVISIONING_SERVER_H
