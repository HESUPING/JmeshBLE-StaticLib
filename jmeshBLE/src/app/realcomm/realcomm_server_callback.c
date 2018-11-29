#include"realcomm_config.h"
#include"realcomm_server_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"../../driver/jmesh_uart.h"
#include"../../jmesh/jmesh_save_define.h"
#include"../../jmesh/jmesh_save.h"
static struct{
    unsigned char baud;
    unsigned char parity;
}realcomm_para;

void realcomm_server_init_callback(void)
{
    realcomm_para.parity=REALCOMM_PARITY_EVEN;
	jmesh_save_read(JMESH_SAVE_BAUTRATE,sizeof(unsigned char),(unsigned char*)&realcomm_para.baud);
	if(!realcomm_para.baud) return;
	realcomm_para.baud--;
	jmesh_uart_baudrate_set(enum_to_baudrate(realcomm_para.baud));
}

int realcomm_server_config_callback(unsigned char baud,unsigned char parity)
{
	print_info("realcomm set baud %d\n",baud);
    realcomm_para.baud=baud;
    realcomm_para.parity=parity;
		unsigned long baudrate = 0;
		switch(realcomm_para.baud)
		{
			case JMESH_UART_BAUD_1200 :
				baudrate = 1200;
				break;
			case JMESH_UART_BAUD_2400 :
				baudrate = 2400;
				break;
			case JMESH_UART_BAUD_4800:
				baudrate = 4800;
				break;
			case JMESH_UART_BAUD_9600:
				baudrate = 9600;
				break;
			case JMESH_UART_BAUD_19200:
				baudrate = 19200;
				break;
			case JMESH_UART_BAUD_38400:
				baudrate = 38400;
				break;		
			case JMESH_UART_BAUD_115200:
				baudrate = 115200;
				break;					
			default :
				return -1;
		}
		jmesh_uart_baudrate_set(baudrate);
    return 0;
}
void realcomm_server_trans_callback(unsigned char length,unsigned char* data)
{
//    print_buffer_info(length,data,"realcomm recv from client:");
		jmesh_uart_send(JMESH_UART_0, length, data);
    //send to uart
}
