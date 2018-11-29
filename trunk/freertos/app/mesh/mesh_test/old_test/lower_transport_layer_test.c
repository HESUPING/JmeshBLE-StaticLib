/*
 * lower_transport_layer_test.c
 *
 *  Created on: 2018-3-23
 *      Author: jiachuang
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "osapp_mesh.h"
#include "mesh_definitions.h"
#include "provision_base.h"
#include "beacon.h"
#include "network.h"
#include "bearer.h"
#include "co_endian.h"
#include "mesh_test_config.h"
#include "upper_transport.h"
#include "lower_transport.h"
#include "access.h"
#include "config_client.h"

#ifdef MESH_TEST_LOWER_TRANSPORT_LAYER
upper_pdu_base_t *recv;


/****start of****bearer -> network -> lower**********/
//Message #1
#define NETWORK_BEARER_LENGTH1 28
uint8_t test_bearer_data1[NETWORK_BEARER_LENGTH1]=
{0x68,0xec,0xa4,0x87,0x51,0x67,0x65,0xb5,0xe5,0xbf,0xda,0xcb,0xaf,0x6c,0xb7,0xfb,0x6b,0xff,0x87,0x1f,0x03,0x54,0x44,0xce,0x83,0xa6,0x70,0xdf};
//Message #2
#define NETWORK_BEARER_LENGTH2 24
uint8_t test_bearer_data2[NETWORK_BEARER_LENGTH2]=
{0x68,0xd4,0xc8,0x26,0x29,0x6d,0x79,0x79,0xd7,0xdb,0xc0,0xc9,0xb4,0xd4,0x3e,0xeb,0xec,0x12,0x9d,0x20,0xa6,0x20,0xd0,0x1e};
//Message #3
#define NETWORK_BEARER_LENGTH3 24
uint8_t test_bearer_data3[NETWORK_BEARER_LENGTH3]=
{0x68,0xda,0x06,0x2b,0xc9,0x6d,0xf2,0x53,0x27,0x30,0x86,0xb8,0xc5,0xee,0x00,0xbd,0xd9,0xcf,0xcc,0x62,0xa2,0xdd,0xf5,0x72};
//Message #6 segment 1
#define NETWORK_BEARER_LENGTH6 29
uint8_t test_bearer_data6[NETWORK_BEARER_LENGTH6]=
{0x68,0xca,0xb5,0xc5,0x34,0x8a,0x23,0x0a,0xfb,0xa8,0xc6,0x3d,0x4e,0x68,0x63,0x64,0x97,0x9d,0xea,0xf4,0xfd,0x40,0x96,0x11,0x45,0x93,0x9c,0xda,0x0e};
//Message #6 segment 2
#define NETWORK_BEARER_LENGTH6_2 29
uint8_t test_bearer_data6_2[NETWORK_BEARER_LENGTH6_2]=
{0x68,0x16,0x15,0xb5,0xdd,0x4a,0x84,0x6c,0xae,0x0c,0x03,0x2b,0xf0,0x74,0x6f,0x44,0xf1,0xb8,0xcc,0x8c,0xe5,0xed,0xc5,0x7e,0x55,0xbe,0xed,0x49,0xc0};

//Message #6_1-realyed1
#define NETWORK_BEARER_LENGTH6 29
uint8_t test_bearer_data6R1[NETWORK_BEARER_LENGTH6]=
{0x68,0x97,0xFD,0x4E,0x90,0x5A,0x76,0x78,0x6F,0xEF,0x6E,0xA1,0x43,0x2A,0x54,0xE2,0xC7,0x0B,0x14,0xA7,0x9C,0xF4,0xCB,0x83,0xAD,0x08,0x6E,0x7D,0xC1};
//Message #6_1-realyed2
#define NETWORK_BEARER_LENGTH6 29
uint8_t test_bearer_data6R2[NETWORK_BEARER_LENGTH6]=
{0x68,0x00,0xA2,0xFB,0x62,0x66,0x3A,0x24,0x89,0x98,0x75,0x87,0x73,0x76,0x8A,0xC9,0x91,0x0B,0xD9,0xBF,0x5D,0xF7,0x1A,0xC6,0x08,0x33,0x8D,0x2A,0x4D};

//Message #7
#define NETWORK_BEARER_LENGTH7 24
uint8_t test_bearer_data7[NETWORK_BEARER_LENGTH7]=
{0x68,0xe4,0x76,0xb5,0x57,0x9c,0x98,0x0d,0x0d,0x73,0x0f,0x94,0xd7,0xf3,0x50,0x9d,0xf9,0x87,0xbb,0x41,0x7e,0xb7,0xc0,0x5f};

