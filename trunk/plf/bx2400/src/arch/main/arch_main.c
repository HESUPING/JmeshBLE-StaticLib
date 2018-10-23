/**
 ****************************************************************************************
 *
 * @file arch_main.c
 *
 * @brief Main loop of the application.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */


/*
 * INCLUDES
 ****************************************************************************************
 */
#define __RAM_CODE__
#include "arch.h"      // architectural platform definitions
#include <stdlib.h>    // standard lib functions
#include <stddef.h>    // standard definitions
#include <stdint.h>    // standard integer definition
#include <stdbool.h>   // boolean definition
#include <string.h>
#include "plf.h"
#include "rwip.h"      // RW SW initialization
//#include "intc.h"      // Interrupt initialization
#include "sys_sleep.h"
#include "awo.h"
#include "modem.h"
#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
#include "rf.h"        // RF initialization
#endif // BLE_EMB_PRESENT || BT_EMB_PRESENT
#include "boot.h"
#if (BLE_APP_PRESENT)
#include "app.h"       // application functions
#endif // BLE_APP_PRESENT
#if (PLF_NVDS)
#include "nvds.h"
#endif
#if (PLF_DEBUG)
#include "dbg.h"       // For dbg_warning function
#endif //PLF_DEBUG
#include "log.h"
#include "bx_dbg.h"
#ifdef CFG_FREERTOS_SUPPORT
#include "task_init.h"
#include "os_bridge.h"
#endif
#include "pshare.h"
#include "em_map.h"
#include "rc_calib.h"
//#include "flash.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_cpu.h"
#include "reg_sysc_per.h"
//#include "clk_gen.h"
#include "clk_gate.h"
#include "rst_gen.h"
//#include "test_header.h"
#include "patch.h"
#include "rf_reg_settings.h"
#include "sysctrl.h"
#include "app_uart.h"
#include "app_dmac_wrapper.h"
#include "app_qspi_wrapper.h"
#include "app_hwecc_wrapper.h"
#include "app_gpio.h"
#include "rtc.h"
#include "swint.h"
#include "io_ctrl.h"
#ifdef FLASH_XIP
#include "flash_cache.h"
#endif
#include "compiler_flag.h"
/**
 ****************************************************************************************
 * @addtogroup DRIVERS
 * @{
 *
 *
 * ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
#define RAM_BASE        0x00100000
#define ROM_DATA_BASE   0x0012f5cc
#define RAM_LIMIT       0x00130000
#define BOOT_TUNNEL __attribute__((section("boot_tunnel"), zero_init))
/*
 * STRUCTURE DEFINITIONS
 ****************************************************************************************
 */

/// Description of unloaded RAM area content
struct unloaded_area_tag
{
    // status error
    uint32_t error;
};


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

app_uart_inst_t uart0 = UART_INSTANCE(0);

void uart0_read(uint8_t * bufptr, uint32_t size, void(* callback)(void *, uint8_t), void * dummy)
{
    app_uart_read(&uart0.inst,bufptr,size,callback, dummy);
}

void uart0_write(uint8_t * bufptr, uint32_t size, void(* callback)(void *, uint8_t), void * dummy)
{
    app_uart_write(&uart0.inst,bufptr,size,callback, dummy);
}

void uart0_flow_on()
{
    app_uart_flow_on(&uart0.inst);
}

bool uart0_flow_off()
{
    return app_uart_flow_off(&uart0.inst);
}
// Creation of uart external interface api
const struct rwip_eif_api uart_api =
{
    uart0_read,
    uart0_write,
    uart0_flow_on,
    uart0_flow_off,
};

#if (PLF_DEBUG)
/// Variable to enable infinite loop on assert
volatile int dbg_assert_block = 1;
#endif //PLF_DEBUG

/// Pointer to access unloaded RAM area
struct unloaded_area_tag* unloaded_area;

/// Variable storing the reason of platform reset
uint32_t error = RESET_NO_ERROR;

