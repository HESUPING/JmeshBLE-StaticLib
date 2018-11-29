#ifndef CONFIG_CLIENT_H_
#define CONFIG_CLIENT_H_
#include "mesh_env.h"
#include "mesh_model.h"
#include "sdk_mesh_config.h"


typedef struct
{
    model_client_base_t model;
 //   net_key_t netkey[CONFIG_CLIENT_NETKEY_LIST_MAX];
 //   app_key_t appkey[CONFIG_CLIENT_APPKEY_LIST_MAX];
  //  dev_key_t devkey[CONFIG_CLIENT_DEVKEY_LIST_MAX];
}config_client_model_t;
typedef struct
{
    uint16_t elmt_addr;
    uint16_t appkey_idx;
    uint32_t model_id;
    bool sig_model;
}config_model_app_bind_param_t;
typedef struct
{
    uint16_t elmt_addr;
    uint16_t publish_addr;
    uint16_t appkey_idx : 12,
                    credential_flag : 1;
    uint8_t publish_ttl;
    publish_period_t period;
    transmit_state_t retransmit;
    uint32_t model_id;
    bool sig_model;
}config_model_publish_param_t;

enum model_subscription_op_mode
{
    Subscription_Add,
    Subscription_Virtual_Addr_Add,
    Subscription_Delete,
    Subscription_Virtual_Addr_Delete,
    Subscription_Overwrite,
    Subscription_Virtual_Addr_Overwrite,
    Subscription_Delete_All,
};
typedef struct
{
    mesh_addr_t subscribe_addr;
    uint16_t elmt_addr;
    uint32_t model_id;
    bool sig_model;
    uint8_t op_mode;
}config_model_subscribe_param_t;





void config_appkey_add_tx(model_base_t *model,app_key_t *appkey,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));
void config_appkey_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_model_app_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_model_app_bind_tx(model_base_t *model,config_model_app_bind_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));
void config_model_publication_set_tx(model_base_t *model,config_model_publish_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));
void config_model_publication_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_model_subscription_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_model_subscription_update_tx(model_base_t *model,config_model_subscribe_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));
void config_model_two_octets_item_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t),uint8_t *payload,uint8_t length,uint16_t opcode_offset);
void config_key_refresh_phase_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);


#endif


