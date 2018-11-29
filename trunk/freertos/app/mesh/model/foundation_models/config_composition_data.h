/*
 * config_composition_data.h
 *
 *  Created on: 2018-7-27
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_FOUNDATION_MODELS_CONFIG_COMPOSITION_DATA_H_
#define FREERTOS_APP_MESH_FOUNDATION_MODELS_CONFIG_COMPOSITION_DATA_H_
#include "mesh_model.h"
#include "mesh_env.h"



uint8_t composition_data_get_length(void);
void composition_data_fill_buff(uint8_t * buf , uint8_t verify_length);


void config_composition_data_get_tx(model_base_t *model,uint16_t dst_addr,uint8_t page_number , void (*cb)(access_pdu_tx_t *,uint8_t));
void config_composition_data_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);


void config_composition_data_status_tx_done(access_pdu_tx_t *ptr,uint8_t status);
void config_composition_data_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void config_composition_data_status_tx(model_base_t *model,uint16_t dst_addr,uint8_t page,void (*cb)(access_pdu_tx_t *,uint8_t));









#endif /* FREERTOS_APP_MESH_FOUNDATION_MODELS_CONFIG_COMPOSITION_DATA_H_ */
