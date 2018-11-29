#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "health_server.h"
#include "health_common.h"

static health_server_t s_temp_server;
static void attention_timer_set(health_server_t * p_health_server, uint8_t new_attention_value)
{


}

static void send_period_status(health_server_t *p_health_server,uint16_t opcode,uint8_t *payload)
{
	//
}
static void send_fault_status(health_server_t *p_health_server,uint16_t opcode,uint8_t *payload)
{
	// send message
}

static void send_attention_status(health_server_t *p_health_server,uint16_t opcode,uint8_t *payload)
{

}
void health_fault_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size != sizeof(health_msg_fault_get_t))
	{
		return;
	}
	health_msg_fault_get_t *p_pdu = (health_msg_fault_get_t *)payload;
	if(p_pdu->company_id != s_temp_server->company_id)
	{
		return;
	}
	send_fault_status(&s_temp_server,Health_Fault_Status,)
}
void health_fault_clear_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size != sizeof(health_msg_fault_clear_t))
	{
		return ;
	}
	health_msg_fault_clear_t *p_pdu = (health_msg_fault_clear_t *)payload;
	if(p_pdu->company_id != s_temp_server->company_id)
	{
		return;
	}
	// clear registered_faults
	s_temp_server->registered_faults.top = 0;

	send_fault_status(&s_temp_server,Health_Fault_Status,)
}
void health_fault_clear_unacknowledged_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size != sizeof(health_msg_fault_clear_t))
	{
		return ;
	}
	health_msg_fault_clear_t *p_pdu = (health_msg_fault_clear_t *)payload;
	if(p_pdu->company_id != s_temp_server->company_id)
	{
		return;
	}
	// clear registered_faults
	s_temp_server->registered_faults.top = 0;
}

void health_fault_test_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	uint8_t test_result;
	if(size != sizeof(health_msg_fault_test_t))
	{
		return;
	}
	health_msg_fault_test_t * p_pdu = (const health_msg_fault_test_t *) payload;
	if(p_pdu->company_id != s_temp_server->company_id)
	{
		return 
	}
	test_result = s_temp_server->selftest_handler(s_temp_server->company_id,p_pdu->test_id);
	if(test_result)
	{
		send_fault_status(&s_temp_server,Health_Fault_Status,)
	}
}

void health_fault_test_unacknowledged_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	uint8_t test_result;
	if(size != sizeof(health_msg_fault_test_t))
	{
		return;
	}
	health_msg_fault_test_t * p_pdu = (const health_msg_fault_test_t *) payload;
	if(p_pdu->company_id != s_temp_server->company_id)
	{
		return 
	}
	test_result = s_temp_server->selftest_handler(s_temp_server->company_id,p_pdu->test_id);
}


void health_fault_period_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	
	send_period_status(s_temp_server->fast_period_divisor);
}


void health_fault_period_set_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if (size != sizeof(health_msg_period_set_t))
    {
        return;
    }
    health_msg_period_set_t *p_pdu = (health_msg_period_set_t *)payload;
    if(p_pdu->fast_period_divisor < FAST_PERIOD_DIVISOR_MAX)
    {
		s_temp_server->fast_period_divisor = p_pdu->fast_period_divisor;
		send_period_status(s_temp_server->fast_period_divisor);
    }
    
}

void health_fault_period_set_unacknowledged_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if (size != sizeof(health_msg_period_set_t))
    {
        return;
    }
    health_msg_period_set_t *p_pdu = (health_msg_period_set_t *)payload;
    if(p_pdu->fast_period_divisor < FAST_PERIOD_DIVISOR_MAX)
    {
		s_temp_server->fast_period_divisor = p_pdu->fast_period_divisor;

    }
}

void health_fault_attention_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	
}

void health_fault_attention_set_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size != sizeof(health_msg_attention_set_t))
	{
		return;
	}

	health_msg_attention_set_t *p_pdu = (health_msg_attention_set_t *)payload;
	s_temp_server->attention_timer = p_pdu->attention;
	attention_timer_set(&s_temp_server,s_temp_server->attention_timer);
}


void health_fault_attention_set_unacknowledged_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	if(size != sizeof(health_msg_attention_set_t))
	{
		return;
	}

	health_msg_attention_set_t *p_pdu = (health_msg_attention_set_t *)payload;
	s_temp_server->attention_timer = p_pdu->attention;
	attention_timer_set(&s_temp_server,s_temp_server->attention_timer);

	send_attention_status();
}


//user interfence
void user_health_server_publish_period_set(health_server_t * p_server)
{
	uint16_t ms100_value = p_server->model.publication.period.num_steps;
	switch(p_server->model.publication.period.step_resolution)
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
	// open timer to publish health fault status

}

void user_health_server_attention_set(health_server_t * p_server, uint8_t attention)
{
	return p_server->attention_timer;

}

uint8_t user_health_server_attention_get(const health_server_t * p_server)
{
	attention_timer_set(p_server, attention);
}

uint32_t health_server_init(health_server_t *p_health_server)
{

	s_temp_server = *p_health_server;

}

#endif

