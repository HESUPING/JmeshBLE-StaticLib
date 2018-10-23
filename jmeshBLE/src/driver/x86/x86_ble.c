#include"../jmesh_driver_config.h"
#if(JMESH_DRIVER_X86)

#include"../jmesh_ble.h"
#include"stdio.h"


static int ble_status=JMESH_BLE_STATUS_INIT;
int jmesh_ble_status(void)
{
    return ble_status;
}

 void jmesh_ble_reset(void){
}
 void jmesh_ble_scan_adv(void){
     ble_status=JMESH_BLE_STATUS_SCAN;
     printf("start scan adv\n");
 }

 void jmesh_ble_send_adv(unsigned char type,unsigned char ad_type, unsigned char length,unsigned char *data){
     int i;
     ble_status=JMESH_BLE_STATUS_ADV;
     printf("send a adv type=%x,len=%x,data:",ad_type,length);
     for(i=0;i<length;i++){
        printf("%x",data[i]);
     }
     printf("\n");
 }

void driver_ble_gatt_connected(void)
{

}
 int jmesh_ble_gatt_connect(unsigned char *mac){
     return 0;
}
 void jmesh_ble_gatt_disconnect(unsigned char connect_id){
}

 void jmesh_ble_disc_svc(unsigned char *uuid,unsigned char connect_id){
}

void jmesh_ble_set_local_svc_ins(unsigned short instance)
{
}

unsigned short jmesh_ble_get_local_svc_ins(void)
{
    return 0;
}
 void jmesh_ble_exchange_mtu(unsigned char connect_id){
}

 int jmesh_ble_gatt_write(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
}
 int jmesh_ble_gatt_notify(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
}
void jmesh_ble_cancel(void){
}
#endif
