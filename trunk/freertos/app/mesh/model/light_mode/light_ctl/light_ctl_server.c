#include "light_ctl_server.h"

void light_ctl_msg_complete(access_pdu_tx_t *p_pdu,uint8_t type)
{


}
void handle_light_ctl_six_sec_timer(TimerHandle_t thandle)
{
	generic_valid_field_check_t value;
	inst_parma_t *inst_parma = (inst_parma_t *)pvTimerGetTimerID(thandle);
	light_ctl_server_t *server = (light_ctl_server_t *)inst_parma->inst;
	value = generic_msg_queue_pop(&server->ctl_queue);
	xTimerDelete(value.Timer,0);	
}

static void handler_light_ctl_transition_timer(TimerHandle_t thandle)
{	
	light_ctl_delay_parma_t  *timer_parma = (light_ctl_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	light_ctl_server_t *server = (light_ctl_server_t *)timer_parma->inst;

	server->msg_format.pre_light_ctl_lightness = timer_parma->target_ctl_lightness;

	server->msg_format.pre_light_ctl_temperature = timer_parma->target_ctl_temperature;

	server->msg_format.pre_light_ctl_delta_uv = timer_parma->target_ctl_delta_uv;
	
	if(timer_parma->timer_index != 0xff)
	{
		xTimerDelete(server->delay_timer.trans_timer,0);
	}			
	server->server_state = GENERIC_TRANS_IDALE;
}

static void handler_light_ctl_delay_timer(TimerHandle_t thandle)
{
	uint32_t ms;
	
	light_ctl_delay_parma_t  *timer_parma = (light_ctl_delay_parma_t *)pvTimerGetTimerID(thandle);
	
	light_ctl_server_t *server = (light_ctl_server_t *)timer_parma->inst;
											
	xTimerDelete(server->delay_timer.Timer[timer_parma->timer_index],0);//clear delay timer handler

	server->delay_timer.mask &= ~(1<<timer_parma->timer_index);//clear delay timer mask
	
	if(server->server_state == GENERIC_TRANS_PROCESS)//check server translation status
		xTimerDelete(server->delay_timer.trans_timer,0);

	server->msg_format.tar_light_ctl_lightness = timer_parma->target_ctl_lightness;

	server->msg_format.tar_light_ctl_temperature = timer_parma->target_ctl_temperature;

	server->msg_format.tar_light_ctl_delta_uv = timer_parma->target_ctl_temperature;

	server->trans_tick_start = xTaskGetTickCount();
	
	ms = generic_transition_time_cal(&timer_parma->trans_time);
	
	server->delay_timer.trans_timer = xTimerCreate("Timer",pdMS_TO_TICKS(ms),pdTRUE,
						(void *)timer_parma,handler_light_lightness_transition_timer);		  //transtion timer
	xTimerStart(server->delay_timer.trans_timer,0);
}

void light_ctl_status_tx(light_ctl_server_t *server,access_message_tx_t *p_tx,uint16_t dst_addr)
{
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);	
}
void light_ctl_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_server_t,model);
	uint32_t tick;
	access_message_tx_t access_message_tx;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Ctl_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	if(server->server_state == GENERIC_TRANS_PROCESS)
	{
		msg_light_ctl_status_t msg_light_ctl_status;
		access_message_tx.length = sizeof(msg_light_ctl_status_t);
		tick = xTimerGetExpiryTime( server->delay_timer.trans_timer ) - (xTaskGetTickCount() - server->trans_tick_start);
		msg_light_ctl_status.remaining_time = generic_time_transition_cal(tick);
		msg_light_ctl_status.present_ctl_lightness = server->msg_format.pre_light_ctl_lightness;
		msg_light_ctl_status.target_ctl_lightness = server->msg_format.tar_light_ctl_lightness;
		msg_light_ctl_status.present_ctl_temperature = server->msg_format.tar_light_ctl_temperature;
		msg_light_ctl_status.target_ctl_temperature = server->msg_format.tar_light_ctl_temperature;
		access_message_tx.p_buffer = (uint8_t *)&msg_light_ctl_status_t;
		access_message_tx.cb = light_ctl_msg_complete;
	}else if(server->server_state == GENERIC_TRANS_IDALE)
	{
		msg_light_ctl_lite_status_t msg_light_ctl_status;
		access_message_tx.length = sizeof(msg_light_ctl_lite_status_t);
		msg_light_ctl_status.present_ctl_lightness = server->msg_format.pre_light_ctl_lightness;
		msg_light_ctl_status.present_ctl_temperature = server->msg_format.tar_light_ctl_temperature;
		access_message_tx.p_buffer = (uint8_t *)&msg_light_ctl_status_t;
		access_message_tx.cb = light_ctl_msg_complete;
	}
	
	light_ctl_status_tx(server,&access_message_tx,pdu->base.dst_addr);

}
void light_ctl_set_rx_handle(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint16_t payload_size;
	uint8_t result;

	generic_valid_field_check_t msg_field;// store src ,dst ,tid
	payload_size = pdu->base.total_length - 2 - 4; // opcode=2byte , transmic=4byte
	msg_field.dst = pdu->base.dst_addr;
	msg_field.src = pdu->base.src_addr;
		
	light_ctl_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_server_t,model);
	
	server->ctl_queue.inst = (void *)server;
	if(payload_size == sizeof(msg_light_ctl_set_t))
	{
			
		msg_light_ctl_set_t *p_pdu = (msg_light_ctl_set_t *)(pdu->access + 2);
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->ctl_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST, 
					   //and TID fields as the previous message received within the past 6 seconds
		}	
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->ctl_queue,msg_field);
		
		server->ctl_queue.date[result].Timer = xTimerCreate("Timer",
				pdMS_TO_TICKS(6000),pdFALSE,(void *)server->ctl_queue.inst,handle_generic_onoff_six_sec_timer); //6s
										
		if(server->ctl_queue.date[result].Timer != NULL)
				xTimerStart(server->ctl_queue.date[result].Timer,0);
				
		{//this block code is used to transition state
			
		result =  generic_timer_free_get(server->delay_timer.mask);
		   
		server->delay_timer.delay_parma[result].inst = server->ctl_queue.inst;
		server->delay_timer.delay_parma[result].target_ctl_lightness = p_pdu->ctl_lightness;
		server->delay_timer.delay_parma[result].target_ctl_temperature = p_pdu->ctl_temperature;
		server->delay_timer.delay_parma[result].target_ctl_delta_uv = p_pdu->ctl_delta_uv;
		server->delay_timer.delay_parma[result].trans_time = p_pdu->trans_time;
	
		server->delay_timer.mask |= (1 << result);
		server->delay_timer.Timer[result] = xTimerCreate("Timer",
				pdMS_TO_TICKS(p_pdu->delay * 5),pdFALSE,(void *)&server->delay_timer.delay_parma[result],handler_generic_onoff_delay_timer);		//5ms * p_pdu->delay
		if(server->delay_timer.Timer[result] != NULL)
				xTimerStart(server->delay_timer.Timer[result],0);
			}
		
		}
	else if(payload_size == sizeof(msg_light_ctl_lite_set_t))
	{
		msg_light_ctl_lite_set_t *p_pdu = (msg_light_ctl_lite_set_t *)(pdu->access + 2);
		msg_field.tid = p_pdu->tid;
		result = generic_msg_queue_search(&server->ctl_queue,msg_field);
		if(result)
		{
			return;//discard this message,because same value for the SRC, DST,
					//and TID fields as the previous message received within the past 6 seconds
		}
			
		//this block code is used to  store valid message  within 6 seconds
		result = generic_msg_queue_push(&server->ctl_queue,msg_field);

		server->ctl_queue.date[result].Timer = xTimerCreate("Timer",
							pdMS_TO_TICKS(6000),pdFALSE,(void *)&server->ctl_queue.inst,handle_generic_onoff_six_sec_timer); //6s
														
		if(server->ctl_queue.date[result].Timer != NULL)
					xTimerStart(server->ctl_queue.date[result].Timer,0);
			
		{//this block code is used to transition state
		if(server->server_state == GENERIC_TRANS_PROCESS)
				xTimerDelete(server->delay_timer.trans_timer,0);
					
			result = user_generic_default_transition_time_get();
			uint8_t index;
			index =  generic_timer_free_get(server->delay_timer.mask);
			server->delay_timer.delay_parma[result].target_ctl_lightness = p_pdu->ctl_lightness;
			server->delay_timer.delay_parma[result].target_ctl_temperature = p_pdu->ctl_temperature;
			server->delay_timer.delay_parma[result].target_ctl_delta_uv = p_pdu->ctl_delta_uv;
			server->delay_timer.delay_parma[index].inst = (void *)server;
				
			if(result)
			{
				uint16_t ms;
				ms = generic_transition_time_cal(&result);
				server->delay_timer.trans_timer = xTimerCreate("Timer",
				pdMS_TO_TICKS(ms),pdFALSE,(void *)&server->delay_timer.delay_parma[index],handler_generic_onoff_transition_timer);		//5ms * p_pdu->delay
			}
			else
			{
				server->delay_timer.delay_parma[index].timer_index = 0xff;
				handler_generic_onoff_transition_timer((void *)&server->delay_timer.delay_parma[index]);
			}  
			   
		}
		
	}


}
void light_ctl_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_set_rx_handle(elmt,model,pdu);
}

