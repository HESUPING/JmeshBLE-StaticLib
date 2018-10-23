
#include"../jmesh_driver_config.h"
#if(JMESH_DRIVER_X86)

#include"../jmesh_uart.h"
#include"stdio.h"

void jmesh_uart_init(JMESH_UART_NAME_T uart, JMESH_UART_BAUD_T baud, JMESH_UART_PARITY_T parity,JMESH_UART_STOP_BITS_T stop_bits){
     ;
 }

void jmesh_uart_start(JMESH_UART_NAME_T uart){

}

void jmesh_uart_stop(JMESH_UART_NAME_T uart){
}

void jmesh_uart_send(JMESH_UART_NAME_T uart, unsigned short length, unsigned char *data){
    int i;
    printf("uart %d send:",uart);
    for(i=0;i<length;i++){
        printf("%c",data[i]);
    }
    printf("\n");
}
#endif

