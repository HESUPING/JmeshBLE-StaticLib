#include"config_server.h"
#include"config_client.h"
#include"../../access/jmesh_access.h"
#include"config_server_callback.h"
#include"../../jmesh/jmesh_types.h"
#include"../../jmesh/jmesh_print.h"
#include "config_client_app.h"
#include"../../jmesh/jmesh_addr.h"
JMESH_SIG_MODEL_CREATE_START(config_server,CONFIG_SERVER_MODEL_ID,CONFIG_SERVER_MESSAGE_SIZE)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_APPKEY_ADD,             config_appkey_add_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_APPKEY_DELETE,            config_appkey_delete_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_APPKEY_GET,   config_appkey_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_APPKEY_UPDATE,          config_appkey_update_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_BEACON_GET,             config_beacon_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_BEACON_SET,            config_beacon_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_COMPOSITION_DATA_GET,   config_composition_data_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_GET,          config_default_ttl_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_DEFAULT_TTL_SET,             config_default_ttl_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_GATT_PROXY_GET,            config_gatt_proxy_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_GATT_PROXY_SET,   config_gatt_proxy_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_FRIEND_GET,          config_friend_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_FRIEND_SET,             config_friend_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_RELAY_GET,            config_relay_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_RELAY_SET,   config_relay_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_GET,          config_model_publication_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_SET,             config_model_publication_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET,            config_model_publication_virtual_address_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_ADD,   config_model_subscription_add_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_DELETE,          config_model_subscription_delete_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_DELETE_ALL,             config_model_subscription_delete_all_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_OVERWRITE,            config_model_subscription_overwrite_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD,   config_model_subscription_virtual_address_add_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE,          config_model_subscription_virtual_address_delete_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE,             config_model_subscription_virtual_address_overwrite_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETKEY_ADD,            config_netkey_add_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETKEY_DELETE,   config_netkey_delete_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETKEY_GET,          config_netkey_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETKEY_UPDATE,             config_netkey_update_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_GET,            config_network_transmit_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NETWORK_TRANSMIT_SET,   config_network_transmit_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_SIG_MODEL_SUBSCRIPTION_GET,          config_sig_model_subscription_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_SUBSCRIPTION_GET,          config_vendor_model_subscription_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_APP_BIND,          config_model_app_bind_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_MODEL_APP_UNBIND,          config_model_app_unbind_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_SIG_MODEL_APP_GET,          config_sig_model_app_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_VENDOR_MODEL_APP_GET,          config_vendor_model_app_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_GET,          config_node_identity_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NODE_IDENTITY_SET,          config_node_identity_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_NODE_RESET,          config_node_reset_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_GET,          config_key_refresh_phase_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_KEY_REFRESH_PHASE_SET,          config_key_refresh_phase_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_GET,          config_heartbeat_publication_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_HEARTBEAT_PUBLICATION_SET,          config_heartbeat_publication_set_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_GET,          config_heartbeat_subscription_get_handler)
JMESH_MESSAGE_ADD(MESSAGE_CONFIG_OPCODE_HEARTBEAT_SUBSCRIPTION_SET,          config_heartbeat_subscription_set_handler)
JMESH_MODEL_CREATE_END(config_server)

void config_server_init(void)
{
		jmesh_element_add_model(&element_foundation,&config_server);
}

void config_appkey_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    uint8_t ret_buffer[CONFIG_APPKEY_STATUS_LENGTH] = {0};
		unsigned short netkey_index,appkey_index;
    if(len!=CONFIG_APPKEY_ADD_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		JMESH_KEY_INDEX_PICK2(netkey_index,appkey_index,data);
    ret_buffer[0] = config_appkey_add_server_callback(netkey_index,appkey_index,ret_buffer+4);
		ret_buffer[1] = data[0];
    ret_buffer[2] = data[1];
    ret_buffer[3] = data[2];
    jmesh_config_send(src,
                      &config_server,
                      message_config_opcode_appkey_status,
                      nid,
                      CONFIG_APPKEY_STATUS_LENGTH,ret_buffer);
}

