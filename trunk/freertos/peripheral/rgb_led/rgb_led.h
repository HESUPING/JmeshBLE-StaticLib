/**
 *
 * @file rgb_led.h
 *
 * @brief rgb led driver may use in app layer as a peripheral of bx2400 system. Rgb led combine 3 led with red, green and blue.
 * With these three leds together, it can make full range of color.
 *
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

#ifndef RGB_LED_H
#define RGB_LED_H

#include <stdint.h>
/**
 * @brief initialize the rgb_led driver. Pinshare are defined here which should be modifed when circuit changed.
 */
void rgb_led_init(void);
/**
 * @brief deinitialize the rgb_led driver. Clear the clock gate to save energy.
 */
void rgb_led_deinit(void);
/**
 * @brief set led color.
 * @param red: range from 0 to 255. The greater the value the more bright.
 * @param green: range from 0 to 255. The greater the value the more bright.
 * @param blue: range from 0 to 255. The greater the value the more bright.
 */
void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue);



#endif

///@}
