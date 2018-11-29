#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "generic_default_transition_time.h"
#include "generic_level_server.h"
#include "generic_level_common.h"
#include "generic_common.h"
#include "generic_onoff_server.h"
#include "access.h"
#include "sig_msg.h"


static void send_generic_level_status()
{

}
void handle_generic_level_six_sec_timer(TimerHandle_t thandle)
{
	generic_valid_field_check_t value;
	ger_level_server_t *server = (ger_level_server_t *)pvTimerGetTimerID(thandle);;
	value = generic_msg_queue_pop(&server->level_queue);
	xTimerDelete(value.Timer,0);	
}

static void handler_generic_level_transition_timer(TimerHandle_t thandle)
{	
	ger_level_delay_parma_t  *timer_parma = (ger_level_delay_parma_t *)pvTimerGetTimerID(thandle);;
	
	ger_level_server_t *server = (ger_level_server_t *)timer_parma->inst;

	switch(timer_parma->type)
	{
		case MSG_GENERCI_LEVEL_SET:
			if(timer_parma->timer_index != 0xff)
				xTimerDelete(server->delay_timer.trans_timer,0);
			server->msg_format.present_level = server->msg_format.target_level;
			server->server_state = GENERIC_TRANS_IDALE;
			
			break;
		case MSG_GENERCI_DELTA_SET:
			server->server_state = GENERIC_TRANS_IDALE;
			server->msg_format.present_level = server->delta_queue.delta_init + timer_parma->target_level;
			if(server->msg_format.present_level + timer_parma->target_level > server->upper_limit_level)
			{
				server->msg_format.present_level = server->upper_limit_level;
				
			}
			else if(server->msg_format.present_level + timer_parma->target_level < server->lower_limit_level)
			{
				server->msg_format.present_level = server->lower_limit_level;
				
			}
			if(timer_parma->timer_index != 0xff)
				xTimerDelete(server->delay_timer.trans_timer,0);
			
		case MSG_GENERCI_MOVE_SET:
			if(server->msg_format.present_level + timer_parma->target_level > server->upper_limit_level)
			{
				server->msg_format.present_level = server->upper_limit_level;
				server->server_state = GENERIC_TRANS_IDALE;
				
				xTimerDelete(server->delay_timer.trans_timer,0);
			}
			else if(server->msg_format.present_level + timer_parma->target_level < server->lower_limit_level)
			{
				server->msg_format.present_level = server->lower_limit_level;
				server->server_state = GENERIC_TRANS_IDALE;
				
				xTimerDelete(server->delay_timer.trans_timer,0);
			}
			break;
	}
	
}

static void handler_generic_level_delay_timer(TimerHandle_t thandle)
{
	uint32_t ms;
	ger_level_delay_parma_t  *timer_parma = (ger_level_delay_parma_t *)pvTimerGetTimerID(thandle);;
	
	ger_level_server_t *server = (ger_level_server_t *)timer_parma->inst;
	xTimerDelete(server->delay_timer.Timer[timer_parma->timer_index],0);

	server->delay_timer.mask &= ~(1<<timer_parma->timer_index);//clear delay timer mask
	if(server->server_state == GENERIC_TRANS_PROCESS)
		xTimerDelete(server->delay_timer.trans_timer,0);
		
	ms = generic_transition_time_cal(&timer_parma->trans_time);
	
	server->delay_timer.trans_timer = xTimerCreate("Timer",pdMS_TO_TICKS(ms),pdTRUE,
						(void *)timer_parma,handler_generic_level_transition_timer);		  //transtion timer
						
	xTimerStart(server->delay_timer.trans_timer,0);
}



