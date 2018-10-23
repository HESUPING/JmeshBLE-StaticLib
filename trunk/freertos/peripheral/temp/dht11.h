
/**
 *
 * @file dht11.h
 *
 * @brief dht11 driver may use in app layer as a peripheral of bx2400 system. DHT11 is a module which can collect real-time temperature and humidity.
 * We can combine DHT11 with other chip to develop application for IOT.
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

#ifndef DHT_11_H
#define DHT_11_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/// extern the handler of dht task which can be use when create dht task.
extern TaskHandle_t handler_dht_task;

/**
 * @ brief Struct to store dht data. value[0]: temperature. value[1]: humidity.
 */
struct dht_result_t
{
    uint8_t value[2];
};

/// define a micro to identify the message type.
#define TEMPERATURE_AVALIABLE_IND 5

/**
 * @brief initialize the dht device. Only use this function when do not want to use freertos.
 */
void dht_init(void);
/**
 * @brief De-initialize the dht device. We use this function to clear clock gate in order to save energy.
 */
void dht_deinit(void);
/**
 * @brief reset dht11 and start read data. When the function return, the data are not ready, should wait about 30ms to get data
 * Only use this function when do not want to use freertos.
 */
void dht_start(void);

/**
 * @brief get data and check the checksum. Only use this function when do not want to use freertos.
 * @param temperature: pointer to the data of temperature.
 * @param humidity: pointer to the data of humidity.
 * @return when the result is correct return 1, else return 0.
 */
uint8_t dht_get_result(uint8_t *temperature, uint8_t *humidity);

/**
 * @brief A freertos task. When use dht_task, execute dht_trigger_read to start data collect of DHT11.
 * When use dht_task, do not use dht_init, dht_start and dht_get_result.
 * @param params: pointer to the input parameter.
 */
void dht_task(void *params);

/**
 * @brief use this api to trigger dht11 read when dht run as a freertos task.
 */
void dht_trigger_read(void);


#endif
///@}
