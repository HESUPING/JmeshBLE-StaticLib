/*
 * mesh_uart_ctrl.c
 *
 *  Created on: 2018��6��13��
 *      Author: huichen
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"

#ifdef OSAPP_UART_LOG_TEST
#include "ecc_p256.h"
#include "mesh_uart_ctrl.h"

#ifdef MESH_TEST_UART_PROVISION
#include "unprov_dev_uart_test.h"
#include "provisioner_uart_test.h"

#ifdef MESH_TEST_UART_CLENT_SERVER
#include "client_server_uart_test.h"
#endif/* MESH_TEST_UART_CLENT_SERVER */

#ifdef MESH_UART_DEBUG_TEST_CMD
#include "uart_debug_test.h"
#endif/* MESH_UART_DEBUG_TEST_CMD */

// -----------  define
#define PROVISION_QUEUE_LENGTH   5

// -----------  extern value
TaskHandle_t handler_uart_prov_task;

// -----------  static value
static volatile uart_log_queue_init_t m_provision_task = task_noinit;
static QueueHandle_t m_provisionQueue;
static volatile uart_log_provision_env_t m_provision_env = MESH_UART_INIT;
// -----------  static function
//common
static void uart_ctrl_start(void);
static void provisioning_uart_msg_receive(void);
static void provisioning_system_msg_receive(const uart_log_provision_data_t *pmsg);
// -->>   provisioner
static void uart_provisioner_callback(uint8_t const *param,uint8_t len);
// -->>  unprov device
static void uart_unprov_dev_callback(uint8_t const *param,uint8_t len);
// -->> config client msg
static void uart_config_client_callback(uint8_t const *param,uint8_t len);
// -->> debug msg
static void uart_debug_callback(uint8_t const *param,uint8_t len);


/******USER FUNCTION******/
void app_mesh_test_init(void)
{
	//check
//	while(m_provision_env != MESH_INIT_DONE) vTaskDelay(5);//100ms
    //mesh_node_feature_config_init();
	m_provision_env = OSAPP_MESH_INIT;
	UART_TEST_LOG(LOG_LVL_INFO,"==OSAPP_MESH_INIT==\n");
}

void uart_prov_task(void *params)
{
//	LOG(3,"uart_prov_task start!\n");

	if(m_provision_task == task_noinit)
	{
		m_provisionQueue = xQueueCreate(PROVISION_QUEUE_LENGTH,sizeof(uart_log_provision_data_t));
		BX_ASSERT(m_provisionQueue!=NULL);
	/// <1> callback register
		//1. provisioner callback register
		uart_log_rx_callback_register(UART_PKTCMD_PROVISIONER_RX,uart_provisioner_callback);
		//2. unprov  dev  callback register
		uart_log_rx_callback_register(UART_PKTCMD_UNPROV_DEV_RX,uart_unprov_dev_callback);
		//3. config client callback register
		uart_log_rx_callback_register(UART_PKTCMD_CLIENT_RX,uart_config_client_callback);
		//4. debug callback register
		uart_log_rx_callback_register(UART_PKTCMD_DEBUG_RX,uart_debug_callback);

	/// <2> init register
		provisioner_uart_test_init(m_provisionQueue);
		unprov_dev_uart_test_init(m_provisionQueue);
	#ifdef MESH_TEST_UART_CLENT_SERVER
		client_server_uart_init(m_provisionQueue);
	#endif /* MESH_TEST_UART_CLENT_SERVER */

		m_provision_task = task_init;
	}

	while(1)
	{
		vTaskDelay(1);//20ms

		switch(m_provision_env)
		{
// --> common
		case MESH_UART_INIT://wait for osapp mesh init start
			UART_TEST_LOG(LOG_LVL_INFO,"==MESH_UART_INIT==\n");
			break;
		case OSAPP_MESH_INIT:
			UART_TEST_LOG(LOG_LVL_INFO,"==OSAPP_MESH_INIT==\n");
			m_provision_env = PROVISION_WAIT_MSG;
			break;
		default:
			uart_ctrl_start();
			break;
		}
	}
}
void uart_provision_env_set(uart_log_provision_env_t env)
{
	m_provision_env = env;
}
//----------------------------------------------------------------------------------------------------------------static func
static void uart_ctrl_start(void)
{
	switch(m_provision_env)
	{
// --> common
	case PROVISION_WAIT_MSG:
		UART_TEST_LOG(LOG_LVL_INFO,"==PROVISION_WAIT_MSG==\n");
		break;
	case MESH_INIT_DONE:
		UART_TEST_LOG(LOG_LVL_INFO,"==MESH_INIT_DONE==\n");
		break;
	case PROVISONING_DONE:
		UART_TEST_LOG(LOG_LVL_INFO,"==PROVISONING_DONE==\n");
		break;
// --> unprov device
	case MSG_UNPROV_DEV:
		UART_TEST_LOG(LOG_LVL_INFO,"==MSG_UNPROV_DEV==\n");
		break;
// --> provisioner
	case MSG_PROVIONER_DEV:
		UART_TEST_LOG(LOG_LVL_INFO,"==MSG_PROVIONER_DEV==\n");
		break;
#ifdef MESH_TEST_UART_CLENT_SERVER
// --> client server cfg
	case MSG_CFG_CLIENT:
		UART_TEST_LOG(LOG_LVL_INFO,"==MSG_CFG_CLIENT==\n");
		break;
	case MSG_CFG_CLIENT_INIT_DONE:
		UART_TEST_LOG(LOG_LVL_INFO,"==MSG_CFG_CLIENT_INIT_DONE==\n");
		break;
#endif /* MESH_TEST_UART_CLENT_SERVER */
	default:break;
	}
	//stk_chk_dbg();
	//wait  cfg  for msg receive
	provisioning_uart_msg_receive();
}


