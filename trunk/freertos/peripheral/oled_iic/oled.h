
/**
 *
 * @file oled.h
 *
 * @brief oled driver may use in app layer as a peripheral of bx2400 system. oled module is a screen which can show information
 * It can show user the status of the system or give some alarm.
 * Copyright (C) Bluexmicro electronics 2015-2016
 *
 */

/**
 ****************************************************************************************
 * @addtogroup App Demo
 * @ingroup RTOS App
 * @brief Demo to show the capability of Bx2400.
 * @{
 ****************************************************************************************
 */

#ifndef	__OLED_H
#define	__OLED_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/// extern the handler of oled task which can be use when create oled task.
extern TaskHandle_t handler_oled_task;

/**
 * @breif initialize the oled driver. pinshare, iic init and oled init here.
 */
void oled_init(void);
/**
 * @brief use the same as normal printf with x,y to specify the position. This function send message to oled task.
 * @param x: pixel of the x-axis. range from 0 to 127 for an 12864 screen
 * @param y: pixel of the y-axis/8. range from 0 to 8 for an 12864 screen
 * @param fmt: same as printf.
 */
void oled_printf(unsigned char x, unsigned char y, char *fmt, ...);
/**
 * @brief fill the screen with one character
 * @param fill_Data: character to fill the screen.
 */
void oled_fill(unsigned char fill_Data);
/**
 * @brief clear screen.
 */
void oled_cls(void);
/**
 * @brief turn on oled screen.
 */
void oled_on(void);
/**
 * @brief turn off oled screen can save power when we don't use it.
 */
void oled_off(void);
/**
 * @brief A freertos task. We use a task to schedule a oled because writting an oled is very slow compared with mcu speed.
 * @param params: pointer to the input parameter.
 */
void oled_task(void *params);


#endif
///@}
