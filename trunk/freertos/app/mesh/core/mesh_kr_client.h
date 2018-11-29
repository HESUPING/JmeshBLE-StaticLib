#ifndef MESH_KEY_REFRESH_CLIENT_H_
#define MESH_KEY_REFRESH_CLIENT_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "mesh_definitions.h"
#include "mesh_errors.h"
#include "mesh_kr_comm.h"
#include "device_manager_api.h"

#define DEFAULT_NETKEY_UPDATE_TIMER (20*10)
#define DEFAULT_NETKEY_DISTRIBUTE_FLAG_TIMER (20*10)
#define DEFAULT_NETKEY_INVOKE_KEY_TIMER (20*10)
#define MESH_KR_UPDATE_TICK   1000               // unit: ms
#define MESH_KR_LIST_MAX_SIZE 16


typedef enum
{
    MESH_KR_UPDATE_NORMAL,
    MESH_KR_UPDATE_DISTRIBUTE_KEY,
    MESH_KR_UPDATE_WAIT_ACK,
    MESH_KR_UPDATE_DISTRIBUTE_KEYFRESH_FLAG,
    MESH_KR_UPDATE_WAIT_PHASE2_ACK,
    MESH_KR_UPDATE_INVOKE_KEY,
    MESH_KR_UPDATE_WAIT_PHASE3_ACK,
    MESH_KR_UPDATE_INVALID_STATUS,

} mesh_kr_client_update_t;






typedef void (*mesh_kr_client_timer_handler_t)(dm_netkey_handle_t netkey_handle);
typedef bool (*mesh_kr_client_check_handler_t)(dm_netkey_handle_t netkey_handle);
typedef void (*mesh_kr_client_tran_handler_t)(dm_netkey_handle_t netkey_handle);

//typedef bool (*mesh_kr_client_is_timeout_t)(uint32_t timecount);

/**
 * @brief structure to define message and it's callback
 */
typedef struct
{
    mesh_kr_client_update_t phase;
   // mesh_kr_client_is_timeout_t    is_timeout;
    mesh_kr_client_timer_handler_t timeout_handler;
    mesh_kr_client_check_handler_t check_handler;
    mesh_kr_client_tran_handler_t  trans_handler;
}mesh_kr_client_timer_handler_table_t;

void config_client_kr_netkey_status_ack(netkey_index_t netkey_index, uint16_t dev_addr);
void config_client_net_key_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu);
void mesh_kr_client_init(void);
uint32_t config_client_kr_add_netkey(uint16_t global_idx, uint8_t *netkey);
uint32_t config_client_kr_update_netkey(uint16_t global_idx, uint8_t *netkey);

void mesh_kr_client_output_env(void);

//TODO: move to api.h
err_t mesh_client_batch_remove_node(uint16_t* p_dev_addr, uint8_t size);
void config_client_kr_phase_status_ack(netkey_index_t netkey_index, uint16_t dev_addr);

#endif
