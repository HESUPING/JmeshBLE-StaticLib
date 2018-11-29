/**
 ****************************************************************************************
 *
 * @file   device_keys_dm.c
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH


#include "device_keys_dm.h"
#include "buf_management.h"
#include "network.h"
#include "node_save_keys.h"
#include "mesh_core_api.h"
#include "mesh_env.h"//TODO: remove
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
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
DEF_ARRAY_BUF(m_devkey_hdl,dev_key_t,DM_CFG_DEVKEY_MAX_NUM);

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */


/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
static bool dm_uniaddr_to_devkey_handle_find(uint16_t uni_addr, dm_devkey_handle_t * pp_devkey_handle);
static void dm_devkey_set(uint16_t uni_addr, const uint8_t * p_key, dm_devkey_handle_t p_devkey_handle);

/**
 ****************************************************************************************
 * @brief   Function fo finds the devkey handle of the given unicast address.
 *
 * @param[in] uni_addr           Unicast address associated with this device key.
 * @param[out] pp_devkey_handle  Pointer to the pointer to the handle for the device key.
 *
 * @return If it doesn't exist. Returns true if the devkey exists.
 ****************************************************************************************
 */
static bool dm_uniaddr_to_devkey_handle_find(uint16_t uni_addr, dm_devkey_handle_t * pp_devkey_handle)
{
    bool state = false;
    dm_devkey_handle_t l_handle;

    FOR_EACH_ALLOCATED_ITEM(m_devkey_hdl,l_handle,
       if(l_handle->addr == uni_addr)
       {
           state = true;
           *pp_devkey_handle = l_handle;
           break;
       }
    );

    return state;
}
/**
 ****************************************************************************************
 * @brief   Function To save a device key to device manager.
 *
 * @param[in] uni_addr          Unicast address associated with this device key.
 * @param[in] p_netkey_handle   Pointer to the handle for the net this device key is being added.
 * @param[in] p_key             Pointer to the device key.
 * @param[in] p_devkey_handle   Pointer to the handle for the device key.
 *
 ****************************************************************************************
 */
static void dm_devkey_set(uint16_t uni_addr, const uint8_t * p_key, dm_devkey_handle_t p_devkey_handle)
{
    p_devkey_handle->addr = uni_addr;

    //add bound net key
    //p_devkey_handle->bound_netkey.pool[0] = p_netkey_handle;
    memcpy(p_devkey_handle->key,p_key,MESH_KEY_LENGTH);
}

/**
 ****************************************************************************************
 * @brief   Function To Adds a device key to device manager.
 *
 * @param[in] uni_addr           Unicast address associated with this device key.
 * @param[in] p_netkey_handle    Pointer to the handle for the net this device key is being added.
 * @param[in] p_key              Pointer to the device key.
 * @param[out] pp_devkey_handle  Pointer to the pointer to the handle for the device key.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
err_t dm_devkey_add(uint16_t uni_addr,  const uint8_t * p_key, dm_devkey_handle_t * pp_devkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    dm_devkey_handle_t l_handle;

    LOG(LOG_LVL_INFO,"dm_devkey_add \n");

    if ((NULL == p_key) || (NULL == pp_devkey_handle))
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(!IS_UNICAST_ADDR(uni_addr))
    {
        err = MESH_CORE_ERROR_INVALID_ADDR;
    }
    else if(dm_uniaddr_to_devkey_handle_find(uni_addr,&l_handle))//have in buffer
    {
        err = MESH_CORE_ERROR_FORBIDDEN;
    }
    else
    {
        l_handle = array_buf_calloc(&m_devkey_hdl);
        if(NULL == l_handle)
        {
            err = MESH_CORE_ERROR_NO_MEM;
        }
        else
        {
            //1. local save
            dm_devkey_set(uni_addr,p_key,l_handle);
            //2. flash save
            uint8_t array_index = array_buf_idx_get(&m_devkey_hdl , l_handle);
            node_save_dev_key_add(l_handle , array_index);

            //3. set dev handle
            *pp_devkey_handle = l_handle;
        }
    }

    return err;
}
/**
 ****************************************************************************************
 * @brief   Function To delete an existing device key from the device manager pool.
 *
 * @param[in] p_devkey_handle Pointer to the handle for the device key.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
err_t dm_devkey_delete(dm_devkey_handle_t p_devkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if(NULL == p_devkey_handle)
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else if(!array_buf_is_elem_handle_valid(&m_devkey_hdl,p_devkey_handle))
    {
        err = MESH_CORE_ERROR_NOT_FOUND;
    }
    else
    {
        //1. delete dev handle in buf
        array_buf_release(&m_devkey_hdl,p_devkey_handle);
        //2. delete data in flash
        uint8_t array_index = array_buf_idx_get(&m_devkey_hdl , p_devkey_handle);
        node_save_dev_key_delete(array_index);
    }

    return err;
}
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
err_t dm_devkey_uniaddr_to_handle_get(uint16_t uni_addr, dm_devkey_handle_t * pp_devkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == pp_devkey_handle )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if(!IS_UNICAST_ADDR(uni_addr))
    {
        err = MESH_CORE_ERROR_INVALID_ADDR;
    }
    else
    {
        dm_devkey_handle_t l_handle;

        if(dm_uniaddr_to_devkey_handle_find(uni_addr,&l_handle))//have in buffer
        {
            *pp_devkey_handle = l_handle;
        }
        else
        {
            err = MESH_CORE_ERROR_NOT_FOUND;
        }
    }

    return err;
}


/**
 ****************************************************************************************
 * @brief   Function To obtains all netkey handle for a device key from the device manager pool by unicast address.
 *
 * @param[in] uni_addr          Unicast address associated with this device key.
 * @param[out] pp_netkey_handle Pointer to the Pointer to the handle for the net key.
 *
 * @return If the uniaddr is in device manager pool.
 ****************************************************************************************
 */
