#include "config_client_app.h"
#include"config_client.h"
#include "../../access/jmesh_access.h"
#include"../../jmesh/jmesh_types.h"
#include "config_server.h"
#include"stdint.h"
void config_appkey_get(unsigned short dst,unsigned short netkey_index)
{
    unsigned char data[CONFIG_APPKEY_GET_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    jmesh_config_send(dst,&config_client,message_config_opcode_appkey_get,netkey_index,CONFIG_APPKEY_GET_LENGTH,data);
}
void config_appkey_add(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char* key)
{
    unsigned char data[CONFIG_APPKEY_ADD_LENGTH];
    JMESH_KEY_INDEX_PACK2(netkey_index,appkey_index,data);
    memcpy(data+3,key,JMESH_KEY_SIZE);
    jmesh_config_send(dst,&config_client,message_config_opcode_appkey_add,netkey_index,CONFIG_APPKEY_ADD_LENGTH,data);
}
void config_appkey_update(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,unsigned char* key)
{
    unsigned char data[CONFIG_APPKEY_ADD_LENGTH];
    JMESH_KEY_INDEX_PACK2(netkey_index,appkey_index,data);
    memcpy(data+3,key,JMESH_KEY_SIZE);
    jmesh_config_send(dst,&config_client,message_config_opcode_appkey_update,netkey_index,CONFIG_APPKEY_UPDATA_LENGTH,data);
}
void config_appkey_delete(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index)
{
    unsigned char data[CONFIG_APPKEY_DELETE_LENGTH];
    JMESH_KEY_INDEX_PACK2(netkey_index,appkey_index,data);
    jmesh_config_send(dst,&config_client,message_config_opcode_appkey_delete,netkey_index,CONFIG_APPKEY_DELETE_LENGTH,data);
}
void config_beacon_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_beacon_get,netkey_index,CONFIG_BEACON_GET_LENGTH,NULL);

}
void config_beacon_set(unsigned short dst,unsigned short netkey_index,unsigned char state)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_beacon_set,netkey_index,CONFIG_BEACON_SET_LENGTH,&state);
}
void config_composition_get(unsigned short dst,unsigned short netkey_index,unsigned char page)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_composition_data_get,netkey_index,CONFIG_COMPOSITION_GET_LENGTH,&page);
}

void config_default_ttl_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_default_ttl_get,netkey_index,CONFIG_DEFAULT_TTL_GET_LENGTH,NULL);
}

void config_default_ttl_set(unsigned short dst,unsigned short netkey_index,unsigned char ttl)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_default_ttl_set,netkey_index,CONFIG_DEFAULT_TTL_SET_LENGTH,&ttl);
}

void config_gatt_proxy_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_gatt_proxy_get,netkey_index,CONFIG_GATT_PROXY_GET_LENGTH,NULL);
}
void config_gatt_proxy_set(unsigned short dst,unsigned short netkey_index,unsigned char state)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_gatt_proxy_set,netkey_index,CONFIG_GATT_PROXY_SET_LENGTH,&state);

}

void config_friend_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_friend_get,netkey_index,CONFIG_FRIEND_GET_LENGTH,NULL);

}
void config_friend_set(unsigned short dst,unsigned short netkey_index,unsigned char state)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_friend_set,netkey_index,CONFIG_FRIEND_SET_LENGTH,&state);

}

void config_relay_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_relay_get,netkey_index,CONFIG_RELAY_GET_LENGTH,NULL);

}
void config_relay_set(unsigned short dst,unsigned short netkey_index,unsigned char state)
{
    jmesh_config_send(dst,&config_client,message_config_opcode_relay_set,netkey_index,CONFIG_RELAY_SET_LENGTH,&state);

}


void config_model_publication_get(unsigned short dst,unsigned short netkey_index,unsigned short element_addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID)
	{
	    unsigned char data[CONFIG_SIG_MODEL_PUBLICATION_GET_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+2);
	    jmesh_config_send(dst,&config_client,
                       message_config_opcode_model_publication_get,netkey_index,
                       CONFIG_SIG_MODEL_PUBLICATION_GET_LENGTH,data);

	}
	else	{
	    unsigned char data[CONFIG_VENDOR_MODEL_PUBLICATION_GET_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+4);

		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_publication_get,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_PUBLICATION_GET_LENGTH,data);
	}

}