void config_appkey_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    print_buffer_info(len,data,"appkey add src %x,dst %x,nid %d len %d:\n",src,dst,nid,len);
    uint8_t ret_buffer[CONFIG_APPKEY_STATUS_LENGTH] = {0};
    uint16_t appkey_index,netkey_index;
    if(len!=CONFIG_APPKEY_DELETE_LENGTH){
        return;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    JMESH_KEY_INDEX_PICK2(netkey_index,appkey_index,data);				
    ret_buffer[0]	=	config_appkey_delete_server_callback(netkey_index,appkey_index);
    ret_buffer[1]	=	data[0];
    ret_buffer[2]	=	data[1];
    ret_buffer[3]	=	data[2];
    jmesh_config_send(src,
                      &config_server,
                      message_config_opcode_appkey_status,
                      nid,
                      CONFIG_APPKEY_STATUS_LENGTH,ret_buffer);
}
void config_appkey_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_APPKEY_LIST_VARIABLE_LEN] = {0};
     uint16_t netkey_index;
   if(len!=CONFIG_APPKEY_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    JMESH_KEY_INDEX_PICK1(netkey_index,data);
    ret_buffer[0] = JMESH_STATUS_SUCCESS;		
    ret_buffer[1] = data[0];
    ret_buffer[2] = data[1];		
    uint8_t ret_len =config_appkey_get_server_callback(netkey_index,CONFIG_APPKEY_LIST_VARIABLE_LEN-3,ret_buffer+3);
		ret_len += 3 ;
    if(ret_len > CONFIG_APPKEY_LIST_VARIABLE_LEN) return ;
    jmesh_config_send(src,
                      &config_server,
                      message_config_opcode_appkey_list,
                      nid,
                      ret_len,
                      ret_buffer);
}
void config_appkey_update_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_APPKEY_STATUS_LENGTH] = {0};
    unsigned short appkey_index,netkey_index;
    if(len!=CONFIG_APPKEY_UPDATA_LENGTH){
        return;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    JMESH_KEY_INDEX_PICK2(netkey_index,appkey_index,data);
    ret_buffer[0] = config_appkey_update_server_callback(netkey_index,appkey_index,ret_buffer+4);
    ret_buffer[1] = data[0];
    ret_buffer[2] = data[1];
    ret_buffer[3] = data[2];
    jmesh_config_send(src,
                      &config_server,
                      message_config_opcode_appkey_status,
                      nid,
                      CONFIG_APPKEY_STATUS_LENGTH,ret_buffer);
}

void config_beacon_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data){
    uint8_t ret_buffer[CONFIG_BEACON_STATUS_LENGTH] = {0};
    if(len != CONFIG_BEACON_GET_LENGTH) return ;
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_beacon_get_server_callback();
    jmesh_config_send(src,
                      &config_server,
                      message_config_opcode_beacon_status,
                      nid,
                      CONFIG_BEACON_STATUS_LENGTH,ret_buffer);
}
void config_beacon_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_BEACON_STATUS_LENGTH] = {0};
    if(len != CONFIG_BEACON_SET_LENGTH) return;
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_beacon_set_server_callback(data[0]);
    jmesh_config_send(src,
											&config_server,
											message_config_opcode_beacon_status,
											nid,
											CONFIG_BEACON_STATUS_LENGTH,
											ret_buffer);

}

