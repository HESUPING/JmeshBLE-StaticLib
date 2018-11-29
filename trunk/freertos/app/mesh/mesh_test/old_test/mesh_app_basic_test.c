/*
 * mesh_app_basic_test.c
 *
 *  Created on: 2018-4-10
 *      Author: jiachuang
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#ifdef MESH_TEST_BASIC_APP
#include "provision_test.h"
#include "gpio.h"
#include "config_client.h"
#include "config_server.h"
#include "mesh_definitions.h"
#include "upper_transport.h"
#include "generic_onoff_client.h"
#include "generic_onoff_server.h"
#include "generic_onoff_common.h"
#include "mesh_app_action.h"


//Export External Function
extern void mesh_app_server_init(void);
extern void mesh_app_client_init(void);
extern uint32_t sequence_number;
extern config_client_model_t config_client;
extern config_server_model_t config_server;
extern mesh_elmt_t client_elmts[2];
extern mesh_elmt_t server_elmts[2];
extern generic_onoff_client_t generic_onoff_client_0;
extern generic_onoff_client_t generic_onoff_client_1;
extern generic_onoff_server_t generic_onoff_server_0;
extern generic_onoff_server_t generic_onoff_server_1;
extern void init_elmt_addr(uint16_t addr);
extern void config_server_add_netkey(uint8_t *netkey,uint16_t netkey_idx,uint8_t *status);
//Decalre
void generate_device_key_by_ecdh_and_salt(void);
//#define TEST_APP_DEBUG

/************************==Provisioner && Config Client==************************************/
//system const
uint8_t test_prov_net_key [MESH_KEY_LENGTH] = {0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
#define TEST_PROV_NET_KEY_INDEX     0x0123
#define TEST_PROV_FLAGS             0x00
#define TEST_PROV_IV_INDEX          0x12345678
#define TEST_PROV_UNICAST_ADDR      0x0003
#define TEST_PROV_SEQUENCE_NUM      0x3129ab
//ELEMENT0
uint8_t test_prov_app_key0[MESH_KEY_LENGTH] = {0x63,0x96,0x47,0x71,0x73,0x4f,0xbd,0x76,0xe3,0xb4,0x05,0x19,0xd1,0xd9,0x4a,0x48};
#define TEST_PROV_APP_KEY0_INDEX     0x0456
#define TEST_UNPROV_UNICAST_ADDR0    0x1201
//ELEMENT1
#define ENABLE_ELEMENT1
#define TEST_UNPROV_UNICAST_ADDR1    0x1202



//St=ystem variables
volatile uint8_t provisioner_net_key_all_keys_generate = 0;
volatile uint8_t unprov_dev_net_key_all_keys_generate = 0;
volatile uint8_t provisioner_aid_generate = 0;
volatile uint8_t device_key_generate_done = 0;
//Gerenic onoff variable
generic_onoff_msg_set_t         onoff_val_normal;
generic_onoff_msg_default_set_t onoff_val_default;
uint8_t generic_tid = 0;



void provisioner_init_mesh_provision_data()//external call
{
    memcpy(provision_data.network_key,test_prov_net_key,MESH_KEY_LENGTH);
    provision_data.key_index = TEST_PROV_NET_KEY_INDEX;
    provision_data.flags = TEST_PROV_FLAGS;
    provision_data.current_iv_index = TEST_PROV_IV_INDEX;
    provision_data.unicast_addr = TEST_UNPROV_UNICAST_ADDR0;
}

void config_client_appkey_add_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_appkey_add_test_cb\n");
}
void config_client_model_app_bind_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_model_app_bind_test_cb\n");
}
uint8_t alloc_generic_tid(void)
{
    return generic_tid++;
}

/*******Example***********/
void config_client_set_element0(void)
{
    onoff_val_default.tid = alloc_generic_tid();
    onoff_val_default.onoff = 0;
    generic_onoff_set_tx(&generic_onoff_client_0,&onoff_val_default,sizeof(onoff_val_default),TEST_UNPROV_UNICAST_ADDR0);
}
void config_client_set_element1(void)
{
    onoff_val_default.tid = alloc_generic_tid();
    onoff_val_default.onoff = 1;
    generic_onoff_set_tx(&generic_onoff_client_0,&onoff_val_default,sizeof(onoff_val_default),TEST_UNPROV_UNICAST_ADDR0);
}