uint32_t current_image_base BOOT_TUNNEL;
uint32_t nvds_base BOOT_TUNNEL;
uint32_t flash_dual_quad BOOT_TUNNEL;
/*
 * LOCAL FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize unloaded RAM area
 *
 * The unloaded RAM area is a part of RAM data memory that is not loaded at platform boot.
 * Information written in this area is maintained until device power-off.
 ****************************************************************************************
 */
static void unloaded_area_init(void);


/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static void unloaded_area_init(void)
{

	// Map unloaded RAM area pointer onto RAM memory
     unloaded_area = (struct unloaded_area_tag*)RAM_UNLOADED_BASE;


    /*****************************************************************************
     ***********************        RESET REASON        **************************
     *****************************************************************************/

    // Check if reset is due to FW failure
    error = unloaded_area->error;
    
    // Clear value in unloaded area
    unloaded_area->error = RESET_NO_ERROR;

}


/*
 * EXPORTED FUNCTION DEFINITIONS
 ****************************************************************************************
 */

#if (PLF_DEBUG)
void assert_err(const char *condition, const char * file, int line)
{
	// Trigger assert message
	rwip_assert_err(file, line, 0, 0);
	GLOBAL_INT_STOP();
	LOG(LOG_LVL_ERROR,"ASSERT_ERR: file %s, line %d, %s\n",file,line,condition);
	__BKPT(2);
	while(1);
}

void assert_param(int param0, int param1, const char * file, int line)
{
	// Trigger assert message
	rwip_assert_err(file, line, param0, param1);
	GLOBAL_INT_STOP();
	LOG(LOG_LVL_ERROR,"ASSERT_PARAM: file %s, line %d, param0 %d, param1 %d\n",file,line,param0,param1);
	__BKPT(2);
	while(1);
}

void assert_warn(int param0, int param1, const char * file, int line)
{
	LOG(LOG_LVL_WARN,"ASSERT_WARN: file %s, line %d, param0 %d, param1 %d\n",file,line,param0,param1);
}

void dump_data(uint8_t* data, uint16_t length)
{
	return;
}
#endif //PLF_DEBUG

uint16_t get_stack_usage(void)
{

	return STACK_TOP - __get_MSP();

}

void platform_reset(uint32_t error)
{

    // Disable interrupts
    GLOBAL_INT_STOP();

    // Store information in unloaded area
    unloaded_area->error = error;

    if(error == RESET_AND_LOAD_FW || error == RESET_TO_ROM)
    {
        // Not yet supported
    	//TODO
    }
    else
    {
        // Restart whole chip
        #if HW_BX_VERSION == 2400
    	sysc_awo_awo_reset_signal_pack(0,0,0,0,0,0,0,0,1,0);
        #elif HW_BX_VERSION == 2401
        sysc_awo_sft_rst_set(SRST_ALL_CLR);
        #else
        #error ERROR: ERROR to define HW_BX_VERSION
        #endif
        
    }
}

void SystemInit(uint32_t param0,uint32_t param1,uint32_t param2,uint32_t param3) 
{
    if(param3 != BOOTINIT_FLAG)    //indicate bootram has already run.
    {                                        
        current_image_base = 0;
        nvds_base = 0;
        flash_dual_quad = 2;
    }else
    {
        current_image_base = param0;
        nvds_base = param1;
        flash_dual_quad = param2;
        memset((uint8_t *)RAM_LIMIT,0,0x4000);
    }
        
    // Redirect Interrupt Vectors
    __DMB();
    SCB->VTOR = RAM_BASE;
    __DSB();
    #if (RC32K_USED)
    rc_calib_start(true);
    #endif
    memset((void *)EM_BASE_ADDR,0,EM_BLE_END);
    #ifndef ALL_IN_RAM
    // ROM Code RW ZI Section Initialization
    memset((void *)ROM_DATA_BASE,0,RAM_LIMIT-ROM_DATA_BASE);
    #endif
}

