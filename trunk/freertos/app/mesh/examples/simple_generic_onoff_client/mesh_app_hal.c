/**
 ****************************************************************************************
 *
 * @file   mesh_app_hal.c
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH

#include "mesh_app_hal.h"
#include "io_ctrl.h"
#include "plf.h"
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
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

void hal_set_led1(uint8_t on_off)
{
    if(on_off == 1)
    {
        //data set  io on
        io_pin_clear(LED1_PIN_NUM);
        io_pin_clear(LED1_PIN_NUM_MINI);
    }
    else
    {
        //data set  io off
        io_pin_set(LED1_PIN_NUM);
        io_pin_set(LED1_PIN_NUM_MINI);
    }
}

void hal_set_led2(uint8_t on_off)
{

//    clk_gate_per_g1(PER_CLKG_SET_GPIO);

    if(on_off == 1)
    {
        //data set  io on
        io_pin_clear(LED2_PIN_NUM);
        io_pin_clear(LED2_PIN_NUM_MINI);
    }
    else
    {
        //data set  io off
        io_pin_set(LED2_PIN_NUM);
        io_pin_set(LED2_PIN_NUM_MINI);
    }
}

void hal_init_leds(void)
{
    //1. io dir
    io_cfg_output(LED1_PIN_NUM);
    io_cfg_output(LED2_PIN_NUM);
    io_cfg_output(LED1_PIN_NUM_MINI);
    io_cfg_output(LED2_PIN_NUM_MINI);
    //2. set output
    io_pin_set(LED1_PIN_NUM);
    io_pin_set(LED2_PIN_NUM);
    io_pin_set(LED1_PIN_NUM_MINI);
    io_pin_set(LED2_PIN_NUM_MINI);
}


// button
void hal_button3_cb(void)
{
   io_pin_toggle(LED1_PIN_NUM);
   io_pin_toggle(LED1_PIN_NUM_MINI);

   LOG(LOG_LVL_INFO,"hal_button3_cb\n");
}
void hal_button4_cb(void)
{
   io_pin_toggle(LED2_PIN_NUM);
   io_pin_toggle(LED2_PIN_NUM_MINI);

   LOG(LOG_LVL_INFO,"hal_button4_cb\n");
}
void hal_init_buttons(void)
{
    //1. io dir
    io_cfg_input(BTN3_PIN_NUM);
    io_cfg_input(BTN4_PIN_NUM);
    //2. pull
    io_pin_pull_write(BTN3_PIN_NUM,IO_PULL_UP);
    io_pin_pull_write(BTN4_PIN_NUM,IO_PULL_UP);
    //3. int cfg
    io_ext_int_cfg(BTN3_PIN_NUM,EXT_INT_TRIGGER_NEG_EDGE,hal_button3_cb);
    io_ext_int_cfg(BTN4_PIN_NUM,EXT_INT_TRIGGER_NEG_EDGE,hal_button4_cb);
    //4. en
    io_ext_int_en(BTN3_PIN_NUM,true);
    io_ext_int_en(BTN4_PIN_NUM,true);
}

#endif /* OSAPP_MESH */
