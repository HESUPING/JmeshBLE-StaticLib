#include "light_lightness_common.h"
#include "light_lightness_server.h"
#include "generic_common.h"

void handle_light_lightness_six_sec_timer(TimerHandle_t thandle)
{
	generic_valid_field_check_t value;
	inst_parma_t *inst_parma = (inst_parma_t *)pvTimerGetTimerID(thandle);
	light_lightness_server_t *server = (light_lightness_server_t *)inst_parma->inst;

	if(inst_parma->mask == LINEAR_QUEUE)
		value = generic_msg_queue_pop(&server->linear_queue);
	else if(inst_parma->mask == LIGHTNESS_QUEUE)
		value = generic_msg_queue_pop(&server->lightness_queue);
	xTimerDelete(value.Timer,0);	
}

static void handler_light_lightness_transition_timer(TimerHandle_t thandle)
{	
	li_lightness_delay_parma_t  *timer_parma = (li_lightness_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	light_lightness_server_t *server = (light_lightness_server_t *)timer_parma->inst;

	if(timer_parma->type == MSG_LIGHT_LIGHTNESS_SET)
	{
		server->msg_format.pre_lightness_actual = timer_parma->targe_lightness;
	}
	else if(timer_parma->type == MSG_LIGHT_LIGHTNESS_LINEAR_SET)
	{
		server->msg_format.pre_lightness_linear = timer_parma->targe_lightness;
	}
	if(timer_parma->timer_index != 0xff)
	{
		xTimerDelete(server->delay_timer.trans_timer,0);
	}			
	server->server_state = GENERIC_TRANS_IDALE;
}

static void handler_light_lightness_delay_timer(TimerHandle_t thandle)
{
	uint16_t ms;
	li_lightness_delay_parma_t  *timer_parma = (li_lightness_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	light_lightness_server_t *server = (light_lightness_server_t *)timer_parma->inst;
											
	xTimerDelete(server->delay_timer.Timer[timer_parma->timer_index],0);//clear delay timer handler

	server->delay_timer.mask &= ~(1<<timer_parma->timer_index);//clear delay timer mask
	
	if(server->server_state == GENERIC_TRANS_PROCESS)//check server translation status
		xTimerDelete(server->delay_timer.trans_timer,0);	
	ms = generic_transition_time_cal(&timer_parma->trans_time)*100;
	
	server->delay_timer.trans_timer = xTimerCreate("Timer",pdMS_TO_TICKS(ms),pdTRUE,
						(void *)timer_parma,handler_light_lightness_transition_timer);		  //transtion timer
	xTimerStart(server->delay_timer.trans_timer,0);
}



void light_lightness_status_tx(light_lightness_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);
}

void light_lightness_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	access_message_tx_t access_message_tx;

	light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
	
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	
	if(server->server_state == GENERIC_TRANS_PROCESS)
	{
		light_lightness_status_t msg;
		access_message_tx.length = sizeof(generic_onoff_msg_state_t);
		msg.present_lightness = server->msg_format.pre_lightness_actual;
		msg.target_level = server->msg_format.tar_lightness_actual;
		access_message_tx.p_buffer = (uint8_t *)&msg;
	}
	else if(server->server_state == GENERIC_TRANS_IDALE)
	{
		light_lightness_lite_status_t msg;
		access_message_tx.length = sizeof(light_lightness_lite_status_t);
		msg.present_lightness = server->msg_format.pre_lightness_actual;
		access_message_tx.p_buffer = (uint8_t *)&msg;
	}

	//access_message_tx.cb = server->user_cb;
	light_lightness_status_tx(server,&access_message_tx,pdu->base.dst_addr);

}
void light_lightness_set_rx_handler(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length;
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
	
	light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
	
	server->lightness_queue.inst_parma.inst = (void *)server;
	server->lightness_queue.inst_parma.mask = LINEAR_QUEUE;

	
	if(payload_size == sizeof(light_lightness_set_t))
	{
		light_lightness_set_t *p_pdu = (light_lightness_set_t *)pdu->access;
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->lightness_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST, 
				   //and TID fields as the previous message received within the past 6 seconds
		}
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->lightness_queue,msg_field);

		server->linear_queue.date[result].Timer = xTimerCreate("Timer",
					pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->linear_queue.inst_parma,handle_light_lightness_six_sec_timer);             //6s
					
		if(server->linear_queue.date[result].Timer != NULL)
	   		xTimerStart(server->lightness_queue.date[result].Timer,0);
			
        {//this block code is used to transition state

        result =  generic_timer_free_get(server->delay_timer.mask);
        server->delay_timer.delay_parma[result].inst = &server->lightness_queue.inst_parma.inst;
        
     	server->delay_timer.delay_parma[result].targe_lightness = p_pdu->level;
        server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
        server->delay_timer.delay_parma[result].type = MSG_LIGHT_LIGHTNESS_SET;
        server->delay_timer.mask |= (1 << result);
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
			pdMS_TO_TICKS(p_pdu->delay * 5),pdTRUE,(void *)&server->delay_timer.delay_parma[result],handler_light_lightness_delay_timer); 		//5ms * p_pdu->delay
		if(server->delay_timer.Timer[result] != NULL)
			xTimerStart(server->delay_timer.Timer[result],0);
        }
	
	}
	else if(payload_size == sizeof(light_lightness_lite_set_t))
	{
		light_lightness_lite_set_t *p_pdu = (light_lightness_lite_set_t *)pdu->access;
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->lightness_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST,
					//and TID fields as the previous message received within the past 6 seconds
		}
		
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->lightness_queue,msg_field);

	    server->lightness_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->lightness_queue.inst_parma,handler_light_lightness_delay_timer);             //6s
							
		if(server->lightness_queue.date[result].Timer != NULL)
	            	xTimerStart(server->lightness_queue.date[result].Timer,0);
	            	
        {//this block code is used to transition state
	     	result = user_generic_default_transition_time_get();
     		server->delay_timer.delay_parma[result].targe_lightness = p_pdu->level;
			server->delay_timer.delay_parma[result].type = MSG_LIGHT_LIGHTNESS_SET;
     		server->delay_timer.delay_parma[result].inst = (void *)server;
        	if(server->server_status == GENERIC_TRANS_PROCESS)
	        		xTimerDelete(server->delay_timer.trans_timer,0);
	        uint8_t index;
	       	index =  generic_timer_free_get(server->delay_timer.mask);
	        if(result)// use default transition time
	        {
	        	uint16_t ms;
	        	ms = generic_transition_time_cal(&result);
				server->delay_timer.trans_timer = xTimerCreate("Timer",
					pdMS_TO_TICKS(ms),pdTRUE,(void *)&server->delay_timer.delay_parma[index],handler_light_lightness_delay_timer); 		//5ms * p_pdu->delay

				xTimerStart(server->delay_timer.trans_timer,0);
	        }
	        else//immediate exe
	        {
	        	server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_light_lightness_transition_timer((void *)&server->delay_timer.delay_parma[index]);
	        }  
		   
	    }
	
	}

}
void light_lightness_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_lightness_set_rx_handler(elmt,model,pdu);

}
void light_lightness_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{

	light_lightness_set_rx_handler(elmt,model,pdu);
}

