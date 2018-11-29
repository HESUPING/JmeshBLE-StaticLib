/*
 * multi_basic_test_client.c
 *
 *  Created on: 2018Äê5ÔÂ17ÈÕ
 *      Author: jiachuang
 */


#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#ifdef MESH_TEST_BASIC_MULTI_NODE
#include "multi_basic_test_common.h"

//Gerenic onoff variable
generic_onoff_msg_set_t         onoff_val_normal;
generic_onoff_msg_default_set_t onoff_val_default;
uint8_t generic_tid = 0;

//group add variable
#define ADD_GROUP_MSG_MAX   8
__IO uint8_t group_add_index = 0;
uint8_t group_add_tab[ADD_GROUP_MSG_MAX][3]=
{
0,0,0,
0,1,0,
1,0,0,
1,1,0,
2,0,1,
2,1,1,
3,0,1,
3,1,1,
};


//DECLEAR
void add_model_to_group(void);



void provisioner_init_mesh_provision_data(void)
{
    #ifdef TEST_APP_DEBUG
        memcpy(provision_data.network_key,test_prov_net_key,MESH_KEY_LENGTH);
        provision_data.key_index = TEST_PROV_NET_KEY_INDEX;
        provision_data.flags = TEST_PROV_FLAGS;
        provision_data.current_iv_index = TEST_PROV_IV_INDEX;
    #else
        //test keys
        uint8_t tttmp[] = {0xef,0xb2,0x25,0x5e,0x64,0x22,0xd3,0x30,0x08,0x8e,0x09,0xbb,0x01,0x5e,0xd7,0x07};
        memcpy(provision_data.network_key,tttmp,16);
        provision_data.key_index = 0x0567;
        provision_data.flags = 0x00;
        provision_data.current_iv_index = 0x01020304;   
    #endif
    
    provision_data.unicast_addr = test_unprov_uni_addr[current_node_index];
}






void provisioner_start_prov(void)
{
    current_node_index = mesh_app_uart_buff[1] - '0';
    // make random value
    prov_random[0] = mesh_app_uart_buff[1];
    prov_random[1] = current_node_index;
    //init
    app_mesh_test_provisioner_init();
    //clear osapp mesh cache
    mesh_flush_msg_cache();
}

uint8_t alloc_generic_tid(void)
{
    return generic_tid++;
}



void config_client_set_element(void)
{
    uint8_t addr    = mesh_app_uart_buff[0] - '0';
    uint8_t element = mesh_app_uart_buff[1] - '0';
    uint8_t value   = mesh_app_uart_buff[2] - '0';
    onoff_val_default.tid = alloc_generic_tid();
    onoff_val_default.onoff = value;
    generic_onoff_set_tx(&generic_onoff_client_0,&onoff_val_default,sizeof(onoff_val_default),test_unprov_uni_addr[addr]+element);
}




/***********************GROUP ACTION************************************/

void subscription_tx_done(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_model_subscription_update_tx_send_done,index=%x\n",group_add_index);
    if(group_add_index < (ADD_GROUP_MSG_MAX-1))
    {
        group_add_index ++;
        mesh_run(add_model_to_group,portMAX_DELAY, false);
    }
}
void add_model_to_group(void)
{
    //get values
    uint8_t node_index  = group_add_tab[group_add_index][0];
    uint8_t elmt_index  = group_add_tab[group_add_index][1];
    uint8_t group_index = group_add_tab[group_add_index][2];
    //send message
    config_model_subscribe_param_t param;
    param.elmt_addr = test_unprov_uni_addr[node_index] + elmt_index;
    param.model_id = GENERIC_ONOFF_SERVER_MODEL_ID;
    param.op_mode  = Subscription_Add;
    param.sig_model= true;
    param.subscribe_addr.is_virt = false;
    param.subscribe_addr.addr.addr = test_group_addr[group_index];
    config_model_subscription_update_tx(&config_client.model.base,&param,test_unprov_uni_addr[node_index],subscription_tx_done);

}
void config_client_config_group_subscribe(void)
{
    group_add_index = 0;
    mesh_run(add_model_to_group,portMAX_DELAY, false);
    /*
    add_model_to_group(0,0,0);
    add_model_to_group(0,1,0);
    add_model_to_group(1,0,0);
    add_model_to_group(1,1,0);
    add_model_to_group(2,0,1);
    add_model_to_group(2,1,1);
    add_model_to_group(3,0,1);
    add_model_to_group(3,1,1);
    */
}

