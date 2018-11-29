/**
 ****************************************************************************************
 *
 * @file   network_keys_dm.c
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH

#include "network_keys_dm.h"
#include "buf_management.h"
#include "security.h"
#include "app_keys_dm.h"
#include "node_save_keys.h"
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
typedef enum
{
   GENERATE_KEYBOX_PHASE_PRIMARY = 0,
   GENERATE_KEYBOX_PHASE_UPDATE = 1,
   GENERATE_KEYBOX_PHASE_USER_CB = 2,
}netkey_generate_keybox_phase_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
   dm_async_cb_t func_done;
   dm_netkey_handle_t key_handle;
   netkey_generate_keybox_phase_t phase;//is ready to generate which auto.
}netkey_generate_keybox_t;


/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
DEF_ARRAY_BUF(m_netkey_hdl,net_key_t,DM_CFG_NETKEY_MAX_NUM);


static volatile netkey_generate_keybox_t m_generate_keybox=
{
    .func_done = NULL,
    .key_handle = NULL,
    .phase = GENERATE_KEYBOX_PHASE_PRIMARY,
};

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
static bool dm_index_to_handle(mesh_global_idx_t netkey_idx, dm_netkey_handle_t * pp_netkey_handle);
static bool dm_key_index_to_handle_find(mesh_global_idx_t netkey_idx, const uint8_t * p_key, dm_netkey_handle_t * pp_netkey_handle);
static void dm_netkey_set(mesh_global_idx_t netkey_idx, const uint8_t * p_key, dm_netkey_handle_t p_netkey_handle,dm_async_cb_t func_done);
bool dm_get_all_netkey_handles(dm_netkey_handle_t * pp_netkey_handle_list, uint32_t * p_count);

//for generate allkeys
static void dm_netkey_generate_all_net_keys(dm_netkey_handle_t p_netkey_handle,dm_async_cb_t func_done);
static void dm_netkey_generate_all_net_keys_callback(void);

/**
 ****************************************************************************************
 * @brief   Universal call to flash save net keys
 *
 * @param[in] l_handle        The handle of netkey
 *
 * @return void
 ****************************************************************************************
 */
static void dm_netkey_save_flash(dm_netkey_handle_t l_handle)
{
    uint8_t array_index = array_buf_idx_get(&m_netkey_hdl , l_handle);
    node_save_net_key_add(l_handle , array_index);
}

/**
 ****************************************************************************************
 * @brief   Function fo finds the key index and the network key has in the buf.
 *
 * @param[in] netkey_idx        The network key index of the network key.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the network key.
 *
 * @return If it doesn't exist. Returns true if the devkey exists.
 ****************************************************************************************
 */
static bool dm_index_to_handle(mesh_global_idx_t netkey_idx, dm_netkey_handle_t * pp_netkey_handle)
{
    /* network key index match*/
    bool state = false;
    dm_netkey_handle_t l_handle;

    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
       if(l_handle->global_idx == netkey_idx)
       {
           state = true;
           *pp_netkey_handle = l_handle;
           break;
       }
    );

    return state;
}
/**
 ****************************************************************************************
 * @brief   Function fo finds the key index and the network key has in the buf.
 *
 * @param[in] netkey_idx        The network key index of the network key.
 * @param[in] p_key             Pointer to the network key, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the network key.
 *
 * @return If it doesn't exist. Returns true if the devkey exists.
 ****************************************************************************************
 */
static bool dm_key_index_to_handle_find(mesh_global_idx_t netkey_idx, const uint8_t * p_key, dm_netkey_handle_t * pp_netkey_handle)
{
    /* network key index match  and   key match ,mean Key_Index_Already_Stored*/
    bool state = false;
    dm_netkey_handle_t l_handle;

    if(dm_index_to_handle(netkey_idx,&l_handle))
    {
        if(0 == memcmp(l_handle->key[KEY_PRIMARY].netkey,p_key,MESH_KEY_LENGTH))//same
        {
           state = true;
           *pp_netkey_handle = l_handle;
        }
    }

    return state;
}

