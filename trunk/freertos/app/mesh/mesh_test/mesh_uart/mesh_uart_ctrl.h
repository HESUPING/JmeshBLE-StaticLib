/*
 * mesh_uart_ctrl.h
 *
 *  Created on: 2018Äê6ÔÂ13ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_MESH_UART_MESH_UART_CTRL_H_
#define FREERTOS_APP_MESH_MESH_TEST_MESH_UART_MESH_UART_CTRL_H_

#include "provision_base.h"
#include "beacon.h"
#include "unprov_device.h"
#include "provisioner.h"
#include "mesh_definitions.h"
#include "LOG.h"
#include "mesh_uart_config.h"

#ifdef MESH_TEST_UART_PROVISION
#include "uart_log_test.h"
///  ---------------   define
/// define task priority of uart prov task. Should be careful some priority are defined in task_init.h
#define OS_PRIORITY_UART_PROV_TASK           (OS_PRIORITY_UART_LOG_TASK  - 1)		// 2
/// stack size of dht task
#define UART_PROV_TASK_STACK_SIZE             300//300*4 Bytes


//#define UART_UNPROV_OPCODE_PUBLIC_KEY   0x01//
///  ---------------   typedef
typedef enum {
// --> common state
  MESH_UART_INIT = 0,
  OSAPP_MESH_INIT,
  PROVISION_WAIT_MSG,
  MESH_INIT_DONE,
  PROVISONING_DONE,
// --> unprov device state
  MSG_UNPROV_DEV,
// --> provisioner state
  MSG_PROVIONER_DEV,
// --> config client state
  MSG_CFG_CLIENT,
  MSG_CFG_CLIENT_INIT_DONE,
}uart_log_provision_env_t;
typedef enum {
	SYSTEM_MSG = 0x00,
	PC_SET_CFG_CLIENT_MSG = 0x91,
	PC_SET_DEV_PROVISIONER = 0x92,
	PC_SET_DEV_UNPROV = 0x93,
	PC_SET_DEBUG = 0xf2,
}uart_log_provision_devset_t;
typedef enum {
	random_system = 0,
	random_user
}uart_log_provision_random_type_t;
typedef struct
{
	uint8_t Opcode;
	uint8_t len;
	uart_log_provision_devset_t device;
	void *param;
}uart_log_provision_data_t;
typedef struct
{
	uint8_t dev_uuid[MESH_DEVICE_UUID_LENGTH];
	uint32_t uri_hash;
	uint16_t oob_info;
}uart_log_mesh_beacon_t;
typedef struct
{
	uint8_t system[AUTHVALUE_LEN];
	uint8_t user[AUTHVALUE_LEN];
	uart_log_provision_random_type_t type;
}uart_log_provisioner_output_auth_t;
typedef struct
{
	uint8_t * pvalue;
	void (*cb)();
	uint8_t val[AUTHVALUE_LEN];
}uart_log_provisioner_input_auth_t;
typedef struct
{
	uint8_t reason;
	uint8_t success;
}uart_log_provisioning_done_state_t;

//system msg id
enum {
	// -- >system provisioner  msg
	SYSTEM_MSG_PROV_OWN_PUBLIC_KEY,
	SYSTEM_MSG_UNPROV_OWN_PUBLIC_KEY,
	SYSTEM_MSG_SECURITY_INIT_DONE,
	SYSTEM_MSG_CLIENT_ALL_NET_KEY,
	SYSTEM_MSG_CLIENT_APP_AID_KEY,
	SYSTEM_MSG_CLIENT_DEV_KEY,
	SYSTEM_MSG_SERVER_DEV_KEY,
	SYSTEM_MSG_CLIENT_DATA_INIT_DONE,
	SYSTEM_MSG_PROVISIONING_DONE,
};
///  ---------------  EXTERN value
/// extern the handler of uart prov task which can be use when create uart log task.
extern TaskHandle_t handler_uart_prov_task;

///  ---------------  EXTERN FUNCTION
//FUNCTION to system use
extern void uart_prov_task(void *params);
//FUNCTION to uesr use
//Common
extern void app_mesh_test_init(void);
//==
extern void uart_provision_env_set(uart_log_provision_env_t env);

#endif /* MESH_TEST_UART_PROVISION */
#endif /* FREERTOS_APP_MESH_MESH_TEST_MESH_UART_MESH_UART_CTRL_H_ */
