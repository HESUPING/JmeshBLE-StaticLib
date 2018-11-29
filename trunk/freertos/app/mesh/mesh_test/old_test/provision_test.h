/*
 * provision_test.h
 *
 *  Created on: 2018-1-22
 *      Author: jiachuang
 */
#ifndef FREERTOS_APP_MESH_MESH_TEST_PROVISION_TEST_H_
#define FREERTOS_APP_MESH_MESH_TEST_PROVISION_TEST_H_

#include "provision_base.h"
#include "beacon.h"
#include "unprov_device.h"
#include "provisioner.h"
#include "LOG.h"

#include "mesh_test_config.h"

#ifdef MESH_TEST_PROVISION


//Common
void app_mesh_test_init(void);



//provisioner
extern public_key_t provisioner_public_key;
extern uint8_t static_auth_value[AUTHVALUE_LEN];
void user_unprovisioned_dev_beacon_rx_callback(uint8_t *dev_uuid,uint16_t oob_info,uint32_t *uri_hash);
void app_mesh_test_provisioner_init(void);
void user_provisioner_link_ack_rx_callback(void);
void user_provisioner_capabilities_rx_callback(provision_capabilities_t * para);
void user_provisioner_read_peer_public_key_oob(void (*callback)(void));
void user_provisioner_provision_input_auth_value(uint8_t *buff,void (*cb)());
void user_provisioner_provision_output_auth_value(uint8_t *buff);
void user_provisioner_provision_static_auth_value(uint8_t *buff);
void provisioner_provision_done(uint8_t success , uint8_t reason);


//unprov_device
extern public_key_t unprov_dev_public_key;
uint8_t user_compare_uuid_with_own(uint8_t *dev_uuid);
void app_mesh_test_unprodev_init(void);
void unprov_dev_make_attention_user(uint8_t duration);
void unprov_dev_capabilities_init_user(void);
void user_unprov_dev_expose_public_key_oob(public_key_t * public_keys);
void user_unprov_provision_input_auth_value(uint8_t *buff,void (*cb)());
void user_unprov_provision_output_auth_value(uint8_t *buff);
void user_unprov_provision_static_auth_value(uint8_t *buff);
void unprov_dev_provision_done(uint8_t success , uint8_t reason);

#endif









#endif /* FREERTOS_APP_MESH_MESH_TEST_PROVISION_TEST_H_ */

