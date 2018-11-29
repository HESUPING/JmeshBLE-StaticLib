/*
 * mesh_gatt.c
 *
 *  Created on: 2018��8��2��
 *      Author: huichen
 */

/**
 ****************************************************************************************
 * @addtogroup BLE_MESH_GATT  BLE Mesh Gatt Internal
 * @ingroup BLE_MESH
 * @brief defines for BLE mesh gatt contral
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
#include "mesh_gatt.h"
#include "mesh_gatt_proxy.h"
#include "provisioning_s.h"
#include "proxy_s.h"
#include "osapp_mesh.h"
#include "osapp_utils.h"
#include "ke_msg.h"
#include "co_utils.h"
#include "config_server.h"
#include "sdk_mesh_config_pro.h"
#include "device_keys_dm.h"
#include "network_keys_dm.h"
#include "app_keys_dm.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define MESH_GATT_SYS_TIMER_NAME "MeshGattTimer"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
enum
{
   GATT_RX_SEG_TIMER_STOP = 0,
   GATT_RX_SEG_TIMER_DELETE = 1,
};

/* database reset to delete*/
typedef enum
{
    DATABASE_RESET_MASK_INVALID=0,
    DATABASE_RESET_MASK_DISCONNECT = 0x01,
    DATABASE_RESET_MASK_PROVISION = 0x02,
    DATABASE_RESET_MASK_FLASHSAVE = 0x04,
    DATABASE_RESET_MASK = 0x07,
}database_mask_t;
/*
 * MACROS
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
static bool is_rx_session_in_progress(mesh_gatt_connection_t * p_conn);
static void mesh_gatt_proxy_pdu_rx_first(uint16_t conn_index, const uint8_t * p_data, uint16_t length);
static void mesh_gatt_proxy_pdu_rx_cont(uint16_t conn_index, const uint8_t * p_data, uint16_t length);
static void mesh_gatt_proxy_pdu_rx_done(mesh_gatt_connection_t * p_conn);
static void rx_timer_restart(mesh_gatt_connection_t * p_conn);

static uint16_t conn_index_alloc(uint16_t conn_handle);
static uint16_t conn_handle_to_index(uint16_t conn_handle);
static void conn_index_free(uint16_t conn_index);
static void tx_state_clear(mesh_gatt_connection_t * p_conn);
static void rx_state_clear(mesh_gatt_connection_t * p_conn,bool timer_stop);

static bool is_tx_session_in_progress(mesh_gatt_connection_t * p_conn);
static void mesh_gatt_pdu_send(uint16_t conn_index);
static mesh_gatt_proxy_sar_type_t tools_sar_type_get(uint8_t pdu_length, uint8_t offset, uint16_t mtu);

static void mesh_gatt_timer_create(uint16_t conn_index);
static void mesh_gatt_timer_timerout_callback(TimerHandle_t xTimer);
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static mesh_gatt_t m_gatt;


static osapp_svc_helper_t mesh_svc[2] =
{
    [PROVISION_SVC_IDX] = {
        .svc_desc = &provision_svc_desc,
        .att_desc = provision_svc_att_db,
        .att_num = PROVISION_SVC_ATT_NUM,
        .read = provision_read_req_ind_callback,
        .write = provision_write_req_ind_callback,
    },
    [PROXY_SVC_IDX] = {
        .svc_desc = &proxy_svc_desc,
        .att_desc = proxy_svc_att_db,
        .att_num = PROXY_SVC_ATT_NUM,
        .read = proxy_read_req_ind_callback,
        .write= proxy_write_req_ind_callback,
    },
};
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief The Mesh Gatt disconnect to peer device.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] reason	   gatt disconnect reason.
 *
 ****************************************************************************************
 */
void mesh_gatt_disconnect(uint16_t conn_handle,uint8_t reason)
{
//    /* The timer is stopped in the disconnected event, but we stop it here anyway. */
//    timer_sch_abort(&m_gatt.connections[conn_index].rx.timeout_event);

    struct gapc_disconnect_cmd *cmd = AHI_MSG_ALLOC(GAPC_DISCONNECT_CMD,TASK_ID_GAPC,gapc_disconnect_cmd);

    cmd->operation = GAPC_DISCONNECT;
    cmd->reason = reason;

    osapp_ahi_msg_send(cmd,sizeof(struct gapc_disconnect_cmd), portMAX_DELAY);

	LOG(LOG_LVL_INFO, "mesh_gatt_disconnect.  rea: 0x%x  \n",reason);
}
/**
 ****************************************************************************************
 * @brief The ble Gatt exchange mtu handle.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] mtu  Exchanged MTU value.
 *
 ****************************************************************************************
 */