void light_lightness_linear_status_tx(light_lightness_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);
}

void light_lightness_linear_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	access_message_tx_t access_message_tx;

	light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
	
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Linear_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	
	if(server->server_state == GENERIC_TRANS_PROCESS)
	{
		light_lightness_linear_status_t msg;
		access_message_tx.length = sizeof(generic_onoff_msg_state_t);
		msg.present_lightness = server->msg_format.pre_lightness_linear;
		msg.target_lightness = server->msg_format.tar_lightness_linear;
		access_message_tx.p_buffer = (uint8_t *)&msg;
	}
	else if(server->server_state == GENERIC_TRANS_IDALE)
	{
		light_lightness_linear_lite_status_t msg;
		access_message_tx.length = sizeof(light_lightness_lite_status_t);
		msg.present_lightness = server->msg_format.pre_lightness_linear;
		access_message_tx.p_buffer = (uint8_t *)&msg;
	}

	//access_message_tx.cb = server->user_cb;
	light_lightness_status_tx(server,&access_message_tx,pdu->base.dst_addr);

}

void light_lightness_linear_set_rx_handler(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
		uint16_t payload_size;
		uint8_t result;
	
		generic_valid_field_check_t msg_field;// store src ,dst ,tid
		payload_size = pdu->base.total_length;
		msg_field.dst = pdu->base.dst_addr;
		msg_field.src = pdu->base.src_addr;
		
		light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
		
		server->linear_queue.inst_parma.inst = (void *)server;
		server->linear_queue.inst_parma.mask = LINEAR_QUEUE;
	
		
		if(payload_size == sizeof(light_lightness_linear_set_t))
		{
			light_lightness_linear_set_t *p_pdu = (light_lightness_linear_set_t *)pdu->access;
			msg_field.tid = p_pdu->tid;
			result = generic_msg_queue_search(&server->linear_queue,msg_field);
			if(result)
			{
				return;//discard this message,because same value for the SRC, DST, 
					   //and TID fields as the previous message received within the past 6 seconds
			}
			
			//this block code is used to  store valid message  within 6 seconds
			result = generic_msg_queue_push(&server->linear_queue,msg_field);
	
			server->linear_queue.date[result].Timer = xTimerCreate("Timer",
						pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->linear_queue.inst_parma,handle_light_lightness_six_sec_timer);			   //6s
						
			if(server->linear_queue.date[result].Timer != NULL)
				xTimerStart(server->linear_queue.date[result].Timer,0);
				
			{//this block code is used to transition state
	
			result =  generic_timer_free_get(server->delay_timer.mask);
			server->delay_timer.delay_parma[result].inst = &server->linear_queue.inst_parma.inst;
			
			server->delay_timer.delay_parma[result].targe_lightness = p_pdu->level;
			server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
			server->delay_timer.delay_parma[result].type = MSG_LIGHT_LIGHTNESS_SET;
			server->delay_timer.mask |= (1 << result);
			server->delay_timer.Timer[result] = xTimerCreate("Timer",
				pdMS_TO_TICKS(p_pdu->delay * 5),pdTRUE,(void *)&server->delay_timer.delay_parma[result],handler_light_lightness_delay_timer);		//5ms * p_pdu->delay
			if(server->delay_timer.Timer[result] != NULL)
				xTimerStart(server->delay_timer.Timer[result],0);
			}
		
		}
		else if(payload_size == sizeof(light_lightness_linear_lite_set_t))
		{
			light_lightness_linear_lite_set_t *p_pdu = (light_lightness_linear_lite_set_t *)pdu->access;
			msg_field.tid = p_pdu->tid;
			result = generic_msg_queue_search(&server->linear_queue,msg_field);
			if(result)
			{
				return;//discard this message,because same value for the SRC, DST,
						//and TID fields as the previous message received within the past 6 seconds
			}
			
			//this block code is used to  store valid message  within 6 seconds
			result = generic_msg_queue_push(&server->linear_queue,msg_field);
	
			server->lightness_queue.date[result].Timer = xTimerCreate("Timer",
								pdMS_TO_TICKS(6000),pdTRUE,(void *)&server->linear_queue.inst_parma,handler_light_lightness_delay_timer);			  //6s
								
			if(server->lightness_queue.date[result].Timer != NULL)
						xTimerStart(server->linear_queue.date[result].Timer,0);
						
			{//this block code is used to transition state
				result = user_generic_default_transition_time_get();
				server->delay_timer.delay_parma[result].targe_lightness = p_pdu->level;
				server->delay_timer.delay_parma[result].type = MSG_LIGHT_LIGHTNESS_SET;
				server->delay_timer.delay_parma[result].inst = (void *)server;
				if(server->server_state == GENERIC_TRANS_PROCESS)
						xTimerDelete(server->delay_timer.trans_timer,0);
				uint8_t index;
				index =  generic_timer_free_get(server->delay_timer.mask);
				if(result)// use default transition time
				{
					uint16_t ms;
					ms = generic_transition_time_cal(&result);
					server->delay_timer.trans_timer = xTimerCreate("Timer",
						pdMS_TO_TICKS(ms),pdTRUE,(void *)&server->delay_timer.delay_parma[index],handler_light_lightness_delay_timer);		//5ms * p_pdu->delay
	
					xTimerStart(server->delay_timer.trans_timer,0);
				}
				else//immediate exe
				{
					server->delay_timer.delay_parma[index].timer_index = 0xff;
					handler_light_lightness_transition_timer((void *)&server->delay_timer.delay_parma[index]);
				}  
			   
			}
		
		}


}

