#ifndef MESH_KEY_REFRESH_COMM_H_
#define MESH_KEY_REFRESH_COMM_H_


#define MAX_KR_NETKEY_SEARCH_SIZE 5

#define MAX_KR_NETKEY_INVALID_POS (0xff)


#define BIT_BLOCK_SIZE (8)
#define BIT_MASK(BIT) (1u << ((BIT) & (BIT_BLOCK_SIZE - 1)))
#define BIT_BLOCK_COUNT(BITS) (((BITS) + BIT_BLOCK_SIZE - 1) / BIT_BLOCK_SIZE)



typedef enum
{

    MESH_KEY_TRANSITION_TO_PHASE_2 = 0x2,
    MESH_KEY_TRANSITION_TO_PHASE_3,
} mesh_key_refresh_transition_t;


typedef uint16_t netkey_index_t;
typedef uint16_t appkey_index_t;


typedef uint8_t netkey_handle_t;
typedef uint8_t appkey_handle_t;
typedef uint8_t devkey_handle_t;

#define INVALID_DEV_HANDLER 0x00000000


//typedef uint16_t config_msg_key_index_12_t;

/** Message format for the Key Refresh Phase Get message. */
typedef struct 
{
    mesh_global_idx_t netkey_index; /**< Index of the network to get the key refresh phase for. */
} __attribute((packed)) config_msg_key_refresh_phase_get_t;

/** Message format for the Key Refresh Phase Set message. */
typedef struct 
{
    mesh_global_idx_t netkey_index; /**< Index of the network to set the key refresh phase for. */
    mesh_key_refresh_transition_t transition;                     /**< ID of the phase to transition to. */
} __attribute((packed)) config_msg_key_refresh_phase_set_t;

/** Message format for the Key Refresh Phase Status message. */
typedef struct 
{
    uint8_t status;                         /**< Status code. */
    mesh_global_idx_t netkey_index; /**< Index of the network the key refresh phase is reported for. */
    uint8_t phase;                          /**< Current key refresh phase for the subnet. */
} __attribute((packed)) config_msg_key_refresh_phase_status_t;

/** Message format for the Network Key Add/Update messages. */
typedef struct 
{
    mesh_global_idx_t netkey_index;              /**< Network key index. */
    uint8_t                   netkey[MESH_KEY_LENGTH]; /**< Network key contents. */
} __attribute((packed)) config_msg_netkey_add_update_t;

/** Message format for the Network Key Delete message. */
typedef struct 
{
    mesh_global_idx_t netkey_index; /**< Network key index. */
} __attribute((packed)) config_msg_netkey_delete_t;

/** Message format for the Network Key Status message. */
typedef struct
{
    uint8_t status;                         /**< Status code. */
    mesh_global_idx_t netkey_index; /**< Network key index.*/
} __attribute((packed)) config_msg_netkey_status_t;



uint8_t mesh_kr_Get_tx_key_index(net_key_t *netkey);
uint8_t mesh_kr_Get_beacon_key_index(net_key_t *netkey);
uint8_t mesh_kr_Get_beacon_key_newindex(net_key_t *netkey);
uint8_t mesh_get_key_refresh(net_key_t *netkey);

void mesh_kr_log(int8_t level, const char * format, ...);

bool bit_get(const uint8_t * p_bitfield, uint32_t bit);
void bit_set(uint8_t * p_bitfield, uint32_t bit);
void bit_clear(uint8_t * p_bitfield, uint32_t bit);



#endif

