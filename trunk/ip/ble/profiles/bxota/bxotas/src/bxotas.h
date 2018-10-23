/**
 ****************************************************************************************
 *
 * @file bxotas.h
 *
 * @brief Header file - BlueX BLE OTA Server.
 *
 * Copyright (C) BlueX Micro 2015-2016
 *
 *
 ****************************************************************************************
 */
 #ifndef BXOTA_H_
 #define BXOTA_H_

/**
 ****************************************************************************************
 * @addtogroup BXOTAS BlueX BLE OTA Server
 * @ingroup BXOTA
 * @brief BlueX BLE OTA Server
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "bxota_common.h"
#include "prf.h"
#include "prf_types.h"
#include "nvds_in_ram.h"
/*
 * DEFINES
 ****************************************************************************************
 */
#define BXOTAS_IDX_MAX 1
#define BLOCK_4K_SECTOR         0x1000

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

enum bxotas_att_db_handles
{
    BXOTAS_IDX_SVC,
        
    BXOTAS_IDX_SW_VER_CHAR,
    BXOTAS_IDX_SW_VER_VAL,

    BXOTAS_IDX_FLASH_ERASE_REQ_CHAR,
    BXOTAS_IDX_FLASH_ERASE_REQ_VAL,
    
    BXOTAS_IDX_UPDATE_INIT_CHAR,
    BXOTAS_IDX_UPDATE_INIT_VAL,
        
    BXOTAS_IDX_UPDATE_REQ_CHAR,
    BXOTAS_IDX_UPDATE_REQ_VAL,

    BXOTAS_IDX_STATUS_CHAR,
    BXOTAS_IDX_STATUS_VAL,
    
    BXOTAS_IDX_PROGRAM_CHAR,
    BXOTAS_IDX_PROGRAM_VAL,

    BXOTAS_IDX_BOOT_OVERRIDE_CHAR,
    BXOTAS_IDX_BOOT_OVERRIDE_VAL,
    
    BXOTAS_IDX_NB
};
 



/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    uint8_t conidx;
    bool  valid;
}initiator_info_t;
typedef struct
{
    uint32_t total_size;
    uint32_t current_size;
}rx_info_t;
typedef struct
{
    uint32_t current_offset;
}program_stat_t;
typedef struct
{
    uint8_t *object_ptr;
}bxotas_nvds_t;
struct bxotas_env_tag
{
    prf_env_t prf_env;
    rx_info_t rx_info;
    program_stat_t program_stat;
    bxotas_nvds_t bxotas_nvds;
    uint16_t start_hdl;
    initiator_info_t init_device;
    ke_state_t state[BXOTAS_IDX_MAX];
};


/*
 * GLOBAL FUNCTION DECLARATIONS
 ****************************************************************************************
 */
 uint8_t bxotas_get_att_db_idx_from_handle(uint16_t handle);

uint16_t bxotas_get_att_db_handle_from_idx(uint8_t idx);

 void bxotas_erase_flash(uint32_t total_image_size);

 void bxotas_perform_sw_update(uint8_t *data,uint16_t length,uint8_t conidx, ke_task_id_t const task_id);
 
 void bxotas_response_update_req(bxotas_update_req_t *update_req,uint8_t conidx, ke_task_id_t const task_id);

 void bxotas_sw_ver_request(uint8_t conidx,ke_task_id_t const task_id);

 void bxotas_program_request(bxotas_update_init_t *update_init,uint8_t conidx,ke_task_id_t const task_id);

void bxotas_update_prepare(uint8_t conidx,ke_task_id_t const task_id);

void bxotas_last_procedure(bxotas_boot_override_t *boot_override,uint8_t conidx,ke_task_id_t const task_id);

void bxotas_nvds_update_done(ke_task_id_t const task_id);

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler bxotas_default_handler;


/// @} BXOTAS
 #endif // BXOTA_H_
 
