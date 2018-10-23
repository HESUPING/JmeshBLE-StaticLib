#include <stdint.h>
#include "reg_rtc.h"
extern uint32_t flash_dual_quad;
static uint32_t io_retention_val;
static uint32_t io_retention_dir;

#ifdef DO_NOT_WAKEUP
static void do_not_wakeup()
{
    rtc_countermatch_setf(0xffffffff);
    NVIC_DisableIRQ(BLE_LP_IRQn);
    uint32_t i;
    for(i = 0 ;i<2000; ++i) __NOP();
}
#endif

uint32_t get_real_rtc()
{
    uint32_t last = rtc_currentcountervalue_getf();
    uint32_t current;
    do
    {
        current = rtc_currentcountervalue_getf();
    }
    while(last == current);
    return current;
}

static void sync_with_ble_sleep()
{

}

void wait_rtc_until(uint32_t target)
{

}

static void switch_to_32m_rc(uint32_t current_time)
{

}

static void close_32m_xtal()
{

}

static void deep_sleep_io_state_set()
{

}

static void deepsleep_prepare()
{

}

void pre_deepsleep_processing_mp()
{

}

static uint32_t config_and_enable_32m_xtal()
{

}

static void gpio_status_restore()
{

}

void flash_recovery()
{

}

void post_deepsleep_processing_mp()
{

}

