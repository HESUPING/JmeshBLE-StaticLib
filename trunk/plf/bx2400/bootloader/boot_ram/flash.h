#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>              
#include <stdbool.h>

/**
 ****************************************************************************************
 * @addtogroup FLASH
 * @ingroup DRIVERS
 *
 * @brief Flash memory driver
 *
 * @{
 ****************************************************************************************
 */

typedef enum{
    Sector_Erase,
    Block_32KB_Erase,
    Block_64KB_Erase,
    Chip_Erase,
}erase_t;


/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

void flash_reset(void);
void flash_wakeup(void);
uint32_t flash_read_memory_density(void);
void flash_read_sfdp(uint32_t addr,uint8_t *buf,uint8_t buf_len);

uint8_t flash_erase(uint32_t offset,erase_t type);

/**
 ****************************************************************************************
 * @brief   Write a flash section.
 *
 * This function is used to write a part of the flash memory.
 * 
 * Note: callback parameter is not used
 *
 * @param[in]    offset      Starting offset from the beginning of the flash device
 * @param[in]    length      Size of the portion of flash to write
 * @param[in]    buffer      Pointer on data to write
 * @return       status      0 if operation can start successfully
 ****************************************************************************************
 */
uint8_t flash_program(uint32_t offset, uint32_t length, uint8_t *buffer);

/**
 ****************************************************************************************
 * @brief   Read a flash section.
 *
 * This function is used to read a part of the flash memory.
 * 
 * Note: callback parameter is not used
 *
 * @param[in]    offset      Starting offset from the beginning of the flash device
 * @param[in]    length      Size of the portion of flash to read
 * @param[out]   buffer      Pointer on data to read
 * @return       status      0 if operation can start successfully
 ****************************************************************************************
 */
uint8_t flash_read(uint32_t offset, uint32_t length, uint8_t *buffer);

uint8_t flash_dual_read(uint32_t offset, uint32_t length, uint8_t *buffer);

uint8_t flash_quad_read(uint32_t offset, uint32_t length, uint8_t *buffer);

void flash_deep_power_down(void);

///
uint8_t flash_status_read(uint8_t reg_idx);
///
uint8_t flash_status_write(uint8_t reg,uint8_t value);
///
uint16_t flash_status_write_2bytes(uint8_t val_l,uint8_t val_h);

/// @} FLASH

#endif // FLASH_H_
