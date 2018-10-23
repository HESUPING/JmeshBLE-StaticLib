#ifndef CONFIG_CLIENT_APP_H
#define CONFIG_CLIENT_APP_H
#include "../../access/jmesh_model.h"
JMESH_MODEL_NAME(config_client);
#define CONFIG_APPKEY_GET_LENGTH     2
#define CONFIG_APPKEY_ADD_LENGTH     19
#define CONFIG_APPKEY_UPDATA_LENGTH  19
#define CONFIG_APPKEY_DELETE_LENGTH   3
#define CONFIG_APPKEY_STATUA_LENGTH   4
#define CONFIG_BEACON_GET_LENGTH      0
#define CONFIG_BEACON_SET_LENGTH      1
#define CONFIG_COMPOSITION_GET_LENGTH 1
#define CONFIG_DEFAULT_TTL_GET_LENGTH         0
#define CONFIG_DEFAULT_TTL_SET_LENGTH		  1
#define CONFIG_GATT_PROXY_GET_LENGTH         0
#define CONFIG_GATT_PROXY_SET_LENGTH		  1
#define CONFIG_FRIEND_GET_LENGTH         		0
#define CONFIG_FRIEND_SET_LENGTH		  1
#define CONFIG_RELAY_GET_LENGTH         		0
#define CONFIG_RELAY_SET_LENGTH		  1
#define CONFIG_SIG_MODEL_PUBLICATION_GET_LENGTH   4
#define CONFIG_VENDOR_MODEL_PUBLICATION_GET_LENGTH   6
#define CONFIG_MODEL_PUBLICATION_SIG_SET_LENGTH         11
#define CONFIG_MODEL_PUBLICATION_VENDOR_SET_LENGTH     13
#define CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SIG_SET_LENGTH 25
#define CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_VENDOR_SET_LENGTH 27
#define CONFIG_SIG_MODEL_SUBSCRIPTION_ADD_LENGTH                   6
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_ADD_LENGTH                8
#define CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_LENGTH                 6
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_LENGTH                8
#define CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH        4
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH		6
#define CONFIG_SIG_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH            		6
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH				8
#define CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH 	20
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH 22
#define CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH 20
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH 22
#define CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH 20
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH 22
#define CONFIG_SIG_MODEL_SUBSCRIPTION_GET_LENGTH 		4
#define CONFIG_VENDOR_MODEL_SUBSCRIPTION_GET_LENGTH		6
#define CONFIG_NETKEY_ADD_LENGTH  18
#define CONFIG_NETKEY_UPDATE_LENGTH 18
#define CONFIG_NETKEY_DELETE_LENGTH 2
#define CONFIG_NETKEY_GET_LENGTH    0
#define CONFIG_NETKEY_TRANSMIT_GET_LENGTH 0
#define CONFIG_NETKEY_TRANSMIT_SET_LENGTH 1
#define CONFIG_KEY_REFRESH_PHASE_GET_LENGTH      2
#define CONFIG_KEY_REFRESH_PHASE_SET_LENGTH      3
#define CONFIG_NODE_IDENTITY_GET_LENGTH          2
#define CONFIG_NODE_IDENTITY_SET_LENGTH			3
#define CONFIG_SIG_MODEL_APP_BIND_LENGTH        6
#define CONFIG_SIG_MODEL_APP_UNBIND_LENGTH		6
#define CONFIG_SIG_MODEL_APP_GET_LENGTH         4
#define CONFIG_VENDOR_MODEL_APP_GET_LENGTH         6
#define CONFIG_VENDOR_MODEL_APP_BIND_LENGTH     8
#define CONFIG_VENDOR_MODEL_APP_UNBIND_LENGTH   8
#define CONFIG_NODE_RESET_LENGTH          0
#define	CONFIG_HEARTBEAT_PUBLICATION_GET_LENGTH  0
#define	CONFIG_HEARTBEAT_PUBLICATION_SET_LENGTH  9
#define CONFIG_HEARTBEAT_SUBSCRIPTION_GET_LENGTH 0
#define CONFIG_HEARTBEAT_SUBSCRIPTION_SET_LENGTH 5
typedef struct {

}jmesh_publication_t;

