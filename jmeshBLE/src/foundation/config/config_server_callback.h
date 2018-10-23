#ifndef CONFIG_SERVER_CALLBACK_H
#define CONFIG_SERVER_CALLBACK_H
#include"../../access/jmesh_model.h"
#include "stdint.h"

int config_appkey_add_server_callback(unsigned short netkey_index,unsigned short appkey_index,uint8_t* ret_buffer);
int config_appkey_delete_server_callback(unsigned short netkey_index,unsigned short appkey_index);
int config_appkey_get_server_callback(unsigned short netkey_index,unsigned char length,unsigned char* ret_buffer);
int config_appkey_update_server_callback(unsigned short netkey_index,unsigned short appkey_index,uint8_t* ret_buffer);
int config_beacon_get_server_callback(void);
int config_beacon_set_server_callback(unsigned char beacon);
int config_composition_get_server_handler(unsigned char page,unsigned char buffer_size,unsigned char* ret_buffer);
int config_default_ttl_get_server_callback(void);
int config_default_ttl_set_server_callback(unsigned char ttl);
int config_gatt_proxy_get_server_callback(void);
int config_gatt_proxy_set_server_callback(unsigned char proxy);
int config_friend_get_server_callback(void);
int config_friend_set_server_callback(unsigned char friend);
int config_relay_get_server_callback(void);
int config_relay_set_server_callback(unsigned char reley);
int config_sig_model_publication_get_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_vendor_model_publication_get_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_sig_model_publication_set_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_vendor_model_publication_set_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_model_publication_virtual_address_sig_set_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_model_publication_virtual_address_vendor_set_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_sig_model_subscription_add_server_callback(jmesh_model_t* sig_model,unsigned short address);
int config_vendor_model_subscription_add_server_callback(jmesh_model_t* sig_model,unsigned short address);
int config_sig_model_subscription_delete_server_callback(jmesh_model_t* model,unsigned short address);
int config_vendor_model_subscription_delete_server_callback(jmesh_model_t* model,unsigned short address);
int config_sig_model_subscription_delete_all_server_callback(jmesh_model_t* model);
int config_vendor_model_subscription_delete_all_server_callback(jmesh_model_t* model);
int config_sig_model_subscription_overwrite_server_callback(jmesh_model_t* model,unsigned short address);
int config_vendor_model_subscription_overwrite_server_callback(jmesh_model_t* model,unsigned short address);
int config_sig_model_subscription_virtual_address_add_server_callback(jmesh_model_t* model,unsigned char* virtual_addr);
int config_vendor_model_subscription_virtual_address_add_server_callback(jmesh_model_t* model,unsigned char* virtual_addr);
int config_sig_model_subscription_virtual_address_delete_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_vendor_model_subscription_virtual_address_delete_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_sig_model_subscription_virtual_address_overwrite_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_vendor_model_subscription_virtual_address_overwrite_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_sig_model_subscription_get_server_callback(jmesh_model_t* model,uint8_t* ret_buffer);
int config_vendor_model_subscription_get_server_callback(jmesh_model_t* model,uint8_t* ret_buffer);
int config_netkey_add_server_callback(unsigned short netkey_index,uint8_t* key);
int config_netkey_update_server_callback(unsigned short netkey_index,uint8_t* key);
int config_netkey_delete_server_callback(unsigned short netkey_index);
int config_netkey_get_server_callback(unsigned char buffer_size,unsigned char* ret_buffer);
int config_key_refresh_phase_get_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_key_refresh_phase_set_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_network_transmit_get_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_network_transmit_set_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_sig_model_app_bind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey);
int config_vendor_model_app_bind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey);
int config_sig_model_app_unbind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey);
int config_vendor_model_app_unbind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey);
int config_sig_model_app_get_server_callback(jmesh_model_t* model,unsigned char buffer_size,unsigned char* ret_buffer);
int config_vendor_model_app_get_server_callback(jmesh_model_t* model,unsigned char buffer_size,unsigned char* ret_buffer);
int config_node_identity_get_server_callback(uint8_t* data,uint8_t* ret_buffer);
int config_node_identity_set_server_callback(uint8_t* data,uint8_t* ret_buffer);


#endif // CONFIG_SERVER_CALLBACK_H
