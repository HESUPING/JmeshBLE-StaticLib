/**
 ****************************************************************************************
 *
 * @file bxota.c
 *
 * @brief BlueX BLE OTA Implementation.
 *
 * Copyright (C) BlueX Micro 2015-2016
 *
 *
 ****************************************************************************************
 */

 /**
 ****************************************************************************************
 * @addtogroup BXOTAS
 * @{
 ****************************************************************************************
 */

 /*
 * INCLUDE FILES
 ****************************************************************************************
 */
 #include "rwip_config.h"
 #if (BLE_BXOTA_SERVER)
 #include <stddef.h>
 #include "attm.h"
 #include "prf_utils.h"
 #include "prf.h"
 #include "plf.h"
 #include "flash.h"
 #include "bxotas.h"
 #include "ke_mem.h"
 #include "log.h"
 #include "bxotas_task.h"




 /*
 * MACROS
 ****************************************************************************************
 */
#define IMAGE_OFFSET_BASE 				0x1000  //boot ram size
#define IMAGE_LIMIT_OFFSET_IN_BOOT_RAM  0x18
#define FEATURE_OFFSET_IN_IMAGE_HEADER	0x50
#define VALID_BIT_OFFSET_IN_FEATURE		0x00


 /*
 * DECLARATIONS
 ****************************************************************************************
 */
extern uint32_t current_image_base;	//0x0 or image_size_limit
uint32_t ota_image_base = 0;        //opposite part of current_image_base
uint32_t image_size_limit = 0;      //image size max limit , defined in merge.ini , we read from flash bootram.

