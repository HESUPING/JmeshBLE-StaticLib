#include"jmesh_adv.h"
#include"../../driver/jmesh_ble.h"
#include"../../driver/jmesh_system.h"
#include"../beacon/jmesh_beacon.h"
#include"../../network/jmesh_interface.h"
#include"../../network/jmesh_network.h"
#include"../../jmesh/jmesh_pdu.h"
#include"../../driver/jmesh_driver_config.h"
#include"../../jmesh/jmesh_task.h"
#include"../../jmesh/jmesh_print.h"
#include"stdio.h"
#include"FreeRTOS.h"
#include"task.h"
static os_timer_t adv_beacon_timer,adv_message_timer;

void jmesh_adv_start(void){
	os_timer_set(&adv_beacon_timer,JMESH_ADV_RECV_INTERVAL_MS);
    os_timer_set(&adv_message_timer,JMESH_ADV_RECV_INTERVAL_MS);
    jmesh_ble_scan_adv();
}
void jmesh_adv_send(jmesh_pdu_t* pdu)
{
	vTaskDelay(2);
	jmesh_ble_send_adv(ADV_MODE_CONN,pdu->adv.ad_type,pdu->adv.length,pdu->adv.para);
	jmesh_pdu_free(pdu);
}

void jmesh_adv_send_beacon(jmesh_pdu_t* pdu)
{
    pdu->adv.ad_type=JMESH_ADV_TYPE_BEACON;
    jmesh_adv_send(pdu);
}
void jmesh_adv_send_message(jmesh_pdu_t* pdu){
    pdu->adv.ad_type=JMESH_ADV_TYPE_MESSAGE;
    jmesh_adv_send(pdu);
}
void jmesh_adv_send_provision(jmesh_pdu_t* pdu){
    pdu->adv.ad_type=JMESH_ADV_TYPE_PROVISIONING;
    jmesh_adv_send(pdu);
}

void jmesh_adv_recv(unsigned char* mac,unsigned char rssi,unsigned char len,unsigned char ad_type,unsigned char* data)
{
    jmesh_pdu_t* pdu;

    switch(ad_type){
    case(JMESH_ADV_TYPE_BEACON):	
	  if(os_timer_is_flow(&adv_beacon_timer)){
		os_timer_restart(&adv_beacon_timer);			
		jmesh_beacon_handler(mac,rssi,(jmesh_beacon_t*)data);
	  }		
        break;
    case(0xff):
    case(JMESH_ADV_TYPE_MESSAGE):
		if(len<JMESH_NETWORK_PDU_MIN_LEN||len>JMESH_NETWORK_PDU_MAX_LEN){
            return;
       }	

//        if(os_timer_is_flow(&adv_message_timer)){       
//          os_timer_restart(&adv_message_timer);
		if(network_cipher_cache(data)) return ;							
	  if(NULL==(pdu=jmesh_pdu_new(len+2))){
		  return;
	  }
//					print_buffer_info(6,mac,"receive adv data mac = ");
//					print_buffer_info(len,data,"data = ");
          memcpy(pdu->adv.para,data,len);
          pdu->length=len;
          jmesh_interface_recv(JMESH_INTERFACE_ADV,pdu);
//        }
        break;
    case(JMESH_ADV_TYPE_PROVISIONING):

        break;
    }
}
