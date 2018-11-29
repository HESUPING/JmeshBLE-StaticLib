#ifndef PROVISION_BASE_H_
#define PROVISION_BASE_H_
#include <stdint.h>
#include <stdbool.h>
#include "security.h"
#include "gap.h"



                                                       
#define PROVISIONER_TRANS_NUM_INIT  0x00
#define UNPROV_DEV_TRANS_NUM_INIT   0x80
#define BEACON_UUID_LEN             16
#define INVITE_PDU_PARAMS_LEN       1
#define CAPABILITIES_PDU_PARAMS_LEN 11
#define START_PDU_PARAMS_LEN        5
#define PUBLIC_KEY_PDU_PARAMS_LEN   64
#define CONFIRMATION_PDU_PARAMS_LEN MAC_LENGTH
#define RANDOM_PDU_PARAMS_LEN       16
#define INVITE_PDU_OFFSET_IN_CONFIRMATION_INPUTS 0
#define CAPABILITIES_PDU_OFFSET_INCONFIRMATION_INPUTS (INVITE_PDU_OFFSET_IN_CONFIRMATION_INPUTS +\
                                                       INVITE_PDU_PARAMS_LEN)
#define START_PDU_OFFSET_IN_CONFIRMATION_INPUTS (CAPABILITIES_PDU_OFFSET_INCONFIRMATION_INPUTS +\
                                                 CAPABILITIES_PDU_PARAMS_LEN)
#define PROVISIONER_PUBLIC_KEY_OFFSET_IN_CONFIRMATION_INPUTS (START_PDU_OFFSET_IN_CONFIRMATION_INPUTS +\
                                                              START_PDU_PARAMS_LEN)
#define DEVICE_PUBLIC_KEY_OFFSET_IN_CONFIRMATION_INPUTS (PROVISIONER_PUBLIC_KEY_OFFSET_IN_CONFIRMATION_INPUTS +\
                                                         PUBLIC_KEY_PDU_PARAMS_LEN)
#define CONFIRMATION_INPUTS_BUF_SIZE (INVITE_PDU_PARAMS_LEN +\
                                      CAPABILITIES_PDU_PARAMS_LEN +\
                                      START_PDU_PARAMS_LEN +\
                                      PUBLIC_KEY_PDU_PARAMS_LEN*2)
#define ENCRYPTED_PROVISIONING_DATA_LEN 25
#define PROVISIONING_DATA_MIC_LEN 8
#define DATA_PDU_PARAMS_LEN (ENCRYPTED_PROVISIONING_DATA_LEN + PROVISIONING_DATA_MIC_LEN)

#define GENERIC_PROVISIONING_PDU_MAX_SIZE (BEARER_BUF_SIZE - 5)
#define MAX_DATA_SIZE_TRANSACTION_START_PDU (GENERIC_PROVISIONING_PDU_MAX_SIZE - 4)
#define MAX_DATA_SIZE_TRANSACTION_CONTINUATION_PDU (GENERIC_PROVISIONING_PDU_MAX_SIZE - 1)
#define DATA_OFFSET_IN_PB_ADV 5
#define PARAMS_OFFSET_IN_PROVISIONING_PDU 1
#define TRANSACTION_ACK_TIMEOUT     30000
#define RETRANSMISSION_TIMEOUT      3000
#define STATE_CHANGE_TIMEOUT        (TRANSACTION_ACK_TIMEOUT * 3)
#define MESH_RAND_DELAY_MIN 20 // unit:ms
#define MESH_RAND_DELAY_MAX 50




#define PARAM_P_CONFIRMATION "prck"
#define PARAM_P_SESSIONKEY "prsk"
#define PARAM_P_SESSION_NONCE "prsn"
#define AUTHVALUE_LEN 16


#define STOP_CURRENT_ADV    {}//air_op.adv_count = MESH_DEFAULT_ADV_CYCLES

//change state after actioned ok.
typedef enum _Provisioner_stage_All_
{
    ProvStage_Beacon_rx                     ,
    ProvStage_LinkOpen_tx                   ,
    ProvStage_LinkAck_rx                    ,
    ProvStage_Invite_tx                     ,
    ProvStage_Capa_rx                       ,
    ProvStage_Invite_Complele__             ,
    ProvStage_Start_tx                      ,
    ProvStage_PublicKey_tx                  ,
    ProvStage_PublicKey_rx                  ,
    ProvStage_ExchangePublicKey_Complete__  ,
    ProvStage_InputComplete_rx              ,
    ProvStage_SendConfirm_tx                ,
    ProvStage_ReadConfirm_tx                ,
    ProvStage_SendRandom_tx                 ,
    ProvStage_ReadRandom_rx                 ,
    ProvStage_AuthComplete__                ,
    ProvStage_Data_tx                       ,
    ProvStage_Complete_rx                   ,
    ProvStage_ProvComplete__                ,
    ProvStage_MAX                           ,
} Provisioner_stage_All;

