#include "light_hsl_setup_server.h"
void light_hsl_default_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_setup_server_t,model);
	msg_light_hsl_default_status_t *msg_light_hsl_default_status = (msg_light_hsl_default_status_t *)(pdu + 2);
	server->light_hsl_server.msg_format.default_hsl_hue = msg_light_hsl_default_status->hue;
	server->light_hsl_server.msg_format.default_hsl_lightness = msg_light_hsl_default_status->lightness;
	server->light_hsl_server.msg_format.default_hsl_saturation = msg_light_hsl_default_status->saturation;

	light_hsl_default_status_tx(server->light_hsl_server,pdu->base.dst_addr);
}
void light_hsl_default_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_setup_server_t,model);
	msg_light_hsl_default_status_t *msg_light_hsl_default_status = (msg_light_hsl_default_status_t *)(pdu + 2);
	server->light_hsl_server.msg_format.default_hsl_hue = msg_light_hsl_default_status->hue;
	server->light_hsl_server.msg_format.default_hsl_lightness = msg_light_hsl_default_status->lightness;
	server->light_hsl_server.msg_format.default_hsl_saturation = msg_light_hsl_default_status->saturation;
}
void light_hsl_range_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_setup_server_t,model);
	msg_light_hsl_range_set_t *msg_light_hsl_range_set = (msg_light_hsl_range_set_t *)(pdu->access + 2);
	server->light_hsl_server.msg_format.status_code = ST_LIGHT_HSL_SUCCESS;

	server->light_hsl_server.msg_format.hue_range_min = msg_light_hsl_range_set->hue_range_min;
	
	server->light_hsl_server.msg_format.hue_range_max = msg_light_hsl_range_set->hue_range_max;

	server->light_hsl_server.msg_format.saturation_range_min = msg_light_hsl_range_set->saturation_range_min;

	server->light_hsl_server.msg_format.saturation_range_max = msg_light_hsl_range_set->saturation_range_max;

	light_hsl_range_status(server->light_hsl_server,pdu->base.dst_addr);
}
void light_hsl_range_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_setup_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_setup_server_t,model);
	msg_light_hsl_range_set_t *msg_light_hsl_range_set = (msg_light_hsl_range_set_t *)(pdu->access + 2);
	server->light_hsl_server.msg_format.status_code = ST_LIGHT_HSL_SUCCESS;

	server->light_hsl_server.msg_format.hue_range_min = msg_light_hsl_range_set->hue_range_min;
	
	server->light_hsl_server.msg_format.hue_range_max = msg_light_hsl_range_set->hue_range_max;

	server->light_hsl_server.msg_format.saturation_range_min = msg_light_hsl_range_set->saturation_range_min;

	server->light_hsl_server.msg_format.saturation_range_max = msg_light_hsl_range_set->saturation_range_max;
}

