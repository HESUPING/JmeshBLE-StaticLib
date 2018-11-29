/*
 * uart_log_test.h
 *
 *  Created on: 2018年4月10日
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_UART_LOG_TEST_H_
#define FREERTOS_APP_MESH_MESH_TEST_UART_LOG_TEST_H_

//include
#include "bx_config.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "log.h"

///  ---------------   define
/// define task priority of uart log_TASK. Should be careful some priority are defined in task_init.h
#define OS_PRIORITY_UART_LOG_TASK           (OS_PRIORITY_APP_TASK  - 1)		// 3
/// stack size of dht task
#define UART_LOG_TASK_STACK_SIZE             300//300*4 Bytes


//uart log config
#define UART_LOG_PKT_CRC_SET        1//true
#define UART_LOG_CFG_SEND_BLOCK     0//false 1//true


// uart log packet head
#define UART_LOG_PACKET_HEAD  0xA5

//packet cmd  id
//tx
#define UART_PKTCMD_LOG_OUT_TX   	0x10 //LOG out
#define UART_PKTCMD_CLIENT_TX 	    0x11 //Config client out message
#define UART_PKTCMD_PROVISIONER_TX  0x12 //Provisioner out message
#define UART_PKTCMD_UNPROV_DEV_TX   0x13 //Unprov device out message
#define UART_PKTCMD_DEBUG_TX   		0xf1 //debug out message

//rx
#define UART_PKTCMD_CLIENT_RX  		0x91 //Config client set message
#define UART_PKTCMD_PROVISIONER_RX  0x92 //Provisioner Set
#define UART_PKTCMD_UNPROV_DEV_RX   0x93 //Unprov device Set
#define UART_PKTCMD_DEBUG_RX   		0xf2 //debug set message

///  ---------------   typedef
//uart rx callback
typedef void (*uartlog_msg_handler_t)(uint8_t const *param,uint8_t len);
typedef struct
{
   uartlog_msg_handler_t cfg_client_cb;
   uartlog_msg_handler_t provisoner_cb;
   uartlog_msg_handler_t unprov_dev_cb;
   uartlog_msg_handler_t debug_cb;
}uartlog_msg_handler_table_t;

typedef enum
{
	Receiver_Empty = 0,
	Receiver_Ready
}uart_log_rx_fifo_st_t;

/* States for CRC parser */
typedef enum {
  SERIAL_ST_HEAD = 0,
  SERIAL_ST_CMD,
  SERIAL_ST_LEN,
  SERIAL_ST_DATA,
  SERIAL_ST_CHECK,
}uart_log_rx_env_t;

typedef struct
{
  uint8_t cmd;//功能码
  uint8_t *pdata;//内容
  uint8_t rx_len;//准备接收的长度
  uint8_t data_len;//数据内容的长度
  uint16_t crc;//CRC校验
}uart_log_packet_t;
typedef struct
{
  uint8_t cmd;//功能码
  uint16_t tx_len;//准备接收的长度
  uint8_t *pdata;//内容

}uart_log_tx_env_t;
typedef enum {
  isunblock =0,
  isblock
}uart_log_queue_block_t;
typedef enum {
  task_noinit =0,
  task_init
}uart_log_queue_init_t;
typedef struct
{
  uint8_t front;
  uint8_t rear;
  uint8_t maxlen;
  uart_log_queue_init_t is_init;
  uart_log_queue_block_t block;
  uart_log_tx_env_t *buffer;
}uart_log_msg_queue_t;

typedef uint16_t (*crc_func_t)(uint16_t ,const void *,uint32_t);
///  ---------------  EXTERN value

/// extern the handler of uart log task which can be use when create uart log task.
extern TaskHandle_t handler_uart_log_task;

///  ---------------  EXTERN FUNCTION
//FUNCTION to system use
extern void uart_log_task(void *params);


//FUNCTION to uesr use
//==
extern void uart_log_rx_callback_register(uint8_t id,uartlog_msg_handler_t callback);
//==
extern void uart_log_send_cmd(uint8_t cmd,const void *parma,uint16_t len);
//==
extern void uart_log_printf(int8_t level, const char * format, ...);
//==
#define UART_TEST_LOG(level,...)	 \
		do{\
			uart_log_printf((level),__VA_ARGS__);\
		}while(0)
//== re defined
#if 0
#ifdef  LOG(level,...)
#undef  LOG(level,...)
#define LOG(level,...)\
		do{\
			uart_log_printf((level),__VA_ARGS__);\
		}while(0)
#endif/* defined LOG(level,...) */
#endif/* LOG()  re defined */

#endif /* FREERTOS_APP_MESH_MESH_TEST_UART_LOG_TEST_H_ */
