#ifndef OS_TASK_JMESH_H
#define OS_TASK_JMESH_H

#include"os_queue.h"
#include"os_core.h"
#include"os_timer_event.h"
//#include"../upper_transport/jmesh_control.h"
//#include"../app/app_light_client.h"

//#include"../app/protocol_645_client.h"

//#include"jmeshs_prov.h"
//#include"jmeshs_prov_task.h"

#define UART_CACHE_SIZE 5
#define UART_CACHE_BUFFER_SIZE 100
OS_TASK_NAME(os_task_jmesh);
enum {
    OS_TASK_JMESH_APP_LIGHT,
    OS_TASK_JEMSH_ACCESS_SEND,
    OS_TASK_JEMSH_BEARER_READ,
    OS_TASK_JMESH_PROTOCOL_645,
    OS_TASK_JMESH_UART_SEND,
    OS_TASK_JMESH_UART_READ,

    OS_TASK_MESH_PROVISIONING,
    OS_TASK_JMESH_SIZE
};

typedef struct {
    unsigned char dat[UART_CACHE_BUFFER_SIZE];
    unsigned char len;
    unsigned char flag;
}common_dat_t;

//typedef struct {
//    jmesh_pdu_t*  pdu;
//    unsigned char length;
//}bearer_read_t;

int os_task_jmesh_app_light(unsigned char light_id,unsigned char on_off);
void os_uart_timer_handler(os_data_t data);
void os_uart_write_callback(void* buffer,unsigned char length);
extern common_dat_t uart_read_dat;

//#define ELECTRONIC_645_GATEWAY
//#define WATER_PROTOCOL_188_GATEWAY
//#define LIGHT_GATEWAY
#define SERIAL_TRANSPARENT_TRANSMISSION
#endif
