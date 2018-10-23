/**
 ****************************************************************************************
 *
 * @file bxotas_task.c
 *
 * @brief BlueX BLE OTA Service Task implementation.
 *
 * Copyright (C) BlueX Micro 2015-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup BXOTASTASK
 * @{
 ****************************************************************************************
 */
 /*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_BXOTA_SERVER)
#include <string.h>
#include "bxotas.h"
#include "gattc_task.h"
#include "bx_dbg.h"
#include "bxotas_task.h"
#include "prf.h"
#include "prf_utils.h"
#include "log.h"
/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
static int gattc_read_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    int msg_status = KE_MSG_CONSUMED;
    uint8_t att_db_idx = bxotas_get_att_db_idx_from_handle(param->handle);
    switch(att_db_idx)
    {
    case BXOTAS_IDX_SW_VER_VAL:
        bxotas_sw_ver_request(KE_IDX_GET(src_id), dest_id);
        break;
    case BXOTAS_IDX_STATUS_VAL:
        {
            ke_state_t server_stat = ke_state_get(dest_id);
            struct gattc_read_cfm *cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm,sizeof(bxotas_stat_t));
            cfm->handle = param->handle;
            cfm->length = sizeof(ke_state_t);
            cfm->status = ATT_ERR_NO_ERROR;
            *(ke_state_t *)cfm->value = server_stat;
            ke_msg_send(cfm);
        }
        break;
    default:
        {
            struct gattc_read_cfm* cfm = KE_MSG_ALLOC(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm);
            cfm->handle = param->handle;
            cfm->status = ATT_ERR_APP_ERROR;
            ke_msg_send(cfm);
        }
        break;
    }
    
    return msg_status;
}

static int gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                       struct gattc_write_req_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    uint8_t att_db_idx = bxotas_get_att_db_idx_from_handle(param->handle);
    uint8_t conidx = KE_IDX_GET(src_id);
    struct gattc_write_cfm *cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    cfm->status = ATT_ERR_NO_ERROR;
    switch(att_db_idx)
    {
    case BXOTAS_IDX_FLASH_ERASE_REQ_VAL:
        {
            BX_ASSERT(param->length == sizeof(bxotas_flash_erase_req_t));
            bxotas_flash_erase_req_t flash_erase_req;
            memcpy(&flash_erase_req,param->value,sizeof(bxotas_flash_erase_req_t));
            bxotas_erase_flash(flash_erase_req.total_image_size);
        }
        break;
    case BXOTAS_IDX_UPDATE_INIT_VAL:
        {
            BX_ASSERT(param->length == sizeof(bxotas_update_init_t));
            bxotas_update_init_t update_init;
            memcpy(&update_init,param->value,sizeof(bxotas_update_init_t));
            bxotas_program_request(&update_init,conidx,dest_id);
        }
        break;
    case BXOTAS_IDX_UPDATE_REQ_VAL:
        {
            BX_ASSERT(param->length == sizeof(bxotas_update_req_t));
            bxotas_update_req_t update_req;
            memcpy(&update_req,param->value,sizeof(bxotas_update_req_t));
            bxotas_response_update_req(&update_req,conidx,dest_id);
        }
        break;
    case BXOTAS_IDX_PROGRAM_VAL:
        bxotas_perform_sw_update((uint8_t*)param->value,param->length,conidx,dest_id);
        break;
    case BXOTAS_IDX_BOOT_OVERRIDE_VAL:
        {
            BX_ASSERT(param->length == sizeof(bxotas_boot_override_t));
            bxotas_boot_override_t boot_override;
            memcpy(&boot_override,param->value,sizeof(bxotas_boot_override_t));
            bxotas_last_procedure(&boot_override,conidx, dest_id);
        }
        break;
    default:
        LOG(LOG_LVL_INFO,"invalid,%d\n",att_db_idx);
        cfm->status = ATT_ERR_INVALID_HANDLE;
        break;
    }
    ke_msg_send(cfm);
    
    
    return KE_MSG_CONSUMED;
}

static int bxotas_enable_req_handler(ke_msg_id_t const msgid,
                                       struct bxotas_enable_req const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    if(param->enable&&ke_state_get(dest_id)==BXOTAS_DISABLED)
    {
        ke_state_set(dest_id,BXOTAS_IDLE);
    }
    return KE_MSG_CONSUMED;
}

static int bxotas_sw_ver_cfm_handler(ke_msg_id_t const msgid,
                                       struct bxotas_sw_ver_cfm const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    struct bxotas_env_tag* bxotas_env = PRF_ENV_GET(BXOTAS, bxotas);
    struct gattc_read_cfm *cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, KE_BUILD_ID(TASK_GATTC, bxotas_env->init_device.conidx), dest_id, gattc_read_cfm,sizeof(bxotas_sw_ver_t));
    cfm->handle = bxotas_get_att_db_handle_from_idx(BXOTAS_IDX_SW_VER_VAL);
    cfm->length = sizeof(struct bxotas_sw_ver_cfm);
    cfm->status = ATT_ERR_NO_ERROR;
    memcpy(cfm->value,param,sizeof(struct bxotas_sw_ver_cfm));
    ke_msg_send(cfm);
    return KE_MSG_CONSUMED;
}

static int bxotas_program_cfm_handler(ke_msg_id_t const msgid,
                                       struct bxotas_program_cfm const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    if(param->confirm)
    {
        bxotas_update_prepare(param->conidx, dest_id);
    }
    return KE_MSG_CONSUMED;
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler bxotas_default_state[] =
{
    {GATTC_WRITE_REQ_IND,      (ke_msg_func_t)gattc_write_req_ind_handler},
    {GATTC_READ_REQ_IND,      (ke_msg_func_t)gattc_read_req_ind_handler},
    {BXOTAS_ENABLE_REQ,         (ke_msg_func_t)bxotas_enable_req_handler},
    {BXOTAS_SW_VER_CFM,         (ke_msg_func_t)bxotas_sw_ver_cfm_handler},
    {BXOTAS_PROGRAM_CFM,    (ke_msg_func_t)bxotas_program_cfm_handler},
};

///Specifies the message handlers that are common to all states.
const struct ke_state_handler bxotas_default_handler = KE_STATE_HANDLER(bxotas_default_state);


#endif // BLE_BXOTA_SERVER
/// }@ BXOTASTASK
