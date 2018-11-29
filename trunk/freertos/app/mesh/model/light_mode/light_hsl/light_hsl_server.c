#include "light_hsl_server.h"

void light_hsl_msg_complete(access_pdu_tx_t *p_pdu,uint8_t type)
{


}
void handle_light_hsl_six_sec_timer(TimerHandle_t thandle)
{
	generic_valid_field_check_t value;
	inst_parma_t *inst_parma = (inst_parma_t *)pvTimerGetTimerID(thandle);
	light_hsl_server_t *server = (light_hsl_server_t *)inst_parma->inst;
	value = generic_msg_queue_pop(&server->hsl_queue);
	xTimerDelete(value.Timer,0);	
}

static void handler_light_hsl_transition_timer(TimerHandle_t thandle)
{	
	light_hsl_delay_parma_t  *timer_parma = (light_hsl_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	light_hsl_server_t *server = (light_hsl_server_t *)timer_parma->inst;

	server->msg_format.present_hsl_hue = timer_parma->target_hsl_hue;

	server->msg_format.present_hsl_lightness = timer_parma->target_hsl_lightness;

	server->msg_format.present_hsl_saturation = timer_parma->target_hsl_saturation;
	
	if(timer_parma->timer_index != 0xff)
	{
		xTimerDelete(server->delay_timer.trans_timer,0);
	}			
	server->server_state = GENERIC_TRANS_IDALE;
}

static void handler_light_hsl_delay_timer(TimerHandle_t thandle)
{
	uint32_t ms;
	
	light_hsl_delay_parma_t  *timer_parma = (light_hsl_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	light_hsl_server_t *server = (light_hsl_server_t *)timer_parma->inst;
											
	xTimerDelete(server->delay_timer.Timer[timer_parma->timer_index],0);//clear delay timer handler

	server->delay_timer.mask &= ~(1<<timer_parma->timer_index);//clear delay timer mask
	
	if(server->server_state == GENERIC_TRANS_PROCESS)//check server translation status
		xTimerDelete(server->delay_timer.trans_timer,0);

	server->msg_format.target_hsl_hue = timer_parma->target_hsl_hue;

	server->msg_format.target_hsl_lightness = timer_parma->target_hsl_lightness;

	server->msg_format.target_hsl_saturation = timer_parma->target_hsl_saturation;

	server->trans_tick_start = xTaskGetTickCount();
	
	ms = generic_transition_time_cal(&timer_parma->trans_time);
	
	server->delay_timer.trans_timer = xTimerCreate("Timer",pdMS_TO_TICKS(ms),pdTRUE,
						(void *)timer_parma,handler_light_lightness_transition_timer);		  //transtion timer
	xTimerStart(server->delay_timer.trans_timer,0);
}


void light_hsl_status_tx(light_hsl_server_t *server,uint16_t dst_addr)
{
	uint32_t tick;
	access_message_tx_t access_message_tx;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Hsl_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	if(server->server_state == GENERIC_TRANS_PROCESS)
	{
		msg_light_hsl_status_t msg_light_hsl_status;
		
		tick = xTimerGetExpiryTime( server->delay_timer.trans_timer ) - (xTaskGetTickCount() - server->trans_tick_start);
		msg_light_hsl_status.remaining_time = generic_time_transition_cal(tick);
		
		access_message_tx.length = sizeof(msg_light_hsl_status_t);
		msg_light_hsl_status.hsl_lightness = server->msg_format.present_hsl_lightness
		msg_light_hsl_status.hsl_hue = server->msg_format.present_hsl_hue;
		msg_light_hsl_status.hsl_saturation= server->msg_format.present_hsl_saturation;	
		
		access_message_tx.p_buffer = (uint8_t *)&msg_light_hsl_status;
		access_message_tx.cb = light_hsl_msg_complete;
		
	}
	else if(server->server_state == GENERIC_TRANS_IDALE)
	{
		msg_light_hsl_lite_status_t msg_light_hsl_lite_status;
		
		access_message_tx.length = sizeof(msg_light_hsl_status_t);
		msg_light_hsl_lite_status.hsl_lightness = server->msg_format.present_hsl_lightness
		msg_light_hsl_lite_status.hsl_hue = server->msg_format.present_hsl_hue;
		msg_light_hsl_lite_status.hsl_saturation= server->msg_format.present_hsl_saturation;	
		
		access_message_tx.p_buffer = (uint8_t *)&msg_light_hsl_lite_status;
		access_message_tx.cb = light_hsl_msg_complete;

	}	
	access_model_reply(server->model.base.elmt,&server->model.base,&access_message_tx,dst_addr);
}
void light_hsl_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_server_t,model);
	light_hsl_status_tx(server,pdu->base.dst_addr);
}
void light_hsl_set_rx_handle(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length - 2 - 4; // opcode=2byte , transmic=4byte
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
		
	light_hsl_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_server_t,model);

	server->hsl_queue.inst_parma.inst = (void *)server;
	if(payload_size == sizeof(msg_light_hsl_set_t))
	{
			
		msg_light_hsl_set_t *p_pdu = (msg_light_hsl_set_t *)(pdu->access + 2);
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->hsl_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST, 
					   //and TID fields as the previous message received within the past 6 seconds
		}	
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->hsl_queue,msg_field);
		
		server->hsl_queue.date[result].Timer = xTimerCreate("Timer",
				pdMS_TO_TICKS(6000),pdFALSE,(void *)server->hsl_queue.inst,handle_light_hsl_six_sec_timer); //6s
										
		if(server->hsl_queue.date[result].Timer != NULL)
				xTimerStart(server->hsl_queue.date[result].Timer,0);
				
		{//this block code is used to transition state
			
		result =  generic_timer_free_get(server->delay_timer.mask);
		   
		server->delay_timer.delay_parma[result].inst = server->hsl_queue.inst;
		server->delay_timer.delay_parma[result].target_hsl_lightness = p_pdu->hsl_lightness;
		server->delay_timer.delay_parma[result].target_hsl_hue = p_pdu->hsl_hue;
		server->delay_timer.delay_parma[result].target_hsl_saturation = p_pdu->hsl_saturation;
		server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;

		server->delay_timer.mask |= (1 << result);
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
				pdMS_TO_TICKS(p_pdu->delay * 5),pdFALSE,(void *)&server->delay_timer.delay_parma[result],handler_light_hsl_delay_timer);		//5ms * p_pdu->delay
		if(server->delay_timer.Timer[result] != NULL)
				xTimerStart(server->delay_timer.Timer[result],0);
			}
		
		}
	else if(payload_size == sizeof(msg_light_hsl_lite_set_t))
	{
		msg_light_hsl_lite_set_t *p_pdu = (msg_light_hsl_lite_set_t *)(pdu->access + 2);
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->hsl_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST,
					//and TID fields as the previous message received within the past 6 seconds
		}
			
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->hsl_queue,msg_field);

		server->hsl_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdFALSE,(void *)&server->hsl_queue.inst,handle_light_hsl_six_sec_timer); //6s
														
		if(server->hsl_queue.date[result].Timer != NULL)
					xTimerStart(server->hsl_queue.date[result].Timer,0);
			
		{//this block code is used to transition state
		if(server->server_state == GENERIC_TRANS_PROCESS)
				xTimerDelete(server->delay_timer.trans_timer,0);
					
			result = user_generic_default_transition_time_get();
			uint8_t index;
			index =  generic_timer_free_get(server->delay_timer.mask);
			server->delay_timer.delay_parma[result].target_hsl_lightness = p_pdu->hsl_lightness;
			server->delay_timer.delay_parma[result].target_hsl_hue = p_pdu->hsl_hue;
			server->delay_timer.delay_parma[result].target_hsl_saturation = p_pdu->hsl_saturation;
			server->delay_timer.delay_parma[index].inst = (void *)server;
				
			if(result)
			{
				uint16_t ms;
				ms = generic_transition_time_cal(&result);
				server->delay_timer.trans_timer = xTimerCreate("Timer",
				pdMS_TO_TICKS(ms),pdFALSE,(void *)&server->delay_timer.delay_parma[index],handler_light_hsl_transition_timer);		//5ms * p_pdu->delay
			}
			else
			{
				server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_light_hsl_transition_timer((void *)&server->delay_timer.delay_parma[index]);
			}  
			   
		}
		
	}

}
void light_hsl_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{	
	light_hsl_set_rx_handle(elmt,model,pdu);
}
void light_hsl_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_set_rx_handle(elmt,model,pdu);

}
void light_hsl_target_status_tx(light_hsl_server_t *server,uint16_t dst_addr)
{
	uint32_t tick;
	access_message_tx_t access_message_tx;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Hsl_Target_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	if(server->server_state == GENERIC_TRANS_PROCESS)
	{
		msg_light_hsl_target_status_t msg_light_hsl_target_status;
		
		tick = xTimerGetExpiryTime( server->delay_timer.trans_timer ) - (xTaskGetTickCount() - server->trans_tick_start);
		msg_light_hsl_target_status.remaining_time = generic_time_transition_cal(tick);
		
		access_message_tx.length = sizeof(msg_light_hsl_status_t);
		msg_light_hsl_target_status.hsl_lightness = server->msg_format.target_hsl_lightness
		msg_light_hsl_target_status.hsl_hue = server->msg_format.target_hsl_hue;
		msg_light_hsl_target_status.hsl_saturation= server->msg_format.target_hsl_saturation;	
		
		access_message_tx.p_buffer = (uint8_t *)&msg_light_hsl_target_status;
		access_message_tx.cb = light_hsl_msg_complete;
		
	}
	else if(server->server_state == GENERIC_TRANS_IDALE)
	{
		msg_light_hsl_lite_target_status_t msg_light_hsl_lite_target_status;
		
		access_message_tx.length = sizeof(msg_light_hsl_status_t);
		msg_light_hsl_lite_target_status.hsl_lightness_target = server->msg_format.target_hsl_lightness
		msg_light_hsl_lite_target_status.hsl_hue_target = server->msg_format.target_hsl_hue;
		msg_light_hsl_lite_target_status.hsl_saturation_target= server->msg_format.target_hsl_saturation;	
		
		access_message_tx.p_buffer = (uint8_t *)&msg_light_hsl_lite_target_status;
		access_message_tx.cb = light_hsl_msg_complete;
	}	
	access_model_reply(server->model.base.elmt,&server->model.base,&access_message_tx,dst_addr);
}

