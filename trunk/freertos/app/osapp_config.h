
/**
 *
 * @file osapp_config.h
 *
 * @brief Define some general structure and macro for os application
 *
 * Copyright (C) Bluexmicro electronics 2015-2016
 *
 */

#ifndef OSAPP_CONFIG_H_
#define OSAPP_CONFIG_H_
#define __RAM_CODE__
#include "Freertos.h"
#include "task.h"
#include "event_groups.h"
#include "gapm_task.h"
#include "gapc_task.h"
#include "gattc_task.h"
#include "gattm_task.h"
#include "attm.h"
#include "bx_dbg.h"
#include "log.h"
#include "nvds_in_ram.h"
#include "osapp_task.h"
#include "co_bt.h"
#include "co_math.h"
#include "prf.h"
#include "osapp_utils.h"

typedef void (*osapp_msg_handler_t)(ke_msg_id_t const msgid,
                            void const *param,
                            ke_task_id_t const dest_id,
                            ke_task_id_t const src_id);
/**
 * @brief structure to define message and it's callback
 */
typedef struct
{
    ke_msg_id_t id;
    osapp_msg_handler_t func;
}osapp_msg_handler_table_t;

/**
 * @brief osapp_task use this structure to find callback for a message.
 */
typedef struct
{
    const osapp_msg_handler_table_t *  handler_table;
    uint8_t table_size;
}osapp_msg_handler_info_t;
/**
 * @brief structure to define a freertos task.
 */
typedef struct
{
	bool 			is_used;						/* if this task is in use */
	const char *const	task_name;	  /* Task name,max length is 16 */
	uint8_t 			priority;						/* Task priority */
	uint16_t			stack_size; 					/* size of stack for this task */
	void *				param;							/* task argument */
	TaskFunction_t		entry_proc; 					/* Task entry function */
	TaskHandle_t		*task_handle;
} task_table_t;
/**
 * @brief This structure help to initialize a freertos task.
 */
typedef struct
{
    const task_table_t *task_table;
    const uint8_t table_size;
}task_table_info_t;
#define ARRAY_INFO(hdl) {hdl,sizeof(hdl)/sizeof(hdl[0])}

///define stack size
#define BLE_TASK_STACK_SIZE				500							// actual size = (XXX_TASK_STACK_SIZE * 4) Byte						
#define APP_TASK_STACK_SIZE			         256	

///define task priority
#define OS_PRIORITY_BLE_TASK			(configMAX_PRIORITIES  - 1)		//5
#define OS_PRIORITY_APP_TASK			(OS_PRIORITY_BLE_TASK - 1)          // 4

//#define OSAPP_TEMPLATE			/**<template, a very simple application. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_ADV				/**<An example for advertising using Bx2400. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_DIS_SERVER		/**<An example for Bx2400 using as a gapm server. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_DIS_CLIENT		/**<An example for Bx2400 using as a client. Run with a OSAPP_DIS_SERVER on the opposite side. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_SELFIE			/**<An example for Bx2400 using as a selfie controller. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_ADV_CHG			/**<An example for advertising continuously when changing advertising data. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_SCAN			/**<An example for Bx2400 scan other device. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_CONNPARAM_CHG	/**<An example for changing connection parameter while keeping a connection. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_BOND_SLAVE		/**<An example for bonding as a slave. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_BOND_MASTER		/**<An example for bonding as a master. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_ADVINTV_CHANGE	/**<An example for changing advertising interval. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_FINDT			/**<An example for the slave of findme profile. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_DEMO			/**<Bx2400 demo project, also operate peripheral devices. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_GBLE			/**<An example for Gizwits GBLE. Only one OSAPP_XXX macro can be defined. */

//#define OSAPP_MI_SCALE

//#define OSAPP_UART_SERVER

//#define OSAPP_MESH
//#define OSAPP_1M2M_SLAVE
//#define OSAPP_1M2M_MASTER

#define  OSAPP_JMESH

//#define OSAPP_BLE_DEMO	/**<An example for Bx2400 using as a ble demo. Only one OSAPP_XXX macro can be defined.  */


//#define OSAPP_THROUGHPUT_SERVER /**<An example for BX2400 GATT server. Push throughput to peak by sending frequent notifications. */

//#define OSAPP_THROUGHPUT_CLIENT /**<An example for BX2400 GATT client. Exchange MTU before receiving notifications. */
#endif

