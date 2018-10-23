/*
 * security_kn.h
 *
 *  Created on: 2017��10��11��
 *      Author: wz
 */

#ifndef SECURITY_TOOLBOX_SECURITY_KN_H_
#define SECURITY_TOOLBOX_SECURITY_KN_H_

#include "../base/aes128_ccm.h"


typedef struct{
    uint8_t k1[16];
}k1_result_t;

typedef struct _k2{
    uint8_t nid:7;
    uint8_t encryption_key[16];
    uint8_t privacy_key[16];
}k2_result_t;

typedef struct {
    uint8_t network_id[8];
}k3_result_t;

typedef uint8_t k4_result_t;

int  security_AES_CMAC(uint8_t* key, uint16_t len_msg, uint8_t* msg, uint8_t* MAC);
int  security_s1_salt_generation(uint8_t* m, uint8_t len_m, uint8_t* s1);
void security_k1_derivation(uint8_t* n, uint8_t len_n, uint8_t* p, uint8_t len_p, uint8_t* salt, k1_result_t* k1_result);
void security_k2_derivation(uint8_t* n, uint8_t* p, uint8_t len_p, k2_result_t* k2_result);
void security_k3_derivation(uint8_t* n, k3_result_t* k3_result);
void security_k4_derivation(uint8_t* n, k4_result_t* k4_result);


#endif /* SECURITY_TOOLBOX_SECURITY_KN_H_ */
