#include "uart.h"
#include "pshare.h"
#include "intc.h"
#include "log.h"

static uint8_t buf[1];

void uart_tx_finish()
{

}

void uart_rx_finish()
{
	uart_read(buf,1,(void (*)(void*,uint8_t))uart_rx_finish,NULL);
	LOG(LOG_LVL_INFO,"%c\n",buf[0]);

	uart_write(buf, 1, (void (*)(void*,uint8_t))uart_tx_finish, NULL);

}

void read_uart_Byte()
{
	uart_read(buf,1,(void (*)(void*,uint8_t))uart_rx_finish,NULL);
}


void uart_echo_test()
{

    pshare_funcio_set(FUNC_IO_10,IO_UART0_TXD,ENABLE);      //funcio 10 = gpio_mux[12]
    pshare_funcio_set(FUNC_IO_11,IO_UART0_RXD,ENABLE);      //funcio 11 = gpio_mux[13]

    pshare_funcio_set(FUNC_IO_18,IO_UART0_CTS,ENABLE);      //funcio 18 = gpio_mux[20]
    pshare_funcio_set(FUNC_IO_19,IO_UART0_RTS,ENABLE);      //funcio 19 = gpio_mux[21]
    
    // Initialize UART
    uart_init(SET_UART_DIVISOR(UART_CLK,UART_DEFAULT_BAUDRATE));
    // Initialize the Interrupt Controller

    intc_init();

    read_uart_Byte();

    if(*( ( volatile uint32_t * )  0x0 ) != 0)
	{
		while(1);
	}
}


