/*
 * cb_mesh_uart_test_all.h
 *
 *  Created on: 2018-5-23
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_MESH_TEST_CB_MESH_UART_TEST_ALL_H_
#define FREERTOS_APP_MESH_MESH_TEST_CB_MESH_UART_TEST_ALL_H_

///  ---------------   include
#include "mesh_env.h"
#include "mesh_model.h"

//==
extern void cb_config_client_config_appkey_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
//==
extern void cb_config_client_config_model_app_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
//==
extern void cb_config_relay_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
//==
extern void cb_config_composition_data_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);

#endif /* FREERTOS_APP_MESH_MESH_TEST_CB_MESH_UART_TEST_ALL_H_ */
