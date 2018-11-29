/**
 ****************************************************************************************
 *
 * @file   network_keys_dm.h
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-15 10:21
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
 * @addtogroup MESH_NETWORK_KEYS_MANAGER_API Mesh network keys manager API
 * @ingroup MESH_DEVICE_MANAGER_API
 * @brief Mesh network keys manager  API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_NETWORK_KEYS_DM_H_
#define FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_NETWORK_KEYS_DM_H_

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

typedef void (*dm_netkey_nid_search_action)(const dm_netkey_handle_t p_netkey_handle,const net_key_box_t *p_keybox);

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
 * @brief   Func to search netkey which match nid and do the action.
 *
 * @param[in] nid    The network key nid of the network key.
 * @param[in] action The callback function when search the match nid in network key pool.
 *
 * @return The result status of nid search.true when one/more key match ,false when no match key.
 ****************************************************************************************
 */
//extern bool dm_netkey_nid_search(uint8_t nid,dm_netkey_nid_search_action action);
bool dm_netkey_nid_search(uint8_t nid,key_ptr_t *netkey,uint8_t *matched_num);


/**
 ****************************************************************************************
 * @brief   Func to transform a network key index to a network key handle in the device manager.
 *
 * @param[in] netkey_idx   The network key index of the network key.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the network key.
 *
 * @return The result status of the netkey netkey_index_to_netkey_handle cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_index_to_netkey_handle(mesh_global_idx_t netkey_idx,dm_netkey_handle_t * pp_netkey_handle);

/**
 ****************************************************************************************
 * @brief   Func to transform a network key handle to a network key index in the device manager.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 * @param[out] p_netkey_idx     Pointer to the network key index of the network key.
 *
 * @return The result status of the netkey netkey_handle_to_netkey_index cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_handle_to_netkey_index(dm_netkey_handle_t p_netkey_handle, mesh_global_idx_t * p_netkey_idx);

/**
 ****************************************************************************************
 * @brief   Func to adds a network key and its associated network key index to the device manager.
 *
 * @param[in] netkey_idx        The network key index of the network key being added.
 * @param[in] p_key             Pointer to the network key, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the network key.
 * @param[in] func_done         The callback function when add netkey is done.
 *
 * @return The result status of the netkey add cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_add(mesh_global_idx_t netkey_idx, const uint8_t * p_key, dm_netkey_handle_t * pp_netkey_handle,dm_async_cb_t func_done);

/**
 ****************************************************************************************
 * @brief   Function To delete an existing network key from the device manager pool.
 *  All applications bound to the specified subnetwork will also be deleted.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 *
 * @return  The result status of the netkey delete cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_delete(dm_netkey_handle_t p_netkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To gets the network key for a given network handle from the device manager pool.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 * @param[out] p_key    Pointer to MESH_KEY_LENGTH array to store the key.
 *
 * @return  The result status of the netkey get cmd.
 ****************************************************************************************
 */
extern err_t dm_network_key_get(dm_netkey_handle_t p_netkey_handle, uint8_t ** p_key);

