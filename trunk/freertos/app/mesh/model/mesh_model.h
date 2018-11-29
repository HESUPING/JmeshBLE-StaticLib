#ifndef MESH_MODEL_H_
#define MESH_MODEL_H_
#include <stdint.h>
#include <stdbool.h>
#include "co_list.h"
#include "co_utils.h"
#include "mesh_definitions.h"
#include "virt_addr_mngt.h"
#include "sdk_mesh_config_pro.h"

typedef struct
{
    union{
        virt_addr_mngt_t *virt;
        uint16_t addr;
    }addr;
    bool is_virt;
}mesh_addr_t;
typedef struct
{
    struct co_list model_list;
    uint16_t uni_addr;
}mesh_elmt_t;


enum Step_Resolution
{
    Milliseconds_100,
    Second_1,
    Seconds_10,
    Minutes_10,
};
typedef struct
{
    uint8_t num_steps: 6,
        step_resolution: 2;
}publish_period_t;
typedef struct
{
    uint8_t count:3,
        interval_steps:5;
}transmit_state_t;
typedef struct
{
    mesh_addr_t addr;
    uint16_t appkey_idx : 12,
                    credential_flag : 1;
    uint8_t ttl;
    publish_period_t period;
    transmit_state_t retransmit;
}model_publish_state_t;

//network key array index
typedef enum
{
    KEY_PRIMARY = 0,
    KEY_UPDATED = 1,
}key_box_array_idx_t;
typedef uint16_t mesh_global_idx_t;//mesh global index typedef

typedef struct
{
    uint8_t netkey[MESH_KEY_LENGTH];
    uint8_t identity_key[MESH_KEY_LENGTH];
    uint8_t beacon_key[MESH_KEY_LENGTH];
    uint8_t network_id[NETWORK_ID_LENGTH];
    uint8_t privacy_key[MESH_KEY_LENGTH];
    uint8_t encryption_key[MESH_KEY_LENGTH];
    uint8_t nid;
}net_key_box_t;
typedef struct
{
     net_key_box_t key[2];
     uint16_t global_idx;
     mesh_key_refresh_phase_t  key_refresh_phase;
     //uint8_t curr_idx;
     //bool is_used;
}net_key_t;
/** node save device key structure */
typedef struct
{
     uint8_t netkey[2][MESH_KEY_LENGTH];
     uint16_t global_idx;
     mesh_key_refresh_phase_t  key_refresh_phase;
    // uint8_t curr_idx;
    // bool is_used;
}net_key_nodesave_t;

typedef struct
{
    uint8_t appkey[MESH_KEY_LENGTH];
    uint8_t aid;
}app_key_box_t;
typedef struct
{
    net_key_t *bound_netkey;
    app_key_box_t key[2];
    uint16_t global_idx;//mesh need(0-1024)
    //uint8_t curr_idx;//if update , which is new (0-1)
    //bool is_used;
}app_key_t;
/** node save device key structure */
typedef struct
{
    app_key_t src_app_key;
    uint16_t netkey_global_idx;
}app_key_nodesave_t;

typedef struct
{
    net_key_t *pool[DEVKEY_BOUND_NETKEY_MAX_NUM];
    uint8_t update_ack[DEVKEY_BOUND_NETKEY_MAX_NUM];
}dev_key_bound_netkey_pool_t;
typedef struct
{
    dev_key_bound_netkey_pool_t bound_netkey;
    uint8_t  key[MESH_KEY_LENGTH];
    uint16_t addr;
//    bool is_used;
}dev_key_t;
/** node save device key structure */
typedef struct
{
    dev_key_t src_dev_key;
    uint16_t net_key_global_index_pool[DEVKEY_BOUND_NETKEY_MAX_NUM];
}dev_key_nodesave_t;


typedef struct{
    union{
        app_key_t *app;
        net_key_t *net;
    }key;
    uint8_t idx;//decrpt select(0-1)
}key_ptr_t;
typedef struct
{
    struct co_list_hdr hdr; 
    mesh_elmt_t *elmt;
    uint32_t model_id;
    model_publish_state_t *publish;
    mesh_addr_t *subscription_list;
    app_key_t **bound_key_buf;
    uint8_t bound_key_buf_size;
    uint8_t subscription_list_size;
    bool sig_model;
}model_base_t;
typedef struct
{
    model_base_t base;
}model_server_base_t;
typedef struct
{
    model_base_t base;
}model_client_base_t;
#define IS_MESH_ADDR_STRUCT_VALID(ptr) (*(uint32_t *)&((ptr)->addr)!=0)
#define GET_SERVER_MODEL_PTR(type,ptr)   CONTAINER_OF(CONTAINER_OF((ptr),model_server_base_t,base),type,model)
#define GET_CLIENT_MODEL_PTR(type,ptr)   CONTAINER_OF(CONTAINER_OF((ptr),model_client_base_t,base),type,model)
enum MESH_BOUND_EVENT
{
	BOUND_SYS = 0x01,
	BOUND_STATE_CHANGE,
	BOUND_DELETE
};
enum MESH_BOUND_STATE
{
	GENERIC_ONOFF_STATE = 0x01,
	GENERIC_LEVEL_STATE
};
typedef void(*mesh_state_bound_cb_t)(uint8_t type,uint8_t state_type,void *arg);

#endif



