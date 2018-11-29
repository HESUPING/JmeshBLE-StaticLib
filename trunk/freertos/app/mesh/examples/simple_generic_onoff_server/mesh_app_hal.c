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
#include "mesh_core_api.h"
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
 
TimerHandle_t gal_heartbeat_Timer;

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

void hal_set_heartbeat_led(uint8_t on_off)
{

    if(on_off == 1)
    {
        //data set  io on
        io_pin_set(HEARTBEAT_PIN_NUM_MINI);
    }
    else
    {
        //data set  io off
        io_pin_clear(HEARTBEAT_PIN_NUM_MINI);
    }
}


void hal_init_leds(void)
{
    //1. io dir
    io_cfg_output(LED1_PIN_NUM);
    io_cfg_output(LED2_PIN_NUM);
    io_cfg_output(LED1_PIN_NUM_MINI);
    io_cfg_output(LED2_PIN_NUM_MINI);

    io_cfg_output(BX_DONGLE_LED1_G);//relay state
    //2. set output
    io_pin_clear(LED1_PIN_NUM);
    io_pin_clear(LED2_PIN_NUM);
    io_pin_clear(LED1_PIN_NUM_MINI);
    io_pin_clear(LED2_PIN_NUM_MINI);

    io_pin_set(BX_DONGLE_LED1_G);//relay state
}

void hal_init_heartbeat_led(void)
{
    io_cfg_output(HEARTBEAT_PIN_NUM_MINI);
    io_pin_clear(HEARTBEAT_PIN_NUM_MINI);
}


// button
void hal_button3_cb(void)
{
    mesh_core_params_t core_param;

    core_param.relay = MESH_FEATURE_DISABLED;
    mesh_core_params_set(MESH_CORE_PARAM_FEATURE_RELAY,&core_param);
    io_pin_set(BX_DONGLE_LED1_G);//relay state  disable

    LOG(LOG_LVL_INFO,"hal_button3_cb\n");
}
void hal_button4_cb(void)
{
   mesh_core_params_t core_param;

   core_param.relay = MESH_FEATURE_ENABLED;
   mesh_core_params_set(MESH_CORE_PARAM_FEATURE_RELAY,&core_param);
   io_pin_clear(BX_DONGLE_LED1_G);//relay state  enable

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

static void heartbeatTimeoutCallback(TimerHandle_t xTimer)
{
    static uint8_t on_off = 1;
    hal_set_heartbeat_led(on_off);
    on_off = 1 - on_off;
}


void hal_timer_init(void)
{
     gal_heartbeat_Timer = xTimerCreate("gal_heartbeat_Timer",pdMS_TO_TICKS(HEARTBEAT_BLINKY_TICK),pdTRUE,(void *)0,heartbeatTimeoutCallback);
     if(gal_heartbeat_Timer != NULL)
     {
         xTimerStart(gal_heartbeat_Timer,0);
     }
}

void hal_heartbeat_init(void)
{
    hal_init_heartbeat_led();
    hal_timer_init();
}



#endif /* OSAPP_MESH */
