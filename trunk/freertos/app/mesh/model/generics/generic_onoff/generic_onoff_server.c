#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "access.h"
#include "sig_msg.h"
#include "generic_default_transition_time.h"
#include "generic_onoff_server.h"
#include "generic_onoff_client.h"
#include "generic_onoff_common.h"
#include "generic_level_server.h"
#include "generic_common.h"

static void generic_onoff_status_tx_done(access_pdu_tx_t *pdu,uint8_t status)
{
    LOG(3,"generic_onoff_status_tx_done\n");
}

static void handle_generic_onoff_six_sec_timer(TimerHandle_t thandle)
{
    LOG(3,"handle_generic_onoff_six_sec_timer\n");
    generic_onoff_server_t *server = (generic_onoff_server_t *)pvTimerGetTimerID(thandle);
	generic_valid_field_check_t value;
	LOG(3,"generic_onoff_server_t *server=0x%x\n",server);
	value = generic_msg_queue_pop(&server->onoff_queue);
	xTimerDelete(value.Timer,0);
	LOG(3,"TimerHandle_t=0x%x,value.Timer=0x%x\n",thandle,value.Timer);
}

void generic_onoff_status_publish(generic_onoff_server_t *server,access_message_tx_t *p_tx)
{

}
void generic_onoff_status_tx(generic_onoff_server_t *server,uint16_t dst_addr)
{
    access_message_tx_t access_message_tx;
    generic_onoff_msg_state_t msg1;
    generic_onoff_msg_default_state_t msg2;
    
	if(server->server_state == GENERIC_TRANS_PROCESS)
	{
		access_message_tx.length = sizeof(generic_onoff_msg_state_t);
		
		msg1.present_onoff = server->message_format.present_onoff;
		msg1.target_onoff = server->message_format.target_onoff;
		//TODO
		msg1.remaining_time = server->message_format.remaining_time;
		
		access_message_tx.p_buffer = (uint8_t *)&msg1;
	}
	else if(server->server_state == GENERIC_TRANS_IDALE)
	{
		access_message_tx.length = sizeof(generic_onoff_msg_default_state_t);
		
		msg2.present_onoff = server->message_format.present_onoff;
		access_message_tx.p_buffer = (uint8_t *)&msg2;
	}
	
	access_message_tx.opcode =  TWO_OCTETS_OPCODE_GEN(GENERIC_ONOFF_OPCODE_OFFSET,Generic_OnOff_Status);
	
	access_message_tx.cb = generic_onoff_status_tx_done;
	
	access_model_reply(server->model.base.elmt,&server->model.base,&access_message_tx,dst_addr);
}

void onoff_server_off_action(generic_onoff_server_t *server)
{
	if(server->message_format.target_onoff == 0)
	{
	    //user callback
	    mesh_model_evt_t evt;
	    evt.type = ONOFF_MODEL_EVT_SET;
	    evt.params.onoff_set.target_state = server->message_format.target_onoff;
	    server->cb(&evt);
	    //state change
		server->message_format.present_onoff = server->message_format.target_onoff;
	}
	server->server_state = GENERIC_TRANS_PROCESS;
}

void onoff_server_on_action(generic_onoff_server_t *server)
{
	if(server->message_format.target_onoff == 1)
	{
        //user callback
        mesh_model_evt_t evt;
        evt.type = ONOFF_MODEL_EVT_SET;
        evt.params.onoff_set.target_state = server->message_format.target_onoff;
        server->cb(&evt);
        //state change
		server->message_format.present_onoff = 1;
	}
}
static void handler_generic_onoff_transition_timer(TimerHandle_t thandle)
{	
    LOG(3,"handler_generic_onoff_transition_timer\n");
	ger_onoff_delay_parma_t  *timer_parma = (ger_onoff_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	generic_onoff_server_t *server = (generic_onoff_server_t *)timer_parma->inst;

    onoff_server_off_action(server);

	if(timer_parma->timer_index != 0xff)
	{
		xTimerDelete(server->delay_timer.trans_timer,0);
	}			
	server->server_state = GENERIC_TRANS_IDALE;
}

static void handler_generic_onoff_delay_timer(TimerHandle_t thandle)
{
    LOG(3,"handler_generic_onoff_delay_timer\n");
	uint32_t ms,ticks;
	ger_onoff_delay_parma_t  *timer_parma = (ger_onoff_delay_parma_t *)pvTimerGetTimerID(thandle);
	LOG(3,"ger_onoff_delay_parma_t  *timer_parma=0x%x\n",timer_parma);
	generic_onoff_server_t *server = (generic_onoff_server_t *)timer_parma->inst;
	LOG(3,"generic_onoff_server_t *server=0x%x\n",server);
	xTimerDelete(server->delay_timer.Timer[timer_parma->timer_index],0);//clear delay timer handler

	server->delay_timer.mask &= ~(1<<timer_parma->timer_index);//clear delay timer mask
	
	if(server->server_state == GENERIC_TRANS_PROCESS)//check server translation status
		xTimerDelete(server->delay_timer.trans_timer,0);
		
	server->message_format.target_onoff = timer_parma->targe;
    onoff_server_on_action(server);

	ms = generic_transition_time_cal(&timer_parma->trans_time);
	ticks=pdMS_TO_TICKS(ms);
	if(ticks == 0) ticks ++;//make sure tick > 0
	LOG(3,"valus=0x%x,trans time = %dms\n",timer_parma->trans_time,ms);
	server->delay_timer.trans_timer = xTimerCreate("Timer",ticks,pdTRUE,
	                    (void *)timer_parma,handler_generic_onoff_transition_timer);		  //transtion timer

	xTimerStart(server->delay_timer.trans_timer,0);
}

void generic_onoff_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_onoff_server_t *server = GET_SERVER_MODEL_PTR(generic_onoff_server_t,model);
    //user callback
    mesh_model_evt_t evt;
    evt.type = ONOFF_MODEL_EVT_GET;
    server->cb(&evt);
    //send status
	generic_onoff_status_tx(server,pdu->base.src_addr);
}


