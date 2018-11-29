/*
 * mesh_app_action.c
 *
 *  Created on: 2018-5-8
 *      Author: jiachuang
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_app_action.h"
#include "osapp_mesh.h"
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#include "clk_gate.h"
#include "app_uart.h"
#include "stdint.h"
#ifdef MESH_TEST_UART_CLENT_SERVER
#include "client_server_uart_test.h"
#endif /* MESH_TEST_UART_CLENT_SERVER */

#define LED1_PIN_NUM        8
#define LED2_PIN_NUM        9
#define LED1_PIN_NUM_MINI   3
#define LED2_PIN_NUM_MINI   22
//server





void set_led1(uint8_t on_off)
{
#ifdef MESH_TEST_UART_CLENT_SERVER
        uart_log_server_led_ctrl_t led;
        led.id = 1;
        led.OnOff = on_off;
        config_server_send_led_state(led);
#endif /* MESH_TEST_UART_CLENT_SERVER */

//    clk_gate_per_g1(PER_CLKG_SET_GPIO);

    if(on_off == 1)
    {
    	//data set  io on
    	volatile uint32_t d_gpio = *(volatile uint32_t *)0x20148000;
    	d_gpio &= ~(1<<(LED1_PIN_NUM));
    	d_gpio &= ~(1<<(LED1_PIN_NUM_MINI));
    	*(volatile uint32_t *)0x20148000 = d_gpio;
//        gpio_SetOutputValue(LED1_PIN_NUM,gpio_Low);
    }
    else
    {
    	//data set  io off
    	volatile uint32_t d_gpio = *(volatile uint32_t *)0x20148000;
    	d_gpio |= (1<<(LED1_PIN_NUM)) ;
    	d_gpio |= (1<<(LED1_PIN_NUM_MINI)) ;
    	*(volatile uint32_t *)0x20148000 = d_gpio;
//        gpio_SetOutputValue(LED1_PIN_NUM,gpio_High);
    }
}

void set_led2(uint8_t on_off)
{
#ifdef MESH_TEST_UART_CLENT_SERVER
        uart_log_server_led_ctrl_t led;
        led.id = 2;
        led.OnOff = on_off;
        config_server_send_led_state(led);
#endif /* MESH_TEST_UART_CLENT_SERVER */

//    clk_gate_per_g1(PER_CLKG_SET_GPIO);

    if(on_off == 1)
    {
    	//data set  io on
    	volatile uint32_t d_gpio = *(volatile uint32_t *)0x20148000;
    	d_gpio &= ~(1<<(LED2_PIN_NUM));
    	d_gpio &= ~(1<<(LED2_PIN_NUM_MINI));
    	*(volatile uint32_t *)0x20148000 = d_gpio;
//        gpio_SetOutputValue(LED2_PIN_NUM,gpio_Low);
    }
    else
    {
    	//data set  io off
    	volatile uint32_t d_gpio = *(volatile uint32_t *)0x20148000;
    	d_gpio |= (1<<(LED2_PIN_NUM)) ;
    	d_gpio |= (1<<(LED2_PIN_NUM_MINI)) ;
    	*(volatile uint32_t *)0x20148000 = d_gpio;

//        gpio_SetOutputValue(LED2_PIN_NUM,gpio_High);
    }
}

void init_leds(void)
{
//    struct gpioConfigStruct cfg;
//    memset(&cfg,0,sizeof(cfg));
//    cfg.dir = gpio_Output;
//    cfg.value = gpio_High;
//    gpio_SetConfig((uint8_t)LED1_PIN_NUM,&cfg);
//    gpio_SetConfig((uint8_t)LED2_PIN_NUM,&cfg);
    //set clock gate
    clk_gate_per_g1(PER_CLKG_SET_GPIO);
	//dir  out
    volatile uint32_t d_dir = *(volatile uint32_t *)0x20148004;
    d_dir |= (1<<(LED1_PIN_NUM)|1<<(LED2_PIN_NUM));
    d_dir |= (1<<(LED1_PIN_NUM_MINI)|1<<(LED2_PIN_NUM_MINI));
	*(volatile uint32_t *)0x20148004 = d_dir;
	//data set  io on
	volatile uint32_t d_gpio = *(volatile uint32_t *)0x20148000;
	d_gpio &= ~(1<<(LED1_PIN_NUM)|1<<(LED2_PIN_NUM)) ;
	d_gpio &= ~(1<<(LED1_PIN_NUM_MINI)|1<<(LED2_PIN_NUM_MINI)) ;
//	d_gpio |= (1<<(LED1_PIN_NUM)|1<<(LED2_PIN_NUM)) ;
	*(volatile uint32_t *)0x20148000 = d_gpio;
}


#ifdef MESH_TEST_BASIC_APP





//client
uint8_t mesh_app_uart_buff[10];
app_uart_inst_t mesh_app_uart0 = UART_INSTANCE(0);  /**< UART0 instance. */

extern void config_client_set_element0(void);
extern void config_client_set_element1(void);

void uart_receive_callback(void *parma,uint8_t i)
{
    switch(mesh_app_uart_buff[0])
    {
    case '0':
        mesh_run(config_client_set_element0, portMAX_DELAY, true);
        break;
    case '1':
        mesh_run(config_client_set_element1, portMAX_DELAY, true);
        break;
    case 'F':
        mesh_flush_msg_cache();
        break;
    default :
        break;
    }
    app_uart_read(&mesh_app_uart0,mesh_app_uart_buff,1,uart_receive_callback,NULL);
}

void uart_cmd_init(void)
{
    app_uart_comm_params_t uart_parm =
    {
        .rx_pin_no = 13,
        .tx_pin_no = 12,
        .rts_pin_no = 21,
        .cts_pin_no = 20,
        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
        .use_parity = 0,
        .priority = APP_IRQ_PRIORITY_MID,
        .baud_rate = UART_BAUDRATE_115200
    };
    app_uart_init(&mesh_app_uart0, &uart_parm);
    app_uart_read(&mesh_app_uart0,mesh_app_uart_buff,1,uart_receive_callback,NULL);
}

#endif
#endif
