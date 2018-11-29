/*
 * mesh_gatt_filter.c
 *
 *  Created on: 2018Äê8ÔÂ3ÈÕ
 *      Author: huichen
 */

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
#include "mesh_gatt_error.h"
#include "mesh_gatt_filter.h"
#include "mesh_gatt_proxy.h"
#include "co_endian.h"
/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static bool mesh_proxy_filter_is_has_addr(const proxy_filter_t * p_filter, uint16_t addr);

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 *****************************************************************************************
 * @brief Judge whether the given filter has the given address.
 *
 * @param[in] p_filter Pointer to the Filter to check.
 * @param[in] addr The Address to be judged.
 *
 * @return Whether the address is in the filter true/false.
 *
 *****************************************************************************************
 */
static bool mesh_proxy_filter_is_has_addr(const proxy_filter_t * p_filter, uint16_t addr)
{
    for (uint16_t i = 0; i < p_filter->count; i++)
    {
        if (p_filter->addrs[i] == addr)
        {
            return true;
        }
    }
    return false;
}
/**
 ****************************************************************************************
 * @brief Reset the filter list.Clear all addresses in the filter, and set the filter type to whitelist.
 *
 * @param[in,out] p_filter  Pointer to the Filter to be reset.
 *
 ****************************************************************************************
 */
void mesh_proxy_filter_reset(proxy_filter_t * p_filter)
{
	BX_ASSERT(p_filter);

	p_filter->type  = PROXY_FILTER_TYPE_WHITELIST;
	p_filter->count = 0;
}
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
uint32_t mesh_proxy_set_filter_type(proxy_filter_t * p_filter, proxy_filter_type_t type)
{
    BX_ASSERT(p_filter);

    if (type >= PROXY_FILTER_TYPE_RFU)
    {
        return MESH_GATT_ERROR_INVALID_DATA;
    }

    mesh_proxy_filter_reset(p_filter);
    p_filter->type = type;
    return MESH_GATT_SUCCESS;
}
/**
 *****************************************************************************************
 * @brief Add a list of addresses to the filter.
 *
 * @note Only valid addresses which aren't already present in the filter will be added.
 *
 * @param[in,out] p_filter Pointer to the Filter to be add to.
 * @param[in] p_addrs Pointer to the List of addresses which will to be add.
 * @param[in] addr_count The Number of addresses in @c p_addrs.
 *
 *****************************************************************************************
 */
void mesh_proxy_add_filter_addr(proxy_filter_t * p_filter, const uint16_t * p_addrs, uint16_t addr_count)
{
    BX_ASSERT(p_filter && p_addrs);

    for (uint16_t i = 0;((i < addr_count) && (p_filter->count < MESH_GATT_PROXY_FILTER_ADDR_MAX));i++)
    {
        if ((p_addrs[i] != MESH_ADDR_UNASSIGNED) && (!mesh_proxy_filter_is_has_addr(p_filter, p_addrs[i])))//not invalid addr and not in list
        {
            p_filter->addrs[p_filter->count++] = p_addrs[i];
        }
    }
}
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
void mesh_proxy_remove_filter_addr(proxy_filter_t * p_filter, const uint16_t * p_addrs, uint16_t addr_count)
{
    BX_ASSERT(p_filter && p_addrs);

    /* Replace the address we will remove with the last one, and reduce count by 1,changing the order, but maintaining the set. */
    for (uint16_t i = 0; i < addr_count; i++)
    {
        for (uint16_t j = 0; j < p_filter->count; j++)
        {
            if (p_addrs[i] == p_filter->addrs[j])
            {
                p_filter->addrs[j] = p_filter->addrs[--p_filter->count];
                break;
            }
        }
    }
}
/**
 *****************************************************************************************
 * @brief Fill status data to pdu from the filter.
 *
 * @param[in] p_filter Pointer to the Filter to send status.
 * @param[out] p_addrs Pointer to the array to be fill data.
 *
 *****************************************************************************************
 */
void mesh_proxy_fill_filter_status(const proxy_filter_t * p_filter,uint8_t *p_data)
{
    if (p_data)
    {
    	p_data[0] = PROXY_CONFIG_OPCODE_FILTER_STATUS;//opcode
    	p_data[1] = p_filter->type;//tpye
    	p_data[2] = (p_filter->count>>8)&0xff;//high count
    	p_data[3] = p_filter->count&0xff;//low count
    }
}
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
bool mesh_proxy_filter_addr_is_accept(const proxy_filter_t * p_filter, uint16_t addr)
{
    BX_ASSERT(p_filter);

    bool has_addr = mesh_proxy_filter_is_has_addr(p_filter, addr);

    if (p_filter->type == PROXY_FILTER_TYPE_WHITELIST)
    {
        return has_addr;
    }
    else
    {
        return !has_addr;
    }
}








#endif /* OSAPP_MESH */
/// @} BLE_MESH_GATT_FILTER

