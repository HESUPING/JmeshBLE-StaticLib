/**
 ****************************************************************************************
 *
 * @file   sdk_mesh_definitions.h
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-15 15:02
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
 * @addtogroup MESH_SDK_DEFINES Mesh SDK data struck and define definitions
 * @ingroup MESH_API
 * @brief Mesh SDK data struck and define definitions
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_CORE_SDK_MESH_DEFINITIONS_H_
#define FREERTOS_APP_MESH_CORE_SDK_MESH_DEFINITIONS_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_model.h"
#include "mesh_definitions.h"
/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

///*
// * ENUMERATIONS
// ****************************************************************************************
// */
///** RX data From type. */
//typedef enum
//{
//    MESH_RX_FROM_GATT,    /**< The data came from a GATT connection. */
//    MESH_RX_FROM_SCANNER, /**< The data came from the scanner. */
//    MESH_RX_FROM_FRIEND,  /**< The data came from a friend node. */
//    MESH_RX_FROM_LOW_POWER,  /**< The data came from a low power node. */
//    MESH_RX_FROM_LOOPBACK,  /**< The data came from this device. */
//    MESH_RX_FROM_DECRYPT,  /**< The data came from inter decrypt. */
//    MESH_RX_FROM_INVALID  /**< The data came from invalid error. */
//} mesh_rx_from_t;
//
///** TX data From type. */
//typedef enum
//{
//    MESH_TX_FROM_GATT,    /**< The data came from a GATT connection. */
//    MESH_TX_FROM_SCANNER, /**< The data came from the scanner. */
//    MESH_TX_FROM_FRIEND,  /**< The data came from a friend node. */
//    MESH_TX_FROM_LOW_POWER,  /**< The data came from a low power node. */
//    MESH_TX_FROM_LOOPBACK,  /**< The data came from this device. */
//    MESH_TX_FROM_RELAY,  /**< The data came from relay. */
//    MESH_TX_FROM_ENCRYPT,  /**< The data came from inter encrypt. */
//    MESH_TX_FROM_INVALID  /**< The data came from invalid error. */
//} mesh_tx_from_t;
//
///*
// * TYPE DEFINITIONS
// ****************************************************************************************
// */
///**
// * @brief Callback function type for Mesh network pdu decrypt.
// *
// * @param[in] p_pdu       Pointer to the network pdu database.
// * @param[in] length      The length of the decrypt data.
// * @param[in] conn_index  gatt connect index.
// *
// */
//typedef void (*network_pdu_decrypt_cb_t)(const void *p_pdu,uint16_t length,uint16_t conn_index);
//
///** Mesh GATT Network packet structure. */
//typedef struct
//{
//    uint16_t connection_index; /**< Proxy connection index the packet was received from. */
//} mesh_gatt_network_rx_t;
//
///** Mesh Scanner Network packet structure. */
//typedef struct
//{
//    int8_t rssi; /**< RSSI value of the received packet. */
//} mesh_scanner_network_rx_t;
//
///** Mesh decrypt Network packet structure. */
//typedef struct
//{
//    uint16_t conn_index;
//} mesh_decrypt_network_rx_t;
//
///** Mesh encrypt Network packet structure. */
//typedef struct
//{
//    uint16_t conn_index;
//} mesh_encrypt_network_tx_t;
//
///** RX From type params. */
//typedef struct
//{
//    mesh_rx_from_t rx_from; /**< Source of the received data. */
//    union
//    {
//        /** GATT packet metadata */
//        mesh_gatt_network_rx_t gatt;
//        mesh_scanner_network_rx_t scanner;
//        mesh_decrypt_network_rx_t decrypt;
//    } params;
//} mesh_rx_params_t;
//
///** TX From type params. */
//typedef struct
//{
//    mesh_tx_from_t  tx_from; /**< Source of the received data. */
//    union
//    {
//        /** GATT packet metadata */
//        mesh_encrypt_network_tx_t encrypt;
//    } params;
//} mesh_tx_params_t;
///*
// * GLOBAL VARIABLE DECLARATIONS
// ****************************************************************************************
// */
//
//
///*
// * FUNCTION DECLARATIONS
// ****************************************************************************************
// */
//


#endif /* FREERTOS_APP_MESH_CORE_SDK_MESH_DEFINITIONS_H_ */ 
/// @} MESH_SDK_DEFINES