void config_composition_data_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_COMPOSITION_DATA_STATUS_VARIABLE_LEN] = {0};
    if(len!=CONFIG_COMPOSITION_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		ret_buffer[0] = data[0];
    uint8_t ret_len = config_composition_get_server_handler(data[0],CONFIG_COMPOSITION_DATA_STATUS_VARIABLE_LEN-1,ret_buffer+1);
		ret_len += 1;
		print_buffer_note(ret_len,data,"composition data:");

    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_composition_data_status,
                            nid,
                            ret_len,
                            ret_buffer);
}
void config_default_ttl_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len != CONFIG_DEFAULT_TTL_GET_LENGTH) return;
    uint8_t ret_buffer[CONFIG_DEFAULT_TTL_STATUS_LENGTH]= {0};
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_default_ttl_get_server_callback();
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_default_ttl_status,
                            nid,
                            CONFIG_DEFAULT_TTL_STATUS_LENGTH,
                            ret_buffer);
}
void config_default_ttl_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len != CONFIG_DEFAULT_TTL_SET_LENGTH) return;
    uint8_t ret_buffer[CONFIG_DEFAULT_TTL_STATUS_LENGTH]= {0};
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_default_ttl_set_server_callback(data[0]);
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_default_ttl_status,
                            nid,
                            CONFIG_DEFAULT_TTL_STATUS_LENGTH,
                            ret_buffer);
}
void config_gatt_proxy_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len != CONFIG_GATT_PROXY_GET_LENGTH) return;
    uint8_t ret_buffer[CONFIG_GATT_PROXY_STATUS_LENGTH];
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_gatt_proxy_get_server_callback();
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_gatt_proxy_status,
                            nid,
                            CONFIG_GATT_PROXY_STATUS_LENGTH,
                            ret_buffer);
}
void config_gatt_proxy_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len!=CONFIG_GATT_PROXY_SET_LENGTH) return ;
    uint8_t ret_buffer[CONFIG_GATT_PROXY_STATUS_LENGTH];
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_gatt_proxy_set_server_callback(data[0]);
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_gatt_proxy_status,
                            nid,
                            CONFIG_GATT_PROXY_STATUS_LENGTH,
                            ret_buffer);
}
void config_friend_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len!=CONFIG_FRIEND_GET_LENGTH) return;
    uint8_t ret_buffer[CONFIG_FRIEND_STATUS_LENGTH];
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_friend_get_server_callback();
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_friend_status,
                            nid,
                            CONFIG_FRIEND_STATUS_LENGTH,
                            ret_buffer);
}
void config_friend_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len!=CONFIG_FRIEND_SET_LENGTH){
        return;
    }
    uint8_t ret_buffer[CONFIG_FRIEND_STATUS_LENGTH];
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_friend_set_server_callback(data[0]);
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_friend_status,
                            nid,
                            CONFIG_FRIEND_STATUS_LENGTH,
                            ret_buffer);
}
void config_relay_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len!=CONFIG_RELAY_GET_LENGTH) return;
    uint8_t ret_buffer[CONFIG_RELAY_STATUS_LENGTH];
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_relay_get_server_callback();
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_relay_status,
                            nid,
                            CONFIG_RELAY_STATUS_LENGTH,
                            ret_buffer);
}
void config_relay_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len!=CONFIG_RELAY_SET_LENGTH) return;
    uint8_t ret_buffer[CONFIG_RELAY_STATUS_LENGTH];
		print_buffer_note(len,data,"%s: ",__func__);
    ret_buffer[0] = config_relay_get_server_callback();
    jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_relay_status,
                            nid,
                            CONFIG_RELAY_STATUS_LENGTH,
                            ret_buffer);
}
void config_model_publication_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{		
    if(len==CONFIG_SIG_MODEL_PUBLICATION_GET_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_sig_model_publication_get_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_publication_status,
                            nid,
                            CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH,
                            ret_buffer);
    }else if(len==CONFIG_SIG_MODEL_PUBLICATION_GET_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_vendor_model_publication_get_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_publication_status,
                            nid,
                            CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH,
                            ret_buffer);
    }else{
        return;
    }
}
void config_model_publication_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len == CONFIG_MODEL_PUBLICATION_SIG_SET_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_sig_model_publication_set_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_publication_status,
                            nid,
                            CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH,
                            ret_buffer);
    }else if(len == CONFIG_MODEL_PUBLICATION_VENDOR_SET_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_vendor_model_publication_set_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_publication_status,
                            nid,
                            CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH,
                            ret_buffer);
    }else
    {
        return ;
    }
}
void config_model_publication_virtual_address_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len == CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SIG_SET_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_model_publication_virtual_address_sig_set_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_publication_status,
                            nid,
                            CONFIG_SIG_MODEL_PUBLICATION_STATUS_LENGTH,
                            ret_buffer);
    }else if(len == CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_VENDOR_SET_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_model_publication_virtual_address_vendor_set_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_publication_status,
                            nid,
                            CONFIG_VENDOR_MODEL_PUBLICATION_STATUS_LENGTH,
                            ret_buffer);
    }else {
        return ;
    }
}
void config_model_subscription_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element,address;
		jmesh_model_id_t model_id;
	  jmesh_model_t* model;
	
		//TODO: judge the address type
	
    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_ADD_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);

				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(address,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+4);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);
        ret_buffer[0] = config_sig_model_subscription_add_server_callback(model,address);			
				memcpy(ret_buffer+1,data,6);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_ADD_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(address,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+4);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+6);			
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
        ret_buffer[0] = config_vendor_model_subscription_add_server_callback(model,address);
				memcpy(ret_buffer+1,data,8);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return ;
    }
}
void config_model_subscription_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element,address;
		jmesh_model_t* model;
		jmesh_model_id_t model_id;
		//TODO: judge the address type

    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(address,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+4);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);
        ret_buffer[0] = config_sig_model_subscription_delete_server_callback(model,address);
				memcpy(ret_buffer+1,data,6);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(address,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+4);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+6);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
        ret_buffer[0] = config_vendor_model_subscription_delete_server_callback(model,address);
				memcpy(ret_buffer+1,data,8);			
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return;
    }
}
void config_model_subscription_delete_all_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element;
		jmesh_model_t* model;
		jmesh_model_id_t model_id;	
    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);

				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+4);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);
        ret_buffer[0] = config_sig_model_subscription_delete_all_server_callback(model);
				ret_buffer[1]=data[0];
				ret_buffer[2]=data[1];
				ret_buffer[3]=ret_buffer[4]=0;
				memcpy(ret_buffer+5,data+2,2);			
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+4);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+6);
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
        ret_buffer[0] = config_vendor_model_subscription_delete_all_server_callback(model);
				ret_buffer[1]=data[0];
				ret_buffer[2]=data[1];
				ret_buffer[3]=ret_buffer[4]=0;
				memcpy(ret_buffer+5,data+2,4);			
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return ;
    }
}

