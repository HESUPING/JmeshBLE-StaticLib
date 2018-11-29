/*
 * multi_basic_test_common.c
 *
 *  Created on: 2018Äê5ÔÂ17ÈÕ
 *      Author: jiachuang
 */



#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#ifdef MESH_TEST_BASIC_MULTI_NODE
#include "multi_basic_test_common.h"
#include "flash.h"

/************************************** START OF CONFIG********************************************/

//SYSTEM CONST
uint8_t test_prov_net_key [MESH_KEY_LENGTH]   = {0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
uint8_t test_prov_app_key[MESH_KEY_LENGTH]    = {0x63,0x96,0x47,0x71,0x73,0x4f,0xbd,0x76,0xe3,0xb4,0x05,0x19,0xd1,0xd9,0x4a,0x48};
uint16_t test_unprov_uni_addr[NUMBER_OF_NODES]= {0x1000,0x1100,0x1200,0x1300,0x1400,0x1500,0x1600,0x1700};
uint16_t test_group_addr[2]                   = {0xF111,0xF222};


//System variables
uint8_t  temp_devkey[MESH_KEY_LENGTH];




//VAR
uint8_t current_role = ROLE_UNPROV_CONFIG_SERVER;
uint8_t current_node_index = 0;
void (*generate_device_key_done_cb)()=NULL;


//DECLARE
void init_leds(void);
void uart_cmd_init(void);
void set_led1(uint8_t on_off);
void set_led2(uint8_t on_off);




void dev_key_gen_done()
{
    LOG(3,"dev_key_gen_done\n");
    LOG(3,"devkey=");
    log_hex_data(temp_devkey,16);

    //add to devkey list
    config_add_devkey(temp_devkey , provision_data.unicast_addr);
    if(generate_device_key_done_cb)
    {
        generate_device_key_done_cb();
    }

}
void generate_device_key_by_ecdh_and_salt(void (*cb)())
{
    generate_device_key_done_cb=cb;
    #ifdef TEST_APP_DEBUG
        uint8_t test_dev_key_debug[16] = {0x9d,0x6d,0xd0,0xe9,0x6e,0xb2,0x5d,0xc1,0x9a,0x40,0xed,0x99,0x14,0xf8,0xf0,0x3f};
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[current_node_index]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[0]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[1]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[2]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[3]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[4]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[5]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[6]);
        config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[7]);
        if(generate_device_key_done_cb)
        {
            generate_device_key_done_cb();
        }
    #else
        //calcuate devkey
        ecdh_prov_salt_to_devkey(provision_key.ecdh_secret.x , session_info.provisioning_salt , temp_devkey , dev_key_gen_done);
    #endif
}

//short GPIO10 and GPIO11 is Provisioner && Config Client
//float GPIO10 and GPIO11 is Unprov Devices && Config Server
void init_mesh_gpio_config(void)
{
    struct gpioConfigStruct cfg;
    memset(&cfg,0,sizeof(cfg));
    cfg.dir = gpio_Input;
    cfg.debounce = gpio_Deb;
    cfg.value = gpio_High;
    cfg.pullup = gpio_PullUp;
    cfg.irqLevel = gpio_Edge;
    cfg.irq_enabled = gpio_DisableIRQ;
    gpio_SetConfig((uint8_t)10,&cfg);//GPIO10  pullup
    cfg.dir = gpio_Output;
    cfg.value = gpio_Low;
    gpio_SetConfig((uint8_t)11,&cfg);//GPIO11 output 0
}

void export_tx_rx_en_pin(void)
{
    //rx_en(gpio_7),tx_en(gpio8)
    *(volatile uint32_t*)0x20132020 |= (1<<16)|(1<<17)|(1<<20); // bit20: calibration done(gpio_11)    bit17: rx_en(gpio_7),tx_en(gpio8)
    *(volatile uint32_t*)0x20110024 &= ~(3<<0);
    *(volatile uint32_t*)0x20100050 &=~(0xf);
    *(volatile uint32_t*)0x20100050 |= 0xa5;
}

void read_nvds_addr(void)
{
#if 0
    //GPIO 20/21/22/23 is ADDR 0/1/2/3
    struct gpioConfigStruct cfg;
    memset(&cfg,0,sizeof(cfg));
    cfg.dir = gpio_Input;
    cfg.debounce = gpio_Deb;
    cfg.value = gpio_High;
    cfg.pullup = gpio_PullUp;
    cfg.irqLevel = gpio_Edge;
    cfg.irq_enabled = gpio_DisableIRQ;

    gpio_SetConfig((uint8_t)20,&cfg);
    gpio_SetConfig((uint8_t)21,&cfg);
    gpio_SetConfig((uint8_t)22,&cfg);
    gpio_SetConfig((uint8_t)23,&cfg);
    

    if(gpio_GetValue(20) == gpio_Low) current_node_index = 0;
    if(gpio_GetValue(21) == gpio_Low) current_node_index = 1;
    if(gpio_GetValue(22) == gpio_Low) current_node_index = 2;
    if(gpio_GetValue(23) == gpio_Low) current_node_index = 3;
    LOG(3,"GPIO_NODE = 0x%x\n",current_node_index);
#endif
#if 0
    //read from flash
    flash_init();
    flash_read(0xFFFFF,1,&current_node_index);
    LOG(3,"FLASH_NODE = 0x%x\n",current_node_index);
#endif
}