void ble_mesh_gatt_exchange_mtu_req_handle(uint16_t conn_handle,uint16_t mtu)
{
    uint16_t conn_index = conn_handle_to_index(conn_handle);

    if (conn_index != MESH_GATT_CONN_INDEX_INVALID)
    {
        m_gatt.connections[conn_index].effective_mtu = mtu - MESH_GATT_WRITE_OVERHEAD;
    }
}
/**
 ****************************************************************************************
 * @brief The ble Gatt disconnect event  callback.
 *
 * @param[in] conn_handle  gatt connect handle.
 *
 ****************************************************************************************
 */
void ble_mesh_gatt_disconnect_evt_callback(uint16_t conn_handle)
{
	uint16_t conn_index = conn_handle_to_index(conn_handle);

    if (conn_index != MESH_GATT_CONN_INDEX_INVALID)
    {
        conn_index_free(conn_index);
    	mesh_gatt_proxy_disconnection_reset(conn_index);

    	//adv restart
	    ble_mesh_gatt_adv_start(PROXY_ADV_EVT_BLE_DISCONNECT,0);
	    //delete database
	    ble_mesh_gatt_evt_update(BLE_MESH_EVT_DISCONNECT,0);
    }
    // add user api cb
    if(m_gatt.p_evt_cb) m_gatt.p_evt_cb(MESH_GATT_EVT_DISCONNECT,(mesh_gatt_evt_api_param_t *)&conn_index);

	LOG(LOG_LVL_INFO, "Disconnected\n");
}
/**
 ****************************************************************************************
 * @brief The ble Gatt connect event  callback.
 *
 * @param[in] conn_handle  gatt connect handle.
 *
 ****************************************************************************************
 */
void ble_mesh_gatt_connect_evt_callback(uint16_t conn_handle)
{
    uint16_t conn_index = conn_index_alloc(conn_handle);//connect_src_id -> index

    if (conn_index != MESH_GATT_CONN_INDEX_INVALID)
    {
		//1. proxy connect reset
		mesh_gatt_proxy_connection_reset(conn_index);
		//2. adv stop
	    ble_mesh_gatt_adv_start(PROXY_ADV_EVT_BLE_CONNECT,0);
	    //3. create timer
	    mesh_gatt_timer_create(conn_index);

	//    on_adv_end();
	//    p_connection->connected = true;
	//    connection_reset(p_connection);
	//
	//    /* Send beacons for all known networks upon connection */
	//    beacon_cycle_trigger(p_connection);
	//
	//    /* Advertising must be restarted manually after connecting: */
	//    if (active_connection_count() < MESH_GATT_CONNECTION_COUNT_MAX)
	//    {
	//        adv_start(PROXY_ADV_TYPE_NETWORK_ID, true);
	//    }
	//    break;
    }
    // add user api cb
    if(m_gatt.p_evt_cb) m_gatt.p_evt_cb(MESH_GATT_EVT_CONNECT,(mesh_gatt_evt_api_param_t *)&conn_index);

    LOG(LOG_LVL_INFO, "Connected\n");
}
/**
 ****************************************************************************************
 * @brief The ble Gatt adv start event.
 *
 * @param[in] evt  gatt proxy adv evt.
 * @param[in] p_param   Pointer to the param data.
 *
 ****************************************************************************************
 */
