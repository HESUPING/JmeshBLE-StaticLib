/*
 * cb_mesh_uart_test_all.c
 *
 *  Created on: 2018Äê5ÔÂ23ÈÕ
 *      Author: huichen
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#include "cb_mesh_uart_test_all.h"

#ifdef MESH_TEST_UART_CLENT_SERVER
#include "client_server_uart_test.h"
#endif /* MESH_TEST_UART_CLENT_SERVER */

void cb_config_client_config_appkey_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	// config_appkey_add_tx  done success
	#ifdef MESH_TEST_UART_CLENT_SERVER
		config_client_appkey_add_success_cb(elmt,model,pdu);
	#endif /* MESH_TEST_UART_CLENT_SERVER */

}

void cb_config_client_config_model_app_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	// config_model_app_status_rx  done success
	#ifdef MESH_TEST_UART_CLENT_SERVER
		config_client_model_app_bind_success_cb(elmt,model,pdu);
	#endif /* MESH_TEST_UART_CLENT_SERVER */
}

void cb_config_relay_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	// config_model_app_status_rx  done success
	#ifdef MESH_TEST_UART_CLENT_SERVER
		config_client_config_relay_status_success_cb(elmt,model,pdu);
//	    extern void mesh_debug_uart_test_tx(const void *param,uint16_t len);
//		mesh_debug_uart_test_tx("\1\2\3\4\5",5);
	#endif /* MESH_TEST_UART_CLENT_SERVER */
}

void cb_config_composition_data_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    // config_model_app_status_rx  done success
    #ifdef MESH_TEST_UART_CLENT_SERVER
        extern void mesh_debug_uart_test_tx(const void *param,uint16_t len);
        uint8_t payload_size = pdu->base.total_length - 2 - 4; // opcode=2byte , transmic=4byte
        mesh_debug_uart_test_tx(&pdu->access[2] , payload_size);
    #endif /* MESH_TEST_UART_CLENT_SERVER */
}


#endif /* OSAPP_MESH */
