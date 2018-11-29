/*
 * mesh_app_action.h
 *
 *  Created on: 2018��5��8��
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_MESH_APP_ACTION_H_
#define FREERTOS_APP_MESH_MESH_TEST_MESH_APP_ACTION_H_
#include <stdint.h>



void set_led1(uint8_t on_off);
void set_led2(uint8_t on_off);
void init_leds(void);
void uart_cmd_init(void);

#endif /* FREERTOS_APP_MESH_MESH_TEST_MESH_APP_ACTION_H_ */
