/**
 ****************************************************************************************
 *
 * @file bxotas_task.h
 *
 * @brief Header file - BXOTASTASK.
 *
 * Copyright (C) BlueX Micro 2015-2016
 *
 *
 ****************************************************************************************
 */

#ifndef BXOTAS_TASK_H_
#define BXOTAS_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup BXOTASTASK Task
 * @ingroup BXOTAS
 * @brief BlueX BLE OTA Server Task
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "rwip_task.h" // Task definitions
#include "prf_types.h"
#include "bxota_common.h"

enum bxotas_msg_id
{
    BXOTAS_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_BXOTAS),
    BXOTAS_SW_VER_REQ_IND,
    BXOTAS_SW_VER_CFM,
    BXOTAS_PROGRAM_REQ_IND,
    BXOTAS_PROGRAM_CFM,
    BXOTAS_PROGRAM_DONE_IND,
};

struct bxotas_enable_req
{
    bool enable;  
};
struct bxotas_sw_ver_cfm 
{
    bxotas_sw_ver_t ver;
};
struct bxotas_program_req
{
    uint8_t conidx;
};
struct bxotas_program_cfm
{
    uint8_t conidx;
    bool confirm;
};
struct bxotas_nvds_update_req
{
    void *bxotas_env;
};
struct bxotas_nvds_update_cfm 
{
    uint32_t status;
};
uint8_t bxotas_nvds_get_length_by_name(void *env,uint8_t name);
uint8_t *bxotas_nvds_get_data_ptr_by_name(void *env,uint8_t name);
bool bxotas_nvds_check_valid_by_name(void *env,uint8_t name);
void bxotas_nvds_valid_set_by_name(void *env,uint8_t name,bool valid);

/// }@ BXOTASTASK
#endif // BXOTAS_TASK_H_

