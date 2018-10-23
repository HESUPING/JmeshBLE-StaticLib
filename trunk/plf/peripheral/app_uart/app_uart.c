#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "reg_uart.h"
#include "dw_apb_uart_typedef.h"
#include "field_manipulate.h"
#include "app_uart.h"
#include "bx_dbg.h"
#include "ll.h"
#include "rwip.h"
#include "log.h"
#include "co_utils.h"
#include "app_dmac_wrapper.h"

#define BIT_FETCH(val,index)	(((val)>>(index))&0x1)

extern periph_universal_func_set_t uart_universal_func;

static void uart_rx_complete(app_uart_inst_t *inst)
{
    void (*callback) (void*,uint8_t) = NULL;
    void *data = NULL;
    reg_uart_t *reg = inst->reg;

    // Disable Rx interrupt
    FIELD_WR(reg,DLH_IER,UART_ERBFI,Received_Data_Available_Interrupt_Disabled);
    
    // Retrieve callback pointer
    callback = inst->env.rx.callback;
    data = inst->env.rx.dummy;
    
    BX_ASSERT(callback);
    
    // Clear callback pointer
    inst->env.rx.callback = NULL;
    inst->env.rx.dummy = NULL;
    uart_universal_func.sys_stat_func(inst,UART_READ_DONE);
    if(inst->env.errordetect==false)
    {
         // Call handler
        callback(data, RWIP_EIF_STATUS_OK);
    }else
    {
        inst->env.errordetect = false;
        callback(data,RWIP_EIF_STATUS_ERROR);
    }
}

static void uart_rec_data_avail_isr(app_uart_inst_t *inst)
{

    reg_uart_t *reg = inst->reg;
    while (FIELD_RD(reg, LSR, UART_DR)==Data_Ready)
    {
        // Read the received in the FIFO
        *inst->env.rx.bufptr = reg->RBR_THR_DLL;
//        LOG(LOG_LVL_INFO,"%02X ",*inst->env.rx.bufptr);
        // Update RX parameters
        inst->env.rx.size--;
        inst->env.rx.bufptr++;

        // Check if all expected data have been received
        if (inst->env.rx.size == 0)
        {
            // Reset RX parameters
            inst->env.rx.bufptr = NULL;
            uart_rx_complete(inst);
            // Exit loop
            break;
        }
    }
}

static void uart_tx_complete(app_uart_inst_t *inst)
{
    void (*callback) (void*,uint8_t) = NULL;
    void * dummy = NULL;
    reg_uart_t *reg = inst->reg;
    while(FIELD_RD(reg,LSR,UART_TEMT) == Transmitter_Not_Empty);
    // Disable TX interrupt
    FIELD_WR(reg,DLH_IER,UART_ETBEI,Transmit_Holding_Register_Empty_Interrupt_Disabled);
    // Retrieve callback pointer
    callback = inst->env.tx.callback;
    dummy = inst->env.tx.dummy;
    BX_ASSERT(callback);
    // Clear callback pointer
    inst->env.tx.callback = NULL;
    inst->env.tx.dummy = NULL;
    //set uart idle status
    uart_universal_func.sys_stat_func(inst,UART_WRITE_DONE);
    // Call handler
    callback(dummy, RWIP_EIF_STATUS_OK);
}

static void uart_thr_empty_isr(app_uart_inst_t *inst)
{
    if(inst->env.tx.size)
    {
        reg_uart_t *reg = inst->reg;
        // Fill TX FIFO until there is no more room inside it
        while (FIELD_RD(reg,USR,UART_TFNF)==Transmit_FIFO_Not_Full)
        {
            // Put a byte in the FIFO
            reg->RBR_THR_DLL = *inst->env.tx.bufptr;
            // Update TX parameters
            inst->env.tx.bufptr++;
            inst->env.tx.size--;
            if (inst->env.tx.size == 0)
            {
                // Exit loop
                break;
            }
        }
    }else
    {
        // Reset TX parameters
        inst->env.tx.bufptr = NULL;
        uart_tx_complete(inst);
    }
}

static void uart_rec_error_isr(app_uart_inst_t *inst)
{
    reg_uart_t *reg = inst->reg;
    uint8_t LSR = (uint8_t)reg->LSR;
    if(BIT_FETCH(LSR,1)==Overrun_Error)
    {
        LOG(LOG_LVL_ERROR,"uart overrun\n");
        while(FIELD_RD(reg,LSR,UART_DR)==Data_Ready)
        {
            reg->RBR_THR_DLL;
        }
    }
    if(BIT_FETCH(LSR,3)==Framing_Error)
    {
        LOG(LOG_LVL_ERROR,"uart framing error\n");
        inst->env.errordetect = true;
    }
}

