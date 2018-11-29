/*
 * mesh_test.c
 *
 *  Created on: 2018-3-20
 *      Author: jiachuang
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "osapp_mesh.h"
#include "security.h"
#include "bx_ring_queue.h"
#include "log.h"
#include "mesh_test_config.h"
#ifdef MESH_CCM_CMAC_QUEUE_TEST



//Mesh message #4
//COMMON
#define TEST_MSG_LENGTH 4
uint8_t test_key[]   = {0xbe,0x63,0x51,0x05,0x43,0x48,0x59,0xf4,0x84,0xfc,0x79,0x8e,0x04,0x3c,0xe4,0x0e};
uint8_t test_nonce[] = {0x00,0x80,0x00,0x00,0x02,0x12,0x01,0x00,0x00,0x12,0x34,0x56,0x78};
//ENC
uint8_t test_src_msg[]   = {0x23,0x45,0x01,0x00};
aes_ccm_param_t test_enc_aes_ccm_para;
uint8_t test_mesh_encrypted_data[40]={0};
//DEC
uint8_t test_enced_msg[12]   = {0xb0,0xe5,0xd0,0xad,0x97,0x0d,0x57,0x9a,0x4e,0x88,0x05,0x1c};
aes_ccm_param_t test_dec_aes_ccm_para;
volatile uint8_t test_mesh_decrypted_data[12];

//CMAC Example2
#define CMAC_KEY_LEN    16
#define CMAC_M_LEN      16
#define CMAC_RES_LEN    16
uint8_t cmac_key[CMAC_KEY_LEN] = {0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C};
uint8_t cmac_msg[CMAC_M_LEN  ] = {0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,0x7E,0x11,0x73,0x93,0x17,0x2A};
uint8_t cmac_res[CMAC_RES_LEN] = {0};//070A16B4 6B4D4144 F79BDD9D D04A287C



void test_mesh_enc_cb(void)
{
    LOG(3,"ENCRIPTED OK\n");
}
void test_mesh_dec_cb(void)
{
    LOG(3,"DECRIPTED OK\n");
}
void test_mesh_cmac_cb(void)
{
    LOG(3,"CMAC OK\n");
}


void test_data_init()
{
    //CCM_ENC
    test_enc_aes_ccm_para.key               = test_key;
    test_enc_aes_ccm_para.nonce             = test_nonce;
    test_enc_aes_ccm_para.msg               = test_src_msg;
    test_enc_aes_ccm_para.additional_data   = NULL;
    test_enc_aes_ccm_para.msg_length        = TEST_MSG_LENGTH;
    test_enc_aes_ccm_para.mic_length        = 8;
    test_enc_aes_ccm_para.additional_data_length = 0;
    //CCM_DEC
    test_dec_aes_ccm_para.key               = test_key;
    test_dec_aes_ccm_para.nonce             = test_nonce;
    test_dec_aes_ccm_para.msg               = test_enced_msg;
    test_dec_aes_ccm_para.additional_data   = NULL;
    test_dec_aes_ccm_para.msg_length        = TEST_MSG_LENGTH;
    test_dec_aes_ccm_para.mic_length        = 8;
    test_dec_aes_ccm_para.additional_data_length = 0;
}




void app_mesh_test_init(void)
{
    test_data_init();
    aes_ccm_encrypt(&test_enc_aes_ccm_para,test_mesh_encrypted_data,test_mesh_enc_cb);
    aes_ccm_decrypt(&test_dec_aes_ccm_para,test_mesh_decrypted_data,test_mesh_dec_cb);
    aes_cmac(cmac_key , cmac_msg , CMAC_M_LEN , cmac_res , test_mesh_cmac_cb);
    
}




#endif

#endif
