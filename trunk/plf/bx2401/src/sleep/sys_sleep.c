/**
 ****************************************************************************************
 *
 * @file sys_sleep.c
 *
 * @brief Implementation of sys_sleep.c. Sleep and wakeup process of Bx2400
 *
 * Copyright (C) bluexmicro electronics 2015-2016 by zhaoweiqi
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup SYS_SLEEP
  * @ingroup SLEEP
 * @{
 ****************************************************************************************
 */
#include "bx2400.h"
#include "sys_sleep.h"
#include "bx_dbg.h"
#include "rwip.h"
blemac_stat_t mac_status = active_clk;




void ble_lp_intr_clr()
{

}

void ble_lp_irq_enable()
{

}

void ble_lp_irq_disable()
{

}


/**
 * @brief do ble task.
 */
void ble_schedule()
{
    if(mac_status==active_clk)
    {
        // schedule all pending events
        rwip_schedule();
    }
}

/**
 * @brief get sleep type. Sometimes we should not power off(just WFI), sometimes we can go deep sleep. It depends, so we should get the sleep type and do different process
 * @return return a struct of sleep type.
 */
uint8_t sleep_prepare_and_check()
{

}

void ble_soft_wakeup_if_sleep_mp()
{

}

void ble_lp_isr_mp()
{

}

void BLE_LP_IRQHandler(void)
{
    ble_lp_isr_mp();
}


