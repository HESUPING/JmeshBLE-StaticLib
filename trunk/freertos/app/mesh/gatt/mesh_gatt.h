/*
 * mesh_gatt.h
 *
 *  Created on: 2018��8��2��
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_GATT_MESH_GATT_H_
#define FREERTOS_APP_MESH_GATT_MESH_GATT_H_

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
#include "mesh_gatt_cfg.h"
#include "provision_base.h"
#include "ke_msg.h"
#include "co_error.h"
#include "mesh_env.h"
#include "mesh_gatt_api.h"
/*
 * DEFINES
 ****************************************************************************************
 */
/** Timeout for an incoming SAR transfer as defined in the Mesh Profile specification v1.0, sec. 6.6. */
#define MESH_GATT_RX_SAR_TIMEOUT_MS  pdMS_TO_TICKS(20000)	//20s

/** The maximum number of concurrent GATT connections supported. */
#define MESH_GATT_CONNECTION_COUNT_MAX (1)
#define MAX_CONN_NUM MESH_GATT_CONNECTION_COUNT_MAX



#define MESH_GATT_PROXY_PDU_MAX_SIZE (66)
#define MESH_GATT_MTU_SIZE_MAX       (69)
#define MESH_GATT_PACKET_MAX_SIZE    (MESH_GATT_PROXY_PDU_MAX_SIZE - 1)
#define MESH_GATT_TX_BUFFER_SIZE     (MESH_GATT_PACKET_MAX_SIZE + sizeof(mesh_gatt_proxy_pdu_t))

#define MESH_GATT_ATT_MTU_DEFAULT       (23)
#define MESH_GATT_WRITE_OVERHEAD 		(3)
#define MESH_GATT_CONN_INDEX_INVALID 	(0xFFFF)/**< Invalid Connection Handle. */

/*
 * MACROS
 ****************************************************************************************
 */
/// Macro used to retrieve field
#define MESH_CONNECT_SRCID_TO_HANDLE(src_id) KE_IDX_GET(src_id)//(((src_id)>>8)&0xff)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */
/// mesh gatt pdu type (Type of message contained in the PDU)
typedef enum
{
    MESH_GATT_PDU_TYPE_NETWORK_PDU = 0x00,
    MESH_GATT_PDU_TYPE_MESH_BEACON = 0x01,
    MESH_GATT_PDU_TYPE_PROXY_CONFIG = 0x02,
    MESH_GATT_PDU_TYPE_PROV_PDU = 0x03,
    MESH_GATT_PDU_TYPE_RFU = 0x04,
    MESH_GATT_PDU_TYPE_INVALID = 0xFF
} mesh_gatt_pdu_type_t;
/// mesh gatt proxy sar type  (Message segmentation and reassembly information)
typedef enum
{
	PROXY_SAR_TYPE_COMPLETE = 0x00,
	PROXY_SAR_TYPE_FIRST_SEGMENT = 0x01,
	PROXY_SAR_TYPE_CONT_SEGMENT = 0x02,
	PROXY_SAR_TYPE_LAST_SEGMENT = 0x03,
} mesh_gatt_proxy_sar_type_t;

/// mesh service add database
enum mesh_svc_idx
{
    PROVISION_SVC_IDX,
    PROXY_SVC_IDX,
};
enum mesh_gatt_notify_id
{
    PROXY_NOTIFY = 0,
    PROVISION_NOTIFY = 1,
};
typedef enum
{
    PROXY_ADV_EVT_PROVISIONING_START,
    PROXY_ADV_EVT_PROVISIONING_DONE,
    PROXY_ADV_EVT_BLE_CONNECT,
    PROXY_ADV_EVT_BLE_DISCONNECT,
} mesh_gatt_adv_evt_t;

typedef enum
{
    BLE_MESH_EVT_PROVISIONING_DONE,// the device is provision done.
    BLE_MESH_EVT_DISCONNECT,// ble is to disconnect
    BLE_MESH_EVT_FLASHSAVE_DONE,//save data to flash done,device can reset it self.
} mesh_gatt_evt_t;
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/** Mesh device adv beacon context structure. */
typedef struct
{
	uint8_t dev_uuid[MESH_DEVICE_UUID_LENGTH];
	uint32_t uri_hash;
	uint16_t oob_info;
}mesh_device_adv_beacon_t;

/** Mesh GATT proxy pdu context structure. */
typedef struct
{
    uint8_t pdu_type : 6;
    uint8_t sar_type : 2;
    uint8_t pdu[];
} mesh_gatt_proxy_pdu_t;

