
#include "rwip_config.h"

#include "jmeshc.h"
#include "jmeshc_task.h"
#include "gap.h"

#include "ke_mem.h"

struct jmeshc_env_tag jmeshc_env;
static uint8_t jmeshc_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void* params)
{
    uint8_t idx;
    //-------------------- allocate memory required for the profile  ---------------------

    struct jmeshc_env_tag* jmeshc_env =
            (struct jmeshc_env_tag* ) ke_malloc(sizeof(struct jmeshc_env_tag), KE_MEM_ATT_DB);

    // allocate DISC required environment variable
    env->env = (prf_env_t*) jmeshc_env;

    jmeshc_env->prf_env.app_task = app_task
            | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
    jmeshc_env->prf_env.prf_task = env->task | PERM(PRF_MI, ENABLE);

    // initialize environment variable
    env->id                     = TASK_ID_JMESHC_PROV;
    env->desc.idx_max           = JMESHC_IDX_MAX;
    env->desc.state             = jmeshc_env->state;
    env->desc.default_handler   = &jmeshc_default_handler;

    for(idx = 0; idx < JMESHC_IDX_MAX ; idx++)
    {
        ke_state_set(KE_BUILD_ID(env->task, idx), JMESHC_FREE);
    }


    return GAP_ERR_NO_ERROR;
}

/**
 ****************************************************************************************
 * @brief Destruction of the DISC module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void jmeshc_destroy(struct prf_task_env* env)
{
    int idx;
    for(idx = 0; idx < JMESHC_IDX_MAX ; idx++)
    {
        jmeshc_env.cache[idx].svc_nb=0;
    }
    env->env = NULL;
}

static void jmeshc_create(struct prf_task_env* env, uint8_t conidx)
{
    ke_state_set(KE_BUILD_ID(env->task, conidx), JMESHC_IDLE);
}

static void jmeshc_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    int idx;
    for(idx = 0; idx < JMESHC_IDX_MAX ; idx++)
    {
        jmeshc_env.cache[idx].svc_nb=0;
    }
}

const struct prf_task_cbs jmeshc_itf =
{
        jmeshc_init,
        jmeshc_destroy,
        jmeshc_create,
        jmeshc_cleanup,
};


const struct prf_task_cbs* jmeshc_prf_itf_get(void)
{
   return &jmeshc_itf;
}

