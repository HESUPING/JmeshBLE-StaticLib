#include"realcomm_config_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"../../driver/jmesh_uart.h"

void realcomm_config_client_status_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned short addr)
{
    print_info("realcomm config server callback");
}
void realcomm_config_server_status_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char baud,unsigned char parity)
{
    print_info("realcomm config client callback\n");
}
