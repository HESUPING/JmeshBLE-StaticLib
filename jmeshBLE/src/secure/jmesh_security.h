#ifndef JMESH_SECURITY_H
#define JMESH_SECURITY_H

#include"../jmesh/jmesh_types.h"
#include"AES_CMAC/base/aes128_ccm.h"
#include"AES_CMAC/base/aes128_cmac.h"
#include"AES_CMAC/toolbox/security_kn.h"


enum{
    JMESH_NONCE_NETWWORK=0,
    JMESH_NONCE_APPLICATION=1,
    JMESH_NONCE_DEVICE=2,
    JMESH_NONCE_PROXY=3
};

typedef unsigned char jmesh_nonce_t[13];

#define jmesh_generate_network_nonce(nonce,CTL_and_TTL,seq,src,iv_index)  \
    jmesh_generate_nonce(nonce,JMESH_NONCE_NETWWORK,CTL_and_TTL,seq,src,0,iv_index)

#define jmesh_generate_application_nonce(nonce,ASZMIC_and_pad,seq,src,dst,iv_index)  \
    jmesh_generate_nonce(nonce,JMESH_NONCE_APPLICATION,ASZMIC_and_pad,seq,src,dst,iv_index)

#define jmesh_generate_device_nonce(nonce,ASZMIC_and_pad,seq,src,dst,iv_index)  \
    jmesh_generate_nonce(nonce,JMESH_NONCE_DEVICE,ASZMIC_and_pad,seq,src,dst,iv_index)

#define jmesh_generate_proxy_nonce(nonce,seq,src,iv_index)  \
    jmesh_generate_nonce(nonce,JMESH_NONCE_PROXY,0,seq,src,0,iv_index)

void jmesh_generate_nonce(unsigned char* nonce,unsigned char type,unsigned char opcode,unsigned long seq,unsigned short src,unsigned short dst,unsigned long iv_index);

int jmesh_security_encrypt(unsigned short length,unsigned char* data,unsigned char* nonce,jmesh_key_t key,unsigned char mic_length);
int jmesh_security_decrypt(unsigned short length,unsigned char* data,unsigned char* nonce,jmesh_key_t key,unsigned char mic_length);




jmesh_addr_t jmesh_security_cal_virtual_addr(unsigned char* uuid);
unsigned char jmesh_security_cal_aid(jmesh_key_t key);
unsigned char jmesh_security_cal_master_encryption_and_privacy_keys(jmesh_key_t netkey,jmesh_key_t encryption_key,jmesh_key_t privacy_key);
unsigned char jmesh_security_cal_friendship_encryption_and_privacy_keys(jmesh_key_t netkey,unsigned char* p,jmesh_key_t encryption_key,jmesh_key_t privacy_key);
void jmesh_security_cal_netid(jmesh_key_t netkey,jmesh_netid_t netid);
void jmesh_security_cal_identity_key(jmesh_key_t netkey,jmesh_key_t identity_key);
void jmesh_security_cal_beacon_key(jmesh_key_t netkey,jmesh_key_t beacon_key);

#ifdef JMESH_TEST
#ifdef JMESH_TEST_SECURITY
void jmesh_security_test(void);
#endif // JMESH_TEST_SECURITY
#endif // JMESH_TEST


#endif
