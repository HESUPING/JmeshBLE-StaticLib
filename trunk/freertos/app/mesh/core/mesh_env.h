#ifndef MESH_ENV_H_
#define MESH_ENV_H_
#include <stdint.h>
#include "sdk_mesh_config.h"
#include "osapp_mesh.h"
#include "mesh_model.h"
#include "bearer.h"
#include "network_keys_dm.h"
#include "mesh_core_api.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define NETWORK_MATCHED_KEY_MAX_NUM 3

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
//===================gatt network===========================<<<<<<<<<<<<<<<
/**
 * @brief Callback function type for Mesh network pdu decrypt.
 *
 * @param[in] p_pdu 	  Pointer to the network pdu database.
 * @param[in] length      The length of the decrypt data.
 * @param[in] conn_index  gatt connect index.
 *
 */
typedef void (*network_pdu_decrypt_cb_t)(const void *p_pdu,uint16_t length,uint16_t conn_index);

/** RX data From type. */
typedef enum
{
    MESH_RX_FROM_GATT,    /**< The data came from a GATT connection. */
    MESH_RX_FROM_SCANNER, /**< The data came from the scanner. */
    MESH_RX_FROM_FRIEND,  /**< The data came from a friend node. */
    MESH_RX_FROM_LOW_POWER,  /**< The data came from a low power node. */
    MESH_RX_FROM_LOOPBACK,  /**< The data came from this device. */
    MESH_RX_FROM_DECRYPT,  /**< The data came from inter decrypt. */
	MESH_RX_FROM_INVALID  /**< The data came from invalid error. */
} mesh_rx_from_t;

/** TX data From type. */
typedef enum
{
    MESH_TX_FROM_GATT,    /**< The data came from a GATT connection. */
    MESH_TX_FROM_SCANNER, /**< The data came from the scanner. */
    MESH_TX_FROM_FRIEND,  /**< The data came from a friend node. */
    MESH_TX_FROM_LOW_POWER,  /**< The data came from a low power node. */
    MESH_TX_FROM_LOOPBACK,  /**< The data came from this device. */
    MESH_TX_FROM_RELAY,  /**< The data came from relay. */
    MESH_TX_FROM_ENCRYPT,  /**< The data came from inter encrypt. */
	MESH_TX_FROM_INVALID  /**< The data came from invalid error. */
} mesh_tx_from_t;

/** Mesh GATT Network packet structure. */
typedef struct
{
    uint16_t connection_index; /**< Proxy connection index the packet was received from. */
} mesh_gatt_network_rx_t;

/** Mesh Scanner Network packet structure. */
typedef struct
{
    int8_t rssi; /**< RSSI value of the received packet. */
} mesh_scanner_network_rx_t;

/** Mesh decrypt Network packet structure. */
typedef struct
{
	uint16_t conn_index;
} mesh_decrypt_network_rx_t;

/** Mesh encrypt Network packet structure. */
typedef struct
{
	uint16_t conn_index;
} mesh_encrypt_network_tx_t;

/** RX From type params. */
typedef struct
{
	mesh_rx_from_t rx_from; /**< Source of the received data. */
    union
    {
        /** GATT packet metadata */
		mesh_gatt_network_rx_t gatt;
		mesh_scanner_network_rx_t scanner;
		mesh_decrypt_network_rx_t decrypt;
    } params;
} mesh_rx_params_t;

/** TX From type params. */
typedef struct
{
	mesh_tx_from_t	tx_from; /**< Source of the received data. */
    union
    {
        /** GATT packet metadata */
		mesh_encrypt_network_tx_t encrypt;
    } params;
} mesh_tx_params_t;
//===================gatt network===========================>>>>>>>>>>>>>>>
typedef struct
{
    uint8_t data[BEARER_BUF_SIZE];
    uint8_t length;
    bool is_used;
}network_rx_buf_t;
typedef  struct
{
    union{
        mesh_tx_buf_t *tx;
        network_rx_buf_t *rx;
    }buf;
    uint32_t iv_index;
    uint32_t ctl_ttl_seq_num;
    uint16_t src_addr;
    uint16_t dst_addr;
    key_ptr_t netkey;
    uint8_t network_raw_data[BEARER_BUF_SIZE];
    uint8_t ivi_nid;
    uint8_t encrypted_length;
    uint8_t mic_length;
    bool is_used;
    union{
    mesh_rx_params_t rx_params; /**< Source of the received data. */
    mesh_tx_params_t tx_params;
    }io_param;
}network_pdu_base_t;
typedef struct
{
    network_pdu_base_t base;
}lower_pdu_rx_t;