static void generic_onoff_set_handler(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

    LOG(3,"generic_onoff_set_handler\n");
	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length - 2 - 4; // opcode=2byte , transmic=4byte
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
	
	generic_onoff_server_t *server = GET_SERVER_MODEL_PTR(generic_onoff_server_t,model);

	server->onoff_queue.inst_parma.inst = (void *)server;
	if(payload_size == sizeof(generic_onoff_msg_set_t))
	{
	    LOG(3,"generic_onoff_msg_set_t\n");
		generic_onoff_msg_set_t *p_pdu = (generic_onoff_msg_set_t *)(pdu->access + 2);
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->onoff_queue,msg_field);
		if(result)
		{
		    LOG(3,"TID SAME , DISCARD THIS MESSAGE\n");
			return;//discard this message,because same value for the SRC, DST, 
				   //and TID fields as the previous message received within the past 6 seconds
		}
		
		if(p_pdu->onoff > 1)
		{
		    LOG(3,"ERROR ONOFF VALUE\n");
			return;//discard this message,prohibit
		}

		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->onoff_queue,msg_field);

		server->onoff_queue.date[result].Timer = xTimerCreate("Timer",
				pdMS_TO_TICKS(6000),pdFALSE,(void *)server->onoff_queue.inst_parma.inst,handle_generic_onoff_six_sec_timer); //6s
									
		if(server->onoff_queue.date[result].Timer != NULL)
	   		xTimerStart(server->onoff_queue.date[result].Timer,0);
		
	                

			
        {//this block code is used to transition state
		
        result =  generic_timer_free_get(server->delay_timer.mask);
       
        server->delay_timer.delay_parma[result].inst = server->onoff_queue.inst_parma.inst;
     	server->delay_timer.delay_parma[result].targe = p_pdu->onoff;
     	
        server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
        
        server->delay_timer.mask |= (1 << result);
        uint32_t normal_msg_ticks = pdMS_TO_TICKS(p_pdu->delay * 5);
        if(normal_msg_ticks == 0) normal_msg_ticks = 1;
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
		     normal_msg_ticks,pdFALSE,(void *)&server->delay_timer.delay_parma[result],handler_generic_onoff_delay_timer); 		//5ms * p_pdu->delay
		if(server->delay_timer.Timer[result] != NULL)
			xTimerStart(server->delay_timer.Timer[result],0);
        }
	
	}
	else if(payload_size == sizeof(generic_onoff_msg_default_set_t))
	{
	    LOG(3,"generic_onoff_msg_default_set_t\n");
		generic_onoff_msg_default_set_t *p_pdu = (generic_onoff_msg_default_set_t *)(pdu->access + 2);
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->onoff_queue,msg_field);
		if(result)
		{
		    LOG(3,"TID SAME , DISCARD THIS MESSAGE\n");
			return;//discard this message,because same value for the SRC, DST,
					//and TID fields as the previous message received within the past 6 seconds
		}
		
		if(p_pdu->onoff > 1)
		{
		    LOG(3,"ERROR ONOFF VALUE\n");
			return;//discard this message,prohibit
		}

		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->onoff_queue,msg_field);

		server->onoff_queue.date[result].Timer = xTimerCreate("Timer",
						pdMS_TO_TICKS(6000),pdFALSE,(void *)server->onoff_queue.inst_parma.inst,handle_generic_onoff_six_sec_timer); //6s
													
		if(server->onoff_queue.date[result].Timer != NULL)
	            	xTimerStart(server->onoff_queue.date[result].Timer,0);

		
			
        {//this block code is used to transition state
		    if(server->server_state == GENERIC_TRANS_PROCESS)
	        		xTimerDelete(server->delay_timer.trans_timer,0);

	      	//TODO:
	        //result = user_generic_default_transition_time_get();
	        result = 1;
	        uint8_t index;
	       	index =  generic_timer_free_get(server->delay_timer.mask);
     		server->delay_timer.delay_parma[index].targe = p_pdu->onoff;
     		server->delay_timer.delay_parma[index].inst = (void *)server;
     		
     		server->message_format.target_onoff = p_pdu->onoff;
     		onoff_server_on_action(server);
     		
     		if(p_pdu->onoff)
     			server->message_format.present_onoff = p_pdu->onoff;

	        if(result)
	        {
	        	uint32_t ms;
	        	ms = generic_transition_time_cal(&result);
	        	LOG(3,"default trans time = %dms\n",ms);
				server->delay_timer.trans_timer = xTimerCreate("Timer000",
				pdMS_TO_TICKS(ms),pdFALSE,(void *)&server->delay_timer.delay_parma[index],handler_generic_onoff_transition_timer);
				if(server->delay_timer.trans_timer != NULL)
				{
				    xTimerStart(server->delay_timer.trans_timer,portMAX_DELAY);
				}
	        }
	        else
	        {
	        	server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_generic_onoff_transition_timer((void *)&server->delay_timer.delay_parma[index]);
	        }  
		   
	    }
	
	}

}
void generic_onoff_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	LOG(3,"generic_onoff_set_rx\n");
	generic_onoff_set_handler(elmt,model,pdu);
    //send ack
	LOG(3,"mesh_elmt_t *elmt=0x%x,model_base_t *model=0x%x,access_pdu_rx_t *pdu=0x%x,\n",elmt,model,pdu);
    generic_onoff_server_t *server = GET_SERVER_MODEL_PTR(generic_onoff_server_t,model);
	generic_onoff_status_tx(server,pdu->base.src_addr);
}
void generic_onoff_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_onoff_set_handler(elmt,model,pdu);
}


