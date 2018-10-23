#include"jmesh_state.h"
#include"string.h"

static jmesh_mac_t jmesh_mac;
static unsigned long jmesh_seq = 0;
static unsigned char jmesh_default_ttl = 0;
static jmesh_flags_t jmesh_flags ;

void jmesh_mac_init(void)
{
		jmesh_save_read(TAG_BD_ADDRESS-TAG_APP_SPECIFIC_FIRST,sizeof(jmesh_mac_t),jmesh_mac);
}
void jmesh_mac_get(jmesh_mac_t mac)
{
    memcpy(mac,jmesh_mac,JMESH_MAC_SIZE);
		
}
void jmesh_mac_set(jmesh_mac_t mac)
{
    memcpy(jmesh_mac,mac,JMESH_MAC_SIZE);
    jmesh_save_write(TAG_BD_ADDRESS-TAG_APP_SPECIFIC_FIRST,sizeof(jmesh_mac_t),jmesh_mac);
}

void jmesh_seq_init(void)
{
    jmesh_save_read(JMESH_SAVE_SEQ,sizeof(unsigned long),(unsigned char*)&jmesh_seq);
    jmesh_seq+=10000;
    jmesh_save_write(JMESH_SAVE_SEQ,sizeof(unsigned long),(unsigned char*)&jmesh_seq);
}
void jmesh_state_add_seq(void)
{
    static unsigned short write_count=0;
    if(write_count++>=10000){
        write_count=0;
        jmesh_save_write(JMESH_SAVE_SEQ,sizeof(unsigned long),(unsigned char*)&jmesh_seq);
        if(jmesh_seq>=JMESH_SEQ_WARNING_FLOW){
            ;//TODO: iv index update
        }
    }
    jmesh_seq++;
}
unsigned long jmesh_state_get_seq(void)
{
    return jmesh_seq;
}
void jmesh_state_clear_seq(void)
{
    jmesh_seq=0;
    jmesh_save_write(JMESH_SAVE_SEQ,sizeof(unsigned long),(unsigned char*)&jmesh_seq);
}
void jmesh_state_set_seq(unsigned long seq)
{
    jmesh_seq=seq;
    jmesh_save_write(JMESH_SAVE_SEQ,sizeof(unsigned long),(unsigned char*)&jmesh_seq);
}
void jmesh_default_ttl_init(void)
{
    if(0==jmesh_save_read(JMESH_SAVE_DEFAULT_TTL,sizeof(unsigned char),&jmesh_default_ttl)){
        jmesh_default_ttl=5;
    }
}
void jmesh_default_ttl_set(unsigned char default_ttl)
{
    if(default_ttl==0||(default_ttl!=1&&default_ttl<0x80)){
        jmesh_default_ttl = default_ttl;
        jmesh_save_write(JMESH_SAVE_DEFAULT_TTL,sizeof(unsigned char),&jmesh_default_ttl);
    }
}
unsigned char jmesht_default_ttl_get(void)
{
    return jmesh_default_ttl;
}

void jmesh_state_init_flags(void)
{
    jmesh_save_read(JMESH_SAVE_STATE_FLAGS,sizeof(jmesh_flags_t),(unsigned char*)&jmesh_flags);
}
void jmesh_state_set_relay(unsigned char relay_state)
{
    if(relay_state<2){
        if(jmesh_flags.relay!=relay_state){
            jmesh_flags.relay=relay_state;
            jmesh_save_write(JMESH_SAVE_STATE_FLAGS,sizeof(jmesh_flags_t),(unsigned char*)&jmesh_flags);
        }
    }
}
unsigned char jmesh_state_get_relay(void)
{
    #if(JMESH_FEATURE_RELAY==JMESH_FEATURE_DISABLE)
        return 2;
    #else
        return jmesh_flags.relay;
    #endif
}

int jmesh_state_set_secure_network_beacon(unsigned char secure_network_beacon_state)
{
    if(secure_network_beacon_state<2){
        if(jmesh_flags.secure_network_beacon!=secure_network_beacon_state){
            jmesh_flags.secure_network_beacon=secure_network_beacon_state;
            jmesh_save_write(JMESH_SAVE_STATE_FLAGS,sizeof(jmesh_flags_t),&jmesh_flags.flags);
        }
				return JMESH_STATUS_SUCCESS;
    }
		return -1;
}
unsigned char jmesh_state_get_secure_network_beacon(void)
{
    #if(JMESH_FEATURE_BEACON==JMESH_FEATURE_DISABLE)
        return 2;
    #else
        return jmesh_flags.secure_network_beacon;
    #endif
}

void jmesh_state_set_gatt_proxy(unsigned char gatt_proxy_state)
{
    if(gatt_proxy_state<2){
        if(jmesh_flags.gatt_proxy!=gatt_proxy_state){
            jmesh_flags.gatt_proxy=gatt_proxy_state;
            jmesh_save_write(JMESH_SAVE_STATE_FLAGS,sizeof(jmesh_flags),&jmesh_flags.flags);
        }
    }
}
unsigned char jmesh_state_get_gatt_proxy(void)
{
    #if(JMESH_FEATURE_GATT==JMESH_FEATURE_DISABLE)
        return 2;
    #else
        return jmesh_flags.gatt_proxy;
    #endif
}


void jmesh_state_set_friend(unsigned char state)
{
    if(state<2){
        if(jmesh_flags.friend_state!=state){
            jmesh_flags.friend_state=state;
            jmesh_save_write(JMESH_SAVE_STATE_FLAGS,sizeof(jmesh_flags),&jmesh_flags.flags);
        }
    }
}
unsigned char jmesh_state_get_friend(void)
{
    #if(JMESH_FEATURE_FRIEND==JMESH_FEATURE_DISABLE)
        return 2;
    #else
        return jmesh_flags.friend_state;
    #endif
}

int jmesh_composition_page_data_get(unsigned char* data)
{
		unsigned char model_len = 0,length = 0;
		JMESH_LITTLE_ENDIAN_FILL2(JMESH_MODEL_COMPANY_ID,data);
		JMESH_LITTLE_ENDIAN_FILL2(JMESH_PRODUCT_ID,data+2);
		JMESH_LITTLE_ENDIAN_FILL2(JMESH_VERSION_ID,data+4);
		JMESH_LITTLE_ENDIAN_FILL2(REPLAY_PROTECTION_LIST_SIZE,data+6);
		JMESH_LITTLE_ENDIAN_FILL2(jmesh_flags.flags,data+8);

	/*  foundation element*/
		JMESH_LITTLE_ENDIAN_FILL2(JMESH_ELEMENT_LOC,data+10);
		length = 12;
		model_len = jmesh_list_model_id(jmesh_element_get_by_index(0),data+length+2);
		data[length++] =  model_len/2;
		data[length++] = 0;
		length += model_len;
	/*  app element*/	
		JMESH_LITTLE_ENDIAN_FILL2(JMESH_ELEMENT_LOC,data+length);	
		length += 2;
		model_len = jmesh_list_model_id(jmesh_element_get_by_index(1),data+length+2);
		data[length++] = 0;
		data[length++] = model_len/2;
		length += model_len;		
		return length;
}