/**
 ****************************************************************************************
 * @brief   Function fo finds the key pos  in the buf.
 *
 * @param[in]  p_netkey_handle   Pointer to the Pointer to the handle for the network key.
 * @param[out] p_netkey_pos      Pointer to the pos of  the network key.
 *
 * @return MESH_CORE_ERROR_NOT_FOUND If it doesn't exist. Returns MESH_CORE_SUCCESS if the devkey exists.
 ****************************************************************************************
 */
err_t dm_netkey_handle_to_pos(dm_netkey_handle_t p_netkey_handle, dm_netkey_pos_t *p_pos)
{
    *p_pos = array_buf_idx_get(&m_netkey_hdl,p_netkey_handle);
    return MESH_CORE_SUCCESS;
}

err_t dm_netkey_pos_to_handle(dm_netkey_pos_t pos, dm_netkey_handle_t *pp_netkey_handle)
{
    err_t err =  MESH_CORE_ERROR_NOT_FOUND;
    dm_netkey_handle_t l_handle;
    dm_netkey_pos_t temp = 0;

    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
    {

        if(pos == temp)
        {
            *pp_netkey_handle = l_handle;
            return MESH_CORE_SUCCESS;
        }
        temp++;
    }
    );
    return err;

}

/**
 ****************************************************************************************
 * @brief   Function fo finds the key handle by  network id
 *
 * @param[in] p_network_id      Pointer to the network id, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the network key.
 *
 * @return MESH_CORE_ERROR_NOT_FOUND If it doesn't exist. Returns MESH_CORE_SUCCESS if the netkey exists.
 ****************************************************************************************
 */

err_t dm_netkey_network_id_to_handle(uint8_t *p_network_id,dm_netkey_handle_t *pp_netkey_handle)
{
    err_t err =  MESH_CORE_ERROR_NOT_FOUND;
    dm_netkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle, \
        if(!memcmp(l_handle->key[KEY_PRIMARY].network_id, p_network_id, MESH_KEY_LENGTH) || !memcmp(l_handle->key[KEY_UPDATED].network_id, p_network_id, MESH_KEY_LENGTH)) \
        { \
            *pp_netkey_handle = l_handle;  \
            err = MESH_CORE_SUCCESS;
            break;
        } \
    );
    return err;
}






/**
 ****************************************************************************************
 * @brief   Function To gets all the network key from the device manager pool.
 *
 * @param[out] pp_netkey_handle_list Pointer to the array for storing all the network key handle.
 * @param[out] p_count The size of the @c pp_netkey_handle_list array. Will be changed to the number of
 *
 * @return  false if the given list is not large enough to store all the available network key indices.
 ****************************************************************************************
 */
 bool dm_get_all_netkey_handles(dm_netkey_handle_t * pp_netkey_handle_list, uint32_t * p_count)
{

    bool state = false;
    dm_netkey_handle_t l_handle;
    uint32_t i=0;

    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
           pp_netkey_handle_list[i++] = l_handle;
    );

    if(i) state = true;
    *p_count = i;

    return state;
}
/**
 ****************************************************************************************
 * @brief   Func to save a network key and its associated network key index to the device manager.
 *
 * @param[in] netkey_idx        The network key index of the network key being added.
 * @param[in] p_key             Pointer to the network key, it must be @ref MESH_KEY_LENGTH bytes long.
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 * @param[in] func_done         The callback function when add netkey is done.
 *
 ****************************************************************************************
 */
