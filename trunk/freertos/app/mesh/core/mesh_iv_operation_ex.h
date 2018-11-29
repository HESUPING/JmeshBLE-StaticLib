
#ifndef MESH_IV_OPERATION_EX_H_
#define MESH_IV_OPERATION_EX_H_


typedef enum
{
	IV_UPDATE_START,
	IV_UPDATE_IN_PROGRESS,
	IV_UPDATE_TO_NORMAL,
	IV_UPDATE_SEND_PKT,
	IV_UPDATE_RX_PKT
} mesh_iv_update_log_cmd;

typedef enum
{
    MESH_TO_IV_UPDATE_IN_PROGRESS_SIGNAL,
    MESH_TO_NORMAL_SIGNAL,
    MESH_TO_TESTMODE_ON,
    MESH_TO_TESTMODE_OFF,
} mesh_iv_update_signals_t;


extern void mesh_iv_sec_bean_rx(const uint8_t * p_network_id, uint32_t iv_index, bool iv_update, bool key_refresh);
extern void mesh_iv_init(void);
extern uint32_t mesh_seqnum_alloc(uint32_t num);
extern uint32_t mesh_rx_iv_index_get(uint8_t ivi);
extern uint32_t mesh_tx_iv_index_get(void);
extern uint32_t mesh_beacon_iv_index_get(void);
extern void mesh_beacon_iv_index_set(uint32_t val);

extern bool mesh_iv_update_is_processing(void);
extern uint32_t mesh_test_mode_transition_run(mesh_iv_update_signals_t signal);
extern void mesh_iv_update_test_mode_set(bool test_mode_on);
extern void iv_update_log_event(mesh_iv_update_log_cmd cmd);


#endif