void config_model_publication_set(unsigned short dst,unsigned short netkey_index,unsigned short element_addr,jmesh_publication_t* p,jmesh_model_id_t* model_id)
{
    if(model_id->model_id == JMESH_MODEL_ID_INVALID){
        unsigned char data[CONFIG_MODEL_PUBLICATION_SIG_SET_LENGTH];
        JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
        memcpy(data+2,p,sizeof(jmesh_publication_t));
        JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+9);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_publication_set,
                    netkey_index,
                    CONFIG_MODEL_PUBLICATION_SIG_SET_LENGTH,data);
    }
    else{
        unsigned char data[CONFIG_MODEL_PUBLICATION_VENDOR_SET_LENGTH];
        JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
        memcpy(data+2,p,sizeof(jmesh_publication_t));
        JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+9);
        JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+11);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_publication_set,
                    netkey_index,
                    CONFIG_MODEL_PUBLICATION_VENDOR_SET_LENGTH,data);
   }
}

void config_model_publication_virtual_address_set(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_publication_t* p,unsigned char* virtual_uuid,jmesh_model_id_t* model_id)
{
 /*   uint8_t opcode_buf[4] = {0};
    JMESH_BIG_ENDIAN_FILL4(MESSAGE_CONFIG_OPCODE_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET,opcode_buf);
    if(model_id->model_id == JMESH_MODEL_ID_INVALID){
        unsigned char data[CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SIG_SET_LENGTH];
        JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
        memcpy(data+16,p,sizeof(jmesh_publication_t));
        memcpy(data+2,virtual_uuid,JMESH_UUID_SIZE);
        JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+23);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_publication_virtual_address_set,
                    netkey_index,
                    CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SIG_SET_LENGTH,data);
    }
    else{
        unsigned char data[CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_VENDOR_SET_LENGTH];
        JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
        memcpy(data+16,p,sizeof(jmesh_publication_t));
        memcpy(data+2,virtual_uuid,JMESH_UUID_SIZE);
        JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+23);
        JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+25);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_publication_virtual_address_set,
                    netkey_index,
                    CONFIG_MODEL_PUBLICATION_VIRTUAL_ADDRESS_VENDOR_SET_LENGTH,data);
    }
*/
}

void config_model_subscription_add(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID)
	{
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_ADD_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(addr,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+4);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_add,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_ADD_LENGTH,data);
	}else {
		unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_ADD_LENGTH];
		JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
		JMESH_LITTLE_ENDIAN_FILL2(addr,data+2);
		JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+4);
		JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+6);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_add,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_ADD_LENGTH,data);
	}
}
void config_model_subscription_delete(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID)
	{
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(addr,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+4);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_delete,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_LENGTH,data);
	}else{
	    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(addr,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+4);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+6);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_delete,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_LENGTH,data);
	}

}
void config_model_subscription_delete_all(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID){
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+2);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_delete_all,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH,data);

	}else{
	    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+4);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_delete_all,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_DELETE_ALL_LENGTH,data);
	}
}

void config_model_subscription_overwrite(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID){
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(addr,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+4);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_overwrite,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH,data);

	}else {
	    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_LITTLE_ENDIAN_FILL2(addr,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+4);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+6);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_overwrite,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_OVERWRITE_LENGTH,data);
	}
}

void config_model_subscription_virtual_address_add(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned char* virtual_addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID){
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    memcpy(data+2,virtual_addr,16);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+18);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_virtual_address_add,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH,data);
	}else {
	    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    memcpy(data+2,virtual_addr,16);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+18);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+20);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_virtual_address_add,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_ADD_LENGTH,data);
	}
}

void config_model_subscription_virtual_address_delete(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned char* virtual_addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID){
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    memcpy(data+2,virtual_addr,16);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+18);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_virtual_address_delete,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH,data);
	}else {
	    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    memcpy(data+2,virtual_addr,16);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+18);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+20);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_virtual_address_delete,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_DELETE_LENGTH,data);
	}


}
void config_model_subscription_virtual_address_overwrite(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned char* virtual_addr,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID){
	    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    memcpy(data+2,virtual_addr,16);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+18);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_virtual_address_overwrite,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH,data);
	}else {
	    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    memcpy(data+2,virtual_addr,16);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+18);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+20);
		jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_subscription_virtual_address_overwrite,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_VIRTUAL_ADDRESS_OVERWRITE_LENGTH,data);
	}
}


