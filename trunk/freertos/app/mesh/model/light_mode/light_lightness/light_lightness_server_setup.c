#include "light_lightness_server_setup.h"

void light_lightness_default_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	
	light_lightness_default_set_t *msg =(light_lightness_default_set_t *)pdu->access;
	
	light_lightness_setup_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_setup_server_t,model);
	
	server->light_lightness_server.msg_format.lightness_default = msg->lightness;
	

	// this paragraph is send light lightness default status
	access_message_tx_t access_message_tx;

	light_lightness_default_status_t st_msg;
	
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Default_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);	

	st_msg.lightness = msg->lightness;

	access_message_tx.p_buffer = (uint8_t *)&st_msg;
	
	light_lightness_default_status_tx(server->light_lightness_server,&access_message_tx,pdu->base.dst_addr);


}

void light_lightness_default_set_Unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_lightness_default_set_t *msg =(light_lightness_default_set_t *)pdu->access;
	
	light_lightness_setup_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_setup_server_t,model);
	
	server->light_lightness_server.msg_format.lightness_default = msg->lightness;
	
}

void light_lightness_range_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_lightness_range_set_t *msg =(light_lightness_range_set_t *)pdu->access;
	
	light_lightness_setup_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_setup_server_t,model);

	if(msg->range_min >= msg->range_max)
	{
		server->light_lightness_server.msg_format.status_code = ST_LIGHT_MIN_INVALID
	}
	else
	{
		server->light_lightness_server.msg_format.status_code = ST_LIGHT_SUCCESS;
		server->light_lightness_server.msg_format.range_min = msg->range_min;
		server->light_lightness_server.msg_format.range_max = msg->range_max;
	}
	
	// this paragraph is send light lightness default status
	access_message_tx_t access_message_tx;

	light_lightness_range_status_t st_msg;
	
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Default_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);	
	st_msg.status_code = server->light_lightness_server.msg_format.status_code;
	st_msg.range_min = server->light_lightness_server.msg_format.range_min;
	st_msg.range_max = server->light_lightness_server.msg_format.range_max;
	access_message_tx.p_buffer = (uint8_t *)&st_msg;
	
	light_lightness_range_status_tx(server->light_lightness_server,&access_message_tx,pdu->base.dst_addr);

}

void light_lightness_range_set_Unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_lightness_range_set_t *msg =(light_lightness_range_set_t *)pdu->access;
	
	light_lightness_setup_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_setup_server_t,model);

	if(msg->range_min >= msg->range_min)
	{
		server->light_lightness_server.msg_format.status_code = ST_LIGHT_MIN_INVALID
	}
	else
	{
		server->light_lightness_server.msg_format.status_code = ST_LIGHT_SUCCESS;
		server->light_lightness_server.msg_format.range_min = msg->range_min;
		server->light_lightness_server.msg_format.range_max = msg->range_max;
	}

}


