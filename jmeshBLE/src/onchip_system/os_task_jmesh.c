#include "os_task_jmesh.h"
#if 0
//#include "../foundation/configuration_cmd.h"
#include"../network/jmesh_interface.h"
#include"os_memb.h"
//#include"../jmesh_print.h"
//#include"../driver/driver.h"
#include"../access/jmesh_access.h"

#define uart_read(a,b,c,d)

os_timer_event_t baudrate_timer;
static const unsigned int BpsItem[4]={1200,2400,4800,9600};

static os_timer_event_t os_uart_timer,uart_notify_timer;

static common_dat_t message;
OS_QUEUE_CREATE(uart_cache,sizeof(common_dat_t),UART_CACHE_SIZE)


int os_task_jmesh_app_light_handler(common_dat_t* data);
int os_task_jmesh_access_send_handler(jmesh_pdu_t* pdu);
int os_task_jmesh_bearer_read_handler(jmesh_interface_cache_t* cache);
int os_task_jmesh_protocol_645_handler(protocol_dat_t* protocol_dat);
int os_task_jmesh_uart_send_handler(common_dat_t* dat);
int os_task_jmesh_uart_read_handler(common_dat_t* dat);



static const os_event_handler_t handler_table[OS_TASK_JMESH_SIZE]={
    (os_event_handler_t)os_task_jmesh_app_light_handler,
    (os_event_handler_t)os_task_jmesh_access_send_handler,
    (os_event_handler_t)os_task_jmesh_bearer_read_handler,
    (os_event_handler_t)os_task_jmesh_protocol_645_handler,
    (os_event_handler_t)os_task_jmesh_uart_send_handler,
    (os_event_handler_t)os_task_jmesh_uart_read_handler,

};
#if(JMESH_NOTE_PRINTABLE==yes)
static char* event_info[OS_TASK_JMESH_SIZE]={
    "app light",
    "access send",
    "bearer read",
    "protocol 645",
    "uart send",
    "uart read"
};
#endif

int os_task_jmesh_app_light_handler(common_dat_t* dat)
{
    switch(dat->flag)
    {
        case APP_LIGHT_SET_FLAG :
            light_set_with_default(dat->dat[0],dat->dat[1]);
            break;
        case APP_LIGHT_GET_FLAG :
            light_get((dat->dat[0]<<8)+dat->dat[1],dat->dat[2]);
            break;
    }
    return 0;
}

int os_task_jmesh_access_send_handler(jmesh_pdu_t* pdu)
{
    jmesh_access_send_handler(pdu);
    return 0;
}

int os_task_jmesh_protocol_645_handler(protocol_dat_t* protocol_dat)
{
    unsigned short target = protocol_dat->target;
    unsigned char addr[6] ;//= {0x11,0x11,0x11,0x11,0x11,0x11};
    if(protocol_dat->flag ==PROTOCOL_645_GET_ADDR )
    {
        protocol_645_get_addr(protocol_dat->target);
    }else if(protocol_dat->flag == PROTOCOL_645_GET_ENERGY)
    {
        protocol_645_get_energy(target);

    }else if(protocol_dat->flag == PROTOCOL_645_GET_PDU)
    {

    }

    return 0;
}

int os_task_jmesh_bearer_read_handler(jmesh_interface_cache_t* cache)
{
    jmesh_network_read(cache->interface,cache->pdu);
    os_memb_free(interface_cache_memb,cache);
    return 0;
}
void os_uart_write_callback(void* buffer,unsigned char length)
{
}

int os_task_jmesh_uart_send_handler(common_dat_t* dat)
{
    driver_uart_send(UART_0,dat->len,dat->dat);
    return 0;
}
int os_task_jmesh_uart_read_handler(common_dat_t* dat)
{
    common_dat_t* uart_read_dat = os_queue_pop(uart_cache);
	  //jmeshs_send_notification(uart_read_dat->dat, uart_read_dat->len,JMESHS_IDX_MESH_SERIAL_TRANSMIT_VAL);  //send nofification to server by gatt

#ifdef LIGHT_GATEWAY
		jmesh_pdu_t pdu ;
		memcpy(pdu.pdu,uart_read_dat->dat,uart_read_dat->len);
		jmesh_network_read(JMESH_NETWORK_INTERFACE_ADV,&pdu);
#endif

#ifdef WATER_PROTOCOL_188_GATEWAY
		uart_water_protocol_188_handler(uart_read_dat->len,uart_read_dat->dat);
#endif

#ifdef ELECTRONIC_645_GATEWAY
		uart_protocol_645_handler(uart_read_dat->len,uart_read_dat->dat);
#endif

#ifdef SERIAL_TRANSPARENT_TRANSMISSION
		//uart_conditioner_serial_hadler(uart_read_dat->len,uart_read_dat->dat);
#endif
    jmesh_access_message_trigger(PROTOCOL_645_ADDR_GET,uart_read_dat->len,uart_read_dat->dat);
    jmesh_access_message_trigger(PROTOCOL_645_ENERGY_GET,uart_read_dat->len,uart_read_dat->dat);
    jmesh_access_message_trigger(PROTOCOL_645_PDU_GET,uart_read_dat->len,uart_read_dat->dat);

    configuration_cmd_process(uart_read_dat->len,uart_read_dat->dat);
    return 0;
}


int os_uart_read_callback(unsigned char* buffer)
{
    os_timer_event_restart(&os_uart_timer);
    message.len++;
    uart_read(message.dat+message.len,1,os_uart_read_callback,message.dat);
    if(message.len>=UART_CACHE_BUFFER_SIZE){
        os_uart_timer_handler(NULL);
    }
    return 0;
}

void os_uart_timer_handler(os_data_t data)
{
    if(message.len!=0)
    {
        os_queue_push(uart_cache,&message);
        os_event_post(&os_task_jmesh, OS_TASK_JMESH_UART_READ,uart_cache);
        memset(&message,0,sizeof(message));
        message.len=0;

 //       uart_read(message.dat, 1, os_uart_read_callback,message.dat);
    }
}
void baudrate_timer_handler(signed char* count)
{
  	(*count)--;
    if((*count)<0x00){
        os_timer_event_remove(&baudrate_timer);
        return;
    }
    os_timer_event_restart(&baudrate_timer);

    //protocol_645_addr_get_callback();

}


OS_TASK(os_task_jmesh,event,data)
{
    static signed char count = 4;
    OS_START();
    os_queue_init(uart_cache);
    os_timer_event_set(&os_uart_timer,50,(os_timer_event_caller_t)os_uart_timer_handler,	NULL);
    os_timer_event_restart(&os_uart_timer);
//		os_timer_event_set(&uart_notify_timer,3000,(os_timer_event_caller_t)os_uart_notify_handler,	NULL);

//    os_timer_event_set(&baudrate_timer,1000,(os_timer_event_caller_t)baudrate_timer_handler,&count);
    memset(&message,0,sizeof(message));
    message.len=0;

    while(1){
        OS_YIELD_UNTIL(event<OS_TASK_JMESH_SIZE);
        handler_table[event](data);
    }
    OS_END();
}
#endif