void config_model_subscription_overwrite_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element,address;
		jmesh_model_id_t model_id;	
		jmesh_model_t* model;
    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(address,data+2);				
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+4);
				element -= jmesh_get_primary_addr();
        model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);
				ret_buffer[0] = config_sig_model_subscription_overwrite_server_callback(model,address);
				memcpy(ret_buffer+1,data,6);				
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(address,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+4);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+6);		
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
        ret_buffer[0] = config_vendor_model_subscription_overwrite_server_callback(model,address);
				memcpy(ret_buffer+1,data,8);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return ;
    }
}
void config_model_subscription_virtual_address_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element;
		unsigned char virtual_addr[16];
		jmesh_model_id_t model_id;
		jmesh_model_t* model;
    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);		
				memcpy(virtual_addr,data+2,16);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+18);	
				element -= jmesh_get_primary_addr();
	      model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);		
        ret_buffer[0] = config_sig_model_subscription_virtual_address_add_server_callback(model,virtual_addr);
				memcpy(ret_buffer+1,data,2);
			//				memcpy(address,.....); TOTO:
				memcpy(ret_buffer+5,data+18,2);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                             ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
				JMESH_LITTLE_ENDIAN_PICK2(element,data);		
				memcpy(virtual_addr,data+2,16);			
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+18);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+20);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
        ret_buffer[0] = config_vendor_model_subscription_virtual_address_add_server_callback(model,virtual_addr);
 				memcpy(ret_buffer+1,data,2);
			//				memcpy(address,.....); TOTO:
				memcpy(ret_buffer+5,data+18,4);      
				jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return;
    }
}
void config_model_subscription_virtual_address_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_sig_model_subscription_virtual_address_delete_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_vendor_model_subscription_virtual_address_delete_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return ;
    }
}

