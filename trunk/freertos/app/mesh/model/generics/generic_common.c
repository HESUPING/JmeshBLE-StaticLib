#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "generic_common.h"
#include "mesh_model.h"
int generic_msg_queue_push(generic_valid_field_queue_t *queue,generic_valid_field_check_t value)
{
    uint8_t posi;
	if((queue->rear+1)%GENERIC_MSG_MAX != queue->front)
	{
	    queue->date[queue->rear] = value;
	    posi = queue->rear;
		queue->rear = (queue->rear+1)%GENERIC_MSG_MAX;
		return posi;
	}
	else
	{
		BX_ASSERT(0);
		return 0;//keep the compiler from issuing warnings
	}
	
}
generic_valid_field_check_t generic_msg_queue_pop(generic_valid_field_queue_t *queue)
{
	generic_valid_field_check_t value;
	if(queue->front!=queue->rear)
	{
		value = queue->date[queue->front];
		queue->front = (queue->front+1)%GENERIC_MSG_MAX;
		return value;
	}
	else
	{
	    BX_ASSERT(0);
	    return value;//keep the compiler from issuing warnings
	}
} 
// search dst src tid have no change within 6 second
uint8_t  generic_msg_queue_search(generic_valid_field_queue_t *queue,generic_valid_field_check_t value)
{

	uint8_t i;
	i = queue->front;
	while(i != queue->rear)
	{
		if(queue->date[i].dst == value.dst && queue->date[i].src == value.src && queue->date[i].tid == value.tid)
		{
			return 1;
		}
		i = (i + 1)%GENERIC_MSG_MAX;
	}

	return 0;
}
// search dst src tid have no change within 6 second
uint8_t  generic_msg_queue_search_last(generic_valid_field_queue_t *queue,generic_valid_field_check_t value)
{

	uint8_t i;
	i = queue->front;
	if(queue->front == queue->rear)
	{
		return GENERIC_LEVEL_DELTA_TRANSACTION_START;
	}
	else if(queue->date[i].dst != value.dst || queue->date[i].src != value.src )
	{
		return GENERIC_LEVEL_DELTA_TRANSACTION_ABORD;
	}
	else if(queue->date[i].dst == value.dst && queue->date[i].src == value.src && queue->date[i].tid == value.tid)
	{
		return GENERIC_LEVEL_DELTA_TRANSACTING;
	}	
	return GENERIC_LEVEL_UNRESOLVE;
}

//return unit is ms
uint32_t generic_transition_time_cal(uint8_t *trans_time)
{
	generic_transition_time_t *time_tran = (generic_transition_time_t *)trans_time;
	LOG(3,"time_tran=0x%x,num_steps=0x%x,step_resolution=0x%x\n",*time_tran,time_tran->num_steps,time_tran->step_resolution);
	uint32_t ms100_value = time_tran->num_steps;
	switch(time_tran->step_resolution)
	{
		case Milliseconds_100:
			ms100_value = ms100_value *  1;break;
    	case Second_1:
    		ms100_value = ms100_value *  10;break;
    	case Seconds_10:
    		ms100_value = ms100_value *  100;break;
    	case Minutes_10:
    		ms100_value = ms100_value *  6000;break;
	}
	return ms100_value * 100;
}

//convert remaining time to trans_time
generic_transition_time_t generic_time_transition_cal(uint32_t tick)
{
	uint8_t tick_ms = 20;
	generic_transition_time_t time_tran; 
	if(tick <= (6200/tick_ms)) //the range is 0 through 6.2 seconds
	{
		time_tran.step_resolution = Milliseconds_100;
		time_tran.num_steps = (tick * tick_ms)/100;
	}
	else if(tick <= (62000/tick_ms))
	{
		time_tran.step_resolution = Second_1;
		time_tran.num_steps = (tick * tick_ms)/1000;
	}
	else if(tick <= (620000/tick_ms))
	{
		time_tran.step_resolution = Seconds_10;
		time_tran.num_steps = (tick * tick_ms)/10000;
	}
	else
	{
		time_tran.step_resolution = Minutes_10;
		time_tran.num_steps = (tick * tick_ms)/600000;
	}
	return time_tran;
}

uint8_t generic_timer_free_get(uint16_t mask)
{
	uint8_t i;
	for(i = 0;i < GENERIC_TIMER_MAX;i++)
	{
		if(((1<<i)&(mask)) == 0)
			return i;
	}
	BX_ASSERT(0);
	return 0;//keep the compiler from issuing warnings
}

#endif

