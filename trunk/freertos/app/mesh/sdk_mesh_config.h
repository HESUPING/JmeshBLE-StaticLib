/**
 ****************************************************************************************
 *
 * @file sdk_mesh_config.h
 *
 * @brief Config BLE Mesh SDK Parameter.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_CORE_SDK_MESH_CONFIG_H_
#define FREERTOS_APP_MESH_CORE_SDK_MESH_CONFIG_H_

/**
 @defgroup MESH_API
 @{
 @}
 */
/**
 * @addtogroup MESH_SDK_CFG_API
 * @ingroup  MESH_API
 * @brief defines for BLE MESH  sdk config common params
 * @{
 * @}
 */
/**
 ****************************************************************************************
 * @addtogroup MESH_SDK_CFG_SIMPLE
 * @ingroup  MESH_SDK_CFG_API
 * @brief defines for BLE MESH  sdk config common params
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "sdk_mesh_config_pro.h"
#include "mesh_errors.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
/**
 * @brief mesh feature support status.
 */
typedef enum
{
    /// feature is support but disabled.
    MESH_FEATURE_DISABLED      =0,
    /// feature is support and enabled.
    MESH_FEATURE_ENABLED       =1,
    /// feature is not support.
    MESH_FEATURE_NOT_SUPPORT   =2,
} mesh_feature_stat_t;

/**
 * @brief mesh roles
 */
typedef enum
{
    /// node is config server.
    MESH_ROLE_CONFIG_SERVER,
    /// node is config client.
    MESH_ROLE_CONFIG_CLIENT,
}mesh_role_t;


/**
 * @brief mesh network transmit count and interval
 */
typedef struct
{
    /// the retransmit count of the message.
    uint8_t count:3;            //LSB
    /// the interval between two messages.(unit is 10ms)
    uint8_t interval_steps:5;   //MSB
}network_transmit_state_t;


/*
 * DEFINES
 ****************************************************************************************
 */
/**
 @defgroup MESH_ROLE_SELECTION select mesh roles
 @{
 @brief select mesh roles
*/
#define ENABLE_CONFIG_SERVER    /// config server role
#define ENABLE_CONFIG_CLIENT    /// config client role
/**
 @}MESH_ROLE_SELECTION
*/


/**
 @defgroup MESH_FEATURE_SUPPORT mesh feature support status
 @{
 @brief mesh feature support status
*/
#define MESH_SUPPORT_RELAY      MESH_FEATURE_DISABLED       /// support relay feature
#define MESH_SUPPORT_PROXY      MESH_FEATURE_ENABLED        /// support proxy feature
#define MESH_SUPPORT_FRIEND     MESH_FEATURE_NOT_SUPPORT    /// support friend feature
#define MESH_SUPPORT_LOW_POWER  MESH_FEATURE_NOT_SUPPORT    /// support low power feature
/**
 @}MESH_FEATURE_SUPPORT
*/





#endif /* FREERTOS_APP_MESH_CORE_SDK_MESH_CONFIG_H_ */
/// @} MESH_SDK_CFG_SIMPLE