static void dm_netkey_set(mesh_global_idx_t netkey_idx, const uint8_t * p_key, dm_netkey_handle_t p_netkey_handle,dm_async_cb_t func_done)
{
    LOG(LOG_LVL_INFO,"dm_netkey_set  in\n");

    p_netkey_handle->global_idx = netkey_idx;
    p_netkey_handle->key_refresh_phase = MESH_KEY_REFRESH_PHASE_0;

    memcpy(p_netkey_handle->key[KEY_PRIMARY].netkey,p_key,MESH_KEY_LENGTH);

    //1. save value
    m_generate_keybox.func_done = func_done;
    m_generate_keybox.key_handle = p_netkey_handle;
    m_generate_keybox.phase = GENERATE_KEYBOX_PHASE_USER_CB;
    //2. generate all keys
    generte_all_net_keys(&p_netkey_handle->key[KEY_PRIMARY],dm_netkey_generate_all_net_keys_callback);

    LOG(LOG_LVL_INFO,"dm_netkey_set  out\n");
}

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
err_t dm_netkey_add(mesh_global_idx_t netkey_idx, const uint8_t * p_key, dm_netkey_handle_t * pp_netkey_handle,dm_async_cb_t func_done)
{
    err_t err =  MESH_CORE_SUCCESS;

    dm_netkey_handle_t l_handle;

    if( (NULL == p_key) || (NULL == pp_netkey_handle))
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(dm_key_index_to_handle_find(netkey_idx,p_key,&l_handle))//have in buf
    {
        err = MESH_CORE_ERROR_FORBIDDEN;
    }
    else
    {
        l_handle = array_buf_calloc(&m_netkey_hdl);
        if(NULL == l_handle)
        {
            err = MESH_CORE_ERROR_NO_MEM;
        }
        else
        {
            //1. local save
            dm_netkey_set(netkey_idx,p_key,l_handle,func_done);
            //2. flash save
            dm_netkey_save_flash(l_handle);

            //3. set dev handle
            *pp_netkey_handle = l_handle;
            //4. notify gatt  by send secret beacon
        }
    }

    LOG(LOG_LVL_INFO,"dm_netkey_add err: %d\n", err);
    return err;
}



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
err_t dm_netkey_update(dm_netkey_handle_t p_netkey_handle, const uint8_t * p_key,dm_async_cb_t func_done)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == p_netkey_handle || NULL == p_key )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        memcpy(p_netkey_handle->key[KEY_UPDATED].netkey, p_key, MESH_KEY_LENGTH);

        //1. save value
        m_generate_keybox.func_done = func_done;
        m_generate_keybox.key_handle = p_netkey_handle;
        m_generate_keybox.phase = GENERATE_KEYBOX_PHASE_USER_CB;
        //2. generate all keys
        generte_all_net_keys(&p_netkey_handle->key[KEY_UPDATED],dm_netkey_generate_all_net_keys_callback);
        //flash save
        dm_netkey_save_flash(p_netkey_handle);
    }
    return err;
}

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
err_t dm_netkey_delete(dm_netkey_handle_t p_netkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if(NULL == p_netkey_handle)
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        /* Ensure that the subnetwork has no apps associated */
        //:1. delete bound appkeys
         dm_appkey_netkey_unbind_all(p_netkey_handle);
        //2. delete dev handle in buf
        array_buf_release(&m_netkey_hdl,p_netkey_handle);
        //3. delete data in flash
        uint8_t array_index = array_buf_idx_get(&m_netkey_hdl , p_netkey_handle);
        node_save_net_key_delete(array_index);
    }

    return err;
}
/**
 ****************************************************************************************
 * @brief   Function fo finds the update key info  by  handle
 *
 * @param[in] p_netkey_handle      Pointer to the Pointer to the handle.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the network key.
 *
 * @return MESH_CORE_ERROR_NOT_FOUND If it doesn't exist. Returns MESH_CORE_SUCCESS if the netkey exists.
 ****************************************************************************************
 */

err_t dm_netkey_get_update_info(dm_netkey_handle_t p_netkey_handle, net_key_box_t ** pp_update_netkey_info)
{
    err_t err =  MESH_CORE_SUCCESS;
    if(NULL == p_netkey_handle || NULL == pp_update_netkey_info)
    {
         return MESH_CORE_ERROR_NOT_FOUND;
    }
    *pp_update_netkey_info =&(p_netkey_handle->key[KEY_UPDATED]);
     return err;
}



/**
 ****************************************************************************************
 * @brief   Function To gets the network key for a given network handle from the device manager pool.
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 * @param[out] p_key    Pointer to MESH_KEY_LENGTH array to store the key.
 *
 * @return  The result status of the netkey delete cmd.
 ****************************************************************************************
 */
err_t dm_network_key_get(dm_netkey_handle_t p_netkey_handle, uint8_t ** p_key)
{
    err_t err =  MESH_CORE_SUCCESS;

    if(NULL == p_netkey_handle)
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        *p_key =(p_netkey_handle->key[KEY_PRIMARY].netkey);
    }

    return err;
}