/*
 * BXOTA ATTRIBUTES
 ****************************************************************************************
 */
 const struct attm_desc bxotas_att_db[BXOTAS_IDX_NB] =
 {
    [BXOTAS_IDX_SVC] = {ATT_DECL_PRIMARY_SERVICE,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_SW_VER_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_SW_VER_VAL] = {ATT_CHAR_BXOTA_SW_VER,PERM(RD,ENABLE)|PERM(RP,NO_AUTH),PERM(RI,ENABLE),sizeof(bxotas_sw_ver_t)},
    [BXOTAS_IDX_FLASH_ERASE_REQ_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_FLASH_ERASE_REQ_VAL] ={ATT_CHAR_BXOTA_FLASH_ERASE_REQ,PERM(WP,NO_AUTH)|PERM(WRITE_REQ,ENABLE),0,sizeof(bxotas_flash_erase_req_t)},
    [BXOTAS_IDX_UPDATE_INIT_CHAR] =  {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_UPDATE_INIT_VAL] = {ATT_CHAR_BXOTA_UPDATE_INIT,PERM(WP,NO_AUTH)|PERM(WRITE_REQ,ENABLE),0,sizeof(bxotas_update_init_t)},
    [BXOTAS_IDX_UPDATE_REQ_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_UPDATE_REQ_VAL] = {ATT_CHAR_BXOTA_UPDATE_REQ,PERM(WP,NO_AUTH)|PERM(WRITE_REQ,ENABLE),0,sizeof(bxotas_update_req_t)},
    [BXOTAS_IDX_STATUS_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_STATUS_VAL] = {ATT_CHAR_BXOTA_STATUS,PERM(RD,ENABLE)|PERM(RP,NO_AUTH),PERM(RI,ENABLE),sizeof(bxotas_stat_t)},
    [BXOTAS_IDX_PROGRAM_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_PROGRAM_VAL] = {ATT_CHAR_BXOTA_PROGRAM,PERM(WP,NO_AUTH)|PERM(WRITE_REQ,ENABLE),0,BXOTA_PROGRAM_MAX_SIZE},
    [BXOTAS_IDX_BOOT_OVERRIDE_CHAR] = {ATT_DECL_CHARACTERISTIC,PERM(RD,ENABLE),0,0},
    [BXOTAS_IDX_BOOT_OVERRIDE_VAL] = {ATT_CHAR_BXOTA_BOOT_OVERRIDE,PERM(WP,NO_AUTH)|PERM(WRITE_REQ,ENABLE),0,sizeof(bxotas_boot_override_t)},
 };

 /*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
static uint8_t bxotas_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void *params)
{
    uint8_t status = attm_svc_create_db(start_hdl, ATT_SVC_BXOTA, NULL, BXOTAS_IDX_NB, NULL, env->task, bxotas_att_db, sec_lvl);
    if(status == ATT_ERR_NO_ERROR)
    {
        struct bxotas_env_tag *bxotas_env = (struct bxotas_env_tag *)ke_malloc(sizeof(struct bxotas_env_tag),KE_MEM_ATT_DB);
        env->env = (prf_env_t *)bxotas_env;
        bxotas_env->init_device.conidx = 0;
        bxotas_env->init_device.valid = false;
        bxotas_env->rx_info.total_size = 0;
        bxotas_env->rx_info.current_size = 0;
        bxotas_env->bxotas_nvds.object_ptr = NULL;
        bxotas_env->start_hdl = *start_hdl;
        bxotas_env->prf_env.app_task = app_task  | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        bxotas_env->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);
        env->id = TASK_ID_BXOTAS;
        env->desc.idx_max = BXOTAS_IDX_MAX;
        env->desc.state = bxotas_env->state;
        env->desc.default_handler = &bxotas_default_handler;

        //read image_size_limit from flash
        flash_read(IMAGE_LIMIT_OFFSET_IN_BOOT_RAM , sizeof(image_size_limit) , (uint8_t*)&image_size_limit);
        LOG(3,"image_size_limit = 0x%x\n" , image_size_limit);
        
        // calc opposite image location
		ota_image_base = current_image_base ? 0 : image_size_limit;
		LOG(3,"current_image_base = 0x%x\n" , current_image_base);
		LOG(3,"ota_image_base = 0x%x\n"     , ota_image_base);

        ke_state_set(env->task,BXOTAS_DISABLED);
    }
    


    return status;
}
static void bxotas_destroy(struct prf_task_env* env)
{
    struct bxotas_env_tag *bxotas_env =(struct bxotas_env_tag *)env->env;

    env->env = NULL;
    ke_free(bxotas_env);
}

static void bxotas_create(struct prf_task_env* env, uint8_t conidx)
{
    /* Nothing to do */
}

static void bxotas_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    /* Nothing to do */
}

static void bxotas_program(uint32_t *prog_offset,uint8_t * data,uint16_t length)
{
    flash_program(*prog_offset,length,data);
    *prog_offset += length;
}