static void uart_provisioner_callback(uint8_t const *param,uint8_t len)
{
	if(m_provision_task == task_init)
	{
		provisioner_uart_test_rx_callback(param,len);
	}

    UART_TEST_LOG(LOG_LVL_INFO,"provisioner opcode: 0x%02x,len %d\n",param[0],len);
}
static void uart_unprov_dev_callback(uint8_t const *param,uint8_t len)
{
	if(m_provision_task == task_init)
	{
		unprov_dev_uart_test_rx_callback(param,len);
	}
	UART_TEST_LOG(LOG_LVL_INFO,"unprov_dev opcode: 0x%02x,len %d\n",param[0],len);
//    UART_TEST_LOG(LOG_LVL_INFO,"==uart_unprov_dev_callback==\n");
}
static void uart_config_client_callback(uint8_t const *param,uint8_t len)
{
	if(m_provision_task == task_init)
	{
#ifdef MESH_TEST_UART_CLENT_SERVER
		//config client callback
		client_server_uart_config_client_callback(param,len);
#endif /* MESH_TEST_UART_CLENT_SERVER */
	}
	UART_TEST_LOG(LOG_LVL_INFO,"config_client opcode: 0x%02x,len %d\n",param[0],len);
}

static void uart_debug_callback(uint8_t const *param,uint8_t len)
{
	if(m_provision_task == task_init)
	{
#ifdef MESH_UART_DEBUG_TEST_CMD
		//debug callback
		mesh_debug_uart_test_rx_callback(param,len);
#endif/* MESH_UART_DEBUG_TEST_CMD */
	}
}

static void provisioning_uart_msg_receive(void)
{
	uart_log_provision_data_t msg;
	xQueueReceive(m_provisionQueue,&msg,portMAX_DELAY);

	UART_TEST_LOG(LOG_LVL_INFO,"msg type: [0x%x] opcode: [0x%x] len [%d]\n",msg.device,msg.Opcode,msg.len);

	switch(msg.device)
	{
	case PC_SET_DEV_PROVISIONER :
		provisioner_uart_msg_receive(&msg);
		break;
	case PC_SET_DEV_UNPROV :
		unprov_uart_msg_receive(&msg);
		break;
#ifdef MESH_TEST_UART_CLENT_SERVER
	case PC_SET_CFG_CLIENT_MSG :
		client_server_uart_config_client_msg_receive(&msg);
		break;
#endif /* MESH_TEST_UART_CLENT_SERVER */
	case SYSTEM_MSG :
		provisioning_system_msg_receive(&msg);
		break;
	default:break;
	}

	if(msg.len) vPortFree(msg.param);
}
static void provisioning_system_msg_receive(const uart_log_provision_data_t *pmsg)
{
	switch(pmsg->Opcode)
	{
	case SYSTEM_MSG_PROVISIONING_DONE :
		m_provision_env = PROVISONING_DONE;
		break;
	default:break;
	}
	provisioner_uart_test_system_msg_receive(pmsg);
	unprov_dev_uart_test_system_msg_receive(pmsg);

#ifdef MESH_TEST_UART_CLENT_SERVER
	client_server_uart_system_msg_receive(pmsg);
#endif /* MESH_TEST_UART_CLENT_SERVER */
}
//----------------------------------------------------------------------------------------------------------------
#endif /* MESH_TEST_UART_PROVISION */
#endif /* OSAPP_UART_LOG_TEST */
#endif /* OSAPP_MESH */