/**
 ****************************************************************************************
 * @brief   Function To gets all the network key from the device manager pool.
 *
 * @param[out] pp_netkey_handle_list Pointer to the array for storing all the network key handle.
 * @param[out] p_count The size of the @c pp_netkey_handle_list array. Will be changed to the number of
 *
 * @return  The result status of the netkey delete cmd.
 ****************************************************************************************
 */
err_t dm_netkey_handle_list_get(dm_netkey_handle_t * pp_netkey_handle_list, uint32_t * p_count)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == pp_netkey_handle_list || NULL == p_count )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else
    {
        dm_get_all_netkey_handles(pp_netkey_handle_list, p_count);
    }

    return err;
}

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
err_t dm_netkey_kr_phase_get(dm_netkey_handle_t p_netkey_handle, mesh_key_refresh_phase_t * p_phase)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == p_netkey_handle || NULL == p_phase )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        *p_phase = p_netkey_handle->key_refresh_phase;
    }

    return err;
}

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
err_t dm_netkey_kr_phase_set(dm_netkey_handle_t p_netkey_handle, mesh_key_refresh_phase_t phase)
{
   err_t err =  MESH_CORE_SUCCESS;

   if (NULL == p_netkey_handle )
   {
       err =  MESH_CORE_ERROR_NULL;
   }
   else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
   {
       err = MESH_CORE_ERROR_NOT_FOUND;
   }
   else
   {
       p_netkey_handle->key_refresh_phase = phase;
       // flash save
       dm_netkey_save_flash(p_netkey_handle);
   }

   return err;
}





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
err_t dm_netkey_update_swap_keys(dm_netkey_handle_t p_netkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == p_netkey_handle)
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else if(p_netkey_handle->key_refresh_phase != MESH_KEY_REFRESH_PHASE_1)
    {
        /* Network keys can only be swapped in key refresh phase 1, */
        /* which will move the procedure to key refresh phase 2.    */
        err = MESH_CORE_ERROR_INVALID_STATE;
    }
    else
    {
        p_netkey_handle->key_refresh_phase = MESH_KEY_REFRESH_PHASE_2;
        //TODO: key refresh change
    }

    return err;
}
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
err_t dm_netkey_update_commit(dm_netkey_handle_t p_netkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == p_netkey_handle)
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else if(MESH_KEY_REFRESH_PHASE_0 == p_netkey_handle->key_refresh_phase )
    {
        err = MESH_CORE_ERROR_INVALID_STATE;
    }
    else
    {
        //TODO: key refresh commit
        memcpy(p_netkey_handle->key[KEY_PRIMARY].netkey,p_netkey_handle->key[KEY_UPDATED].netkey, MESH_KEY_LENGTH);
        p_netkey_handle->key_refresh_phase = MESH_KEY_REFRESH_PHASE_0;

        //app key change
        dm_appkey_refresh_swap_keys(p_netkey_handle);
        //flash save
    }

    return err;
}

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
err_t dm_netkey_index_to_netkey_handle(mesh_global_idx_t netkey_idx,dm_netkey_handle_t * pp_netkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if ( NULL == pp_netkey_handle )
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(!dm_index_to_handle(netkey_idx,pp_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        //find
    }

    return err;
}

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
err_t dm_netkey_handle_to_netkey_index(dm_netkey_handle_t p_netkey_handle, mesh_global_idx_t * p_netkey_idx)
{
    err_t err =  MESH_CORE_SUCCESS;

    if ( (NULL == p_netkey_handle) || (NULL == p_netkey_idx) )
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_netkey_hdl,p_netkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        *p_netkey_idx = p_netkey_handle->global_idx;
    }

    return err;
}



