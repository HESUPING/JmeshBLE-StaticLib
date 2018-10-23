#include "jmeshs_app_task.h"

///received data read require from gatt client
static int gattc_read_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    struct gattc_read_cfm* cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, JMESHS_APP_DESCRIPTION);
    if (param->handle == jmeshs_app_env.start_hdl+JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_VAL) {
        cfm->status = ATT_ERR_NO_ERROR;
        //cfm->length = gattc_get_appisioning_data(cfm->value);
        strcpy(cfm->value, "gattc read req feedback");
        cfm->length = 4;
    }
    else {
        cfm->status = ATT_ERR_READ_NOT_PERMITTED;
    }
    cfm->handle = param->handle;
    ke_msg_send(cfm);
    
    return KE_MSG_CONSUMED;
}

void jmesh_connect_num_answer(unsigned char id, unsigned short length, unsigned char *data);

static int gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                       struct gattc_write_req_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{

		struct gattc_write_cfm* cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
		cfm->handle = param->handle;
		cfm->status = ATT_ERR_NO_ERROR;
		ke_msg_send(cfm);
		LOG(LOG_LVL_INFO,"param gattc_write_ind:%d,%d,%s\n", param->length, param->handle, param->value);
		//driver_gatt_recv_cb(KE_IDX_GET(src_id),param->handle,param->length,(unsigned char *)param->value);
		//jmesh_connect_num_answer(KE_IDX_GET(src_id),param->length,(unsigned char *)param->value);
    jmesh_ble_gatt_writed_callback(KE_IDX_GET(src_id),param->handle,param->length,(unsigned char *)param->value);
    return KE_MSG_CONSUMED;
}

static int gattc_write_cfm_handler(const ke_msg_id_t msgid, const struct gattc_write_cmd* param,
                                    const ke_task_id_t dest_id, const ke_task_id_t src_id)
{
    return KE_MSG_CONSUMED;
}   
                                        

/// Default State handlers definition
const struct ke_msg_handler jmeshs_app_default_state[] =
{
    {GATTC_READ_REQ_IND,        (ke_msg_func_t)gattc_read_req_ind_handler},
    {GATTC_WRITE_REQ_IND,       (ke_msg_func_t)gattc_write_req_ind_handler},
    {GATTC_WRITE_CFM,           (ke_msg_func_t) gattc_write_cfm_handler},
    
};

///Specifies the message handlers that are common to all states.
const struct ke_state_handler jmeshs_app_default_handler = KE_STATE_HANDLER(jmeshs_app_default_state);