void config_appkey_list(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_appkey_status(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_appkey_get(unsigned short dst,unsigned short netkey_index);
void config_appkey_add(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char* key);
void config_appkey_update(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char* key);
void config_appkey_delete(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index);
void config_beacon_get(unsigned short dst,unsigned short netkey_index);
void config_beacon_set(unsigned short dst,unsigned short netkey_index,unsigned char state);
void config_composition_get(unsigned short dst,unsigned short netkey_index,unsigned char page);
void config_default_ttl_get(unsigned short dst,unsigned short netkey_index);
void config_default_ttl_set(unsigned short dst,unsigned short netkey_index,unsigned char ttl);
void config_gatt_proxy_get(unsigned short dst,unsigned short netkey_index);
void config_gatt_proxy_set(unsigned short dst,unsigned short netkey_index,unsigned char state);
void config_friend_get(unsigned short dst,unsigned short netkey_index);
void config_friend_set(unsigned short dst,unsigned short netkey_index,unsigned char state);
void config_relay_get(unsigned short dst,unsigned short netkey_index);
void config_relay_set(unsigned short dst,unsigned short netkey_index,unsigned char state);
void config_model_publication_get(unsigned short dst,unsigned short netkey_index,unsigned short element_addr,jmesh_model_id_t* model_id);
void config_model_publication_set(unsigned short dst,unsigned short netkey_index,unsigned short element_addr,jmesh_publication_t* p,jmesh_model_id_t* model_id);
void config_model_publication_virtual_address_set(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_publication_t* p,unsigned char* virtual_uuid,jmesh_model_id_t* model_id);
void config_model_subscription_add(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short addr,jmesh_model_id_t* model_id);
void config_model_subscription_delete(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short addr,jmesh_model_id_t* model_id);
void config_model_subscription_delete_all(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id);
void config_model_subscription_overwrite(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short addr,jmesh_model_id_t* model_id);
void config_model_subscription_virtual_address_add(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned char* virtual_addr,jmesh_model_id_t* model_id);
void config_model_subscription_virtual_address_delete(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned char* virtual_addr,jmesh_model_id_t* model_id);
void config_model_subscription_virtual_address_overwrite(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned char* virtual_addr,jmesh_model_id_t* model_id);
void config_sig_model_subscription_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id);
void config_vendor_model_subscription_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id);
void config_netkey_add(unsigned short dst,unsigned short netkey_index,unsigned char* key);
void config_netkey_update(unsigned short dst,unsigned short netkey_index,unsigned char* key);
void config_netkey_delete(unsigned short dst,unsigned short netkey_index);
void config_netkey_get(unsigned short dst,unsigned short netkey_index);
void config_network_transmit_get(unsigned short dst,unsigned short netkey_index);
void config_network_transmit_set(unsigned short dst,unsigned short netkey_index,unsigned char counts,unsigned char steps);
void config_key_refresh_phase_get(unsigned short dst,unsigned short netkey_index);
void config_key_refresh_phase_set(unsigned short dst,unsigned short netkey_index,unsigned char transition);
void config_node_identity_get(unsigned short dst,unsigned short netkey_index);
void config_node_identity_set(unsigned short dst,unsigned short netkey_index,unsigned char identity);
void config_model_app_bind(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short appkey_index,jmesh_model_id_t* model_id);
void config_model_app_unbind(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short appkey_index,jmesh_model_id_t* model_id);
void config_sig_model_app_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id);
void config_vendor_model_app_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id);
void config_node_reset(unsigned short dst,unsigned short netkey_index);
void config_heartbeat_publication_get(unsigned short dst,unsigned short netkey_index);
void config_heartbeat_publication_set(unsigned short dst,unsigned short netkey_index,unsigned short heartbeat_dest,unsigned char count_log,unsigned char period_log,unsigned char TTL,unsigned short features);
void config_heartbeat_subscription_get(unsigned short dst,unsigned short netkey_index);
void config_heartbeat_subscription_set(unsigned short dst,unsigned short netkey_index,unsigned short heartbeat_source,unsigned short heartbeat_dest,unsigned char period_log);

#endif // CONFIG_CLIENT_H