static void bxotas_rx_info_update(bxotas_update_req_t *update_req,struct bxotas_env_tag *bxotas_env,uint8_t conidx,image_section_t section)
{
    if(update_req->section == section && 
        bxotas_env->rx_info.current_size == bxotas_env->rx_info.total_size &&
        bxotas_env->init_device.valid == true &&
        bxotas_env->init_device.conidx == conidx)
    {
        bxotas_env->rx_info.total_size = update_req->total_size;
        bxotas_env->rx_info.current_size = 0;
        if(section == CODE_DATA_SECTION)
        {
			bxotas_env->program_stat.current_offset = ota_image_base + IMAGE_OFFSET_BASE + update_req->offset;
        }
    }else
    {
        LOG(LOG_LVL_WARN,"bxotas_rx_info_update check fail\n");
    }
}



 /*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
const struct prf_task_cbs bxotas_itf =
{
    bxotas_init,
    bxotas_destroy,
    bxotas_create,
    bxotas_cleanup
};
 
 /*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
const struct prf_task_cbs *bxotas_prf_itf_get()
{
    return &bxotas_itf;
}
 
uint8_t bxotas_get_att_db_idx_from_handle(uint16_t handle)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    return handle -bxotas_env->start_hdl;
}

uint16_t bxotas_get_att_db_handle_from_idx(uint8_t idx)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    return bxotas_env->start_hdl + idx;
}

void bxotas_erase_flash(uint32_t total_image_size)
{
    uint8_t sector_num = total_image_size / BLOCK_4K_SECTOR + 2;
    uint32_t offset = ota_image_base + IMAGE_OFFSET_BASE;
    uint8_t i;
    for(i=0;i<sector_num;++i)
    {
        flash_erase(offset,Sector_Erase);//must be sector erase ,cannot erase boot_ram.
        offset += BLOCK_4K_SECTOR;
    }
}


void bxotas_perform_sw_update(uint8_t *data,uint16_t length,uint8_t conidx, ke_task_id_t const task_id)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t server_stat = ke_state_get(task_id);
    BX_ASSERT(length+bxotas_env->rx_info.current_size<=bxotas_env->rx_info.total_size);
    
    switch(server_stat)
    {
    case BXOTAS_RX_CODE_DATA:
        bxotas_env->rx_info.current_size += length;
        bxotas_program(&bxotas_env->program_stat.current_offset, data, length);
        if(bxotas_env->rx_info.current_size==bxotas_env->rx_info.total_size)
        {
            ke_state_set(task_id, BXOTAS_RX_NVDS_SECTION);
        }
        break;
    }
    
}



void bxotas_response_update_req(bxotas_update_req_t *update_req,uint8_t conidx, ke_task_id_t const task_id)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t server_stat = ke_state_get(task_id);
    switch(server_stat)
    {
    case BXOTAS_RX_CODE_DATA:
        bxotas_rx_info_update(update_req,bxotas_env,conidx,CODE_DATA_SECTION);
        break;
    default:
        LOG(LOG_LVL_WARN,"update_req in wrong state:server_state:%d,update_section:%d\n",server_stat,update_req->section);
        break;
    }
    
}

void bxotas_sw_ver_request(uint8_t conidx,ke_task_id_t const task_id)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    ke_msg_send_basic(BXOTAS_SW_VER_REQ_IND,prf_dst_task_get(&bxotas_env->prf_env,conidx),task_id);
}

void bxotas_program_request(bxotas_update_init_t *update_init,uint8_t conidx,ke_task_id_t const task_id)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    struct bxotas_program_req *req = KE_MSG_ALLOC(BXOTAS_PROGRAM_REQ_IND,prf_dst_task_get(&bxotas_env->prf_env,conidx), task_id, bxotas_program_req);
    req->conidx = conidx;
    ke_msg_send(req);
}

void set_ota_image_valid(void)
{
	uint8_t feature_byte;
	flash_read(ota_image_base + IMAGE_OFFSET_BASE + FEATURE_OFFSET_IN_IMAGE_HEADER,sizeof(feature_byte),(void *)&feature_byte);
	feature_byte &= ~(1 << VALID_BIT_OFFSET_IN_FEATURE);
	flash_program(ota_image_base + IMAGE_OFFSET_BASE + FEATURE_OFFSET_IN_IMAGE_HEADER,sizeof(feature_byte),(void *)&feature_byte);
}

void bxotas_last_procedure(bxotas_boot_override_t *boot_override,uint8_t conidx,ke_task_id_t const task_id)
{
	set_ota_image_valid();
    ke_state_set(task_id, BXOTAS_IDLE);
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    ke_msg_send_basic(BXOTAS_PROGRAM_DONE_IND,prf_dst_task_get(&bxotas_env->prf_env,conidx),task_id);
}

void bxotas_update_prepare(uint8_t conidx,ke_task_id_t const task_id)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    bxotas_env->init_device.conidx = conidx;
    bxotas_env->init_device.valid = true;
    bxotas_env->rx_info.current_size = 0;
    bxotas_env->rx_info.total_size = 0;
    ke_state_set(task_id, BXOTAS_RX_CODE_DATA);
}



#endif //BLE_BXOTA_SERVER
 /// @} BXOTAS
 
