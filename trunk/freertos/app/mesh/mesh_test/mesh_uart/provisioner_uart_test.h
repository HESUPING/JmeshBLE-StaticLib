/*
 * provisioner_uart_test.h
 *
 *  Created on: 2018Äê4ÔÂ16ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_PROVISIONER_UART_TEST_H_
#define FREERTOS_APP_MESH_MESH_TEST_PROVISIONER_UART_TEST_H_

#include "mesh_uart_config.h"
#ifdef MESH_TEST_UART_PROVISION

///  ---------------   typedef
//pc and device  msg id (provisioner)
enum {
	// -- >device to pc
	TX_OP_PROV_BEACON_DATA = 0x01,
	TX_OP_PROV_LINK_ACK = 0x02,
	TX_OP_PROV_DEV_CAPABILITIES = 0x03,
	TX_OP_PROV_DEV_PUBLIC_KEY = 0x04,
	TX_OP_PROV_INPUT_AUTH_REQ = 0x05,
	TX_OP_PROV_OUTPUT_AUTH_VAL = 0x06,
	TX_OP_PROV_STATIC_AUTH_REQ = 0x07,
	TX_OP_PROV_DONE_STATE = 0x08,
	TX_OP_PROV_PRIVATE_KEY_REQ = 0x09,
	TX_OP_PROV_RANDOM_AUTH_REQ = 0x0A,
	TX_OP_PROV_OUTPUT_AUTH_REQ = 0x0B,

	TX_OP_PROV_OWN_PRIVATE_KEY = 0x20,
	TX_OP_PROV_OWN_PUBLIC_KEY = 0x21,
	TX_OP_PROV_INVITE_REQ= 0x22,
	TX_OP_PROV_DISTRIBUTION_DATA_REQ= 0x23,
	// -- > pc to device
	RX_OP_PROV_CFG = 0x85,
	RX_OP_PROV_PRIVATE_KEY = 0x81,
	RX_OP_PROV_RANDOM_AUTH_VAL = 0x82,
	RX_OP_PROV_INPUT_AUTH_VAL = 0x88,
	RX_OP_PROV_OUTPUT_AUTH_VAL = 0x8A,
	RX_OP_PROV_FLUSH_CACHE_VAL = 0x8B,
	RX_OP_PROV_STATIC_AUTH_VAL = 0x83,
	RX_OP_PROV_DISTRIBUTION_DATA = 0x84,
	RX_OP_PROV_BEACON_UUID = 0x91,
	RX_OP_PROV_INVITE_RSP = 0x86,
	RX_OP_PROV_START_PDU = 0x93,
	RX_OP_PROV_DEV_PUBLIC_KEY = 0x87,
};
typedef struct
{
	uint8_t prov_private_key[GAP_P256_KEY_LEN];
	public_key_t provisioner_public_key;
	volatile uint8_t provisioner_public_key_done;
	uart_log_mesh_beacon_t beacon;
	uint8_t attention_duration;
	provision_capabilities_t dev_capabilities;
	provision_data_t distribution;
	provision_start_t start_pdu;
	public_key_t dev_public_key;
	void (*read_peer_public_key_cb)(void);
	uart_log_provisioner_input_auth_t input_value;
	uart_log_provisioner_output_auth_t output_value;
	uint8_t static_value[AUTHVALUE_LEN];
	uint8_t random_value[AUTHVALUE_LEN];
	uart_log_provisioning_done_state_t done_state;
}uart_log_provisioner_owndata_t;
///  ---------------  EXTERN FUNCTION
//FUNCTION to system use
//==
extern void provisioner_uart_test_init(QueueHandle_t handle);
//==
extern void provisioner_uart_test_rx_callback(uint8_t const *param,uint8_t len);
//==
extern void provisioner_uart_test_system_msg_receive(const uart_log_provision_data_t *pmsg);
//==
extern void provisioner_uart_msg_receive(const uart_log_provision_data_t *pmsg);

#endif /* MESH_TEST_UART_PROVISION */
#endif /* FREERTOS_APP_MESH_MESH_TEST_PROVISIONER_UART_TEST_H_ */
