#include"meter_server.h"
#include"meter_client.h"
#include"protocol_645.h"
#include"meter_server_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"../../driver/jmesh_uart.h"
#include"stdint.h"
#include"stdlib.h"
static uint8_t protocol_645_addr[6] ={0};
int meter_server_addr_get_callback(uint8_t* data,uint8_t len)
{
    uint8_t get_645_addr[]={0x68,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0x68,0x13,0x00,0xdf,0x16};
		jmesh_uart_send(JMESH_UART_0, sizeof(get_645_addr),get_645_addr);
    return 0;	
}

const uint8_t protocol_energy_di[4]={0x00,0x00,0x00,0x00};

//68 aa aa aa aaa aa aa 68 11 04 33 33 34 33 cs 16
int meter_server_energy_get_callback(uint8_t* data,uint8_t len)
{
    uint8_t buffer[16];
    uint8_t ret=protocol_64507_pack(protocol_645_addr,(unsigned char*)protocol_energy_di,0x11,0,NULL,16,buffer);
		jmesh_uart_send(JMESH_UART_0, ret, buffer);
    return 0;
}
const uint8_t protocol_voltage_di[4]={0x00,0x01,0x01,0x02};

int meter_server_voltage_get_callback(uint8_t* data,uint8_t len)
{
    uint8_t buffer[16];
    uint8_t ret=protocol_64507_pack(protocol_645_addr,(unsigned char*)protocol_voltage_di,0x11,0,NULL,16,buffer);
    jmesh_uart_send(JMESH_UART_0,ret,buffer);
    return 0;
}

int meter_server_pdu_get_callback(uint8_t* data,uint8_t len)
{
    uint8_t buffer[16];
    uint8_t ret=protocol_64507_pack(protocol_645_addr,data,0x11,0,NULL,16,buffer);
    jmesh_uart_send(JMESH_UART_0,ret,buffer);
    return 0;
}