void ble_mesh_gatt_adv_start(mesh_gatt_adv_evt_t evt,const uint8_t * p_param)
{
	LOG(LOG_LVL_INFO, "ble_mesh_gatt_adv_start %d \n",evt);

	switch(evt)
	{
	case PROXY_ADV_EVT_PROVISIONING_START :
		{
			const mesh_device_adv_beacon_t *p_beacon = (const mesh_device_adv_beacon_t *)p_param;

			provision_service_beacon_start(p_beacon->dev_uuid ,p_beacon->oob_info);
		}
		break;
	case PROXY_ADV_EVT_PROVISIONING_DONE :
		{
            //1.update mesh_provisioning_state
            mesh_provisioning_state_set(PROVISIONING_DONE);
            //2. provision beacon stop
            provision_service_beacon_stop();
            //3. proxy_service_beacon_node_identity_start
            //TODO: select proxy_service_beacon_network_id_start / proxy_service_beacon_node_identity_start
		    if(NULL == p_param)
		    {
		        LOG(LOG_LVL_INFO, "PROXY_ADV--1 \n");

                dm_netkey_handle_t p_netkey_handle[DM_CFG_NETKEY_MAX_NUM];
                uint32_t counter = 0;

                dm_netkey_handle_list_get(&p_netkey_handle[0],&counter);
                BX_ASSERT(counter);
                if( counter )
                {
                    LOG(LOG_LVL_INFO, "PROXY_ADV--2 \n");
                    uint8_t* p_key = NULL;
                    if(MESH_CORE_SUCCESS == dm_netkey_get_identity_key(p_netkey_handle[0],&p_key))
                    {
                        LOG(LOG_LVL_INFO, "PROXY_ADV--3 \n");
                        proxy_service_beacon_node_identity_start(p_key);
                    }
                }
		    }
		}
		break;
	case PROXY_ADV_EVT_BLE_CONNECT :
		{
			//adv stop
			provision_service_beacon_stop();
			proxy_service_beacon_stop();
		}
		break;
	case PROXY_ADV_EVT_BLE_DISCONNECT :
		{
			//adv restart
	    	provision_service_beacon_restart();
	    	proxy_service_beacon_restart();
		}
		break;
	default:break;
	}
}
/**
 ****************************************************************************************
 * @brief The ble mesh gatt events.
 *
 * @param[in] evt  gatt proxy adv evt.
 * @param[in] p_param   Pointer to the param data.
 *
 ****************************************************************************************
 */
void ble_mesh_gatt_evt_update(mesh_gatt_evt_t evt,const uint8_t * p_param)
{
    static volatile database_mask_t l_database_mask = DATABASE_RESET_MASK_INVALID;

    LOG(LOG_LVL_INFO, "ble_mesh_gatt_evt_update %d \n",evt);

    taskENTER_CRITICAL();

    switch(evt)
    {
    case BLE_MESH_EVT_PROVISIONING_DONE :
    {
        gatt_provisioning_states_t state = PROVISIONING_DONE;
        ble_mesh_gatt_adv_start(PROXY_ADV_EVT_PROVISIONING_DONE,&state);
        l_database_mask |= DATABASE_RESET_MASK_PROVISION;
    }
        break;
    case BLE_MESH_EVT_DISCONNECT :
        l_database_mask |= DATABASE_RESET_MASK_DISCONNECT;
        break;
    case BLE_MESH_EVT_FLASHSAVE_DONE :
        l_database_mask |= DATABASE_RESET_MASK_FLASHSAVE;
        break;
    default:
        l_database_mask = DATABASE_RESET_MASK_INVALID;
        break;
    }

    //check evt is all ready
    if((l_database_mask&DATABASE_RESET_MASK) == DATABASE_RESET_MASK)
    {
        // device is ready to reset.
        provision_delete_provision_database();//TODO: ！！！考虑多次重新入网，设备角色属性
    }

    taskEXIT_CRITICAL();
}
/**
 ****************************************************************************************
 * @brief The Mesh  gatt proxy pdu receive (peer device write)
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 ****************************************************************************************
 */
void mesh_gatt_proxy_pdu_rx(uint16_t conn_handle, const uint8_t * p_data, uint16_t length)
{
	uint16_t conn_index = conn_handle_to_index(conn_handle);//connect_src_id -> index

	LOG(LOG_LVL_INFO,"mesh_gatt_proxy_pdu_rx \n");

    if (conn_index != MESH_GATT_CONN_INDEX_INVALID)
    {
		mesh_gatt_connection_t * p_conn = &m_gatt.connections[conn_index];

		if(is_rx_session_in_progress(p_conn))
		{
			mesh_gatt_proxy_pdu_rx_cont(conn_index, p_data, length);
		}
		else
		{
			mesh_gatt_proxy_pdu_rx_first(conn_index, p_data, length);
		}
    }
}

