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

void jmesh_state_init_flags(void);
int jmesh_state_set_secure_network_beacon(unsigned char secure_network_beacon_state);
unsigned char jmesh_state_get_secure_network_beacon(void);
int jmesh_composition_page_data_get(unsigned char* data);

#endif

