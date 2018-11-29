#ifndef ACCESS_H_
#define ACCESS_H_
#include <stdint.h>
#include "mesh_env.h"
#include "bx_dbg.h"
#include "virt_addr_mngt.h"
#include "access_api.h"
#include "security.h"


typedef struct
{
    access_pdu_rx_t *pdu;
}access_rx_env_t;
typedef struct
{
    access_pdu_tx_t *pdu;
    aes_ccm_param_t enc_param;
    uint8_t nonce[NONCE_LENGTH];
}access_tx_env_t;
typedef struct
{
    model_base_t *model;
    void (*cb)(access_pdu_tx_t *,uint8_t);
    virt_addr_mngt_t *virt_dst;
    uint16_t src_addr;
    uint16_t dst_addr;
    uint16_t ttl : 7,
        szmic: 1,
        seg: 1;
}access_pdu_param_t;



extern access_rx_env_t access_rx_env;
access_pdu_tx_t *alloc_access_tx_pdu(uint16_t length);
void access_tx_pdu_set(access_pdu_tx_t *ptr,access_pdu_param_t *param);
void access_pdu_tx(access_pdu_tx_t *ptr,bool as_response);
void free_access_tx_pdu(access_pdu_tx_t *ptr);
void free_access_pdu_tx_buf(access_pdu_tx_t *ptr);
void access_pdu_rx(void);

uint8_t *access_tx_pdu_get_data_buf(access_pdu_tx_t *ptr);
void access_model_publish(mesh_elmt_t *elmt,model_base_t *model,access_message_tx_t *p_tx);





#endif 