/***end of*****bearer -> network -> lower**********/


/****start of*****COMMON***********/
uint8_t test_net_key[MESH_KEY_LENGTH] = {0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
key_ptr_t test_keys;//test network layer
net_key_box_t generate_test_keys;//only test security toolbox
net_key_t test_netket_list;
volatile uint8_t waitinf_for_gen_done = 0;


void generate_keys_test_cb(void)
{
    waitinf_for_gen_done =1;
    LOG(3,"ALL KEYS GENERATE DONE");
}
void generate_keys_test(void)
{
    memcpy(generate_test_keys.netkey , test_net_key , MESH_KEY_LENGTH);
    generte_all_net_keys(&generate_test_keys , generate_keys_test_cb);
}
void generate_keys(void)
{
    test_keys.key.net = &test_netket_list;
    memcpy(test_keys.key.net->key[0].netkey , test_net_key , MESH_KEY_LENGTH);
    generte_all_net_keys(&test_keys.key.net->key[0] , generate_keys_test_cb);
    while(waitinf_for_gen_done == 0);
}
/******end of***COMMON***********/



void app_lower_test_deliver_to_upper_call(upper_pdu_base_t *ptr)
{
    recv=ptr;
    LOG(3,"app_lower_test_deliver_to_upper_call\n");
    LOG(3,"app_lower_test_deliver_to_upper_call\n");
}

void bear_to_net_to_lower_test(void)
{
    //bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data1,NETWORK_BEARER_LENGTH1);
    //bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data7,NETWORK_BEARER_LENGTH7);
    bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data6,NETWORK_BEARER_LENGTH6);
    bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data6_2,NETWORK_BEARER_LENGTH6_2);
}


#if 0
//Example 1
#define UPPER_TEST_UNSEG_MSG
#define UPPER_TEST_SEQ      0x000001
#define UPPER_TEST_HEADER   0x03
#define UPPER_TEST_CTL      0x01
#define UPPER_TEST_TTL      0x00
#define UPPER_TEST_SRCADDR  0x1201
#define UPPER_TEST_SRCDST   0xFFFD
#define UPPER_TEST_ININDEX  0x12345678

#define UPPER_TEST_MSG_LTNGTH  10
uint8_t upper_test_msg[UPPER_TEST_MSG_LTNGTH]={0x4b,0x50,0x05,0x7e,0x40,0x00,0x00,0x01,0x00,0x00};
#endif

#if 0
//Example 6.1
#define UPPER_TEST_SEG_MSG
#define UPPER_TEST_SEQ      0x3129ab
#define UPPER_TEST_CTL      0x00
#define UPPER_TEST_TTL      0x04
#define UPPER_TEST_SRCADDR  0x0003
#define UPPER_TEST_SRCDST   0x1201
#define UPPER_TEST_ININDEX  0x12345678
#define UPPER_TEST_MIC      0x00

#define UPPER_TEST_SEGN     0x01
#define UPPER_TEST_SEGO     0x00


#define UPPER_TEST_MSG_LTNGTH  12
uint8_t upper_test_msg[UPPER_TEST_MSG_LTNGTH]={0xee,0x9d,0xdd,0xfd,0x21,0x69,0x32,0x6d,0x23,0xf3,0xaf,0xdf};
#endif

#if 1
//Example 6.2
#define UPPER_TEST_SEG_MSG
#define UPPER_TEST_SEQ      0x3129ac
#define UPPER_TEST_CTL      0x00
#define UPPER_TEST_TTL      0x04
#define UPPER_TEST_SRCADDR  0x0003
#define UPPER_TEST_SRCDST   0x1201
#define UPPER_TEST_ININDEX  0x12345678
#define UPPER_TEST_MIC      0x00

#define UPPER_TEST_SEGN     0x01
#define UPPER_TEST_SEGO     0x01


#define UPPER_TEST_MSG_LTNGTH  12
uint8_t upper_test_msg[UPPER_TEST_MSG_LTNGTH]={0xcf,0xdc,0x18,0xc5,0x2f,0xde,0xf7,0x72,0xe0,0xe1,0x73,0x08};
#endif

upper_pdu_base_t test_upper;
segmentation_mngt_t test_seg_mng;
void upper_to_lower_test_callback(void)
{
    LOG(3,"OK\n");
}

