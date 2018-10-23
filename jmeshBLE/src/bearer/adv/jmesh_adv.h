#ifndef JMESH_ADV_H
#define JMESH_ADV_H
#include"../../jmesh/jmesh_pdu.h"
#include"../../jmesh/jmesh_config.h"
#include"../../onchip_system/os_timer_event.h"
#include"../../onchip_system/os_queue.h"

#define JMESH_ADV_TYPE_BEACON 0x2A
#define JMESH_ADV_TYPE_MESSAGE 0x2B
#define JMESH_ADV_TYPE_PROVISIONING 0x2C
void jmesh_ble_cancel(void);
extern os_timer_event_t adv_timer;
extern int ble_status;
OS_QUEUE_NAME(adv_cache_queue);
void adv_scan_timer(void);
void jmesh_adv_start(void);
void jmesh_adv_recv(unsigned char* mac,unsigned char rssi,unsigned char len,unsigned char ad_type,unsigned char* data);
void jmesh_adv_send(jmesh_pdu_t* pdu);
void jmesh_adv_scan_timer(void);
void jmesh_adv_send_beacon(jmesh_pdu_t* pdu);
void jmesh_adv_send_message(jmesh_pdu_t* pdu);
void jmesh_adv_send_provision(jmesh_pdu_t* pdu);


#endif // JMESH_ADV_H