void light_ctl_set_unacknowledged_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_set_rx_handle(elmt,model,pdu);
}

void light_ctl_temperature_range_status_tx(light_ctl_server_t *server,uint16_t dst_addr)
{
	access_message_tx_t access_message_tx;
	msg_light_ctl_temperature_range_status_t msg_light_ctl_temperature_range_status;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Ctl_Temperature_Range_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	
	access_message_tx.length = sizeof(msg_light_ctl_temperature_range_status_t);
	
	msg_light_ctl_temperature_range_status.status_code = server->msg_format.light_ctl_temp_range_status_code;
	msg_light_ctl_temperature_range_status.range_min = server->msg_format.light_ctl_temp_range_min;
	msg_light_ctl_temperature_range_status.range_max = server->msg_format.light_ctl_temp_range_max;	
	
	access_message_tx.p_buffer = (uint8_t *)&msg_light_ctl_temperature_range_status;

	access_message_tx.cb = light_ctl_msg_complete;
	access_model_reply(server->model.base.elmt,&server->model.base,p_tx,dst_addr);	
}

void light_ctl_temperature_range_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_server_t,model);
	
	light_ctl_temperature_range_status_tx(server,pdu->base.dst_addr);
}

void light_ctl_default_status_tx(light_ctl_server_t *server,uint16_t dst_addr)
{
	access_message_tx_t access_message_tx;
	msg_light_ctl_default_status_t msg_light_ctl_default_status;
	access_message_tx.opcode = TWO_OCTETS_OPCODE_GEN(Light_Ctl_Default_Status,LIGHT_TWO_OCTETS_OPCODE_OFFSET);
	
	access_message_tx.length = sizeof(msg_light_ctl_temperature_range_status_t);
	
	msg_light_ctl_default_status.ctl_lightness = server->msg_format.light_ctl_lightness_default;
	msg_light_ctl_default_status.ctl_temperature = server->msg_format.light_ctl_temperature_default;
	msg_light_ctl_default_status.ctl_delta_uv= server->msg_format.light_ctl_delta_uv_default;	
	
	access_message_tx.p_buffer = (uint8_t *)&msg_light_ctl_default_status;

	access_message_tx.cb = light_ctl_msg_complete;
	
	access_model_reply(server->model.base.elmt,&server->model.base,&access_message_tx,dst_addr);	
}


void light_ctl_default_get(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	light_ctl_server_t *server = GET_SERVER_MODEL_PTR(light_ctl_server_t,model);
	
	light_ctl_default_status_tx(server,pdu->base.dst_addr);	
}





