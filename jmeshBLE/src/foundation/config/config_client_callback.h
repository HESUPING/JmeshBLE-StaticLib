#ifndef CONFIG_CLIENT_CALLBACK_H
#define CONFIG_CLIENT_CALLBACK_H
#include"../../access/jmesh_model.h"

void config_appkey_list_callback(unsigned short src,unsigned short netkey_index,unsigned char len,unsigned char* appkey_index_list);
void config_appkey_status_callback(unsigned short src,unsigned short netkey_index,unsigned short appkey_index);
void config_beacon_status_callback(unsigned short src,unsigned char beacon);
void config_composition_data_status_callback(unsigned short src,unsigned char page, unsigned short len,unsigned char* composition_data);
void config_default_ttl_status_callback(unsigned short src,unsigned char ttl);
void config_gatt_proxy_status_callback(unsigned short src,unsigned char proxy);
void config_friend_status_callback(unsigned short src,unsigned char friend);
void config_relay_status_callback(unsigned short src,unsigned char relay);
void config_model_subscription_status_callback(unsigned short src,unsigned short element,unsigned short address,jmesh_model_id_t* model_id);
void config_sig_model_subscription_list_callback(unsigned short src,unsigned short element,jmesh_model_id_t* model, unsigned short len ,unsigned char* data);
void config_vendor_model_subscription_list_callback(unsigned short src,unsigned short element,jmesh_model_id_t* model, unsigned short len ,unsigned char* data);
void config_netkey_status_callback(unsigned short src,unsigned short netkey_index);
void config_netkey_list_callback(unsigned short src,unsigned short len ,unsigned char* data);
void config_model_app_bind_callback(unsigned short src,unsigned short element,unsigned short appkey_index,jmesh_model_id_t* model_id);
void config_sig_model_app_list_callback(unsigned short src,unsigned short element ,jmesh_model_id_t* model_id,unsigned short len ,unsigned char* data);
void config_vendor_model_app_list_callback(unsigned short src,unsigned short element ,jmesh_model_id_t* model_id,unsigned short len ,unsigned char* data);










#endif // CONFIG_CLIENT_CALLBACK_H
