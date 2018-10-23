 
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "bx_config.h"
#include "osapp_config.h"
#include "rwip_config.h"
#include <stdbool.h>
#include <stdint.h>
#include "task_init.h"
#include "rwip.h"
#include "bx_dbg.h"
#include "log.h"
#include "arch.h"
#include "ble_task.h"
#include "osapp_task.h"
#include "gap.h"
#include "gapm_task.h"
#include "bx2400.h"
#include "awo.h"
#include "rtc.h"
#include "log.h"
#include "rst_gen.h"
#include "plf.h"
#include "reg_sysc_awo.h"
#include "sys_sleep.h"
#include "os_main.h"
#if defined( INCLUDE_uxTaskGetStackHighWaterMark )
extern void stk_chk_dbg( void );
#endif

/*
 * DEFINES
 ****************************************************************************************
 */
#define APP_MSG_TX_QUEUE_SIZE     3    
#define APP_MSG_RX_QUEUE_SIZE     8    

#if (RC32K_USED)
extern uint32_t rc_freq;
#define portRTC_FREQUENCY rc_freq
#else
#if (HZ32000)
#define portRTC_FREQUENCY 32000
#else
#define portRTC_FREQUENCY 32768
#endif
#endif




static msg_queue_t msg_queue;

extern const task_table_info_t extra_task_table_info;
static const task_table_t default_task_table[] =
{
/*	  IsUse  TaskName	            Prio	         Stksize			Arg    Entry	  handler */
/* ----------------------------------------------------------------- */
    { true, "BLE_TASK",  OS_PRIORITY_BLE_TASK,	 BLE_TASK_STACK_SIZE,  &msg_queue,  ble_stack_task,  &handler_ble_stack_task },  
    { true, "APP_TASK",  OS_PRIORITY_APP_TASK,   APP_TASK_STACK_SIZE,  &msg_queue,  osapp_task,  &handler_osapp_task },
};
const task_table_info_t core_task_table_info = ARRAY_INFO(default_task_table);
__attribute__((weak)) const task_table_info_t extra_task_table_info = {NULL,0};

static uint32_t ulTimerCountsForOneTick;
static uint32_t RTCWakeupDelay;
static uint32_t rtcMatchCount;
#define RTC_INITIAL_VAL 0xfff00000


/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
#if defined( INCLUDE_uxTaskGetStackHighWaterMark )
void stk_chk_dbg( void )
{
	unsigned portBASE_TYPE uxHighWaterMark;
	uint8_t task_num,i;

	task_num = core_task_table_info.table_size;
    const task_table_t *task_table = core_task_table_info.task_table;
	for(i=0; i < task_num; i++)
	{
		if(task_table[i].is_used == true)
		{
			BX_ASSERT(task_table[i].task_handle != NULL);									// task should already been initialized

			uxHighWaterMark = uxTaskGetStackHighWaterMark(*task_table[i].task_handle);		// null means check current task stack
			LOG(LOG_LVL_INFO,"%s stk remain 0x%x*4Byte\n",task_table[i].task_name,uxHighWaterMark);
		}
	}

    
    task_num = extra_task_table_info.table_size;
    task_table = extra_task_table_info.task_table;
    for(i=0; i < task_num; i++)
    {
        if(task_table[i].is_used == true)
        {
            BX_ASSERT(task_table[i].task_handle != NULL);                                   // task should already been initialized

            uxHighWaterMark = uxTaskGetStackHighWaterMark(*task_table[i].task_handle);      // null means check current task stack
            LOG(LOG_LVL_INFO,"%s stk remain 0x%x*4Byte\n",task_table[i].task_name,uxHighWaterMark);
        }
    }

}
#endif


void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if malloc failed */
        LOG(LOG_LVL_INFO,"Malloc Failed\n");
        __BKPT(2);
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* vApplicationStackOverflowHook will only be called if stackoverflow */
    LOG(LOG_LVL_INFO,"StackOverFlow\n");
    __BKPT(2);
}

static void rtos_tasks_create(const task_table_info_t * task_table_info)
{
    uint8_t task_num = task_table_info->table_size;
    const task_table_t *task_table = task_table_info->task_table;
    uint8_t i;
    for( i = 0; i < task_num; i++ )
    {
        if( (task_table[i].is_used) && (task_table[i].entry_proc != NULL) )
        {
            xTaskCreate(task_table[i].entry_proc,task_table[i].task_name,task_table[i].stack_size,task_table[i].param,task_table[i].priority,task_table[i].task_handle);
            BX_ASSERT(task_table[i].task_handle != NULL);
        }
    }
}
void rtos_task_init()
{
	
    msg_queue.cmd_q = xQueueCreate(APP_MSG_TX_QUEUE_SIZE,sizeof(AHI_MSGBOX_t));
    msg_queue.rsp_q = xQueueCreate(APP_MSG_RX_QUEUE_SIZE,sizeof(AHI_MSGBOX_t));
	
	// Here : Init variables and state before all the freertos tasks run

	////////////////////////////////////////////////////////////////////
	
    rtos_tasks_create(&core_task_table_info);
    rtos_tasks_create(&extra_task_table_info);
    
    os_start();//jmesh
    
    vTaskStartScheduler();

}