void upper_to_lower_test(void)
{
    extern uint32_t sequence_number;
    sequence_number = UPPER_TEST_SEQ;

    test_upper.ctl =        UPPER_TEST_CTL;
    test_upper.ttl_for_tx = UPPER_TEST_TTL;
    test_upper.src_addr =   UPPER_TEST_SRCADDR;
    test_upper.dst_addr =   UPPER_TEST_SRCDST;
    test_upper.iv_index =   UPPER_TEST_ININDEX;
    test_upper.netkey =     test_keys;
#ifdef UPPER_TEST_UNSEG_MSG
    test_upper.header.byte = UPPER_TEST_HEADER;
#endif
#ifdef UPPER_TEST_SEG_MSG
    test_upper.mic_length = UPPER_TEST_MIC;
    test_upper.seq_auth_lsb = LSB(sequence_number-UPPER_TEST_SEGO,SEQZERO_LENGTH);

    test_seg_mng.SegN    =  UPPER_TEST_SEGN;
    test_seg_mng.SegO    =  UPPER_TEST_SEGO;

    test_upper.mngt.segmentation = &test_seg_mng;
    test_seg_mng.upper = &test_upper;
#endif
    //send
    lower_transport_tx(&test_upper,upper_test_msg,UPPER_TEST_MSG_LTNGTH,upper_to_lower_test_callback);
}




/***start of***config_client->access->upper->lower->bear*********/

uint8_t test_app_key_val[16]={0x63,0x96,0x47,0x71,0x73,0x4f,0xbd,0x76,0xe3,0xb4,0x05,0x19,0xd1,0xd9,0x4a,0x48};
model_base_t test_model;
mesh_elmt_t test_mesh_elmt;

app_key_t test_app_key_list;
app_key_box_t test_app_key;
net_key_t test_net_key_list;

void config_client_test_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_client_test_cb\n");
    LOG(3,"config_client_test_cb\n");

}

void config_client_test(void)
{
    test_mesh_elmt.uni_addr = 0x0003;
    test_app_key_list.curr_idx = 0;
    test_app_key_list.global_idx = 0x456;
    test_net_key_list.global_idx = 0x123;

    test_model.elmt = &test_mesh_elmt;
    test_app_key_list.bound_netkey = &test_net_key_list;
    memcpy(test_app_key_list.key[0].key , &test_app_key_val , 16);

    extern uint32_t sequence_number;
    sequence_number = 0x3129ab;
    mesh_beacon_iv_index_set(0x12345678);
    config_appkey_add_tx(&test_model,&test_app_key_list,0x1201,config_client_test_cb);

}


/**end of****config_client->access->upper->lower->bear*********/
void test_mesh_app_init()
{
    extern void mesh_app_init();
    extern void init_elmt_addr(uint16_t addr);
    extern void config_server_add_netkey(uint8_t *netkey,uint16_t netkey_idx,uint8_t *status);
    uint8_t status=0;
    mesh_app_init();
    init_elmt_addr(0x1203);
    init_elmt_addr(0x1201);
    config_server_add_netkey(test_net_key,0x123,&status);
}
void app_mesh_test_init(void)
{
    //iv_index = 0x12345678;
    mesh_beacon_iv_index_set(0x12345678);
    //INIT
    security_init();
    generate_keys();
    upper_transport_init();
    //TEST
    test_mesh_app_init();
    bear_to_net_to_lower_test();
    //upper_to_lower_test();
    //config_client_test();
}

/*

*********************************************************************************************************
bear->network->lower->(upper)
    Unsegement:
        Normal msg (Example #1)             -- OK
        Segment Ack msg (Example #7)        -- OK
    Segemented:
        2 seg:Message #6                    -- OK  (<- relay*2+ack*1)
        
*********************************************************************************************************

upper->lower->bear
    Unsegement:
        Example 1                     --OK
    Segemented:
        Message #6.1                    --OK
        Message #6.2                    --OK


exception
    bear->network->lower->(upper)
        segmement msg timeout , only receive #6.1,no#6.2 -> relay*1 + timeout_ack*1     --OK

*********************************************************************************************************

    
SeqAuthLsb
        LOG(3,"A=0x%x\n",seq_auth_lsb(0x647262,0x1849));
        LOG(3,"B=0x%x\n",seq_auth_lsb(0x647262,0x1263));
        LOG(3,"C=0x%x\n",seq_auth_lsb(0x3129ab,0x9ab));
        LOG(3,"D=0x%x\n",seq_auth_lsb(0x3129ac,0x9ab));
        --PASS

*********************************************************************************************************


bear->network->lower->upper->access->config_appkey_add_rx->status_tx
    Message #6.1+Message #6.2       --OK

*********************************************************************************************************

config_client->access->upper->lower->bear
    Message part1 and part2 OK .


*********************************************************************************************************

*/
#endif
#endif