/**
 ****************************************************************************************
 * @brief   Function To gets all the network key from the device manager pool.
 *
 * @param[out] pp_netkey_handle_list Pointer to the array for storing all the network key handle.
 * @param[out] p_count The size of the @c pp_netkey_handle_list array. Will be changed to the number of
 *
 * @return  The result status of the netkey list get cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_handle_list_get(dm_netkey_handle_t * pp_netkey_handle_list, uint32_t * p_count);

/**
 ****************************************************************************************
 * @brief   Function To updates an existing network key.
 *
 *  This starts the key refresh procedure for this network, and causes the network
 *  to enter phase 1 of the procedure. In phase 1, the old keys are still used to transmit
 *  messages, but messages can be received using either the old or the new keys.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 * @param[in] p_key             Pointer to the new network key to use, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[in] func_done         The callback function when update netkey is done.
 *
 * @return  The result status of the netkey update cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_update(dm_netkey_handle_t p_netkey_handle, const uint8_t * p_key,dm_async_cb_t func_done);

/**
 ****************************************************************************************
 * @brief   Function To get the current key refresh phase for a network.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key to obtain the key refresh phase from.
 * @param[in] p_phase           Pointer to a variable where the key refresh phase is returned.
 *
 * @return  The result status of the netkey kr_phase_get cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_kr_phase_get(dm_netkey_handle_t p_netkey_handle, mesh_key_refresh_phase_t * p_phase);


/**
****************************************************************************************
* @brief   Function To set the current key refresh phase for a network.
*
* @param[in] p_netkey_handle   Pointer to the handle for the network key which will be set.
* @param[in] phase              a variable indicate  the key refresh phase
*
* @return  The result status of the netkey kr_phase_set cmd.
****************************************************************************************
*/
err_t dm_netkey_kr_phase_set(dm_netkey_handle_t p_netkey_handle, mesh_key_refresh_phase_t phase);



/**
 ****************************************************************************************
 * @brief   Function To Starts using the new network key for the netkey handle.
 *
 *  This switches the key refresh procedure into phase 2. In phase 2, the key refresh
 *  flag is set, and the new keys are used to transmit messages. Messages can still be
 *  received using either the old or the new keys.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key to swap the keys for.
 *
 * @return  The result status of the netkey swap_keys cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_update_swap_keys(dm_netkey_handle_t p_netkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To Commits to using the new network key.
 *
 *  This switches the key refresh procedure into phase 3. In phase 3, the key refresh
 *  flag is cleared and only the new keys are used to send and receive messages. The old
 *  keys are cleared from memory. After the new keys have been set up, phase 0 is automatically
 *  entered.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key to commit the new key to.
 *
 * @return  The result status of the netkey update_commit cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_update_commit(dm_netkey_handle_t p_netkey_handle);

/**
 ****************************************************************************************
 * @brief   Function To recovery netkeys from bxfs.
 *
 * @param[in] idx               The index of the netkey in bxfs to set in the network key pool in array index position.
 * @param[in] p_handle          Pointer to the netkey node data recovery from bxfs.
 * @param[in] func_done         The function is callback when the netkey recovery completed.
 *
 * @return  The result status of the netkey recovery_from_bxfs cmd.
 ****************************************************************************************
 */
extern err_t dm_netkey_recovery_from_bxfs(uint16_t idx,net_key_t *p_handle,dm_async_cb_t func_done);



err_t dm_netkey_handle_to_pos(dm_netkey_handle_t p_netkey_handle, dm_netkey_pos_t *p_pos);
err_t dm_netkey_network_id_to_handle(uint8_t *p_network_id,dm_netkey_handle_t *pp_netkey_handle);
err_t dm_netkey_get_update_info(dm_netkey_handle_t p_netkey_handle, net_key_box_t ** pp_update_netkey_info);
bool dm_get_all_netkey_handles(dm_netkey_handle_t * pp_netkey_handle_list, uint32_t * p_count);
void dm_set_netkey_ptr(dm_netkey_handle_t p_netkey_handle,key_ptr_t *key_ptr,bool use_new);
err_t dm_netkey_get_first_handle(uint16_t addr,dm_netkey_handle_t *pp_netkey_handle);
err_t dm_netkey_pos_to_handle(dm_netkey_pos_t pos, dm_netkey_handle_t *pp_netkey_handle);
bool dm_netkey_nid_check(uint8_t nid);
err_t dm_netkey_get_identity_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key);
err_t dm_netkey_get_beacon_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key);
err_t dm_netkey_get_privacy_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key);
err_t dm_netkey_get_encryption_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key);
err_t dm_netkey_get_network_id(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key);

#endif /* FREERTOS_APP_MESH_DEVICE_MANAGER_KEYS_NETWORK_KEYS_DM_H_ */ 
/// @} MESH_NETWORK_KEYS_MANAGER_API