void config_client_send_message_model_test()
{
    /*********Model test***********/
    #if 1
    //generic_onoff_set_tx (standard message) ->
    onoff_val_normal.tid = alloc_generic_tid();
    onoff_val_normal.trans_time = (Second_1<<6) | 2;
    onoff_val_normal.onoff = 1;
    onoff_val_normal.delay = 10;
    generic_onoff_set_tx(&generic_onoff_client_0,&onoff_val_normal,sizeof(onoff_val_normal),TEST_UNPROV_UNICAST_ADDR0);
    #endif
    #if 1
    //generic_onoff_set_tx (default message) ->
    onoff_val_default.tid = alloc_generic_tid();
    onoff_val_default.onoff = 1;
    generic_onoff_set_tx(&generic_onoff_client_0,&onoff_val_default,sizeof(onoff_val_default),TEST_UNPROV_UNICAST_ADDR0);
    #endif
    #ifdef ENABLE_ELEMENT1
    //generic_onoff_set_tx (default message) -> (client 1)
    onoff_val_default.tid = alloc_generic_tid();
    onoff_val_default.onoff = 1;
    generic_onoff_set_tx(&generic_onoff_client_0,&onoff_val_default,sizeof(onoff_val_default),TEST_UNPROV_UNICAST_ADDR1);
    #endif
    #if 0
    //generic_onoff_set_unacknowledged_tx (standard message) ->
    onoff_val_normal.tid = alloc_generic_tid();
    onoff_val_normal.trans_time = (Second_1<<6) | 2;
    onoff_val_normal.onoff = 1;
    onoff_val_normal.delay = 10;
    generic_onoff_set_unacknowledged_tx(&generic_onoff_client_0,&onoff_val_normal,sizeof(onoff_val_normal),TEST_UNPROV_UNICAST_ADDR);
    #endif
    #if 0
    //generic_onoff_get_tx ->
    generic_onoff_get_tx(&generic_onoff_client_0,0,0,TEST_UNPROV_UNICAST_ADDR);
    #endif
}
void provisioner_complete_callback(uint8_t success , uint8_t reason)//external call
{
    config_model_app_bind_param_t test_bind_param;
    if(success == 1)
    {
        //generate device key
        generate_device_key_by_ecdh_and_salt();
        //bound local appkey.
       *generic_onoff_client_0.model.base.bound_key_buf = &config_client.appkey[0];
       *config_client.model.base.bound_key_buf = &config_client.appkey[0];
        //config_appkey_add_tx-> //ok
        config_appkey_add_tx(&config_client.model.base,&config_client.appkey[0],TEST_UNPROV_UNICAST_ADDR0,config_client_appkey_add_test_cb);

        //ELEMENT 0 
        //config_model_app_bind_tx-> //
        test_bind_param.appkey_idx = TEST_PROV_APP_KEY0_INDEX;
        test_bind_param.elmt_addr = TEST_UNPROV_UNICAST_ADDR0;
        test_bind_param.model_id = GENERIC_ONOFF_SERVER_MODEL_ID;
        test_bind_param.sig_model = true;
        config_model_app_bind_tx(&config_client.model.base,&test_bind_param,TEST_UNPROV_UNICAST_ADDR0,config_client_model_app_bind_test_cb);

        //ELEMENT 1
        #ifdef ENABLE_ELEMENT1
        //config_model_app_bind_tx-> //
        test_bind_param.appkey_idx = TEST_PROV_APP_KEY0_INDEX;
        test_bind_param.elmt_addr = TEST_UNPROV_UNICAST_ADDR1;
        test_bind_param.model_id = GENERIC_ONOFF_SERVER_MODEL_ID;
        test_bind_param.sig_model = true;
        config_model_app_bind_tx(&config_client.model.base,&test_bind_param,TEST_UNPROV_UNICAST_ADDR0,config_client_model_app_bind_test_cb);
        #endif
        
        //MODEL TEST
        config_client_send_message_model_test();
    }
}



void provisioner_net_key_all_keys_generate_done()
{
    provisioner_net_key_all_keys_generate = 1;
    LOG(3,"provisioner_net_key_all_keys_generate_done\n");
}
void provisioner_aid_generate_done()
{
    provisioner_aid_generate = 1;
    LOG(3,"provisioner_aid_generate_done\n");
}
void init_config_client_model_keys_data()
{
    //sequence number/iv index
    sequence_number = TEST_PROV_SEQUENCE_NUM;
    //iv_index = TEST_PROV_IV_INDEX;
    mesh_beacon_iv_index_set(TEST_PROV_IV_INDEX);
    //netkey
    provisioner_net_key_all_keys_generate = 0;
    config_client.netkey[0].is_used = true;
    config_client.netkey[0].curr_idx = 0;
    config_client.netkey[0].global_idx = TEST_PROV_NET_KEY_INDEX;
    memcpy(config_client.netkey[0].key[0].netkey , test_prov_net_key , MESH_KEY_LENGTH);
    generte_all_net_keys(&config_client.netkey[0].key[0] , provisioner_net_key_all_keys_generate_done);
    while(provisioner_net_key_all_keys_generate == 0);
    
    //appkey gen
    provisioner_aid_generate = 0;
    config_client.appkey[0].global_idx = TEST_PROV_APP_KEY0_INDEX;
    config_client.appkey[0].curr_idx = 0;
    config_client.appkey[0].is_used = true;
    config_client.appkey[0].bound_netkey = &config_client.netkey[0];
    memcpy(config_client.appkey[0].key[0].key , test_prov_app_key0 , MESH_KEY_LENGTH);
    k4_derivation(config_client.appkey[0].key[0].key , &config_client.appkey[0].key[0].aid , provisioner_aid_generate_done);
    while(provisioner_aid_generate == 0);
    //ELEMENT 0 
    client_elmts[0].uni_addr = TEST_PROV_UNICAST_ADDR;
    config_client.model.base.elmt = &client_elmts[0];
    
    //ELEMENT 1
    #ifdef ENABLE_ELEMENT1
    client_elmts[1].uni_addr = TEST_PROV_UNICAST_ADDR;   
    #endif
}



