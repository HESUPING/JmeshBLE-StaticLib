#ifndef UPPER_TRANSPORT_H_
#define UPPER_TRANSPORT_H_
#include <stdint.h>
#include "sdk_mesh_config.h"
#include "mesh_env.h"
#include "security.h"
#include "bx_ring_queue.h"

#define TRANSMIC_64BIT 8
#define TRANSMIC_32BIT 4
#define IS_VIRTUAL_ADDR(addr) (((addr)&0x8000)&&((~addr)&0x4000))

#define UPPER_TRANSPORT_RX_QUEUE_LENGTH 10
#define UPPER_TRANSPORT_TX_QUEUE_LENGTH 10
#define ACCESS_MATCHED_KEY_MAX_NUM 2
#define VIRT_ADDR_MATCHED_BUF_SIZE 3
#define SEGMENTATION_TRANSMISSION_TIMER_MIN 250
#define AKF_MASK 0x40
#define AKF_OFFSET 6
#define AID_MASK 0x3f
#define AID_OFFSET 0



enum upper_pdu_tx_stat
{
    UPPER_TX_SUCCESS,
    UPPER_TX_CANCEL,
};
typedef struct
{
    upper_pdu_base_t *base;
}upper_transport_tx_env_t;
typedef struct
{
    virt_addr_mngt_t *buf[VIRT_ADDR_MATCHED_BUF_SIZE];
    uint8_t matched_num;
    uint8_t idx;
}virt_addr_match_env_t;
typedef struct
{
    upper_pdu_base_t *base;
    aes_ccm_param_t enc_param;
    uint8_t nonce[NONCE_LENGTH];
    key_ptr_t matched_appkey[ACCESS_MATCHED_KEY_MAX_NUM];
    uint8_t matched_num;
    uint8_t idx;
    virt_addr_match_env_t virt_addr_match;
}upper_transport_rx_env_t;
extern upper_transport_rx_env_t upper_transport_rx_env;
extern upper_transport_tx_env_t upper_transport_tx_env;
extern ring_queue_t upper_transport_rx_q;
segmentation_mngt_t *bind_segmentation_mngt(upper_pdu_base_t *ptr);void fill_app_dev_nonce(uint8_t *nonce,uint8_t nonce_type,upper_pdu_base_t *base);
void upper_transport_free_rx_access_pdu(access_pdu_rx_t *ptr);
void upper_pdu_tx_ack_received(network_pdu_base_t *ptr,uint8_t obo,uint16_t seqzero,uint32_t block_ack);
void upper_transport_pdu_tx(upper_pdu_base_t *base);
void upper_transport_pdu_rx(void);
void upper_transport_init(void);
#endif

