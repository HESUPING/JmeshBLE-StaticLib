#include "jmeshs_prov.h"
#include "jmeshs_prov_task.h"

#define NETWORK_TRANSMIT_LENGTH  31
#define SERIAL_TRANSMIT_LENGTH   50
#define BEACON_TRANSMIT_LENGTH 31 
#define PROXY_TRANSMIT_LENGTH  100

const struct attm_desc jmeshs_prov_att_db[JMESHS_IDX_PROV_NB] = 
{
    [JMESHS_IDX_PROV_SVC]                           = {ATT_DECL_PRIMARY_SERVICE, PERM(RD, ENABLE), 0, 0},

    [JMESHS_IDX_MESH_PROVISIONING_DATA_IN_CHAR]     = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_PROVISIONING_DATA_IN_VAL]      = {0x2AFE,PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE), PERM(RI, ENABLE), PROVISION_DATA_MAX_LENGTH},
    
    [JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_VAL]     = {0x2AFF, PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), PROVISION_DATA_MAX_LENGTH},
    [JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},
		
    [JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_VAL]     = {0x2B01, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE), PERM(RI, ENABLE), NETWORK_TRANSMIT_LENGTH},
		
    [JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_VAL]     = {0x2B00, PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), NETWORK_TRANSMIT_LENGTH},
    [JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},

    [JMESHS_IDX_MESH_PROXY_CONFIG_IN_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_PROXY_CONFIG_IN_VAL]     = {0x2B02, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE), PERM(RI, ENABLE), PROXY_TRANSMIT_LENGTH},
		
    [JMESHS_IDX_MESH_PROXY_CONFIG_OUT_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_PROXY_CONFIG_OUT_VAL]     = {0x2B03, PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), PROXY_TRANSMIT_LENGTH},
    [JMESHS_IDX_MESH_PROXY_CONFIG_OUT_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},

    [JMESHS_IDX_MESH_BEACON_IN_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_BEACON_IN_VAL]     = {0x2B04, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE), PERM(RI, ENABLE), PROXY_TRANSMIT_LENGTH},
		
    [JMESHS_IDX_MESH_BEACON_OUT_CHAR]    = {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_BEACON_OUT_VAL]     = {0x2B05, PERM(RD, ENABLE)|PERM(NTF,ENABLE), PERM(RI, ENABLE), PROXY_TRANSMIT_LENGTH},
    [JMESHS_IDX_MESH_BEACON_OUT_NTF_CFG] = {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},
		
};

struct jmeshs_prov_env_tag jmeshs_prov_env;

static uint8_t jmeshs_prov_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void* params)
{
    //------------------ create the attribute database for the profile -------------------

    // Service content flag
    uint32_t cfg_flag;
    // DB Creation Statis
    uint8_t status = ATT_ERR_NO_ERROR;

    // Compute Attribute Table and save it in environment
    cfg_flag = 0xffffffff;

    status = attm_svc_create_db(start_hdl, 0xff03, (uint8_t *)&cfg_flag,
            JMESHS_IDX_PROV_NB, NULL, env->task, &jmeshs_prov_att_db[0],
            (sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)));

    //-------------------- allocate memory required for the profile  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
        env->env = (prf_env_t*) &jmeshs_prov_env;
        jmeshs_prov_env.start_hdl = *start_hdl;
        jmeshs_prov_env.prf_env.app_task = app_task
                | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        jmeshs_prov_env.prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);

        // initialize environment variable
        env->id                     = TASK_ID_JMESHS_PROV;
        env->desc.idx_max           = JMESHS_PROV_IDX_MAX;
        env->desc.state             = 0;
        env->desc.default_handler   = &jmeshs_prov_default_handler;

        //ke_state_set(KE_BUILD_ID(env->task, 0), JMESHS_PROV_IDLE);
    }
    return (status);
}

static void jmeshs_prov_destroy(struct prf_task_env* env)
{
    env->env=NULL;
}


static void jmeshs_prov_create(struct prf_task_env* env, uint8_t conidx)
{
    /* Nothing to do */
    jmeshs_prov_env.src_id = prf_src_task_get(&(jmeshs_prov_env.prf_env), 0);
    jmeshs_prov_env.dest_id = KE_BUILD_ID(TASK_GATTC, conidx);
}


static void jmeshs_prov_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    /* Nothing to do */
}


const struct prf_task_cbs jmeshs_prov_itf =
{
    (prf_init_fnct) jmeshs_prov_init,
    jmeshs_prov_destroy,
    jmeshs_prov_create,
    jmeshs_prov_cleanup,
};

const struct prf_task_cbs* jmeshs_prov_prf_itf_get(void)
{
   return &jmeshs_prov_itf;
}

uint16_t jmeshs_prov_get_att_handle(uint8_t att_idx)
{
    uint16_t handle = ATT_INVALID_HDL;
    if (att_idx < JMESHS_IDX_PROV_NB)
        handle += att_idx;
    return handle;
}
 
