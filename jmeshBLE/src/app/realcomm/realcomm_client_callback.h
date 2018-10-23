#ifndef REALCOMM_CLIENT_CALLBACK_H
#define REALCOMM_CLIENT_CALLBACK_H

void realcomm_client_init_callback(void);
int realcomm_config_addr_get(void);
int realcomm_client_config_callback(unsigned short addr,unsigned short nid,unsigned short aid);
void realcomm_client_uart_recv_callback(unsigned char length,unsigned char* data);
#endif // REALCOMM_CLIENT_CALLBACK_H
