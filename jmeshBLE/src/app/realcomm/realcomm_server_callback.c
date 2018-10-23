#include"realcomm_config.h"
#include"realcomm_server_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"../../driver/jmesh_uart.h"
#include"../../jmesh/jmesh_save_define.h"
#include"../../jmesh/jmesh_save.h"
static struct{
    unsigned short baud;
    unsigned char parity;

}realcomm_para;
void realcomm_server_init_callback(void)
{
    realcomm_para.baud=REALCOMM_BAUD_9600;
    realcomm_para.parity=REALCOMM_PARITY_EVEN;
    //save read
}
int realcomm_server_config_callback(unsigned short baud,unsigned char parity)
{
    print_info("realcomm set baud %d\n",baud);
    realcomm_para.baud=baud;
    realcomm_para.parity=parity;
		jmesh_uart_baudrate_set(baud);
		
//		switch(baud)
//		{
//			case 1200:
//				jmesh_uart_init(JMESH_UART_0, JMESH_UART_BAUD_1200, realcomm_para.parity,JMESH_UART_STOP_BITS_1);
//				break;
//			case 2400:
//				jmesh_uart_init(JMESH_UART_0, JMESH_UART_BAUD_2400, realcomm_para.parity,JMESH_UART_STOP_BITS_1);
//				break;
//			case 4800:
//				jmesh_uart_init(JMESH_UART_0, JMESH_UART_BAUD_4800, realcomm_para.parity,JMESH_UART_STOP_BITS_1);
//				break;
//			case 9600:
//				jmesh_uart_init(JMESH_UART_0, JMESH_UART_BAUD_9600, realcomm_para.parity,JMESH_UART_STOP_BITS_1);
//				break;
//			default:
//				print_info("invalid baudrate:current only can be 1200 2400 4800 9600!\n");
//				break;
//		}
//		jmesh_uart_init(JMESH_UART_0, JMESH_UART_BAUD_T baud, JMESH_UART_PARITY_T parity,JMESH_UART_STOP_BITS_T stop_bits);
		jmesh_save_write(JMESH_SAVE_BAUTRATE,sizeof(unsigned long),(unsigned char*)&realcomm_para.baud);
    //save write
    return 1;
}
void realcomm_server_trans_callback(unsigned char length,unsigned char* data)
{
    print_buffer_info(length,data,"realcomm recv from client:");
		jmesh_uart_send(JMESH_UART_0, length, data);
    //send to uart
}
