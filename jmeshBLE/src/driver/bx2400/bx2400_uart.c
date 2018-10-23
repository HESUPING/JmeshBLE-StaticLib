#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"../jmesh_uart.h"
#include"../../onchip_system/os_timer_event.h"
#include"stdio.h"
#include "../../../../trunk/plf/peripheral/app_uart/app_uart.h"
#include"../jmesh_uart_callback.h"
#include"string.h"
#include"osapp_config.h"

#define UART_CACHE_BUFFER_SIZE 150
#define UART_RECV_INTERVAL_TIMEOUT_MS 50
static app_uart_inst_t uart0=UART_INSTANCE(0);
static app_uart_inst_t uart1=UART_INSTANCE(1);
typedef struct {
    unsigned char dat[UART_CACHE_BUFFER_SIZE];
    unsigned char len;
}common_dat_t;


static os_timer_event_t os_uart0_timer;
static os_timer_event_t os_uart1_timer;

static common_dat_t uart_data[2];

static void os_uart0_read_callback(void* buffer,unsigned char length);
static void os_uart1_read_callback(void* buffer,unsigned char length);

static void os_uart0_timer_handler(os_data_t data)
{
    os_timer_event_restart(&os_uart0_timer);
    if(uart_data[0].len!=0)
    {
        jmesh_uart_recv_callback(JMESH_UART_0,uart_data[0].len,uart_data[0].dat);
        memset(&uart_data[0],0,sizeof(common_dat_t));
        app_uart_read(&uart0.inst,uart_data[0].dat,1,os_uart0_read_callback,NULL);
    }
}


static void os_uart1_timer_handler(os_data_t data)
{
    os_timer_event_restart(&os_uart1_timer);
    if(uart_data[1].len!=0)
    {
        jmesh_uart_recv_callback(JMESH_UART_1,uart_data[1].len,uart_data[1].dat);
        memset(&uart_data[1],0,sizeof(common_dat_t));
        app_uart_read(&uart1.inst,uart_data[1].dat,1,os_uart1_read_callback,NULL);
    }
}

static void os_uart0_read_callback(void* buffer,unsigned char length)
{
    os_timer_event_restart(&os_uart0_timer);
    uart_data[0].len++;
    if(uart_data[0].len>=UART_CACHE_BUFFER_SIZE)
    {
        os_uart0_timer_handler(NULL);
        return;
    }
    app_uart_read(&uart0.inst,uart_data[0].dat+uart_data[0].len,1,os_uart0_read_callback,NULL);
}

static void os_uart1_read_callback(void* buffer,unsigned char length)
{
    os_timer_event_restart(&os_uart1_timer);
    uart_data[1].len++;
    if(uart_data[1].len>=UART_CACHE_BUFFER_SIZE)
    {
        os_uart1_timer_handler(NULL);
        return;
    }
    app_uart_read(&uart1.inst,uart_data[1].dat+uart_data[1].len,1,os_uart1_read_callback,NULL);
}