void generic_level_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	send_generic_level_status();
}
void generic_level_set_rx_handler(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length;
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
	
	ger_level_server_t *server = GET_SERVER_MODEL_PTR(ger_level_server_t,model);
	
	server->level_queue.inst = (void *)server;
	
	if(payload_size == sizeof(generic_level_msg_set_t))
	{
		generic_level_msg_set_t *p_pdu = (generic_level_msg_set_t *)pdu;
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->level_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST, 
				   //and TID fields as the previous message received within the past 6 seconds
		}
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->level_queue,msg_field);

		server->level_queue.date[result].Timer = xTimerCreate("Timer",
					pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->level_queue.inst,handle_generic_level_six_sec_timer);             //6s
					
		if(server->level_queue.date[result].Timer != NULL)
	   		xTimerStart(server->level_queue.date[result].Timer,0);
			
        {//this block code is used to transition state

        result =  generic_timer_free_get(server->delay_timer.mask);
        server->delay_timer.delay_parma[result].inst = &server->level_queue.inst;
     	server->delay_timer.delay_parma[result].target_level = p_pdu->level;
        server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
        server->delay_timer.delay_parma[result].type = MSG_GENERCI_LEVEL_SET;
        server->delay_timer.mask |= (1 << result);
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
			pdMS_TO_TICKS(p_pdu->delay * 5),pdTRUE,(void *)&server->delay_timer.delay_parma[result],handler_generic_level_delay_timer); 		//5ms * p_pdu->delay
		if(server->delay_timer.Timer[result] != NULL)
			xTimerStart(server->delay_timer.Timer[result],0);
        }
	
	}
	else if(payload_size == sizeof(generic_level_msg_default_t))
	{
		generic_level_msg_default_t *p_pdu = (generic_level_msg_default_t *)pdu;
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->level_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST,
					//and TID fields as the previous message received within the past 6 seconds
		}
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->level_queue,msg_field);

	    server->level_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->level_queue.inst,handle_generic_level_six_sec_timer);             //6s
							
		if(server->level_queue.date[result].Timer != NULL)
	            	xTimerStart(server->level_queue.date[result].Timer,0);
	            	
        {//this block code is used to transition state
	     	result = user_generic_default_transition_time_get();
     		server->delay_timer.delay_parma[result].target_level = p_pdu->level;
			server->delay_timer.delay_parma[result].type = MSG_GENERCI_LEVEL_SET;
     		server->delay_timer.delay_parma[result].inst = (void *)server;
        	if(server->server_state == GENERIC_TRANS_PROCESS)
	        		xTimerDelete(server->delay_timer.trans_timer,0);
	        uint8_t index;
	       	index =  generic_timer_free_get(server->delay_timer.mask);
	        if(result)// use default transition time
	        {
	        	uint32_t ms;
	        	ms = generic_transition_time_cal(&result);
				server->delay_timer.trans_timer = xTimerCreate("Timer",
					pdMS_TO_TICKS(ms),pdTRUE,(void *)&server->delay_timer.delay_parma[index],handler_generic_level_transition_timer); 		//5ms * p_pdu->delay

				xTimerStart(server->delay_timer.trans_timer,0);
	        }
	        else//immediate exe
	        {
	        	server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_generic_level_transition_timer((void *)&server->delay_timer.delay_parma[index]);
	        }  
		   
	    }
	
	}
}
void generic_level_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_level_set_rx_handler(elmt,model,pdu);
}