err_t dm_devkey_uniaddr_belong_to_subnet_get(uint16_t uni_addr, dm_netkey_handle_t * pp_netkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if (NULL == pp_netkey_handle )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if(!IS_UNICAST_ADDR(uni_addr))
    {
        err = MESH_CORE_ERROR_INVALID_ADDR;
    }
    else
    {
        dm_devkey_handle_t l_handle;
        dm_devkey_pos_t pos;
        dm_devkey_pos_t counter = 0;
        FOR_EACH_ALLOCATED_ITEM(m_devkey_hdl,l_handle,
           if(l_handle->addr == uni_addr)
           {
               for(pos=0; pos < DEVKEY_BOUND_NETKEY_MAX_NUM; pos++)
               {
                  if(l_handle->bound_netkey.pool[pos] != MESH_INVALID_NETKEY_HANDLE)
                   {
                          pp_netkey_handle[counter] = l_handle->bound_netkey.pool[pos];
                   }
               }
               break;
           }
        );

    }

    return err;
}


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
err_t dm_devkey_bound_netkey_add(dm_netkey_handle_t p_netkey_handle, dm_devkey_handle_t p_devkey_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if ((NULL == p_netkey_handle) || (NULL == p_devkey_handle))
    {
        err = MESH_CORE_ERROR_NULL;
    }
    else
    {
        //TODO: mask memory mangment.

        //DEVKEY_BOUND_NETKEY_MAX_NUM
        //add bound net key
        p_devkey_handle->bound_netkey.pool[1] = p_netkey_handle;
    }

    return err;
}

/**
 ****************************************************************************************
 * @brief   Function To recovery devkey from bxfs.
 *
 * @param[in] idx               The index of the devkey in bxfs to set in the network key pool in array index position.
 * @param[in] p_handle          Pointer to the devkey node data recovery from bxfs.
 *
 * @return  The result status of the devkey recovery_from_bxfs cmd.
 ****************************************************************************************
 */
err_t dm_devkey_recovery_from_bxfs(uint16_t idx,dev_key_t *p_handle)
{
    err_t err =  MESH_CORE_SUCCESS;

    if( NULL==p_handle )
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else if( idx >=DM_CFG_DEVKEY_MAX_NUM)
    {
        err =  MESH_CORE_ERROR_INVALID_PARAM;
    }
    else
    {
        dm_devkey_handle_t l_handle = array_buf_calloc_idx(&m_devkey_hdl,idx);

        if(NULL == l_handle)
        {
            err = MESH_CORE_ERROR_NO_MEM;
        }
        else
        {
            //TODO:  Add to dm system
            *l_handle = *p_handle;
        }
    }
    return err;
}