void config_sig_model_subscription_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id)
{
    unsigned char data[CONFIG_SIG_MODEL_SUBSCRIPTION_GET_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+2);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_sig_model_subscription_get,
                    netkey_index,
                    CONFIG_SIG_MODEL_SUBSCRIPTION_GET_LENGTH,data);

}
void config_vendor_model_subscription_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id)
{
    unsigned char data[CONFIG_VENDOR_MODEL_SUBSCRIPTION_GET_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+2);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+4);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_vendor_model_subscription_get,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_SUBSCRIPTION_GET_LENGTH,data);
}

void config_netkey_add(unsigned short dst,unsigned short netkey_index,unsigned char* key)
{
    unsigned char data[CONFIG_NETKEY_ADD_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    memcpy(data+2,key,16);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_netkey_add,
                    netkey_index,
                    CONFIG_NETKEY_ADD_LENGTH,data);
}
void config_netkey_update(unsigned short dst,unsigned short netkey_index,unsigned char* key)
{
    unsigned char data[CONFIG_NETKEY_UPDATE_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    memcpy(data+2,key,16);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_netkey_update,
                    netkey_index,
                    CONFIG_NETKEY_UPDATE_LENGTH,data);
}
void config_netkey_delete(unsigned short dst,unsigned short netkey_index)
{
    unsigned char data[CONFIG_NETKEY_DELETE_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_netkey_delete,
                    netkey_index,
                    CONFIG_NETKEY_DELETE_LENGTH,data);
}
void config_netkey_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_netkey_get,
                    netkey_index,
                    CONFIG_NETKEY_GET_LENGTH,NULL);
}
void config_network_transmit_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_network_transmit_get,
                    netkey_index,
                    CONFIG_NETKEY_TRANSMIT_GET_LENGTH,NULL);
}
void config_network_transmit_set(unsigned short dst,unsigned short netkey_index,unsigned char counts,unsigned char steps)
{
    static unsigned char temp;
    temp=(steps<<3)|counts;
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_network_transmit_set,
                    netkey_index,
                    CONFIG_NETKEY_TRANSMIT_SET_LENGTH,&temp);
}
void config_key_refresh_phase_get(unsigned short dst,unsigned short netkey_index)
{
    unsigned char data[CONFIG_KEY_REFRESH_PHASE_GET_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_key_refresh_phase_get,
                    netkey_index,
                    CONFIG_KEY_REFRESH_PHASE_GET_LENGTH,data);
}
void config_key_refresh_phase_set(unsigned short dst,unsigned short netkey_index,unsigned char transition)
{
    unsigned char data[CONFIG_KEY_REFRESH_PHASE_SET_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    data[2]=transition;
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_key_refresh_phase_set,
                    netkey_index,
                    CONFIG_KEY_REFRESH_PHASE_SET_LENGTH,data);
}
void config_node_identity_get(unsigned short dst,unsigned short netkey_index)
{
    unsigned char data[CONFIG_NODE_IDENTITY_GET_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_node_identity_get,
                    netkey_index,
                    CONFIG_NODE_IDENTITY_GET_LENGTH,data);
}
void config_node_identity_set(unsigned short dst,unsigned short netkey_index,unsigned char identity)
{
    unsigned char data[CONFIG_NODE_IDENTITY_SET_LENGTH];
    JMESH_KEY_INDEX_PACK1(netkey_index,data);
    data[2]=identity;
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_node_identity_set,
                    netkey_index,
                    CONFIG_NODE_IDENTITY_SET_LENGTH,data);
}

void config_model_app_bind(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short appkey_index,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID)
	{
    unsigned char data[CONFIG_SIG_MODEL_APP_BIND_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
    JMESH_KEY_INDEX_PACK1(appkey_index,data+2);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+4);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_app_bind,
                    netkey_index,
                    CONFIG_SIG_MODEL_APP_BIND_LENGTH,data);
	}else {
    unsigned char data[CONFIG_VENDOR_MODEL_APP_BIND_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
    JMESH_KEY_INDEX_PACK1(appkey_index,data+2);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+4);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+6);
    jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_app_bind,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_APP_BIND_LENGTH,data);
	}
}