/**
 ****************************************************************************************
 * @brief The Mesh  gatt proxy pdu receive first/complete session (peer device write)
 * @param[in] conn_index  gatt connect index.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_pdu_rx_first(uint16_t conn_index, const uint8_t * p_data, uint16_t length)
{
    mesh_gatt_connection_t * p_conn = &m_gatt.connections[conn_index];
    const mesh_gatt_proxy_pdu_t * p_pdu = (const mesh_gatt_proxy_pdu_t *) p_data;
    uint16_t pdu_length = length - sizeof(mesh_gatt_proxy_pdu_t);

    LOG(LOG_LVL_INFO,"mesh_gatt_proxy_pdu_rx_first \n");

    switch (p_pdu->sar_type)
    {
        case PROXY_SAR_TYPE_COMPLETE:
        {
            memcpy(p_conn->rx.buffer, p_pdu->pdu, pdu_length);
            p_conn->rx.pdu_type = (mesh_gatt_pdu_type_t) p_pdu->pdu_type;
            p_conn->rx.offset = pdu_length;

        	mesh_gatt_proxy_pdu_rx_done(p_conn);
        	rx_state_clear(p_conn,GATT_RX_SEG_TIMER_STOP);
            break;
        }
        case PROXY_SAR_TYPE_FIRST_SEGMENT:
        {
            rx_timer_restart(p_conn);
            memcpy(p_conn->rx.buffer, p_pdu->pdu, pdu_length);
            p_conn->rx.pdu_type = (mesh_gatt_pdu_type_t) p_pdu->pdu_type;
            p_conn->rx.offset = pdu_length;
            break;
        }
        default:
            /* Invalid PDU in this state. */
            break;
    }
}
/**
 ****************************************************************************************
 * @brief The Mesh  gatt proxy pdu receive conntinu/last session (peer device write)
 * @param[in] conn_index  gatt connect index.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_pdu_rx_cont(uint16_t conn_index, const uint8_t * p_data, uint16_t length)
{
    mesh_gatt_connection_t * p_conn = &m_gatt.connections[conn_index];
    const mesh_gatt_proxy_pdu_t * p_pdu = (const mesh_gatt_proxy_pdu_t *) p_data;
    uint16_t pdu_length = length - sizeof(mesh_gatt_proxy_pdu_t);

    LOG(LOG_LVL_INFO,"mesh_gatt_proxy_pdu_rx_cont \n");

    switch (p_pdu->sar_type)
    {
        case PROXY_SAR_TYPE_CONT_SEGMENT:
        {
            rx_timer_restart(p_conn);
            if( (p_conn->rx.offset + pdu_length) <= MESH_GATT_PACKET_MAX_SIZE )
            {
				memcpy(&p_conn->rx.buffer[p_conn->rx.offset], p_pdu->pdu, pdu_length);
				p_conn->rx.offset += pdu_length;
            }
        	else
        	{
        		LOG(LOG_LVL_ERROR,"!!! mesh_gatt_proxy_pdu_rx_cont length error !!! \n");
        	}
            break;
        }
        case PROXY_SAR_TYPE_LAST_SEGMENT:
        {
        	if( (p_conn->rx.offset + pdu_length) <= MESH_GATT_PACKET_MAX_SIZE )
        	{
        		memcpy(&p_conn->rx.buffer[p_conn->rx.offset], p_pdu->pdu, pdu_length);
        		p_conn->rx.offset += pdu_length;
        	}
        	else
        	{
        		LOG(LOG_LVL_ERROR,"!!! mesh_gatt_proxy_pdu_rx_cont length error !!! \n");
        	}
        	mesh_gatt_proxy_pdu_rx_done(p_conn);
            rx_state_clear(p_conn,GATT_RX_SEG_TIMER_STOP);
            break;
        }
        default:
            /* Invalid PDUs in this state. */
            break;
    }
}
/**
 ****************************************************************************************
 * @brief Judge the mesh gatt pdu rx is complete done.
 *
 * @param[in] p_conn Pointer to the gatt connect data.
 *
 ****************************************************************************************
 */
static void mesh_gatt_proxy_pdu_rx_done(mesh_gatt_connection_t * p_conn)
{
	uint16_t conn_index = conn_handle_to_index(p_conn->conn_handle);

	mesh_gatt_proxy_rx_handle(conn_index,p_conn->rx.pdu_type,p_conn->rx.buffer,p_conn->rx.offset);
}
/**
 ****************************************************************************************
 * @brief Judge the mesh gatt pdu rx is sessioning.
 *
 * @param[in] p_conn Pointer to the gatt connect data.
 *
 * @return rx session is in progress. 0 for not session and 1 for sessioning.
 *
 ****************************************************************************************
 */
