#include"jmesh_adv.h"
#include"../../driver/jmesh_ble.h"
#include"../../driver/jmesh_system.h"
#include"../beacon/jmesh_beacon.h"
#include"../../network/jmesh_interface.h"
#include"../../network/jmesh_network.h"
#include"../../jmesh/jmesh_pdu.h"
#include"../../driver/jmesh_driver_config.h"
#include"stdio.h"
os_timer_event_t adv_timer;

OS_QUEUE_CREATE(adv_cache_queue,sizeof(jmesh_pdu_t*),JMESH_ADV_CACHE_SIZE);


#if 1
void adv_scan_timer(void)
{
    os_timer_event_restart(&adv_timer);
		switch(jmesh_ble_status())
		{
			case JMESH_BLE_STATUS_SCAN:
				if(os_queue_is_empty(adv_cache_queue))	return ;
				jmesh_ble_cancel();
				break;
			case JMESH_BLE_STATUS_ADV:
				jmesh_ble_cancel();
				break;
			case JMESH_BLE_STATUS_CONNECT:
				break;
			case JMESH_BLE_STATUS_INIT:
				break;
			default :
				JMESH_ASSERT(0);
				break;
		}
}
#else

void adv_scan_timer(void){
    jmesh_pdu_t** pdu;
    int status;
    status=jmesh_ble_status();
    os_timer_event_reset(&adv_timer);
    if(JMESH_BLE_STATUS_SCAN==status){
        pdu=os_queue_pop(adv_cache_queue);
        if(NULL!=pdu){
            jmesh_ble_send_adv(ADV_MODE_NON_CONN,(*pdu)->adv.ad_type,(*pdu)->adv.length,(*pdu)->adv.para);
            jmesh_pdu_free(*pdu);
            os_timer_event_set(&adv_timer,jmesh_random_get(JMESH_SCAN_MIN_MS,JMESH_SCAN_MAX_MS),(os_timer_event_caller_t)adv_scan_timer,NULL);
        }
    }
    else if(JMESH_BLE_STATUS_ADV==status){
        jmesh_ble_scan_adv();
        os_timer_event_set(&adv_timer,jmesh_random_get(JMESH_ADV_MIN_MS,JMESH_ADV_MAX_MS),(os_timer_event_caller_t)adv_scan_timer,NULL);
    }
}
#endif

void jmesh_adv_start(void){
    os_queue_init(adv_cache_queue);
    jmesh_ble_scan_adv();
    os_timer_event_set(&adv_timer,JMESH_SCAN_MAX_MS,(os_timer_event_caller_t)adv_scan_timer,NULL);
}
void jmesh_adv_send(jmesh_pdu_t* pdu)
{
    if(os_queue_is_full(adv_cache_queue)){
        jmesh_pdu_free(os_queue_pop(adv_cache_queue));
    }
    os_queue_push(adv_cache_queue,&pdu);
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
        jmesh_beacon_handler(mac,rssi,(jmesh_beacon_t*)data);
        break;
    case(JMESH_ADV_TYPE_MESSAGE):
        if(len<JMESH_NETWORK_PDU_MIN_LEN||len>JMESH_NETWORK_PDU_MAX_LEN){
            return;
        }
        if(NULL==(pdu=jmesh_pdu_new(len+2))){
            return;
        }
        memcpy(pdu->adv.para,data,len);
        pdu->length=len;
        jmesh_interface_recv(JMESH_INTERFACE_ADV,pdu);
        break;
    case(JMESH_ADV_TYPE_PROVISIONING):

        break;
    }
}
