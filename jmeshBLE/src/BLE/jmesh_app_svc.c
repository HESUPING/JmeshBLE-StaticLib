#include "jmesh_app_svc.h"

#define JMESH_APP_SVC_UUID {0x04,0xff}
svc_env_t jmesh_app_svc_env;

struct gattm_svc_desc const jmesh_app_svc_desc ={
        .start_hdl = 0,
        .task_id = TASK_ID_AHI,
        .perm = 0,
        .nb_att = JMESHS_IDX_APP_NB,
        .uuid = JMESH_APP_SVC_UUID,
};
struct gattm_att_desc const jmesh_app_svc_att_db[JMESHS_IDX_APP_NB] = {
	
    [JMESHS_IDX_MESH_SERIAL_TRANSMIT_CHAR]    = {{ATT_DECL_CHARACTERISTIC&0xff,ATT_DECL_CHARACTERISTIC>>8}, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_SERIAL_TRANSMIT_VAL]     = {{0x03,0x2b}, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(NTF,ENABLE), 50, PERM(RI, ENABLE)},
    [JMESHS_IDX_MESH_SERIAL_TRANSMIT_NTF_CFG] = {{ATT_DESC_CLIENT_CHAR_CFG&0xff,ATT_DESC_CLIENT_CHAR_CFG>>8}, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},		

    [JMESHS_IDX_MESH_APP_ELEC_CHAR]    = {{ATT_DECL_CHARACTERISTIC&0xff,ATT_DECL_CHARACTERISTIC>>8}, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_APP_ELEC_VAL]     = {{0x04,0x2b}, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(RD, ENABLE)|PERM(NTF,ENABLE), 50, PERM(RI, ENABLE)},
    [JMESHS_IDX_MESH_APP_ELEC_NTF_CFG] = {{ATT_DESC_CLIENT_CHAR_CFG&0xff,ATT_DESC_CLIENT_CHAR_CFG>>8}, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},			
		
    [JMESHS_IDX_MESH_APP_WATER_CHAR]    = {{ATT_DECL_CHARACTERISTIC&0xff,ATT_DECL_CHARACTERISTIC>>8}, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_APP_WATER_VAL]     = {{0x05,0x2b}, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(RD, ENABLE)|PERM(NTF,ENABLE), 50, PERM(RI, ENABLE)},
    [JMESHS_IDX_MESH_APP_WATER_NTF_CFG] = {{ATT_DESC_CLIENT_CHAR_CFG&0xff,ATT_DESC_CLIENT_CHAR_CFG>>8}, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},	
		
    [JMESHS_IDX_MESH_APP_LIGHT_CHAR]    = {{ATT_DECL_CHARACTERISTIC&0xff,ATT_DECL_CHARACTERISTIC>>8}, PERM(RD, ENABLE), 0, 0},
    [JMESHS_IDX_MESH_APP_LIGHT_VAL]     = {{0x06,0x2b}, PERM(WP, NO_AUTH)|PERM(WRITE_REQ, ENABLE)|PERM(RD, ENABLE)|PERM(NTF,ENABLE), 50, PERM(RI, ENABLE)},
    [JMESHS_IDX_MESH_APP_LIGHT_NTF_CFG] = {{ATT_DESC_CLIENT_CHAR_CFG&0xff,ATT_DESC_CLIENT_CHAR_CFG>>8}, PERM(RD, ENABLE)|PERM(WRITE_REQ,ENABLE), 0, 0},	
	        
};
void jmesh_add_app_svc()
{
    struct gattm_add_svc_req *req = AHI_MSG_ALLOC_DYN(GATTM_ADD_SVC_REQ,TASK_ID_GATTM,\
        gattm_add_svc_req,sizeof(jmesh_app_svc_att_db));
    struct gattm_svc_desc *svc = &req->svc_desc;
    memcpy(svc,&jmesh_app_svc_desc,sizeof(jmesh_app_svc_desc));
    memcpy(svc->atts,jmesh_app_svc_att_db,sizeof(jmesh_app_svc_att_db));
    osapp_msg_build_send(req, sizeof(struct gattm_svc_desc)+sizeof(jmesh_app_svc_desc));
}