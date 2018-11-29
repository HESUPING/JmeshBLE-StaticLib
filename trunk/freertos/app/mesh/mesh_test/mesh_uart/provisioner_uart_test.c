/*
 * provisioner_uart_test.c
 *
 *  Created on: 2018-4-16
 *      Author: huichen
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#ifdef OSAPP_UART_LOG_TEST
#include "mesh_uart_ctrl.h"
#ifdef MESH_TEST_UART_PROVISION
#include "provisioner_uart_test.h"
#include "ecc_p256.h"

#ifdef MESH_TEST_UART_CLENT_SERVER
#include "client_server_uart_test.h"
#endif/* MESH_TEST_UART_CLENT_SERVER */

//----------------------------------------------------------------------------------------------------------------
// -----------  define
// -- default linkID
#define PROVISION_DEFAULT_LINKID   0x23af5850
// -- default provisioning random num
#define PROVISION_DEFAULT_RANDOM_NUM   0x8b,0x19,0xac,0x31,0xd5,0x8b,0x12,0x4c,0x94,0x62,0x09,0xb5,0xdb,0x10,0x21,0xb9
// -- default distribution data
#define DISTRIBUTION_DEFAULT_NETWORK_KEY  		0xef,0xb2,0x25,0x5e,0x64,0x22,0xd3,0x30,0x08,0x8e,0x09,0xbb,0x01,0x5e,0xd7,0x07
#define DISTRIBUTION_DEFAULT_KEY_INDEX			0x0567
#define DISTRIBUTION_DEFAULT_FLAGS				0x00
#define DISTRIBUTION_DEFAULT_IV_INDEX			0x01020304
#define DISTRIBUTION_DEFAULT_UNICAST_ADDRESS	0x0b0c

//mask define
#define ROLE_CFG_INIT_MASK_INIT 	   0x00 //role not init
#define ROLE_CFG_INIT_MASK_PROVISIONER 0x01 //provisioner init
#define ROLE_CFG_INIT_MASK_UNPROV_DEV  0x02 //unprov device init
// -----------  extern function
extern void reverse_self(void * src , uint8_t length);
extern void (*unprovisioned_dev_beacon_rx_callback)(uint8_t *,uint16_t ,uint32_t *);
// -----------  static function
// -->>   provisioner
//uart
static void provisioning_provisioner_uart_send(const uart_log_provision_data_t *param);
//cmd
static void provisioner_set_config_init(void);
static void provisioner_set_private_keys(const uint8_t *pkey);
static void provisioner_send_public_keys(void);
static void provisioner_gen_public_keys(void);
static void provisioner_gen_public_keys_done(void* param);
static void app_provisioner_init(void);
static void app_provisioner_set_random_auth_value(const uint8_t *param);
static void user_default_init_distribution_data(void);
static void app_provisioner_set_distribution_data(const uint8_t *param);
static void user_provisioner_function_init(void);
static void user_unprovisioned_dev_beacon_rx_callback(uint8_t *dev_uuid,uint16_t oob_info,uint32_t *uri_hash);
static void app_provisioner_set_link_open(const uint8_t *param);
static void user_provisioner_link_ack_rx_callback(void);
static void app_provisioner_set_invite_duration(const uint8_t *param);
static void user_provisioner_capabilities_rx_callback(provision_capabilities_t * para);
static void app_provisioner_set_start_pdu(const uint8_t *param);
static void user_provisioner_read_peer_public_key_oob(void (*callback)(void));
static void app_provisioner_set_dev_public_key(const uint8_t *param);
static void user_provisioner_provision_input_auth_value(uint8_t *buff,void (*cb)());
static void app_provisioner_set_input_auth_value(const uint8_t *param);
static void user_provisioner_provision_output_auth_value(uint8_t *buff);
static void app_provisioner_set_output_auth_value(const uint8_t *param);
static void user_provisioner_provision_static_auth_value(uint8_t *buff);
static void app_provisioner_set_static_auth_value(const uint8_t *param);
static void user_provisioner_provision_done(uint8_t success , uint8_t reason);

// -----------  static value
static uint8_t m_role=0;
static QueueHandle_t m_provisionerQueue;
static uart_log_provisioner_owndata_t m_provisioner;