/**
 ****************************************************************************************
 * @brief   Func to adds a network key and its associated network key index to the device manager.
 *
 * @param[in] nid   The network key nid of the network key.
 * @param[in] action The callback function when search the match nid in network key pool.
 *
 * @return The result status of nid search.true when one/more key match ,false when no match key.
 ****************************************************************************************
 */
 /*
bool dm_netkey_nid_search(uint8_t nid,dm_netkey_nid_search_action action)
{
    
    bool state = false;
    dm_netkey_handle_t l_handle;

    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
        if(l_handle->key_refresh_phase != MESH_KEY_REFRESH_PHASE_0)
        {
            //old key and new key may all be used

            //1. old key
            if ( l_handle->key[KEY_PRIMARY].nid == nid)
            {
                state = true;
                action( l_handle,&(l_handle->key[KEY_PRIMARY]) );
            }
            //2. new key
            if ( l_handle->key[KEY_UPDATED].nid == nid)
            {
                state = true;
                action( l_handle,&(l_handle->key[KEY_UPDATED]) );
            }
        }
        else
        {
            //only old key used
            if ( l_handle->key[KEY_PRIMARY].nid == nid)
            {
                state = true;
                action( l_handle,&(l_handle->key[KEY_PRIMARY]) );
            }
        }
    );

    return state;
}
*/
bool dm_netkey_nid_search(uint8_t nid,key_ptr_t *netkey,uint8_t *matched_num)
{
    dm_netkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
    {
        if(l_handle->key[KEY_PRIMARY].nid == nid && l_handle->key[KEY_UPDATED].nid == nid && l_handle->key_refresh_phase !=  MESH_KEY_REFRESH_PHASE_0)
        {
            netkey[*matched_num].key.net  = l_handle;
            netkey[*matched_num].idx = 0;
            *matched_num += 1;
            netkey[*matched_num].key.net  = l_handle;
            netkey[*matched_num].idx = 1;
            *matched_num += 1;
			LOG(3,"nid seatch both !\n");
        }
        else if( l_handle->key[KEY_UPDATED].nid == nid && l_handle->key_refresh_phase !=  MESH_KEY_REFRESH_PHASE_0)
        {
			netkey[*matched_num].key.net  = l_handle;
			netkey[*matched_num].idx = KEY_UPDATED ? 0:1;
			*matched_num += 1;
			LOG(3,"nid seatch update !\n");
        }
        else if(l_handle->key[KEY_PRIMARY].nid == nid)
        {
			netkey[*matched_num].key.net  = l_handle;
			netkey[*matched_num].idx = KEY_PRIMARY;
			*matched_num += 1;
			LOG(3,"nid seatch current! \n");
        }
    }
   );
   return true;
}


bool dm_netkey_nid_check(uint8_t nid)
{
    dm_netkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
    {
        if(l_handle->key[KEY_PRIMARY].nid == nid || l_handle->key[KEY_UPDATED].nid == nid )
        {
            return true;
        }
    }
   );
   return false;
}



err_t dm_netkey_get_first_handle(uint16_t addr,dm_netkey_handle_t *pp_netkey_handle)
{

    dm_netkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_netkey_hdl,l_handle,
       {
           *pp_netkey_handle = l_handle;
           return MESH_CORE_SUCCESS;
       }
       );
    return MESH_CORE_ERROR_NOT_FOUND;
}

void dm_set_netkey_ptr(dm_netkey_handle_t p_netkey_handle,key_ptr_t *key_ptr,bool use_new)
{
    key_ptr->key.net = p_netkey_handle;
    key_ptr->idx = use_new ? KEY_PRIMARY : KEY_UPDATED;
}



err_t dm_netkey_get_identity_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key)
{
    if ( (NULL == p_netkey_handle) || (NULL == pp_key) )
    {
        return MESH_CORE_ERROR_NULL;
    }
    *pp_key = p_netkey_handle->key[KEY_PRIMARY].identity_key;
    return MESH_CORE_SUCCESS;
}

err_t dm_netkey_get_beacon_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key)
{
    if ( (NULL == p_netkey_handle) || (NULL == pp_key) )
    {
        return MESH_CORE_ERROR_NULL;
    }
    *pp_key = p_netkey_handle->key[KEY_PRIMARY].beacon_key;
    return MESH_CORE_SUCCESS;
}

err_t dm_netkey_get_privacy_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key)
{
    if ( (NULL == p_netkey_handle) || (NULL == pp_key) )
    {
        return MESH_CORE_ERROR_NULL;
    }
    *pp_key = p_netkey_handle->key[KEY_PRIMARY].privacy_key;
    return MESH_CORE_SUCCESS;
}

