/****************************************************************************************
 *
 * @file mesh_core_api.c
 *
 * @brief mesh core api for user.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH

#include "mesh_core_api.h"
#include "arch.h"
#include "node_save.h"
#include "nvds_in_ram.h"
#include "mesh_tools.h"
/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/**
 * @brief mesh node properties
 */
typedef struct
{
    /// normal network layer transmit
    network_transmit_state_t network_transmit;
    /// network layer retransmit
    network_transmit_state_t relay_transmit;
} mesh_properties_t;

/**
 * @brief mesh node features
 */
typedef struct
{
    /// relay feature status
    mesh_feature_stat_t relay;
    /// proxy feature status
    mesh_feature_stat_t proxy;
    /// friend feature status
    mesh_feature_stat_t friend;
    /// low_power feature status
    mesh_feature_stat_t low_power;
}mesh_features_t;

/**
 * @brief mesh node structure
 */
typedef struct
{
    /// the element pointer of the node
    mesh_elmt_t *elmt;
    /// mesh node features
    mesh_features_t feature;
    /// mesh node properties
    mesh_properties_t properties;
    /// mesh role
    mesh_role_t role;
    /// device is provisioned
    bool is_provisioned;
    /// node is provisioner
    bool is_provisioner;
}mesh_node_t;
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * MACROS
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
static mesh_node_t mesh_node;

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief The mesh core params get.
 *
 * @param[in] type       The mesh core params type which to be get.
 * @param[out] p_param   Pointer to the param data.
 *
 * @return err  the set status  @ref MESH_CORE_ERRORS.
 *
 ****************************************************************************************
 */
err_t mesh_core_params_get(mesh_core_param_types_t type,mesh_core_params_t * p_param)
{
    err_t err = MESH_CORE_SUCCESS;

    if(p_param)
    {
        switch(type)
        {
            case MESH_CORE_PARAM_MESH_ROLES:
                p_param->role = mesh_node.role;
                break;
            case MESH_CORE_PARAM_IS_PROVISIONED :
                p_param->is_provisioned = mesh_node.is_provisioned;
                break;
            case MESH_CORE_PARAM_IS_PROVISIONER:
                p_param->is_provisioner = mesh_node.is_provisioner;
                break;
            case MESH_CORE_PARAM_MAC_ADDRESS:
                tools_gap_public_bd_addr_get(p_param->mac_address);
                break;
            case MESH_CORE_PARAM_ELEMENT_POINTER:
                p_param->mesh_element = mesh_node.elmt;
                break;
            case MESH_CORE_PARAM_FEATURE_RELAY:
                p_param->relay = mesh_node.feature.relay;
                break;
            case MESH_CORE_PARAM_FEATURE_PROXY:
                p_param->proxy = mesh_node.feature.proxy;
                break;
            case MESH_CORE_PARAM_FEATURE_FRIENT:
                p_param->friend = mesh_node.feature.friend;
                break;
            case MESH_CORE_PARAM_FEATURE_LOW_POWER:
                p_param->low_power = mesh_node.feature.low_power;
                break;
            case MESH_CORE_PARAM_PROPERTY_NETWORK_TRANSMIT:
                p_param->network_transmit = mesh_node.properties.network_transmit;
                break;
            case MESH_CORE_PARAM_PROPERTY_RELAY_TRANSMIT:
                p_param->relay_transmit = mesh_node.properties.relay_transmit;
                break;
            default:
                err = MESH_CORE_ERROR_NOT_FOUND;
                break;
        }
    }
    else
    {
        err = MESH_CORE_ERROR_NULL;
    }

    return err;
}
/**
 ****************************************************************************************
 * @brief The mesh core params set.
 *
 * @param[in] type      The mesh core params type which to be set.
 * @param[in] p_param   Pointer to the param data.
 *
 * @return err  the set status  @ref MESH_CORE_ERRORS.
 *
 ****************************************************************************************
 */
err_t mesh_core_params_set(mesh_core_param_types_t type,const mesh_core_params_t * p_param)
{
    err_t err = MESH_CORE_SUCCESS;

    if(p_param)
    {
        switch(type)
        {
            case MESH_CORE_PARAM_MESH_ROLES:
                mesh_node.role = p_param->role;
                break;
            case MESH_CORE_PARAM_IS_PROVISIONED :
                mesh_node.is_provisioned = p_param->is_provisioned;
                break;
            case MESH_CORE_PARAM_IS_PROVISIONER:
                mesh_node.is_provisioner = p_param->is_provisioner;
                break;
            case MESH_CORE_PARAM_MAC_ADDRESS:
                //BLOCKED
                //nvds_put(NVDS_TAG_BD_ADDRESS, NVDS_LEN_BD_ADDRESS, p_param->mac_address);
                break;
            case MESH_CORE_PARAM_ELEMENT_POINTER:
                mesh_node.elmt = p_param->mesh_element;
                break;
            case MESH_CORE_PARAM_FEATURE_RELAY:
                mesh_node.feature.relay = p_param->relay;
                break;
            case MESH_CORE_PARAM_FEATURE_PROXY:
                mesh_node.feature.proxy = p_param->proxy;
                break;
            case MESH_CORE_PARAM_FEATURE_FRIENT:
                mesh_node.feature.friend = p_param->friend;
                break;
            case MESH_CORE_PARAM_FEATURE_LOW_POWER:
                mesh_node.feature.low_power = p_param->low_power;
                break;
            case MESH_CORE_PARAM_PROPERTY_NETWORK_TRANSMIT:
                mesh_node.properties.network_transmit = p_param->network_transmit;
                break;
            case MESH_CORE_PARAM_PROPERTY_RELAY_TRANSMIT:
                mesh_node.properties.relay_transmit = p_param->relay_transmit;
                break;
            default:
                err = MESH_CORE_ERROR_NOT_FOUND;
                break;
        }
    }
    else
    {
        err = MESH_CORE_ERROR_NULL;
    }

    return err;
}
/**
 ****************************************************************************************
 * @brief The mesh core system set.
 *
 * @param[in] cmd      The mesh core system cmd which to be set.
 *
 * @return err  the set status  @ref MESH_CORE_ERRORS.
 *
 ****************************************************************************************
 */
err_t mesh_core_system_set(mesh_core_system_cmds_t cmd)
{
    err_t err = MESH_CORE_SUCCESS;

    switch(cmd)
    {
        case MESH_CORE_SYSTEM_HARD_RESTART :
            platform_reset(0);
            break;
        case MESH_CORE_SYSTEM_ALL_RESET :
            //1. clear mesh data in flash
            node_save_mesh_reset();
            //2. restart
            platform_reset(0);
            break;
        default:
            err = MESH_CORE_ERROR_NOT_FOUND;
            break;
    }

    return err;
}

#endif /* OSAPP_MESH */


