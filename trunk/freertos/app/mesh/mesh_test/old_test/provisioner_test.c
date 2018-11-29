/*
 * provisioner_test.c
 *
 *  Created on: 2018-1-22
 *      Author: jiachuang
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "provision_test.h"
//#include "gpio.h"
#include "ecc_p256.h"
#include "mesh_test_config.h"

#ifdef MESH_TEST_PROVISION

//CONST VALUE
public_key_t provisioner_public_key = {0};
//0x2c,0x31,0xa4,0x7b,0x57,0x79,0x80,0x9e,0xf4,0x4c,0xb5,0xea,0xaf,0x5c,0x3e,0x43,0xd5,0xf8,0xfa,0xad,0x4a,0x87,0x94,0xcb,0x98,0x7e,0x9b,0x03,0x74,0x5c,0x78,0xdd,
//0x91,0x95,0x12,0x18,0x38,0x98,0xdf,0xbe,0xcd,0x52,0xe2,0x40,0x8e,0x43,0x87,0x1f,0xd0,0x21,0x10,0x91,0x17,0xbd,0x3e,0xd4,0xea,0xf8,0x43,0x77,0x43,0x71,0x5d,0x4f
//};
uint8_t prov_private_key[GAP_P256_KEY_LEN] = {
0x06,0xa5,0x16,0x69,0x3c,0x9a,0xa3,0x1a,0x60,0x84,0x54,0x5d,0x0c,0x5d,0xb6,0x41,0xb4,0x85,0x72,0xb9,0x72,0x03,0xdd,0xff,0xb7,0xac,0x73,0xf7,0xd0,0x45,0x76,0x63
};
uint8_t prov_random[RANDOM_PDU_PARAMS_LEN] = {
0x8b,0x19,0xac,0x31,0xd5,0x8b,0x12,0x4c,0x94,0x62,0x09,0xb5,0xdb,0x10,0x21,0xb9
};
uint8_t static_auth_value[AUTHVALUE_LEN] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

#define MODE_IS_NO_PUBLIC_KEY   0x00
#define MODE_IS_USE_PUBLIC_KEY  0x01
#define PROVISING_START_MODE    MODE_IS_NO_PUBLIC_KEY
#define BEACON_LIST_MAX 10
uint8_t uuid_recv_list[BEACON_LIST_MAX][BEACON_UUID_LEN] ={0};
uint8_t beacon_uuid_num = 0;
volatile uint8_t provisioner_public_key_gen_done = 0;

extern void (*unprovisioned_dev_beacon_rx_callback)(uint8_t *,uint16_t ,uint32_t *);


/******USER FUNCTION******/
void user_unprovisioned_dev_beacon_rx_callback(uint8_t *dev_uuid,uint16_t oob_info,uint32_t *uri_hash)
{
    if(current_stage == ProvStage_Beacon_rx)
    {
        LOG(LOG_LVL_INFO,current_stage_s[current_stage]);
        current_stage = ProvStage_LinkOpen_tx;
        provisioning_link_open_tx(dev_uuid);
        LOG(LOG_LVL_INFO,current_stage_s[current_stage]);
    }
}

void user_provisioner_link_ack_rx_callback(void)
{
    provisioner_invite_tx(0);
}

void user_provisioner_capabilities_rx_callback(provision_capabilities_t * para)
{
    provision_start.algorithm   = 0x00;
    provision_start.public_key  = PROVISING_START_MODE;
    provision_start.auth_method = No_OOB_Authentication;
    provision_start.auth_action = 0x00;
    provision_start.auth_size   = 0x00;
    
    provisioner_start_tx();
}

void user_provisioner_read_peer_public_key_oob(void (*callback)(void))
{
    memcpy(&provision_key.peer_public,&unprov_dev_public_key,sizeof(public_key_t));
    callback();
}

void user_provisioner_provision_input_auth_value(uint8_t *buff,void (*cb)())
{
    memcpy(buff,static_auth_value,AUTHVALUE_LEN);
    cb();
}
void user_provisioner_provision_output_auth_value(uint8_t *buff)
{
    memcpy(buff,static_auth_value,AUTHVALUE_LEN);
    return;
}
void user_provisioner_provision_static_auth_value(uint8_t *buff)
{
    memcpy(buff,static_auth_value,AUTHVALUE_LEN);
}

