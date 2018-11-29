/*
 * proxy_s.h
 *
 *  Created on: 2018Äê7ÔÂ31ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_GATT_PROXY_SERVER_PROXY_S_H_
#define FREERTOS_APP_MESH_GATT_PROXY_SERVER_PROXY_S_H_

/**
 ****************************************************************************************
 * @addtogroup BLE_BX2400_MESH_GATT_PROXY BLE mesh gatt proxy
 * @ingroup BLE_BX2400_MESH_GATT
 * @brief defines for BLE mesh gatt proxy
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
#define PROXY_NODE_IDENTITY_HASH_AES_ECB_LEN    16//encrypt data len
#define PROXY_NODE_IDENTITY_HASH_LEN 			8
#define PROXY_NODE_IDENTITY_HASH_PADDING_LEN 	6
#define PROXY_NODE_IDENTITY_HASH_RANDOM_LEN 	8
#define PROXY_NODE_IDENTITY_HASH_SRC_ADDR_LEN 	2
#define PROXY_NODE_IDENTITY_HASH_PARAM_LEN  PROXY_NODE_IDENTITY_HASH_PADDING_LEN \
											+ PROXY_NODE_IDENTITY_HASH_RANDOM_LEN \
											+ PROXY_NODE_IDENTITY_HASH_SRC_ADDR_LEN
/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
	uint8_t *p_identiykey;
	union
	{
		uint8_t p_data[PROXY_NODE_IDENTITY_HASH_PARAM_LEN];
		struct{

			uint8_t padding[PROXY_NODE_IDENTITY_HASH_PADDING_LEN];
			uint8_t random[PROXY_NODE_IDENTITY_HASH_RANDOM_LEN];
			uint8_t source_addr[PROXY_NODE_IDENTITY_HASH_SRC_ADDR_LEN];
		}params;
	}metadata;
}proxy_node_identity_hash_t;
/*
 * ENUMERATIONS
 ****************************************************************************************
 */
enum proxy_identification_type
{
    Network_ID_Type = 0,
    Node_Identity_Type,
};

enum proxy_svc_att_db_handles
{
    PROXY_SVC_IDX_IN_CHAR,
    PROXY_SVC_IDX_IN_VAL,
    PROXY_SVC_IDX_OUT_CHAR,
    PROXY_SVC_IDX_OUT_VAL,
    PROXY_SVC_IDX_OUT_NTF_CFG,
    PROXY_SVC_ATT_NUM
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */
extern struct gattm_svc_desc const proxy_svc_desc;

extern struct gattm_att_desc const proxy_svc_att_db[PROXY_SVC_ATT_NUM];



/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief The Mesh Proxy Data In characteristic is used by the client to send Proxy PDUs
 *  (see Section 6.3) to the server.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 *
 ****************************************************************************************
 */
extern void mesh_proxy_data_in(uint16_t conn_handle, const uint8_t * p_data, uint16_t length);
/**
 ****************************************************************************************
 * @brief The Mesh Proxy Data Out characteristic is used by the server to send Proxy PDUs to the client.
 *
 * @param[in] conn_handle  gatt connect handle.
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      he length of write data.
 *
 *
 ****************************************************************************************
 */
extern void mesh_proxy_data_out(uint16_t conn_handle, const uint8_t * p_data, uint16_t length);
/**
 ****************************************************************************************
 * @brief The Mesh Proxy Data Init.
 *
 ****************************************************************************************
 */
extern void mesh_proxy_service_data_init(void);
/**
 ****************************************************************************************
 * @brief The proxy service beacon network id start.
 *
 ****************************************************************************************
 */
extern void proxy_service_beacon_network_id_start(void);
/**
 ****************************************************************************************
 * @brief The proxy beacon node identity start.
 *
 * @param[in] p_identity_key  Pointer to the identity key.
 *
 ****************************************************************************************
 */
extern void proxy_service_beacon_node_identity_start(const uint8_t *p_identity_key);
/**
 ****************************************************************************************
 * @brief The proxy service beacon stop.
 *
 ****************************************************************************************
 */
extern void proxy_service_beacon_stop(void);
/**
 ****************************************************************************************
 * @brief The proxy service beacon restart (adv data not update).
 *
 ****************************************************************************************
 */
extern void proxy_service_beacon_restart(void);
/**
 ****************************************************************************************
 * @brief The proxy read req ind callback.
 *
 ****************************************************************************************
 */
extern void proxy_read_req_ind_callback(struct osapp_svc_helper_s const *svc_helper,ke_task_id_t const src_id,uint16_t att_idx);
/**
 ****************************************************************************************
 * @brief The proxy write req ind callback.
 *
 ****************************************************************************************
 */
extern void proxy_write_req_ind_callback(struct osapp_svc_helper_s const *svc_helper,ke_task_id_t const src_id,uint16_t att_idx,uint16_t offset,uint16_t length,uint8_t const *value);





#endif /* OSAPP_MESH */
/// @} BLE_BX2400_MESH_GATT_PROXY

#endif /* FREERTOS_APP_MESH_GATT_PROXY_SERVER_PROXY_S_H_ */
