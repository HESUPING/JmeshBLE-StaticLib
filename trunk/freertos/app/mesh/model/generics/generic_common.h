#ifndef GENERIC_COMMON__H
#define	GENERIC_COMMON__H
#include <stdint.h>

#define GENERIC_MSG_MAX   12  //max number of messages in 6 sec to this model
#define GENERIC_TIMER_MAX 4   //handle onoff delay value,maybe a lot of message with delay field.




enum GENERIC_TRANS_STATE_T
{
	GENERIC_TRANS_IDALE = 0x00,
	GENERIC_TRANS_PROCESS
	
};

enum
{
	GENERIC_LEVEL_UNRESOLVE = 0x00 ,
	GENERIC_LEVEL_DELTA_TRANSACTING ,
	GENERIC_LEVEL_DELTA_TRANSACTION_START,
	GENERIC_LEVEL_DELTA_TRANSACTION_ABORD
};


typedef struct
{
    uint8_t num_steps: 6,   //low bit
        step_resolution: 2; //high bit
}generic_transition_time_t;


typedef struct
{
	void *inst;
	uint8_t mask;
}inst_parma_t;


typedef struct
{
	uint16_t src;
	uint16_t dst;
	uint8_t tid;
	TimerHandle_t Timer;
}generic_valid_field_check_t;

typedef struct
{
	generic_valid_field_check_t date[GENERIC_MSG_MAX];
	inst_parma_t inst_parma;
	uint8_t mask;
	uint16_t delta_init;
	uint8_t front;
	uint8_t rear;
}generic_valid_field_queue_t;


generic_transition_time_t generic_time_transition_cal(uint32_t tick);

int generic_msg_queue_push(generic_valid_field_queue_t *queue,generic_valid_field_check_t value);

generic_valid_field_check_t generic_msg_queue_pop(generic_valid_field_queue_t *queue);

uint8_t  generic_msg_queue_search(generic_valid_field_queue_t *queue,generic_valid_field_check_t value);
uint8_t  generic_msg_queue_search_last(generic_valid_field_queue_t *queue,generic_valid_field_check_t value);


uint8_t generic_timer_free_get(uint16_t mask);
uint32_t generic_transition_time_cal(uint8_t *trans_time);






#endif





