#ifndef REALCOMM_SERVER_CALLBACK_H
#define REALCOMM_SERVER_CALLBACK_H
#include"../../driver/jmesh_uart.h"

void realcomm_server_init_callback(void);

int realcomm_server_config_callback(unsigned short baud,unsigned char parity);
void realcomm_server_trans_callback(unsigned char length,unsigned char* data);
#endif // REALCOMM_SERVER_CALLBACK_H
