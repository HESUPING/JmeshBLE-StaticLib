#ifndef OSAPP_MESH_H_
#define OSAPP_MESH_H_
#include <stdint.h>
#include <stdbool.h>
#include "gap.h"
#define ADV_DATA_BUF_SIZE (GAP_ADV_DATA_LEN-0)

enum mesh_adv_type 
{
    BEARER_ADV,
    PROVISIONING_SERVICE_ADV,
    PROXY_SERVICE_ADV,
};

//mesh features status
typedef enum
{
    MESH_FEATURE_DISABLED      =0,
    MESH_FEATURE_ENABLED       =1,
    MESH_FEATURE_NOT_SUPPORT   =2,
} mesh_feature_stat_t;

//mesh features supports
#define MESH_SUPPORT_RELAY      MESH_FEATURE_DISABLED
#define MESH_SUPPORT_PROXY      MESH_FEATURE_DISABLED
#define MESH_SUPPORT_FRIEND     MESH_FEATURE_NOT_SUPPORT
#define MESH_SUPPORT_LOW_POWER  MESH_FEATURE_NOT_SUPPORT



//#define OSAPP_MESH_AES_TEST
//DEFINE
#define MESH_TASK_STACK_SIZE    500  //500*4 Bytes 
#define MESH_ADV_INTERVAL       160  //unit: 0.625ms
#define MESH_SCAN_INTERVAL      48   //30ms

#define MESH_ADV_DURATION   20 //unit: ms



#define MESH_QUEUE_LENGTH           10
#define MESH_ADV_ENV_QUEUE_SIZE     8
#define MESH_DEFFERED_TX_BUF_SIZE   5

//default value of network_transmit_state_t
//count max    = 0b111   = 7
//interval max = 0b11111 = 31
#define NETWORK_TRANSMIT_DEFAULT_COUNT              5   //send 6 times  (count + 1)
#define NETWORK_TRANSMIT_DEFAULT_INTERVAL           10  //interval = step*10 ms
#define NETWORK_TRANSMIT_DEFAULT_RELAY_COUNT        6   //send 7 times
#define NETWORK_TRANSMIT_DEFAULT_RELAY_INTERVAL     10  //interval = step*10 ms





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
    uint8_t count:3;            //LSB
    uint8_t interval_steps:5;   //MSB
}network_transmit_state_t;

typedef struct
{
    struct co_list_hdr hdr;
    void (*callback)();
    mesh_tx_buf_t buf;
    network_transmit_state_t transmit_step_count;
    uint8_t type;
}adv_env_t;

typedef struct
{
    struct co_list adv_env_list;
    adv_env_t *env;
    uint8_t adv_count;
}air_op_t;

//EXTERN FUNCTION
extern void app_mesh_test_init(void);


//EXPORT VARIABLE
extern air_op_t air_op;


//EXPORT FUNCTION
mesh_tx_buf_t *mesh_alloc_tx_adv_buf(uint8_t type);
void mesh_send_tx_cmd(mesh_tx_buf_t * buf,void (*callback)());

void mesh_run(void (*cb)(),uint32_t xTicksToWait,bool inISR);
int32_t osapp_gapm_use_enc_block_cmd(uint8_t const*key,uint8_t const*data);
void mesh_flush_msg_cache(void);
void user_app_mesh_test_init_done(void);


#endif
