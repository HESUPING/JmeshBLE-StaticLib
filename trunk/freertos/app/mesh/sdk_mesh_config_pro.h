/**
 ****************************************************************************************
 *
 * @file sdk_mesh_config_pro.h
 *
 * @brief Config BLE Mesh SDK Proficient Parameter.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_CORE_SDK_MESH_CONFIG_PRO_H_
#define FREERTOS_APP_MESH_CORE_SDK_MESH_CONFIG_PRO_H_

/**
 ****************************************************************************************
 * @addtogroup MESH_SDK_CFG_PRO_API
 * @ingroup  MESH_SDK_CFG_API
 * @brief defines for BLE MESH sdk config proficient params
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

///< the element number in this node.
#define ELEMENT_NUM 2

 /**
  @defgroup MESH_ERRORS_ALLOC Mesh Global Error Codes
  @{

  @brief Global Error definitions
*/
#define MESH_CORE_ERROR_ALLOC  (0)    ///< Global CORE error alloc
#define MESH_GATT_ERROR_ALLOC  (0x20) ///< Global GATT error alloc
/**
  @}
*/


 /**
  @defgroup MESH_NETWORK_CONFIG  Mesh Global Network config params
  @{

  @brief Network config params definitions
*/
#define NETWORK_MATCHED_KEY_MAX_NUM 3 ///< max network keys matched in cache.
#define DEVKEY_BOUND_NETKEY_MAX_NUM 3 ///< max network keys bound to devkey.
#define APPKEY_BOUND_NETKEY_MAX_NUM 3 ///< max network keys bound to appkey.

#define MODEL_SUNSCRIPTION_LENGTH   3 ///< max subscription length to a model
/**
  @}
*/


 /**
  @defgroup MESH_CONFIG_CLIENT_CONFIG  Mesh Global config client config params
  @{

  @brief config client config params definitions
*/
#define CONFIG_CLIENT_NETKEY_LIST_MAX 2  ///< max netkey num for the config client.
#define CONFIG_CLIENT_APPKEY_LIST_MAX 2  ///< max appkey num for the config client.
#define CONFIG_CLIENT_DEVKEY_LIST_MAX 5 ///< max devkey num for the config client.
/**
  @}
*/


 /**
  @defgroup MESH_CONFIG_SERVER_CONFIG  Mesh Global config server config params
  @{

  @brief config server config params definitions
*/
#define CONFIG_SERVER_NETKEY_LIST_MAX 2  ///< max appkey num for the config server.
#define CONFIG_SERVER_APPKEY_LIST_MAX 2  ///< max netkey num for the config server.
#define CONFIG_SERVER_DEVKEY_LIST_MAX 1  ///< max devkey num for the config server.
/**
  @}
*/


 /**
  @defgroup MESH_COMPANY_INFORMATION  Mesh company information
  @{
  @brief Mesh company information (in config composition data message)
*/
#define MESH_PARAM_CID      0x000C      ///<company identifier
#define MESH_PARAM_PID      0x001A      ///<product identifier
#define MESH_PARAM_VID      0x0001      ///<product version identifier
#define MESH_PARAM_CRPL     0x0008      ///<the minimum number of replay protection list entries in a device
#define MESH_PARAM_LOC      0x0100      ///<location descriptor
/**
  @}
*/
 /**
  @defgroup MESH_DEVICE_MANAGER_CONFIG  Mesh Global device manager config params
  @{

  @brief device manager config params definitions
*/
#define DM_CFG_DEVKEY_MAX_NUM 3 ///< device manager buffer max device keys.
#define DM_CFG_NETKEY_MAX_NUM 3 ///< device manager buffer max network keys.
#define DM_CFG_APPKEY_MAX_NUM 3 ///< device manager buffer max application keys.
/**
  @}
*/


 /**
  @defgroup MESH_NETWORK_CONFIG mesh  mesh network parameters configuration
  @{
  @brief default value of network_transmit_state_t
*/
//note:count max    = 0b111   = 7
//note:interval max = 0b11111 = 31
#define NETWORK_TRANSMIT_DEFAULT_COUNT              5   ///send 6 times  (count + 1)
#define NETWORK_TRANSMIT_DEFAULT_INTERVAL           10  ///interval = step*10 ms
#define NETWORK_TRANSMIT_DEFAULT_RELAY_COUNT        6   ///send 7 times
#define NETWORK_TRANSMIT_DEFAULT_RELAY_INTERVAL     10  ///interval = step*10 ms
/**
  @}
*/

/** Enable Mesh GATT test */
#define OSAPP_MESH_GATT_PROVISIONING_TEST


#endif /* FREERTOS_APP_MESH_CORE_SDK_MESH_CONFIG_PRO_H_ */
/// @} MESH_SDK_CFG_PRO_API
