#ifndef JMESH_BLE_H
#define JMESH_BLE_H

enum{
    JMESH_BLE_STATUS_INIT,
    JMESH_BLE_STATUS_SCAN,
    JMESH_BLE_STATUS_ADV,
    JMESH_BLE_STATUS_CONNECT,
};

#define GATT_CON_TIMEOUT_MS 10000
#define MTU_EXC_TIMEOUT_MS 5000
#define SVC_DIS_TIMEOUT_MS 8000

#define ADV_MODE_NON_CONN 0
#define ADV_MODE_CONN 1
#define ADV_MODE_CREATE_CONN 2



extern int jmesh_ble_status(void);
extern void jmesh_ble_reset(void);
extern void jmesh_ble_scan_adv(void);//stop adv
extern void jmesh_ble_send_adv(unsigned char ad_mode,unsigned char ad_type, unsigned char length,unsigned char *data);//stop scan
extern int jmesh_ble_gatt_connect(unsigned char *mac);
extern void jmesh_ble_gatt_disconnect(unsigned char connect_id);

extern void driver_ble_gatt_connected(void);

extern void jmesh_ble_disc_svc(unsigned char *uuid,unsigned char connect_id);
extern void jmesh_ble_set_local_svc_ins(unsigned short instance);
extern unsigned short jmesh_ble_get_local_svc_ins(void);
extern void jmesh_ble_exchange_mtu(unsigned char connect_id);

extern int jmesh_ble_gatt_write(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data);
extern int jmesh_ble_gatt_notify(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data);

extern void driver_gattc_cmp_evt_callback(unsigned char operation);
extern void driver_connect_adv_recv_cb(unsigned char *mac, unsigned short length, unsigned char *data);






#endif // JMESH_BLE_H
