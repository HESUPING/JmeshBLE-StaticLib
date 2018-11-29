#ifndef LOWER_TRANSPORT_H_
#define LOWER_TRANSPORT_H_
#include <stdint.h>
#include "network.h"

#define SEQZERO_LENGTH 13
#define SEGMENTED_ACCESS_MSG_MAX_LENGTH 12
#define SEGMENTED_CONTROL_MSG_MAX_LENGTH 8


/*
typedef struct{
    union{
        struct{
            uint32_t block_env;
            uint16_t obo_seq_zero_rfu;
        }seg_ack;
        struct{
            uint32_t szmic_seq_zero_seqo_seqn;
        }seg_msg;
    }others;
    union{
        uint8_t access;
        uint8_t control;
    }first_byte;
}lower_transport_info_t;
*/
typedef struct{
    uint16_t dst_addr;
    uint8_t data[16];
}unencrypted_data_t;

typedef struct{
    uint8_t raw_data[BEARER_BUF_SIZE];
    uint8_t *netkey;
    uint32_t ctl_ttl_seq_num;
    uint16_t src_addr;
    uint16_t dst_addr;
    uint8_t network_nonce[NONCE_LENGTH];
    uint8_t encrypted_length;
    uint8_t mic_length;
    uint8_t ivi_nid;
}network_pdu_t;

struct lower_tx_struct{
    void (*tx_complete_cb)();
    void (*network_enc_complete_cb)(struct lower_tx_struct *);
    uint8_t *netkey;
    uint32_t ctl_ttl_seq_num;
    unencrypted_data_t *unencrypted;
    uint16_t src_addr;
    uint8_t encrypt_length;
};
typedef struct lower_tx_struct lower_tx_t;
void lower_transport_pdu_rx(network_pdu_t *network_pdu);


typedef struct
{
    network_pdu_base_t *lower_pdu;
}lower_transport_rx_env_t;
extern lower_transport_rx_env_t lower_transport_rx_env;
void free_upper_pdu_rx_buf(upper_pdu_base_t * ptr);
void lower_transport_rx(void);
void lower_transport_tx(upper_pdu_base_t *upper,uint8_t *payload,uint8_t length,uint32_t seq_num,void (*cb)());


#endif