static void sys_setup()
{
    sysctrl_set_ahb_apb_blemac_clk();
    rf_reg_settings_init_mp();
    sysctrl_32k_clk_init();
    srst_cpu(CACHE_SRST_CPU);
    srst_per(UART0_SRST_PER);
    clk_gate_clr_all_clk();
    pshare_reset_to_gpio();
    sysctrl_awo_init();
    io_init();
    app_dmac_init_wrapper();
    app_qspi_init_wrapper(flash_dual_quad);
    #ifdef FLASH_XIP
    flash_cache_config(current_image_base);
    flash_cache_enable(flash_dual_quad);
    #else
//    flash_init_mp(flash_dual_quad); 
    #endif
    NVIC_ClearPendingIRQ(BLE_LP_IRQn);
    NVIC_ClearPendingIRQ(BLE_MAC_IRQn);
    NVIC_EnableIRQ(BLE_LP_IRQn);
    NVIC_EnableIRQ(BLE_MAC_IRQn);
    SWINT_SYS_INT_CLR();
    SWINT_SYS_INT_EN();
    rtc_init();
    app_hwecc_init_wrapper();
}

#ifndef CFG_FREERTOS_SUPPORT
static void debug_init()
{
    uart0.param.baud_rate = UART_BAUDRATE_9600;
    uart0.param.rx_pin_no = 13;
    uart0.param.tx_pin_no = 12;
    uart0.param.tx_dma = 1;
    uart0.param.rx_dma = 1;
    app_uart_init(&uart0.inst);
}
#endif

/**
 ****************************************************************************************
 * @brief RW main function.
 *
 * This function is called right after the booting process has completed.
 *
 * @return status   exit status
 ****************************************************************************************
 */

int main(void)
{
    sys_setup();

    // Initialize unloaded RAM area
    #ifndef BX_VERF
    unloaded_area_init();
    #endif

    LOG_INIT();
    LOG(LOG_LVL_INFO,"main\n");

    patch_init();

    modem_init();
//    intc_init();

    #if (PLF_NVDS)
    nvds_init((uint8_t*)( nvds_base ),0);
    #endif

    #if (RC32K_USED)
    rc_calib_end();
    #endif
    modem_dev_calib_in_main();

    #ifdef CFG_FREERTOS_SUPPORT
    rtos_task_init();
    while(1);
    #else
    RTC_EN_WITHOUT_INT();
    debug_init();
    rwip_init(error);
    // finally start interrupt handling
    GLOBAL_INT_START();
    while(1)
    {
        uint8_t sleep_type;
        ble_schedule();
        GLOBAL_INT_DISABLE();
        sleep_type = sleep_prepare_and_check();
        if(sleep_type == (SYS_DEEP_SLEEP|BLE_DEEP_SLEEP|PROCESSOR_SLEEP))
        {
            pre_deepsleep_processing_mp();
            WFI();
            post_deepsleep_processing_mp();
        }else if(sleep_type & PROCESSOR_SLEEP)
        {
            WFI();
        }
        GLOBAL_INT_RESTORE();
    }
    #endif
}


const struct rwip_eif_api* rwip_eif_get(uint8_t type)
{
    const struct rwip_eif_api* ret = NULL;
    switch(type)
    {
        case RWIP_EIF_AHI:
        {
        #ifdef CFG_FREERTOS_SUPPORT
            ret = os_get_eif_api();             //os_msg_api;
        #else
            ret = &uart_api;
        #endif
        }
        break;
        #if (BLE_EMB_PRESENT) || (BT_EMB_PRESENT)
        case RWIP_EIF_HCIC:
        {
            ret = &uart_api;
        }
        break;
        #elif !(BLE_EMB_PRESENT) || !(BT_EMB_PRESENT)
        case RWIP_EIF_HCIH:
        {
            ret = &uart2_api;
        }
        break;
        #endif // (BLE_EMB_PRESENT)
        default:
        {
            ASSERT_INFO(0, type, 0);
        }
        break;
    }
    return ret;
}


/// @} DRIVERS
