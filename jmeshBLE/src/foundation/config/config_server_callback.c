#include"stdint.h"
#include"../state/jmesh_appkey.h"
#include"../state/jmesh_state.h"
#include"../../access/jmesh_model.h"
#include"../state/jmesh_appkey.h"
#include"../../access/jmesh_access.h"
#include"config_server.h"
#include"config_client.h"
#include"config_server_callback.h"
#include"../../jmesh/jmesh_print.h"
#include "config_client_app.h"
#include"../../jmesh/jmesh_types.h"
#include"../../network/jmesh_netkey.h"
int config_appkey_add_server_callback(unsigned short netkey_index,unsigned short appkey_index,uint8_t* ret_buffer)
{
		return jmesh_appkey_set(netkey_index,appkey_index,ret_buffer);
}
int config_appkey_delete_server_callback(unsigned short netkey_index,unsigned short appkey_index)
{    

    return jmesh_appkey_delete(netkey_index,appkey_index);
}

/*return the variable length*/
int config_appkey_get_server_callback(unsigned short netkey_index,unsigned char length,unsigned char* ret_buffer)
{    
    return jmesh_appkey_list(netkey_index,length,ret_buffer);
}
int config_appkey_update_server_callback(unsigned short netkey_index,unsigned short appkey_index,uint8_t* ret_buffer)
{

    return jmesh_appkey_update(netkey_index,appkey_index,ret_buffer);
}

int config_beacon_get_server_callback(void)
{
    return jmesh_state_get_secure_network_beacon();
}

int config_beacon_set_server_callback(unsigned char beacon)
{
    return jmesh_state_set_secure_network_beacon(beacon);
    
}
int config_composition_get_server_handler(unsigned char page,unsigned char buffer_size,unsigned char* ret_buffer)
{
		int length = 0;
    length = jmesh_composition_page_data_get(ret_buffer);
		if(length>buffer_size)		print_error("composition data buffersize is too smaller!");
		return length;
}

int config_default_ttl_get_server_callback(void)
{
/*
    ret_buffer[0]=jmesh_state_get_default_ttl();
*/    return 0;
}

int config_default_ttl_set_server_callback(unsigned char ttl)
{
/*
    jmesh_state_set_default_ttl(data[0]);
    ret_buffer[0]=jmesh_state_get_default_ttl();
*/    return 0;
}
int config_gatt_proxy_get_server_callback(void)
{
/*
    ret_buffer[0]=jmesh_get_proxy_feature();
*/    return 0 ;
}

int config_gatt_proxy_set_server_callback(unsigned char proxy)
{
/*
    jmesh_set_proxy_feature(data[0]);
    ret_buffer[0]=jmesh_get_proxy_feature();
*/    return 0 ;
}

int config_friend_get_server_callback(void)
{
/*
    ret_buffer[0]=jmesh_get_friend_feature();
*/    return 0;
}
int config_friend_set_server_callback(unsigned char friend)
{
/*
    jmesh_set_friend_feature(data[0]);
    ret_buffer[0]=jmesh_get_friend_feature();
*/    return 0;
}

int config_relay_get_server_callback(void)
{
/*
    ret_buffer[0]=jmesh_get_relay_feature();
*/    return 0;
}
int config_relay_set_server_callback(unsigned char relay)
{
/*
    jmesh_set_relay_feature(data[0]);
    ret_buffer[0]=jmesh_get_relay_feature();
*/    return 0;
}

int config_sig_model_publication_get_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
/*
    unsigned short model_id1,model_id2;
    unsigned short model,addr;
    unsigned short model_instance;
    jmesh_publication_t* publication;
    JMESH_LITTLE_ENDIAN_PICK2(model_id1,data+2);
    JMESH_LITTLE_ENDIAN_PICK2(model_id2,data+4);
    model=jmesh_get_vendor_model(model_id1,model_id2);
    addr=(((unsigned short)data[1])<<8)|data[0];
    model_instance=jmesh_get_model_instance(jmesh_get_element_by_address(addr),model);
    ret_buffer[0]=jmesh_state_get_publication(model_instance,&publication);
    ret_buffer[1]=data[0];
    ret_buffer[2]=data[1];
    if(publication!=NULL){
        memcpy(ret_buffer+3,(unsigned char*)publication,sizeof(jmesh_publication_t));
        memcpy(ret_buffer+3+sizeof(jmesh_publication_t)-1,data+2,length-2);//publication align 2 octects but own 9 data
        return 31+length+sizeof(jmesh_publication_t)-1;
    }
*/    return 3;
}
int config_vendor_model_publication_get_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
/*
    unsigned short model_id1,model_id2;
    unsigned short model,addr;
    unsigned short model_instance;
    jmesh_publication_t* publication;
    JMESH_LITTLE_ENDIAN_PICK2(model_id1,data+2);
    model=jmesh_get_sig_model(model_id1);
    addr=(((unsigned short)data[1])<<8)|data[0];
    model_instance=jmesh_get_model_instance(jmesh_get_element_by_address(addr),model);
    ret_buffer[0]=jmesh_state_get_publication(model_instance,&publication);
    ret_buffer[1]=data[0];
    ret_buffer[2]=data[1];
    if(publication!=NULL){
        memcpy(ret_buffer+3,(unsigned char*)publication,sizeof(jmesh_publication_t));
        memcpy(ret_buffer+3+sizeof(jmesh_publication_t)-1,data+2,length-2);//publication align 2 octects but own 9 data
        return 31+length+sizeof(jmesh_publication_t)-1;
    }
*/    return 3;
}
int config_sig_model_publication_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
/*
    unsigned short model_id1,model_id2;
    unsigned short model,addr;
    unsigned short model_instance;
    jmesh_publication_t publication;
    JMESH_LITTLE_ENDIAN_PICK2(model_id1,data+9);
    model=jmesh_get_sig_model(model_id1);
    JMESH_LITTLE_ENDIAN_PICK2(addr,data);
    model_instance=jmesh_get_model_instance(jmesh_get_element_by_address(addr),model);
    memcpy((unsigned char*)&publication,data+2,7);

    ret_buffer[0]=jmesh_state_set_publication(model_instance,&publication);
    memcpy(ret_buffer+1,data,length);
    return length+1;*/
		return 0;
}
int config_vendor_model_publication_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
/*
    unsigned short model_id1,model_id2;
    unsigned short model,addr;
    unsigned short model_instance;
    jmesh_publication_t publication;
    JMESH_LITTLE_ENDIAN_PICK2(model_id1,data+9);
    JMESH_LITTLE_ENDIAN_PICK2(model_id2,data+11);
    model=jmesh_get_vendor_model(model_id1,model_id2);
    JMESH_LITTLE_ENDIAN_PICK2(addr,data);
    model_instance=jmesh_get_model_instance(jmesh_get_element_by_address(addr),model);
    memcpy((unsigned char*)&publication,data+2,7);

    ret_buffer[0]=jmesh_state_set_publication(model_instance,&publication);
    memcpy(ret_buffer+1,data,length);
    return length+1; */
		return 0;
}
int config_model_publication_virtual_address_sig_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_model_publication_virtual_address_vendor_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_sig_model_subscription_add_server_callback(jmesh_model_t* sig_model,unsigned short address)
{
		return jmesh_model_subscription_list_add(sig_model,address);
}
int config_vendor_model_subscription_add_server_callback(jmesh_model_t* vendor_model, unsigned short address)
{
		return jmesh_model_subscription_list_add(vendor_model,address);
}