//----------------------------------------------------------------------------------------------------------------
/******USER FUNCTION******/
void provisioner_uart_test_init(QueueHandle_t handle)
{
	m_provisionerQueue = handle;
}

void provisioner_uart_test_rx_callback(uint8_t const *param,uint8_t len)
{
	//parse  msg
	uart_log_provision_data_t msg;
	msg.device = PC_SET_DEV_PROVISIONER;
	msg.Opcode = param[0];
	msg.len = len-1;
	if(msg.len)
	{
		msg.param = (uint8_t *)pvPortMalloc(msg.len *sizeof(uint8_t));
		BX_ASSERT(msg.param!=NULL);
		memcpy(msg.param,(param+1),msg.len );
	}

	if(xQueueSend(m_provisionerQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
void provisioner_uart_test_system_msg_receive(const uart_log_provision_data_t *pmsg)
{
	switch(pmsg->Opcode)
	{
	case SYSTEM_MSG_PROV_OWN_PUBLIC_KEY :
		//1. send public key
		provisioner_send_public_keys();
		//2. app init
		app_provisioner_init();
		//3. set mesh init done
		uart_provision_env_set(MESH_INIT_DONE);
		break;
	default:break;
	}
}
void provisioner_uart_msg_receive(const uart_log_provision_data_t *pmsg)
{
	if(m_role != ROLE_CFG_INIT_MASK_PROVISIONER)
	{
		if(m_role != ROLE_CFG_INIT_MASK_INIT)
		{
			UART_TEST_LOG(LOG_LVL_INFO,"!!! provisioner init error: 0x%02x !!!\n",m_role);
		}
		else
		{
			switch(pmsg->Opcode)
			{
			case RX_OP_PROV_CFG :
				if(pmsg->len == 1)
				{
					uint8_t *pconfig = (uint8_t *)(pmsg->param);

					if(pconfig && pconfig[0])//cfg provisioner
					{
						//1. cfg provisioner
						uart_provision_env_set(MSG_PROVIONER_DEV);
		//				m_provision_env = MSG_PROVIONER_DEV;
						provisioner_set_config_init();
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
		case RX_OP_PROV_CFG :
			if(pmsg->len == 1)
			{
				uint8_t *pconfig = (uint8_t *)(pmsg->param);

				if(pconfig && pconfig[0])//cfg provisioner
				{
					//1. cfg provisioner
					uart_provision_env_set(MSG_PROVIONER_DEV);
	//				m_provision_env = MSG_PROVIONER_DEV;
					provisioner_set_config_init();
				}
				else
				{
					uart_provision_env_set(MESH_INIT_DONE);
	//				m_provision_env = MESH_INIT_DONE;
				}
			}
			break;
		case RX_OP_PROV_STATIC_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				uart_log_provision_data_t provisioner;

				//send to pc  output random req
				provisioner.Opcode = TX_OP_PROV_OUTPUT_AUTH_REQ;
				provisioner.len = 0;
				provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

				app_provisioner_set_static_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_OUTPUT_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				uart_log_provision_data_t provisioner;

				//send to pc  auth random req
				provisioner.Opcode = TX_OP_PROV_RANDOM_AUTH_REQ;
				provisioner.len = 0;
				provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

				app_provisioner_set_output_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_PRIVATE_KEY :
			if(pmsg->len == GAP_P256_KEY_LEN)
			{
				provisioner_set_private_keys((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_BEACON_UUID :
			if(pmsg->len == 22)
			{
				app_provisioner_set_link_open((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_INVITE_RSP :
			if(pmsg->len == 1)
			{
				app_provisioner_set_invite_duration((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_DISTRIBUTION_DATA :
			if(pmsg->len == 25)
			{
				app_provisioner_set_distribution_data((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_START_PDU :
			if(pmsg->len == 5)
			{
				app_provisioner_set_start_pdu((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_DEV_PUBLIC_KEY :
			if(pmsg->len == (GAP_P256_KEY_LEN+GAP_P256_KEY_LEN))
			{
				app_provisioner_set_dev_public_key((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_INPUT_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				app_provisioner_set_input_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_RANDOM_AUTH_VAL :
			if(pmsg->len == AUTHVALUE_LEN)
			{
				uart_log_provision_data_t provisioner;

				//send to pc  private key req
				provisioner.Opcode = TX_OP_PROV_PRIVATE_KEY_REQ;
				provisioner.len = 0;
				provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

				app_provisioner_set_random_auth_value((uint8_t *)pmsg->param);
			}
			break;
		case RX_OP_PROV_FLUSH_CACHE_VAL :
			if(pmsg->len == 1)
			{
				//1.clean bear rx  msg cache
				mesh_flush_msg_cache();
			}
			break;

		default:break;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------static func
static void provisioning_provisioner_uart_send(const uart_log_provision_data_t *param)
{
	uart_log_tx_env_t provisioner;

	if(param)
	{
		provisioner.cmd = UART_PKTCMD_PROVISIONER_TX;
		provisioner.tx_len = param->len+1;
		if(provisioner.tx_len)
		{
			provisioner.pdata = (uint8_t *)pvPortMalloc(provisioner.tx_len);
			BX_ASSERT(provisioner.pdata!=NULL);
			provisioner.pdata[0] = param->Opcode;
		}

		switch(param->Opcode)
		{
		case TX_OP_PROV_BEACON_DATA :
		case TX_OP_PROV_LINK_ACK :
		case TX_OP_PROV_DEV_CAPABILITIES :
		case TX_OP_PROV_DEV_PUBLIC_KEY :
		case TX_OP_PROV_INPUT_AUTH_REQ :
		case TX_OP_PROV_OUTPUT_AUTH_VAL :
		case TX_OP_PROV_STATIC_AUTH_REQ :
		case TX_OP_PROV_DONE_STATE :
		case TX_OP_PROV_PRIVATE_KEY_REQ :
		case TX_OP_PROV_OUTPUT_AUTH_REQ :
		case TX_OP_PROV_OWN_PRIVATE_KEY :
		//case TX_OP_PROV_OWN_PUBLIC_KEY :
		case TX_OP_PROV_INVITE_REQ:
		case TX_OP_PROV_DISTRIBUTION_DATA_REQ:
			{
				if(param->len)
				{
					memcpy((uint8_t *)(provisioner.pdata+1),(uint8_t *)(param->param),param->len);
				}
			}
			break;
		case TX_OP_PROV_OWN_PUBLIC_KEY :
			{
				if(param->len)
				{
					memcpy((public_key_t  *)(provisioner.pdata+1),(public_key_t *)(param->param),param->len);
				}
			}
			break;
		default:break;
		}

		uart_log_send_cmd(provisioner.cmd,provisioner.pdata,provisioner.tx_len);
		if(provisioner.tx_len) vPortFree(provisioner.pdata);
	}
}
//----------------------------------------------------------------------------------------------------------------
// -->>   provisioner
static void provisioner_set_config_init(void)
{
	if(!m_role)
	{
		/// <1>
		provisioner_init();// just run once
		/// <2>  provisioner callback register
		user_provisioner_function_init();
		/// <3>
		//mesh_init_start_scan();

		m_role |= ROLE_CFG_INIT_MASK_PROVISIONER;
	}

	if(m_role == ROLE_CFG_INIT_MASK_PROVISIONER)
	{
		uart_log_provision_data_t provisioner;

		//1. send to pc  static value init
		provisioner.Opcode = TX_OP_PROV_STATIC_AUTH_REQ;
		provisioner.len = 0;
		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

	//	//2. send to pc  private key req
	//	provisioner.Opcode = TX_OP_PROV_PRIVATE_KEY_REQ;
	//	provisioner.len = 0;
	//	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);
	//
	//	//3. send to pc  output random req
	//	provisioner.Opcode = TX_OP_PROV_OUTPUT_AUTH_REQ;
	//	provisioner.len = 0;
	//	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);
	//
	//	//4. send to pc  auth random req
	//	provisioner.Opcode = TX_OP_PROV_RANDOM_AUTH_REQ;
	//	provisioner.len = 0;
	//	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);
	}
	else
	{
		UART_TEST_LOG(LOG_LVL_INFO,"!!! provisioner init error: 0x%02x !!!\n",m_role);
	}
}
static void app_provisioner_set_random_auth_value(const uint8_t *param)
{
	if(param)//not null
	{
		//1. copy random auth value
		memcpy(m_provisioner.random_value,param,AUTHVALUE_LEN);
		//2. set mesh system random num
	    memcpy(provision_random.field.random_provisioner,m_provisioner.random_value,AUTHVALUE_LEN);
	}
}
static void provisioner_set_private_keys(const uint8_t *pkey)
{
	if(pkey)
	{
		//1. copy private key
		memcpy(m_provisioner.prov_private_key,pkey,GAP_P256_KEY_LEN);
		//2. set mesh system  private key
	    memcpy(provision_key.private,m_provisioner.prov_private_key,GAP_P256_KEY_LEN);
		//3. gen public key
		provisioner_gen_public_keys();
	}
}
static void provisioner_send_public_keys(void)
{
	while(!m_provisioner.provisioner_public_key_done);
    //1. send to pc  public key
	{
		uart_log_provision_data_t provisioner;
		provisioner.Opcode = TX_OP_PROV_OWN_PUBLIC_KEY;
		provisioner.param = (public_key_t *)&m_provisioner.provisioner_public_key;
		provisioner.len = (GAP_P256_KEY_LEN)+(GAP_P256_KEY_LEN);
		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);
	}
}
//Generate provisioner's public key
static void provisioner_gen_public_keys_done(void* param)
{
	//1. Adjust the order
    reverse_self(m_provisioner.prov_private_key,GAP_P256_KEY_LEN);
    reverse_self(m_provisioner.provisioner_public_key.x,GAP_P256_KEY_LEN);
    reverse_self(m_provisioner.provisioner_public_key.y,GAP_P256_KEY_LEN);
	//2. set done flag
	m_provisioner.provisioner_public_key_done = 1;
	//3. set mesh system public keys
    memcpy(&provision_key.local_public,&m_provisioner.provisioner_public_key,sizeof(public_key_t));
    //4. send system msg
	{
		//parse  msg
		uart_log_provision_data_t msg;
		msg.device = SYSTEM_MSG;
		msg.Opcode = SYSTEM_MSG_PROV_OWN_PUBLIC_KEY;
		msg.len = 0;

		if(xQueueSend(m_provisionerQueue,&msg,portMAX_DELAY)!=pdTRUE)
		{
			BX_ASSERT(0);
		}
	}
}
static void provisioner_gen_public_keys(void)
{
	//0. clear done flag
	m_provisioner.provisioner_public_key_done = 0;
	//1. Adjust the order
	reverse_self(m_provisioner.prov_private_key,GAP_P256_KEY_LEN);
	//2. ecc_gen_new_public_key
    ecc_gen_new_public_key_usr(m_provisioner.prov_private_key,m_provisioner.provisioner_public_key.x,m_provisioner.provisioner_public_key.y,provisioner_gen_public_keys_done);
}
static void app_provisioner_init(void)
{
/// <1>
	//1.clean bear rx  msg cache
	mesh_flush_msg_cache();
	//2. role init          provisioner_init  reset
	provisioner_reset();
/// <2>.  updata init data
	//3. default distribution data set
	user_default_init_distribution_data();
	//4. set deafault linkID
	//provision_env.link_id = PROVISION_DEFAULT_LINKID;
	//5. set mesh system random num
    memcpy(provision_random.field.random_provisioner,m_provisioner.random_value,AUTHVALUE_LEN);
///// <3>
//	//4.  provisioner callback register
//	user_provisioner_function_init();
///// <4>
//	user_app_mesh_test_init_done();
}
static void user_provisioner_function_init(void)
{
	//1. beacon callback
	unprovisioned_dev_beacon_rx_callback = user_unprovisioned_dev_beacon_rx_callback;
	//2. link ack
    provisioner_link_ack_rx_callback = user_provisioner_link_ack_rx_callback;
    //3. capabilities
    provisioner_capabilities_rx_callback = user_provisioner_capabilities_rx_callback;
    //4. exchange public keys
    provisioner_read_peer_public_key_oob = user_provisioner_read_peer_public_key_oob;
    //5. user input auth value
    provision_input_auth_value  = user_provisioner_provision_input_auth_value;
    //6. user output auth value
    provision_output_auth_value = user_provisioner_provision_output_auth_value;
    //7. user static auth value
    provision_static_auth_value = user_provisioner_provision_static_auth_value;
    //8. provisioning done
    user_provision_done = user_provisioner_provision_done;
}
static void user_unprovisioned_dev_beacon_rx_callback(uint8_t *dev_uuid,uint16_t oob_info,uint32_t *uri_hash)
{
    if(current_stage == ProvStage_Beacon_rx)
    {
        LOG(LOG_LVL_INFO,current_stage_s[current_stage]);
        //1. send to pc  beacon data
        if(dev_uuid)// not null
    	{
    		uart_log_provision_data_t provisioner;

    		provisioner.Opcode = TX_OP_PROV_BEACON_DATA;
    		provisioner.len = 22;//16+2+4
    		provisioner.param = (uint8_t *)pvPortMalloc(provisioner.len);//16+2+4
			BX_ASSERT(provisioner.param!=NULL);
			//copy beacon data
			memcpy((uint8_t *)provisioner.param,dev_uuid,16);
			memcpy(((uint8_t *)provisioner.param+16),(uint8_t *)&oob_info,2);
			if(uri_hash)// uar hash  not null
			{
				memcpy(((uint8_t *)provisioner.param+16+2),(uint8_t *)uri_hash,4);
			}
			else
			{
				memset(((uint8_t *)provisioner.param+16+2),0,4);
			}
    		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

    		if(provisioner.param) vPortFree(provisioner.param);
    	}
    }
}
static void app_provisioner_set_link_open(const uint8_t *param)
{
	if(param)//not null
	{
		//save data
		memcpy(m_provisioner.beacon.dev_uuid,param,16);
		memcpy((uint8_t *)&(m_provisioner.beacon.oob_info),(param+16),2);
		memcpy((uint8_t *)&(m_provisioner.beacon.uri_hash),(param+16+2),4);
		//link open
		if(current_stage == ProvStage_Beacon_rx)
		{
			current_stage = ProvStage_LinkOpen_tx;
			provisioning_link_open_tx(m_provisioner.beacon.dev_uuid);
			LOG(LOG_LVL_INFO,current_stage_s[current_stage]);
		}
	}
}
static void user_provisioner_link_ack_rx_callback(void)
{
	uart_log_provision_data_t provisioner;

	//1. send to pc  link ack
	provisioner.Opcode = TX_OP_PROV_LINK_ACK;
	provisioner.len = 0;
	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

	//2. send to pc  distribution data req
	provisioner.Opcode = TX_OP_PROV_DISTRIBUTION_DATA_REQ;
	provisioner.len = 0;
	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

	//3. send to pc  invite req
	provisioner.Opcode = TX_OP_PROV_INVITE_REQ;
	provisioner.len = 0;
	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);
}
static void app_provisioner_set_invite_duration(const uint8_t *param)
{
	if(param)//not null
	{
		//provisioner invite
		m_provisioner.attention_duration = param[0];
		provisioner_invite_tx(m_provisioner.attention_duration);
	}
}
static void user_provisioner_capabilities_rx_callback(provision_capabilities_t * para)
{
    if(para)// not null
	{
        //1. send to pc device capabilities data
		uart_log_provision_data_t provisioner;

		provisioner.Opcode = TX_OP_PROV_DEV_CAPABILITIES;
		provisioner.len = 11;
		provisioner.param = (uint8_t *)pvPortMalloc(provisioner.len);
		BX_ASSERT(provisioner.param!=NULL);
		//2. copy capabilities data
		memcpy((provision_capabilities_t *)&m_provisioner.dev_capabilities,(provision_capabilities_t *)para,sizeof(provision_capabilities_t));
		//3. send
		memcpy((uint8_t *)provisioner.param,(uint8_t *)&m_provisioner.dev_capabilities.elements_num,1);
		memcpy(((uint8_t *)provisioner.param+1),(uint8_t *)&m_provisioner.dev_capabilities.algorithms,2);
		memcpy(((uint8_t *)provisioner.param+1+2),(uint8_t *)&m_provisioner.dev_capabilities.public_key_type,1);
		memcpy(((uint8_t *)provisioner.param+1+2+1),(uint8_t *)&m_provisioner.dev_capabilities.static_oob_type,1);
		memcpy(((uint8_t *)provisioner.param+1+2+1+1),(uint8_t *)&m_provisioner.dev_capabilities.output_oob_size,1);
		memcpy(((uint8_t *)provisioner.param+1+2+1+1+1),(uint8_t *)&m_provisioner.dev_capabilities.output_oob_action,2);
		memcpy(((uint8_t *)provisioner.param+1+2+1+1+1+2),(uint8_t *)&m_provisioner.dev_capabilities.input_oob_size,1);
		memcpy(((uint8_t *)provisioner.param+1+2+1+1+1+2+1),(uint8_t *)&m_provisioner.dev_capabilities.input_oob_action,2);

		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

		if(provisioner.param) vPortFree(provisioner.param);
	}
}
static void app_provisioner_set_start_pdu(const uint8_t *param)
{
	if(param)//not null
	{
		//provisioner start
		//save
		m_provisioner.start_pdu.algorithm = param[0];
		m_provisioner.start_pdu.public_key = param[1];
		m_provisioner.start_pdu.auth_method = param[2];
		m_provisioner.start_pdu.auth_action = param[3];
		m_provisioner.start_pdu.auth_size = param[4];

		//set
		memcpy(&provision_start,&m_provisioner.start_pdu,sizeof(provision_start_t));
		provisioner_start_tx();
	}
}
static void user_provisioner_read_peer_public_key_oob(void (*callback)(void))
{
	if(callback)// not null
	{
		uart_log_provision_data_t provisioner;

		//1. send to pc  device public key req
		provisioner.Opcode = TX_OP_PROV_DEV_PUBLIC_KEY;
		provisioner.len = 0;
		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

		//2. save callback
		m_provisioner.read_peer_public_key_cb = callback;
	}
}
static void app_provisioner_set_dev_public_key(const uint8_t *param)
{
	if(param)//not null
	{
		//provisioner start
		//1. save
		memcpy((public_key_t *)&m_provisioner.dev_public_key,(public_key_t *)param,sizeof(public_key_t));
		//2. set
		memcpy(&provision_key.peer_public,(public_key_t *)&m_provisioner.dev_public_key,sizeof(public_key_t));
		//3. send to mesh
		if(m_provisioner.read_peer_public_key_cb)//not null
		{
			m_provisioner.read_peer_public_key_cb();
		}
	}
}
static void user_provisioner_provision_input_auth_value(uint8_t *buff,void (*cb)())
{
	if(buff&&cb)// not null
	{
		uart_log_provision_data_t provisioner;

		//1. send to pc  input auth key req
		provisioner.Opcode = TX_OP_PROV_INPUT_AUTH_REQ;
		provisioner.len = 0;
		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

		//2. save pvalue hanlde and callback
		m_provisioner.input_value.pvalue = buff;
		m_provisioner.input_value.cb = cb;
	}
}
static void app_provisioner_set_input_auth_value(const uint8_t *param)
{
	if(param)//not null
	{
		//provisioner start
		//1. save
		memcpy((uint8_t *)&m_provisioner.input_value.val,param,AUTHVALUE_LEN);
		//2. set
		memcpy(m_provisioner.input_value.pvalue,param,AUTHVALUE_LEN);
		//3. send to mesh
		if(m_provisioner.input_value.cb)//not null
		{
			m_provisioner.input_value.cb();
		}
	}
}
static void user_provisioner_provision_output_auth_value(uint8_t *buff)
{
	if(buff)// not null
	{
		uart_log_provision_data_t provisioner;
		uint8_t *pout;

		if(m_provisioner.output_value.type != random_user)
		{
			pout = m_provisioner.output_value.system;
			//1. gen rand output auth value
			random_gen_words(pout,AUTHVALUE_LEN);
		}
		else
		{
			pout = m_provisioner.output_value.user;
		}

		//2. set to mesh rand output auth value
		memcpy(buff,pout,AUTHVALUE_LEN);
		//3. send to pc  output auth value
		provisioner.Opcode = TX_OP_PROV_OUTPUT_AUTH_VAL;
		provisioner.len = AUTHVALUE_LEN;
		provisioner.param = (uint8_t *)pvPortMalloc(provisioner.len);
		BX_ASSERT(provisioner.param!=NULL);
		//4. copy output auth value data
		memcpy((uint8_t *)provisioner.param,pout,provisioner.len);

		provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

		if(provisioner.param) vPortFree(provisioner.param);
	}
}
static void app_provisioner_set_output_auth_value(const uint8_t *param)
{
	if(param)// not null
	{
		//1. copy static auth value
		m_provisioner.output_value.type = random_user;
		memcpy(m_provisioner.output_value.user,param,AUTHVALUE_LEN);
	}
}
static void user_provisioner_provision_static_auth_value(uint8_t *buff)
{
	if(buff)// not null
	{
		//1. copy static auth value
		memcpy(buff,m_provisioner.static_value,AUTHVALUE_LEN);
	}
}
static void app_provisioner_set_static_auth_value(const uint8_t *param)
{
	if(param)// not null
	{
		//1. copy static auth value
		memcpy(m_provisioner.static_value,param,AUTHVALUE_LEN);
	}
}
static void user_provisioner_provision_done(uint8_t success , uint8_t reason)
{
	uart_log_provision_data_t provisioner;

	//1. save data
    m_provisioner.done_state.success = success;
    m_provisioner.done_state.reason = reason;

	//2. send to pc  oprovision_done
	provisioner.Opcode = TX_OP_PROV_DONE_STATE;
	provisioner.len = 2;
	provisioner.param = (uint8_t *)pvPortMalloc(provisioner.len);
	BX_ASSERT(provisioner.param!=NULL);
	//4. copy output auth value data
	((uint8_t *)provisioner.param)[0] = m_provisioner.done_state.success;
	((uint8_t *)provisioner.param)[1] = m_provisioner.done_state.reason;

	provisioning_provisioner_uart_send((uart_log_provision_data_t *)&provisioner);

	if(provisioner.param) vPortFree(provisioner.param);

	//5. set system  provisioning done
//	m_provision_env = PROVISONING_DONE;
	uart_provision_env_set(PROVISONING_DONE);
    // send system msg
	{
		uart_log_provision_data_t msg;
		msg.device = SYSTEM_MSG;
		msg.Opcode = SYSTEM_MSG_PROVISIONING_DONE;
		msg.len = 0;

		if(xQueueSend(m_provisionerQueue,&msg,portMAX_DELAY)!=pdTRUE)
		{
			BX_ASSERT(0);
		}
	}
#ifdef MESH_TEST_UART_CLENT_SERVER
/// <2> notify client server done
	client_server_uart_provisioner_done_cb(success,reason);
#endif /* MESH_TEST_UART_CLENT_SERVER */
}
static void user_default_init_distribution_data(void)
{
	uint8_t tttmp[] = {DISTRIBUTION_DEFAULT_NETWORK_KEY};

/// <1> init defalut data
	//1. network_key
	memcpy(m_provisioner.distribution.network_key,tttmp,16);
	//2. key_index
	m_provisioner.distribution.key_index = DISTRIBUTION_DEFAULT_KEY_INDEX;
	//3. flags
	m_provisioner.distribution.flags = DISTRIBUTION_DEFAULT_FLAGS;
	//4. current_iv_index
	m_provisioner.distribution.current_iv_index = DISTRIBUTION_DEFAULT_IV_INDEX;
	//5. unicast_addr
	m_provisioner.distribution.unicast_addr = DISTRIBUTION_DEFAULT_UNICAST_ADDRESS;
/// <2> set init defalut data
	memcpy(&provision_data,&m_provisioner.distribution,sizeof(provision_data_t));
}
static void app_provisioner_set_distribution_data(const uint8_t *param)
{
	if(param)// not null
	{
	/// <1> copy distribution data
		//1. network_key
		memcpy(m_provisioner.distribution.network_key,param,16);
		//2. key_index     lsb
		m_provisioner.distribution.key_index = (uint16_t)param[16]|((uint16_t)param[17]<<8);
		//3. flags
		m_provisioner.distribution.flags = param[18];
		//4. current_iv_index   lsb
		m_provisioner.distribution.current_iv_index = (uint32_t)param[19]|((uint32_t)param[20]<<8)|((uint32_t)param[21]<<16)|((uint32_t)param[22]<<24);
		//5. unicast_addr lsb
		m_provisioner.distribution.unicast_addr = (uint16_t)param[23]|((uint16_t)param[24]<<8);
	/// <2> set init defalut data
		memcpy(&provision_data,&m_provisioner.distribution,sizeof(provision_data_t));
	}
}
//----------------------------------------------------------------------------------------------------------------
#endif /* MESH_TEST_UART_PROVISION */
#endif /* OSAPP_UART_LOG_TEST */
#endif /* OSAPP_MESH */
