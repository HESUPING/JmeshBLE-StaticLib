#include "bx_config.h"
#include "bx2400.h"
#include "app_qspi_wrapper.h"
#include "app_qspi.h"
#ifdef CFG_FREERTOS_SUPPORT
#include "FreeRTOS.h"
#include "task.h"
#endif
#ifdef FLASH_XIP
#include "flash_cache.h"
#endif
#define QSPI_CS_SEL_MASK 0x1
extern uint32_t flash_dual_quad;
app_qspi_inst_t qspi_inst = QSPI_INSTANCE();

static uint32_t flash_qspi_operation_enter()
{
    uint32_t __irq_mask = 0;
    #ifdef FLASH_XIP
    #ifdef CFG_FREERTOS_SUPPORT
    taskENTER_CRITICAL();
    #else
    __irq_mask = __get_PRIMASK();
    __disable_irq();
    #endif
    flash_cache_disable();
    #endif
    return __irq_mask;
}

static void flash_qspi_operation_exit(uint32_t __irq_mask)
{
    #ifdef FLASH_XIP
    flash_cache_enable(flash_dual_quad);
    #ifdef CFG_FREERTOS_SUPPORT
    taskEXIT_CRITICAL();
    #else
    if(__irq_mask == 0)
    {
        __enable_irq();
    }
    #endif
    #endif
}


void app_qspi_init_wrapper(uint8_t mode)
{
    qspi_inst.param.clk_div = 2;
    qspi_inst.param.rxsample_dly = 1;
    qspi_inst.param.mode = mode;
    qspi_inst.param.cs_pin_no[0] = QSPI_CS0_PIN_NO;
    qspi_inst.param.clk_pin_no = QSPI_CLK_PIN_NO;
    qspi_inst.param.data_pin_no[0] = QSPI_D0_PIN_NO;
    qspi_inst.param.data_pin_no[1] = QSPI_D1_PIN_NO;
    qspi_inst.param.data_pin_no[2] = QSPI_D2_PIN_NO;
    qspi_inst.param.data_pin_no[3] = QSPI_D3_PIN_NO;
    app_qspi_init(&qspi_inst.inst); 
}

void app_qspi_uninit_wrapper()
{
    app_qspi_uninit(&qspi_inst.inst);
}

void app_qspi_std_write_wrapper(uint8_t *data,uint32_t length)
{
    uint32_t irq_mask = flash_qspi_operation_enter();
    app_qspi_std_write(&qspi_inst.inst,QSPI_CS_SEL_MASK,data,length);
    flash_qspi_operation_exit(irq_mask);
}

void app_qspi_flash_program_wrapper(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length)
{
    uint32_t irq_mask = flash_qspi_operation_enter();
    app_qspi_flash_program(&qspi_inst.inst,QSPI_CS_SEL_MASK,cmd,addr,data,length);
    flash_qspi_operation_exit(irq_mask);
}

void app_qspi_std_read_wrapper(uint8_t *cmd_buf,uint8_t cmd_len,uint8_t *data_buf,uint16_t data_len)
{
    uint32_t irq_mask = flash_qspi_operation_enter();
    app_qspi_std_read(&qspi_inst.inst,QSPI_CS_SEL_MASK,cmd_buf,cmd_len,data_buf,data_len);
    flash_qspi_operation_exit(irq_mask);
}

void app_qspi_multi_read_wrapper(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length,bool quad)
{
    uint32_t irq_mask = flash_qspi_operation_enter();
    app_qspi_multi_read(&qspi_inst.inst,QSPI_CS_SEL_MASK,cmd,addr,data,length,quad ? Quad_SPI_Format : Dual_SPI_Format);
    flash_qspi_operation_exit(irq_mask);
}

void app_qspi_config_for_cache_wrapper(uint16_t cache_line_size,uint8_t spi_mode)
{
    app_qspi_config_for_cache(&qspi_inst.inst,QSPI_CS_SEL_MASK,cache_line_size,spi_mode);
}

uint32_t app_qspi_dr_reg_addr_for_cache_wrapper()
{
    return app_qspi_dr_reg_addr_for_cache(&qspi_inst.inst);
}

void app_qspi_disable_for_cache_wrapper()
{
    app_qspi_disable_for_cache(&qspi_inst.inst);
}

