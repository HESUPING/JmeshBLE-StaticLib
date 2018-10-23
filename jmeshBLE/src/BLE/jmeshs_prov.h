#ifndef JMESHS_PROV_H
#define JMESHS_PROV_H

#include "rwip_config.h"
#include "prf_types.h"
#include "prf.h"
#include "jmesh_config.h"

#define JMESHS_PROV_IDX_MAX        (1)

enum
{
    JMESHS_PROV_IDLE,
    JMESHS_PROV_BUSY,
    JMESHS_PROV_STATE_MAX
};

typedef enum
{
    PROVISION_DATA_READY,
    PROVISION_LINK_CLOSED,
    PROVISION_STATE_MAX
}provision_state_t;

enum
{
    JMESHS_TRANS_REQ_IND = TASK_FIRST_MSG(TASK_ID_JMESHS_PROV),
    JMESHS_TRANS_CFM,

    JMESHS_TRANS_REQ,
    JMESHS_TRANS_RSP,
};
struct jmeshs_trans_req_ind{
    unsigned short handle;
    unsigned char addr[6];
    ke_task_id_t src_id;
    unsigned char len;
    unsigned char *data;
};
struct jmeshs_trans_cfm{
    unsigned short handle;
    unsigned char addr[6];
    ke_task_id_t src_id;
    unsigned char len;
    unsigned char data[5];
};
#define JMESHS_PROV_DESCRIPTION "JMESH prov desc"
#define PROVISION_DATA_MAX_LENGTH   70

struct jmeshs_prov_env_tag {
    prf_env_t prf_env;
    uint16_t start_hdl;
    uint16_t connect_id;
    uint16_t src_id;
    uint16_t dest_id;
    provision_state_t prov_stat;
};

const struct prf_task_cbs* jmeshs_prov_prf_itf_get(void);
extern const struct ke_state_handler jmeshs_prov_default_handler;
extern struct jmeshs_prov_env_tag jmeshs_prov_env;

uint16_t jmeshs_prov_get_att_handle(uint8_t att_idx);
//void     jmeshs_send_notification(uint8_t const *data, uint16_t length,enum jmeshs_prov_att_db_handles att_offset);

#endif // JMESHS_H

