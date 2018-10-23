#ifndef JMESH_GATT_CALLBACK_H
#define JMESH_GATT_CALLBACK_H


void jmesh_gatt_connected_callback(unsigned char* mac,unsigned char id);
void jmesh_gatt_disconnected_callback(unsigned char id);

void jmesh_gatt_recv_callback(unsigned char id,unsigned short instance,unsigned short length,unsigned char* data);

#endif