void generic_level_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_level_set_rx_handler(elmt,model,pdu);
}
void generic_delta_set_rx_handler(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length;
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
	
	ger_level_server_t *server = GET_SERVER_MODEL_PTR(ger_level_server_t,model);
	server->delta_queue.inst = (void *)server;
	
	if(payload_size == sizeof(generic_delta_msg_set_t))
	{
		generic_delta_msg_set_t *p_pdu = (generic_delta_msg_set_t *)pdu;
		msg_field.tid = p_pdu->tid;
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->delta_queue,msg_field);
		
	    server->delta_queue.date[result].Timer = xTimerCreate("Timer",
			pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->delta_queue.inst,handle_generic_level_six_sec_timer); 
		
		if(server->delta_queue.date[result].Timer != NULL)
			xTimerStart(server->delta_queue.date[result].Timer,0);
			
		result = generic_msg_queue_search_last(&server->delta_queue,msg_field);
		switch(result)
		{
			case GENERIC_LEVEL_DELTA_TRANSACTING:
				break;	
			case GENERIC_LEVEL_DELTA_TRANSACTION_START:
			{
				server->delta_queue.delta_init = server->msg_format.present_level;
				break;
			}
			case GENERIC_LEVEL_DELTA_TRANSACTION_ABORD:
			{
				return;
			}	
		}							
        {
        //this block code is used to transition state
        result =  generic_timer_free_get(server->delay_timer.mask);
        server->delay_timer.delay_parma[result].inst = &server->delta_queue.inst;
     	server->delay_timer.delay_parma[result].target_level = p_pdu->delta_level;
        server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
        server->delay_timer.delay_parma[result].type = MSG_GENERCI_LEVEL_SET;
        server->delay_timer.mask |= (1 << result);
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
			pdMS_TO_TICKS(p_pdu->delay * 5),pdTRUE,(void *)&server->delay_timer.delay_parma[result],handler_generic_level_delay_timer); 		//5ms * p_pdu->delay

		if(server->delay_timer.Timer[result] != NULL)
			xTimerStart(server->delay_timer.Timer[result],0);
        }
	
	}
	else if(payload_size == sizeof(generic_level_msg_default_t))
	{
		generic_level_msg_default_t *p_pdu = (generic_level_msg_default_t *)pdu;
		msg_field.tid = p_pdu->tid;
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->delta_queue,msg_field);
	
	    server->delta_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->delta_queue.inst,handle_generic_level_six_sec_timer); 
							
		if(server->delta_queue.date[result].Timer != NULL)
	   		xTimerStart(server->delta_queue.date[result].Timer,0);

	   	// this function is used to search last message
		result = generic_msg_queue_search_last(&server->delta_queue,msg_field);
		
		switch(result)
		{
			case GENERIC_LEVEL_DELTA_TRANSACTING:
				break;	
			case GENERIC_LEVEL_DELTA_TRANSACTION_START:
			{
				server->delta_queue.delta_init = server->msg_format.present_level;
				break;
			}
			case GENERIC_LEVEL_DELTA_TRANSACTION_ABORD:
			{
				return;
			}	
		}			
		        	
        {//this block code is used to transition state
        	if(server->server_state == GENERIC_TRANS_PROCESS)
	        		xTimerDelete(server->delay_timer.trans_timer,0);
	      		
	        result = user_generic_default_transition_time_get();
	        uint8_t index;
	       	index =  generic_timer_free_get(server->delay_timer.mask);
     		server->delay_timer.delay_parma[index].target_level = p_pdu->level + server->delta_queue.delta_init;
     		server->delay_timer.delay_parma[index].inst = (void *)server;
     		server->delay_timer.delay_parma[index].type = MSG_GENERCI_LEVEL_SET;
	        if(result)
	        {
	        	uint32_t ms;
	        	ms = generic_transition_time_cal(&result);
				server->delay_timer.trans_timer = xTimerCreate("Timer",
				pdMS_TO_TICKS(ms),pdTRUE,(void *)&server->delay_timer.delay_parma[index],handler_generic_level_transition_timer); 		//5ms * p_pdu->delay
				xTimerStart(server->delay_timer.trans_timer,0);
	        }
	        else
	        {
	        	server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_generic_level_transition_timer((void *)&server->delay_timer.delay_parma[index]);
	        }  
	    }
	}
	
}

void generic_delta_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_delta_set_rx_handler(elmt,model,pdu);
}

void generic_delta_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_delta_set_rx_handler(elmt,model,pdu);
}



