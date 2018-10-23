#ifndef JMESH_PROVISIONING_CLIENT_H
#define JMESH_PROVISIONING_CLIENT_H
#include"stdint.h"

uint8_t  gatt_provisioning_device(uint8_t* dat_out);
uint16_t gatt_provisioning_client_handlers(uint8_t* dat_in, uint8_t* dat_out);
void jmesh_provisioning_connected(unsigned char* mac,unsigned short connect_id);
extern void jmesh_create_net(unsigned short nid,unsigned char* netkey,unsigned char* devkey,unsigned short primary_address);
extern void jmesh_provisioning_device(unsigned char* mac,unsigned short primary_address);
int jmesh_provisioning_client_process(unsigned char connect,unsigned char in_len,unsigned char * in_data,
                                      unsigned char out_len,unsigned char* out_buffer);


extern void driver_provisioning_result(unsigned char* mac,unsigned short addr,int status,unsigned char elements,unsigned char* devkey);

#endif // JMESH_PROVISIONING_H