void jmesh_uart_init(JMESH_UART_NAME_T uart, JMESH_UART_BAUD_T baud, JMESH_UART_PARITY_T parity,JMESH_UART_STOP_BITS_T stop_bits){
    app_uart_inst_t *uart_inst;
    switch(uart)
    {
        case JMESH_UART_0:
            uart_inst=&uart0;

            uart_inst->param.rx_pin_no = 13;
            uart_inst->param.tx_pin_no = 12;
            //uart_inst->param.rts_pin_no = 20;
            //uart_inst->param.cts_pin_no = 21;
            break;
        case JMESH_UART_1:
            uart_inst=&uart1;
            uart_inst->param.rx_pin_no = 13;
            uart_inst->param.tx_pin_no = 12;
            //uart_inst->param.rts_pin_no = 20;
            //uart_inst->param.cts_pin_no = 21;
            break;
        default:
            return;
    }
    switch(baud)
    {
        case JMESH_UART_BAUD_1200:
            uart_inst->param.baud_rate = UART_BAUDRATE_1200;
            break;
        case JMESH_UART_BAUD_2400:
            uart_inst->param.baud_rate = UART_BAUDRATE_2400;
            break;
        case JMESH_UART_BAUD_4800:
            uart_inst->param.baud_rate = UART_BAUDRATE_4800;
            break;
        case JMESH_UART_BAUD_9600:
            uart_inst->param.baud_rate = UART_BAUDRATE_9600;
            break;
        case JMESH_UART_BAUD_19200:
            uart_inst->param.baud_rate = UART_BAUDRATE_19200;
            break;
        case JMESH_UART_BAUD_38400:
            uart_inst->param.baud_rate = UART_BAUDRATE_38400;
            break;
        case JMESH_UART_BAUD_115200:
            uart_inst->param.baud_rate = UART_BAUDRATE_115200;
            break;
        default:
            return;
    }
    switch(parity)
    {
        case JMESH_UART_PARITY_EVEN:
            uart_inst->param.parity_en = 1;
						uart0.param.even_parity = 1;
            break;
				case JMESH_UART_PARITY_ODD :
            uart_inst->param.parity_en = 1;
						uart0.param.even_parity = 0;						
						break;
        case JMESH_UART_PARITY_NONE:
            uart_inst->param.parity_en = 0;
            break;
        default:
            return;
    }
    uart_inst->param.flow_control_en = 0;
    uart_inst->param.auto_flow_control = 1;
    uart_inst->param.tx_dma = 0;
    uart_inst->param.rx_dma = 0;
    app_uart_init(&uart_inst->inst);
		jmesh_uart_start(uart);		
}


void jmesh_uart_start(JMESH_UART_NAME_T uart){
    switch(uart)
    {
        case JMESH_UART_0:
            app_uart_read(&uart0.inst,uart_data[0].dat,1,os_uart0_read_callback,NULL);
            os_timer_event_set(&os_uart0_timer,UART_RECV_INTERVAL_TIMEOUT_MS ,os_uart0_timer_handler,NULL);
            break;
        case JMESH_UART_1:
            app_uart_read(&uart1.inst,uart_data[1].dat,1,os_uart1_read_callback,NULL);
            os_timer_event_set(&os_uart1_timer,UART_RECV_INTERVAL_TIMEOUT_MS,os_uart1_timer_handler,NULL);
            break;
        default:
            return;
    }
}

void jmesh_uart_stop(JMESH_UART_NAME_T uart){
    switch(uart)
    {
        case JMESH_UART_0:
            app_uart_uninit(&uart0.inst);
            break;
        case JMESH_UART_1:
            app_uart_uninit(&uart1.inst);
            break;
        default:
            return;
    }
}

void jmesh_uart_send(JMESH_UART_NAME_T uart, unsigned short length, unsigned char *data){
    switch(uart)
    {
        case JMESH_UART_0:
            app_uart_write(&uart0.inst,data,length,(void (*) (void*,uint8_t))jmesh_uart0_send_callback,NULL);
            break;
        case JMESH_UART_1:
            app_uart_write(&uart1.inst,data,length,(void (*) (void*,uint8_t))jmesh_uart1_send_callback,NULL);
            break;
				case JMESH_RTT_LOG :
						rtt_log(LOG_LVL_INFO,(const char*)data);
					break;
        default:
            return;
    }
//    uart0_send_over=0;
//    for(int i=0;i<50;i++)
//    {
//        vTaskDelay(1);
//        if(uart0_send_over)
//        {
//            return;
//        }
//    }
}

int jmesh_uart_baudrate_set(unsigned long baudrate)
{
			switch(baudrate)
			{
				case 1200 :
						uart_set_divisor(uart0.reg,(uint16_t)UART_BAUDRATE_1200&0x3ff);
				break;
				case 2400 :
						uart_set_divisor(uart0.reg,(uint16_t)UART_BAUDRATE_2400&0x3ff);
					break;
				case 4800 :
						uart_set_divisor(uart0.reg,(uint16_t)UART_BAUDRATE_4800&0x3ff);
					break;
				case 9600 :
						uart_set_divisor(uart0.reg,(uint16_t)UART_BAUDRATE_9600&0x3ff);
					break;
				default :
						return -1;
			}
			return baudrate;
}
#endif