/***********************==Unprov Devices && Config Server==****************************/
void unprov_dev_net_key_all_keys_generate_done()
{
    unprov_dev_net_key_all_keys_generate = 1;
    LOG(3,"unprov_dev_net_key_all_keys_generate_done\n");
}
void unprov_dev_complete_callback(uint8_t success , uint8_t reason)//external call
{
    if(success == 1)
    {
        //generate device key
        generate_device_key_by_ecdh_and_salt();
        //FOR DEBUG
        #ifdef TEST_APP_DEBUG
            provisioner_init_mesh_provision_data();
        #endif
        //set iv index
        //iv_index = provision_data.current_iv_index;     
		mesh_beacon_iv_index_set(provision_data.current_iv_index);
        //init self
        uint8_t add_key_statue = 0;
        init_elmt_addr(provision_data.unicast_addr);
        #ifdef ENABLE_ELEMENT1
        init_elmt_addr(TEST_UNPROV_UNICAST_ADDR1);
        #endif
        config_server_add_netkey(provision_data.network_key , provision_data.key_index , &add_key_statue);
        //config_server_add_netkey will generate all keys
        /*
        //set netkey to config_server
        unprov_dev_net_key_all_keys_generate = 0;
        config_server.netkey[0].is_used = true;
        config_server.netkey[0].curr_idx = 0;
        config_server.netkey[0].global_idx = TEST_PROV_NET_KEY_INDEX;
        memcpy(config_server.netkey[0].key[0].netkey , provision_data.network_key , MESH_KEY_LENGTH);
        generte_all_net_keys(&config_server.netkey[0].key[0] , unprov_dev_net_key_all_keys_generate_done);
        while(unprov_dev_net_key_all_keys_generate == 0);
        */
        //ELEMENT 0
        server_elmts[0].uni_addr = provision_data.unicast_addr;
        //ELEMENT1
        #ifdef ENABLE_ELEMENT1
        server_elmts[1].uni_addr = TEST_UNPROV_UNICAST_ADDR1;
        #endif
        //config_server.model.base.elmt = &server_elmts[0];
    }
}

/***********************COMMON****************************/

void dev_key_gen_done()
{
    LOG(3,"dev_key_gen_done\n");
    LOG(3,"devkey=");
    log_hex_data(devkey,16);
    device_key_generate_done = 1;
}
void generate_device_key_by_ecdh_and_salt(void)
{
    #ifdef TEST_APP_DEBUG
    uint8_t test_dev_key_debug[16] = {0x9d,0x6d,0xd0,0xe9,0x6e,0xb2,0x5d,0xc1,0x9a,0x40,0xed,0x99,0x14,0xf8,0xf0,0x3f};
    memcpy(devkey,test_dev_key_debug,16);
    #else
        device_key_generate_done = 0;
        ecdh_prov_salt_to_devkey(provision_key.ecdh_secret.x , session_info.provisioning_salt , devkey , dev_key_gen_done);
        while(device_key_generate_done == 0);
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

void app_mesh_test_init(void)
{
    init_mesh_gpio_config();
    export_tx_rx_en_pin();
    security_init();
    upper_transport_init();
    init_leds();
    uart_cmd_init();
    //Role switch
    if(gpio_GetValue(10) == gpio_Low)
    {
        LOG(LOG_LVL_INFO,"==Provisioner && Config Client==\n");
        mesh_app_client_init();
        init_config_client_model_keys_data();
        #ifdef TEST_APP_DEBUG
            provisioner_complete_callback(1,0);
        #else
            app_mesh_test_provisioner_init();
        #endif
    }
    else
    {
        LOG(LOG_LVL_INFO,"==Unprov Devices && Config Server==\n");
        mesh_app_server_init();
        #ifdef TEST_APP_DEBUG
            unprov_dev_complete_callback(1,0);
        #else
            app_mesh_test_unprodev_init();
        #endif
    }
}

#endif
#endif


