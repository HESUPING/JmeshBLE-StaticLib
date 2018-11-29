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

void jmesh_state_init_flags(void)
{
    jmesh_save_read(JMESH_SAVE_STATE_FLAGS,sizeof(jmesh_flags_t),(unsigned char*)&jmesh_flags);
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