#ifndef QSPI_H_
#define QSPI_H_
#include <stdint.h>
#include "dw_apb_ssi_typedef.h"

void qspi_init(uint16_t clk_div,uint8_t rxsample_dly);

void qspi_std_write(uint8_t *data,uint32_t length);

void qspi_std_read(uint8_t *cmd_buf,uint8_t cmd_len,uint8_t *data_buf,uint32_t data_len);

void qspi_dual_read(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length);

void qspi_quad_read(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length);

void qspi_flash_program(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length);

void qspi_config_for_cache(uint16_t cache_line_size,uint8_t spi_mode);

uint32_t qspi_dr_reg_addr_for_cache(void);

void qspi_disable_for_cache(void);

#endif