void app_uart_isr(app_uart_inst_t *inst)
{
    reg_uart_t *reg = inst->reg;
    while(1)
    {
        IIR_INTERRUPT_ID_FIELD irq_stat = (IIR_INTERRUPT_ID_FIELD)FIELD_RD(reg,IIR_FCR,UART_IID);
        if(irq_stat==No_Interrupt_Pending)  break;
        switch(irq_stat)
        {
        case Receiver_Line_Status_Interrupt:
            uart_rec_error_isr(inst);
        break;
        case Received_Data_Available_Interrupt:
        case Character_Timeout_Interrupt:
            uart_rec_data_avail_isr(inst);
        break;
        case THR_Empty_Interrupt:
            uart_thr_empty_isr(inst);
        break;
        default:
            LOG(LOG_LVL_WARN,"uart:%d unexpected iid\n",inst->idx);
        break;
        }
    }
}


void uart_set_divisor(reg_uart_t *reg,uint16_t divisor)
{
    FIELD_WR(reg,LCR,UART_DLAB,Divisor_Latch_Register_Enabled);	
    reg->RBR_THR_DLL = (uint8_t)divisor;
    reg->DLH_IER = (uint8_t)(divisor>>8);
    FIELD_WR(reg,LCR,UART_DLAB,Divisor_Latch_Register_Disabled);	
}

void app_uart_init(periph_inst_handle_t hdl)
{
    app_uart_inst_t *inst = CONTAINER_OF(hdl, app_uart_inst_t, inst);
    app_uart_comm_params_t *param = &inst->param;
    uint32_t clk_src = (*(uint32_t *)&param->baud_rate>>10);
    uint16_t divisor = (uint16_t)(*(uint32_t *)&param->baud_rate)&0x3ff;
    uart_universal_func.sw_rst_func(inst);
    uart_universal_func.clk_src_cfg_func(inst,clk_src);
    uart_universal_func.clk_gate_func(inst,SET_CLK);
    uart_universal_func.pin_cfg_func(inst,param->rx_pin_no,UART_RXD_PIN);
    uart_universal_func.pin_cfg_func(inst,param->tx_pin_no,UART_TXD_PIN);
    reg_uart_t *reg = inst->reg;
    if(param->flow_control_en)
    {
        uart_universal_func.pin_cfg_func(inst,param->rts_pin_no,UART_RTS_PIN);
        uart_universal_func.pin_cfg_func(inst,param->cts_pin_no,UART_CTS_PIN);
    }
    if(param->auto_flow_control)
    {
        reg->IIR_FCR = FIELD_BUILD(UART_RCVR,RCVR_Trigger_FIFO_Half_Full)
            |FIELD_BUILD(UART_FIFOE,FIFO_Enabled);
        FIELD_WR(reg, MCR, UART_AFCE,1);
    }else
    {
        reg->IIR_FCR = FIELD_BUILD(UART_RCVR,RCVR_Trigger_One_Character)
            |FIELD_BUILD(UART_FIFOE,FIFO_Enabled);
        FIELD_WR(reg, MCR, UART_AFCE,0);
    }
    reg->LCR = FIELD_BUILD(UART_STOP, One_Stop_bit) | FIELD_BUILD(UART_DLS, Data_Length_8_bits) 
        | FIELD_BUILD(UART_PEN, param->parity_en) | FIELD_BUILD(UART_EPS, param->even_parity);
    FIELD_WR(reg,DLH_IER,UART_ELSI,Receiver_Line_Status_Interrupt_Enabled);
    uart_universal_func.intr_op_func(inst,INTR_CLR);
    uart_universal_func.intr_op_func(inst,INTR_ENABLE);
    uart_set_divisor(reg,divisor);
    uart_universal_func.sys_stat_func(inst,UART_INIT);
}

void app_uart_uninit(periph_inst_handle_t hdl)
{
    app_uart_inst_t *inst = CONTAINER_OF(hdl, app_uart_inst_t, inst);
    uart_universal_func.clk_gate_func(inst,CLR_CLK);
    uart_universal_func.intr_op_func(inst,INTR_DISABLE);
    uart_universal_func.sys_stat_func(inst,UART_UNINIT);
}

static void uart_transfer_sanity_check(uint8_t *bufptr,uint32_t size,void (*callback)(void *,uint8_t))
{
    // Sanity check
    BX_ASSERT(bufptr != NULL);
    BX_ASSERT(size != 0);
    BX_ASSERT(callback != NULL);
}

uint16_t uart_get_fifo_depth(app_uart_inst_t *inst);

static void app_uart_read_dma(app_uart_inst_t *inst)
{
    uint16_t fifo_depth = uart_get_fifo_depth(inst);
    app_dmac_transfer_param_t param = 
    {
        .callback = (void (*)(void*))uart_rx_complete,
        .callback_param = inst,
        .src = (uint8_t *)&inst->reg->RBR_THR_DLL,
        .dst = (uint8_t *)inst->env.rx.bufptr,
        .length = inst->env.rx.size,
        .src_tr_width = Transfer_Width_8_bits,
        .dst_tr_width = Transfer_Width_8_bits,
        .src_msize = dmac_get_burst_transaction_size_enum(inst->param.auto_flow_control ? fifo_depth / 2 : 1),
        .dst_msize = Burst_Transaction_Length_4,
        .tt_fc = Peripheral_to_Memory_DMAC_Flow_Controller,
        .src_per = dmac_uart_rx_handshake_enum(inst->idx),
        .dst_per = 0,
        .int_en = 1,
    };
    app_dmac_start_wrapper(&param);
}

