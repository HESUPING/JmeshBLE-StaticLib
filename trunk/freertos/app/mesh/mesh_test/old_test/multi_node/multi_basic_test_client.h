/*
 * multi_basic_test_client.h
 *
 *  Created on: 2018Äê5ÔÂ17ÈÕ
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_MULTI_NODE_MULTI_BASIC_TEST_CLIENT_H_
#define FREERTOS_APP_MESH_MESH_TEST_MULTI_NODE_MULTI_BASIC_TEST_CLIENT_H_
#include "multi_basic_test_common.h"


void provisioner_init_mesh_provision_data(void);
void provisioner_complete_callback(uint8_t success , uint8_t reason);
void init_config_client_model_keys_data(void);
void config_client_set_element(void);
void send_appkey_and_bind(void);
void provisioner_start_prov(void);
void config_client_config_group_subscribe(void);
void config_client_set_group_onoff(void);
void config_client_allnode_onoff(void);




#endif /* FREERTOS_APP_MESH_MESH_TEST_MULTI_NODE_MULTI_BASIC_TEST_CLIENT_H_ */
