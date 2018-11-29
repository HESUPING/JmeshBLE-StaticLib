/*
 * mesh_tools.h
 *
 *  Created on: 2018-1-24
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_TOOLS_MESH_TOOLS_H_
#define FREERTOS_APP_MESH_TOOLS_MESH_TOOLS_H_


/**
 ****************************************************************************************
 * @addtogroup MESH_TOOLS_API
 * @ingroup  MESH_API
 * @brief defines for BLE MESH API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */
#define DISPLAY_MALLOC_FREE         1


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief  tools for printf to segger rtt log data .(temp buff use local variable array)
 *
 * @param[in]  data      Pointer to the data to be printf to segger rtt log.
 * @param[in]  length    The length of data to be printf.
 *
 ****************************************************************************************
 */
extern void log_mesh_received_data(uint8_t * data , uint8_t length);

/**
 ****************************************************************************************
 * @brief  tools for printf to segger rtt log data.(temp buff use malloc)
 *
 * @param[in]  data      Pointer to the data to be printf to segger rtt log.
 * @param[in]  length    The length of data to be printf.
 *
 ****************************************************************************************
 */
extern void log_hex_data(uint8_t * data , uint8_t length);

/**
 ****************************************************************************************
 * @brief  tools for memory reverse and copy.
 *
 * @param[in]  p_src      Pointer to the memcpy source data.
 * @param[out] p_dst      Pointer to the memcpy destination data.
 * @param[in]  length     The length of data to be memcpy.
 *
 * @note  Source and destination addresses cannot have an intersection.
 *
 ****************************************************************************************
 */
extern void memcpy_rev(void * p_dst, void * p_src, uint8_t length);

/**
 ****************************************************************************************
 * @brief  tools for reverse the src data.
 *
 * @param[in]  p_src      Pointer to the memcpy source data.
 * @param[in]  length     The length of data to be reverse.
 *
 ****************************************************************************************
 */
extern void reverse_self(void * src , uint8_t length);

/**
 ****************************************************************************************
 * @brief  tools for random generate.
 *
 * @param[out] p_out      Pointer to the random data.
 * @param[in]  len        generate random length in byte.
 *
 ****************************************************************************************
 */
extern void tools_random_generate(uint8_t *p_out,uint8_t len);

/**
 ****************************************************************************************
 * @brief  tools for get the gap public bd address.
 *
 * @param[out] p_out_addr      Pointer to the gap public bd address data.
 *
 ****************************************************************************************
 */
extern void tools_gap_public_bd_addr_get(uint8_t *p_out_addr);

#endif /* FREERTOS_APP_MESH_TOOLS_MESH_TOOLS_H_ */
/// @} MESH_TOOLS_API
