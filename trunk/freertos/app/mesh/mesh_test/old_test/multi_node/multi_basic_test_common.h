/*
 * multi_basic_test_common.h
 *
 *  Created on: 2018Äê5ÔÂ17ÈÕ
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_MULTI_NODE_MULTI_BASIC_TEST_COMMON_H_
#define FREERTOS_APP_MESH_MESH_TEST_MULTI_NODE_MULTI_BASIC_TEST_COMMON_H_

#include "provision_test.h"
#include "gpio.h"
#include "config_client.h"
#include "config_server.h"
#include "mesh_definitions.h"
#include "upper_transport.h"
#include "generic_onoff_client.h"
#include "generic_onoff_server.h"
#include "generic_onoff_common.h"
#include "co_endian.h"
//
#include "gpio.h"
#include "app_uart.h"
#include "stdint.h"
//
#include "multi_basic_test_server.h"
#include "multi_basic_test_client.h"



//MACRO
//#define TEST_APP_DEBUG
#define NUMBER_OF_NODES     8
//MACRO VAR
//CONFIG CLIENT
#define TEST_PROV_NET_KEY_INDEX     0x0123
#define TEST_PROV_FLAGS             0x00
#define TEST_PROV_IV_INDEX          0x12345678
#define TEST_PROV_UNICAST_ADDR      0x0003
#define TEST_PROV_SEQUENCE_NUM      0x3129ab
//CONFIG SERVER:NODE0 - NODE4
#define TEST_PROV_APP_KEY_INDEX     0x0456
//VAR
extern uint8_t  test_prov_net_key [MESH_KEY_LENGTH]  ;
extern uint8_t  test_prov_app_key [MESH_KEY_LENGTH]  ;
extern uint16_t test_unprov_uni_addr[NUMBER_OF_NODES];
extern uint16_t test_group_addr[2];

//ROLE
#define ROLE_UNPROV_CONFIG_SERVER  0
#define ROLE_PROVER_CONFIG_CLIENT  1


//EXTERN CAR
extern uint8_t prov_random[RANDOM_PDU_PARAMS_LEN];


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

//EXPORT VAR
extern uint8_t current_node_index;
extern uint8_t mesh_app_uart_buff[10];
extern volatile uint8_t provisioner_net_key_all_keys_generate;
extern volatile uint8_t unprov_dev_net_key_all_keys_generate ;
extern volatile uint8_t provisioner_aid_generate;
extern volatile uint8_t device_key_generate_done;

//EXPORT FUN
void generate_device_key_by_ecdh_and_salt(void (*cb)());



#endif /* FREERTOS_APP_MESH_MESH_TEST_MULTI_NODE_MULTI_BASIC_TEST_COMMON_H_ */
