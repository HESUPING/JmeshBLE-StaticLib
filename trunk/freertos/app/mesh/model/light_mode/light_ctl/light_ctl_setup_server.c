#include "light_ctl_setup_server.h"

void light_ctl_default_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_setup_server_t,model);
	msg_light_ctl_default_set_t *p_pdu = (light_ctl_setup_server_t *)(pdu->access + 2);
	
	server->light_ctl_server.msg_format.light_ctl_delta_uv_default = p_pdu->ctl_delta_uv;
	server->light_ctl_server.msg_format.light_ctl_lightness_default = p_pdu->ctl_lightness;
	server->light_ctl_server.msg_format.light_ctl_temperature_default = p_pdu->ctl_temperature;

	light_ctl_default_status_tx(server,pdu->base.dst_addr);
}

void light_ctl_default_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	
	light_ctl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_setup_server_t,model);
	msg_light_ctl_default_set_t *p_pdu = (light_ctl_setup_server_t *)(pdu->access + 2);
	
	server->light_ctl_server.msg_format.light_ctl_delta_uv_default = p_pdu->ctl_delta_uv;
	server->light_ctl_server.msg_format.light_ctl_lightness_default = p_pdu->ctl_lightness;
	server->light_ctl_server.msg_format.light_ctl_temperature_default = p_pdu->ctl_temperature;

}
void light_ctl_temperature_range_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_setup_server_t,model);

	msg_light_ctl_temperature_range_set_t *p_pdu = (msg_light_ctl_temperature_range_set_t *)(pdu->access + 2);

	server->light_ctl_server.msg_format.light_ctl_temp_range_status_code = ST_LIGHT_CTL_SUCCESS;
	server->light_ctl_server.msg_format.light_ctl_temp_range_min = p_pdu->range_min;
	server->light_ctl_server.msg_format.light_ctl_temp_range_min = p_pdu->range_max;
	light_ctl_temperature_range_status_tx(server,pdu->base.dst_addr);

}

void light_ctl_temperature_range_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{

	light_ctl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_setup_server_t,model);

	msg_light_ctl_temperature_range_set_t *p_pdu = (msg_light_ctl_temperature_range_set_t *)(pdu->access + 2);

	server->light_ctl_server.msg_format.light_ctl_temp_range_status_code = ST_LIGHT_CTL_SUCCESS;
	server->light_ctl_server.msg_format.light_ctl_temp_range_min = p_pdu->range_min;
	server->light_ctl_server.msg_format.light_ctl_temp_range_min = p_pdu->range_max;
}