void config_model_subscription_virtual_address_overwrite_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    if(len==CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH){
        uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_sig_model_subscription_virtual_address_overwrite_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_SIG_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else if(len==CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH){
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH];
				print_buffer_note(len,data,"%s: ",__func__);
        config_vendor_model_subscription_virtual_address_overwrite_server_callback(data,ret_buffer);
        jmesh_config_send(src,
                            &config_server,
                            message_config_opcode_model_subscription_status,
                            nid,
                            CONFIG_VENDOR_MODEL_SUBSCRIPTION_STATUS_LENGTH,
                            ret_buffer);
    }
    else{
        return ;
    }
}
void config_sig_model_subscription_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_SIG_MODEL_SUBSCRIPTION_LIST_VARIABLE_LEN];
		unsigned short element,model_id;
		jmesh_model_t* model;
    if(len!=CONFIG_SIG_MODEL_SUBSCRIPTION_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);	
		JMESH_LITTLE_ENDIAN_PICK2(element,data);
		JMESH_LITTLE_ENDIAN_PICK2(model_id,data+2);			
		element -= jmesh_get_primary_addr();
		model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id);
		ret_buffer[0] = JMESH_STATUS_SUCCESS;
		memcpy(ret_buffer+1,data,4);		
    uint8_t ret_len = config_sig_model_subscription_get_server_callback(model,ret_buffer+5);
		ret_len += 5;	
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_sig_model_subscription_list,
                        nid,
                        ret_len,
                        ret_buffer);
}
void config_vendor_model_subscription_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_VENDOR_MODEL_SUBSCRIPTION_LIST_VARIABLE_LEN];
		jmesh_model_id_t model_id;
		jmesh_model_t* model;
		unsigned short element;
    if(len!=CONFIG_VENDOR_MODEL_SUBSCRIPTION_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		
		JMESH_LITTLE_ENDIAN_PICK2(element,data);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+2);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+4);	
		
		ret_buffer[0] = JMESH_STATUS_SUCCESS;
		memcpy(ret_buffer+1,data,6);
		element -= jmesh_get_primary_addr();
		model =jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
    uint8_t ret_len = config_vendor_model_subscription_get_server_callback(model,ret_buffer+7);
		ret_len += 7;
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_vendor_model_subscription_list,
                        nid,
                        ret_len,
                        ret_buffer);
}


void config_netkey_add_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_NETKEY_STATUS_LENGTH];
		unsigned short netkey_index = 0xfff;
    if(len!=CONFIG_NETKEY_ADD_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		JMESH_KEY_INDEX_PICK1(netkey_index,data);	
    ret_buffer[0] = config_netkey_add_server_callback(netkey_index,data+2);
		memcpy(ret_buffer+1,data,2);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_netkey_status,
                        nid,
                        CONFIG_NETKEY_STATUS_LENGTH,
                        ret_buffer);

}
void config_netkey_update_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_NETKEY_STATUS_LENGTH];
		unsigned short netkey_index = 0xfff;
    if(len!=CONFIG_NETKEY_UPDATE_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		JMESH_KEY_INDEX_PICK1(netkey_index,data);	
    ret_buffer[0] = config_netkey_update_server_callback(netkey_index,data+2);
		memcpy(ret_buffer+1,data,2);		
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_netkey_status,
                        nid,
                        CONFIG_NETKEY_STATUS_LENGTH,
                        ret_buffer);

}

void config_netkey_delete_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short netkey_index;
    uint8_t ret_buffer[CONFIG_NETKEY_STATUS_LENGTH];	
    if(len!=CONFIG_NETKEY_DELETE_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		JMESH_KEY_INDEX_PICK1(netkey_index,data);	
		
    ret_buffer[0] = config_netkey_delete_server_callback(netkey_index);
		memcpy(ret_buffer+1,data,2);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_netkey_status,
                        nid,
                        CONFIG_NETKEY_STATUS_LENGTH,
                        ret_buffer);
}
void config_netkey_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_NETKEY_LIST_VARIABLE_LEN];
    if(len!=CONFIG_NETKEY_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    uint8_t ret_len = config_netkey_get_server_callback(CONFIG_NETKEY_LIST_VARIABLE_LEN,ret_buffer);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_netkey_list,
                        nid,
                        ret_len,
                        ret_buffer);

}
void config_key_refresh_phase_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_KEY_REFRESH_PHASE_STATUS_LENGTH];
    if(len!=CONFIG_KEY_REFRESH_PHASE_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    config_key_refresh_phase_get_server_callback(data,ret_buffer);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_key_refresh_phase_status,
                        nid,
                        CONFIG_KEY_REFRESH_PHASE_STATUS_LENGTH,
                        ret_buffer);
}
void config_key_refresh_phase_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_KEY_REFRESH_PHASE_STATUS_LENGTH];
    if(len!=CONFIG_KEY_REFRESH_PHASE_SET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    config_key_refresh_phase_set_server_callback(data,ret_buffer);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_key_refresh_phase_status,
                        nid,
                        CONFIG_KEY_REFRESH_PHASE_STATUS_LENGTH,
                        ret_buffer);
}

