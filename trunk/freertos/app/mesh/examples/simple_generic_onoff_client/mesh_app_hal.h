/**
 ****************************************************************************************
 *
 * @file   mesh_app_hal.h
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-25 17:29
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
 * @addtogroup MESH_mesh_app_hal_API Mesh mesh_app_hal API
 * @ingroup MESH_API
 * @brief Mesh mesh_app_hal  API
 *
 * @{
 ****************************************************************************************
 */

#ifndef FREERTOS_APP_MESH_EXAMPLES_SIMPLE_GENERIC_ONFF_SERVER_MESH_APP_HAL_H_
#define FREERTOS_APP_MESH_EXAMPLES_SIMPLE_GENERIC_ONFF_SERVER_MESH_APP_HAL_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_errors.h"
#include "sdk_mesh_config.h"
#include "sdk_mesh_definitions.h"

/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
/* bluex dongle board pin num */
//led
#define BX_DONGLE_LED1_R    4
#define BX_DONGLE_LED1_G    2
#define BX_DONGLE_LED1_B    3
#define BX_DONGLE_LED2_R    22
#define BX_DONGLE_LED2_G    20
#define BX_DONGLE_LED2_B    21
//button
#define BX_DONGLE_BTN3      15
#define BX_DONGLE_BTN4      17

/*demo use */
#define LED1_PIN_NUM        8
#define LED2_PIN_NUM        9
#define LED1_PIN_NUM_MINI   BX_DONGLE_LED1_B
#define LED2_PIN_NUM_MINI   BX_DONGLE_LED2_R

#define BTN3_PIN_NUM        BX_DONGLE_BTN3
#define BTN4_PIN_NUM        BX_DONGLE_BTN4
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
void hal_set_led1(uint8_t on_off);
void hal_set_led2(uint8_t on_off);
void hal_init_leds(void);
void hal_init_buttons(void);


#endif /* FREERTOS_APP_MESH_EXAMPLES_SIMPLE_GENERIC_ONFF_SERVER_MESH_APP_HAL_H_ */ 
/// @} MESH_mesh_app_hal_API