uint32_t generic_onoff_server_state_bound_event(uint8_t type,uint8_t state_type,void *arg)
{
	switch(type)
	{
		case BOUND_SYS:break;
		case BOUND_STATE_CHANGE:
		if(state_type == GENERIC_LEVEL_STATE)
		{
			ger_level_server_bound_data_t *data = (ger_level_server_bound_data_t *)arg;
			generic_onoff_server_t *server = (generic_onoff_server_t *)data->inst;
			if(data->level > 0)
			{
			    
				server->message_format.present_onoff = 1;
			}
			else
			{
			    
				server->message_format.present_onoff = 0;
			}
		}
		break;
		case BOUND_DELETE:break;
	}

	return 1;

}

uint32_t generic_onoff_server_state_bound_req(generic_onoff_server_t *server,ger_onoff_server_state_info_t *state_info)
{

	uint8_t num_cb;
	uint8_t i,result;
	num_cb = server->state_bound.bound_mask ;
	for(i = 0;i < GENERCI_ONOFF_BOUND_HANDLER_MAX;i++)
	{
		if(!((1<<i)&num_cb))
		{
			result =  i;
			break;
		}
	}
	server->state_bound.bound_mask |= (1<<result);
	server->state_bound.inst[result] = state_info->inst;
	server->state_bound.state_bound_cb[result] = state_info->handler;
	server->state_bound.type[result] = state_info->type;

	/*
	server->state_bound.info.handler = generic_onoff_server_state_bound_event;

	server->state_bound.info.inst = (void *)server;

	server->state_bound.info.type = GENERIC_ONOFF_STATE;

	server->state_bound.state_bound_cb[result](BOUND_SYS,0,server,sizeof(generic_onoff_server_t));*/
	return 1;
	
}


uint32_t generic_onoff_server_state_bound_change(generic_onoff_server_t *server,uint8_t type,uint8_t state_type,void *arg)
{
	uint8_t i;
	ger_onoff_server_bound_data_t bound_data;
	//TODO:
	//bound_data.onoff = server->message_format.present_onoff;
	
	for(i = 0;i < GENERCI_ONOFF_BOUND_HANDLER_MAX;i++)
	{
		if((1<<i)&server->state_bound.bound_mask)
		{
			bound_data.inst = server->state_bound.inst[i];
			server->state_bound.state_bound_cb[i](type,state_type,(void *)&bound_data);
		}
	}

	return 1;
}



#endif

