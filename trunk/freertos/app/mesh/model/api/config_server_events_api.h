/*
 * mesh_model_api.h
 *
 *  Created on: 2018-9-10
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_MODEL_CONFIG_SERVER_EVENTS_API_H_
#define FREERTOS_APP_MESH_MODEL_CONFIG_SERVER_EVENTS_API_H_
/**
 ****************************************************************************************
 * @addtogroup MESH_MODEL_CONFIG_SERVER_EVENTS
 * @ingroup  MESH_MODEL_API
 * @brief defines for BLE MESH MODEL API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_model.h"
#include "mesh_env.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Configuration server event type. */
typedef enum
{
    /** A new application key was added. */
    CONFIG_SERVER_EVT_APPKEY_ADD,
    /** An existing application key was updated. */
    CONFIG_SERVER_EVT_APPKEY_UPDATE,
    /** The publication paremeters for a given model was set. */
    CONFIG_SERVER_EVT_MODEL_PUBLICATION_SET,
    /** The given application key was deleted. */
    CONFIG_SERVER_EVT_APPKEY_DELETE,
    /** Secure network beacon parameters was set. */
    CONFIG_SERVER_EVT_BEACON_SET,
    /** A new default TTL value was set. */
    CONFIG_SERVER_EVT_DEFAULT_TTL_SET,
    /** Friendship parameters was set (not supported). */
    CONFIG_SERVER_EVT_FRIEND_SET,
    /** GATT proxy parameters was set (not supported). */
    CONFIG_SERVER_EVT_GATT_PROXY_SET,
    /** Key refresh phase was set. */
    CONFIG_SERVER_EVT_KEY_REFRESH_PHASE_SET,
    /** Publication to a virtual address for a given model was set. */
    CONFIG_SERVER_EVT_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET,
    /** A subscription was added to the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_ADD,
    /** A subscription was deleted from the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_DELETE,
    /** All subscriptions was deleted for the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_DELETE_ALL,
    /** All subscriptions was overwritten by a new subscription for the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_OVERWRITE,
    /** A subscription to a virtual address was added to the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD,
    /** A subscription to a virtual address was removed from the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE,
    /** All subscriptions was overwritten by a new subscription to a virtual address for the given model. */
    CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE,
    /** Core network transmission parameters was set. */
    CONFIG_SERVER_EVT_NETWORK_TRANSMIT_SET,
    /** Core relay parameters was set. */
    CONFIG_SERVER_EVT_RELAY_SET,
    /** Low power node poll timeout was set (not supported). */
    CONFIG_SERVER_EVT_LOW_POWER_NODE_POLLTIMEOUT_SET,
    /** Heartbeat publication parameters was set. */
    CONFIG_SERVER_EVT_HEARTBEAT_PUBLICATION_SET,
    /** Heartbeat subscription parameters was set. */
    CONFIG_SERVER_EVT_HEARTBEAT_SUBSCRIPTION_SET,
    /** The given model was bound to a new application key. */
    CONFIG_SERVER_EVT_MODEL_APP_BIND,
    /** The given model was unbound from an application key. */
    CONFIG_SERVER_EVT_MODEL_APP_UNBIND,
    /** A new network key was added. */
    CONFIG_SERVER_EVT_NETKEY_ADD,
    /** A network key was deleted. */
    CONFIG_SERVER_EVT_NETKEY_DELETE,
    /** A network key was updated. */
    CONFIG_SERVER_EVT_NETKEY_UPDATE,
    /** The Node Identity was set (not supported). */
    CONFIG_SERVER_EVT_NODE_IDENTITY_SET,
    /** The node was reset, i.e., all mesh state cleared. */
    CONFIG_SERVER_EVT_NODE_RESET,
}config_server_evt_type_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/** Configuration server event structure. */
typedef struct
{
    /** Type of event. */
    config_server_evt_type_t type;
    /** event parameters element. */
    mesh_elmt_t     *elmt;
    /** event parameters model. */
    model_base_t    *model;
    /** event parameters contents. */
    access_pdu_rx_t *pdu;
} config_server_evt_t;

/**
 * @brief     Config server event callback type.
 * @param[in] p_evt Event pointer from the configuration server.
 */
typedef void (*config_server_evt_cb_t)(const config_server_evt_t * p_evt);


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 * @brief     set config server event callback function.
 * @param[in] cb callback of config server.
 */
void regisite_config_server_evt_cb(config_server_evt_cb_t cb);



/// @} MESH_MODEL_CONFIG_SERVER_EVENTS
#endif /* FREERTOS_APP_MESH_MODEL_CONFIG_SERVER_EVENTS_API_H_ */
