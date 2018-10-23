#include "rwip_config.h"
#include "../../../trunk/ip/ble/profiles/dis/disc/api/disc_task.h"
#include "gap.h"
#include "jmeshc_task.h"
#include "jmeshc.h"
#include "gattc_task.h"
#include "log.h"

#include "ke_mem.h"




static int jmeshc_discover_req_handler(ke_msg_id_t const msgid,
                                   struct jmeshc_discover_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{

    LOG(LOG_LVL_WARN,"jmeshc req\n");
//    prf_disc_svc_send(&(jmeshc_env.prf_env), KE_IDX_GET(dest_id), ATT_SVC_DEVICE_INFO);
    return (KE_MSG_CONSUMED);
}
static int gattc_sdp_svc_ind_handler(ke_msg_id_t const msgid,
                                             struct gattc_sdp_svc_ind const *ind,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    uint8_t conidx = KE_IDX_GET(dest_id);
    int i;
    LOG(LOG_LVL_WARN,"jmeshc ind %d\n",conidx);
    for(i=ind->start_hdl;i<ind->end_hdl;i++){
        LOG(LOG_LVL_WARN,"jmeshc handle:%d,type:%d,handle:%d\n",i,ind->info[i-ind->start_hdl].att_char.att_type,ind->info[i-ind->start_hdl].att_char.handle);
    }


    return (KE_MSG_CONSUMED);
}

static int gattc_cmp_evt_handler(ke_msg_id_t const msgid,
                                struct gattc_cmp_evt const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{


    return (KE_MSG_CONSUMED);
}
static int jmeshc_trans_req_handler(ke_msg_id_t const msgid,
                                    struct disc_rd_char_req const *param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    //
    return (KE_MSG_CONSUMED);
}


static int gattc_read_ind_handler(ke_msg_id_t const msgid,
                                  struct gattc_read_ind const *param,
                                  ke_task_id_t const dest_id,
                                  ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}

const struct ke_msg_handler jmeshc_default_state[] =
{
//    {JMESHC_DISCOVER_REQ,    (ke_msg_func_t)jmeshc_discover_req_handler},
    {JMESHC_TRANS_REQ,       (ke_msg_func_t)jmeshc_trans_req_handler},
    {GATTC_READ_IND,         (ke_msg_func_t)gattc_read_ind_handler},
    {GATTC_SDP_SVC_IND,      (ke_msg_func_t)gattc_sdp_svc_ind_handler},
    {GATTC_CMP_EVT,          (ke_msg_func_t)gattc_cmp_evt_handler},
};

// Specifies the message handlers that are common to all states.
const struct ke_state_handler jmeshc_default_handler = KE_STATE_HANDLER(jmeshc_default_state);

