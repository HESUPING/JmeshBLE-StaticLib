#ifndef OSAPP_MESH_H_
#define OSAPP_MESH_H_
#include <stdint.h>
#include <stdbool.h>
#include "gap.h"
#define ADV_DATA_BUF_SIZE (GAP_ADV_DATA_LEN-0)

typedef enum mesh_adv_type
{
    BEARER_ADV,
	BEARER_ADV_RELAY,
	BEARER_ADV_SECURITY_NETWORK_BEACON,
    PROVISIONING_SERVICE_ADV,
    PROXY_SERVICE_ADV,
	ADV_INVALID// invalid type,just for feture
}mesh_adv_type_t;




//#define OSAPP_MESH_AES_TEST
//DEFINE
#define MESH_TASK_STACK_SIZE    500  //500*4 Bytes 
#define MESH_ADV_INTERVAL       160  //unit: 0.625ms
#define MESH_SCAN_INTERVAL      48   //30ms




#define MESH_QUEUE_LENGTH           10
#define MESH_ADV_ENV_QUEUE_SIZE     8
#define MESH_DEFFERED_TX_BUF_SIZE   5







//DATA STRUCT
typedef struct 
{
    void *data;
    uint8_t event_type;
}mesh_queue_t;
typedef struct
{
    uint8_t data[ADV_DATA_BUF_SIZE];
    uint8_t length;
}mesh_tx_buf_t;

typedef struct
{
    uint8_t count;            //LSB
    uint8_t interval_steps;   //MSB
}adv_transmit_state_t;

typedef struct
{
    struct co_list_hdr hdr;
    void (*callback)();
    mesh_tx_buf_t buf;
    adv_transmit_state_t transmit_step_count;
    uint8_t type;
}adv_env_t;

typedef struct
{
    struct co_list adv_env_list;
    adv_env_t *env;
    uint8_t adv_count;
}air_op_t;


typedef struct {
    uint8_t mesh_buf[ADV_DATA_BUF_SIZE];
    uint8_t length;
}adv_report_env_t;


//EXTERN FUNCTION
extern void app_mesh_test_init(void);


//EXPORT VARIABLE
extern air_op_t air_op;


//EXPORT FUNCTION
mesh_tx_buf_t *mesh_alloc_tx_adv_buf(mesh_adv_type_t type);
void mesh_send_tx_cmd(mesh_tx_buf_t * buf,void (*callback)());

void mesh_stack_init_process_next_stage(void);
void mesh_run(void (*cb)(),uint32_t xTicksToWait,bool inISR);
int32_t osapp_gapm_use_enc_block_cmd(uint8_t const*key,uint8_t const*data);
void mesh_flush_msg_cache(void);
void mesh_init_start_scan(void);
void mesh_send_init_msg(void);


#endif