void light_hsl_target_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	
	light_hsl_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_server_t,model);
	light_hsl_target_status_tx(server,pdu->base.dst_addr);
}

void light_hsl_default_status_tx(light_hsl_server_t *server,uint16_t dst_addr)
{
	access_message_tx_t access_message_tx;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Hsl_Default_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	
	msg_light_hsl_default_status_t msg_light_hsl_default_status;

	msg_light_hsl_default_status.hsl_lightness = server->msg_format.default_hsl_lightness
	msg_light_hsl_default_status.hsl_hue = server->msg_format.default_hsl_hue;
	msg_light_hsl_default_status.hsl_saturation= server->msg_format.default_hsl_saturation;	
		
	access_message_tx.p_buffer = (uint8_t *)&msg_light_hsl_default_status;
	access_message_tx.cb = light_hsl_msg_complete;
		
	
}

void light_hsl_default_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_server_t,model);
	light_hsl_default_status_tx(server,pdu->base.dst_addr);
}

void light_hsl_range_status(light_hsl_server_t *server,uint16_t dst_addr)
{
	access_message_tx_t access_message_tx;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Hsl_Range_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	
	msg_light_hsl_range_status_t msg_light_hsl_range_status;

	msg_light_hsl_range_status.status_code = server->msg_format.status_code
	msg_light_hsl_range_status.hue_range_min = server->msg_format.hue_range_min;
	msg_light_hsl_range_status.hue_range_max = server->msg_format.hue_range_max;
	msg_light_hsl_range_status.saturation_range_min = server->msg_format.saturation_range_min;
	msg_light_hsl_range_status.saturation_range_max = server->msg_format.saturation_range_max;
	access_message_tx.p_buffer = (uint8_t *)&msg_light_hsl_range_status;
	
	access_message_tx.cb = light_hsl_msg_complete;
}
void light_hsl_range_get(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_hsl_server_t *server = GET_SERVER_MODEL_PTR(light_hsl_server_t,model);
	light_hsl_range_status(server,pdu->base.dst_addr);
}

