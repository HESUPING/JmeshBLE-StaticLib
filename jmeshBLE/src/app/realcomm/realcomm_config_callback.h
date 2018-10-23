#ifndef REALCOMM_CONFIG_CALLBACK_H
#define REALCOMM_CONFIG_CALLBACK_H


void realcomm_config_client_status_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned short addr);
void realcomm_config_server_status_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned short baud,unsigned char parity);


#endif // REALCOMM_CONFIG_CALLBACK_H