void role_judge(void)
{
    init_mesh_gpio_config();
    if(gpio_GetValue(10) == gpio_Low)
    {
        current_role = ROLE_PROVER_CONFIG_CLIENT;
    }
    else
    {
        current_role = ROLE_UNPROV_CONFIG_SERVER;
    }
    read_nvds_addr();
}

/////////////////INIT MODULE////////////////////////////////////
void app_mesh_test_init_part2(void)
{
    upper_transport_init();
    init_leds();
    uart_cmd_init();
    role_judge();
    //Role switch
    if(current_role == ROLE_PROVER_CONFIG_CLIENT)
    {
        LOG(LOG_LVL_INFO,"==Provisioner && Config Client==\n");
        mesh_app_client_init();
        provisioner_init();//one time
        provisioner_init_mesh_provision_data();
        init_config_client_model_keys_data();
        #ifdef TEST_APP_DEBUG
            provisioner_complete_callback(1,0);
        #else
            //app_mesh_test_provisioner_init(); // uart command
        #endif
    }
    else
    {
        LOG(LOG_LVL_INFO,"==Unprov Devices && Config Server==\n");
        mesh_app_server_init();
        unprovisioned_dev_init();//one time
        #ifdef TEST_APP_DEBUG
            provision_now_status = PROVISIONED_NOW;
            provisioner_init_mesh_provision_data();
            unprov_dev_complete_callback(1,0);
        #else
            app_mesh_test_unprodev_init();
        #endif
    }
    user_app_mesh_test_init_done();
}
void app_mesh_test_init(void)
{
    init_mesh_gpio_config();
    export_tx_rx_en_pin();
    security_init(app_mesh_test_init_part2);
}

/************************************** END OF CONFIG********************************************/



/************************************** START OF PERIPHERAL********************************************/

//server
#define LED1_PIN_NUM    4
#define LED2_PIN_NUM    5

void set_led1(uint8_t on_off)
{
    if(on_off == 1)
    {
        gpio_SetOutputValue(LED1_PIN_NUM,gpio_Low);
    }
    else
    {
        gpio_SetOutputValue(LED1_PIN_NUM,gpio_High);
    }
}

void set_led2(uint8_t on_off)
{
    if(on_off == 1)
    {
        gpio_SetOutputValue(LED2_PIN_NUM,gpio_Low);
    }
    else
    {
        gpio_SetOutputValue(LED2_PIN_NUM,gpio_High);
    }
}

void init_leds(void)
{
    struct gpioConfigStruct cfg;
    memset(&cfg,0,sizeof(cfg));
    cfg.dir = gpio_Output;
    cfg.value = gpio_High;
    gpio_SetConfig((uint8_t)LED1_PIN_NUM,&cfg);
    gpio_SetConfig((uint8_t)LED2_PIN_NUM,&cfg);
}




//client
uint8_t mesh_app_uart_buff[10];
app_uart_inst_t mesh_app_uart0 = UART_INSTANCE(0);  /**< UART0 instance. */
#define UART_MESH_CMD_LEN       3
#define UART_MESH_CMD_APPKEY    'A'
#define UART_MESH_CMD_PROV      'B'
#define UART_MESH_CMD_GROUP     'C'

void uart_receive_callback(void *parma,uint8_t i)
{
    if(mesh_app_uart_buff[0] < '9')
    {
        mesh_run(config_client_set_element,portMAX_DELAY, true);
    }
    if(mesh_app_uart_buff[0] == UART_MESH_CMD_APPKEY)
    {
        mesh_run(send_appkey_and_bind,portMAX_DELAY, true);
    }
    if(mesh_app_uart_buff[0] == UART_MESH_CMD_PROV)
    {
        mesh_run(provisioner_start_prov,portMAX_DELAY, true);
    }
    if(mesh_app_uart_buff[0] == UART_MESH_CMD_GROUP)
    {
        //config group
        if(mesh_app_uart_buff[1] == 'F')
        {
            mesh_run(config_client_config_group_subscribe,portMAX_DELAY, true);
        }
        else if(mesh_app_uart_buff[1] == 'D')//set group:ALL NODE
        {
            mesh_run(config_client_allnode_onoff,portMAX_DELAY, true);
        }
        else////set group:one group
        {
            mesh_run(config_client_set_group_onoff,portMAX_DELAY, true);
        }
    }
    app_uart_read(&mesh_app_uart0,mesh_app_uart_buff,UART_MESH_CMD_LEN,uart_receive_callback,NULL);
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
    app_uart_read(&mesh_app_uart0,mesh_app_uart_buff,UART_MESH_CMD_LEN,uart_receive_callback,NULL);
}
/************************************** END OF PERIPHERAL********************************************/

#endif
#endif


/*
 * TODO:
 *
 *
 *
 *
 */