void config_model_app_unbind(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,unsigned short appkey_index,jmesh_model_id_t* model_id)
{
	if(model_id->model_id == JMESH_MODEL_ID_INVALID)
	{
	    unsigned char data[CONFIG_SIG_MODEL_APP_UNBIND_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_KEY_INDEX_PACK1(appkey_index,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+4);
        jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_app_unbind,
                    netkey_index,
                    CONFIG_SIG_MODEL_APP_UNBIND_LENGTH,data);

	}else {
	    unsigned char data[CONFIG_VENDOR_MODEL_APP_UNBIND_LENGTH];
	    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
	    JMESH_KEY_INDEX_PACK1(appkey_index,data+2);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+4);
	    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+6);
        jmesh_config_send(dst,&config_client,
                    message_config_opcode_model_app_unbind,
                    netkey_index,
                    CONFIG_VENDOR_MODEL_APP_UNBIND_LENGTH,data);
	}
}


void config_sig_model_app_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id)
{
    unsigned char data[CONFIG_SIG_MODEL_APP_GET_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->sig_id,data+2);
    jmesh_config_send(dst,&config_client,
                message_config_opcode_sig_model_app_get,
                netkey_index,
                CONFIG_SIG_MODEL_APP_GET_LENGTH,data);
}

void config_vendor_model_app_get(unsigned short dst,unsigned short element_addr,unsigned short netkey_index,jmesh_model_id_t* model_id)
{
    unsigned char data[CONFIG_VENDOR_MODEL_APP_GET_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(element_addr,data);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->company_id,data+2);
    JMESH_LITTLE_ENDIAN_FILL2(model_id->model_id,data+4);
    jmesh_config_send(dst,&config_client,
                message_config_opcode_vendor_model_app_get,
                netkey_index,
                CONFIG_VENDOR_MODEL_APP_GET_LENGTH,data);
}

void config_node_reset(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,
                message_config_opcode_node_reset,
                netkey_index,
                CONFIG_NODE_RESET_LENGTH,NULL);
}

void config_heartbeat_publication_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,
                message_config_opcode_heartbeat_publication_get,
                netkey_index,
                CONFIG_HEARTBEAT_PUBLICATION_GET_LENGTH,NULL);
}
void config_heartbeat_publication_set(unsigned short dst,unsigned short netkey_index,unsigned short heartbeat_dest,unsigned char count_log,unsigned char period_log,unsigned char TTL,unsigned short features)
{
    unsigned char data[CONFIG_HEARTBEAT_PUBLICATION_SET_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(heartbeat_dest,data);
    data[2]=count_log;
    data[3]=period_log;
    data[4]=TTL;
    JMESH_LITTLE_ENDIAN_FILL2(features,data+5);
    JMESH_KEY_INDEX_PACK1(netkey_index,data+7);
    jmesh_config_send(dst,&config_client,
                message_config_opcode_heartbeat_publication_set,
                netkey_index,
                CONFIG_HEARTBEAT_PUBLICATION_SET_LENGTH,data);
}
void config_heartbeat_subscription_get(unsigned short dst,unsigned short netkey_index)
{
    jmesh_config_send(dst,&config_client,
                message_config_opcode_heartbeat_subscription_get,
                netkey_index,
                CONFIG_HEARTBEAT_SUBSCRIPTION_GET_LENGTH,NULL);
}
void config_heartbeat_subscription_set(unsigned short dst,unsigned short netkey_index,unsigned short heartbeat_source,unsigned short heartbeat_dest,unsigned char period_log)
{
    unsigned char data[CONFIG_HEARTBEAT_SUBSCRIPTION_SET_LENGTH];
    JMESH_LITTLE_ENDIAN_FILL2(heartbeat_source,data);
    JMESH_LITTLE_ENDIAN_FILL2(heartbeat_dest,data+2);
    data[4]=period_log;
    jmesh_config_send(dst,&config_client,
                message_config_opcode_heartbeat_subscription_set,
                netkey_index,
                CONFIG_HEARTBEAT_SUBSCRIPTION_SET_LENGTH,data);
}

