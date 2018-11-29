/**
 ****************************************************************************************
 *
 * @file provision_api.h
 *
 * @brief mesh provision api for user.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_PROVISION_API_PROVISION_API_H_
#define FREERTOS_APP_MESH_PROVISION_API_PROVISION_API_H_

/**
 ****************************************************************************************
 * @addtogroup MESH_PROVISION_API
 * @ingroup  MESH_API
 * @brief defines for BLE MESH PROVISION API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_errors.h"
#include "sdk_mesh_config.h"
#include "sdk_mesh_definitions.h"

#include "stdint.h"
#include "provision_base.h"
/*
 * ENUMERATIONS
 ****************************************************************************************
 */
typedef enum
{
    MESH_ROLE_PROVISIONER,
    MESH_ROLE_UNPROV_DEVICE,
}mesh_provsion_role_t;

/*Method of configuring network access*/
typedef enum
{
    PROVISION_BY_GATT,
    PROVISION_BY_ADV,
    PROVISION_BY_ADV_GATT,
}mesh_provsion_method_t;

//协议->用户
typedef enum
{
    /*******PROVISIONER*******/
    PROV_EVT_BEACON,
    PROV_EVT_CAPABILITIES,
    PROV_EVT_READ_PEER_PUBLIC_KEY_OOB,
    PROV_EVT_AUTH_DISPLAY_NUMBER,//provisioner expose random number (NO ACTION)
    PROV_EVT_AUTH_INPUT_NUMBER,   //alert input dialog
    PROV_EVT_PROVISION_DONE,    //(NO ACTION)

    /*******UNPROV DEVICE*******/
    UNPROV_EVT_INVITE_MAKE_ATTENTION,//(NO ACTION)
    UNPROV_EVT_EXPOSE_PUBLIC_KEY, //(NO ACTION)
    UNPROV_EVT_AUTH_INPUT_NUMBER,//alert input dialog
    UNPROV_EVT_AUTH_DISPLAY_NUMBER,//unprov_device expose random number //(NO ACTION)
    UNPROV_EVT_PROVISION_DONE, //(NO ACTION)
} mesh_prov_evt_type_t;

//用户->协议栈（回复）
typedef enum
{
    /*******PROVISIONER*******/
    //PROV_EVT_AUTH_INPUT_NUMBER
    PROV_ACTION_AUTH_INPUT_NUMBER_DONE,//input random number done
    //PROV_EVT_READ_PEER_PUBLIC_KEY_OOB
    PROV_ACTION_READ_PEER_PUBLIC_KEY_OOB_DONE,
    //PROV_EVT_BEACON
    PROV_ACTION_SET_LINK_OPEN,
    //PROV_EVT_CAPABILITIES
    PROV_ACTION_SEND_START_PDU,

    /*******UNPROV DEVICE*******/
    //UNPROV_EVT_AUTH_INPUT_NUMBER
    UNPROV_ACTION_AUTH_INPUT_NUMBER_DONE,//input random number done
} mesh_prov_action_type_t;

//用户->协议栈
typedef enum
{
    /*******PROVISIONER*******/
    PROV_SET_PRIVATE_KEY,
    PROV_SET_AUTH_STATIC,
    PROV_SET_DISTRIBUTION_DATA,
    PROV_SET_INVITE_DURATION,
    PROV_RESET,
    PROV_CLEAR_CACHE,

    /*******UNPROV DEVICE*******/
    UNPROV_SET_BEACON,
    UNPROV_SET_PRIVATE_KEY,
    UNPROV_SET_OOB_CAPS,
    UNPROV_SET_AUTH_STATIC,
    UNPROV_SET_PROVISION_METHOD,
    UNPROV_RESET,
} mesh_prov_config_type_t;
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    uint8_t dev_uuid[MESH_DEVICE_UUID_LENGTH];
    uint32_t uri_hash;
    uint16_t oob_info;
}mesh_beacon_t;

typedef struct
{
    uint8_t reason;
    uint8_t success;
}provisioning_done_state_t;

typedef union
{
   uint8_t a;
}provision_param_prov_t;

typedef union
{
   mesh_provsion_method_t method;
   uint8_t attention_duration;
   provision_capabilities_t *p_dev_capabilities;
   mesh_beacon_t *p_beacon;
   uint8_t *p_unprov_private_key;
   public_key_t *p_public_keys;
   uint8_t *p_input_val;
   uint8_t *p_output_val;
   uint8_t *p_static_val;
   provisioning_done_state_t done_state;
}provision_param_unprov_t;

typedef union
{
   provision_param_prov_t   prov;
   provision_param_unprov_t unprov;
} mesh_prov_evt_param_t;

typedef void (*mesh_prov_evt_cb_t)(mesh_prov_evt_type_t type,mesh_prov_evt_param_t param);

/* user data*/
typedef struct
{
    uint8_t unprov_private_key[GAP_P256_KEY_LEN];
    uint8_t static_value[AUTHVALUE_LEN];
    provision_capabilities_t dev_capabilities;
    mesh_beacon_t beacon;
    mesh_provsion_method_t method;
}unprov_user_data_t;


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief   Init provision role and callback handle register.
 *
 * @param[in] role     provision role.
 * @param[in] handle   callback handle pointer.
 *
 ****************************************************************************************
 */
extern void provision_init(mesh_provsion_role_t role , mesh_prov_evt_cb_t handle);

/**
 ****************************************************************************************
 * @brief   Send action to mesh stack.
 *
 * @param[in] type     The type of the action message.
 * @param[in] param    The parameter of the action message.
 *
 ****************************************************************************************
 */
extern void provision_action_send (mesh_prov_action_type_t type , mesh_prov_evt_param_t param);

/**
 ****************************************************************************************
 * @brief   Configure parameter to mesh stack.
 *
 * @param[in] type     The opcode of the configure parameter message.
 * @param[in] param    The parameter of the configuration message.
 *
 ****************************************************************************************
 */
extern void provision_config (mesh_prov_config_type_t opcode , mesh_prov_evt_param_t param);

/// @} MESH_PROVISION_API

#endif /* FREERTOS_APP_MESH_PROVISION_API_PROVISION_API_H_ */
