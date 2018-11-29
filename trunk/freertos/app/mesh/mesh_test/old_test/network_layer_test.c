/*
 * network_layer_test.c
 *
 *  Created on: 2018-3-6
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
#include "mesh_iv_operation_ex.h"

#ifdef MESH_TEST_NETWORK_LAYER

/********bearer -> network -> lower**********/
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
//Message #6
#define NETWORK_BEARER_LENGTH6 29
uint8_t test_bearer_data6[NETWORK_BEARER_LENGTH6]=
{0x68,0xca,0xb5,0xc5,0x34,0x8a,0x23,0x0a,0xfb,0xa8,0xc6,0x3d,0x4e,0x68,0x63,0x64,0x97,0x9d,0xea,0xf4,0xfd,0x40,0x96,0x11,0x45,0x93,0x9c,0xda,0x0e};
//Message #6-realyed1
#define NETWORK_BEARER_LENGTH6 29
uint8_t test_bearer_data6R1[NETWORK_BEARER_LENGTH6]=
{0x68,0x97,0xFD,0x4E,0x90,0x5A,0x76,0x78,0x6F,0xEF,0x6E,0xA1,0x43,0x2A,0x54,0xE2,0xC7,0x0B,0x14,0xA7,0x9C,0xF4,0xCB,0x83,0xAD,0x08,0x6E,0x7D,0xC1};
//Message #6-realyed2
#define NETWORK_BEARER_LENGTH6 29
uint8_t test_bearer_data6R2[NETWORK_BEARER_LENGTH6]=
{0x68,0x00,0xA2,0xFB,0x62,0x66,0x3A,0x24,0x89,0x98,0x75,0x87,0x73,0x76,0x8A,0xC9,0x91,0x0B,0xD9,0xBF,0x5D,0xF7,0x1A,0xC6,0x08,0x33,0x8D,0x2A,0x4D};

/********bearer -> network -> lower**********/


/*********COMMON***********/
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
/*********COMMON***********/



/********lower -> network -> bearer**********/
//Example6(Data-2)
#if 1
#define TEST_CTL    0x00
#define TEST_TTL    0x04
#define TEST_SEQ    0x3129AC
#define TEST_SRC_ADDR   0x0003
#define TEST_DST_ADDR   0x1201
#define TEST_PDU_LEN    16
uint8_t test_dst_data[TEST_PDU_LEN] = {0x80,0x26,0xac,0x21,0xcf,0xdc,0x18,0xc5,0x2f,0xde,0xf7,0x72,0xe0,0xe1,0x73,0x08};
#endif
//Example1
#if 0
#define TEST_CTL    0x01
#define TEST_TTL    0x00
#define TEST_SEQ    0x000001
#define TEST_SRC_ADDR   0x1201
#define TEST_DST_ADDR   0xFFFD
#define TEST_PDU_LEN    11
uint8_t test_dst_data[TEST_PDU_LEN] = {0x03,0x4b,0x50,0x05,0x7e,0x40,0x00,0x00,0x01,0x00,0x00};
#endif

network_pdu_base_t *test_network_pdu_ptr;


void lower_send_ok_callback1(void)
{
    LOG(3,"lower_send_ok_callback\n");
}
void lower_send_ok_callback2(void)
{
    LOG(3,"lower_send_ok_callback\n");
}
void lower_send_ok_callback3(void)
{
    LOG(3,"lower_send_ok_callback\n");
}

void send_lower_to_net_to_bear_test(void (*cb)())
{
    test_network_pdu_ptr = alloc_network_tx_env();
    network_pdu_base_t *ptr = test_network_pdu_ptr;
    ptr->ctl_ttl_seq_num = (uint32_t)TEST_CTL<<CTL_OFFSET | ((uint32_t)TEST_TTL)<<TTL_OFFSET | TEST_SEQ;
    ptr->src_addr = TEST_SRC_ADDR;
    ptr->dst_addr = TEST_DST_ADDR;
    ptr->netkey = test_keys;
    ptr->iv_index = mesh_tx_iv_index_get();
    
    network_raw_data_fill(ptr,test_dst_data,TEST_PDU_LEN,0);
    network_pdu_tx(ptr,cb);
}

void lower_to_net_to_bear_test(void)
{
    send_lower_to_net_to_bear_test(lower_send_ok_callback1);
    send_lower_to_net_to_bear_test(lower_send_ok_callback2);
    send_lower_to_net_to_bear_test(lower_send_ok_callback3);
}

/********lower -> network -> bearer**********/



void bear_to_net_to_lower_test(void)
{
    //bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data1,NETWORK_BEARER_LENGTH1);
    //bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data1,NETWORK_BEARER_LENGTH1);
    //bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data2,NETWORK_BEARER_LENGTH2);
    //bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data3,NETWORK_BEARER_LENGTH3);
    bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data6,NETWORK_BEARER_LENGTH6);
    bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data6R1,NETWORK_BEARER_LENGTH6);
    bearer_rx(MESH_MESSAGE_AD_TYPE,test_bearer_data6R2,NETWORK_BEARER_LENGTH6);
}

void app_mesh_test_init(void)
{
    //INIT
    security_init();
    generate_keys();
    //TEST
    bear_to_net_to_lower_test();
    //lower_to_net_to_bear_test();
}

/*
TEST RESULT
bear->network->lower        @ Exampl:1/2/3/6  (simple test)         --  OK 
lower->network->bear        @ Exampl:1/6      (simple test)         --  OK 
bear->network->relay->bear  @Example6         Relay 2 times         --  OK          @NetworkLayer-RelayTest.txt
multi data transfer:lower->bear                                     --  OK          (Add AES_CCM_CMAC QUEUE)
multi data transfer:bear->lower                                     --  OK
same data in cache ignore                                           --  OK



*/
#endif
#endif
