#ifndef JMESHS_PROV_TASK_H
#define JMESHS_PROV_TASK_H
#include <stdint.h>
#include "../driver/jmesh_driver_config.h"
#include "jmeshs_prov.h"
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
#endif
enum jmeshs_prov_msg_id
{
    JMESHS_PROV_TRANS_REQ_IND = TASK_FIRST_MSG(TASK_ID_JMESHS_PROV),
    JMESHS_PROV_TRANS_CFM,

    JMESHS_PROV_TRANS_REQ,
    JMESHS_PROV_TRANS_RSP,
};
struct jmeshs_prov_trans_req_ind{
    unsigned short handle;
    unsigned char addr[6];
    ke_task_id_t src_id;
    unsigned char len;
    unsigned char *data;
};
struct jmeshs_prov_trans_cfm{
    unsigned short handle;
    unsigned char addr[6];
    ke_task_id_t src_id;
    unsigned char len;
    unsigned char data[5];
};
#endif // JMESHS_PROV_TASK_H
