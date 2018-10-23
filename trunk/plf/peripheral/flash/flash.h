/** @addtogroup FLASH
 *    @ingroup PERIPHERAL
 *  @{
 */
#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>
#include <stdbool.h>
#define FLASH_TYPE_UNKNOWN             0
#define FLASH_PAGE_SIZE               256

/**@brief flash erase type */
typedef enum{
    Sector_Erase,
    Block_32KB_Erase,
    Block_64KB_Erase,
    Chip_Erase,
}erase_t;

/**@brief flash reset command */
void flash_reset(void);

/**@brief flash wakeup command */
void flash_wakeup(void);

/**
 * @brief flash read memory density
 * @return flash memory density
 */
uint32_t flash_read_memory_density(void);

/**
 * @brief flash read sfdp register
 * @param[in] addr sfdp register addr
 * @param[out] buf buffer where the content will be put
 * @param[in] buf_len buffer length
 */
void flash_read_sfdp(uint32_t addr,uint8_t *buf,uint8_t buf_len);

/**
 * @brief  Read ID.
 * @return ID.
 */
uint32_t flash_read_ID(void);

/**
 * @brief   Erase a flash section.
 * @param[in] offset Starting offset from the beginning of the flash device to be erased
 * @param[in] type Erase command type
 * @return 0
 */
uint8_t flash_erase(uint32_t offset, erase_t type);

/**
 * @brief  Program flash.
 * @param[in] offset Starting offset from the beginning of the flash device to be programmed
 * @param[in] length Data length
 * @param[in] buffer Pointer on data to write
 * @return 0
 */
uint8_t flash_program(uint32_t offset, uint32_t length, uint8_t *buffer);

/**
 * @brief   Read from flash.
 * @param[in] offset Starting offset from the beginning of the flash device to be read
 * @param[in] length Data length
 * @param[out] buffer buffer where data read from flash will be put
 * @return 0
 */
uint8_t flash_read(uint32_t offset, uint32_t length, uint8_t *buffer);

/**
 * @brief   Flash Quad Read.
 * @param[in] offset Starting offset from the beginning of the flash device to be read
 * @param[in] length Data length
 * @param[out] buffer buffer where data read from flash will be put
 * @return 0
 */
uint8_t flash_quad_read(uint32_t offset, uint32_t length, uint8_t *buffer);

/**
 * @brief   Flash Dual Read.
 * @param[in] offset Starting offset from the beginning of the flash device to be read
 * @param[in] length Data length
 * @param[out] buffer buffer where data read from flash will be put
 * @return 0
 */
uint8_t flash_dual_read(uint32_t offset, uint32_t length, uint8_t *buffer);

/** @brief Flash deep power down command. */
void flash_deep_power_down(void);

uint8_t flash_quad_enable(void);

void flash_test(void);

#endif // FLASH_H_
/** @}*/