typedef struct
{
    TimerHandle_t incomplete;
    TimerHandle_t acknowledgment;
}lower_transport_rx_timer_t;
struct reassembly_base_s;
typedef struct
{
    struct reassembly_base_s *reassembly_base;
    lower_transport_rx_timer_t timer;
    uint8_t seg_num;
}reassembly_mngt_t;
struct upper_pdu_base_s;
typedef struct
{
    struct upper_pdu_base_s *upper;
    TimerHandle_t segment_tx;
    uint32_t seg_acked;
    uint8_t SegN;
    uint8_t SegO;
    uint8_t retransmit_cnt;
    uint8_t cancel_current_transmit;
}segmentation_mngt_t;
typedef union
{
    uint8_t byte;
    struct
    {
        uint8_t head:7,
                   seg:1;
    }field;

}lower_transport_header_t;
typedef struct upper_pdu_base_s
{
    union{
        reassembly_mngt_t *reassembly;
        segmentation_mngt_t *segmentation;
    }mngt;
    uint8_t *upper;
    uint32_t seq_auth_lsb: 24,
                    ttl_for_tx: 7,
                    ctl: 1;
    uint32_t iv_index;
    key_ptr_t netkey;
    uint16_t total_length;
    uint16_t src_addr;
    uint16_t dst_addr;
    lower_transport_header_t header;
    uint8_t mic_length;
    bool is_used;
}upper_pdu_base_t;
typedef struct
{
    upper_pdu_base_t base;
    uint8_t *access;
    key_ptr_t appkey;
    virt_addr_mngt_t *virt_addr;
}access_pdu_base_t;
typedef struct access_pdu_tx_s
{
    access_pdu_base_t base;
    TimerHandle_t rsp_delay;
    void (*cb)(struct access_pdu_tx_s *,uint8_t);
}access_pdu_tx_t;
typedef struct transport_ctrl_pdu_tx_s
{
    upper_pdu_base_t base;
    void (*cb)(struct transport_ctrl_pdu_tx_s *,uint8_t);
}transport_ctrl_pdu_tx_t;

typedef upper_pdu_base_t transport_ctrl_pdu_rx_t;
typedef access_pdu_base_t access_pdu_rx_t;










#define PACK_2_KEY_IDX(buf_ptr,key_id0,key_id1) \
            do{                                                                                   \
                (buf_ptr)[0] = (key_id0) & 0xff;                        \
                (buf_ptr)[1] = (((key_id0) >> 8) & 0xf) | (((key_id1)&0xf)<<4);\
                (buf_ptr)[2] = ((key_id1)>>4)&0xff;                 \
            }while(0)
#define FETCH_2_KEY_IDX(buf_ptr,key_id0_ptr,key_id1_ptr) \
           do{                                                                                                      \
            *(key_id0_ptr) = (((buf_ptr)[1]&0x0f)<<8) | (buf_ptr)[0]; \
           *(key_id1_ptr) = ((buf_ptr)[2]<<4) | (((buf_ptr)[1]&0xf0)>>4); \
          } while(0)






mesh_elmt_t *get_mesh_elmt(void);
void init_elmt_addr(uint16_t addr);
void mesh_node_init(mesh_elmt_t *elmt_buf);
void mesh_element_init(uint8_t elmt_idx,model_base_t *model);
void mesh_model_init(model_base_t *model,uint32_t model_id,bool sig_model,uint8_t bound_key_buf_size,app_key_t **bound_key_buf);
void model_publish_subscribe_bind(model_base_t *model,model_publish_state_t *publish,mesh_addr_t *subscription_list,uint8_t subscription_list_size);

mesh_elmt_t *get_elmt_by_uni_addr(uint16_t uni_addr);
dm_netkey_handle_t get_netkey_by_dst_addr(uint16_t addr);

model_base_t *get_model_inst_from_elmt(mesh_elmt_t *elmt,uint32_t model_id,bool sig_model);
bool appkey_model_check(model_base_t *model_inst,key_ptr_t *appkey);

uint8_t ivi_nid_gen(uint32_t iv_index,key_ptr_t *netkey);
uint8_t get_nid(key_ptr_t *netkey);
uint8_t get_ttl(mesh_elmt_t *elmt);
uint8_t *get_netkey(key_ptr_t *ptr);

uint8_t get_aid(key_ptr_t *ptr);
uint8_t *get_appkey(key_ptr_t *ptr);
uint8_t *get_encryption_key(key_ptr_t *ptr);
uint8_t *get_privacy_key(key_ptr_t * ptr);
uint32_t get_local_iv_index(void);





void config_add_devkey(uint8_t * devkey , uint16_t addr);
void config_client_del_devkey(uint16_t addr);


//config mesh features
void mesh_node_feature_config_init(void);
void bind_appkey_to_model(model_base_t *model,uint16_t appkey_idx,uint8_t *status);



/**
 ****************************************************************************************
 * @brief The mesh node get primary element addr.
 *     (the unicast address of its primary element)
 *
 * @return uni_addr  primary element unicast addr.
 *
 ****************************************************************************************
 */
extern uint16_t mesh_node_get_primary_element_addr(void);


dm_netkey_handle_t  mesh_sec_beacon_get_netlist(uint8_t index);
uint8_t mesh_sec_beacon_get_net_index(uint8_t *network_id);

dm_netkey_handle_t mesh_sec_beacon_get_netlist_by_netid(uint8_t *network_id);




transport_ctrl_pdu_rx_t *alloc_transport_ctrl_pdu_rx_buf(void);
void free_transport_ctrl_pdu_rx_buf(transport_ctrl_pdu_rx_t *ptr);
access_pdu_rx_t *alloc_access_pdu_rx_buf(void);
void free_access_pdu_rx_buf(access_pdu_rx_t *ptr);
lower_pdu_rx_t *alloc_lower_pdu_rx_buf(void);
void free_lower_pdu_rx_buf(lower_pdu_rx_t *ptr);
#endif