static bool is_rx_session_in_progress(mesh_gatt_connection_t * p_conn)
{
    return (p_conn->rx.offset > 0);
}
/**
 ****************************************************************************************
 * @brief The mesh gatt pdu rx timer restart.
 *
 * @param[in] p_conn Pointer to the gatt connect data.
 *
 ****************************************************************************************
 */
static void rx_timer_restart(mesh_gatt_connection_t * p_conn)
{
	//xTimerStart(p_conn->rx.timeout_event.handle,0);
	xTimerReset(p_conn->rx.timeout_event.handle,0);
}
/**
 ****************************************************************************************
 * @brief The mesh gatt pdu rx state reset.
 *
 * @param[in] p_conn Pointer to the gatt connect data.
 * @param[in] timer_stop The value is to stop the timer. 0 is not stop,1 is stop.
 *
 ****************************************************************************************
 */
static void rx_state_clear(mesh_gatt_connection_t * p_conn,bool timer_stop)
{
	if(timer_stop)
	{
		xTimerDelete(p_conn->rx.timeout_event.handle,0);
		memset(&p_conn->rx.timeout_event,0,sizeof(timer_event_t));
	}
    p_conn->rx.offset = 0;
    p_conn->rx.pdu_type = MESH_GATT_PDU_TYPE_INVALID;
}







/**
 ****************************************************************************************
 * @brief The ble Gatt connect index to handle( index -> src id)
 *
 * @param[in] conn_index  gatt connect index.
 *
 * @return conn_handle  gatt connect handle.
 *
 ****************************************************************************************
 */
uint16_t mesh_gatt_conn_index_to_handle(uint16_t conn_index)
{
	if (conn_index < MESH_GATT_CONNECTION_COUNT_MAX)
	{
		return m_gatt.connections[conn_index].conn_handle;
	}
	else
	{
		return MESH_GATT_CONN_INDEX_INVALID;
	}
}
/**
 ****************************************************************************************
 * @brief The ble Gatt connect index alloc ( src id -> index)
 *
 * @param[in] conn_index  gatt connect index.
 *
 * @return conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
static uint16_t conn_index_alloc(uint16_t conn_handle)
{
    for (uint8_t i = 0; i < MESH_GATT_CONNECTION_COUNT_MAX; ++i)
    {
        if (m_gatt.connections[i].conn_handle == MESH_GATT_CONN_INDEX_INVALID)
        {
            m_gatt.connections[i].conn_handle = conn_handle;
            return i;
        }
    }

    return MESH_GATT_CONN_INDEX_INVALID;
}
/**
 ****************************************************************************************
 * @brief The ble Gatt connect handle to index( src id -> index)
 *
 * @param[in] conn_index  gatt connect index.
 *
 * @return conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
static uint16_t conn_handle_to_index(uint16_t conn_handle)
{
    for (uint8_t i = 0; i < MESH_GATT_CONNECTION_COUNT_MAX; ++i)
    {
        if (m_gatt.connections[i].conn_handle == conn_handle)
        {
            return i;
        }
    }

    return MESH_GATT_CONN_INDEX_INVALID;
}
/**
 ****************************************************************************************
 * @brief The ble Gatt connect index free.(database reset)
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
static void conn_index_free(uint16_t conn_index)
{
	BX_ASSERT(conn_index < MESH_GATT_CONNECTION_COUNT_MAX);

    rx_state_clear(&m_gatt.connections[conn_index],GATT_RX_SEG_TIMER_DELETE);
    tx_state_clear(&m_gatt.connections[conn_index]);
    //packet_buffer_flush(&m_gatt.connections[conn_index].tx.packet_buffer);
    m_gatt.connections[conn_index].conn_handle = MESH_GATT_CONN_INDEX_INVALID;
}
/**
 ****************************************************************************************
 * @brief The ble Gatt connect tx state reset.(database reset)
 *
 * @param[in] p_conn Pointer to the gatt connect data.
 *
 ****************************************************************************************
 */
static void tx_state_clear(mesh_gatt_connection_t * p_conn)
{
	p_conn->tx.length = 0;
	p_conn->tx.offset = 0;
	memset(p_conn->tx.pdu.buffer,0,MESH_GATT_TX_BUFFER_SIZE);
}







