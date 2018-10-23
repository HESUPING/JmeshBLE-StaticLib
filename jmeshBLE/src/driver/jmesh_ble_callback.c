#include"jmesh_ble_callback.h"
#include"../bearer/adv/jmesh_adv.h"
#include"../bearer/gatt/jmesh_gatt.h"
#include"../jmesh/jmesh_print.h"

void jmesh_ble_recv_adv_callback(unsigned char *mac, unsigned char rssi,unsigned char ad_type, unsigned char length,unsigned char *data){
    jmesh_adv_recv(mac,rssi,length,ad_type,data);

}

void jmesh_ble_gatt_connected_callback(unsigned char *mac, unsigned char connect_id){
    jmesh_gatt_connected(mac,connect_id);
    //print_note("mac[%02x] connected! connect_id:%d\n",mac[5],connect_id);
}
void jmesh_ble_gatt_disconnected_callback(unsigned char connect_id){
    jmesh_gatt_disconnected(connect_id);
    //print_note("disconnected!!!! connect_id:%d\n",connect_id);
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
