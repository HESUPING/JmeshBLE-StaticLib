/*
 * unprov_dev_test.c
 *
 *  Created on: 2018-1-22
 *      Author: jiachuang
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "provision_test.h"
#include "ecc_p256.h"
#include "mesh_test_config.h"

#ifdef MESH_TEST_PROVISION


uint8_t unprov_dev_uuid[16] = {0x70,0xcf,0x7c,0x97,0x32,0xa3,0x45,0xb6,0x91,0x49,0x48,0x10,0xd2,0xe9,0xcb,0xf4};
uint32_t unprov_uri_hash  = 0xd97478b3;
uint16_t unprov_dev_OOB_info = 0x4020;
public_key_t unprov_dev_public_key = {0};
//0xf4,0x65,0xe4,0x3f,0xf2,0x3d,0x3f,0x1b,0x9d,0xc7,0xdf,0xc0,0x4d,0xa8,0x75,0x81,0x84,0xdb,0xc9,0x66,0x20,0x47,0x96,0xec,0xcf,0x0d,0x6c,0xf5,0xe1,0x65,0x00,0xcc,
//0x02,0x01,0xd0,0x48,0xbc,0xbb,0xd8,0x99,0xee,0xef,0xc4,0x24,0x16,0x4e,0x33,0xc2,0x01,0xc2,0xb0,0x10,0xca,0x6b,0x4d,0x43,0xa8,0xa1,0x55,0xca,0xd8,0xec,0xb2,0x79
//};
uint8_t unprov_dev_private_key[GAP_P256_KEY_LEN] = {
0x52,0x9a,0xa0,0x67,0x0d,0x72,0xcd,0x64,0x97,0x50,0x2e,0xd4,0x73,0x50,0x2b,0x03,0x7e,0x88,0x03,0xb5,0xc6,0x08,0x29,0xa5,0xa3,0xca,0xa2,0x19,0x50,0x55,0x30,0xba
};
uint8_t unprov_dev_random[RANDOM_PDU_PARAMS_LEN] = {
0x55,0xa2,0xa2,0xbc,0xa0,0x4c,0xd3,0x2f,0xf6,0xf3,0x46,0xbd,0x0a,0x0c,0x1a,0x3a
};
volatile uint8_t unprov_dev_public_key_gen_done = 0;

uint8_t user_compare_uuid_with_own(uint8_t *dev_uuid)
{
	if(memcmp(dev_uuid,unprov_dev_uuid,BEACON_UUID_LEN) == 0) 
	{
	    return true;
	}
	else     
	{
	    return false;
	}
}

void unprov_dev_make_attention_user(uint8_t duration)
{
    return;
}



void unprov_dev_capabilities_init_user(void)
{
    provision_capabilities.elements_num = 0x01;
    provision_capabilities.algorithms = 0x0001;
}

void user_unprov_dev_expose_public_key_oob(public_key_t * public_keys)
{
    return;
}

void user_unprov_provision_input_auth_value(uint8_t *buff,void (*cb)())
{
    memcpy(buff,static_auth_value,AUTHVALUE_LEN);
    cb();
}
void user_unprov_provision_output_auth_value(uint8_t *buff)
{
    memcpy(buff,static_auth_value,AUTHVALUE_LEN);
    return;
}
void user_unprov_provision_static_auth_value(uint8_t *buff)
{
    memcpy(buff,static_auth_value,AUTHVALUE_LEN);
}

void unprov_dev_provision_done(uint8_t success , uint8_t reason)
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
        extern void unprov_dev_complete_callback(uint8_t success , uint8_t reason);
        unprov_dev_complete_callback(success,reason);
    #endif
}

//Generate unprov_dev's public key
void unprov_dev_gen_public_keys_done(void* aaaaa)
{
    reverse_self(unprov_dev_private_key,GAP_P256_KEY_LEN);
    reverse_self(unprov_dev_public_key.x,GAP_P256_KEY_LEN);
    reverse_self(unprov_dev_public_key.y,GAP_P256_KEY_LEN);
    unprov_dev_public_key_gen_done = 1;
}
void unprov_dev_gen_public_keys(void)
{
    unprov_dev_public_key_gen_done = 0;
    reverse_self(unprov_dev_private_key,GAP_P256_KEY_LEN);
    ecc_gen_new_public_key_usr(unprov_dev_private_key,unprov_dev_public_key.x,unprov_dev_public_key.y,unprov_dev_gen_public_keys_done);
    while(unprov_dev_public_key_gen_done != 1);
}

void user_unprovisioned_function_init(void)
{
    //init function
    unprov_dev_make_attention = unprov_dev_make_attention_user;
    unprov_dev_capabilities_init = unprov_dev_capabilities_init_user;
    unprov_dev_expose_public_key_oob = user_unprov_dev_expose_public_key_oob;
    provision_input_auth_value  = user_unprov_provision_input_auth_value;
    provision_output_auth_value = user_unprov_provision_output_auth_value;
    provision_static_auth_value = user_unprov_provision_static_auth_value;
    user_provision_done = unprov_dev_provision_done;
    compare_uuid_with_own=user_compare_uuid_with_own;
    
    //run init functino
    unprov_dev_capabilities_init();
}


void app_mesh_test_unprodev_init(void)
{
    unprov_dev_gen_public_keys();
	unprovisioned_dev_reset();
	user_unprovisioned_function_init();
	memcpy(&provision_key.local_public,&unprov_dev_public_key,sizeof(public_key_t));
	memcpy(provision_random.field.random_device,unprov_dev_random,RANDOM_PDU_PARAMS_LEN);
	memcpy(provision_key.private,unprov_dev_private_key,GAP_P256_KEY_LEN);
	unprovisioned_dev_beacon_start(unprov_dev_uuid , unprov_dev_OOB_info , &unprov_uri_hash);
	LOG(LOG_LVL_INFO,current_stage_s[current_stage]);
}
#endif
#endif