enum Generic_Provisioning_PDU_Type{
    Transaction_Start_PDU = 0,
    Transaction_Ack_PDU = 1,
    Transaction_Continuation_PDU = 2,
    Provisioning_Bearer_Control_PDU = 3,
};
	
typedef enum
{
    PROVISION_UNINIT = 0,
    PROVISIONED_NOW,
    PROVIVIONER_NOW,
    UNPROVISION_DEVICE_NOW,
} prov_unprov_status_t;


enum Provisioning_PDU_Type{
    Provisioning_Invite = 0,
    Provisioning_Capabilities ,
    Provisioning_Start,
    Provisioning_Public_Key,
    Provisioning_Input_Complete,
    Provisioning_Confirmation,
    Provisioning_Random,
    Provisioning_Data,
    Provisioning_Complete,
    Provisioning_Failed,
    Provisioning_PDU_Type_Max,
};
enum provision_stage{
    Beaconing,
    Invitation,
    Exchanging_Public_Keys,
    Authentication_Confirmation,
    Authentication_Random,
    Provisioning_Data_Distribution,
    Provision_Done,
};
enum tx_complete_code{
    Acked,
    Timeout_No_Ack,
};
enum Bearer_Opcode_Type{
    Link_Open = 0,
    Link_Ack = 1,
    Link_Close = 2,
    Bearer_Opcode_Max,
};
enum Link_Close_Reason{
    Success = 0,
    Timeout ,
    Fail,
};
enum Provisioning_Error_Codes
{
    Error_Code_RFU = 0,
    Invalid_PDU,
    Invalid_Format,
    Unexpected_PDU,
    Confirmation_Failed,
    Out_of_Resources,
    Decryption_Failed,
    Unexptected_Error,
    Cannot_Assign_Addresses,
};
typedef struct{
    uint32_t Link_ID;
    uint8_t *data_buf;
    uint8_t data_length;
    uint8_t Transaction_Number;
}pb_adv_info_t;
enum Output_OOB_Action{
    Blink = 0,
    Beep ,
    Vibrate ,
    Output_Numeric ,
    Output_Alphanumeric ,
};
enum Input_OOB_Action{
    Push = 0,
    Twist ,
    Input_Number ,
    Input_Alphanumeric ,
};
enum Authentication_Method{
    No_OOB_Authentication = 0,
    Static_OOB_Authentication,
    Output_OOB_Authentication,
    Input_OOB_Authentication,
};
enum Public_Key_Ex{
    Peer_Key_Received = 0x1,
    Local_Key_Sent = 0x2,
    Key_Exchanged = 0x3,
};
typedef enum {
    LINK_CLOSED,
    LINK_OPENED,
}provision_stat_t;
typedef struct{
    uint16_t TotalLength;
    uint8_t SegN;
    uint8_t FCS;
}transaction_start_info_t;
typedef struct{
    uint8_t *buf;
    transaction_start_info_t pdu_info;
    uint16_t rx_length;
    uint8_t next_seg_idx;
}provisioning_rx_env_t;
typedef struct{
    void (*callback)(uint8_t);
    uint8_t *data;
    uint8_t length;
    uint8_t pdu_type;
}provisioning_tx_env_t;
typedef void (*rx_pdu_handler_t)(uint8_t *,uint8_t);
typedef void (*bearer_ctrl_pdu_rx_handler_t)(pb_adv_info_t *,uint8_t *,uint8_t);
typedef struct{
    uint8_t confirmation_inputs[CONFIRMATION_INPUTS_BUF_SIZE];
    uint8_t peer_dev_uuid[MESH_DEVICE_UUID_LENGTH];
    provisioning_rx_env_t rx;
    provisioning_tx_env_t tx;
    uint32_t link_id;
    struct {
        uint8_t peer;
        uint8_t local;
    }transaction_num;
    uint8_t stage;
    uint8_t public_key_ex;
}provision_env_t;
typedef struct
{
    public_key_t peer_public;
    public_key_t local_public;
    uint8_t private[32];
    public_key_t ecdh_secret;
}provision_key_t;
typedef struct{
    uint8_t local[CONFIRMATION_PDU_PARAMS_LEN];
    uint8_t peer[CONFIRMATION_PDU_PARAMS_LEN];
}provision_confirmation_t;
typedef struct{
    uint8_t confirmation_key[K1_LENGTH];
    union{
        uint8_t buf[RANDOM_PDU_PARAMS_LEN + AUTHVALUE_LEN];
        struct{
            uint8_t random[RANDOM_PDU_PARAMS_LEN];
            uint8_t auth_value[AUTHVALUE_LEN];
        }detail;
    }msg_for_cfm;
    uint8_t confirmation_rslt[CONFIRMATION_PDU_PARAMS_LEN];
    void (*confirmation_calc_callback)();
}provision_authentication_t;
typedef struct{
    uint8_t algorithm;
    uint8_t public_key;
    uint8_t auth_method;
    uint8_t auth_action;
    uint8_t auth_size;
}provision_start_t;
typedef struct{
    uint16_t algorithms;
    uint16_t output_oob_action;
    uint16_t input_oob_action;
    uint8_t elements_num;
    uint8_t public_key_type;
    uint8_t static_oob_type;
    uint8_t output_oob_size;
    uint8_t input_oob_size;
}provision_capabilities_t;
typedef union{
    uint8_t provisioning_salt_input[S1_LENGTH + 2*RANDOM_PDU_PARAMS_LEN];
    struct{
        uint8_t confirmation_salt[S1_LENGTH];
        uint8_t random_provisioner[RANDOM_PDU_PARAMS_LEN];
        uint8_t random_device[RANDOM_PDU_PARAMS_LEN];
    }field;    
}provision_random_t;
typedef struct{
    uint8_t provisioning_salt[S1_LENGTH];
    uint8_t session_key[K1_LENGTH];
    uint8_t session_nonce[K1_LENGTH];
    void (*session_calc_callback)();
}session_info_t;
typedef struct{
    uint8_t network_key[MESH_NETWORK_KEY_LENGTH];
    uint16_t key_index;
    uint8_t flags;
    uint32_t current_iv_index;
    uint16_t unicast_addr;
}provision_data_t;
typedef struct{
    uint8_t packed_data[DATA_PDU_PARAMS_LEN];
    uint8_t encrypted_data[DATA_PDU_PARAMS_LEN];
}provision_encrypted_data_t;;
typedef struct
{
    uint8_t pdu[CONFIRMATION_PDU_PARAMS_LEN];
    uint8_t length;
    uint8_t ecdh_calcuating;
    uint8_t received_confirm_pdu_in_calcuating;
} provision_confirmation_cache_t;


