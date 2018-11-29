/**
 ****************************************************************************************
 *
 * @file   device_keys_dm.h
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-15 14:12
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
 * @addtogroup MESH_DEVICE_KEYS_MANAGER_API Mesh device keys manager  API
 * @ingroup MESH_DEVICE_MANAGER_API
 * @brief Mesh device keys manager  API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_DEVICE_KEYS_DM_H_
#define FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_DEVICE_KEYS_DM_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "device_manager_api.h"
/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief   Function To Adds a device key to device manager.
 *
 * @param[in] uni_addr          Unicast address associated with this device key.
 * @param[in] p_netkey_handle   Pointer to the handle for the net this device key is being added.
 * @param[in] p_key             Pointer to the device key.
 * @param[out] pp_devkey_handle Pointer to the Pointer to the handle for the device key.
 *
 * @return  The result status of the devkey add cmd.
 ****************************************************************************************
 */
extern err_t dm_devkey_add(uint16_t uni_addr,  const uint8_t * p_key, dm_devkey_handle_t * pp_devkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To delete an existing device key from the device manager pool.
 *
 * @param[in] p_devkey_handle Pointer to the handle for the device key.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
extern err_t dm_devkey_delete(dm_devkey_handle_t p_devkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To obtains the handle for a device key from the device manager pool by unicast address.
 *
 * @param[in] uni_addr          Unicast address associated with this device key.
 * @param[out] pp_devkey_handle Pointer to the Pointer to the handle for the device key.
 *
 * @return If the uniaddr is in device manager pool.
 ****************************************************************************************
 */
extern err_t dm_devkey_uniaddr_to_handle_get(uint16_t uni_addr, dm_devkey_handle_t * pp_devkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To add netkey bound to the devkey.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the net this device key is being added.
 * @param[in] p_devkey_handle   Pointer to the handle for the device key.
 *
 * @return If the bound netkey was consumed or not.
 ****************************************************************************************
 */
extern err_t dm_devkey_bound_netkey_add(dm_netkey_handle_t p_netkey_handle, dm_devkey_handle_t p_devkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To recovery devkey from bxfs.
 *
 * @param[in] idx               The index of the devkey in bxfs to set in the device key pool in array index position.
 * @param[in] p_handle          Pointer to the devkey node data recovery from bxfs.
 *
 * @return  The result status of the devkey recovery_from_bxfs cmd.
 ****************************************************************************************
 */
extern err_t dm_devkey_recovery_from_bxfs(uint16_t idx,dev_key_t *p_handle);



err_t dm_devkey_uniaddr_belong_to_subnet_get(uint16_t uni_addr, dm_netkey_handle_t * pp_netkey_handle);
void dm_devkey_ack_reset(dm_netkey_handle_t netkey_handle);
err_t dm_devkey_ack_set(dm_netkey_handle_t netkey_handle, uint16_t dev_addr);
bool dm_devkey_check_ack(dm_netkey_handle_t netkey_handle);
err_t  dm_devkey_getnext_dev(dm_netkey_handle_t p_netkey_handle, dm_devkey_handle_t* pp_devkey_handle);
err_t dm_devkey_addr_get( dm_devkey_handle_t p_devkey_handle, uint16_t * p_uni_addr);
err_t dm_devkey_get_key(dm_devkey_handle_t p_devkey_handle, uint8_t ** pp_key);
err_t dm_devkey_get_key_by_addr(uint16_t own_addr,uint16_t peer_addr,uint8_t ** pp_key);

#endif /* FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_DEVICE_KEYS_DM_H_ */ 
/// @} MESH_DEVICE_KEYS_MANAGER_API

