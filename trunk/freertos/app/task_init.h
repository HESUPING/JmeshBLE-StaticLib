
/**
 ****************************************************************************************
 *
 * @file task_init.h
 *
 * @brief responsible for freertos task initialize 
 *
 * Copyright (C) bluexmicro by zhaoweiqi
 *
 *
 ****************************************************************************************
 */

#ifndef TASK_INIT_H_
#define TASK_INIT_H_


/**
 ****************************************************************************************
 * @addtogroup ARCH
 * @ingroup BX2400
 *
 * @brief task init of freertos
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "task.h"


/*
 * DEFINES
 ****************************************************************************************
 */




/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
void rtos_task_init(void);						// init of all freertos tasks.
void stk_chk_dbg( void );
void system_tick_init(void);


#endif // TASK_INIT_H_


