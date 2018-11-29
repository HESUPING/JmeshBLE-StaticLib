#include"jmesh_routing_beacon.h"
#include"../../jmesh/jmesh_pdu.h"
#include"../../onchip_system/os_timer_event.h"
#include"jmesh_beacon.h"
#include"../../jmesh/jmesh_addr.h"
#include"../../upper/routing/jmesh_routing_neighbor_table.h"
#include"../../bearer/gatt/jmesh_gatt.h"
#include"../adv/jmesh_adv.h"
#if(JMESH_DRIVER_BX2400 == 1)
#include "log.h"
#endif
#include"../../jmesh/jmesh_print.h"

static os_timer_event_t routing_beacon_timer;

static os_timer_event_t routing_seq_timer;
static unsigned short routing_seq=0;
static void refresh_routing_seq(void)
{
	  routing_seq++;
	  os_timer_event_restart(&routing_seq_timer);
}
void jmesh_start_routing_seq_count(void)
{
	  os_timer_event_set(&routing_seq_timer,ROUTE_SEQ_REFRESH_INTERVAL_S*1000,(os_timer_event_caller_t)refresh_routing_seq,NULL);
}

unsigned short jmesh_get_routing_seq(void)
{
	  return ++routing_seq;
}
void jmesh_connect_request_beacon(unsigned char* mac)
{
  jmesh_routing_connect(mac);
  jmesh_routing_connect(mac);
  jmesh_routing_connect(mac);
}
void jmesh_routing_connect(unsigned char* mac)
{
      jmesh_pdu_t* pdu;
    jmesh_beacon_t* beacon;
    jmesh_netkey_t *net_key;
    jmesh_key_t cmac;
    unsigned short addr;
    unsigned short seq;

    net_key=jmesh_netkey_get_by_index(0);
    if(NULL==net_key)
    {
        return;
    }
    //else if(JMESH_STATUS_SUCCESS!=jmesh_netkey_state_get(0,net_key)){
    //    return;
    //}

				if(NULL==(pdu=jmesh_pdu_new(sizeof(jmesh_routing_beacon_t)+JMESH_BEACON_HEAD_SIZE))){
					print_note("routing beacon pdu fail!!\n");
			
        return;
    }
    beacon=(jmesh_beacon_t*)pdu->adv.para;
    if(mac==NULL){
      memset(beacon->routing_beacon.connect_request_mac,0,6);
    }
    else{
      memcpy(beacon->routing_beacon.connect_request_mac,mac,6);
    }
    beacon->type=JMESH_BEACON_TYPE_ROUTING;
    beacon->routing_beacon.is_relay=1;
    beacon->routing_beacon.connect_num=jmesh_gatt_ready_num();
    addr=jmesh_get_addr_by_element(0);
    JMESH_BIG_ENDIAN_FILL2(addr,beacon->routing_beacon.addr);
    beacon->routing_beacon.element_num=jmesh_get_element_num();
    seq=jmesh_get_routing_seq();
    JMESH_BIG_ENDIAN_FILL2(seq,beacon->routing_beacon.route_seq);
    beacon->routing_beacon.neighbor_num=jmesh_get_neighbor_num();

    security_AES_CMAC((uint8_t *)JMESH_NETKEY_GET_BEACON_KEY(net_key),7,(uint8_t *)&beacon->routing_beacon,(uint8_t *)cmac);
    memcpy(beacon->routing_beacon.authentication_value,cmac,8);
    pdu->adv.length=1+sizeof(jmesh_routing_beacon_t);

    jmesh_adv_send_beacon(pdu);
}
static void send_routing_beacon(void)
{
  jmesh_routing_connect(NULL);
  os_timer_event_reset(&routing_beacon_timer);
}
void jmesh_routing_beacon_start(int adv_time){
    os_timer_event_set(&routing_beacon_timer,(JMESH_ROUTING_BEACON_INTERVAL_S)*1000,(os_timer_event_caller_t)send_routing_beacon,NULL);
}
void jmesh_routing_beacon_stop(void){
    os_timer_event_remove(&routing_beacon_timer);
}
void jmesh_routing_beacon_handler(unsigned char *mac,unsigned char rssi,jmesh_routing_beacon_t* beacon){
    jmesh_key_t auth;
    static unsigned char cache_auth[8]={0};
    jmesh_netkey_t *net_key;
    unsigned char local_mac[6];

    net_key=jmesh_netkey_get_by_index(0);
    if(NULL==net_key)
    {
        //LOG(LOG_LVL_INFO,"\nprocess routing beacon error 3!!\n");
        //print_note("process routing beacon error3!\n");
        return;
    }
    //else if(JMESH_STATUS_SUCCESS!=jmesh_netkey_state_get(0,net_key)){
    //    return;
    //}
    if(0!=memcmp(cache_auth,beacon->authentication_value,8)){
        security_AES_CMAC((uint8_t *)JMESH_NETKEY_GET_BEACON_KEY(net_key),13,(uint8_t *)beacon,(uint8_t *)auth);
        if(0==memcmp(auth,beacon->authentication_value,8)){
            unsigned short addr;
            unsigned short route_seq;
            //LOG(LOG_LVL_INFO,"\nprocess routing beacon\n");
            memcpy(cache_auth,auth,8);
            JMESH_BIG_ENDIAN_PICK2(addr,beacon->addr);
            JMESH_BIG_ENDIAN_PICK2(route_seq,beacon->route_seq);
            jmesh_neighbor_add_mesh(mac,addr,beacon->element_num,beacon->connect_num,beacon->neighbor_num,beacon->is_relay,route_seq,rssi);
            jmesh_mac_get(local_mac);
            if(0==memcmp(beacon->connect_request_mac,local_mac,6)){
              print_buffer_info(6,mac,"recv a connect request beacon and start cnnect:");
              jmesh_ble_gatt_connect(mac);
            }
            //print_note("process routing beacon sucess!\n");
        }
        else
        {
            //LOG(LOG_LVL_INFO,"\nprocess routing beacon error 1!!\n");
            //print_note("process routing beacon error1!\n");
        }
    }
    else
    {
        //LOG(LOG_LVL_INFO,"\nprocess routing beacon error 2!!\n");
        //print_note("process routing beacon error2!\n");
    }
}
