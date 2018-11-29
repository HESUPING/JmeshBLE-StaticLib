#include"jmesh_ble_callback.h"
#include"../bearer/adv/jmesh_adv.h"
#include"../bearer/gatt/jmesh_gatt.h"
#include"../jmesh/jmesh_print.h"
#include"../onchip_system/os_timer_event.h"
#include"../jmesh/jmesh_task.h"


int jmesh_ble_connected_handler(jmesh_pdu_t* pdu)
{
  jmesh_gatt_connected(pdu->ble.connect.mac,pdu->ble.connect.id,pdu->ble.connect.is_server);
  jmesh_pdu_free(pdu);
}
int jmesh_ble_disconnected_handler(jmesh_pdu_t* pdu)
{
  jmesh_gatt_disconnected(pdu->ble.connect.id);
	jmesh_routing_connect(NULL);
	print_info("disconnected reason: %d\n",pdu->ble.connect.reason);	
  jmesh_pdu_free(pdu);
}
int jmesh_beacon_recv_handler(jmesh_pdu_t* pdu)
{
    jmesh_beacon_handler(pdu->adv.beacon.mac,pdu->adv.beacon.rssi,&pdu->adv.beacon);
    jmesh_pdu_free(pdu);
}
void jmesh_ble_recv_adv_callback(unsigned char *mac, unsigned char rssi,unsigned char ad_type, unsigned char length,unsigned char *data){
    jmesh_adv_recv(mac,rssi,length,ad_type,data);
}

void jmesh_ble_gatt_connected_callback(unsigned char *mac, unsigned char connect_id,unsigned char is_server){
    jmesh_pdu_t* pdu;
    if(NULL!=(pdu=jmesh_pdu_new(8))){
      memcpy(pdu->ble.connect.mac,mac,6);
      pdu->ble.connect.id=connect_id;
      pdu->ble.connect.is_server=is_server;
      os_event_post(&jmesh_task,JMESH_EVENT_BLE_CONNECTED,pdu);
    }
}
void jmesh_ble_gatt_disconnected_callback(unsigned char connect_id,unsigned char reason){
     jmesh_pdu_t* pdu;
    if(NULL!=(pdu=jmesh_pdu_new(8))){
      pdu->ble.connect.id=connect_id;
			pdu->ble.connect.reason = reason;
      os_event_post(&jmesh_task,JMESH_EVENT_BLE_DISCONNECTED,pdu);
    }
}

void jmesh_ble_exchange_mtu_callback(unsigned char connect_id,unsigned short mtu){
    jmesh_gatt_set_mtu(connect_id,mtu);
}
void jmesh_ble_disc_svc_callback(unsigned short connect_id,unsigned char *uuid,unsigned short handler){
    jmesh_gatt_set_svc_instance(connect_id,handler);
}
void jmesh_ble_gatt_writed_callback(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
    jmesh_gatt_recv(connect_id,char_handler,length,data);	
}
void jmesh_ble_gatt_notified_callback(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
    jmesh_gatt_recv(connect_id,char_handler,length,data);
}