err_t dm_netkey_get_encryption_key(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key)
{
    if ( (NULL == p_netkey_handle) || (NULL == pp_key) )
    {
        return MESH_CORE_ERROR_NULL;
    }
    *pp_key = p_netkey_handle->key[KEY_PRIMARY].encryption_key;
    return MESH_CORE_SUCCESS;
}

err_t dm_netkey_get_network_id(dm_netkey_handle_t p_netkey_handle, uint8_t ** pp_key)
{
    if ( (NULL == p_netkey_handle) || (NULL == pp_key) )
    {
        return MESH_CORE_ERROR_NULL;
    }
    *pp_key = p_netkey_handle->key[KEY_PRIMARY].network_id;
    return MESH_CORE_SUCCESS;
}


/**
 ****************************************************************************************
 * @brief   Function To recovery netkeys from bxfs.
 *
 * @param[in] idx               The index of the netkey in bxfs to set in the network key pool in array index position.
 * @param[in] p_handle          Pointer to the netkey node data recovery from bxfs.
 * @param[in] func_done         The function is callback when the netkey recovery completed.
 *
 * @return  The result status of the netkey update_commit cmd.
 ****************************************************************************************
 */
err_t dm_netkey_recovery_from_bxfs(uint16_t idx,net_key_t *p_handle,dm_async_cb_t func_done)
{
    err_t err =  MESH_CORE_SUCCESS;

    if( NULL==p_handle )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if( idx >=DM_CFG_NETKEY_MAX_NUM)
    {
        err =  MESH_CORE_ERROR_INVALID_PARAM;
    }
    else
    {
        dm_netkey_handle_t l_handle = array_buf_calloc_idx(&m_netkey_hdl,idx);

        if(NULL == l_handle)
        {
            err = MESH_CORE_ERROR_NO_MEM;
        }
        else
        {
            //1. memcpy
            *l_handle = *p_handle;
            //2. generate netkey all keys
            dm_netkey_generate_all_net_keys(l_handle,func_done);
        }
    }
    return err;
}

/**
 ****************************************************************************************
 * @brief   Function to generate_all_net_keys_callback.
 *
 ****************************************************************************************
 */
static void dm_netkey_generate_all_net_keys_callback(void)
{
    LOG(LOG_LVL_INFO,"dm_netkey_generate_all_net_keys_callback phase: %d\n", m_generate_keybox.phase);
    //start generate
    switch(m_generate_keybox.phase)
    {
        case GENERATE_KEYBOX_PHASE_UPDATE :
            m_generate_keybox.phase = GENERATE_KEYBOX_PHASE_USER_CB;// primary is callback by system,and is to generate update auto.
            generte_all_net_keys(&(m_generate_keybox.key_handle->key[KEY_UPDATED]),dm_netkey_generate_all_net_keys_callback);
            break;
        case GENERATE_KEYBOX_PHASE_USER_CB:
            if(NULL != m_generate_keybox.func_done)
            {
                m_generate_keybox.func_done(m_generate_keybox.key_handle);//generate done,and just nofity the user.
            }
            break;
        default:
            LOG(LOG_LVL_ERROR, "!!! ERROR dm_netkey_generate_all_net_keys_callback phase !!!\n");
            break;
    }
}
/**
 ****************************************************************************************
 * @brief   Function to generate_all_net_keys   for recovery netkeys from bxfs.
 *          include   generate all keys for  netkey1 and netkey2
 *
 * @param[in] p_netkey_handle   Pointer to the handle for the network key.
 * @param[in] func_done         The function is callback when the netkey recovery completed.
 *
 ****************************************************************************************
 */
static void dm_netkey_generate_all_net_keys(dm_netkey_handle_t p_netkey_handle,dm_async_cb_t func_done)
{
    //1. save value
    m_generate_keybox.func_done = func_done;
    m_generate_keybox.key_handle = p_netkey_handle;
    m_generate_keybox.phase = GENERATE_KEYBOX_PHASE_UPDATE;// primary is callback by system,and is to generate update auto.
    //2. start generate
    generte_all_net_keys(&(p_netkey_handle->key[KEY_PRIMARY]),dm_netkey_generate_all_net_keys_callback);
}

#endif /* OSAPP_MESH */