extern void (*provision_input_auth_value)(uint8_t *,void (*cb)());
extern void (*provision_output_auth_value)(uint8_t *);
extern void (*provision_static_auth_value)(uint8_t *);
extern void (*user_provision_done)(uint8_t ,uint8_t );
extern provision_env_t provision_env;
extern provision_key_t provision_key;
extern provision_capabilities_t provision_capabilities;
extern provision_start_t provision_start;
extern provision_confirmation_t provision_confirmation;
extern provision_authentication_t provision_authentication;
extern provision_random_t provision_random;
extern provision_data_t provision_data;
extern provision_encrypted_data_t provision_encrypted_data;
extern session_info_t session_info;
extern provision_stat_t provision_stat;
extern Provisioner_stage_All current_stage;
extern const char current_stage_s[ProvStage_MAX][44];

extern void (*provisioner_capabilities_rx_callback)(provision_capabilities_t *);
extern void (*provisioner_read_peer_public_key_oob)(void (*callback)(void));
extern void (*provisioner_link_ack_rx_callback)(void);

extern void (*unprov_dev_make_attention)(uint8_t);
extern void (*unprov_dev_expose_public_key_oob)(public_key_t *);
extern void (*unprov_dev_capabilities_init)(void);
extern uint8_t (*compare_uuid_with_own)(uint8_t *);
extern prov_unprov_status_t provision_now_status;
extern provision_confirmation_cache_t provision_confirmation_cache;




void set_pdu_tx_complete_callback(void (*cb)(uint8_t));
void provision_set_auth_value(uint8_t *dst,bool static_oob);
void provisioning_link_close_tx(uint8_t reason);
void provisioning_link_ack_tx(void);
void provisioning_link_open_tx(uint8_t *dev_uuid);
uint8_t *provisioning_pdu_build(uint8_t type);
void provisioning_pdu_tx(void);

void provisioning_confirmation_value_calc(void (*cb)());
bool provisioning_public_key_rx(uint8_t *data,uint8_t length,uint8_t peer_public_key_offset_in_confirmation_inputs);
bool provisioning_confirmation_rx(uint8_t *data,uint8_t length);
void provisioning_confirmation_tx(void);
void provisioning_random_tx(uint8_t *random);
bool provisioning_confirmation_check(void);
bool provisioning_random_rx(uint8_t *data,uint8_t length,uint8_t *random_buf,void (*cfm_chk_cb)());
void provisioning_public_key_tx(uint8_t local_public_key_offset_in_confirmation_inputs);
void calc_session_key_nounce(void (*cb)());
void provision_pb_adv_rx(uint8_t *data,uint8_t len);
void provisioning_pdu_gatt_rx(const uint8_t *p_data,uint8_t length);

void random_gen_words(uint8_t *buf , uint8_t length_in_word);
void provision_transaction_num_init(uint8_t local , uint8_t peer);

void provisioning_link_open_stop(void);
void stop_all_provision_timer(void);
void provision_base_init(void);
void provision_base_reset(void);

void set_provisioning_handler(rx_pdu_handler_t *pdu_handler,bearer_ctrl_pdu_rx_handler_t* ctrl_handler,void (*key_exchanged_cb)());
void provisioner_start_tx(void);
void provision_done(uint8_t success , uint8_t reason);
void provision_delete_provision_database(void);
bool provision_is_provision_done(void);
//#include "mesh_uart_ctrl.h"

#endif

