#ifndef CONFIG_CLIENT_H
#define CONFIG_CLIENT_H

#include"../../access/jmesh_model.h"
#include"config_server.h"

enum {
    CONFIG_SERVER_MODEL_ID,
    CONFIG_CLIENT_MODEL_ID,
    HEALTH_SERVER_MODEL_ID,
    HEALTH_CLIENT_MODEL_ID
};

#define CONFIG_SERVER_MESSAGE_SIZE 46
#define CONFIG_CLIENT_MESSAGE_SIZE 23


#define MESSAGE_CONFIG_OPCODE_APPKEY_ADD {0X00}
#define MESSAGE_CONFIG_OPCODE_APPKEY_UPDATE {0X01}
#define MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_SET {0X03}
#define MESSAGE_CONFIG_OPCODE_APPKEY_DELETE   {0X80,0X00}
#define MESSAGE_CONFIG_OPCODE_APPKEY_GET   {0X80,0X01}
#define MESSAGE_CONFIG_OPCODE_COMPOSITION_DATA_GET   {0X80,0X08}
#define MESSAGE_CONFIG_OPCODE_BEACON_GET   {0X80,0X09}
#define MESSAGE_CONFIG_OPCODE_BEACON_SET   {0X80,0X0A}
#define MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_GET   {0X80,0X0C}
#define MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_SET   {0X80,0X0D}
#define MESSAGE_CONFIG_OPCODE_FRIEND_GET   {0X80,0X0F}
#define MESSAGE_CONFIG_OPCODE_FRIEND_SET   {0X80,0X10}
#define MESSAGE_CONFIG_OPCODE_GATT_PROXY_GET   {0X80,0X12}
#define MESSAGE_CONFIG_OPCODE_GATT_PROXY_SET   {0X80,0X13}
#define MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_GET   {0X80,0X15}
#define MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_SET   {0X80,0X16}
#define MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_GET   {0X80,0X18}
#define MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET   {0X80,0X1A}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_ADD   {0X80,0X1B}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_DELETE   {0X80,0X1C}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_DELETE_ALL   {0X80,0X1D}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_OVERWRITE   {0X80,0X1E}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD   {0X80,0X20}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE   {0X80,0X21}
#define MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE   {0X80,0X22}
#define MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_GET   {0X80,0X23}
#define MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_SET   {0X80,0X24}
#define MESSAGE_CONFIG_OPCODE_RELAY_GET   {0X80,0X26}
#define MESSAGE_CONFIG_OPCODE_RELAY_SET   {0X80,0X27}
#define MESSAGE_CONFIG_OPCODE_SIG_MODEL_SUBSCRIPTION_GET   {0X80,0X29}
#define MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_SUBSCRIPTION_GET   {0X80,0X2B}
#define MESSAGE_CONFIG_OPCODE_LOW_POWER_NODE_POLLTIMEOUT_GET   {0X80,0X2D}
#define MESSAGE_CONFIG_OPCODE_LOW_POWER_NODE_POLLTIMEOUT_SET   {0X80,0X2E}
#define MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_GET   {0X80,0X38}
#define MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_SET   {0X80,0X39}
#define MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_GET   {0X80,0X3A}
#define MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_SET   {0X80,0X3B}
#define MESSAGE_CONFIG_OPCODE_MODEL_APP_BIND   {0X80,0X3D}
#define MESSAGE_CONFIG_OPCODE_MODEL_APP_UNBIND   {0X80,0X3F}
#define MESSAGE_CONFIG_OPCODE_NETKEY_ADD   {0X80,0X40}
#define MESSAGE_CONFIG_OPCODE_NETKEY_DELETE   {0X80,0X41}
#define MESSAGE_CONFIG_OPCODE_NETKEY_GET   {0X80,0X42}
#define MESSAGE_CONFIG_OPCODE_NETKEY_UPDATE   {0X80,0X45}
#define MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_GET   {0X80,0X46}
#define MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_SET   {0X80,0X47}
#define MESSAGE_CONFIG_OPCODE_NODE_RESET   {0X80,0X49}
#define MESSAGE_CONFIG_OPCODE_SIG_MODEL_APP_GET   {0X80,0X4B}
#define MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_APP_GET   {0X80,0X4D}

JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_APPKEY_ADD, message_config_opcode_appkey_add);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_APPKEY_UPDATE,  message_config_opcode_appkey_update);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_SET,message_config_opcode_model_publication_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_APPKEY_DELETE,message_config_opcode_appkey_delete);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_APPKEY_GET, message_config_opcode_appkey_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_COMPOSITION_DATA_GET,message_config_opcode_composition_data_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_BEACON_GET, message_config_opcode_beacon_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_BEACON_SET, message_config_opcode_beacon_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_GET, message_config_opcode_default_ttl_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_SET, message_config_opcode_default_ttl_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_FRIEND_GET, message_config_opcode_friend_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_FRIEND_SET, message_config_opcode_friend_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_GATT_PROXY_GET, message_config_opcode_gatt_proxy_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_GATT_PROXY_SET,message_config_opcode_gatt_proxy_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_GET, message_config_opcode_key_refresh_phase_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_SET, message_config_opcode_key_refresh_phase_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_GET, message_config_opcode_model_publication_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET,message_config_opcode_model_publication_virtual_address_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_ADD, message_config_opcode_model_subscription_add);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_DELETE, message_config_opcode_model_subscription_delete);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_DELETE_ALL, message_config_opcode_model_subscription_delete_all);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_OVERWRITE, message_config_opcode_model_subscription_overwrite);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD, message_config_opcode_model_subscription_virtual_address_add);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE,message_config_opcode_model_subscription_virtual_address_delete);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE,message_config_opcode_model_subscription_virtual_address_overwrite);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_GET, message_config_opcode_network_transmit_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_SET, message_config_opcode_network_transmit_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_RELAY_GET,message_config_opcode_relay_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_RELAY_SET,message_config_opcode_relay_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_SIG_MODEL_SUBSCRIPTION_GET,message_config_opcode_sig_model_subscription_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_SUBSCRIPTION_GET,message_config_opcode_vendor_model_subscription_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_LOW_POWER_NODE_POLLTIMEOUT_GET, message_config_opcode_low_power_node_polltimeout_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_LOW_POWER_NODE_POLLTIMEOUT_SET,message_config_opcode_low_power_node_polltimeout_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_GET, message_config_opcode_heartbeat_publication_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_SET,message_config_opcode_heartbeat_publication_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_GET,message_config_opcode_heartbeat_subscription_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_SET,message_config_opcode_heartbeat_subscription_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_APP_BIND, message_config_opcode_model_app_bind);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_MODEL_APP_UNBIND,message_config_opcode_model_app_unbind);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETKEY_ADD,message_config_opcode_netkey_add);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETKEY_DELETE,message_config_opcode_netkey_delete);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETKEY_GET,message_config_opcode_netkey_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NETKEY_UPDATE, message_config_opcode_netkey_update);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_GET,message_config_opcode_node_identity_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_SET, message_config_opcode_node_identity_set);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_NODE_RESET, message_config_opcode_node_reset);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_SIG_MODEL_APP_GET,message_config_opcode_sig_model_app_get);
JMESH_MESSAGE_CREATE(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_APP_GET,message_config_opcode_vendor_model_app_get);

JMESH_MODEL_NAME(config_client);
void config_client_init(void);
void config_appkey_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_appkey_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_beacon_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_composition_data_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_default_ttl_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_gatt_proxy_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_friend_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_relay_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_publication_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_subscription_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_sig_model_subscription_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_vendor_model_subscription_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_vendor_model_subscription_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_netkey_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_netkey_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_model_app_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_sig_model_app_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_vendor_model_app_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_node_identity_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_node_reset_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_key_refresh_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_heartbeat_publication_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_heartbeat_publication_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_heartbeat_subscription_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);
void config_network_transmit_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

#endif // CONFIG_CLIENT_H