void dm_devkey_ack_reset(dm_netkey_handle_t netkey_handle)
{
    dm_netkey_pos_t pos;
    dm_devkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_devkey_hdl,l_handle,
         for(pos=0; pos < DEVKEY_BOUND_NETKEY_MAX_NUM; pos++)
         {
                 if(l_handle->bound_netkey.pool[pos] == netkey_handle)
                 {
                     l_handle->bound_netkey.update_ack[pos] = MESH_NO_ACK;
                 }
         }

    );

}


err_t dm_devkey_ack_set(dm_netkey_handle_t netkey_handle, uint16_t dev_addr)
{
    err_t err =  MESH_CORE_ERROR_NOT_FOUND;
    dm_devkey_pos_t pos;
    dm_devkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_devkey_hdl,l_handle,
         for(pos=0; pos < DEVKEY_BOUND_NETKEY_MAX_NUM; pos++)
         {
                 if(l_handle->bound_netkey.pool[pos] == netkey_handle && l_handle->addr == dev_addr)
                 {
                     l_handle->bound_netkey.update_ack[pos] = MESH_ACK;
                     return MESH_CORE_SUCCESS;
                 }
         }

    );
    return err;
}


bool dm_devkey_check_ack(dm_netkey_handle_t netkey_handle)
{
    dm_netkey_pos_t pos;
    dm_devkey_handle_t l_handle;
    FOR_EACH_ALLOCATED_ITEM(m_devkey_hdl,l_handle,
         for(pos=0; pos < DEVKEY_BOUND_NETKEY_MAX_NUM; pos++)
         {
                 if(l_handle->bound_netkey.pool[pos] == netkey_handle)
                 {
                     if(l_handle->bound_netkey.update_ack[pos] == MESH_NO_ACK)
                     {
                         return false;
                     }
                 }
         }

    );
    return true;
}

err_t  dm_devkey_getnext_dev(dm_netkey_handle_t p_netkey_handle, dm_devkey_handle_t* pp_devkey_handle)
{
    dm_devkey_handle_t l_handle;
    bool flag = false;
    dm_netkey_pos_t pos;
    if(*pp_devkey_handle == MESH_INVALID_DEVKEY_HANDLE)
    {
        flag = true;
    }
    FOR_EACH_ALLOCATED_ITEM(m_devkey_hdl,l_handle,
    {
         if(l_handle == *pp_devkey_handle)
         {
             flag = true;
             continue;
         }
         for(pos=0; pos < DEVKEY_BOUND_NETKEY_MAX_NUM; pos++)
         {
             if(l_handle->bound_netkey.pool[pos] == p_netkey_handle && flag)
             {
                   *pp_devkey_handle =l_handle;
                   return MESH_CORE_SUCCESS;
             }
         }
    }

    );
    return MESH_CORE_ERROR_NOT_FOUND;
}


err_t dm_devkey_addr_get( dm_devkey_handle_t p_devkey_handle, uint16_t * p_uni_addr)
{
    if(p_devkey_handle == MESH_INVALID_DEVKEY_HANDLE)
    {
        return MESH_CORE_ERROR_NOT_FOUND;
    }
    *p_uni_addr = p_devkey_handle->addr;
    return MESH_CORE_SUCCESS;
}


err_t dm_devkey_get_key(dm_devkey_handle_t p_devkey_handle, uint8_t ** pp_key)
{
    if ( (NULL == p_devkey_handle) || (NULL == pp_key) )
    {
        return MESH_CORE_ERROR_NULL;
    }
    *pp_key = p_devkey_handle->key;
    return MESH_CORE_SUCCESS;
}


err_t dm_devkey_get_key_by_addr(uint16_t own_addr,uint16_t peer_addr,uint8_t ** pp_key)
{
    dm_devkey_handle_t p_devkey_handle;
    err_t err;
    //get feature
    mesh_core_params_t param;
    mesh_core_params_get(MESH_CORE_PARAM_MESH_ROLES , &param);

    if (NULL == pp_key)
    {
        err =  MESH_CORE_ERROR_NULL;
    }
    else
    {
        if(MESH_ROLE_CONFIG_SERVER == param.role)//config server
        {
            err =  dm_devkey_uniaddr_to_handle_get(own_addr,&p_devkey_handle);
        }
        else//config client
        {
            err =  dm_devkey_uniaddr_to_handle_get(peer_addr,&p_devkey_handle);
        }

        if(err == MESH_CORE_SUCCESS)
        {
            err = dm_devkey_get_key(p_devkey_handle,pp_key);
        }
    }
    return err;
}


#endif /* OSAPP_MESH */
