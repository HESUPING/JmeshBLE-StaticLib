/*
 * security_kn.c
 *
 *  Created on: 2017��10��11��
 *      Author: wz
 */

#include "security_kn.h"
#include "../base/aes128_cmac.h"

int security_AES_CMAC(uint8_t* key, uint16_t len_msg, uint8_t* msg, uint8_t* MAC)
{
    LoadMacKey(key);
    GenerateMAC(len_msg, msg, MAC);
    return 16;
}

int security_s1_salt_generation(uint8_t* m, uint8_t len_m, uint8_t* s1)
{
    uint8_t zeros[16];
    memset(zeros, 0, 16);
    return security_AES_CMAC(zeros, len_m, m, s1);
}


void security_k1_derivation(uint8_t* n, uint8_t len_n, uint8_t* p, uint8_t len_p, uint8_t* salt, k1_result_t* k1_result)
{
    uint8_t t[16] = {0};
    security_AES_CMAC(salt, len_n, n, t);
    security_AES_CMAC(t, len_p, p, k1_result->k1);
}

void security_k2_derivation(uint8_t* n, uint8_t* p, uint8_t len_p, k2_result_t* k2_result)
{
    uint8_t salt[16] = {0x4f,0x90,0x48,0x0c,0x18,0x71,0xbf,0xbf,0xfd,0x16,0x97,0x1f,0x4d,0x8d,0x10,0xb1};
    uint8_t T[16];
//    char* str = "smk2";
//    security_s1_salt_generation((uint8_t*)str, strlen(str), (uint8_t*)salt);

    security_AES_CMAC(salt, 16, n, T);


    uint8_t T1[16] = {0};
    uint8_t* T2 = k2_result->encryption_key;
    uint8_t* T3 = k2_result->privacy_key;

    uint8_t temp[33] = {0};

    //T0 = empty string (zero length)

    //T1 = AES-CMACT (T0 || P || 0x01)
    memcpy(temp, p, len_p);
    temp[len_p] = 0x01;
    security_AES_CMAC(T, 0+len_p+1, temp, T1);

    //T2 = AES-CMACT (T1 || P || 0x02)
    memcpy(temp, T1, 16);
    memcpy(temp+16, p, len_p);
    temp[16+len_p] = 0X02;
    security_AES_CMAC(T, 16+len_p+1, temp, T2);

    //T3 = AES-CMACT (T2 || P || 0x03)
    memcpy(temp, T2, 16);
    memcpy(temp+16, p, len_p);
    temp[16+len_p] = 0X03;
    security_AES_CMAC(T, 16+len_p+1, temp, T3);

    k2_result->nid = T1[15] & 0X7F;
}

void security_k3_derivation(uint8_t* n, k3_result_t* k3_result)
{
    uint8_t salt[16] = {0x00,0x36,0x44,0x35,0x03,0xf1,0x95,0xcc,0x8a,0x71,0x6e,0x13,0x62,0x91,0xc3,0x02};
    uint8_t t[16];
    uint8_t temp[16];

    uint8_t strings[5] = "smk3";
//    security_s1_salt_generation(strings, strlen(strings), salt);
    security_AES_CMAC(salt, 16, n, t);
    memset(strings, 0, 5);
    memcpy(strings, "id64", 4);
    strings[4] = 0x01;
    security_AES_CMAC(t, 5, strings, temp);
    //todo mod 2^64
    memcpy(k3_result->network_id, temp + 8, 8);
}

void security_k4_derivation(uint8_t* n, k4_result_t* k4_result)
{
    uint8_t t[16] = {0};
    uint8_t salt[16] = {0x0e,0x9a,0xc1,0xb7,0xce,0xfa,0x66,0x87,0x4c,0x97,0xee,0x54,0xac,0x5f,0x49,0xbe};
    uint8_t output[16];
    uint8_t strings[5] = "smk4";
//    security_s1_salt_generation(strings, strlen(strings), salt);
    security_AES_CMAC(salt, 16, n, t);
    memset(strings, 0, 5);
    memcpy(strings, "id6", 3);
    strings[3] = 0x01;
    security_AES_CMAC(t, 4, strings, output);
    *k4_result = output[15] & 0x3f;
}
