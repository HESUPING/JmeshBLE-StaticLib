/*
 * mesh_gatt_filter.h
 *
 *  Created on: 2018Äê8ÔÂ3ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_GATT_MESH_GATT_FILTER_H_
#define FREERTOS_APP_MESH_GATT_MESH_GATT_FILTER_H_

/**
 ****************************************************************************************
 * @addtogroup BLE_MESH_GATT_FILTER  BLE Mesh Gatt filter Internal
 * @ingroup BLE_MESH_GATT
 * @brief defines for BLE mesh gatt contral filter
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
/*
 * DEFINES
 ****************************************************************************************
 */
#define MESH_PROXY_CFG_FILTER_STATUS_LENGHT  4


/*
 * ENUMERATIONS
 ****************************************************************************************
 */
typedef enum
{
    PROXY_FILTER_TYPE_WHITELIST,
    PROXY_FILTER_TYPE_BLACKLIST,
    PROXY_FILTER_TYPE_RFU,
} proxy_filter_type_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    uint16_t count;
    uint16_t addrs[MESH_GATT_PROXY_FILTER_ADDR_MAX];
    proxy_filter_type_t type;
} proxy_filter_t;

/*
 * INTERNAL API TYPES
 ****************************************************************************************
 */

/*
 * MACROS
 ****************************************************************************************
 */
/// Macro used to retrieve field


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Reset the filter list.Clear all addresses in the filter, and set the filter type to whitelist.
 *
 * @param[in,out] p_filter  Pointer to the Filter to be reset.
 *
 ****************************************************************************************
 */
extern void mesh_proxy_filter_reset(proxy_filter_t * p_filter);

/**
 ****************************************************************************************
 * @brief  Set the filter type, and first reset the filter.
 *
 * @param[in,out] p_filter  Pointer to the Filter list to be set.
 * @param[in] type Filter type to set.
 *
 * @return The filter type result. (successfully/fail).
 *
 ****************************************************************************************
 */
extern uint32_t mesh_proxy_set_filter_type(proxy_filter_t * p_filter, proxy_filter_type_t type);

/**
 *****************************************************************************************
 * @brief Add a list of addresses to the filter.
 *
 * Only valid addresses which aren't already present in the filter will be added.
 *
 * @param[in,out] p_filter Pointer to the Filter to be add to.
 * @param[in] p_addrs Pointer to the List of addresses which will to be add.
 * @param[in] addr_count The Number of addresses in @c p_addrs.
 *
 *****************************************************************************************
 */
extern void mesh_proxy_add_filter_addr(proxy_filter_t * p_filter, const uint16_t * p_addrs, uint16_t addr_count);

/**
 *****************************************************************************************
 * @brief Remove a list of addresses from the filter.
 *
 * @note Ignores any addresses that aren't in the filter.
 *
 * @param[in,out] p_filter Pointer to the Filter to remove from.
 * @param[in] p_addrs Pointer to the List of addresses which will to be remove.
 * @param[in] addr_count The Number of addresses in @c p_addrs.
 *
 *****************************************************************************************
 */
extern void mesh_proxy_remove_filter_addr(proxy_filter_t * p_filter, const uint16_t * p_addrs, uint16_t addr_count);

/**
 *****************************************************************************************
 * @brief Fill status data to pdu from the filter.
 *
 * @param[in] p_filter Pointer to the Filter to send status.
 * @param[out] p_addrs Pointer to the array to be fill data.
 *
 *****************************************************************************************
 */
extern void mesh_proxy_fill_filter_status(const proxy_filter_t * p_filter,uint8_t *p_data);

/**
 *****************************************************************************************
 * @brief Check whether the given filter accepts the address.
 *
 * @param[in] p_filter Filter to use.
 * @param[in] addr Address to check.
 *
 * @return Whether or not the filter accepts the address.
 *
 *****************************************************************************************
 */
extern bool mesh_proxy_filter_addr_is_accept(const proxy_filter_t * p_filter, uint16_t addr);








#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT_FILTER


#endif /* FREERTOS_APP_MESH_GATT_MESH_GATT_FILTER_H_ */
