/**
 ****************************************************************************************
 *
 * @file   device_manager_api.h
 *
 * @brief  mesh stack for device to manager inter params.
 *
 * @author  Hui Chen
 * @date    2018-09-15 09:50
 * @version <0.0.0.1>
 *
 * @license 
 *              Copyright (C) BlueX Microelectronics 2018
 *                         ALL Right Reserved.
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup MESH_DEVICE_MANAGER_API
 * @ingroup MESH_API
 * @brief defines for BLE MESH DEVICE MANAGER API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_DEVICE_MANAGER_API_DEVICE_MANAGER_API_H_
#define FREERTOS_APP_MESH_DEVICE_MANAGER_API_DEVICE_MANAGER_API_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_errors.h"
#include "sdk_mesh_definitions.h"
/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define MESH_NO_ACK 0
#define MESH_ACK 1
#define MESH_INVALID_NETKEY_HANDLE 0x00000000
#define MESH_INVALID_DEVKEY_HANDLE 0x00000000
#define MESH_INVALID_APPKEY_HANDLE 0x00000000


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief   The callback function is for device manager asynchronous execution action,and it runs when the action is done success.
 *
 * @param[in] dm_handle   Pointer to the handle for the device manager key handle.
 *
 * @note The dm_handle may be  dm_appkey_handle_t / dm_netkey_handle_t.
 *
 ****************************************************************************************
 */
typedef void (*dm_async_cb_t)(void* dm_handle);


/** device manager application key handle type, used for the handles returned for the each set of data added. */
typedef app_key_t * dm_appkey_handle_t;
/** device manager device key handle type, used for the handles returned for the each set of data added. */
typedef dev_key_t * dm_devkey_handle_t;
/** device manager network key handle type, used for the handles returned for the each set of data added. */
typedef net_key_t * dm_netkey_handle_t;



typedef uint8_t  dm_netkey_pos_t;
typedef uint8_t  dm_devkey_pos_t;
typedef uint8_t  dm_appkey_pos_t;

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */



#endif /* FREERTOS_APP_MESH_DEVICE_MANAGER_API_DEVICE_MANAGER_API_H_ */ 
/// @} MESH_DEVICE_MANAGER_API

