#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include"../../access/jmesh_model.h"

#define MESSAGE_CONFIG_OPCODE_COMPOSITION_DATA_STATUS {0X02}
#define MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_STATUS {0X06}
#define MESSAGE_CONFIG_OPCODE_APPKEY_LIST   {0X80,0X02}
#define MESSAGE_CONFIG_OPCODE_APPKEY_STATUS   {0X80,0X03}
#define MESSAGE_CONFIG_OPCODE_BEACON_STATUS   {0X80,0X0B}
#define MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_STATUS   {0X80,0X0E}
#define MESSAGE_CONFIG_OPCODE_FRIEND_STATUS   {0X80,11}
#define MESSAGE_CONFIG_OPCODE_GATT_PROXY_STATUS   {0X80,0X14}
#define MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_STATUS   {0X80,0X17}
#define MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_STATUS   {0X80,0X19}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_STATUS   {0X80,0X1F}
#define MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_STATUS   {0X80,0X25}
#define MESSAGE_CONFIG_OPCODE_RELAY_STATUS   {0X80,0X28}
#define MESSAGE_CONFIG_OPCODE_SIG_MODEL_SUBSCRIPTION_LIST   {0X80,0X2A}
#define MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_SUBSCRIPTION_LIST   {0X80,0X2C}
#define MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_STATUS   {0X80,0X3C}
#define MESSAGE_CONFIG_OPCODE_MODEL_APP_STATUS   {0X80,0X3E}
#define MESSAGE_CONFIG_OPCODE_NETKEY_LIST   {0X80,0X43}
#define MESSAGE_CONFIG_OPCODE_NETKEY_STATUS   {0X80,0X44}
#define MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_STATUS   {0X80,0X48}
#define MESSAGE_CONFIG_OPCODE_NODE_RESET_STATUS   {0X80,0X4A}
#define MESSAGE_CONFIG_OPCODE_SIG_MODEL_APP_LIST   {0X80,0X4C}
#define MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_APP_LIST   {0X80,0X4E}


JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_COMPOSITION_DATA_STATUS, message_config_opcode_composition_data_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_STATUS, message_config_opcode_heartbeat_publication_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_APPKEY_LIST,message_config_opcode_appkey_list);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_APPKEY_STATUS, message_config_opcode_appkey_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_BEACON_STATUS, message_config_opcode_beacon_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_STATUS, message_config_opcode_default_ttl_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_FRIEND_STATUS,message_config_opcode_friend_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_GATT_PROXY_STATUS,message_config_opcode_gatt_proxy_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_STATUS, message_config_opcode_key_refresh_phase_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_STATUS,message_config_opcode_model_publication_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_STATUS, message_config_opcode_model_subscription_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_STATUS,message_config_opcode_network_transmit_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_RELAY_STATUS,message_config_opcode_relay_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_SIG_MODEL_SUBSCRIPTION_LIST,message_config_opcode_sig_model_subscription_list);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_SUBSCRIPTION_LIST,message_config_opcode_vendor_model_subscription_list);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_STATUS,message_config_opcode_heartbeat_subscription_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_APP_STATUS,message_config_opcode_model_app_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETKEY_LIST,message_config_opcode_netkey_list);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETKEY_STATUS, message_config_opcode_netkey_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_STATUS,message_config_opcode_node_identity_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NODE_RESET_STATUS,message_config_opcode_node_reset_status);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_SIG_MODEL_APP_LIST,message_config_opcode_sig_model_app_list);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_APP_LIST,message_config_opcode_vendor_model_app_list);


JMESH_MODEL_NAME(config_server);

#define  CONFIG_BEACON_STATUS_LENGTH  1
#define  CONFIG_DEFAULT_TTL_STATUS_LENGTH  1
#define  CONFIG_GATT_PROXY_STATUS_LENGTH   1
#define  CONFIG_RELAY_STATUS_LENGTH       2
#define  CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH 12
#define  CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH 14
#define  CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH  7
#define  CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH 9
#define  CONFIG_NETKEY_STATUS_LENGTH  3
#define  CONFIG_APPKEY_STATUS_LENGTH   4
#define  CONFIG_NODE_IDENTITY_STATUS_LENGTH 4
#define  CONFIG_SIG_MODEL_APP_STATUS_LENGTH   7
#define  CONFIG_VENDOR_MODEL_APP_STATUS_LENGTH 9
#define  CONFIG_FRIEND_STATUS_LENGTH          1
#define  CONFIG_KEY_REFRESH_PHASE_STATUS_LENGTH   4
#define  CONFIG_HEARTBEAT_PUBLICATION_STATUS_LENGTH 10
#define  CONFIG_HEARTBEAT_SUBSCRIPTION_STATUS_LENGTH 9
#define  CONFIG_CONFIG_LOWER_POWER_NODE_POLLTIME_STATUS_LENGTH 5
#define  CONFIG_NETWORK_TRANSMIT_STATUS_LENGTH 1

#define  CONFIG_COMPOSITION_DATA_STATUS_VARIABLE_LEN  50
#define  CONFIG_SIG_MODEL_SUBSCRIPTION_LIST_VARIABLE_LEN 30
#define  CONFIG_VENDOR_MODEL_SUBSCRIPTION_LIST_VARIABLE_LEN  30
#define  CONFIG_NETKEY_LIST_VARIABLE_LEN           30
#define  CONFIG_APPKEY_LIST_VARIABLE_LEN           30
#define  CONFIG_MODEL_APP_BIND_LIST_VARIABLE_LEN   30
void config_server_init(void);
void config_appkey_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_appkey_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_appkey_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_appkey_update_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_beacon_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_beacon_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_composition_data_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_default_ttl_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_default_ttl_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_gatt_proxy_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_gatt_proxy_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_friend_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_friend_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_relay_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_relay_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_publication_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_publication_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_publication_virtual_address_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_delete_all_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_overwrite_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_virtual_address_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_virtual_address_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_virtual_address_overwrite_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_sig_model_subscription_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_vendor_model_subscription_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_netkey_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_netkey_update_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_netkey_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_netkey_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_key_refresh_phase_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_key_refresh_phase_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_network_transmit_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_network_transmit_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_app_bind_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_app_unbind_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_sig_model_app_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_vendor_model_app_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_node_identity_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_node_identity_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_node_reset_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_heartbeat_publication_get_handler(unsigned short src,unsigned short dst,unsigned short aid,unsigned short nid,unsigned short len,unsigned char* data);
void config_heartbeat_publication_set_handler(unsigned short src,unsigned short dst,unsigned short aid,unsigned short nid,unsigned short len,unsigned char* data);
void config_heartbeat_subscription_get_handler(unsigned short src,unsigned short dst,unsigned short aid,unsigned short nid,unsigned short len,unsigned char* data);
void config_heartbeat_subscription_set_handler(unsigned short src,unsigned short dst,unsigned short aid,unsigned short nid,unsigned short len,unsigned char* data);
#endif // CONFIG_SERVER_H
