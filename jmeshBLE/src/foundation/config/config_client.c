#include"config_server.h"
#include"config_client.h"
#include"config_client_callback.h"
#include"../../jmesh/jmesh_types.h"
#include"../../access/jmesh_access.h"
#include "../../jmesh/jmesh_print.h"
JMESH_SIG_MODEL_CREATE_START(config_client,CONFIG_CLIENT_MODEL_ID,CONFIG_CLIENT_MESSAGE_SIZE)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_APPKEY_LIST,             config_appkey_list_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_APPKEY_STATUS,            config_appkey_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_BEACON_STATUS,   config_beacon_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_COMPOSITION_DATA_STATUS,          config_composition_data_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_STATUS,             config_default_ttl_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_GATT_PROXY_STATUS,             config_gatt_proxy_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_FRIEND_STATUS,            config_friend_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_RELAY_STATUS,   config_relay_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_STATUS,          config_model_publication_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_STATUS,             config_model_subscription_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_SIG_MODEL_SUBSCRIPTION_LIST,          config_sig_model_subscription_list_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_SUBSCRIPTION_LIST,             config_vendor_model_subscription_list_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETKEY_STATUS,             config_netkey_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETKEY_LIST,            config_netkey_list_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_APP_STATUS,   config_model_app_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_SIG_MODEL_APP_LIST,          config_sig_model_app_list_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_APP_LIST,             config_vendor_model_app_list_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_STATUS,          config_node_identity_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NODE_RESET_STATUS,             config_node_reset_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_STATUS,          config_key_refresh_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_STATUS,             config_heartbeat_publication_status_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_STATUS,          config_heartbeat_subscription_status_handler )
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_STATUS,             config_network_transmit_status_handler)

JMESH_MODEL_CREATE_END(config_client)

void config_client_init(void)
{
		jmesh_element_add_model(&element_foundation,&config_client);
}


void config_appkey_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short netkey_index;
		unsigned char status = data[0];
		if(status == JMESH_STATUS_SUCCESS){
				JMESH_KEY_INDEX_PICK1(netkey_index,data+1);
				config_appkey_list_callback(src,netkey_index,len-3,data+3);			
		}else {
				print_error("invalid status: %d\n",status);
		}
}
void config_appkey_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		if(len != CONFIG_APPKEY_STATUS_LENGTH) return;
		unsigned short netkey_index,appkey_index;
		unsigned char status = data[0];
		if(status == JMESH_STATUS_SUCCESS){
				JMESH_KEY_INDEX_PICK2(netkey_index,appkey_index,data+1);
				config_appkey_status_callback(src,netkey_index,appkey_index);
		}else{
				print_error("invalid status: %d\n",status);		
		}
}
void config_beacon_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		if(len != CONFIG_BEACON_STATUS_LENGTH) return ;
		unsigned char beacon = data[0];
		config_beacon_status_callback(src,beacon);
}
void config_composition_data_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned char page = data[0];
		config_composition_data_status_callback(src,page,len,data+1);
}
void config_default_ttl_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		if(len != CONFIG_DEFAULT_TTL_STATUS_LENGTH) return ;
		unsigned char ttl = data[0];
		config_default_ttl_status_callback(src,ttl);
}
void config_gatt_proxy_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		if(len != CONFIG_GATT_PROXY_STATUS_LENGTH) return ;
		unsigned char proxy = data[0];
		config_gatt_proxy_status_callback(src,proxy);
	
}
void config_friend_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		if(len != CONFIG_FRIEND_STATUS_LENGTH) return ;
		unsigned char friend = data[0];
		config_friend_status_callback(src,friend);
	
}
void config_relay_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		if(len != CONFIG_RELAY_STATUS_LENGTH) return ;
		unsigned char relay = data[0];
		config_relay_status_callback(src,relay);
}
void config_model_publication_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}
void config_model_subscription_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{	
		print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned char status = data[0];
		unsigned short element,address;
		jmesh_model_id_t model_id;
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(element,data+1);
		JMESH_LITTLE_ENDIAN_PICK2(address,data+3);
		if(len == CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH){
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+5);
				model_id.model_id = JMESH_MODEL_ID_INVALID;
		}else if(len == CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH){
			  JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+5);
			  JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+7);				
		}else{
				return ;
		}
		config_model_subscription_status_callback(src,element,address,&model_id);
}
void config_sig_model_subscription_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short element;
		jmesh_model_id_t model_id;
		unsigned char status = data [0];
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(element,data+1);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+3);
		model_id.model_id = JMESH_MODEL_ID_INVALID;
		config_sig_model_subscription_list_callback(src,element,&model_id,len-5,data+5);
}
void config_vendor_model_subscription_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short element;
		jmesh_model_id_t model_id;
		unsigned char status = data [0];
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(element,data+1);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+3);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+5);
		config_vendor_model_subscription_list_callback(src,element,&model_id,len-7,data+7);
	
		
}
void config_netkey_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short netkey_index ;
		unsigned char status = data[0];
		if(len != CONFIG_NETKEY_STATUS_LENGTH) return;
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(netkey_index,data+1);
		config_netkey_status_callback(src,netkey_index);
	
}
void config_netkey_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		config_netkey_list_callback(src,len,data);
}
void config_model_app_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short element,appkey_index ;
		jmesh_model_id_t model_id;
		unsigned char status = data[0];
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(element,data+1);	
		JMESH_LITTLE_ENDIAN_PICK2(appkey_index,data+3);	
		if(len == CONFIG_SIG_MODEL_APP_STATUS_LENGTH){
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+5);	
				model_id.model_id = JMESH_MODEL_ID_INVALID;
		}else if(len == CONFIG_VENDOR_MODEL_APP_STATUS_LENGTH){
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+5);	
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+7);			
		}else{
				return ;
		}
		config_model_app_bind_callback(src,element,appkey_index,&model_id);
}
void config_sig_model_app_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short element ;
		jmesh_model_id_t model_id;
		unsigned char status = data[0];
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(element,data+1);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+3);
		model_id.model_id = JMESH_MODEL_ID_INVALID;
		config_sig_model_app_list_callback(src,element,&model_id,len-5,data+5);
}
void config_vendor_model_app_list_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
		unsigned short element ;
		jmesh_model_id_t model_id;
		unsigned char status = data[0];
		if(status != JMESH_STATUS_SUCCESS) print_error("invalid status: %d\n",status);
		JMESH_LITTLE_ENDIAN_PICK2(element,data+1);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+3);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+5);
		config_sig_model_app_list_callback(src,element,&model_id,len-7,data+7);
}
void config_node_identity_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}
void config_node_reset_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}
void config_key_refresh_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}
void config_heartbeat_publication_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}
void config_heartbeat_subscription_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}
void config_network_transmit_status_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"%s : data = ",__func__);
}

