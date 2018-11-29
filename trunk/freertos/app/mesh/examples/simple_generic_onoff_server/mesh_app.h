/**
 ****************************************************************************************
 *
 * @file   mesh_app.h
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-25 17:20
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
 * @addtogroup MESH_mesh_app_API Mesh mesh_app API
 * @ingroup MESH_API
 * @brief Mesh mesh_app  API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_EXAMPLES_SIMPLE_GENERIC_ONFF_SERVER_MESH_APP_H_
#define FREERTOS_APP_MESH_EXAMPLES_SIMPLE_GENERIC_ONFF_SERVER_MESH_APP_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

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
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
//TODO:THIS IS ONLY USED　FIX WARNINGS !!
void user_onoff_client_set(void *msg , uint8_t msg_length,uint16_t dst_addr,uint8_t need_ack);
void mesh_app_server_init(void);
//init user models
void mesh_app_init_user(void);



#endif /* FREERTOS_APP_MESH_EXAMPLES_SIMPLE_GENERIC_ONFF_SERVER_MESH_APP_H_ */ 
/// @} MESH_mesh_app_API

