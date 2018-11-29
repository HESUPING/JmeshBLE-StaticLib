/*
 * config_relay.h
 *
 *  Created on: 2018��7��27��
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_FOUNDATION_MODELS_CONFIG_RELAY_H_
#define FREERTOS_APP_MESH_FOUNDATION_MODELS_CONFIG_RELAY_H_
#include "mesh_model.h"
#include "mesh_env.h"



typedef struct
{
    mesh_feature_stat_t relay;
    network_transmit_state_t retransmit;
}config_relay_param_t;


void config_relay_get_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));
void config_relay_set_tx(model_base_t *model,config_relay_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));
void config_relay_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);

void config_relay_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_relay_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_relay_status_tx(model_base_t *model,config_relay_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t));



#endif /* FREERTOS_APP_MESH_FOUNDATION_MODELS_CONFIG_RELAY_H_ */