static void app_uart_read_no_dma(app_uart_inst_t *inst)
{
    reg_uart_t *reg = inst->reg;
    FIELD_WR(reg,DLH_IER,UART_ERBFI,Received_Data_Available_Interrupt_Enabled);
}

void app_uart_read(periph_inst_handle_t hdl,uint8_t *bufptr, uint32_t size, void (*callback) (void*,uint8_t),void* dummy)
{
    uart_transfer_sanity_check(bufptr,size,callback);
    app_uart_inst_t *inst = CONTAINER_OF(hdl, app_uart_inst_t, inst);
//    LOG(LOG_LVL_INFO,"%x,%d\n",bufptr,size);
    // Prepare RX parameters
    inst->env.rx.bufptr = bufptr;
    inst->env.rx.size = size;
    inst->env.rx.callback = callback; 
    inst->env.rx.dummy = dummy;
    uart_universal_func.sys_stat_func(inst,UART_READ_START);
    if(inst->param.rx_dma)
    {
        app_uart_read_dma(inst);
    }else
    {
        app_uart_read_no_dma(inst);
    }
}

static void uart_write_dma_callback(app_uart_inst_t *inst)
{
    reg_uart_t *reg = inst->reg;
    inst->env.tx.size = 0;
    FIELD_WR(reg,DLH_IER,UART_ETBEI,Transmit_Holding_Register_Empty_Interrupt_Enabled);
}

static void app_uart_write_dma(app_uart_inst_t *inst)
{
    uint16_t fifo_depth = uart_get_fifo_depth(inst);
    app_dmac_transfer_param_t param = 
    {
        .callback = (void (*)(void*))uart_write_dma_callback,
        .callback_param = inst,
        .src = (uint8_t *)inst->env.tx.bufptr,
        .dst = (uint8_t *)&inst->reg->RBR_THR_DLL,
        .length = inst->env.tx.size,
        .src_tr_width = Transfer_Width_8_bits,
        .dst_tr_width = Transfer_Width_8_bits,
        .src_msize = Burst_Transaction_Length_4,
        .dst_msize = Burst_Transaction_Length_4,
        .tt_fc = Memory_to_Peripheral_DMAC_Flow_Controller,
        .src_per = 0,
        .dst_per = dmac_uart_tx_handshake_enum(inst->idx),
        .int_en = 1,
    };
    app_dmac_start_wrapper(&param);
}

static void app_uart_write_no_dma(app_uart_inst_t *inst)
{
    reg_uart_t *reg = inst->reg;
    FIELD_WR(reg,DLH_IER,UART_ETBEI,Transmit_Holding_Register_Empty_Interrupt_Enabled);
}

void app_uart_write(periph_inst_handle_t hdl,uint8_t *bufptr, uint32_t size, void (*callback) (void*,uint8_t),void* dummy)
{
    uart_transfer_sanity_check(bufptr,size,callback);
    app_uart_inst_t *inst = CONTAINER_OF(hdl, app_uart_inst_t, inst);
    // Prepare TX parameters
    inst->env.tx.bufptr = bufptr;
    inst->env.tx.size = size;
    inst->env.tx.callback = callback; 
    inst->env.tx.dummy = dummy;
    uart_universal_func.sys_stat_func(inst,UART_WRITE_START);
    if(inst->param.tx_dma)
    {
        app_uart_write_dma(inst);
    }else
    {
        app_uart_write_no_dma(inst);
    }
}

void app_uart_flow_on(periph_inst_handle_t hdl)
{
    app_uart_inst_t *inst = CONTAINER_OF(hdl, app_uart_inst_t, inst);
    reg_uart_t *reg = inst->reg;
    FIELD_WR(reg,MCR,UART_RTS,RTS_Signal_Low);
}

bool app_uart_flow_off(periph_inst_handle_t hdl)
{
    app_uart_inst_t *inst = CONTAINER_OF(hdl, app_uart_inst_t, inst);
    reg_uart_t *reg = inst->reg;
    bool flow_off;
    GLOBAL_INT_DISABLE();
    if(FIELD_RD(reg,USR,UART_RFNE)==Receive_FIFO_Empty && FIELD_RD(reg,USR,UART_TFE)==Transmit_FIFO_Empty)
    {
        FIELD_WR(reg,MCR,UART_RTS,RTS_Signal_High);
        flow_off = true;
    }else
    {
        flow_off = false;
    }
    GLOBAL_INT_RESTORE();
    return (flow_off);
}