void config_client_set_group_onoff(void)
{
    uint8_t group_index = mesh_app_uart_buff[1] - '0';
    uint8_t value       = mesh_app_uart_buff[2] - '0';
    onoff_val_normal.tid = alloc_generic_tid();
    onoff_val_normal.onoff = value;
    onoff_val_normal.trans_time = 0;
    onoff_val_normal.delay = 0;
    generic_onoff_set_unacknowledged_tx(&generic_onoff_client_0,&onoff_val_normal,sizeof(onoff_val_normal),test_group_addr[group_index]);
    
}

void config_client_allnode_onoff(void)
{
    uint8_t value       = mesh_app_uart_buff[2] - '0';
    onoff_val_normal.tid = alloc_generic_tid();
    onoff_val_normal.onoff = value;
    onoff_val_normal.trans_time = 0;
    onoff_val_normal.delay = 0;
    generic_onoff_set_unacknowledged_tx(&generic_onoff_client_0,&onoff_val_normal,sizeof(onoff_val_normal),ALL_NODES_GROUP_ADDR);
    
}



/***********************GROUP ACTION************************************/




void config_client_appkey_add_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_appkey_add_test_cb\n");
}
void config_client_model_app_bind_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_model_app_bind_test_cb\n");
}

void send_appkey_and_bind(void)
{
    uint8_t node_index = mesh_app_uart_buff[1] - '0';

    config_model_app_bind_param_t test_bind_param;

    //config_appkey_add_tx-> //ok
    config_appkey_add_tx(&config_client.model.base,&config_client.appkey[0],test_unprov_uni_addr[node_index],config_client_appkey_add_test_cb);

    //ELEMENT 0
    //config_model_app_bind_tx-> //
    test_bind_param.appkey_idx = TEST_PROV_APP_KEY_INDEX;
    test_bind_param.elmt_addr = test_unprov_uni_addr[node_index];
    test_bind_param.model_id = GENERIC_ONOFF_SERVER_MODEL_ID;
    test_bind_param.sig_model = true;
    config_model_app_bind_tx(&config_client.model.base,&test_bind_param,test_unprov_uni_addr[node_index],config_client_model_app_bind_test_cb);

    //ELEMENT 1
    //config_model_app_bind_tx-> //
    test_bind_param.appkey_idx = TEST_PROV_APP_KEY_INDEX;
    test_bind_param.elmt_addr = test_unprov_uni_addr[node_index]+1;
    test_bind_param.model_id = GENERIC_ONOFF_SERVER_MODEL_ID;
    test_bind_param.sig_model = true;
    config_model_app_bind_tx(&config_client.model.base,&test_bind_param,test_unprov_uni_addr[node_index],config_client_model_app_bind_test_cb);

}

void provisioner_complete_callback(uint8_t success , uint8_t reason)
{
    if(success == 1)
    {
        //bound local appkey.
       *generic_onoff_client_0.model.base.bound_key_buf = &config_client.appkey[0];
       *config_client.model.base.bound_key_buf = &config_client.appkey[0];

        //generate keys
        generate_device_key_by_ecdh_and_salt(NULL);
    }
}





void provisioner_aid_generate_done()
{
    LOG(3,"provisioner_aid_generate_done\n");

    //ELEMENT 0/1
    config_client.model.base.elmt = &client_elmts[0];
    client_elmts[0].uni_addr = TEST_PROV_UNICAST_ADDR;
}

void provisioner_net_key_all_keys_generate_done()
{
    LOG(3,"provisioner_net_key_all_keys_generate_done\n");

    //appkey gen
    config_client.appkey[0].global_idx = TEST_PROV_APP_KEY_INDEX;
    config_client.appkey[0].curr_idx = 0;
    config_client.appkey[0].is_used = true;
    config_client.appkey[0].bound_netkey = &config_client.netkey[0];
    memcpy(config_client.appkey[0].key[0].key , test_prov_app_key , MESH_KEY_LENGTH);
    k4_derivation(config_client.appkey[0].key[0].key , &config_client.appkey[0].key[0].aid , provisioner_aid_generate_done);

}

void init_config_client_model_keys_data(void)
{
    //sequence number/iv index
    sequence_number = TEST_PROV_SEQUENCE_NUM;
    //iv_index = provision_data.current_iv_index;
    mesh_beacon_iv_index_set(provision_data.current_iv_index);
    //netkey
    config_client.netkey[0].is_used = true;
    config_client.netkey[0].curr_idx = 0;
    config_client.netkey[0].global_idx = provision_data.key_index;
    memcpy(config_client.netkey[0].key[0].netkey , provision_data.network_key , MESH_KEY_LENGTH);
    generte_all_net_keys(&config_client.netkey[0].key[0] , provisioner_net_key_all_keys_generate_done);
}



#endif
#endif




