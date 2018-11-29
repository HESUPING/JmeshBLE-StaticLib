/**
 ****************************************************************************************
 *
 * @file   mesh_stack_init.h
 *
 * @brief  .
 *
 * @author  jiachuang
 * @date    2018-09-18 17:25
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
 * @addtogroup MESH_mesh_stack_init_API Mesh mesh_stack_init API
 * @ingroup MESH_API
 * @brief Mesh mesh_stack_init  API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_MESH_STACK_INIT_H_
#define FREERTOS_APP_MESH_MESH_STACK_INIT_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "sdk_mesh_config.h"
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
    MESH_INIT_START,                                ///< 00.start of init
    MESH_INIT_IV_BEACON_KEYREFRESH,                 ///< 01.mesh_iv_init、mesh_sec_beacon_init、mesh_kr_client_init
    MESH_INIT_UPPPER,                               ///< 02.upper_transport_init
    MESH_INIT_SECURITY,                             ///< 03.security_init
    MESH_INIT_NODE_SYSTEM,                          ///< 04.system init node-element-model tree
    MESH_INIT_NODE_USER,                            ///< 05.user node-element-model tree init
    MESH_INIT_NODE_CONFIG,                          ///< 06.init node feature property
    MESH_INIT_NODE_RECOVER,                         ///< 07.bxfs_init,make_dir,recover
    MESH_INIT_AFTER_NODE_RECOVER_ADD_SVC,           ///< 08.node recover add GATT services
#ifdef MESH_TEST_UART_CTRL
    MESH_INIT_TEST_CONFIG,                          ///< 09.UART test init
#endif /* def MESH_TEST_UART_CTRL */
    MESH_INIT_START_SCAN,                           ///< 10.mesh start scan
    MESH_INIT_USER,                                 ///< 11.user init function
    MESH_INIT_COMPLETE,                             ///< 12.init complete
}mesh_init_process_t;

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

/**
 ****************************************************************************************
 * @brief   Start mesh stack init process
 * @return  void
 ****************************************************************************************
 */
void mesh_stack_init_process(void);


#endif /* FREERTOS_APP_MESH_MESH_STACK_INIT_H_ */ 
/// @} MESH_mesh_stack_init_API

