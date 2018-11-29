

#include "osapp_config.h"

#ifdef OSAPP_MESH
#include "arch.h"
#include "mesh_definitions.h"
#include "mesh_env.h"
#include "beacon.h"
#include "co_endian.h"
#include "config_client.h"
#include "mesh_iv_operation.h"
#include "mesh_iv_operation_ex.h"
#include "mesh_model.h"
#include "network_keys_dm.h"
#include "device_keys_dm.h"
#include "app_keys_dm.h"

#include "mesh_kr_comm.h"
#include "mesh_kr_client.h"
#include "mesh_kr_server.h"
#include "mesh_kr_test.h"

#include "uart_debug_test.h"






extern void net_beacon_kr_handle(uint8_t *network_id, bool key_refresh);
extern void mesh_kr_client_kr_start(netkey_handle_t netkey_handle);


#define SERVER_ADDR 0x0010
#define NETKEY_NEW_INDEX 0x0123


void mesh_kr_test_add_dev(void)
{
    uint16_t test_unprov_uni_addr[]= {0x1000,0x1100,0x1200,0x1300,0x1400,0x1500,0x1600,0x1700};
    uint8_t test_dev_key_debug[16] = {0x9d,0x6d,0xd0,0xe9,0x6e,0xb2,0x5d,0xc1,0x9a,0x40,0xed,0x99,0x14,0xf8,0xf0,0x3f};
    config_add_devkey(test_dev_key_debug , test_unprov_uni_addr[0]);
}


void mesh_kr_test_server_init(void)
{
    
    extern void init_elmt_addr(uint16_t addr);
    extern void config_server_add_netkey(uint8_t *netkey,uint16_t netkey_idx,uint8_t *status);

	uint8_t test_prov_net_key [MESH_KEY_LENGTH]   = {0x7d,0xdd,0xdd,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
	//uint8_t test_prov_app_key[MESH_KEY_LENGTH]    = {0x63,0x96,0x47,0x71,0x73,0x4f,0xbd,0x76,0xe3,0xb4,0x05,0x19,0xd1,0xd9,0x4a,0x48};
	uint16_t test_unprov_uni_addr[]= {0x1000,0x1100,0x1200,0x1300,0x1400,0x1500,0x1600,0x1700};
	//uint16_t test_group_addr[2]                   = {0xF111,0xF222};
    uint8_t test_dev_key_debug[16] = {0x9d,0x6d,0xd0,0xe9,0x6e,0xb2,0x5d,0xc1,0x9a,0x40,0xed,0x99,0x14,0xf8,0xf0,0x3f};
    uint8_t status;
    init_elmt_addr(0x1203);
    init_elmt_addr(0x1201);
	config_add_devkey(test_dev_key_debug,test_unprov_uni_addr[0]);
    config_server_add_netkey(test_prov_net_key , NETKEY_NEW_INDEX , &status);

}


void mesh_kr_test_add_netkey(void)
{
     static uint8_t  inc_random = 0;
     uint8_t   netkey[] = {0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xdd,0xdd};
     netkey[1] = netkey[1] + inc_random;
     config_client_kr_update_netkey(0x567,netkey);
     inc_random ++;
}


extern void mesh_debug_uart_test_tx(const void *param,uint16_t len);

void mesh_kr_update_scene_test(uint32_t scene)
{
   
    uint8_t   network_id[] = {0x3e,0xca,0xff,0x67,0x2f,0x67,0x33,0x70};
    uint8_t   netkey[] = {0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
    mesh_flush_msg_cache();
    switch(scene)
    {
       case SCENE_KR_CLIENT_START_UPDATE:
       {
          mesh_kr_test_add_dev();
          mesh_kr_client_kr_start(0);
       }
       break;
       case SCENE_KR_CLIENT_RECEIVE_UPDATE_ACK:
       {
          uint16_t addr = SERVER_ADDR;
          config_client_kr_netkey_status_ack(0,addr);
       }
       break;
       case SCENE_KR_SERVER_UPDATE_NETKEY:
       {
          mesh_kr_test_server_init();
          mesh_kr_config_netkey_update(NETKEY_NEW_INDEX, netkey);
       }
       break;
       case SCENE_KR_SERVER_RECEIVE_REFRESH_FLAG:
       {
	        net_beacon_kr_handle(network_id,1);
       }
       break;
       case SCENE_KR_SERVER_RECEIVE_FLAG:
       case SCENE_KR_SERVER_INVOKE_KEY:
       {
		   net_beacon_kr_handle(network_id,0);
       }
       break;
       case SCENE_KR_CLIENT_TEST_UPDATE_NETKEY:
       {
          mesh_kr_test_add_netkey();
       }
       break;
       case SCENE_KR_CLIENT_TEST_IN_TWONODE:
       {
          mesh_kr_client_kr_start(0);
       }
       break;
       case SCENE_KR_CLIENT_CLEAR_CACHE:
       {
           // do clear opr every time
       }
       break;
       case SCENE_KR_OUTPUT_ENV:
       {
          mesh_kr_output_env();
          mesh_kr_client_output_env();
       }
       break;
       case SCENE_KR_REMOVE_API:
       {
           uint16_t addr = 0x0003;
           mesh_kr_test_add_netkey();
           mesh_client_batch_remove_node(&addr,1);
       }
       break;
       case SCENE_KR_REMOVE_RESET:
       {
          extern  void node_save_mesh_reset(void);
		  node_save_mesh_reset();
		  platform_reset(0x0);

       }
       break;
       
  }
       

}



#endif
