#include"jmesh_uart_callback.h"
#include"../app/meter/protocol_645.h"
#include"../foundation/config/configuration_cmd.h"
#include"../jmesh/jmesh_print.h"
#include"../app/meter/meter_server.h"
#include"../app/realcomm/realcomm_client_callback.h"
#define UART_REALCOMM_ENABLE
void jmesh_uart_recv_callback(JMESH_UART_NAME_T uart,unsigned short len,unsigned char* data)
{
    protocol_645_timed_handler(data,len);
    configuration_cmd_process(len,data);
	
#ifdef UART_REALCOMM_ENABLE
		if(memcmp("AT+",data,3)==0) return ;
		realcomm_client_uart_recv_callback(len,data);
#endif
}

volatile unsigned char uart0_send_over=1;
void jmesh_uart0_send_callback(void)
{
    uart0_send_over=1;
}
void wait_uart_send_over(void)
{
    while(uart0_send_over==0);
    uart0_send_over=0;
}
void jmesh_uart1_send_callback(void)
{

}

