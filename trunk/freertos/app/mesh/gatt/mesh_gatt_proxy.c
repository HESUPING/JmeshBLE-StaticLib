/*
 * mesh_gatt_proxy.c
 *
 *  Created on: 2018-8-7
 *      Author: huichen
 */

/**
 ****************************************************************************************
 * @addtogroup BLE_MESH_GATT_PROXY  BLE Mesh Gatt proxy Internal
 * @ingroup BLE_MESH_GATT
 * @brief defines for BLE mesh gatt proxy contral
 *
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_gatt_error.h"
#include "mesh_gatt_filter.h"
#include "mesh_gatt_proxy.h"
#include "provisioning_s.h"
#include "proxy_s.h"
#include "mesh_env.h"
#include "network.h"
#include "mesh_iv_operation_ex.h"
#include "mesh_tools.h"
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    proxy_filter_t filter;
    bool connected;
//    nrf_mesh_key_refresh_phase_t kr_phase;
//    const nrf_mesh_beacon_info_t * p_pending_beacon_info;
//    uint8_t * p_alloc_packet;
//    core_tx_bearer_t bearer;
	network_pdu_base_t net_pdu;
} proxy_connection_t;

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * MACROS
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
//rx
static void mesh_gatt_proxy_config_pdu_rx(uint16_t conn_index,const uint8_t * p_data,uint32_t length);
static void mesh_gatt_proxy_config_pdu_decrypt(uint16_t conn_index,const uint8_t * p_data,uint32_t length);
//tx
static void mesh_gatt_proxy_config_pdu_send_filter_status(void);
static void mesh_gatt_proxy_config_pdu_encrypt(uint16_t conn_index);
static void mesh_gatt_proxy_config_pdu_encrypt_callback(void);
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static proxy_connection_t m_connections[MESH_GATT_CONNECTION_COUNT_MAX];

static uint16_t m_conn_index = MESH_GATT_CONN_INDEX_INVALID;

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy connect event reset inter database.
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_connection_reset(uint16_t conn_index)
{
	proxy_connection_t * p_connection = &m_connections[conn_index];

	p_connection->connected = true;
    mesh_proxy_filter_reset(&p_connection->filter);
//    p_connection->p_pending_beacon_info = NULL;
}
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy disconnect event reset inter database.
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_disconnection_reset(uint16_t conn_index)
{
	proxy_connection_t * p_connection = &m_connections[conn_index];

	p_connection->connected = false;
}
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy rx handler.
 *
 * @param[in] conn_index  gatt connect index.
 * @param[in] pdu_type    The gatt proxy pdu type.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_rx_handle(uint16_t conn_index,mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint16_t length)
{
    const mesh_rx_params_t rx_params =
    {
        .rx_from = MESH_RX_FROM_GATT,
        .params.gatt =
        {
            .connection_index = conn_index,
        }
    };

//	proxy_connection_t * p_connection = &m_connections[conn_index];

    LOG(LOG_LVL_INFO, "RX_GATT_PDU_type 0x%x, len %u\n", pdu_type, length);

    switch (pdu_type)
    {
        case MESH_GATT_PDU_TYPE_NETWORK_PDU:
            network_pdu_gatt_rx(p_data, length, &rx_params);
            break;
        case MESH_GATT_PDU_TYPE_MESH_BEACON:
            //net_beacon_packet_in(p_data, length, &rx_metadata);
            break;
        case MESH_GATT_PDU_TYPE_PROXY_CONFIG:
        	mesh_gatt_proxy_config_pdu_rx(conn_index, p_data, length);
            break;
        case MESH_GATT_PDU_TYPE_PROV_PDU:
        	provisioning_pdu_gatt_rx(p_data,length);
            break;
        default:
            /* Ignore unknown PDU type, according to Mesh Profile Specification v1.0, section 6.6 */
            break;
    }
}
/**
 ****************************************************************************************
 * @brief The ble Gatt Proxy gatt network messages pdu decrypt done callback.
 *
 * @param[in] p_pdu 	  Pointer to the network pdu database.
 * @param[in] length      The length of the decrypt data.
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_gatt_network_decrypt_callback(const network_pdu_base_t * p_pdu,uint16_t length,uint16_t conn_index)
{
	if( (length >= sizeof(network_pdu_base_t)) && (conn_index < MESH_GATT_CONNECTION_COUNT_MAX) )
	{

		proxy_connection_t * p_connection = &m_connections[conn_index];

        if (p_connection->connected)
        {
            if (p_connection->filter.type == PROXY_FILTER_TYPE_WHITELIST)
            {
            	/*
            	 * If the proxy filter is a white list filter, upon receiving a valid Mesh message from the Proxy Client,
            	 * the Proxy Server shall add the unicast address contained in the SRC field of the message to the white list.
            	 * */
            	mesh_proxy_add_filter_addr(&p_connection->filter, &p_pdu->src_addr, 1);
            }
            else
            {
            	/*
            	 * If the proxy filter is a black list filter, upon receiving a valid Mesh message from the Proxy Client,
            	 * the Proxy Server shall remove the unicast address contained in the SRC field of the message from the black list.
            	 * */
            	mesh_proxy_remove_filter_addr(&p_connection->filter, &p_pdu->src_addr, 1);
            }
        }
	}
	else
	{
		LOG(LOG_LVL_ERROR, "!!!mesh_gatt_proxy_gatt_network_decrypt_callback error !!!\n");
	}
}
/**
 ****************************************************************************************
 * @brief The ble Gatt Proxy configuration messages rx handler.
 * 		  (Proxy configuration messages are used to configure the proxy filters.)
 *
 * @param[in] conn_index  gatt connect index.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_config_pdu_rx(uint16_t conn_index,const uint8_t * p_data,uint32_t length)
{
    if (length <= MESH_GATT_PROXY_PDU_MAX_SIZE && length >= PROXY_CONFIG_PARAM_OVERHEAD)
    {
    	mesh_gatt_proxy_config_pdu_decrypt(conn_index,p_data,length);
    }
    else
    {
    	 LOG(LOG_LVL_INFO, "mesh_gatt_proxy_config_pdu_rx too long 0x%x \n", length);
    }
}
/**
 ****************************************************************************************
 * @brief The ble Gatt Proxy configuration messages pdu decrypt.
 *
 * @param[in] conn_index  gatt connect index.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_config_pdu_decrypt(uint16_t conn_index,const uint8_t * p_data,uint32_t length)
{
    const mesh_rx_params_t rx_params =
    {
        .rx_from = MESH_RX_FROM_DECRYPT,
		.params.decrypt =
		{
			.conn_index = conn_index,
		}
    };

	network_pdu_gatt_decrypt(p_data,length,&rx_params);
}
/**
 ****************************************************************************************
 * @brief The Gatt Proxy configuration messages pdu send filter status.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_config_pdu_send_filter_status(void)
{
	if( m_conn_index != MESH_GATT_CONN_INDEX_INVALID)
	{
		proxy_connection_t * p_connection = &m_connections[m_conn_index];

		if(p_connection->connected == true)
		{
			//tx
			mesh_gatt_proxy_config_pdu_encrypt(m_conn_index);
		}
	}
}
/**
 ****************************************************************************************
 * @brief The mesg gatt proxy config pdu encrypt callback.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_config_pdu_encrypt_callback(void)
{
	LOG(LOG_LVL_INFO,"mesh_gatt_proxy_config_pdu_encrypt_callback \n");
}
/**
 ****************************************************************************************
 * @brief The ble Gatt Proxy configuration messages pdu encrypt.
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_config_pdu_encrypt(uint16_t conn_index)
{
	//1. rx data
	proxy_connection_t * p_connection = &m_connections[conn_index];
	network_pdu_base_t *p_pdu_rx = &p_connection->net_pdu;
	//2. tx buf
	network_pdu_base_t *ptr = alloc_network_tx_env(BEARER_ADV);
	uint32_t seq_num = mesh_seqnum_alloc(1);
	uint8_t raw_pdu[MESH_PROXY_CFG_FILTER_STATUS_LENGHT];

	//3. set tx data
	ptr->ctl_ttl_seq_num = (uint32_t)1<<CTL_OFFSET | ((uint32_t)0)<<TTL_OFFSET | seq_num<<SEQ_NUM_OFFSET;//ctl=1 && ttl= 0 && the SEQ field shall use the sequence number of its primary element.
	ptr->src_addr = mesh_node_get_primary_element_addr();//When sending a proxy configuration message, a Proxy Server shall set the SRC field to the unicast address of its primary element.
	ptr->dst_addr = NETWORK_UNASSIGNED_ADDR;//The DST field shall be set to the unassigned address.
	ptr->netkey = p_pdu_rx->netkey;//struct memcpy
	ptr->iv_index = mesh_tx_iv_index_get();
	mesh_proxy_fill_filter_status(&p_connection->filter,raw_pdu);//The TransportPDU field
	network_raw_data_fill(ptr,raw_pdu,sizeof(raw_pdu),0);
	//4. set tx params
	ptr->io_param.tx_params.tx_from = MESH_TX_FROM_ENCRYPT;
	ptr->io_param.tx_params.params.encrypt.conn_index = conn_index;

	//5. network tx
	network_pdu_tx(ptr,mesh_gatt_proxy_config_pdu_encrypt_callback);
//


	LOG(LOG_LVL_INFO,"mesh_gatt_proxy_config_pdu_encrypt \n");

}
/**
 ****************************************************************************************
 * @brief The ble Gatt Proxy configuration messages pdu decrypt done callback.
 *
 * @param[in] p_pdu 	  Pointer to the network pdu database.
 * @param[in] length      The length of the decrypt data.
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_config_pdu_decrypt_callback(const network_pdu_base_t * p_pdu,uint16_t length,uint16_t conn_index)
{
	if( (length >= sizeof(network_pdu_base_t)) && (conn_index < MESH_GATT_CONNECTION_COUNT_MAX) )
	{

		proxy_connection_t * p_connection = &m_connections[conn_index];
		proxy_config_network_pdu_t pdu;
		uint32_t status = MESH_GATT_SUCCESS;
		const uint8_t * p_data = p_pdu->network_raw_data + SRC_DATA_OFFSET ;
		uint16_t msg_len = p_pdu->encrypted_length-3;//dst+op = 2+1 = 3

		//1. save proxy decrypt pdu data
		memcpy(&p_connection->net_pdu,p_pdu,sizeof(network_pdu_base_t));
		//2. set config opcode
		pdu.src_addr = (p_data[0]<<8)|p_data[1];
		pdu.dst_addr = (p_data[2]<<8)|p_data[3];
		pdu.msg.opcode = p_data[4];

		switch (pdu.msg.opcode)
		{
			case PROXY_CONFIG_OPCODE_SET_FILTER_TYPE:
				{
					if(msg_len == 1)
					{
						pdu.msg.params.set_type.filter_type = p_data[5];

						status = mesh_proxy_set_filter_type(&p_connection->filter,pdu.msg.params.set_type.filter_type);
					}
					else
					{
						status = MESH_GATT_ERROR_INVALID_LENGTH;
					}
				}
				break;
			case PROXY_CONFIG_OPCODE_ADD_FILTER_ADDR:
				{
					if(msg_len>1&&!(msg_len%0x01)&&msg_len<=10)//(2~10  2N) 96/8 = 12  12-1=11 ~2N = 10
					{
						pdu.msg.params.add_addr.count = msg_len/2;

						for(uint8_t i=0;i<pdu.msg.params.add_addr.count;i++)
						{
							pdu.msg.params.add_addr.addrs[i]= (p_data[i*2+5]<<8) | (p_data[i*2+6]);
						}
						mesh_proxy_add_filter_addr(&p_connection->filter,pdu.msg.params.add_addr.addrs,pdu.msg.params.add_addr.count);
					}
					else
					{
						status = MESH_GATT_ERROR_INVALID_LENGTH;
					}
				}
				break;
			case PROXY_CONFIG_OPCODE_REMOVE_FILTER_ADDR:
				{
					if(msg_len>1&&!(msg_len%0x01)&&msg_len<=10)//(2~10  2N) 96/8 = 12  12-1=11 ~2N = 10
					{
						pdu.msg.params.remove_addr.count = msg_len/2;

						for(uint8_t i=0;i<pdu.msg.params.remove_addr.count;i++)
						{
							pdu.msg.params.remove_addr.addrs[i]= (p_data[i*2+5]<<8) | (p_data[i*2+6]);
						}
						mesh_proxy_remove_filter_addr(&p_connection->filter,pdu.msg.params.remove_addr.addrs,pdu.msg.params.remove_addr.count);
					}
					else
					{
						status = MESH_GATT_ERROR_INVALID_LENGTH;
					}
				}
				break;
			default:
				status = MESH_GATT_ERROR_INVALID_PARAM;
				LOG(LOG_LVL_ERROR, "!!!proxy_config_network_pdu msg.opcode 0x%x !!!\n", pdu.msg.opcode);
				break;
		}

		//3. send state
        if (status == MESH_GATT_SUCCESS)
        {
        	m_conn_index = conn_index;
        	mesh_run(mesh_gatt_proxy_config_pdu_send_filter_status,portMAX_DELAY,false);
        }
        else
        {
        	LOG(LOG_LVL_ERROR, "!!!proxy_config_network_pdu status 0x%x !!!\n", status);
        }
	}
	else
	{
		LOG(LOG_LVL_ERROR, "!!!mesh_gatt_proxy_config_pdu_decrypt_callback error !!!\n");
	}
}
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy tx handler.
 *
 * @param[in] conn_index  gatt connect index.
 * @param[in] pdu_type    The gatt proxy pdu type.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_tx_handle(uint16_t conn_index,mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint16_t length)
{
//	proxy_connection_t * p_connection = &m_connections[conn_index];
	uint16_t conn_handle = mesh_gatt_conn_index_to_handle(conn_index);

	if(conn_handle != MESH_GATT_CONN_INDEX_INVALID )
	{
		LOG(LOG_LVL_INFO, "TX GATT PDU type 0x%x, len %u\n", pdu_type, length);
	    LOG(LOG_LVL_INFO,"mesh_gatt_proxy_tx_handle: pdu=");
	    log_hex_data((uint8_t *)p_data,length);

		switch (pdu_type)
		{
			case MESH_GATT_PDU_TYPE_NETWORK_PDU:
			case MESH_GATT_PDU_TYPE_MESH_BEACON:
			case MESH_GATT_PDU_TYPE_PROXY_CONFIG:
				mesh_proxy_data_out(conn_handle,p_data,length);
				break;
			case MESH_GATT_PDU_TYPE_PROV_PDU:
				mesh_provisioning_data_out(conn_handle,p_data,length);
				break;
			default:
				/* Ignore unknown PDU type, according to Mesh Profile Specification v1.0, section 6.6 */
				break;
		}
	}
	else
	{
		LOG(LOG_LVL_ERROR,"!!! mesh_gatt_proxy_tx_handle conn_handle error !!! \n");
	}
}
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy tx addr is in the filter valid.
 *
 * @param[in] conn_index  The gatt connect index.
 * @param[in] dst_addr    The destination address.
 *
 * @return Whether or not the tx address is valid( true/false).
 *
 ****************************************************************************************
 */
bool mesh_gatt_proxy_tx_addr_is_valid(uint16_t conn_index,uint16_t dst_addr)
{
	proxy_connection_t * p_connection = &m_connections[conn_index];

	return ((p_connection->connected) && mesh_proxy_filter_addr_is_accept(&p_connection->filter,dst_addr));
}

#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT_PROXY