void light_lightness_linear_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_lightness_linear_set_rx_handler(elmt,model,pdu);
}
void light_lightness_linear_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_lightness_linear_set_rx_handler(elmt,model,pdu);
}


void light_lightness_last_status_tx(light_lightness_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);
}

void light_lightness_last_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	access_message_tx_t access_message_tx;
	light_lightness_last_status_t msg;
	light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Last_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);	
	msg.lightness = server->msg_format.lightness_last;
	access_message_tx.p_buffer = (uint8_t *)&msg;
	light_lightness_last_status_tx(server,&access_message_tx,pdu->base.dst_addr);
}

void light_lightness_default_status_tx(light_lightness_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);
}
void light_lightness_default_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	access_message_tx_t access_message_tx;
	light_lightness_default_status_t msg;
	light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Default_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);	
	msg.lightness = server->msg_format.lightness_default;
	access_message_tx.p_buffer = (uint8_t *)&msg;
	light_lightness_last_status_tx(server,&access_message_tx,pdu->base.dst_addr);

}

void light_lightness_range_status_tx(light_lightness_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);
}

void light_lightness_range_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	
	access_message_tx_t access_message_tx;
	light_lightness_range_status_t msg;
	light_lightness_server_t *server = GET_SERVER_MODEL_PTR(light_lightness_server_t,model);
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Lightness_Range_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);	
	
	msg.status_code = server->msg_format.status_code;
	msg.range_min = server->msg_format.range_min;
	msg.range_max = server->msg_format.range_max;
	access_message_tx.p_buffer = (uint8_t *)&msg;
	light_lightness_last_status_tx(server,&access_message_tx,pdu->base.dst_addr);

}


