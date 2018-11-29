/**
 ****************************************************************************************
 *
 * @file mesh_gatt_api.h
 *
 * @brief mesh gatt api for user.
 *
 * Copyright (C) BlueX Microelectronics 2018-2023
 *
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_GATT_API_MESH_GATT_API_H_
#define FREERTOS_APP_MESH_GATT_API_MESH_GATT_API_H_
/**
 ****************************************************************************************
 * @addtogroup MESH_GATT_API
 * @ingroup  MESH_API
 * @brief defines for BLE MESH API
 *
 * @{
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
/**@brief mesh gatt event type enum */
typedef enum
{
    MESH_GATT_EVT_DISCONNECT,
    MESH_GATT_EVT_CONNECT,
} mesh_gatt_evt_api_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/**@brief mesh gatt event type's parameters structure */
typedef struct
{
    uint16_t conn_index;/// connect index.
} mesh_gatt_evt_api_param_t;

/**
 ****************************************************************************************
 * @brief Callback function type for Mesh gatt event for user api callback.
 *
 * @param[in] evt       The gatt event type.
 * @param[in] p_param   Pointer to the param of the event.
 *
 ****************************************************************************************
 */
typedef void (*mesh_gatt_evt_api_cb_t)(mesh_gatt_evt_api_t evt,mesh_gatt_evt_api_param_t *p_param);

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Register Callback function type for Mesh gatt event for user api callback.
 *
 * @param[in] p_cb   Pointer to the mesh_gatt_evt_api_cb func.
 *
 ****************************************************************************************
 */
extern void ble_mesh_gatt_evt_register(mesh_gatt_evt_api_cb_t p_cb);


/// @} MESH_GATT_API
#endif /* FREERTOS_APP_MESH_GATT_API_MESH_GATT_API_H_ */
