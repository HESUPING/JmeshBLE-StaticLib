#ifndef JMESH_UART_CALLBACK_H
#define JMESH_UART_CALLBACK_H
#include"jmesh_uart.h"

void jmesh_uart_recv_callback(JMESH_UART_NAME_T uart,unsigned short len,unsigned char* data);

void jmesh_uart0_send_callback(void);

void jmesh_uart1_send_callback(void);

void wait_uart_send_over(void);

#endif // JMESH_UART_CALLBACK_H


