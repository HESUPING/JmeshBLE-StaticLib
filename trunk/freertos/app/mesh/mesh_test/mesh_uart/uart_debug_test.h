/*
 * uart_debug_test.h
 *
 *  Created on: 2018Äê7ÔÂ14ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_MESH_UART_UART_DEBUG_TEST_H_
#define FREERTOS_APP_MESH_MESH_TEST_MESH_UART_UART_DEBUG_TEST_H_

#include "mesh_uart_config.h"

#ifdef MESH_UART_DEBUG_TEST_CMD

///  ---------------   typedef

///  ---------------  EXTERN FUNCTION
//FUNCTION to system use
//==
extern void mesh_debug_uart_test_rx_callback(uint8_t const *param,uint8_t len);

//FUNCTION to app user
//==
extern void mesh_debug_uart_test_tx(const void *param,uint16_t len);

#endif /* MESH_UART_DEBUG_TEST_CMD */

#endif /* FREERTOS_APP_MESH_MESH_TEST_MESH_UART_UART_DEBUG_TEST_H_ */
