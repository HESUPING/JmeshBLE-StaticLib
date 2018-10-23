#include "jmeshs_app.h"
#include "jmeshs_app_task.h"

const struct attm_desc jmeshs_app_att_db[JMESHS_IDX_APP_NB] = 
{
    [JMESHS_IDX_APP_SVC]                           = {ATT_DECL_PRIMARY_SERVICE, PERM(RD, ENABLE), 0, 0},

    [JMESHS_IDX_MESH_SERIAL_TRANSMIT_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_SERIAL_TRANSMIT_VAL]     = {0x2B03, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), 50},
    [JMESHS_IDX_MESH_SERIAL_TRANSMIT_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},		

    [JMESHS_IDX_MESH_APP_ELEC_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_APP_ELEC_VAL]     = {0x2B04, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), 50},
    [JMESHS_IDX_MESH_APP_ELEC_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},			
		
    [JMESHS_IDX_MESH_APP_WATER_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_APP_WATER_VAL]     = {0x2B05, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), 50},
    [JMESHS_IDX_MESH_APP_WATER_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},	
		
    [JMESHS_IDX_MESH_APP_LIGHT_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_APP_LIGHT_VAL]     = {0x2B06, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), 50},
    [JMESHS_IDX_MESH_APP_LIGHT_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},	
		
};

struct jmeshs_app_env_tag jmeshs_app_env;

static uint8_t jmeshs_app_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void* params)
{
    //------------------ create the attribute database for the profile -------------------

    // Service content flag
    uint32_t cfg_flag;
    // DB Creation Statis
    uint8_t status = ATT_ERR_NO_ERROR;

    // Compute Attribute Table and save it in environment
    cfg_flag = 0xffffffff;
 
		
    status = attm_svc_create_db(start_hdl, 0xff04, (uint8_t *)&cfg_flag,
            JMESHS_IDX_APP_NB, NULL, env->task, &jmeshs_app_att_db[0],
            (sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)));		
    if (status == ATT_ERR_NO_ERROR)
    {
        env->env = (prf_env_t*) &jmeshs_app_env;
        jmeshs_app_env.start_hdl = *start_hdl;
        jmeshs_app_env.prf_env.app_task = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        jmeshs_app_env.prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);

        // initialize environment variable
        env->id                     = TASK_ID_JMESHS_APP;
        env->desc.idx_max           = JMESHS_APP_IDX_MAX;
        env->desc.state             = 0;
        env->desc.default_handler   = &jmeshs_app_default_handler;

        //ke_state_set(KE_BUILD_ID(env->task, 0), JMESHS_APP_IDLE);
    }		
		
    return (status);
}

static void jmeshs_app_destroy(struct prf_task_env* env)
{
    env->env=NULL;
}

static void jmeshs_app_create(struct prf_task_env* env, uint8_t conidx)
{
    jmeshs_app_env.src_id = prf_src_task_get(&(jmeshs_app_env.prf_env), 0);
    jmeshs_app_env.dest_id = KE_BUILD_ID(TASK_GATTC, conidx);
}


static void jmeshs_app_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    /* Nothing to do */
}


const struct prf_task_cbs jmeshs_app_itf =
{
    (prf_init_fnct) jmeshs_app_init,
    jmeshs_app_destroy,
    jmeshs_app_create,
    jmeshs_app_cleanup,
};

const struct prf_task_cbs* jmeshs_app_prf_itf_get(void)
{
   return &jmeshs_app_itf;
}

uint16_t jmeshs_app_get_att_handle(uint8_t att_idx)
{
    uint16_t handle = ATT_INVALID_HDL;
    if (att_idx < JMESHS_IDX_APP_NB)
        handle += att_idx;
    return handle;
}
 
