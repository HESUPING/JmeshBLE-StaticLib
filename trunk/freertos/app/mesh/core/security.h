#ifndef SECURITY_H_
#define SECURITY_H_
#include <stdint.h>
#include "mesh_model.h"

#define AES_BLOCK_SIZE 16
#define MAC_LENGTH 16
#define S1_LENGTH MAC_LENGTH
#define K1_LENGTH MAC_LENGTH
#define NONCE_LENGTH 13
#define MSG_LENGTH_FIELD_SIZE (AES_BLOCK_SIZE -NONCE_LENGTH - 1)
#define ADDITIONAL_DATA_LENGTH_FIELD_SIZE 2
enum Decryption_Result{
  DECRYPTED,
  AUTH_FAILED,
};
enum CCM_CMAC_STATE{
    AES_CCM_CMAC_IDLE,
    AES_CCM_ENCRYPT,
    AES_CCM_DECRYPT,
    AES_CMAC_BUSY,
};
typedef struct{
    uint8_t const *key;
    uint8_t const *plain;
    uint8_t *encrypted;
    void (*cb)();
}hw_aes_buf_t;
typedef struct
{
    uint16_t friend_cnt;
    uint16_t lpn_cnt;
    uint16_t friend_addr;
    uint16_t lpn_addr;
}k2_friendship_param_t;

typedef struct
{
    uint8_t *key;
    uint8_t *nonce;
    uint8_t *msg;
    uint8_t *additional_data;
    uint8_t msg_length;
    uint8_t mic_length;
    uint8_t additional_data_length;
}aes_ccm_param_t;
typedef struct{
    uint8_t key_t[GAP_KEY_LEN];
    uint8_t t3[GAP_KEY_LEN];
    uint8_t t2[GAP_KEY_LEN];
    uint8_t t1[GAP_KEY_LEN];
    uint8_t tmp[26];
    void (*callback)(uint8_t *);
    k2_friendship_param_t friend;
    bool master;
}k2_derivation_env_t;
extern k2_derivation_env_t k2_derivation_env;

void reverse_strings(const uint8_t *src , uint8_t *dst , uint8_t length);
void aes_cmac(uint8_t const*k,uint8_t const*m,uint8_t length,uint8_t *result,void (*cb)());
void s1_salt_generation(uint8_t *m,uint8_t length,uint8_t *result, void (*cb)());
void k1_derivation(uint8_t *n,uint8_t n_len,uint8_t *salt,uint8_t *p,uint8_t p_len,uint8_t *result,void (*cb)());
void k2_derivation_master(uint8_t *n,void (*cb)(uint8_t *));
void k2_derivation_friendship(uint8_t * n,uint16_t lpn_addr,uint16_t friend_addr,uint16_t lpn_cnt,uint16_t friend_cnt, void(* cb)(uint8_t *));
void k3_derivation(uint8_t *n , uint8_t *result , void (*cb)());
void k4_derivation(uint8_t *n , uint8_t *result , void (*cb)());

void generte_all_net_keys(net_key_box_t * your_keys , void (*cb)());
void ecdh_prov_salt_to_devkey(uint8_t* ecdh , uint8_t* prov_salt , uint8_t* dev_key , void(*cb)());

void aes_128(uint8_t const*key,uint8_t const*plain,uint8_t *encrypted,void (*cb)());
void aes_128_result_ind(void);
void aes_ccm_encrypt(aes_ccm_param_t *param,uint8_t *encrypted_data,void (*cb)());
void aes_ccm_decrypt(aes_ccm_param_t *param,uint8_t *decrypted_data,void (*cb)(uint8_t));
void security_init(void (*cb)());

//=========gatt  proxy_node_identity_hash_generation =====================
extern void proxy_node_identity_hash_generation(const uint8_t * p_plain,void (*cb)(const uint8_t *p_hash,const uint8_t *p_random));

#endif


