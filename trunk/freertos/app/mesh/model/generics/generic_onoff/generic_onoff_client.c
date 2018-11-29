#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "sig_msg.h"
#include "access.h"
#include "mesh_model.h"
#include "mesh_env.h"
#include "generic_common.h"
#include "generic_onoff_client.h"
#include "generic_onoff_common.h"
#include "generic_onoff_client_api.h"
#include "model_servers_events_api.h"



static void generic_onoff_get_tx_done(access_pdu_tx_t *pdu,uint8_t status)
{
    LOG(3,"generic_onoff_get_tx_done\n");
}

static void generic_onoff_set_tx_done(access_pdu_tx_t *pdu,uint8_t status)
{
    LOG(3,"generic_onoff_set_tx_done\n");
}

static void generic_onoff_set_unacknowledged_tx_done(access_pdu_tx_t *pdu,uint8_t status)
{
    LOG(3,"generic_onoff_set_unacknowledged_tx_done\n");
}
static void generic_onoff_status_rx_done(uint8_t status , uint8_t * value)
{
    LOG(3,"generic_onoff_status_rx\n");
    if(status == GENERIC_ONOFF_DEFAULT_STATUS)
    {
        LOG(3,"Present Onoff = 0x%x\n",*(value+2));//82 04 00
    }
    if(status == GENERIC_ONOFF_STATUS)
    {
        LOG(3,"Present Onoff = 0x%x\n", *(value+2));
        LOG(3,"Target Onoff = 0x%x\n",  *(value+3));
        LOG(3,"Remaining Time = 0x%x\n",*(value+4));
    }
}
void generic_onoff_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	//user_mesh_event_t event;
	
	//generic_onoff_client_t *ptr = GET_CLIENT_MODEL_PTR(generic_onoff_client_t,model);
	uint8_t payload_size = pdu->base.total_length - 2 - 4; // opcode=2byte , transmic=4byte
    
	if(payload_size == sizeof(generic_onoff_msg_default_state_t))
	{
		generic_onoff_status_rx_done(GENERIC_ONOFF_DEFAULT_STATUS , (void *)pdu->access);
	}
	else if(payload_size == sizeof(generic_onoff_msg_state_t))
	{
		generic_onoff_status_rx_done(GENERIC_ONOFF_STATUS , (void *)pdu->access);
	}
	
}
void generic_onoff_get_tx(generic_onoff_client_t *client,void *msg , uint8_t msg_length,uint16_t dst_addr)
{
    LOG(3,"generic_onoff_get_tx\n");
    access_message_tx_t p_tx;
    p_tx.opcode = TWO_OCTETS_OPCODE_GEN(GENERIC_ONOFF_OPCODE_OFFSET , Generic_OnOff_Get);
    p_tx.length = msg_length;
    p_tx.p_buffer = msg;
    p_tx.cb=generic_onoff_get_tx_done;
	access_model_send(client->model.base.elmt,&client->model.base,&p_tx,dst_addr);
}
void generic_onoff_set_tx(generic_onoff_client_t *client,void *msg , uint8_t msg_length,uint16_t dst_addr)
{
    LOG(3,"generic_onoff_set_tx\n");
    access_message_tx_t p_tx;
    p_tx.opcode = TWO_OCTETS_OPCODE_GEN(GENERIC_ONOFF_OPCODE_OFFSET , Generic_OnOff_Set);
    p_tx.length = msg_length;
    p_tx.p_buffer = msg;
    p_tx.cb = generic_onoff_set_tx_done;
	access_model_send(client->model.base.elmt,&client->model.base,&p_tx,dst_addr);
}
void generic_onoff_set_unacknowledged_tx(generic_onoff_client_t *client,void *msg , uint8_t msg_length,uint16_t dst_addr)
{
    LOG(3,"generic_onoff_set_unacknowledged_tx\n");
    access_message_tx_t p_tx;
    p_tx.opcode = TWO_OCTETS_OPCODE_GEN(GENERIC_ONOFF_OPCODE_OFFSET , Generic_OnOff_Set_Unacknowledged);
    p_tx.length = msg_length;
    p_tx.p_buffer = msg;
    p_tx.cb = generic_onoff_set_unacknowledged_tx_done;
	access_model_send(client->model.base.elmt,&client->model.base,&p_tx,dst_addr);
}
#endif

