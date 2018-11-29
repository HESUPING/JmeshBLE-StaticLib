/*
 * unprov_dev_uart_test.c
 *
 *  Created on: 2018��6��13��
 *      Author: huichen
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#ifdef OSAPP_UART_LOG_TEST
#include "mesh_uart_ctrl.h"
#ifdef MESH_TEST_UART_PROVISION
#include "unprov_dev_uart_test.h"
#include "ecc_p256.h"

#ifdef MESH_TEST_UART_CLENT_SERVER
#include "client_server_uart_test.h"
#endif/* MESH_TEST_UART_CLENT_SERVER */
//gatt
#include "provisioning_s.h"
#include "proxy_s.h"

//----------------------------------------------------------------------------------------------------------------
// -----------  define
//mask define
#define ROLE_CFG_INIT_MASK_INIT 	   0x00 //role not init
#define ROLE_CFG_INIT_MASK_PROVISIONER 0x01 //provisioner init
#define ROLE_CFG_INIT_MASK_UNPROV_DEV  0x02 //unprov device init

// -----------  extern function
extern void reverse_self(void * src , uint8_t length);
extern void (*unprovisioned_dev_beacon_rx_callback)(uint8_t *,uint16_t ,uint32_t *);
// -----------  static function
// -->>  unprov device
static void provisioning_unprov_uart_send(const uart_log_provision_data_t *param);
//cmd
static void unprov_device_set_config_init(void);
static void app_unprov_set_beacon_data_value(const uint8_t *param);
static void unprov_set_private_keys(const uint8_t *pkey);
static void unprov_gen_public_keys(void);
static void unprov_gen_public_keys_done(void* param);
static void unprov_send_public_keys(void);
static void app_unprov_device_init(void);
static void app_unprov_set_random_auth_value(const uint8_t *param);
static void user_unprov_function_init(void);
static void user_unprov_dev_beacon_rx_callback(uint8_t *dev_uuid,uint16_t oob_info,uint32_t *uri_hash);
static void user_unprov_dev_make_attention(uint8_t duration);
static void user_unprov_dev_expose_public_key_oob(public_key_t * public_keys);
static void user_unprov_dev_capabilities_init(void);
static void app_unprov_set_dev_capabilities(const uint8_t *param);
static void user_unprov_provision_input_auth_value(uint8_t *buff,void (*cb)());
static void app_unprov_set_input_auth_value(const uint8_t *param);
static void user_unprov_provision_output_auth_value(uint8_t *buff);
static void app_unprov_set_output_auth_value(const uint8_t *param);
static void user_unprov_provision_static_auth_value(uint8_t *buff);
static void app_unprov_set_static_auth_value(const uint8_t *param);
static uint8_t user_compare_uuid_with_own(uint8_t *dev_uuid);
static void user_unprov_dev_provision_done(uint8_t success , uint8_t reason);

// -----------  static value
static QueueHandle_t m_unprovQueue;
static uart_log_unprov_owndata_t  m_unprov;
static uint8_t m_role = 0;
//----------------------------------------------------------------------------------------------------------------
/******USER FUNCTION******/
void unprov_dev_uart_test_init(QueueHandle_t handle)
{
	m_unprovQueue = handle;
}

