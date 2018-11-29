/*
 * mesh_gatt_proxy.h
 *
 *  Created on: 2018Äê8ÔÂ7ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_GATT_MESH_GATT_PROXY_H_
#define FREERTOS_APP_MESH_GATT_MESH_GATT_PROXY_H_

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
#include "mesh_gatt_cfg.h"
#include "mesh_gatt_filter.h"
#include "mesh_gatt.h"
#include "mesh_env.h"
/*
 * DEFINES
 ****************************************************************************************
 */
#define PROXY_CONFIG_PARAM_OVERHEAD (offsetof(proxy_config_msg_t, params))

/*
 * MACROS
 ****************************************************************************************
 */
/// Macro used to retrieve field



/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef enum
{
    PROXY_CONFIG_OPCODE_SET_FILTER_TYPE = 0x00,
    PROXY_CONFIG_OPCODE_ADD_FILTER_ADDR = 0x01,
    PROXY_CONFIG_OPCODE_REMOVE_FILTER_ADDR = 0x02,
    PROXY_CONFIG_OPCODE_FILTER_STATUS = 0x03,
} proxy_config_opcode_t;

typedef struct
{
    uint8_t filter_type;
} proxy_config_params_set_filter_type_t;

typedef struct
{
	uint8_t count;
    uint16_t addrs[5];
} proxy_config_params_add_filter_addr_t;

typedef struct
{
	uint8_t count;
    uint16_t addrs[5];
} proxy_config_params_remove_filter_addr_t;

typedef struct
{
    uint8_t filter_type;
    uint16_t list_size;
} proxy_config_params_filter_status_t;

typedef struct
{
    uint8_t opcode;
    union
    {
    	proxy_config_params_set_filter_type_t set_type;
    	proxy_config_params_add_filter_addr_t add_addr;
    	proxy_config_params_remove_filter_addr_t remove_addr;
        proxy_config_params_filter_status_t filter_status;
    } params;
} proxy_config_msg_t;

typedef struct
{
	uint16_t src_addr;
	uint16_t dst_addr;
	proxy_config_msg_t msg;
}proxy_config_network_pdu_t;
/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */
///**
// * @brief struct to mesh gatt config information
// */
//struct mesh_gatt_cfg_t
//{
//    /// valid or not
//    uint8_t valid;
//    /// store connect index
//    uint16_t conn_idx;
//    /// store the master address
//    bd_addr_t device_addr;
//};
///**
// * @brief struct to mesh gatt config information
// */
//struct mesh_gatt_env_t
//{
//    /// valid or not
//    uint8_t valid;
//    /// store connect index
//    uint16_t conn_idx;
//    /// store the master address
//    bd_addr_t device_addr;
//};


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
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
extern void mesh_gatt_proxy_config_pdu_decrypt_callback(const network_pdu_base_t * p_pdu,uint16_t length,uint16_t conn_index);

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
extern void mesh_gatt_proxy_gatt_network_decrypt_callback(const network_pdu_base_t * p_pdu,uint16_t length,uint16_t conn_index);


/**
 ****************************************************************************************
 * @brief The ble Gatt porxy connect event reset inter database.
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
extern void mesh_gatt_proxy_connection_reset(uint16_t conn_index);
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy disconnect event reset inter database.
 *
 * @param[in] conn_index  gatt connect index.
 *
 ****************************************************************************************
 */
extern void mesh_gatt_proxy_disconnection_reset(uint16_t conn_index);
/**
 ****************************************************************************************
 * @brief The ble Gatt porxy rx handler.
 *
 * @param[in] conn_index  gatt connect index.
 * @param[in] pdu_type    The gatt proxy pdu type.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 ****************************************************************************************
 */
extern void mesh_gatt_proxy_rx_handle(uint16_t conn_index,mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint16_t length);
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
extern void mesh_gatt_proxy_tx_handle(uint16_t conn_index,mesh_gatt_pdu_type_t pdu_type,const uint8_t * p_data,uint16_t length);

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
extern bool mesh_gatt_proxy_tx_addr_is_valid(uint16_t conn_index,uint16_t dst_addr);


#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT_PROXY

#endif /* FREERTOS_APP_MESH_GATT_MESH_GATT_PROXY_H_ */
