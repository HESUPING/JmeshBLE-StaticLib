/**
 ****************************************************************************************
 *
 * @file mesh_gatt_cfg.h
 *
 * @brief BLE Mesh Gatt Config Internal.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */
#ifndef FREERTOS_APP_MESH_GATT_MESH_GATT_CFG_H_
#define FREERTOS_APP_MESH_GATT_MESH_GATT_CFG_H_

/**
 ****************************************************************************************
 * @addtogroup BLE_MESH_GATT_CONFIG  BLE Mesh Gatt Config Internal
 * @ingroup BLE_MESH_GATT
 * @brief defines for BLE mesh gatt  config
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
#include <stdbool.h>
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/** Maximum number of addresses in the GATT proxy address filter, per connection. */
#ifndef MESH_GATT_PROXY_FILTER_ADDR_MAX
#define MESH_GATT_PROXY_FILTER_ADDR_MAX 32 //(2N) = (65-1)/2 = 32
#endif

/** Unassigned address. */
#define MESH_ADDR_UNASSIGNED                  (0x0000)

/** All-proxies fixed group address. */
#define MESH_ALL_PROXIES_ADDR                 (0xFFFC)

/** All-friends fixed group address. */
#define MESH_ALL_FRIENDS_ADDR                 (0xFFFD)

/** All-relays fixed group address. */
#define MESH_ALL_RELAYS_ADDR                  (0xFFFE)

/** All-nodes fixed group address. */
#define MESH_ALL_NODES_ADDR                   (0xFFFF)
/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */
/**
 * @brief struct to mesh gatt config information
 */
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
 * MACROS
 ****************************************************************************************
 */
/// Macro used to retrieve field

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
/// BX24XX Peripheral Service Table
//enum
//{
//    BX24XX_SIMPLES_SERVICE_ID,
//
//
//	BLE_PERIPHERAL_SERVICES_NUM,
//};






/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */







#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT_CONFIG

#endif /* FREERTOS_APP_MESH_GATT_MESH_GATT_CFG_H_ */