void unprov_dev_uart_test_rx_callback(uint8_t const *param,uint8_t len)
{
	//parse  msg
	uart_log_provision_data_t msg;
	msg.device = PC_SET_DEV_UNPROV;
	msg.Opcode = param[0];
	msg.len = len-1;
	if(msg.len)
	{
		msg.param = (uint8_t *)pvPortMalloc(msg.len *sizeof(uint8_t));
		BX_ASSERT(msg.param!=NULL);
		memcpy(msg.param,(param+1),msg.len );
	}

	if(xQueueSend(m_unprovQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
void unprov_dev_uart_test_system_msg_receive(const uart_log_provision_data_t *pmsg)
{
	switch(pmsg->Opcode)
	{
	case SYSTEM_MSG_UNPROV_OWN_PUBLIC_KEY :
		//1. send public key
		unprov_send_public_keys();
		//2. app init
		app_unprov_device_init();
		//3. set mesh init done
//		m_provision_env = MESH_INIT_DONE;
		uart_provision_env_set(MESH_INIT_DONE);
		//4. send to pc  beacon data req
		uart_log_provision_data_t unprov;
		unprov.Opcode = TX_OP_UNPROV_BEACON_DATA_REQ;
		unprov.len = 0;
		provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
		break;
	default:break;
	}
}
void unprov_uart_msg_receive(const uart_log_provision_data_t *pmsg)
{
	if(m_role != ROLE_CFG_INIT_MASK_UNPROV_DEV)
	{
		if(m_role != ROLE_CFG_INIT_MASK_INIT)
		{
			UART_TEST_LOG(LOG_LVL_INFO,"!!! unprov dev init error: 0x%02x !!!\n",m_role);
		}
		else
		{
			switch(pmsg->Opcode)
			{
			case RX_OP_UNPROV_CFG :
				if(pmsg->len == 1)
				{
					uint8_t *pconfig = (uint8_t *)(pmsg->param);

					if(pconfig && pconfig[0])//cfg unprov device
					{
						//1. cfg provisioner
						uart_provision_env_set(MSG_UNPROV_DEV);
		//				m_provision_env = MSG_UNPROV_DEV;
						unprov_device_set_config_init();
					}
					else
					{
						uart_provision_env_set(MESH_INIT_DONE);
		//				m_provision_env = MESH_INIT_DONE;
					}
				}
				break;
			default:break;
			}
		}
	}
	else
	{
		switch(pmsg->Opcode)
		{
		case RX_OP_UNPROV_CFG :
			if(pmsg->len == 1)
			{
				uint8_t *pconfig = (uint8_t *)(pmsg->param);

				if(pconfig && pconfig[0])//cfg unprov device
				{
					//1. cfg provisioner
					uart_provision_env_set(MSG_UNPROV_DEV);
	//				m_provision_env = MSG_UNPROV_DEV;
					unprov_device_set_config_init();
				}
				else
				{
					uart_provision_env_set(MESH_INIT_DONE);
	//				m_provision_env = MESH_INIT_DONE;
				}
			}
			break;
		case RX_OP_UNPROV_BEACON_DATA_VAL :
			if(pmsg->len == 22)
			{
				app_unprov_set_beacon_data_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_UNPROV_PRIVATE_KEY :
			if(pmsg->len == GAP_P256_KEY_LEN)
			{
				unprov_set_private_keys((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_UNPROV_RANDOM_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				uart_log_provision_data_t unprov;
				// send to pc  private key req
				unprov.Opcode = TX_OP_UNPROV_PRIVATE_KEY_REQ;
				unprov.len = 0;
				provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

				app_unprov_set_random_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_UNPROV_DEV_CAPABILITIES :
			if(pmsg->len == 11)
			{
				uart_log_provision_data_t unprov;
				// send to pc  auth random req
				unprov.Opcode = TX_OP_UNPROV_RANDOM_AUTH_REQ;
				unprov.len = 0;
				provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

				app_unprov_set_dev_capabilities((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_UNPROV_INPUT_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				app_unprov_set_input_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_UNPROV_OUTPUT_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				uart_log_provision_data_t unprov;
				//send to pc  capabilities req
				unprov.Opcode = TX_OP_UNPROV_CAPABILITIES_REQ;
				unprov.len = 0;
				provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

				app_unprov_set_output_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_UNPROV_STATIC_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				uart_log_provision_data_t unprov;
				//send to pc  output random req
				unprov.Opcode = TX_OP_UNPROV_OUTPUT_AUTH_REQ;
				unprov.len = 0;
				provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

				app_unprov_set_static_auth_value((uint8_t *)pmsg->param);
			}
			break;

		default:break;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------static func
static void provisioning_unprov_uart_send(const uart_log_provision_data_t *param)
{
	uart_log_tx_env_t unprov;

	if(param)
	{
		unprov.cmd = UART_PKTCMD_UNPROV_DEV_TX;
		unprov.tx_len = param->len+1;
		if(unprov.tx_len)
		{
			unprov.pdata = (uint8_t *)pvPortMalloc(unprov.tx_len);
			BX_ASSERT(unprov.pdata!=NULL);
			unprov.pdata[0] = param->Opcode;
		}

		switch(param->Opcode)
		{
		case TX_OP_UNPROV_INPUT_AUTH_REQ :
		case TX_OP_UNPROV_OUTPUT_AUTH_REQ :
		case TX_OP_UNPROV_STATIC_AUTH_REQ :
		case TX_OP_UNPROV_RANDOM_AUTH_REQ :
		case TX_OP_UNPROV_PRIVATE_KEY_REQ :
		case TX_OP_UNPROV_BEACON_DATA_REQ :
		case TX_OP_UNPROV_DONE_STATE :
		case TX_OP_UNPROV_CAPABILITIES_REQ :
		case TX_OP_UNPROV_ATTENTION_DURATION:
		case TX_OP_UNPROV_OUTPUT_AUTH_VAL :
		case TX_OP_UNPROV_DISTRIBUTION_DATA:
			{
				if(param->len)
				{
					memcpy((uint8_t *)(unprov.pdata+1),(uint8_t *)(param->param),param->len);
				}
			}
			break;
		case TX_OP_UNPROV_OWN_PUBLIC_KEY :
			{
				if(param->len)
				{
					memcpy((public_key_t  *)(unprov.pdata+1),(public_key_t *)(param->param),param->len);
				}
			}
			break;
		default:break;
		}

		uart_log_send_cmd(unprov.cmd,unprov.pdata,unprov.tx_len);
		if(unprov.tx_len) vPortFree(unprov.pdata);
	}
}
// -->>   unprov device
static void unprov_device_set_config_init(void)
{
	if(!m_role)
	{
		/// <1>
		unprovisioned_dev_init();// just run once
		/// <2>  unprovisioned_dev callback register
		user_unprov_function_init();
		/// <3>
		//mesh_init_start_scan();

		m_role |= ROLE_CFG_INIT_MASK_UNPROV_DEV;
	}

	if(m_role == ROLE_CFG_INIT_MASK_UNPROV_DEV)
	{
		uart_log_provision_data_t unprov;

	//	//1. send to pc  beacon data req
	//	unprov.Opcode = TX_OP_UNPROV_BEACON_DATA_REQ;
	//	unprov.len = 0;
	//	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	//
	//	//2. send to pc  private key req
	//	unprov.Opcode = TX_OP_UNPROV_PRIVATE_KEY_REQ;
	//	unprov.len = 0;
	//	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	//
	//	//3. send to pc  auth random req
	//	unprov.Opcode = TX_OP_UNPROV_RANDOM_AUTH_REQ;
	//	unprov.len = 0;
	//	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	//
	//	//4. send to pc  capabilities req
	//	unprov.Opcode = TX_OP_UNPROV_CAPABILITIES_REQ;
	//	unprov.len = 0;
	//	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	//
	//	//5. send to pc  output random req
	//	unprov.Opcode = TX_OP_UNPROV_OUTPUT_AUTH_REQ;
	//	unprov.len = 0;
	//	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

		//6. send to pc  static value init
		unprov.Opcode = TX_OP_UNPROV_STATIC_AUTH_REQ;
		unprov.len = 0;
		provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	}
	else
	{
		UART_TEST_LOG(LOG_LVL_INFO,"!!! unprov dev init error: 0x%02x !!!\n",m_role);
	}
}
static void app_unprov_set_beacon_data_value(const uint8_t *param)
{
	if(param)//not null
	{
		//save data
		memcpy(m_unprov.beacon.dev_uuid,param,16);
		memcpy((uint8_t *)&(m_unprov.beacon.oob_info),(param+16),2);
		memcpy((uint8_t *)&(m_unprov.beacon.uri_hash),(param+16+2),4);

		//TODO <by user select  adv/gatt prosioning beacon data>
		//beaconing
		//unprovisioned_dev_beacon_start(m_unprov.beacon.dev_uuid , m_unprov.beacon.oob_info , &m_unprov.beacon.uri_hash);
#ifdef OSAPP_MESH_GATT_PROVISIONING_TEST
	    ble_mesh_gatt_adv_start(PROXY_ADV_EVT_PROVISIONING_START,(const uint8_t *)&m_unprov.beacon);
#endif /* OSAPP_MESH_GATT_PROVISIONING_TEST */
		LOG(LOG_LVL_INFO,"app_unprov_set_beacon_data_value\n");
		LOG(LOG_LVL_INFO,current_stage_s[current_stage]);
	}
}
static void unprov_set_private_keys(const uint8_t *pkey)
{
	if(pkey)
	{
		//1. copy private key
		memcpy(m_unprov.unprov_private_key,pkey,GAP_P256_KEY_LEN);
		//2. set mesh system  private key
	    memcpy(provision_key.private,m_unprov.unprov_private_key,GAP_P256_KEY_LEN);
		//3. gen public key
		unprov_gen_public_keys();
	}
}
//Generate provisioner's public key
static void unprov_gen_public_keys_done(void* param)
{
	//1. Adjust the order
    reverse_self(m_unprov.unprov_private_key,GAP_P256_KEY_LEN);
    reverse_self(m_unprov.unprov_public_key.x,GAP_P256_KEY_LEN);
    reverse_self(m_unprov.unprov_public_key.y,GAP_P256_KEY_LEN);
	//2. set done flag
    m_unprov.unprov_public_key_done = 1;
	//3. set mesh system public keys
    memcpy(&provision_key.local_public,&m_unprov.unprov_public_key,sizeof(public_key_t));
    //4. send system msg
	{
		//parse  msg
		uart_log_provision_data_t msg;
		msg.device = SYSTEM_MSG;
		msg.Opcode = SYSTEM_MSG_UNPROV_OWN_PUBLIC_KEY;
		msg.len = 0;

		if(xQueueSend(m_unprovQueue,&msg,portMAX_DELAY)!=pdTRUE)
		{
			BX_ASSERT(0);
		}
	}
}
static void unprov_gen_public_keys(void)
{
	//0. clear done flag
	m_unprov.unprov_public_key_done = 0;
	//1. Adjust the order
	reverse_self(m_unprov.unprov_private_key,GAP_P256_KEY_LEN);
	//2. ecc_gen_new_public_key
    ecc_gen_new_public_key_usr(m_unprov.unprov_private_key,m_unprov.unprov_public_key.x,m_unprov.unprov_public_key.y,unprov_gen_public_keys_done);
}
static void unprov_send_public_keys(void)
{
	while(!m_unprov.unprov_public_key_done);
    //1. send to pc  public key
	{
		uart_log_provision_data_t unprov;
		unprov.Opcode = TX_OP_UNPROV_OWN_PUBLIC_KEY;
		unprov.param = (public_key_t *)&m_unprov.unprov_public_key;
		unprov.len = (GAP_P256_KEY_LEN)+(GAP_P256_KEY_LEN);
		provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	}
}
static void app_unprov_device_init(void)
{
/// <1>
	//1.clean bear rx  msg cache
	mesh_flush_msg_cache();
	//2. role init          unprovisioned_dev_init reset
	unprovisioned_dev_reset();
/// <2> updata init data
	//3. set mesh system random num
    memcpy(provision_random.field.random_device,m_unprov.random_value,AUTHVALUE_LEN);
///// <3>
//    //4.  unprovisioned_dev callback register
//	user_unprov_function_init();
///// <4>
//	user_app_mesh_test_init_done();

	LOG(LOG_LVL_INFO,"user_app_mesh_test_init_done\n");
}
static void app_unprov_set_random_auth_value(const uint8_t *param)
{
	if(param)//not null
	{
		//1. copy random auth value
		memcpy(m_unprov.random_value,param,AUTHVALUE_LEN);
		//2. set mesh system random num
	    memcpy(provision_random.field.random_device,m_unprov.random_value,AUTHVALUE_LEN);
	}
}
static void user_unprov_function_init(void)
{
    //init function
	//1. beacon callback
	unprovisioned_dev_beacon_rx_callback = user_unprov_dev_beacon_rx_callback;//just register it,do nothing
    unprov_dev_make_attention = user_unprov_dev_make_attention;
    unprov_dev_capabilities_init = user_unprov_dev_capabilities_init;
    unprov_dev_expose_public_key_oob = user_unprov_dev_expose_public_key_oob;
    provision_input_auth_value  = user_unprov_provision_input_auth_value;
    provision_output_auth_value = user_unprov_provision_output_auth_value;
    provision_static_auth_value = user_unprov_provision_static_auth_value;
    compare_uuid_with_own=user_compare_uuid_with_own;
    user_provision_done = user_unprov_dev_provision_done;
    //run init functin
    unprov_dev_capabilities_init();
}
static void user_unprov_dev_beacon_rx_callback(uint8_t *dev_uuid,uint16_t oob_info,uint32_t *uri_hash)
{
	//do nothing
}
static void user_unprov_dev_make_attention(uint8_t duration)
{
	uart_log_provision_data_t unprov;
	//1. save data
	m_unprov.attention_duration = duration;
	//2. send to pc  attention_duration value
	unprov.Opcode = TX_OP_UNPROV_ATTENTION_DURATION;
	unprov.len = 1;
	unprov.param = (uint8_t *)pvPortMalloc(unprov.len);
	BX_ASSERT(unprov.param!=NULL);
	//3. copy attention_duration data
	memcpy((uint8_t *)unprov.param,(uint8_t *)&m_unprov.attention_duration,unprov.len);
	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	if(unprov.param) vPortFree(unprov.param);
}
static void user_unprov_dev_capabilities_init(void)
{
//    provision_capabilities.elements_num = 0x01;
//    provision_capabilities.algorithms = 0x0001;
	//2. set capabilities data
	memcpy((provision_capabilities_t *)&provision_capabilities,(provision_capabilities_t *)&m_unprov.dev_capabilities,sizeof(provision_capabilities_t));
}
static void app_unprov_set_dev_capabilities(const uint8_t *param)
{
    if(param)// not null
	{
		//1. copy capabilities data
		memcpy((uint8_t *)&m_unprov.dev_capabilities.elements_num,param,1);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.algorithms,(param+1),2);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.public_key_type,(param+1+2),1);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.static_oob_type,(param+1+2+1),1);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.output_oob_size,(param+1+2+1+1),1);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.output_oob_action,(param+1+2+1+1+1),2);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.input_oob_size,(param+1+2+1+1+1+2),1);
		memcpy((uint8_t *)&m_unprov.dev_capabilities.input_oob_action,(param+1+2+1+1+1+2+1),2);
		//2. set capabilities data
		memcpy((provision_capabilities_t *)&provision_capabilities,(provision_capabilities_t *)&m_unprov.dev_capabilities,sizeof(provision_capabilities_t));
	}
}
static void user_unprov_dev_expose_public_key_oob(public_key_t * public_keys)
{
    //1. send to pc  public key
	if(public_keys);
	{
		uart_log_provision_data_t unprov;
		unprov.Opcode = TX_OP_UNPROV_OWN_PUBLIC_KEY;
		unprov.param = public_keys;
		unprov.len = (GAP_P256_KEY_LEN)+(GAP_P256_KEY_LEN);
		provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);
	}
	//send public keys
	//unprov_send_public_keys();
}
static void user_unprov_provision_input_auth_value(uint8_t *buff,void (*cb)())
{
	if(buff&&cb)// not null
	{
		uart_log_provision_data_t unprov;

		//1. send to pc  input auth req
		unprov.Opcode = TX_OP_UNPROV_INPUT_AUTH_REQ;
		unprov.len = 0;
		provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

		//2. save pvalue hanlde and callback
		m_unprov.input_value.pvalue = buff;
		m_unprov.input_value.cb = cb;
	}
}
static void app_unprov_set_input_auth_value(const uint8_t *param)
{
	if(param)//not null
	{
		//unprov start
		//1. save
		memcpy((uint8_t *)&m_unprov.input_value.val,param,AUTHVALUE_LEN);
		//2. set
		if(m_unprov.input_value.pvalue)//not null
		{
			memcpy(m_unprov.input_value.pvalue,param,AUTHVALUE_LEN);
		}
		//3. send to mesh
		if(m_unprov.input_value.cb)//not null
		{
			m_unprov.input_value.cb();
		}
	}
}
static void user_unprov_provision_output_auth_value(uint8_t *buff)
{
	if(buff)// not null
	{
		uart_log_provision_data_t unprov;
		uint8_t *pout;

		if(m_unprov.output_value.type != random_user)
		{
			pout = m_unprov.output_value.system;
			//1. gen rand output auth value
			random_gen_words(pout,AUTHVALUE_LEN);
		}
		else
		{
			pout = m_unprov.output_value.user;
		}

		//2. set to mesh rand output auth value
		memcpy(buff,pout,AUTHVALUE_LEN);
		//3. send to pc  output auth value
		unprov.Opcode = TX_OP_UNPROV_OUTPUT_AUTH_VAL;
		unprov.len = AUTHVALUE_LEN;
		unprov.param = (uint8_t *)pvPortMalloc(unprov.len);
		BX_ASSERT(unprov.param!=NULL);
		//4. copy output auth value data
		memcpy((uint8_t *)unprov.param,pout,unprov.len);

		provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

		if(unprov.param) vPortFree(unprov.param);
	}
}
static void app_unprov_set_output_auth_value(const uint8_t *param)
{
	if(param)// not null
	{
		//1. copy static auth value
		m_unprov.output_value.type = random_user;
		memcpy(m_unprov.output_value.user,param,AUTHVALUE_LEN);
	}
}
static void user_unprov_provision_static_auth_value(uint8_t *buff)
{
	if(buff)// not null
	{
		//1. copy static auth value
		memcpy(buff,m_unprov.static_value,AUTHVALUE_LEN);
	}
}
static void app_unprov_set_static_auth_value(const uint8_t *param)
{
	if(param)// not null
	{
		//1. copy static auth value
		memcpy(m_unprov.static_value,param,AUTHVALUE_LEN);
	}
}
static uint8_t user_compare_uuid_with_own(uint8_t *dev_uuid)
{
	if(memcmp(dev_uuid,m_unprov.beacon.dev_uuid,BEACON_UUID_LEN) == 0)
	{
	    return true;
	}
	else
	{
	    return false;
	}
}
static void user_unprov_dev_provision_done(uint8_t success , uint8_t reason)
{
	volatile uart_log_provision_data_t unprov;

/// <1> send result
	//1. save data
    m_unprov.done_state.success = success;
    m_unprov.done_state.reason = reason;

	//2. send to pc  provision_done
	unprov.Opcode = TX_OP_UNPROV_DONE_STATE;
	unprov.len = 2;
	unprov.param = (uint8_t *)pvPortMalloc(unprov.len);
	BX_ASSERT(unprov.param!=NULL);
	//3. copy output auth value data
	((uint8_t *)unprov.param)[0] = m_unprov.done_state.success;
	((uint8_t *)unprov.param)[1] = m_unprov.done_state.reason;

	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

	if(unprov.param) vPortFree(unprov.param);

/// <2> send distribution data
	unprov.Opcode = TX_OP_UNPROV_DISTRIBUTION_DATA;
	unprov.len = 25;
	unprov.param = (uint8_t *)pvPortMalloc(unprov.len);
	BX_ASSERT(unprov.param!=NULL);
	// save distribution value data
	memcpy(&m_unprov.distribution,&provision_data,sizeof(provision_data_t));
	// copy distribution data
	//1. network_key
	memcpy((uint8_t *)unprov.param,m_unprov.distribution.network_key,16);
	//2. key_index     lsb
	((uint8_t *)unprov.param)[16] = m_unprov.distribution.key_index&0xff;
	((uint8_t *)unprov.param)[17] = (m_unprov.distribution.key_index>>8)&0xff;
	//3. flags
	((uint8_t *)unprov.param)[18] = m_unprov.distribution.flags;
	//4. current_iv_index   lsb
	((uint8_t *)unprov.param)[19] = m_unprov.distribution.current_iv_index&0xff;
	((uint8_t *)unprov.param)[20] = (m_unprov.distribution.current_iv_index>>8)&0xff;
	((uint8_t *)unprov.param)[21] = (m_unprov.distribution.current_iv_index>>16)&0xff;
	((uint8_t *)unprov.param)[22] = (m_unprov.distribution.current_iv_index>>24)&0xff;
	//5. unicast_addr lsb
	((uint8_t *)unprov.param)[23] = m_unprov.distribution.unicast_addr&0xff;
	((uint8_t *)unprov.param)[24] = (m_unprov.distribution.unicast_addr>>8)&0xff;

	provisioning_unprov_uart_send((uart_log_provision_data_t *)&unprov);

	if(unprov.param) vPortFree(unprov.param);

/// <3> set system  provisioning done
//	m_provision_env = PROVISONING_DONE;
	uart_provision_env_set(PROVISONING_DONE);
    // send system msg
	{
		uart_log_provision_data_t msg;
		msg.device = SYSTEM_MSG;
		msg.Opcode = SYSTEM_MSG_PROVISIONING_DONE;
		msg.len = 0;

		if(xQueueSend(m_unprovQueue,&msg,portMAX_DELAY)!=pdTRUE)
		{
			BX_ASSERT(0);
		}
	}
#ifdef MESH_TEST_UART_CLENT_SERVER
/// <4> notify client server done
	client_server_uart_unprov_dev_done_cb(success,reason);
#endif /* MESH_TEST_UART_CLENT_SERVER */
/*
    LOG(3,"=====PROVISION DONE!!=====\n");
    LOG(3,"Success=%d,Reason=%d\n",success,reason);
    //Display provision_data.
    LOG(3,"provision_data.network_key=0x\n");
    log_hex_data(provision_data.network_key,MESH_NETWORK_KEY_LENGTH);
    LOG(3,"provision_data.key_index=0x%x\n",provision_data.key_index);
    LOG(3,"provision_data.flags=0x%x\n",provision_data.flags);
    LOG(3,"provision_data.current_iv_index=0x%x\n",provision_data.current_iv_index);
    LOG(3,"provision_data.unicast_addr=0x%x\n",provision_data.unicast_addr);
*/
}
//----------------------------------------------------------------------------------------------------------------
#endif /* MESH_TEST_UART_PROVISION */
#endif /* OSAPP_UART_LOG_TEST */
#endif /* OSAPP_MESH */
