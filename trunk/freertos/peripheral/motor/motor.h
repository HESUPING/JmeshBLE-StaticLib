/**
 *
 * @file motor.h
 *
 * @brief Motor driver may use in app layer as a peripheral of bx2400 system.
 * We can use the motor to simulate a fan or led light which control through way of pwm.
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

#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

/// motor rotation clockwise.
#define CLOCKWISE           0
/// motor rotation counter-clockwise.
#define COUNTER_CLOCKWISE   1

/**
 * @brief set motor pwm value. This function should run after
 * @param direction: choose from CLOCKWISE and COUNTER_CLOCKWISE
 * @param pwm: pwm range from 0 to 65535
 */
void motor_set(uint8_t direction, uint16_t pwm);

/**
 * @brief init of motor driver. Here pinshare are initiated, user should modify pinshare definition.
 */
void motor_init(void);
/**
 * @brief deinit of motor driver. clear the clock gate when we don't need the device anymore in order to save energy.
 */
void motor_deinit(void);

#endif

///@}

