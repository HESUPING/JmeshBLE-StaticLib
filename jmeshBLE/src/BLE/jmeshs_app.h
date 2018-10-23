#ifndef JMESHS_APP_H
#define JMESHS_APP_H

#include "rwip_config.h"
#include "prf_types.h"
#include "prf.h"
#include "jmesh_config.h"

#define JMESHS_APP_IDX_MAX        (1)

enum
{
    JMESHS_APP_IDLE,
    JMESHS_APP_BUSY,
    JMESHS_APP_STATE_MAX
};

typedef enum
{
    APP_DATA_READY,
    APP_LINK_CLOSED,
    APP_STATE_MAX
}app_state_t;

#define JMESHS_APP_DESCRIPTION "JMESH prov desc"
#define APP_DATA_MAX_LENGTH   70

struct jmeshs_app_env_tag {
    prf_env_t prf_env;
    uint16_t start_hdl;
    uint16_t connect_id;
    uint16_t src_id;
    uint16_t dest_id;
    app_state_t app_stat;
};

const struct prf_task_cbs* jmeshs_app_prf_itf_get(void);
extern const struct ke_state_handler jmeshs_app_default_handler;
extern struct jmeshs_app_env_tag jmeshs_app_env;

uint16_t jmeshs_app_get_att_handle(uint8_t att_idx);
//void     jmeshs_send_notification(uint8_t const *data, uint16_t length,enum jmeshs_prov_att_db_handles att_offset);

#endif // JMESHS_H