/** Mesh timer event context structure. */
typedef struct
{
	TimerHandle_t handle;
} timer_event_t;

/** Mesh GATT connection context structure. */
typedef struct
{
    /** Softdevice connection handle */
    uint16_t conn_handle;
    /** Effective ATT MTU. Three bytes shorter than the negotiated value. */
    uint16_t effective_mtu;
    struct
    {
    	union
		{	struct
    		{
    		    uint8_t pdu_type : 6;
    		    uint8_t sar_type : 2;
    		}proxy;
    		uint8_t buffer[MESH_GATT_TX_BUFFER_SIZE];
		}pdu;
        uint8_t offset;
        uint8_t length;
    } tx;
    struct
    {
        uint8_t buffer[MESH_GATT_PACKET_MAX_SIZE];
        mesh_gatt_pdu_type_t pdu_type;
        uint8_t offset;
        timer_event_t timeout_event;
    } rx;
} mesh_gatt_connection_t;

/**
 * Mesh GATT context structure.
 * @note Not modified by the user.
 */
typedef struct
{
    mesh_gatt_connection_t connections[MESH_GATT_CONNECTION_COUNT_MAX];
    mesh_gatt_evt_api_cb_t p_evt_cb;
} mesh_gatt_t;

/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief The ble Gatt disconnect event  callback.
 *
 * @param[in] conn_handle  gatt connect handle.
 *
 ****************************************************************************************
 */
extern void ble_mesh_gatt_disconnect_evt_callback(uint16_t conn_handle);

/**
 ****************************************************************************************
 * @brief The ble Gatt connect event  callback.
 *
 * @param[in] conn_handle  gatt connect handle.
 *
 ****************************************************************************************
 */
extern void ble_mesh_gatt_connect_evt_callback(uint16_t conn_handle);

/**
 ****************************************************************************************
 * @brief The ble Gatt exchange mtu handle.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] mtu  Exchanged MTU value.
 *
 ****************************************************************************************
 */
extern void ble_mesh_gatt_exchange_mtu_req_handle(uint16_t conn_handle,uint16_t mtu);

/**
 ****************************************************************************************
 * @brief The ble Gatt adv start event.
 *
 * @param[in] evt  gatt proxy adv evt.
 * @param[in] p_param   Pointer to the param data.
 *
 ****************************************************************************************
 */
extern void ble_mesh_gatt_adv_start(mesh_gatt_adv_evt_t evt,const uint8_t * p_param);

/**
 ****************************************************************************************
 * @brief The ble Gatt adv start event.
 *
 * @param[in] evt  ble mesh gatt event.
 * @param[in] p_param   Pointer to the param data.
 *
 ****************************************************************************************
 */
extern void ble_mesh_gatt_evt_update(mesh_gatt_evt_t evt,const uint8_t * p_param);


/**
 ****************************************************************************************
 * @brief The Mesh Gatt disconnect to peer device.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] reason	   gatt disconnect reason.
 *
 ****************************************************************************************
 */
extern void mesh_gatt_disconnect(uint16_t conn_handle,uint8_t reason);

/**
 ****************************************************************************************
 * @brief The Mesh  gatt proxy pdu receive (peer device write)
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 *
 ****************************************************************************************
 */
extern void mesh_gatt_proxy_pdu_rx(uint16_t conn_handle, const uint8_t * p_data, uint16_t length);

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
extern void mesh_gatt_proxy_pdu_tx(mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint8_t length,uint16_t dst_addr);

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
extern uint32_t mesh_gatt_packet_send(uint16_t conn_index, mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint8_t length);

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
extern uint16_t mesh_gatt_conn_index_to_handle(uint16_t conn_index);

/**
 ****************************************************************************************
 * @brief The Mesh  gatt init database.
 *
 ****************************************************************************************
 */
extern void mesh_gatt_init(void);

/**
 ****************************************************************************************
 * @brief The Mesh gatt add service database.
 *
 ****************************************************************************************
 */
extern void mesh_add_gatt_svc(void);
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
extern uint8_t *gatt_alloc_notify_msg(uint8_t conidx,uint8_t length,bool provision);
/**
 ****************************************************************************************
 * @brief The Mesh gatt send notify message.
 *
 ****************************************************************************************
 */
extern void gatt_notify_msg_send(uint8_t *data,uint16_t seq_num);






#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT

#endif /* FREERTOS_APP_MESH_GATT_MESH_GATT_H_ */
