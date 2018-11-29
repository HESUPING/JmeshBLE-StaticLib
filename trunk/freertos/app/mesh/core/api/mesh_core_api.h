/****************************************************************************************
 *
 * @file mesh_core_api.h
 *
 * @brief mesh core api for user.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_CORE_API_MESH_CORE_API_H_
#define FREERTOS_APP_MESH_CORE_API_MESH_CORE_API_H_

/**
 ****************************************************************************************
 * @addtogroup MESH_CORE_API
 * @ingroup  MESH_API
 * @brief defines for BLE MESH CORE API
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
/*
 * ENUMERATIONS
 ****************************************************************************************
 */
/**
 * @brief enum mesh core param types
 */
typedef enum
{
    /// node roles.
    MESH_CORE_PARAM_MESH_ROLES,
    /// device is provisioned
    MESH_CORE_PARAM_IS_PROVISIONED,
    /// node is provisioner
    MESH_CORE_PARAM_IS_PROVISIONER,
    /// get device MAC address
    MESH_CORE_PARAM_MAC_ADDRESS,
    /// mesh node element pointer
    MESH_CORE_PARAM_ELEMENT_POINTER,
    /// mesh feature relay
    MESH_CORE_PARAM_FEATURE_RELAY,
    /// mesh feature proxy
    MESH_CORE_PARAM_FEATURE_PROXY,
    /// mesh feature friend
    MESH_CORE_PARAM_FEATURE_FRIENT,
    /// mesh feature low power
    MESH_CORE_PARAM_FEATURE_LOW_POWER,
    /// mesh property network transmit
    MESH_CORE_PARAM_PROPERTY_NETWORK_TRANSMIT,
    /// mesh property relay transmit
    MESH_CORE_PARAM_PROPERTY_RELAY_TRANSMIT,
} mesh_core_param_types_t;
/**
 * @brief enum mesh core system cmd types
 */
typedef enum
{
    /// the device will power down and restart.
    MESH_CORE_SYSTEM_HARD_RESTART,
    /// clear user data in flash and set the device power down to restart.
    MESH_CORE_SYSTEM_ALL_RESET,
} mesh_core_system_cmds_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */




/** Mesh core params union structure information. */
typedef union
{
  /// mesh role
  mesh_role_t role;
  /// device is provisioned
  bool is_provisioned;
  /// node is provisioner
  bool is_provisioner;
  /// MAC address pointer
  uint8_t * mac_address;
  /// mesh first element pointer
  mesh_elmt_t * mesh_element;
  /// mesh feature relay
  mesh_feature_stat_t relay;
  /// mesh feature proxy
  mesh_feature_stat_t proxy;
  /// mesh feature friend
  mesh_feature_stat_t friend;
  /// mesh feature low_power
  mesh_feature_stat_t low_power;
  /// mesh property network transmit
  network_transmit_state_t network_transmit;
  /// mesh property relay transmit
  network_transmit_state_t relay_transmit;
} mesh_core_params_t;
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
extern err_t mesh_core_params_get(mesh_core_param_types_t type,mesh_core_params_t * p_param);

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
extern err_t mesh_core_params_set(mesh_core_param_types_t type,const mesh_core_params_t * p_param);

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
extern err_t mesh_core_system_set(mesh_core_system_cmds_t cmd);

#endif /* FREERTOS_APP_MESH_CORE_API_MESH_CORE_API_H_ */
/// @} MESH_CORE_API

