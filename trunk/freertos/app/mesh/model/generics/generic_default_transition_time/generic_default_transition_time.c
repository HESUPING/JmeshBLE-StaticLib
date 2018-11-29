#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "generic_default_transition_time.h"
#include "access.h"
#include "sig_msg.h"
void generic_default_transition_time_status_tx(ger_default_trans_time_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);
}

void generic_default_transition_time_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{

	access_message_tx_t access_message_tx;
	
	ger_default_trans_time_server_t *server = GET_SERVER_MODEL_PTR(ger_default_trans_time_server_t,model);

	access_message_tx.p_buffer = (uint8_t *)&(server->trans_time);

	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Generic_Default_Transition_Time_Status,GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_OFFSET);	

	generic_default_transition_time_status_tx(server,&access_message_tx,pdu->base.dst_addr);
}
void generic_default_transition_time_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	access_message_tx_t access_message_tx;
	
	ger_default_trans_time_server_t *server = GET_SERVER_MODEL_PTR(ger_default_trans_time_server_t,model);

	server->trans_time = *(uint16_t *)pdu->access;

	access_message_tx.p_buffer = (uint8_t *)&server->trans_time;

	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Generic_Default_Transition_Time_Status,GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_OFFSET);	

	generic_default_transition_time_status_tx(server,&access_message_tx,pdu->base.dst_addr);

}
void generic_default_transition_time_unacknowledge_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	ger_default_trans_time_server_t *server = GET_SERVER_MODEL_PTR(ger_default_trans_time_server_t,model);

	server->trans_time = *(uint8_t *)pdu->access;
}

uint8_t user_generic_default_transition_time_get(ger_default_trans_time_server_t *server)
{
	return server->trans_time;
}



#endif

