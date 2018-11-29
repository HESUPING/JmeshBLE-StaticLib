/*
 * mesh_uart_config.h
 *
 *  Created on: 2018Äê6ÔÂ13ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_MESH_UART_MESH_UART_CONFIG_H_
#define FREERTOS_APP_MESH_MESH_TEST_MESH_UART_MESH_UART_CONFIG_H_


#include "mesh_test_config.h"

#ifdef  MESH_TEST_UART_CTRL

//uart log cfg
#define OSAPP_UART_LOG_TEST       /** <Bx2400 UART LOG TEST TOOL.  when you use this, should define OSAPP_MESH ! */
#define MESH_TEST_UART_PROVISION  /** <Bx2400 UART LOG PROVISION test.  when you use this, should define OSAPP_UART_LOG_TEST ! */
#define MESH_TEST_UART_CLENT_SERVER  /** <Bx2400 UART CLENT SERVER test.  when you use this, should define OSAPP_UART_LOG_TEST ! */
#define MESH_UART_DEBUG_TEST_CMD  /** <Bx2400 UART DEBUG test.  when you use this, should define OSAPP_UART_LOG_TEST ! */


#endif /* MESH_UART_TEST */

#endif /* FREERTOS_APP_MESH_MESH_TEST_MESH_UART_MESH_UART_CONFIG_H_ */
