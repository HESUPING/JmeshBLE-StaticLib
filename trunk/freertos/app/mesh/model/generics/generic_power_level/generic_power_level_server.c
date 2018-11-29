#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "generic_power_level_server.h"
#include "generci_level_server.h"
static generic_power_level_server_t s_generic_power_level_server;

static void send_generic_power_level_status()
{

}

static void send_generic_power_last_status()
{

}

static void send_generic_power_default_status()
{

}

static void send_generic_power_range_status()
{

}

static void handler_generic_level_power_state_delay_time()
{



}
static void handler_generic_power_level_state_transition_time(uint8_t type,uint8_t trans_time,uint16_t level_target)
{


}
static uint16_t generic_level_power_state_transition_time_cal(uint8_t trans_time,uint8_t delay)
{
	generic_transition_time_t time_tran = (generic_transition_time_t)trans_time;
	uint16_t ms100_value = time_tran.interval_steps;
	switch(time_tran.count)
	{
		case Milliseconds_100:
			ms100_value = ms100_value *  1;break
    	case Second_1:
    		ms100_value = ms100_value *  10;break;
    	case Seconds_10:
    		ms100_value = ms100_value *  100;break;
    	case Minutes_10:
    		ms100_value = ms100_value *  6000;break;
	}
	return ms100_value;
}

void generic_power_level_status_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	send_generic_power_level_status();
}

void generic_power_level_status_set_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size == sizeof(generic_msg_power_level_default_t))
	{
		generic_level_msg_default_t *p_pdu = (generic_msg_power_level_default_t *)payload;
		if(p_pdu->tid == s_generic_power_level_server.tid)
		{
			return;
		}
		s_generic_power_level_server.tid = p_pdu->tid;
		s_generic_power_level_server.generic_power_actual_target = p_pdu->power;
		send_generic_power_level_status();
		//open delay timer to arrive at init status
		//
	}
	else if(size == sizeof(generic_msg_power_level_set_t))
	{
		generic_msg_power_level_set_t *p_pdu = (generic_msg_power_level_set_t *)payload;
		s_generic_power_level_server.tid = p_pdu->tid;
		s_generic_power_level_server.generic_power_actual_target = p_pdu->power;
		s_generic_power_level_server.delay = p_pdu->delay;
		s_generic_power_level_server.trans_time = p_pdu->trans_time;
		send_generic_power_level_status();
		//open delay timer to arrive at init status
		//
	}
	else
	{
		return;
	}
}

void generic_power_level_status_set_unackonwledged_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size == sizeof(generic_msg_power_level_default_t))
	{
		generic_level_msg_default_t *p_pdu = (generic_msg_power_level_default_t *)payload;
		if(p_pdu->tid == s_generic_power_level_server.tid)
		{
			return;
		}
		s_generic_power_level_server.tid = p_pdu->tid;
		s_generic_power_level_server.generic_power_actual_target = p_pdu->power;
		//open delay timer to arrive at init status
		//
	}
	else if(size == sizeof(generic_msg_power_level_set_t))
	{
		generic_msg_power_level_set_t *p_pdu = (generic_msg_power_level_set_t *)payload;
		s_generic_power_level_server.tid = p_pdu->tid;
		s_generic_power_level_server.generic_power_actual_target = p_pdu->power;
		s_generic_power_level_server.delay = p_pdu->delay;
		s_generic_power_level_server.trans_time = p_pdu->trans_time;
		//open delay timer to arrive at init status
		//
	}
	else
	{
		return;
	}

}

void generic_power_last_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	send_generic_power_last_status();
}

void generic_power_range_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	send_generic_power_range_status();
}

void generic_power_defalut_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	send_generic_power_default_status();
}
uint32_t generic_level_power_server_state_bound_event(uint8_t type,void *arg,uint8_t size)
{
	switch(type)
	{
			case:BOUND_SYS;break;
			case:BOUND_STATE_CHANGE;break;
			case:BOUND_DELETE;break;
	}
}

uint32_t generic_power_level_server_init(generic_power_level_server_t *server)
{
	ger_level_server_state_info_t info;
	info.handler = generic_level_power_server_state_bound_event;
	info.peer_level_state_min = s_generic_power_level_server.generic_power_range_min;
	info.peer_level_state_max = s_generic_power_level_server.generic_power_range_max;
	info.peer_level_state = s_generic_power_level_server.generic_power_default;
	generic_level_server_state_bound_req(&info);
	
}

#endif

