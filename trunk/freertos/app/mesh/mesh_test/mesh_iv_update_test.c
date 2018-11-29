
#include "osapp_config.h"

#ifdef OSAPP_MESH
#include <stdint.h>
#include "bearer.h"
#include "mesh_definitions.h"
#include "co_endian.h"
#include "beacon.h"
#include "bx_ring_queue.h"
#include "security.h"
#include "mesh_model.h"
#include "mesh_env.h"
#include "mesh_iv_operation.h"
#include "mesh_iv_operation_ex.h"
#include "mesh_iv_update_test.h"


extern uint8_t adv_report_queue_busy ;
extern ring_queue_t adv_report_q;
extern void mesh_flush_msg_cache(void);

void iv_update_beacon_pkt_test_done(void)
{
     iv_update_log_event(IV_UPDATE_SEND_PKT);
}


void iv_update_beacon_stub(void)
{
    uint8_t *buf = bearer_get_data_buffer(BEARER_ADV_SECURITY_NETWORK_BEACON);
    buf[0] = Secure_Network_Beacon;
    uint8_t network_id[NETWORK_ID_LENGTH] = {0x3e,0xca,0xff,0x67,0x2f,0x67,0x33,0x70};
    uint8_t aes_cmc[NET_BEACON_CMAC_SIZE] = {0x8e,0xa2,0x61,0x58,0x2f,0x36,0x4f,0x6f};
    net_beacon_t *beacon_data_ptr =(net_beacon_t *) (buf + BEACON_TYPE_LENGTH);

    memset(&beacon_data_ptr->payload, 0, sizeof(net_beacon_payload_t));
    beacon_data_ptr->payload.iv_index = co_htonl(0x12345678);
    beacon_data_ptr->payload.flags.key_refresh = 0;
    beacon_data_ptr->payload.flags.iv_update = 0;
    memcpy(beacon_data_ptr->payload.network_id, network_id, NETWORK_ID_LENGTH);
    memcpy(beacon_data_ptr->cmac, aes_cmc, NET_BEACON_CMAC_SIZE);

    //send beacon message
    bearer_tx(MESH_BEACON_AD_TYPE,buf, BEACON_SEC_PKT_LENGTH,iv_update_beacon_pkt_test_done);
}


void iv_update_beacon_stub_iv(void)
{
    uint8_t *buf = bearer_get_data_buffer(BEARER_ADV_SECURITY_NETWORK_BEACON);
    buf[0] = Secure_Network_Beacon;
    uint8_t network_id[NETWORK_ID_LENGTH] = {0x3e,0xca,0xff,0x67,0x2f,0x67,0x33,0x70};
    uint8_t aes_cmc[NET_BEACON_CMAC_SIZE] = {0xc2,0xaf,0x80,0xad,0x07,0x2a,0x13,0x5c};
    net_beacon_t *beacon_data_ptr =(net_beacon_t *) (buf + BEACON_TYPE_LENGTH);

    memset(&beacon_data_ptr->payload, 0, sizeof(net_beacon_payload_t));
    beacon_data_ptr->payload.iv_index = co_htonl(0x12345679);
    beacon_data_ptr->payload.flags.key_refresh = 1;
    beacon_data_ptr->payload.flags.iv_update = 1;
    memcpy(beacon_data_ptr->payload.network_id, network_id, NETWORK_ID_LENGTH);
    memcpy(beacon_data_ptr->cmac, aes_cmc, NET_BEACON_CMAC_SIZE);

    //send beacon message
    bearer_tx(MESH_BEACON_AD_TYPE,buf, BEACON_SEC_PKT_LENGTH ,iv_update_beacon_pkt_test_done);
}

uint8_t  iv_update_build_sec_beacon_test(uint8_t *buf, uint8_t iv_update)
{
    
    buf[0] = BEACON_SEC_PKT_LENGTH + 1;
    buf[1] = MESH_BEACON_AD_TYPE;
    
    buf[2] = Secure_Network_Beacon;
    uint8_t network_id[NETWORK_ID_LENGTH] = {0x3e,0xca,0xff,0x67,0x2f,0x67,0x33,0x70};
    uint8_t aes_cmc[NET_BEACON_CMAC_SIZE] = {0xc2,0xaf,0x80,0xad,0x07,0x2a,0x13,0x5c};
    net_beacon_t *beacon_data_ptr =(net_beacon_t *) (buf + BEACON_TYPE_LENGTH + DATA_OFFSET_IN_BEARER);

    memset(&beacon_data_ptr->payload, 0, sizeof(net_beacon_payload_t));
    beacon_data_ptr->payload.iv_index = co_htonl(0x12345679);
    beacon_data_ptr->payload.flags.key_refresh = 0;
    beacon_data_ptr->payload.flags.iv_update = iv_update;
    memcpy(beacon_data_ptr->payload.network_id, network_id, NETWORK_ID_LENGTH);
    memcpy(beacon_data_ptr->cmac, aes_cmc, NET_BEACON_CMAC_SIZE);
    return (BEACON_SEC_PKT_LENGTH + DATA_OFFSET_IN_BEARER);
}

extern void mesh_bearer_rx_test(void);

void iv_update_ivrefresh_pkt_in_test(uint8_t iv_update)
{
    //add to queue
    taskENTER_CRITICAL();
        bool bool_queue_full = bx_ring_queue_full(&adv_report_q);
    taskEXIT_CRITICAL();
    if(bool_queue_full)
    {
        LOG(3,"adv_report_q full!\n");
        BX_ASSERT(0);
    }
    adv_report_env_t *ptr = bx_enqueue_position(&adv_report_q);
    ptr->length = iv_update_build_sec_beacon_test(ptr->mesh_buf,iv_update);
    taskENTER_CRITICAL();
    bx_enqueue_nocopy(&adv_report_q);
    //execute
    if(adv_report_queue_busy == 0)
    {
        adv_report_queue_busy = 1;//make sure change state quickly.
        taskEXIT_CRITICAL();
        mesh_run(mesh_bearer_rx_test,portMAX_DELAY,false);
    }
    else
    {
        taskEXIT_CRITICAL();
    }

}

/*  test scene : 

    SCENE_IVUPDATE_AND_BIG_ONE = 2,
    SCENE_IVUPDATE_LESS_FT,
    SCENE_IVUPDATE_BIG_FT,
    SCENE_IVUPDATE_PROC_IN
*/


void iv_update_ivrefresh_scene(uint32_t scene)
{
    uint32_t  base_in_index = 0x12345679;
    mesh_flush_msg_cache();
    switch(scene)
    {
       case SCENE_IVUPDATE_AND_BIG_ONE:
       {
            mesh_beacon_iv_index_set(base_in_index - 1);
            
            iv_update_ivrefresh_pkt_in_test(1);
       }
       break;
       case SCENE_IVUPDATE_LESS_FT:
       {
            mesh_beacon_iv_index_set(base_in_index -10);
            iv_update_ivrefresh_pkt_in_test(1);
       }
       break;
       case SCENE_IVUPDATE_BIG_FT:
       {
            mesh_beacon_iv_index_set(base_in_index - MESH_IV_RECOVERY_LIMIT - 1);
            iv_update_ivrefresh_pkt_in_test(1);
       }
       break;
       case SCENE_IVUPDATE_PROC_IN:
       {
            mesh_beacon_iv_index_set(base_in_index);
            //iv_update_ivrefresh_pkt_in_test(1);
            iv_update_ivrefresh_pkt_in_test(0);
       }
       break;
  }
       

}



#endif