//----------------------------------------------------------------------------------------------------tx
/**
 *************************************************************************************************
 * @brief Sends a mesh gatt proxy pdu tx.
 *
 * @param[in] pdu_type    The proxy pdu type.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 * @param[in] dst_addr    The destination address.
 *
 *************************************************************************************************
 */
void mesh_gatt_proxy_pdu_tx(mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint8_t length,uint16_t dst_addr)
{
	uint32_t state = MESH_GATT_ERROR_INTERNAL;

	for(uint8_t i=0;i<MESH_GATT_CONNECTION_COUNT_MAX;i++)
	{
		mesh_gatt_connection_t * p_conn = &m_gatt.connections[i];

		if(p_conn->conn_handle != MESH_GATT_CONN_INDEX_INVALID)
		{
			switch (pdu_type)
			{
				case MESH_GATT_PDU_TYPE_NETWORK_PDU:
					{
						if(mesh_gatt_proxy_tx_addr_is_valid(i,dst_addr))
						{
							state = mesh_gatt_packet_send(i,pdu_type,p_data,length);
						}
					}
					break;
				case MESH_GATT_PDU_TYPE_MESH_BEACON:
				case MESH_GATT_PDU_TYPE_PROXY_CONFIG:
				case MESH_GATT_PDU_TYPE_PROV_PDU:
					state = mesh_gatt_packet_send(i,pdu_type,p_data,length);
					break;
				default:
					/* Ignore unknown PDU type, according to Mesh Profile Specification v1.0, section 6.6 */
					break;
			}
			LOG(LOG_LVL_INFO,"mesh_gatt_proxy_pdu_tx state 0x%x ,pdu_tpye 0x%x\n",state,pdu_type);
		}
	}
}



/**
 *************************************************************************************************
 * @brief Sends a mesh gatt packet.
 *
 * @param[in] conn_index  Connection index of the Mesh GATT connection to transmit the packet.
 * @param[in] pdu_type    The proxy pdu type.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 * @retval MESH_GATT_SUCCESS             Successfully started packet transmission.
 * @retval MESH_GATT_ERROR_INVALID_STATE The given @c conn_index is not in a connected state.
 *
 *************************************************************************************************
 */
uint32_t mesh_gatt_packet_send(uint16_t conn_index, mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint8_t length)
{
	BX_ASSERT(p_data != NULL);
	BX_ASSERT(conn_index < MESH_GATT_CONNECTION_COUNT_MAX);
	BX_ASSERT(length <= MESH_GATT_PACKET_MAX_SIZE);

	mesh_gatt_connection_t * p_conn = &m_gatt.connections[conn_index];
	mesh_gatt_proxy_pdu_t * p_pdu = (mesh_gatt_proxy_pdu_t *)&m_gatt.connections[conn_index].tx.pdu.buffer[0];

	if (p_conn->conn_handle == MESH_GATT_CONN_INDEX_INVALID || is_tx_session_in_progress(p_conn))
	{
		return MESH_GATT_ERROR_INVALID_STATE;
	}

	p_pdu->pdu_type = pdu_type;
	memcpy(p_pdu->pdu,p_data,length);
	m_gatt.connections[conn_index].tx.offset = 0;
	m_gatt.connections[conn_index].tx.length = length + sizeof(mesh_gatt_proxy_pdu_t);

	mesh_gatt_pdu_send(conn_index);

	return MESH_GATT_SUCCESS;
}



/**
 *************************************************************************************************
 * @brief Sends mesh gatt pdu.
 *
 * @param[in] conn_index  Connection index of the Mesh GATT connection to transmit the packet.
 *
 *************************************************************************************************
 */
