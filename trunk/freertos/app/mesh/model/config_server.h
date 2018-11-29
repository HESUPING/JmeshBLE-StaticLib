#ifndef CONFIG_SERVER_H_
#define CONFIG_SERVER_H_

#include <stdint.h>
#include "mesh_model.h"
#include "mesh_env.h"
#include "config_server_events_api.h"

typedef struct
{
    uint16_t features;
    uint16_t netkey_idx;
    uint16_t dst_addr;
    uint16_t count;
    uint16_t period;
    uint8_t ttl;
}heartbeat_publication_state_t;

typedef struct
{
    uint16_t src_addr;
    uint16_t dst_addr;
    uint16_t count;
    uint16_t period;
    uint8_t min_hops;
    uint8_t max_hops;
}heartbeat_subscription_state_t;

typedef struct
{
    model_server_base_t model; 
    //net_key_t netkey[CONFIG_SERVER_NETKEY_LIST_MAX];
    //app_key_t appkey[CONFIG_SERVER_APPKEY_LIST_MAX];
    //dev_key_t devkey[CONFIG_SERVER_DEVKEY_LIST_MAX];
    heartbeat_publication_state_t heartbeat_publication;
    heartbeat_subscription_state_t heartbeat_subscription;
}config_server_model_t;

net_key_t *get_netkey_by_global_idx(net_key_t *netkey,uint8_t key_buf_size,uint16_t idx);
bool appkey_is_bound(app_key_t **buf,uint8_t size,app_key_t *appkey);
app_key_t **alloc_bound_appkey_buf(app_key_t **buf,uint8_t size,uint8_t *save_keybuf_index);

void config_appkey_add_rx(mesh_elmt_t *,model_base_t *,access_pdu_rx_t *);
void config_model_publication_set_rx(mesh_elmt_t *,model_base_t *,access_pdu_rx_t *);
void config_model_subscription_update_rx(mesh_elmt_t *,model_base_t *,access_pdu_rx_t *);

void config_model_app_bind_rx(mesh_elmt_t *,model_base_t *,access_pdu_rx_t *);
void config_appkey_update_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_server_add_netkey(uint8_t *netkey,uint16_t netkey_idx,uint8_t *status,dm_async_cb_t cb);
/**
 ****************************************************************************************
 * @brief  config server get network key list.
 *
 * @return Pointer to the net key list data.
 *
 ****************************************************************************************
 */


/**
 * @brief     Call config server action function
 * @param[in] type  Type of event.
 * @param[in] elmt  event parameters element.
 * @param[in] model event parameters model.
 * @param[in] pdu   event parameters contents.
 * @return    void
 */
extern void config_server_evt_act(config_server_evt_type_t type, mesh_elmt_t *elmt,  model_base_t  *model,  access_pdu_rx_t *pdu);


/**/
extern void config_server_unprov_dev_done_cb(uint8_t success , uint8_t reason);


#endif


