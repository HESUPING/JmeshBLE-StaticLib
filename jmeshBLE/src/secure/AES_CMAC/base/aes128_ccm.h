/*
 * aes128_ccm.h
 *
 *  Created on: 2017��10��10��
 *      Author: wz
 */

#ifndef SECURITY_BASE_AES128_CCM_H_
#define SECURITY_BASE_AES128_CCM_H_

#include "aes128.h"

#define Master 1    //control the direction bit
#define AES_BUFF_SIZE 400
#define MIC32 4
#define MIC64 8

typedef enum _MIC_MODE{
    MODE_MIC32 = 4,
    MODE_MIC64 = 8
}MIC_MODE;

typedef struct{
    uint8_t len;
    uint8_t mac[16];
}mac_t;

/// COUNTER MODE BLOCKS
//IV
struct _B0_T{
    uint8_t Flags;
    uint8_t Nonce[13];
    uint8_t Len_Payload_h;
    uint8_t Len_Payload_l;
};

struct _B1_T{
    uint8_t Len_ADD_h;
    uint8_t Len_ADD_l;
    uint8_t ADD;
    uint8_t Padding[13];
};

/// ENCRYPTION BLOCKS
struct _Ax_t{
    uint8_t Flags;
    uint8_t Nonce[13];
    uint8_t Counter_h;
    uint8_t Counter_l;
};

typedef struct _aes_ccm_t{
    uint8_t len_data;
    uint8_t* data;
    uint8_t mic[MIC64];
}aes_ccm_t;


mac_t    aes_cbc_mac(uint8_t* key, uint8_t dat[], uint8_t len_dat);
uint16_t generate_blocks2(uint8_t addition_data, uint8_t* Nonce, uint8_t* payload, uint16_t payload_len, uint8_t** blocks);
void     CTR_encrypt(uint8_t* key,  uint8_t* Nonce, mac_t mic, uint8_t* dat, uint8_t len_dat, MIC_MODE mic_mode);
void     CTR_decrypt(uint8_t* key,  uint8_t* Nonce,  uint8_t* dat, uint8_t len_dat, MIC_MODE mic_mode);
void     security_aes_ccm_encrypt2(uint8_t* key, uint8_t* Nonce, uint8_t* dat, uint16_t dat_len, uint8_t a_data, MIC_MODE mic_mode);
uint8_t  security_aes_ccm_decrypt2(uint8_t* key, uint8_t* Nonce, uint8_t* dat, uint16_t dat_len, uint8_t a_data, MIC_MODE mic_mode);


#endif /* SECURITY_BASE_AES128_CCM_H_ */