static void mesh_gatt_pdu_send(uint16_t conn_index)
{
    mesh_gatt_connection_t * p_conn = &m_gatt.connections[conn_index];
    uint8_t send_state = 1;//sending
    uint16_t send_len = 0;
    mesh_gatt_pdu_type_t pdu_type = (mesh_gatt_pdu_type_t)m_gatt.connections[conn_index].tx.pdu.proxy.pdu_type;

    while(send_state)
    {
    	mesh_gatt_proxy_sar_type_t sar_type = tools_sar_type_get(p_conn->tx.length,p_conn->tx.offset,p_conn->effective_mtu);
        mesh_gatt_proxy_pdu_t * p_proxy_pdu =(mesh_gatt_proxy_pdu_t *) &m_gatt.connections[conn_index].tx.pdu.buffer[p_conn->tx.offset];

    	switch(sar_type)
    	{
    	case PROXY_SAR_TYPE_FIRST_SEGMENT:
    	case PROXY_SAR_TYPE_CONT_SEGMENT:
    		send_len = p_conn->effective_mtu;
    		break;
    	case PROXY_SAR_TYPE_COMPLETE:
    	case PROXY_SAR_TYPE_LAST_SEGMENT:
    		send_len = p_conn->tx.length -p_conn->tx.offset;
    		send_state = 0;//send over
    		break;
    	default:
    		LOG(LOG_LVL_ERROR,"!!! mesh_gatt_pdu_send sar type error !!! \n");
    		BX_ASSERT(0);
    		break;
    	}
    	p_proxy_pdu->pdu_type = pdu_type;
    	p_proxy_pdu->sar_type = sar_type;
    	//send pdu
    	mesh_gatt_proxy_tx_handle(conn_index,pdu_type,(uint8_t *)p_proxy_pdu,send_len);
    	//updata
    	if(send_state)	p_conn->tx.offset += send_len - sizeof(mesh_gatt_proxy_pdu_t);
    	else			p_conn->tx.offset = 0;
    }
}


/**
 ****************************************************************************************
 * @brief Judge the mesh gatt pdu tx is sessioning.
 *
 * @param[in] p_conn Pointer to the gatt connect data.
 *
 * @return tx session is in progress. 0 for not session and 1 for sessioning.
 *
 ****************************************************************************************
 */
static bool is_tx_session_in_progress(mesh_gatt_connection_t * p_conn)
{
    return (p_conn->tx.offset > 0);
}

/**
 ****************************************************************************************
 * @brief Judge the mesh gatt pdu  sar type
 *
 * @param[in] pdu_length The length of pdu.
 * @param[in] offset 	 The offset in pdu.
 * @param[in] mtu 		 The max mtu size in tx.
 *
 * @return proxy pdu sar type.
 *
 ****************************************************************************************
 */
static mesh_gatt_proxy_sar_type_t tools_sar_type_get(uint8_t pdu_length, uint8_t offset, uint16_t mtu)
{
    if (offset == 0)
    {
        if (pdu_length <= mtu)
        {
            return PROXY_SAR_TYPE_COMPLETE;
        }
        else
        {
            return PROXY_SAR_TYPE_FIRST_SEGMENT;
        }
    }
    else
    {
        if ((pdu_length - offset) <= mtu)
        {
            return PROXY_SAR_TYPE_LAST_SEGMENT;
        }
        else
        {
            return PROXY_SAR_TYPE_CONT_SEGMENT;
        }
    }
}


/**
 ****************************************************************************************
 * @brief The mesh gatt sar timer time out callback.
 *
 * @param[in] xTimer  Timer Handle.
 *
 ****************************************************************************************
 */
static void mesh_gatt_timer_timerout_callback(TimerHandle_t xTimer)
{
	uint8_t i=0;

	LOG(LOG_LVL_ERROR,"!!! mesh_gatt_timer_timerout_callback !!! \n");

	for(i=0;i<MESH_GATT_CONNECTION_COUNT_MAX;i++)
	{
		if(m_gatt.connections[i].rx.timeout_event.handle == xTimer)
		{
			mesh_gatt_disconnect(m_gatt.connections[i].conn_handle,CO_ERROR_CONN_ACCEPT_TIMEOUT_EXCEED);
		}
	}
}
/**
 ****************************************************************************************
 * @brief The Mesh Gatt timer create.
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
static void mesh_gatt_timer_create(uint16_t conn_index)
{
	m_gatt.connections[conn_index].rx.timeout_event.handle = xTimerCreate(MESH_GATT_SYS_TIMER_NAME,MESH_GATT_RX_SAR_TIMEOUT_MS,pdFALSE,(void *)0,mesh_gatt_timer_timerout_callback);
	BX_ASSERT(m_gatt.connections[conn_index].rx.timeout_event.handle !=0 );
}

/**
 ****************************************************************************************
 * @brief The mesh gatt database init.
 *
 ****************************************************************************************
 */
