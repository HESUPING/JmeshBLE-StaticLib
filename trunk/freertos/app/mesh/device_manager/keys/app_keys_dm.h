/**
 ****************************************************************************************
 *
 * @file   app_keys_dm.h
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-15 10:22
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
 * @addtogroup MESH_APP_KEYS_MANAGER_API Mesh app keys  manager API
 * @ingroup MESH_DEVICE_MANAGER_API
 * @brief defines for Mesh app keys  manager API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_APP_KEYS_DM_H_
#define FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_APP_KEYS_DM_H_

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

typedef void (*dm_appkey_aid_search_action)(const dm_appkey_handle_t p_appkey_handle,const app_key_box_t *p_keybox);


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
 * @brief   Func to search appkey which match aid and netkey handle,and do the action when it matchs.
 *
 * @param[in] aid                   The application key aid of the application key.
 * @param[in] p_netkey_handle       Pointer to the handle for the network key.
 * @param[in] action The callback   Function when search the match aid in application key pool.
 *
 * @return The result status of aid search.true when one/more key match ,false when no match key.
 ****************************************************************************************
 */
extern bool dm_appkey_aid_search(uint8_t aid,dm_netkey_handle_t p_netkey_handle,dm_appkey_aid_search_action action);

/**
 ****************************************************************************************
 * @brief   Func to transform a application key index to a application key handle in the device manager.
 *
 * @param[in] appkey_idx   The application key index of the application key.
 * @param[out] pp_appkey_handle Pointer to the Pointer to the handle for the application key.
 *
 * @return The result status of the appkey appkey_index_to_appkey_handle cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_index_to_appkey_handle(mesh_global_idx_t appkey_idx,dm_appkey_handle_t * pp_appkey_handle);

/**
 ****************************************************************************************
 * @brief   Func to transform a application key handle to a application key index in the device manager.
 *
 * @param[in] p_appkey_handle   Pointer to the handle for the application key.
 * @param[out] p_appkey_idx     Pointer to the application key index of the application key.
 *
 * @return The result status of the appkey appkey_handle_to_appkey_index cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_handle_to_appkey_index(dm_appkey_handle_t p_appkey_handle, mesh_global_idx_t * p_appkey_idx);

/**
 ****************************************************************************************
 * @brief   Func to adds a application key and its associated application key index to the device manager.
 *
 * @param[in] appkey_idx        The application key index of the application key being added.
 * @param[in] p_key             Pointer to the application key, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[out] pp_appkey_handle Pointer to the Pointer to the handle for the application key.
 * @param[in] func_done         The callback function when add appkey is done.
 *
 * @return The result status of the appkey add cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_add(mesh_global_idx_t appkey_idx, const uint8_t * p_key, dm_appkey_handle_t * pp_appkey_handle,dm_async_cb_t func_done);

/**
 ****************************************************************************************
 * @brief   Function To delete an existing application key from the device manager pool.
 *  All applications bound to the specified application will also be deleted.
 *
 * @param[in] p_appkey_handle   Pointer to the handle for the application key.
 *
 * @return  The result status of the appkey delete cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_delete(dm_appkey_handle_t p_appkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To gets all the application key from the device manager pool.
 *
 * @param[out] pp_appkey_handle_list Pointer to the array for storing all the application key handle.
 * @param[out] p_count The size of the @c pp_appkey_handle_list array. Will be changed to the number of
 *
 * @return  The result status of the appkey list get cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_handle_list_get(dm_appkey_handle_t * pp_appkey_handle_list, uint32_t * p_count);

/**
 ****************************************************************************************
 * @brief   Function To updates an existing application key.
 *
 *  This starts the key refresh procedure for this application, and causes the application
 *  to enter phase 1 of the procedure. In phase 1, the old keys are still used to transmit
 *  messages, but messages can be received using either the old or the new keys.
 *
 * @param[in] p_appkey_handle   Pointer to the handle for the application key.
 * @param[in] p_key             Pointer to the new application key to use, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[in] func_done         The callback function when update appkey is done.
 *
 * @return  The result status of the appkey update cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_update(dm_appkey_handle_t p_appkey_handle, const uint8_t * p_key,dm_async_cb_t func_done);

/**
 ****************************************************************************************
 * @brief   Function To recovery appkey from bxfs.
 *
 * @param[in] idx               The index of the appkey in bxfs to set in the application key pool in array index position.
 * @param[in] p_handle          Pointer to the appkey node data recovery from bxfs.
 *
 * @return  The result status of the devkey recovery_from_bxfs cmd.
 ****************************************************************************************
 */
extern err_t dm_appkey_recovery_from_bxfs(uint16_t idx,app_key_t *p_handle);



void dm_appkey_netkey_unbind_all(dm_netkey_handle_t p_netkey_handle);
void dm_appkey_refresh_swap_keys(dm_netkey_handle_t p_netkey_handle);
err_t dm_appkey_match(mesh_global_idx_t appkey_idx,uint8_t *key);
err_t dm_appkey_find(mesh_global_idx_t appkey_idx, dm_appkey_handle_t * pp_appkey_handle);
void dm_appkey_netkey_unbind(mesh_global_idx_t appkey_idx, dm_netkey_handle_t p_netkey_handle);
void dm_appkey_netkey_bind(mesh_global_idx_t appkey_idx, dm_netkey_handle_t p_netkey_handle);
err_t dm_appkey_get_info(dm_appkey_handle_t p_appkey_handle, app_key_box_t ** pp_update_appkey_info);
err_t dm_appkey_get_update_info(dm_appkey_handle_t p_appkey_handle, app_key_box_t ** pp_update_appkey_info);
err_t dm_appkey_get_bound_netkey(dm_appkey_handle_t        p_appkey_handle, dm_netkey_handle_t* pp_netkey_handle);
void dm_set_appkey_ptr(dm_appkey_handle_t p_appkey_handle,key_ptr_t *key_ptr,bool use_new);
void dm_aid_search(uint8_t aid,key_ptr_t *appkey,uint8_t *matched_num);
err_t dm_appkey_pos_to_handle(dm_appkey_pos_t pos, dm_appkey_handle_t *pp_appkey_handle);

#endif /* FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_APP_KEYS_DM_H_ */ 
/// @} MESH_APP_KEYS_MANAGER_API