void xPortSysTickHandler( void );
void vPortOSTick_IRQ()
{
    RTC_INT_CLR();
    uint32_t prev_rtc_matchcnt = rtcMatchCount;
    rtcMatchCount += ulTimerCountsForOneTick;
    /* --start-- for breakpoint debug use */
    bool wrap = prev_rtc_matchcnt > rtcMatchCount ? true : false;
    if(wrap == false)
    {
        uint32_t current_rtc_val = RTC_CURRENTCNT_GET();
        if(current_rtc_val >= rtcMatchCount)
        {
            LOG(LOG_LVL_WARN,"missing ticks\n");
            uint32_t step_ticks = (current_rtc_val - rtcMatchCount) / ulTimerCountsForOneTick + 1;
            rtcMatchCount += step_ticks * ulTimerCountsForOneTick;
        }
    }
    
    /* --end-- */
    RTC_MATCHCNT_SET(rtcMatchCount);
    xPortSysTickHandler();
}

void RTC_IRQHandler(void)
{
    vPortOSTick_IRQ();
}

void system_tick_init()
{
    RTCWakeupDelay = rwip_us_2_lpcycles(FREERTOS_WAKEUP_DELAY);
    ulTimerCountsForOneTick = portRTC_FREQUENCY / configTICK_RATE_HZ;
    rtcMatchCount = RTC_INITIAL_VAL + ulTimerCountsForOneTick;
    RTC_MATCHCNT_SET(rtcMatchCount);
    RTC_LOADCNT_SET(RTC_INITIAL_VAL);
    RTC_EN_WITH_INT();

}

static void clr_rtc_intr()
{   
    RTC_INT_CLR();
    NVIC_ClearPendingIRQ(RTC_IRQn);
}

void bxSuppressTicksAndSleep(uint32_t xExpectedIdleTime )
{
    taskENTER_CRITICAL();
    uint8_t sleep_type = sleep_prepare_and_check();
    eSleepModeStatus eSleepStatus = eTaskConfirmSleepModeStatus();
    if(eSleepStatus != eAbortSleep && sleep_type == (PROCESSOR_SLEEP|BLE_DEEP_SLEEP|SYS_DEEP_SLEEP))
    {
        uint32_t wakeupMatchValue; 
        uint32_t prevRTCMatchCount = rtcMatchCount - ulTimerCountsForOneTick;
        if(eSleepStatus == eStandardSleep)
        {
            wakeupMatchValue = prevRTCMatchCount + ulTimerCountsForOneTick*(xExpectedIdleTime+1) - RTCWakeupDelay;
        }else
        {
            wakeupMatchValue = prevRTCMatchCount - 1; // long enough before RTC IRQ raise
        }
        RTC_MATCHCNT_SET(wakeupMatchValue);
        clr_rtc_intr();
        pre_deepsleep_processing_mp();
        __WFI();
        post_deepsleep_processing_mp();
        bool rtc_int = RTC_INT_STAT_GET()? true : false;
        uint32_t RTCValueAfterSleep = RTC_CURRENTCNT_GET();
        if(eSleepStatus == eStandardSleep &&  rtc_int) 
        {
            BX_ASSERT((uint64_t)wakeupMatchValue + RTCWakeupDelay >RTCValueAfterSleep );
        }
        uint32_t RTCIncrement;
        if(RTCValueAfterSleep < prevRTCMatchCount)
        {
            RTCIncrement = (~0)-prevRTCMatchCount  + RTCValueAfterSleep + 1;
        }else
        {
            RTCIncrement = RTCValueAfterSleep - prevRTCMatchCount;
        }
        uint32_t OSTickIncrement = RTCIncrement /ulTimerCountsForOneTick;
        vTaskStepTick(OSTickIncrement);
        bool wrapping;
        if(rtcMatchCount<prevRTCMatchCount || rtcMatchCount > (~0) - ulTimerCountsForOneTick * OSTickIncrement)
        {
            wrapping = true;
        }else
        {
            wrapping = false;
        }
        rtcMatchCount += ulTimerCountsForOneTick * OSTickIncrement;
        RTC_MATCHCNT_SET(rtcMatchCount);
        clr_rtc_intr();
        if(wrapping == false)
        {
            BX_ASSERT(RTC_CURRENTCNT_GET()<=rtcMatchCount);
        }
    }else if(sleep_type & PROCESSOR_SLEEP)
    {
        __WFI();
    }
    taskEXIT_CRITICAL();
}





