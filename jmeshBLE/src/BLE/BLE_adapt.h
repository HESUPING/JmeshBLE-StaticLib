#ifndef BLE_ADAPT_H
#define BLE_ADAPT_H


int ble_reset(void);

int ble_connect(unsigned short timeflow_ms,unsigned char addr_type,unsigned char* addr);

int ble_bond(unsigned char connect_id);
int ble_gatt_send(unsigned char connect_id);
int ble_gatt_read(unsigned char connect_id);

typedef struct st_mesh_env{
    unsigned char MAC[6];
    unsigned char URI[32];
    unsigned char net_ID[6];
}mesh_env_t;
void mesh_env_init(void);
const unsigned char* ble_get_mac(void);
const unsigned char* ble_get_uri(void);
const unsigned char* ble_get_net_id(void);
void ble_set_net_id(const unsigned char* net_id);
#endif
