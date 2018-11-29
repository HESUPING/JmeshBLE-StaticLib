#ifndef MESH_KEY_REFRESH_SERVER_H_
#define MESH_KEY_REFRESH_SERVER_H_
#include "mesh_errors.h"


void net_beacon_kr_handle(uint8_t *network_id, bool key_refresh);
err_t mesh_kr_config_netkey_update(netkey_index_t netkey_index, uint8_t *netkey);
err_t mesh_kr_config_get_phase(netkey_index_t netkey_index, mesh_key_refresh_phase_t  * p_phase);
err_t mesh_kr_config_netkey_phase(netkey_index_t netkey_index, mesh_key_refresh_transition_t  transiton);
void config_server_update_netkey_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void handle_config_key_refresh_phase_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void handle_config_key_refresh_phase_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void mesh_kr_output_env(void);



#endif