void config_network_transmit_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
     uint8_t ret_buffer[CONFIG_NETWORK_TRANSMIT_STATUS_LENGTH];
    if(len!=CONFIG_NETKEY_TRANSMIT_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    config_network_transmit_get_server_callback(data,ret_buffer);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_network_transmit_status,
                        nid,
                        CONFIG_NETWORK_TRANSMIT_STATUS_LENGTH,
                        ret_buffer);

}
void config_network_transmit_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
     uint8_t ret_buffer[CONFIG_NETWORK_TRANSMIT_STATUS_LENGTH];
    if(len!=CONFIG_NETKEY_TRANSMIT_SET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    config_network_transmit_set_server_callback(data,ret_buffer);
    jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_network_transmit_status,
                        nid,
                        CONFIG_NETWORK_TRANSMIT_STATUS_LENGTH,
                        ret_buffer);
}
void config_model_app_bind_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element,appkey_index;	
		jmesh_model_t* model;
		jmesh_appkey_t* appkey;
		jmesh_model_id_t model_id;
		print_buffer_note(len,data,"%s: ",__func__);
    if(len == CONFIG_SIG_MODEL_APP_BIND_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_SIG_MODEL_APP_STATUS_LENGTH];

				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(appkey_index,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+4);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);
				appkey = jmesh_appkey_get_by_key_index(nid, appkey_index);
        ret_buffer[0] = config_sig_model_app_bind_server_callback(model,appkey);
			  memcpy(ret_buffer+1,data,6);
        jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_model_app_status,
                        nid,
                        CONFIG_SIG_MODEL_APP_STATUS_LENGTH,
                        ret_buffer);
    }else if(len == CONFIG_VENDOR_MODEL_APP_BIND_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_APP_STATUS_LENGTH];
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(appkey_index,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+4);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+6);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
				appkey = jmesh_appkey_get_by_key_index(nid, appkey_index);
  			ret_buffer[0] = config_vendor_model_app_bind_server_callback(model,appkey);
				memcpy(ret_buffer+1,data,8);		
        jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_model_app_status,
                        nid,
                        CONFIG_VENDOR_MODEL_APP_STATUS_LENGTH,
                        ret_buffer);
    }else {
				print_error("invalid app bind length!\n");
        return ;
    }
}
void config_model_app_unbind_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		unsigned short element,appkey_index;	
		jmesh_model_t* model;
		jmesh_appkey_t* appkey;
		jmesh_model_id_t model_id;
		print_buffer_note(len,data,"%s: ",__func__);
    if(len == CONFIG_SIG_MODEL_APP_UNBIND_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_SIG_MODEL_APP_STATUS_LENGTH];
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(appkey_index,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.sig_id,data+4);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id.sig_id);
				appkey = jmesh_appkey_get_by_key_index(nid, appkey_index);
        ret_buffer[0] = config_sig_model_app_unbind_server_callback(model,appkey);
			  memcpy(ret_buffer+1,data,6);
        jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_model_app_status,
                        nid,
                        CONFIG_SIG_MODEL_APP_STATUS_LENGTH,
                        ret_buffer);
    }else if(len == CONFIG_VENDOR_MODEL_APP_UNBIND_LENGTH)
    {
        uint8_t ret_buffer[CONFIG_VENDOR_MODEL_APP_STATUS_LENGTH];
				JMESH_LITTLE_ENDIAN_PICK2(element,data);
				JMESH_LITTLE_ENDIAN_PICK2(appkey_index,data+2);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+4);
				JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+6);	
				element -= jmesh_get_primary_addr();
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
				appkey = jmesh_appkey_get_by_key_index(nid, appkey_index);
  			ret_buffer[0] = config_vendor_model_app_unbind_server_callback(model,appkey);
				memcpy(ret_buffer+1,data,8);		
        jmesh_config_send(src,
                        &config_server,
                        message_config_opcode_model_app_status,
                        nid,
                        CONFIG_VENDOR_MODEL_APP_STATUS_LENGTH,
                        ret_buffer);
    }else {
        return ;
    }
}
void config_sig_model_app_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_MODEL_APP_BIND_LIST_VARIABLE_LEN];
		unsigned short element,model_id;
		jmesh_model_t*  model;
    if(len!=CONFIG_SIG_MODEL_APP_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);		
		JMESH_LITTLE_ENDIAN_PICK2(element,data);
		JMESH_LITTLE_ENDIAN_PICK2(model_id,data+2);
		ret_buffer[0] = JMESH_STATUS_SUCCESS;
		memcpy(ret_buffer+1,data,4);	
		element -= jmesh_get_primary_addr();
		model = jmesh_model_get_by_sig_id(jmesh_element_get_by_index(element),model_id);
    uint8_t ret_len = config_sig_model_app_get_server_callback(model,CONFIG_MODEL_APP_BIND_LIST_VARIABLE_LEN,ret_buffer+5);
		ret_len += 5;
    jmesh_config_send(src,
                    &config_server,
                    message_config_opcode_sig_model_app_list,
                    nid,
                    ret_len,
                    ret_buffer);

}
void config_vendor_model_app_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_MODEL_APP_BIND_LIST_VARIABLE_LEN];
		unsigned short element;
		jmesh_model_id_t model_id;
		jmesh_model_t*  model;
  	if(len!=CONFIG_VENDOR_MODEL_APP_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
		JMESH_LITTLE_ENDIAN_PICK2(element,data);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.company_id,data+2);
		JMESH_LITTLE_ENDIAN_PICK2(model_id.model_id,data+4);	
		ret_buffer[0] = JMESH_STATUS_SUCCESS;
		memcpy(ret_buffer+1,data,6);	
		element -= jmesh_get_primary_addr();
		model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id);
    uint8_t ret_len = config_vendor_model_app_get_server_callback(model,CONFIG_MODEL_APP_BIND_LIST_VARIABLE_LEN,ret_buffer+7);
		ret_len += 7;
    jmesh_config_send(src,
                    &config_server,
                    message_config_opcode_vendor_model_app_list,
                    nid,
                    ret_len,
                    ret_buffer);
}
void config_node_identity_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_NODE_IDENTITY_STATUS_LENGTH];
    if(len!=CONFIG_NODE_IDENTITY_GET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    config_node_identity_get_server_callback(data,ret_buffer);
    jmesh_config_send(src,
                    &config_server,
                    message_config_opcode_node_identity_status,
                    nid,
                    CONFIG_NODE_IDENTITY_STATUS_LENGTH,
                    ret_buffer);
}
void config_node_identity_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
    uint8_t ret_buffer[CONFIG_NODE_IDENTITY_STATUS_LENGTH];
    if(len!=CONFIG_NODE_IDENTITY_SET_LENGTH){
        return ;
    }
		print_buffer_note(len,data,"%s: ",__func__);
    config_node_identity_set_server_callback(data,ret_buffer);
    jmesh_config_send(src,
                    &config_server,
                    message_config_opcode_node_identity_status,
                    nid,
                    CONFIG_NODE_IDENTITY_STATUS_LENGTH,
                    ret_buffer);
}
void config_node_reset_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{
		print_buffer_note(len,data,"%s: ",__func__);
    uint8_t ret_buffer[CONFIG_NODE_RESET_LENGTH];
    if(len!=CONFIG_NODE_RESET_LENGTH){
        return ;
    }
}

void config_heartbeat_publication_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void config_heartbeat_publication_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void config_heartbeat_subscription_get_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
void config_heartbeat_subscription_set_handler(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data)
{

}
