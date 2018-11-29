#ifndef JMESH_PROV_SVC_H
#define JMESH_PROV_SVC_H
#include "rwip_config.h"
#include "prf_types.h"
#include "prf.h"
#include "jmesh_config.h"
#include <stdint.h>
#include "../driver/jmesh_driver_config.h"
#include "os_task_jmesh.h"
#include "../jmesh/jmesh_pdu.h"
#include "jmesh_interface.h"
#include"jmesh_ble_callback.h"
#if (JMESH_DRIVER_BX2400)
#include "rwip_task.h" 
#include "prf_types.h"
#include "prf_utils.h"
#include "log.h"
#include "ke_mem.h"
#include "rwip_config.h"
#include "osapp_config.h"
#include "gap.h"
#include "pshare.h"
#include "gattc_task.h"
#include "jmesh_app_svc.h"
#endif
#define NETWORK_TRANSMIT_LENGTH  31
#define SERIAL_TRANSMIT_LENGTH   50
#define BEACON_TRANSMIT_LENGTH 31 
#define PROXY_TRANSMIT_LENGTH  100

#define PROVISION_DATA_MAX_LENGTH   70

enum{
    JMESHS_IDX_MESH_PROVISIONING_DATA_IN_CHAR,
    JMESHS_IDX_MESH_PROVISIONING_DATA_IN_VAL,
	
    JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_CHAR,
    JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_VAL,
    JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_NTF_CFG,

		JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_CHAR,
		JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_VAL,

		JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_CHAR,
		JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_VAL,
		JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_NTF_CFG,

		JMESHS_IDX_MESH_PROXY_CONFIG_IN_CHAR,
		JMESHS_IDX_MESH_PROXY_CONFIG_IN_VAL,

		JMESHS_IDX_MESH_PROXY_CONFIG_OUT_CHAR,
		JMESHS_IDX_MESH_PROXY_CONFIG_OUT_VAL,
		JMESHS_IDX_MESH_PROXY_CONFIG_OUT_NTF_CFG,
		
		JMESHS_IDX_MESH_BEACON_IN_CHAR,
		JMESHS_IDX_MESH_BEACON_IN_VAL,

		JMESHS_IDX_MESH_BEACON_OUT_CHAR,
		JMESHS_IDX_MESH_BEACON_OUT_VAL,
		JMESHS_IDX_MESH_BEACON_OUT_NTF_CFG,
	
		JMESHS_IDX_MESH_MAC_CHAR,
		JMESHS_IDX_MESH_MAC_VAL,
		JMESHS_IDX_MESH_MAC_NTF_CFG,
    JMESHS_IDX_PROV_NB,
};

typedef struct svc_env_st{
		uint16_t start_hdl;
    uint16_t connect_id;
    uint16_t src_id;
    uint16_t dest_id;		
}svc_env_t;
extern struct gattm_att_desc const jmesh_prov_svc_att_db[JMESHS_IDX_PROV_NB];
extern svc_env_t jmesh_prov_svc_env;
extern struct gattm_svc_desc const jmesh_prov_svc_desc;
void jmesh_add_prov_svc();

#endif

