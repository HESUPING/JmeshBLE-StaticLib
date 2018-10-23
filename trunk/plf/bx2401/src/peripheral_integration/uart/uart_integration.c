#include "periph_common.h"
#include "app_uart.h"
#include "periph_mngt.h"
#include "bx_config.h"
#include "bx2400.h"
#include "bx_dbg.h"
#include "rst_gen.h"
#include "clk_gate.h"
#include "reg_sysc_per.h"
#include "pin_share.h"
#include "log.h"

#define UART0_FIFO_DEPTH 32
#define UART1_FIFO_DEPTH 32
typedef struct
{
    uint16_t  clk_div_len0: 3,
        clk_div_len1: 3,
        clk_div_num0: 4,
        clk_div_num1: 4,
        src_sel : 2;
}uart_clk_src_cfg_t;

static periph_intr_env_t uart_intr_env[2];
static void uart_intr_op(app_uart_inst_t * inst,intr_operation_t op,void (*isr)(void *))
{
    IRQn_Type uart_irq = inst->idx ? UART1_IRQn : UART0_IRQn;
    if(op == INTR_ENABLE)
    {
        uart_intr_env[inst->idx].inst_ptr = inst;
        uart_intr_env[inst->idx].isr = isr;
        NVIC_EnableIRQ(uart_irq);
    }else if(op == INTR_DISABLE)
    {
        NVIC_DisableIRQ(uart_irq);
    }else if(op == INTR_CLR)
    {
        NVIC_ClearPendingIRQ(uart_irq);
    }else
    {
        BX_ASSERT(0);
    }
}

static void uart_sw_rst(app_uart_inst_t * inst)
{
    uint32_t rst_mask = inst->idx ? UART1_SRST_PER : UART0_SRST_PER;
    srst_per(rst_mask);
}

static void uart_clk_src_cfg(app_uart_inst_t * inst,uint32_t clk_cfg)
{
    uint8_t idx =inst->idx;
    uart_clk_src_cfg_t cfg = *(uart_clk_src_cfg_t *)&clk_cfg;
    #ifdef CFG_ON_CHIP
    if(idx)
    {
        sysc_per_clk_div_param2_pack(cfg.clk_div_num1, cfg.clk_div_num0,cfg.clk_div_len1, cfg.clk_div_len0);
        sysc_per_clk_sel_uart1_setf(cfg.src_sel);
    }else
    {
        sysc_per_clk_div_param1_pack(cfg.clk_div_num1, cfg.clk_div_num0,cfg.clk_div_len1, cfg.clk_div_len0);
        sysc_per_clk_sel_uart0_setf(cfg.src_sel);
    }
    #endif
}

static void uart_clk_gate(app_uart_inst_t * inst,clk_gate_operation_t op)
{
    uint8_t idx = inst->idx;
    #ifdef CFG_ON_CHIP
    if(op == SET_CLK )
    {
        if(idx)
        {
            clk_gate_per_g0(PER_CLKG0_SET_UART1|PER_CLKG1_SET_UART1);
        }else
        {
            clk_gate_per_g0(PER_CLKG0_SET_UART0|PER_CLKG1_SET_UART0);
        }
    }else
    {
        if(idx)
        {
            clk_gate_per_g0(PER_CLKG0_CLR_UART1|PER_CLKG1_CLR_UART1);
        }else
        {
            clk_gate_per_g0(PER_CLKG0_CLR_UART0|PER_CLKG1_CLR_UART0);
        }
    }   
    #endif
}

static void uart_pin_cfg(app_uart_inst_t * inst,uint8_t pin_num,uint32_t pin_role)
{
//    sysctrl_io_config(pin_num, pin_role);

    #ifdef CFG_ON_CHIP

    #else
    pshare_funcio_set(FUNC_IO_2,IO_UART0_RXD,ENABLE);
    pshare_funcio_set(FUNC_IO_3,IO_UART0_TXD,ENABLE);
    #endif
}

static void uart_sys_stat(app_uart_inst_t *inst,uint32_t sys_stat)
{
    uint8_t idx = inst->idx;
    switch(sys_stat)
    {
    case UART_INIT:
        recovery_list_add(&periph_domain_recovery_mngt, &inst->inst);
    break;
    case UART_UNINIT:
        recovery_list_remove(&periph_domain_recovery_mngt,&inst->inst);
    break;
    case UART_READ_START:
    case UART_WRITE_START:
        if(idx)
        {
            periph_domain_stat.uart1 = 1;
        }else
        {
            periph_domain_stat.uart0 = 1;
        }
    break;
    case UART_READ_DONE:
    case UART_WRITE_DONE:
        if(idx)
        {
            periph_domain_stat.uart1 = 0;
        }else
        {
            periph_domain_stat.uart0 = 0;
        }
    break;
    default:
        LOG(LOG_LVL_WARN,"unexpected sys stat: %d\n",sys_stat);
    break;
    }
}

const periph_universal_func_set_t uart_universal_func = {
    .intr_op_func = (intr_op_func_t)uart_intr_op,
    .sw_rst_func = (sw_rst_func_t)uart_sw_rst,
    .clk_src_cfg_func = (clk_src_cfg_func_t)uart_clk_src_cfg,
    .clk_gate_func = (clk_gate_func_t)uart_clk_gate,
    .pin_cfg_func = (pin_cfg_func_t)uart_pin_cfg,
    .sys_stat_func = (sys_stat_func_t)uart_sys_stat,
};

uint16_t uart_get_fifo_depth(app_uart_inst_t *inst)
{
    return inst->idx ? UART1_FIFO_DEPTH : UART0_FIFO_DEPTH;
}

void UART0_IRQHandler(void)
{
    uart_intr_env[0].isr(uart_intr_env[0].inst_ptr);
}

void UART1_IRQHandler(void)
{
    uart_intr_env[1].isr(uart_intr_env[1].inst_ptr);
}