int config_sig_model_subscription_delete_server_callback(jmesh_model_t* model,unsigned short address)
{
		return jmesh_model_subscription_list_remove(model,address);
}
int config_vendor_model_subscription_delete_server_callback(jmesh_model_t* model,unsigned short address)
{
		return  jmesh_model_subscription_list_remove(model,address);
}
int config_sig_model_subscription_delete_all_server_callback(jmesh_model_t* model)
{
		return jmesh_model_subscription_list_delete_all(model);
}
int config_vendor_model_subscription_delete_all_server_callback(jmesh_model_t* model)
{

		return jmesh_model_subscription_list_delete_all(model);

}
int config_sig_model_subscription_overwrite_server_callback(jmesh_model_t* model,unsigned short address)
{		
		return jmesh_model_subscription_list_overwrite(model,address);
}
int config_vendor_model_subscription_overwrite_server_callback(jmesh_model_t* model,unsigned short address)
{
		return jmesh_model_subscription_list_overwrite(model,address);
}
int config_sig_model_subscription_virtual_address_add_server_callback(jmesh_model_t* model,unsigned char* virtual_addr)
{
		return 0 /* TODO: call corresponding function*/;
}

int config_vendor_model_subscription_virtual_address_add_server_callback(jmesh_model_t* model,unsigned char* virtual_addr)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_sig_model_subscription_virtual_address_delete_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}

int config_vendor_model_subscription_virtual_address_delete_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_sig_model_subscription_virtual_address_overwrite_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}

int config_vendor_model_subscription_virtual_address_overwrite_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_sig_model_subscription_get_server_callback(jmesh_model_t* model,uint8_t* ret_buffer)
{
		return jmesh_model_subscription_list(model,ret_buffer+5);	
}
int config_vendor_model_subscription_get_server_callback(jmesh_model_t* model,uint8_t* ret_buffer)
{
		return jmesh_model_subscription_list(model,ret_buffer+7);
}

int config_netkey_add_server_callback(unsigned short netkey_index,uint8_t* key)
{

		return jmesh_netkey_state_set(netkey_index,key);

	
}
int config_netkey_update_server_callback(unsigned short netkey_index,uint8_t* key)
{

		return jmesh_netkey_state_update(netkey_index,key);

}
int config_netkey_delete_server_callback(unsigned short netkey_index)
{

		return jmesh_netkey_state_del(netkey_index);

}
int config_netkey_get_server_callback(unsigned char buffer_size,unsigned char* ret_buffer)
{
		 return jmesh_netkey_state_list(buffer_size,ret_buffer);
}
int config_key_refresh_phase_get_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_key_refresh_phase_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}

int config_network_transmit_get_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}
int config_network_transmit_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0 /* TODO: call corresponding function*/;

}

int config_sig_model_app_bind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey)
{
		return jmesh_model_bind_app(model,appkey);
}
int config_vendor_model_app_bind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey)
{
		return jmesh_model_bind_app(model,appkey);
}
int config_sig_model_app_unbind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey)
{
		return jmesh_model_unbind_app(model,appkey);
}
int config_vendor_model_app_unbind_server_callback(jmesh_model_t* model,jmesh_appkey_t* appkey)
{
		return jmesh_model_unbind_app(model,appkey);
}

int config_sig_model_app_get_server_callback(jmesh_model_t* model,unsigned char buffer_size,unsigned char* ret_buffer)
{
		return  jmesh_model_bind_list(model,buffer_size, ret_buffer);
}
int config_vendor_model_app_get_server_callback(jmesh_model_t* model,unsigned char buffer_size,unsigned char* ret_buffer)
{

		return jmesh_model_bind_list(model,buffer_size, ret_buffer);

}

int config_node_identity_get_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0;
}
int config_node_identity_set_server_callback(uint8_t* data,uint8_t* ret_buffer)
{
		return 0;
}