void user_init_provisioning_data(void)
{
#if (defined(MESH_TEST_BASIC_APP) || defined(MESH_TEST_BASIC_MULTI_NODE))
    extern void provisioner_init_mesh_provision_data();
    provisioner_init_mesh_provision_data();
#else
    uint8_t tttmp[] = {0xef,0xb2,0x25,0x5e,0x64,0x22,0xd3,0x30,0x08,0x8e,0x09,0xbb,0x01,0x5e,0xd7,0x07};
    memcpy(provision_data.network_key,tttmp,16);
    provision_data.key_index = 0x0567;
    provision_data.flags = 0x00;
    provision_data.current_iv_index = 0x01020304;
    provision_data.unicast_addr = 0x0b0c;
#endif
}

void provisioner_provision_done(uint8_t success , uint8_t reason)
{
    LOG(3,"=====PROVISION DONE!!=====\n");
    LOG(3,"Success=%d,Reason=%d\n",success,reason);
    #if (defined(MESH_TEST_BASIC_APP) || defined(MESH_TEST_BASIC_MULTI_NODE))
        //Display provision_data.
        LOG(3,"provision_data.network_key=0x\n");
        log_hex_data(provision_data.network_key,MESH_NETWORK_KEY_LENGTH);
        LOG(3,"provision_data.key_index=0x%x\n",provision_data.key_index);
        LOG(3,"provision_data.flags=0x%x\n",provision_data.flags);
        LOG(3,"provision_data.current_iv_index=0x%x\n",provision_data.current_iv_index);
        LOG(3,"provision_data.unicast_addr=0x%x\n",provision_data.unicast_addr);
        //app call back
        extern void provisioner_complete_callback(uint8_t success , uint8_t reason);
        provisioner_complete_callback(success , reason);
    #endif
}

//Generate provisioner's public key
void provisioner_gen_public_keys_done(void* aaaaa)
{
    reverse_self(prov_private_key,GAP_P256_KEY_LEN);
    reverse_self(provisioner_public_key.x,GAP_P256_KEY_LEN);
    reverse_self(provisioner_public_key.y,GAP_P256_KEY_LEN);
    provisioner_public_key_gen_done = 1;
}
void provisioner_gen_public_keys(void)
{
    provisioner_public_key_gen_done = 0;
    reverse_self(prov_private_key,GAP_P256_KEY_LEN);
    ecc_gen_new_public_key_usr(prov_private_key,provisioner_public_key.x,provisioner_public_key.y,provisioner_gen_public_keys_done);
    while(provisioner_public_key_gen_done != 1);
}

/******USER FUNCTION******/
void user_provisioner_function_init(void)
{
    provisioner_capabilities_rx_callback = user_provisioner_capabilities_rx_callback;
    provisioner_read_peer_public_key_oob = user_provisioner_read_peer_public_key_oob;
    provision_input_auth_value  = user_provisioner_provision_input_auth_value;
    provision_output_auth_value = user_provisioner_provision_output_auth_value;
    provision_static_auth_value = user_provisioner_provision_static_auth_value;
    user_provision_done = provisioner_provision_done;
    provisioner_link_ack_rx_callback = user_provisioner_link_ack_rx_callback;
    unprovisioned_dev_beacon_rx_callback=user_unprovisioned_dev_beacon_rx_callback;
}

void app_mesh_test_provisioner_init(void)
{
    provisioner_gen_public_keys();
    provisioner_reset();
    user_provisioner_function_init();
    user_init_provisioning_data();
    provision_env.link_id = 0x23af5850;
    memcpy(&provision_key.local_public,&provisioner_public_key,sizeof(public_key_t));
    memcpy(provision_random.field.random_provisioner,prov_random,RANDOM_PDU_PARAMS_LEN);
    memcpy(provision_key.private,prov_private_key,GAP_P256_KEY_LEN);
}




//short GPIO10 and GPIO11 is Provisioner && Config Client
//float GPIO10 and GPIO11 is Unprov Devices && Config Server
__weak void app_mesh_test_init(void)
{
    struct gpioConfigStruct cfg={0};
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
    //GPIO8=0:Provisioner
    //GPIO8=1:UnprovDev
    if(gpio_GetValue(8) == gpio_Low)
    {
        LOG(LOG_LVL_INFO,"==Provisioner==\n");
        provisioner_init();
        app_mesh_test_provisioner_init();
    }
    else
    {
        LOG(LOG_LVL_INFO,"==Unprov Devices==\n");
        unprovisioned_dev_init();
        app_mesh_test_unprodev_init();
    }
}


#endif
#endif