void mesh_gatt_init(void)
{
	//1.
	mesh_proxy_service_data_init();


    for (uint32_t i = 0; i < MESH_GATT_CONNECTION_COUNT_MAX; ++i)
    {
        m_gatt.connections[i].effective_mtu = MESH_GATT_ATT_MTU_DEFAULT - MESH_GATT_WRITE_OVERHEAD;
        m_gatt.connections[i].rx.pdu_type = MESH_GATT_PDU_TYPE_INVALID;
//        m_gatt.connections[i].rx.timeout_event.cb = timeout_cb;
//        m_gatt.connections[i].rx.timeout_event.p_context = &m_gatt.connections[i];
        m_gatt.connections[i].conn_handle = MESH_GATT_CONN_INDEX_INVALID;
        memset(&m_gatt.connections[i].tx,0,sizeof(m_gatt.connections[i].tx));
    }
}

void notify_gatt_server_ready(void)
{
	LOG(LOG_LVL_INFO,"notify_gatt_server_ready\n");
	mesh_stack_init_process_next_stage();
}

/**
 ****************************************************************************************
 * @brief The Mesh gatt add service database callback func.
 *
 ****************************************************************************************
 */
static void add_svc_cb(uint8_t status,osapp_svc_helper_t *svc_helper)
{
    BX_ASSERT(status==ATT_ERR_NO_ERROR);
	notify_gatt_server_ready();
}
/**
 ****************************************************************************************
 * @brief The Mesh gatt add service database.
 *
 ****************************************************************************************
 */
void mesh_add_gatt_svc()
{
	//data init
	mesh_gatt_init();
	if(provision_is_provision_done())
	{
	    LOG(LOG_LVL_INFO,"add_gatt_svc proxy\n");
        osapp_add_svc_req_helper(&mesh_svc[PROXY_SVC_IDX],1,add_svc_cb);
	}
	else
	{
	    LOG(LOG_LVL_INFO,"add_gatt_svc provisoin\n");
        osapp_add_svc_req_helper(&mesh_svc[PROVISION_SVC_IDX],1,add_svc_cb);
	}
}
/**
 ****************************************************************************************
 * @brief The Mesh gatt malloc notify message struct.
 *
 * @param[in] conidx 	 The gatt connect handle.
 * @param[in] length 	 The notify message length.
 * @param[in] provision  The malloc message type. @enum mesh_gatt_notify_id
 *
 * @return Pointer to the notify message value.
 *
 ****************************************************************************************
 */
uint8_t *gatt_alloc_notify_msg(uint8_t conidx,uint8_t length,bool provision)
{
    uint16_t handle;
    if(provision)
    {
        handle = osapp_get_att_handle_helper(&mesh_svc[PROVISION_SVC_IDX],PROVISION_SVC_IDX_OUT_VAL);
    }else
    {
        handle = osapp_get_att_handle_helper(&mesh_svc[PROXY_SVC_IDX],PROXY_SVC_IDX_OUT_VAL);
    }
    struct gattc_send_evt_cmd *cmd = AHI_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,KE_BUILD_ID(TASK_ID_GATTC,conidx), gattc_send_evt_cmd,length);
    cmd ->operation = GATTC_NOTIFY;
    cmd->handle = handle;
    cmd->length = length;
    return cmd->value;
}
/**
 ****************************************************************************************
 * @brief The Mesh gatt send notify message.
 *
 ****************************************************************************************
 */
void gatt_notify_msg_send(uint8_t *data,uint16_t seq_num)
{
    struct gattc_send_evt_cmd *cmd = CONTAINER_OF(data, struct gattc_send_evt_cmd ,value);
    cmd->seq_num = seq_num;
    osapp_ahi_msg_send(cmd,sizeof(struct gattc_send_evt_cmd) + cmd->length, portMAX_DELAY);
}


/**
 ****************************************************************************************
 * @brief Register Callback function type for Mesh gatt event for user api callback.
 *
 * @param[in] p_cb   Pointer to the mesh_gatt_evt_api_cb func.
 *
 ****************************************************************************************
 */
void ble_mesh_gatt_evt_register(mesh_gatt_evt_api_cb_t p_cb)
{
    if(p_cb != NULL)
    {
        m_gatt.p_evt_cb = p_cb;
    }
    else
    {
        LOG(LOG_LVL_ERROR,"!!! ble_mesh_gatt_evt_register cb is null !!! \n");
    }
}

#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT
