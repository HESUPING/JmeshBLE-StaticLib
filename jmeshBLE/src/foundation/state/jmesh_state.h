#ifndef  	JMESH_STATE_H
#define   JMESH_STATE_H
#include"../../jmesh/jmesh_types.h"
#include"../../jmesh/jmesh_save.h"
#include"../../access/jmesh_model.h"
#include"../../access/jmesh_element.h"
#include"../../access/jmesh_access.h"
#define JMESH_SEQ_WARNING_FLOW 0x00efffff
#define JMESH_PRODUCT_ID  1
#define JMESH_VERSION_ID  1
#define REPLAY_PROTECTION_LIST_SIZE 100
#define JMESH_ELEMENT_LOC           0xffff
typedef union{
		unsigned char flags;
		struct{
				unsigned char relay                 :1;
				unsigned char secure_network_beacon :1;
				unsigned char gatt_proxy            :1;
				unsigned char friend_state          :1;
				unsigned char iv_update_flag        :1;
		};
}jmesh_flags_t;
enum{
		TAG_BD_ADDRESS = 0x01,
		TAG_APP_SPECIFIC_FIRST = 0x90,
};
void jmesh_mac_init(void);
void jmesh_mac_get(jmesh_mac_t mac);
void jmesh_mac_set(jmesh_mac_t mac);
void jmesh_seq_init(void);
void jmesh_state_add_seq(void);
unsigned long jmesh_state_get_seq(void);
void jmesh_state_clear_seq(void);
void jmesh_state_set_seq(unsigned long seq);
void jmesh_default_ttl_init(void);
void jmesh_default_ttl_set(unsigned char default_ttl);
unsigned char jmesht_default_ttl_get(void);
void jmesh_state_init_flags(void);
void jmesh_state_set_relay(unsigned char relay_state);
unsigned char jmesh_state_get_relay(void);
int jmesh_state_set_secure_network_beacon(unsigned char secure_network_beacon_state);
unsigned char jmesh_state_get_secure_network_beacon(void);
void jmesh_state_set_gatt_proxy(unsigned char gatt_proxy_state);
unsigned char jmesh_state_get_gatt_proxy(void);
void jmesh_state_set_friend(unsigned char state);
unsigned char jmesh_state_get_friend(void);
int jmesh_composition_page_data_get(unsigned char* data);

#endif