void generic_move_set_rx_handler(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length;
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
	
	ger_level_server_t *server =GET_SERVER_MODEL_PTR(ger_level_server_t,model);
	server->level_queue.inst = (void *)server;
	
	if(payload_size == sizeof(generic_move_msg_set_t))
	{
		generic_move_msg_set_t *p_pdu = (generic_move_msg_set_t *)pdu;
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->move_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST, 
				   //and TID fields as the previous message received within the past 6 seconds
		}
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->move_queue,msg_field);
									
	    server->move_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->move_queue.inst,handle_generic_level_six_sec_timer);             //6s

		if(server->move_queue.date[result].Timer != NULL)
	   		xTimerStart(server->move_queue.date[result].Timer,0);	
	   		
        {//this block code is used to transition state

        result =  generic_timer_free_get(server->delay_timer.mask);
        server->delay_timer.delay_parma[result].inst = &server->move_queue.inst;
     	server->delay_timer.delay_parma[result].target_level = p_pdu->delta_level;
        server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
        server->delay_timer.delay_parma[result].type = MSG_GENERCI_MOVE_SET;
        server->delay_timer.mask |= (1 << result);
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
			pdMS_TO_TICKS(p_pdu->delay * 5),pdTRUE,(void *)&server->delay_timer.delay_parma[result],handler_generic_level_delay_timer); 		//5ms * p_pdu->delay
		if(server->delay_timer.Timer[result] != NULL)
			xTimerStart(server->delay_timer.Timer[result],0);
        }
	
	}
	else if(payload_size == sizeof(generic_level_msg_default_t))
	{
		generic_level_msg_default_t *p_pdu = (generic_level_msg_default_t *)pdu;
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->move_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST,
					//and TID fields as the previous message received within the past 6 seconds
		}
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->move_queue,msg_field);

	    server->move_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->move_queue.inst,handle_generic_level_six_sec_timer);             //6s
		if(server->move_queue.date[result].Timer != NULL)
	            	xTimerStart(server->move_queue.date[result].Timer,0);
	            	
        {//this block code is used to transition state
	    if(server->server_state == GENERIC_TRANS_PROCESS)
	        		xTimerDelete(server->delay_timer.trans_timer,0);
	      		
	        result = user_generic_default_transition_time_get();
	        uint8_t index;
	       	index =  generic_timer_free_get(server->delay_timer.mask);
     		server->delay_timer.delay_parma[index].target_level = p_pdu->level;
     		server->delay_timer.delay_parma[index].inst = (void *)server;
     		server->delay_timer.delay_parma[index].type = MSG_GENERCI_MOVE_SET;
     		server->delay_timer.mask |= (1 << result);
	        if(result)
	        {
	        	uint32_t ms;
	        	ms = generic_transition_time_cal(&result);
				server->delay_timer.trans_timer = xTimerCreate("Timer",
					pdMS_TO_TICKS(ms),pdTRUE,(void *)&server->delay_timer.delay_parma[index],handler_generic_level_transition_timer); 		//5ms * p_pdu->delay
				xTimerStart(server->delay_timer.trans_timer, 0);
	        }
	        else
	        {
	        	server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_generic_level_transition_timer((void *)&server->delay_timer.delay_parma[index]);
	        }   	
		}
	}
}

void generic_move_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_move_set_rx_handler(elmt,model,pdu);
}
void generic_move_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	generic_move_set_rx_handler(elmt,model,pdu);
}

uint32_t generic_level_server_state_bound_event(uint8_t type,uint8_t state_type,void *arg)
{
	switch(type)
	{
		case BOUND_SYS:break;
		case BOUND_STATE_CHANGE:
		if(state_type == GENERIC_ONOFF_STATE)
		{
			ger_onoff_server_bound_data_t *data = (ger_onoff_server_bound_data_t *)arg;
			ger_level_server_t *server = (ger_level_server_t *)data->inst;
			if(data->onoff)
			{
				server->msg_format.present_level = server->msg_format.present_level;
			}
			else
			{
				server->msg_format.present_level = 0;
			}
		}
		break;
		case BOUND_DELETE:break;
	}

	return 1;
}

uint32_t generic_level_server_state_bound_req(ger_level_server_t *server,ger_level_server_state_info_t *state_info)
{

	uint8_t num_cb;
	uint8_t i,result;
	//ger_level_server_state_info_t *server_info;
	num_cb = server->state_bound.bound_mask ;
	for(i = 0;i < GENERCI_LEVEL_BOUND_HANDLER_MAX;i++)
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


uint32_t generic_le_server_state_bound_change(ger_level_server_t *server,uint8_t type,uint8_t state_type,void *arg)
{
	uint8_t i;
	ger_level_server_bound_data_t bound_data;
	bound_data.level = server->msg_format.present_level;
	
	for(i = 0;i < GENERCI_LEVEL_BOUND_HANDLER_MAX;i++)
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

