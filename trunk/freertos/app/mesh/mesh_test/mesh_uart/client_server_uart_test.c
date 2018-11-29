/*
 * client_service_uart_test.c
 *
 *  Created on: 2018��5��14��
 *      Author: huichen
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#ifdef OSAPP_UART_LOG_TEST
#include "client_server_uart_test.h"
#ifdef MESH_TEST_UART_CLENT_SERVER

//#include "gpio.h"
#include "config_client.h"
#include "config_server.h"
#include "mesh_definitions.h"
#include "upper_transport.h"
#include "generic_onoff_client.h"
#include "generic_onoff_server.h"
#include "generic_onoff_common.h"
#include "mesh_app_action.h"
#include "mesh_app.h"
#include "node_save.h"
#include "mesh_node_base.h"
//gatt
#include "provisioning_s.h"
#include "proxy_s.h"
#include "mesh_iv_operation.h"
//config messages
#include "config_relay.h"
#include "config_composition_data.h"
#include "sdk_mesh_config_pro.h"
#include "device_keys_dm.h"
#include "network_keys_dm.h"
#include "app_keys_dm.h"

// -----------  define
//mask define
#define CLINET_SERVER_CFG_INIT_MASK_C 0x01 //client init
#define CLINET_SERVER_CFG_INIT_MASK_S 0x02 //server init

///  ---------------   inclue extern function
//Export External Function
extern void mesh_app_server_init(void);
extern void mesh_app_client_init(void);
//extern uint8_t devkey[MESH_KEY_LENGTH];
extern uint32_t sequence_number;
extern uint32_t iv_index;
extern mesh_elmt_t client_elmts[2];
extern mesh_elmt_t server_elmts[2];
extern void init_elmt_addr(uint16_t addr);
// -----------  extern value

// -----------  extern function

// -----------  static value
static uint8_t m_client_server_init_flag=0;
static QueueHandle_t m_clientQueue;

static uart_log_client_server_owndata_t m_client;
// -----------  static function
//uart send
static void client_server_uart_msg_send(const uart_log_provision_data_t *param);

//clint server
static void client_server_uart_client_init(void);
static void client_server_uart_server_init(void);
static void client_server_cfg_server_data_init(void);
static void client_server_cfg_client_data_init(void);

static void generate_device_key_by_ecdh_and_salt(void);
static void server_generate_device_key_by_ecdh_and_salt(void);


//msg receive  set value
static void app_client_set_sequence_number_value(const uint8_t *param);
static void app_client_set_distribution_data(const uint8_t *param);
static void client_net_key_all_keys_generate_done(void* dm_handle);
static void app_client_set_app_key_value(const uint8_t *param);
static void client_aid_generate_done(void* dm_handle);
static void app_client_set_element_addr_value(const uint8_t *param);
static void app_client_set_model_appkey_index_value(const uint8_t *param);
static void app_client_set_appkey_add_tx_value(const uint8_t *param);
static void app_client_set_model_app_bind_tx_value(const uint8_t *param);
static void app_client_set_client_model_ctrl_msg_value(const uint8_t *param);
static void app_client_set_client_model_ctrl_msg_noack_value(const uint8_t *param);
static void app_client_set_model_subscription_update_tx_value(const uint8_t *param);
static void app_client_set_config_relay_get_value(const uint8_t *param);
static void app_client_set_config_relay_set_value(const uint8_t *param);

//msg send req
static void client_element_addr_req(uint16_t element_id);
static void client_model_appkey_index_req(uint16_t model_id);
//msg send val
static void client_send_dev_key_val(void);
static void server_send_dev_key_val(void);
//msg send ack
static void config_client_model_subscription_tx_done(access_pdu_tx_t * param_a,uint8_t param_b);
static void config_relay_get_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b);
static void config_relay_set_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b);

//msg send sys
static void security_init_done_cb(void);
static void security_init_done_msg(void);
static void client_server_cfg_data_init_done(void);
static void client_server_server_cfg_data_init_done(void);
static void generate_device_key_by_ecdh_and_salt(void);
static void dev_key_gen_done(void);
static void server_dev_key_gen_done(void);

//sys cb
static void config_client_appkey_add_test_cb(access_pdu_tx_t * param_a,uint8_t param_b);
static void config_client_model_app_bind_test_cb(access_pdu_tx_t * param_a,uint8_t param_b);
static void server_network_keys_generation_done_cb(void* handle);
//common
static uint8_t alloc_generic_tid(void);
/******USER FUNCTION******/
void client_server_uart_init(QueueHandle_t handle)
{
	m_clientQueue = handle;

    security_init(security_init_done_cb);
}
//uart rx callback  send msg to queue
void client_server_uart_config_client_callback(uint8_t const *param,uint8_t len)
{
	//parse  msg
	uart_log_provision_data_t msg;
	msg.device = PC_SET_CFG_CLIENT_MSG;
	msg.Opcode = param[0];
	msg.len = len-1;
	if(msg.len)
	{
		msg.param = (uint8_t *)pvPortMalloc(msg.len *sizeof(uint8_t));
		BX_ASSERT(msg.param!=NULL);
		memcpy(msg.param,(param+1),msg.len );
	}

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
void client_server_uart_system_msg_receive(const uart_log_provision_data_t *pmsg)
{
	switch(pmsg->Opcode)
	{
	case SYSTEM_MSG_SECURITY_INIT_DONE :
		{
			security_init_done_msg();
		}
		break;
	case SYSTEM_MSG_CLIENT_ALL_NET_KEY :
		{
			//1. send to pc  app key req
			uart_log_provision_data_t client;
			client.Opcode = TX_OP_CLIENT_APP_KEY_REQ;
			client.len = 0;
			client_server_uart_msg_send((uart_log_provision_data_t *)&client);
		}
		break;
	case SYSTEM_MSG_CLIENT_APP_AID_KEY :
		{
			//1. send to pc  aelement  req
			client_element_addr_req(0);
		}
		break;
	case SYSTEM_MSG_CLIENT_DEV_KEY :
		{
			client_send_dev_key_val();
		}
		break;
	case SYSTEM_MSG_SERVER_DEV_KEY :
		{
			server_send_dev_key_val();
		}
		break;
	case SYSTEM_MSG_CLIENT_DATA_INIT_DONE :
		{
		    // client data init done
			uart_provision_env_set(MSG_CFG_CLIENT_INIT_DONE);
		}
		break;
	default:break;
	}
}
void client_server_uart_config_client_msg_receive(const uart_log_provision_data_t *pmsg)
{
	switch(pmsg->Opcode)
	{
	case RX_OP_CLIENT_CFG :
		if(pmsg->len == 1)
		{
			uint8_t *pconfig = (uint8_t *)(pmsg->param);

			if(pconfig && pconfig[0])//cfg client
			{
				//1 set env
				uart_provision_env_set(MSG_CFG_CLIENT);
				//2 config init
				if(pconfig[0] == CLIENT_SERVER_MSG_CFG_CLIENT)
				{
					client_server_uart_client_init();
				}
				else if(pconfig[0] == CLIENT_SERVER_MSG_CFG_SERVER)
				{
					client_server_uart_server_init();
				}
			}
			else
			{
				//1 set env
				uart_provision_env_set(MSG_CFG_CLIENT_INIT_DONE);
			}
		}
		break;
	case RX_OP_CLIENT_SEQUENCE_NUM_RSP :
		if(pmsg->len == 4)
		{
			//1. send to pc  sequence number req
			uart_log_provision_data_t client;
			client.Opcode = TX_OP_CLIENT_DISTRIBUTION_REQ;
			client.len = 0;
			client_server_uart_msg_send((uart_log_provision_data_t *)&client);

			//2. set val
		    app_client_set_sequence_number_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_DISTRIBUTION_RSP :
		if(pmsg->len == 25)
		{
			//1. set val
			app_client_set_distribution_data((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_APP_KEY_RSP :
		if(pmsg->len == 21)
		{
			//1. set val
			app_client_set_app_key_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_ELEMENT_ADDR_RSP :
		if(pmsg->len == 4)
		{
			//1. set val
			app_client_set_element_addr_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_MODEL_APPKEY_INDEX_RSP :
		if(pmsg->len == 4)
		{
			//1. set val
			app_client_set_model_appkey_index_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_CLIENT_APPKEY_ADD_TX_RSP :
		if(pmsg->len == 4)
		{
			//1. set val
			app_client_set_appkey_add_tx_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_MODEL_APP_BIND_TX_RSP :
		if(pmsg->len == 11)
		{
			//1. set val
			app_client_set_model_app_bind_tx_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_CLIENT_MODLE_CTRL_MSG_RSP :
		if(pmsg->len >= 4)
		{
			//1. set val
			app_client_set_client_model_ctrl_msg_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_MODLE_CTRL_MSG_NOACK_RSP :
		if(pmsg->len >= 4)
		{
			//1. set val
			app_client_set_client_model_ctrl_msg_noack_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_MODLE_SUBSCRIP_UPDATA_TX_RSP :
		if(pmsg->len == 12)
		{
			//1. set val
			app_client_set_model_subscription_update_tx_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_CONFIG_RELAY_Get :
		if(pmsg->len == 2)
		{
			//1. set val
			app_client_set_config_relay_get_value((uint8_t *)pmsg->param);
		}
		break;
	case RX_OP_CLIENT_CONFIG_RELAY_Set :
		if(pmsg->len == 4)
		{
			//1. set val
			app_client_set_config_relay_set_value((uint8_t *)pmsg->param);
		}
		break;
	default:break;
	}
}
void client_server_uart_provisioner_done_cb(uint8_t success , uint8_t reason)//external call
{
	if(success == 1)
	{
        //generate device key
        generate_device_key_by_ecdh_and_salt();
	}
}

void client_server_uart_unprov_dev_done_cb(uint8_t success , uint8_t reason)//external call
{
    if(success == 1)
    {
        LOG(LOG_LVL_INFO,"client_server_uart_unprov_dev_done_cb \n");

		//generate device key
    	server_generate_device_key_by_ecdh_and_salt();
    }
}
//------------------------------------------------------------static function
static void security_init_done_cb(void)
{
    //LOG(3,"security_init_done_cb \n");
	uart_log_provision_data_t msg;

    //1. send system msg
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_SECURITY_INIT_DONE;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
static void security_init_done_msg(void)
{
    upper_transport_init();
    init_leds();

    UART_TEST_LOG(LOG_LVL_INFO,"==security_init_done_msg==\n");
}
static void client_server_uart_msg_send(const uart_log_provision_data_t *param)
{
	uart_log_tx_env_t clinet;

	if(param)
	{
		clinet.cmd = UART_PKTCMD_CLIENT_TX;
		clinet.tx_len = param->len+1;
		if(clinet.tx_len)
		{
			clinet.pdata = (uint8_t *)pvPortMalloc(clinet.tx_len);
			BX_ASSERT(clinet.pdata!=NULL);
			clinet.pdata[0] = param->Opcode;
		}

		switch(param->Opcode)
		{
		case TX_OP_CLIENT_SEQUENCE_NUM_REQ :
		case TX_OP_CLIENT_DISTRIBUTION_REQ :
		case TX_OP_CLIENT_APP_KEY_REQ :
		case TX_OP_CLIENT_ELEMENT_ADDR_REQ :
		case TX_OP_CLIENT_MODEL_APPKEY_INDEX_REQ :
		case TX_OP_CLIENT_CLIENT_DATA_INIT_DONE :
		case TX_OP_CLIENT_DEVICE_KEY_VAL :
		case TX_OP_CLIENT_CLIENT_APPKEY_ADD_TX_REQ :
		case TX_OP_CLIENT_MODEL_APP_BIND_TX_REQ :
		case TX_OP_SERVER_SERVER_DATA_INIT_DONE :
		case TX_OP_SERVER_DEVICE_KEY_VAL :
		case TX_OP_SERVER_LED_STATE_VAL :
		case TX_OP_CLIENT_MODLE_CTRL_MSG_NOACK_ACK :
		case TX_OP_CLIENT_MODLE_SUBSCRIP_UPDATA_TX_ACK :
		case TX_OP_CLIENT_CONFIG_RELAY_Set_ACK :
			{
				if(param->len)
				{
					memcpy((uint8_t *)(clinet.pdata+1),(uint8_t *)(param->param),param->len);
				}
			}
			break;
		default:break;
		}

		uart_log_send_cmd(clinet.cmd,clinet.pdata,clinet.tx_len);
		if(clinet.tx_len) vPortFree(clinet.pdata);
	}
}
static void client_server_uart_client_init(void)
{
	if(!m_client_server_init_flag)
	{
		//mesh_app_client_init(); //no need
		m_client_server_init_flag |= CLINET_SERVER_CFG_INIT_MASK_C;
	}
	else
	{
		UART_TEST_LOG(LOG_LVL_INFO,"m_client_server_init_flag: 0x%02x\n",m_client_server_init_flag);
	}

	if(m_client_server_init_flag == CLINET_SERVER_CFG_INIT_MASK_C)//just client init
	{
		client_server_cfg_client_data_init();
	}
	else
	{
		UART_TEST_LOG(LOG_LVL_INFO,"!!! client init error: 0x%02x !!!\n",m_client_server_init_flag);
	}
}
static void client_server_uart_server_init(void)
{
	if(!m_client_server_init_flag)
	{
		//mesh_app_server_init(); // no need
		//set flag
		m_client_server_init_flag |= CLINET_SERVER_CFG_INIT_MASK_S;
	}
	else
	{
		UART_TEST_LOG(LOG_LVL_INFO,"m_client_server_init_flag: 0x%02x\n",m_client_server_init_flag);
	}

	if(m_client_server_init_flag == CLINET_SERVER_CFG_INIT_MASK_S)//just server init
	{
		client_server_cfg_server_data_init();
	}
	else
	{
		UART_TEST_LOG(LOG_LVL_INFO,"!!! server init error: 0x%02x !!!\n",m_client_server_init_flag);
	}
}
static void client_server_cfg_client_data_init(void)
{
	uart_log_provision_data_t client;
	//send to pc  sequence number req
	client.Opcode = TX_OP_CLIENT_SEQUENCE_NUM_REQ;
	client.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}
static void client_server_cfg_server_data_init(void)
{
	//no data to init  , derect to done
	client_server_server_cfg_data_init_done();
}
static void app_client_set_sequence_number_value(const uint8_t *param)
{
	if(param)//not null
	{
	    //sequence number/iv index
		//sequence_number = TEST_PROV_SEQUENCE_NUM;
		memcpy((uint8_t *)&(sequence_number),param,4);
		node_save_misc_sequence_number();
	}
}
static void app_client_set_distribution_data(const uint8_t *param)
{
    dm_netkey_handle_t netkey_handle;
	if(param)// not null
	{
	/// <1> copy distribution data
		//1. network_key
		memcpy(m_client.distribution.network_key,param,16);
		//2. key_index     lsb
		m_client.distribution.key_index = (uint16_t)param[16]|((uint16_t)param[17]<<8);
		//3. flags
		m_client.distribution.flags = param[18];
		//4. current_iv_index   lsb
		m_client.distribution.current_iv_index = (uint32_t)param[19]|((uint32_t)param[20]<<8)|((uint32_t)param[21]<<16)|((uint32_t)param[22]<<24);
		//5. unicast_addr lsb
		m_client.distribution.unicast_addr = (uint16_t)param[23]|((uint16_t)param[24]<<8);
	/// <2> set init defalut data
	    mesh_beacon_iv_index_set(m_client.distribution.current_iv_index);
	    //iv_index = m_client.distribution.current_iv_index;
	    node_save_misc_iv_index();
	    if(MESH_CORE_SUCCESS != dm_netkey_add(m_client.distribution.key_index, m_client.distribution.network_key,&netkey_handle,client_net_key_all_keys_generate_done))
	    {
		     UART_TEST_LOG(LOG_LVL_INFO,"app_client_set_distribution_data fail\n");
	    }
	    //netkey
	    //get_config_client()->netkey[0].is_used = true;
	    //get_config_client()->netkey[0].curr_idx = 0;
	    //get_config_client()->netkey[0].global_idx = m_client.distribution.key_index;
	    //memcpy(get_config_client()->netkey[0].key[0].netkey , m_client.distribution.network_key , MESH_KEY_LENGTH);
	    //generte_all_net_keys(&get_config_client()->netkey[0].key[0] , client_net_key_all_keys_generate_done);
	}
}
static void client_net_key_all_keys_generate_done(void* dm_handle)
{
    //LOG(3,"client_net_key_all_keys_generate_done\n");
    //1. send system msg
	uart_log_provision_data_t msg;
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_CLIENT_ALL_NET_KEY;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
static void app_client_set_app_key_value(const uint8_t *param)
{
	if(param)// not null
	{
	    dm_appkey_handle_t appkey_handle;
	/// <1> copy appkey data
		//1. bound_netkey_idx
		m_client.appkey.bound_netkey_idx = param[0];
		//2. appkey key
		memcpy(m_client.appkey.key,(param+1),MESH_KEY_LENGTH);
		//3. global_idx     lsb
		m_client.appkey.global_idx = (uint16_t)param[17]|((uint16_t)param[18]<<8);
		//4. curr_idx
		//m_client.appkey.curr_idx = param[19];
		//5. is_used
		//m_client.appkey.is_used = param[20];
	/// <2> set init defalut data
	    //appkey gen
	    if(MESH_CORE_SUCCESS != dm_appkey_add(m_client.appkey.global_idx,m_client.appkey.key,&appkey_handle,client_aid_generate_done))
	    {
			UART_TEST_LOG(LOG_LVL_INFO,"app_client_set_app_key_value fail\n");
	    }
		//get_config_client()->appkey[0].global_idx = m_client.appkey.global_idx;
		//get_config_client()->appkey[0].curr_idx = m_client.appkey.curr_idx;
		//get_config_client()->appkey[0].is_used = m_client.appkey.is_used;
		//get_config_client()->appkey[0].bound_netkey = &get_config_client()->netkey[m_client.appkey.bound_netkey_idx];
	   // memcpy(get_config_client()->appkey[0].key[0].appkey , m_client.appkey.key , MESH_KEY_LENGTH);
	    //k4_derivation(get_config_client()->appkey[0].key[0].appkey , &get_config_client()->appkey[0].key[0].aid , client_aid_generate_done);
	}
}
static void client_aid_generate_done(void* dm_handle)
{
    //LOG(3,"client_aid_generate_done\n");
    //1. send system msg
	//parse  msg
	uart_log_provision_data_t msg;
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_CLIENT_APP_AID_KEY;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
static void client_element_addr_req(uint16_t element_id)
{
	//1. send to pc element req
	uart_log_provision_data_t client;
	client.Opcode = TX_OP_CLIENT_ELEMENT_ADDR_REQ;
	client.len = 2;
	client.param = (uint8_t *)pvPortMalloc(client.len);
	BX_ASSERT(client.param!=NULL);
	//2. copy element id data
	memcpy((uint8_t *)client.param,(uint8_t *)&element_id,2);//id
	client_server_uart_msg_send((uart_log_provision_data_t *)&client);

	if(client.param) vPortFree(client.param);
}
static void app_client_set_element_addr_value(const uint8_t *param)
{
	if(param)// not null
	{
	/// <1> copy element data
		//1. element id
		//m_client.element.id = (uint16_t)param[0]|((uint16_t)param[1]<<8);
		memcpy((uint8_t *)&m_client.element.id,param,2);//id

		if( (m_client.element.id+1) <= CLINET_SERVER_UART_ELEMENT_NUM )//save addr
		{
			//2. element uni_addr
			memcpy((uint8_t *)&m_client.element.uni_addr[m_client.element.id],(param+2),2);
			//m_client.element.uni_addr[m_client.element.id] = (uint16_t)param[2]|((uint16_t)param[3]<<8);
		/// <2> set init defalut data
			//ELEMENT 0
			client_elmts[m_client.element.id].uni_addr = m_client.element.uni_addr[m_client.element.id];
			if(!m_client.element.id)//first element id
			{
			    get_config_client()->model.base.elmt = &client_elmts[0];
			}
		/// req next addr
			m_client.element.id++;
			if(m_client.element.id < CLINET_SERVER_UART_ELEMENT_NUM)
			{
				client_element_addr_req(m_client.element.id);
			}
			else
			{
				client_model_appkey_index_req(0);
			}
	    }
		else//element addr set ok   and  model req
		{
			client_model_appkey_index_req(0);
		}
	}
}
static void client_model_appkey_index_req(uint16_t model_id)
{
	//1. send to pc element req
	uart_log_provision_data_t client;
	client.Opcode = TX_OP_CLIENT_MODEL_APPKEY_INDEX_REQ;
	client.len = 2;
	client.param = (uint8_t *)pvPortMalloc(client.len);
	BX_ASSERT(client.param!=NULL);
	//2. copy element id data
	memcpy((uint8_t *)client.param,(uint8_t *)&model_id,2);//id
	client_server_uart_msg_send((uart_log_provision_data_t *)&client);

	if(client.param) vPortFree(client.param);
}
static void app_client_set_model_appkey_index_value(const uint8_t *param)
{
	if(param)// not null
	{
	/// <1> copy model data
		//1. model id
		memcpy((uint8_t *)&m_client.model.id,param,2);//id

		if( (m_client.model.id+1) <= CLINET_SERVER_UART_MODEL_NUM )//save index
		{
			//2. model index
			memcpy((uint8_t *)&m_client.model.index[m_client.model.id],(param+2),2);
		/// <2> set init defalut data
			//model 0
	        //bound local appkey.
			if(!m_client.model.id)//first element id
			{
			   dm_appkey_handle_t l_handle;
			   dm_appkey_pos_to_handle(m_client.model.index[0],&l_handle);
//			   *generic_onoff_client_0.model.base.bound_key_buf = l_handle;//move to mesh_app.c
//			   *get_config_client()->model.base.bound_key_buf = l_handle;   //no need
			}
		/// req next addr
			m_client.model.id++;
			if(m_client.model.id < CLINET_SERVER_UART_MODEL_NUM)
			{
				client_model_appkey_index_req(m_client.model.id);
			}
			else
			{
				client_server_cfg_data_init_done();
			}
	    }
		else//model index set ok
		{
			client_server_cfg_data_init_done();
		}
	}
}
static void app_client_set_appkey_add_tx_value(const uint8_t *param)
{
	if(param)// not null
	{
		uint16_t app_index=0;
		uint16_t uni_addr =0;
		//1. app_index
		memcpy((uint8_t *)&app_index,param,2);
		//2. uni_addr
		memcpy((uint8_t *)&uni_addr,(param+2),2);
		dm_appkey_handle_t l_handle;
		dm_appkey_pos_to_handle(app_index,&l_handle);
        //3. config_appkey_add_tx-> //ok
        //config_appkey_add_tx(&config_client.model.base,&config_client.appkey[app_index],m_client.distribution.unicast_addr,config_client_appkey_add_test_cb);
		config_appkey_add_tx(&get_config_client()->model.base,l_handle,uni_addr,config_client_appkey_add_test_cb);
	}
}
static void app_client_set_model_app_bind_tx_value(const uint8_t *param)
{
	if(param)// not null
	{
		config_model_app_bind_param_t bind;
		uint16_t uni_addr =0;

		//1. elmt_addr
		memcpy((uint8_t *)&bind.elmt_addr,param,2);
		//2. appkey_idx
		memcpy((uint8_t *)&bind.appkey_idx,(param+2),2);
		//3. model_id
		memcpy((uint8_t *)&bind.model_id,(param+2+2),4);
		//4. sig_model
		memcpy((uint8_t *)&bind.sig_model,(param+2+2+4),1);
		//5. addr
		memcpy((uint8_t *)&uni_addr,(param+2+2+4+1),2);

        //5. config_model_app_bind_tx-> //ok
		//config_model_app_bind_tx(&config_client.model.base,&bind,m_client.distribution.unicast_addr,config_client_model_app_bind_test_cb);
		config_model_app_bind_tx(&get_config_client()->model.base,&bind,uni_addr,config_client_model_app_bind_test_cb);
	}
}
static void app_client_set_client_model_ctrl_msg_value(const uint8_t *param)
{
	if(param)// not null
	{
		uart_log_client_ctrl_msg_t msg;
		//1. id
		memcpy((uint8_t *)&msg.id,param,2);
		//2. addr
		memcpy((uint8_t *)&msg.addr,(param+2),2);
		//3. padta
		switch(msg.id)
		{
		case CTRL_MSG_ID_GENERIC_ONOFF_SET :
			{
				generic_onoff_msg_set_t onoff_val_normal;

				memcpy((uint8_t *)&onoff_val_normal,(param+2+2),sizeof(generic_onoff_msg_set_t));
				onoff_val_normal.tid =  alloc_generic_tid();//auto add

				user_onoff_client_set(&onoff_val_normal,sizeof(onoff_val_normal),msg.addr,1);
			}
			break;
		case CTRL_MSG_ID_GENERIC_ONOFF_SET_DEF :
			{
				generic_onoff_msg_default_set_t onoff_val_default;

				memcpy((uint8_t *)&onoff_val_default,(param+2+2),sizeof(generic_onoff_msg_default_set_t));
				onoff_val_default.tid =  alloc_generic_tid();//auto add

				user_onoff_client_set(&onoff_val_default,sizeof(onoff_val_default),msg.addr,1);
			}
			break;
		default:break;
		}
	}
}
static void app_client_set_client_model_ctrl_msg_noack_value(const uint8_t *param)
{
	if(param)// not null
	{
		uart_log_client_ctrl_msg_t msg;
		//1. id
		memcpy((uint8_t *)&msg.id,param,2);
		//2. addr
		memcpy((uint8_t *)&msg.addr,(param+2),2);
		//3. padta
		switch(msg.id)
		{
		case CTRL_MSG_ID_GENERIC_ONOFF_SET :
			{
				generic_onoff_msg_set_t onoff_val_normal;

				memcpy((uint8_t *)&onoff_val_normal,(param+2+2),sizeof(generic_onoff_msg_set_t));
				onoff_val_normal.tid =  alloc_generic_tid();//auto add

				user_onoff_client_set(&onoff_val_normal,sizeof(onoff_val_normal),msg.addr,0);
			}
			break;
		case CTRL_MSG_ID_GENERIC_ONOFF_SET_DEF :
			{
				generic_onoff_msg_default_set_t onoff_val_default;

				memcpy((uint8_t *)&onoff_val_default,(param+2+2),sizeof(generic_onoff_msg_default_set_t));
				onoff_val_default.tid = alloc_generic_tid();//auto add

				user_onoff_client_set(&onoff_val_default,sizeof(onoff_val_default),msg.addr,0);
			}
			break;
		default:break;
		}

		//4. send ack
		uart_log_provision_data_t ack;

		//1. send to pc client data init done msg
		ack.Opcode = TX_OP_CLIENT_MODLE_CTRL_MSG_NOACK_ACK;
		ack.len = 0;
		client_server_uart_msg_send((uart_log_provision_data_t *)&ack);
	}
}
static void app_client_set_model_subscription_update_tx_value(const uint8_t *param)
{
	if(param)// not null
	{
		config_model_subscribe_param_t subscrip;
		uint16_t uni_addr =0;

		subscrip.subscribe_addr.is_virt = false;//no virt

		//1. subscribe_addr  addr
		memcpy((uint8_t *)&subscrip.subscribe_addr.addr.addr,param,2);
		//2. elmt_addr
		memcpy((uint8_t *)&subscrip.elmt_addr,(param+2),2);
		//3. model_id
		memcpy((uint8_t *)&subscrip.model_id,(param+2+2),4);
		//4. sig_model
		memcpy((uint8_t *)&subscrip.sig_model,(param+2+2+4),1);
		//5. op_mode
		memcpy((uint8_t *)&subscrip.op_mode,(param+2+2+4+1),1);
		//6. addr
		memcpy((uint8_t *)&uni_addr,(param+2+2+4+1+1),2);

        //7. config_model_subscription_update_tx-> //ok
		config_model_subscription_update_tx(&get_config_client()->model.base,&subscrip,uni_addr,config_client_model_subscription_tx_done);
	}
}
static void config_client_model_subscription_tx_done(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_model_subscription_tx_done\n");

	uart_log_provision_data_t msg;

	//1. send to pc client data init done msg
	msg.Opcode = TX_OP_CLIENT_MODLE_SUBSCRIP_UPDATA_TX_ACK;
	msg.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&msg);
}
static void app_client_set_config_relay_get_value(const uint8_t *param)
{
	if(param)// not null
	{
		uint16_t uni_addr =0;

		//1. addr
		memcpy((uint8_t *)&uni_addr,param,2);
        //2. app_client_set_config_relay_get_value-> //ok
		config_relay_get_tx(&get_config_client()->model.base,uni_addr,config_relay_get_tx_cb);
	}
}
static void config_relay_get_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_relay_get_tx_cb\n");
}
static void app_client_set_config_relay_set_value(const uint8_t *param)
{
	if(param)// not null
	{
        config_relay_param_t relay_para;
		uint16_t uni_addr =0;

        //1. relay_para
        memcpy((uint8_t *)&relay_para ,param,2);
		//2. addr
		memcpy((uint8_t *)&uni_addr,(param+2),2);
		//3.app_client_set_config_relay_set_value
        config_relay_set_tx(&get_config_client()->model.base,&relay_para,uni_addr,config_relay_set_tx_cb);
	}
}
static void config_relay_set_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_relay_set_tx_cb\n");
}
static void client_server_cfg_data_init_done(void)
{
    //LOG(3,"client_server_cfg_data_init_done\n");

	uart_log_provision_data_t msg;

	//1. send to pc client data init done msg
	msg.Opcode = TX_OP_CLIENT_CLIENT_DATA_INIT_DONE;
	msg.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&msg);

	//2. set provision env state
	uart_provision_env_set(MSG_CFG_CLIENT_INIT_DONE);

    //3. send system msg
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_CLIENT_DATA_INIT_DONE;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
static void client_server_server_cfg_data_init_done(void)
{
    //LOG(3,"client_server_server_cfg_data_init_done\n");

	uart_log_provision_data_t msg;

	//1. send to pc client data init done msg
	msg.Opcode = TX_OP_SERVER_SERVER_DATA_INIT_DONE;
	msg.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&msg);

	//2. set provision env state
	uart_provision_env_set(MSG_CFG_CLIENT_INIT_DONE);

    //3. send system msg
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_CLIENT_DATA_INIT_DONE;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}

static void generate_device_key_by_ecdh_and_salt(void)
{
    ecdh_prov_salt_to_devkey(provision_key.ecdh_secret.x , session_info.provisioning_salt , m_client.devkey , dev_key_gen_done);
}
static void dev_key_gen_done(void)
{
//    LOG(3,"dev_key_gen_done\n");
//    LOG(3,"devkey=");
//    log_hex_data(devkey,16);
    //1. send system msg
	//parse  msg
	uart_log_provision_data_t msg;
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_CLIENT_DEV_KEY;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
static void client_send_dev_key_val(void)
{
	///<1>. save devkey
	    //memcpy(devkey,m_client.devkey,MESH_KEY_LENGTH);
		config_add_devkey(m_client.devkey,provision_data.unicast_addr);//m_client.distribution.unicast_addr);
	///<2>. send pc devkey
		uart_log_provision_data_t client;

		client.Opcode = TX_OP_CLIENT_DEVICE_KEY_VAL;
		client.len = MESH_KEY_LENGTH;//16
		client.param = (uint8_t *)pvPortMalloc(client.len);//16
		BX_ASSERT(client.param!=NULL);
		//copy devkey data
		memcpy((uint8_t *)client.param,m_client.devkey,MESH_KEY_LENGTH);
		//uart send
		client_server_uart_msg_send((uart_log_provision_data_t *)&client);

		if(client.param) vPortFree(client.param);

	///<3>.send to pc  appkey add req
		client.Opcode = TX_OP_CLIENT_CLIENT_APPKEY_ADD_TX_REQ;
		client.len = 0;
		client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}

static void config_client_appkey_add_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_appkey_add_test_cb\n");

	//1. send model_app_bind  tx req
//	uart_log_provision_data_t client;
//	client.Opcode = TX_OP_CLIENT_MODEL_APP_BIND_TX_REQ;
//	client.len = 0;
//	client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}
static void config_client_model_app_bind_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_model_app_bind_test_cb\n");

	//1. send client_send_message_model  req
//	uart_log_provision_data_t client;
//	client.Opcode = TX_OP_CLIENT_CLIENT_MODLE_CTRL_MSG_REQ;
//	client.len = 0;
//	client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}

//extern system
void config_client_appkey_add_success_cb(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"config_client_appkey_add_success_cb\n");

	//1. send model_app_bind  tx req
	uart_log_provision_data_t client;
	client.Opcode = TX_OP_CLIENT_MODEL_APP_BIND_TX_REQ;
	client.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}
void config_client_model_app_bind_success_cb(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"config_client_model_app_bind_success_cb\n");

	//1. send client_send_message_model  req
	uart_log_provision_data_t client;
	client.Opcode = TX_OP_CLIENT_CLIENT_MODLE_CTRL_MSG_REQ;
	client.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}
void config_client_config_relay_status_success_cb(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"config_client_config_relay_status_success_cb\n");

	//1. send config_client_config_relay_status_success_cb  req
	uart_log_provision_data_t client;
	client.Opcode = TX_OP_CLIENT_CONFIG_RELAY_Set_ACK;
	client.len = 0;
	client_server_uart_msg_send((uart_log_provision_data_t *)&client);
}
///---------------------------- server
static void server_generate_device_key_by_ecdh_and_salt(void)
{
    ecdh_prov_salt_to_devkey(provision_key.ecdh_secret.x , session_info.provisioning_salt , m_client.devkey_s , server_dev_key_gen_done);
}
static void server_dev_key_gen_done(void)
{
//    LOG(3,"dev_key_gen_done\n");
//    LOG(3,"devkey=");
//    log_hex_data(devkey,16);
    //1. send system msg
	//parse  msg
	uart_log_provision_data_t msg;
	msg.device = SYSTEM_MSG;
	msg.Opcode = SYSTEM_MSG_SERVER_DEV_KEY;
	msg.len = 0;

	if(xQueueSend(m_clientQueue,&msg,portMAX_DELAY)!=pdTRUE)
	{
		BX_ASSERT(0);
	}
}
static void server_send_dev_key_val(void)
{
	///<1>. save devkey
	    //memcpy(devkey,m_client.devkey_s,MESH_KEY_LENGTH);
	    config_add_devkey(m_client.devkey_s,provision_data.unicast_addr);

	///<2>. set server data
        //set iv index
        mesh_beacon_iv_index_set(provision_data.current_iv_index);
        //iv_index = provision_data.current_iv_index;
        //init self
        uint8_t add_key_statue = 0;
        init_elmt_addr(provision_data.unicast_addr);
        config_server_add_netkey(provision_data.network_key , provision_data.key_index , &add_key_statue,server_network_keys_generation_done_cb);

//        //ELEMENT 0/1
//        server_elmts[0].uni_addr = provision_data.unicast_addr;
//        server_elmts[1].uni_addr = provision_data.unicast_addr + 1;

	///<2>. send pc devkey
		uart_log_provision_data_t server;

		server.Opcode = TX_OP_SERVER_DEVICE_KEY_VAL;
		server.len = MESH_KEY_LENGTH;//16
		server.param = (uint8_t *)pvPortMalloc(server.len);//16
		BX_ASSERT(server.param!=NULL);
		//copy devkey data
		memcpy((uint8_t *)server.param,m_client.devkey_s,MESH_KEY_LENGTH);
		//uart send
		client_server_uart_msg_send((uart_log_provision_data_t *)&server);

		node_save_element_uni_adddr();
		node_save_misc_iv_index();

		//node data save data done.
		ble_mesh_gatt_evt_update(BLE_MESH_EVT_FLASHSAVE_DONE,0);

		if(server.param) vPortFree(server.param);
}
static void server_network_keys_generation_done_cb(void* handle)
{
    //(dm_netkey_handle_t)handle;
    LOG(3,"server_network_keys_generation_done\n");
}
//-------------------------------------------------------------------------------------------------------------
//send led state
void config_server_send_led_state(uart_log_server_led_ctrl_t led)
{
	///<1>. send pc devkey
		uart_log_provision_data_t server;

		server.Opcode = TX_OP_SERVER_LED_STATE_VAL;
		server.len = 2;
		server.param = (uint8_t *)pvPortMalloc(server.len);
		BX_ASSERT(server.param!=NULL);
		//copy data
		memcpy((uint8_t *)server.param,(uint8_t *)&led.id,1);
		memcpy((uint8_t *)server.param+1,(uint8_t *)&led.OnOff,1);
		//uart send
		client_server_uart_msg_send((uart_log_provision_data_t *)&server);

		if(server.param) vPortFree(server.param);
}
// tid auto add
static uint8_t alloc_generic_tid(void)
{
	static uint8_t client_generic_tid=0;

	client_generic_tid++;
    return client_generic_tid;
}
//-------------------------------------------------------------------------------------------------------------
#endif /* MESH_TEST_UART_CLENT_SERVER */
#endif /* OSAPP_UART_LOG_TEST */
#endif /* OSAPP_MESH */

