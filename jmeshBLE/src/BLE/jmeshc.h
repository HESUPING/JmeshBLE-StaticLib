#ifndef JMESH_PROFILE_H
#define JMESH_PROFILE_H

#include"prf_types.h"
#include"prf.h"

#define JMESHC_IDX_MAX       (BLE_CONNECTION_MAX)
enum{
    JMESHC_FREE,
    JMESHC_IDLE,
    JMESHC_DISCOVERING,
    JMESHC_BUSY,
    JMESHC_STATE_MAX,
};
struct jmeshc_env_tag
{
    prf_env_t prf_env;
    struct {
        uint8_t svc_nb;
        uint8_t last_char;
    }cache[JMESHC_IDX_MAX];
    ke_state_t state[JMESHC_IDX_MAX];
};
const struct prf_task_cbs* jmeshc_prf_itf_get(void);

extern struct jmeshc_env_tag jmeshc_env;
extern const struct ke_state_handler jmeshc_default_handler;
#endif // _JMESH_PROFILE_H
