/*
 * provisioning_s.h
 *
 *  Created on: 2018Äê8ÔÂ2ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_GATT_PROVISIONING_SERVER_PROVISIONING_S_H_
#define FREERTOS_APP_MESH_GATT_PROVISIONING_SERVER_PROVISIONING_S_H_
/**
 ****************************************************************************************
 * @addtogroup BLE_BX2400_MESH_GATT_PROVISIONING BLE mesh gatt provisioning
 * @ingroup BLE_BX2400_MESH_GATT
 * @brief defines for BLE mesh gatt provisioning
 *
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH

#include "mesh_gatt_cfg.h"
#include "mesh_gatt.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
enum provision_svc_att_db_handles
{
    PROVISION_SVC_IDX_IN_CHAR,
    PROVISION_SVC_IDX_IN_VAL,
    PROVISION_SVC_IDX_OUT_CHAR,
    PROVISION_SVC_IDX_OUT_VAL,
    PROVISION_SVC_IDX_OUT_NTF_CFG,
    PROVISION_SVC_ATT_NUM
};

typedef enum
{
	PROVISIONING_IDLE,
	PROVISIONING_START,
    PROVISIONING_DONE,
}gatt_provisioning_states_t;
/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */
extern struct gattm_svc_desc const provision_svc_desc;

extern struct gattm_att_desc const provision_svc_att_db[PROVISION_SVC_ATT_NUM];


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief The Mesh Provisioning Data In characteristic can be written to send a Proxy PDU message
 *   (see Section 6.3.1) containing Provisioning PDU (see Section 5.3) to the Provisioning Server.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 *
 ****************************************************************************************
 */
extern void mesh_provisioning_data_in(uint16_t conn_handle, const uint8_t * p_data, uint16_t length);
/**
 ****************************************************************************************
 * @brief The Mesh Provisioning Data Out characteristic can be notified to send a Proxy PDU message
 *  containing Provisioning PDU from a Provisioning Server to a Provisioning Client.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 *
 ****************************************************************************************
 */
extern void mesh_provisioning_data_out(uint16_t conn_handle, const uint8_t * p_data, uint16_t length);
/**
 ****************************************************************************************
 * @brief The provision service beacon start.
 *
 * @param[in] dev_uuid  Pointer to the device uuid.
 * @param[in] OOB_info  the OOB info data.
 *
 ****************************************************************************************
 */
extern void provision_service_beacon_start(const uint8_t *dev_uuid,const uint16_t OOB_info);
/**
 ****************************************************************************************
 * @brief The provision service beacon stop.
 *
 ****************************************************************************************
 */
extern void provision_service_beacon_stop(void);
/**
 ****************************************************************************************
 * @brief The provision service beacon restart.
 *
 ****************************************************************************************
 */
extern void provision_service_beacon_restart(void);
/**
 ****************************************************************************************
 * @brief The provision read req ind callback.
 *
 ****************************************************************************************
 */
extern void provision_read_req_ind_callback(struct osapp_svc_helper_s const *svc_helper,ke_task_id_t const src_id,uint16_t att_idx);
/**
 ****************************************************************************************
 * @brief The provision write req ind callback.
 *
 ****************************************************************************************
 */
extern void provision_write_req_ind_callback(struct osapp_svc_helper_s const *svc_helper,ke_task_id_t const src_id,uint16_t att_idx,uint16_t offset,uint16_t length,uint8_t const*value);
/**
 ****************************************************************************************
 * @brief The Mesh Provisioning state set.
 *
 * @param[in] state  Provisioning state. @enum gatt_provisioning_states_t
 *
 ****************************************************************************************
 */
extern void mesh_provisioning_state_set(gatt_provisioning_states_t state);





#endif /* OSAPP_MESH */

/// @} BLE_BX2400_MESH_GATT_PROVISIONING
#endif /* FREERTOS_APP_MESH_GATT_PROVISIONING_SERVER_PROVISIONING_S_H_ */
