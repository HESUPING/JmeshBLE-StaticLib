#include"jmesh_appkey.h"
#include"../../jmesh/jmesh_types.h"
#include"../../jmesh/jmesh_save.h"
#include"../../secure/jmesh_security.h"

static jmesh_appkey_t jmesh_appkey[JMESH_APPKEY_MAX_NUM];

void jmesh_appkey_init(void)
{
    int i;
    for(i=0;i<JMESH_APPKEY_MAX_NUM;i++){
        jmesh_appkey[i].is_valid=0;
        jmesh_save_buffer_read(JMESH_SAVE_APPKEY,i,sizeof(jmesh_appkey_t),(unsigned char*)&jmesh_appkey[i]);
    }
}
int jmesh_appkey_set(unsigned short netkey_index,unsigned short appkey_index,unsigned char *key)
{
    int i,j=-1;
    for(i=0;i<JMESH_APPKEY_MAX_NUM;i++){
        if(jmesh_appkey[i].is_valid){
            if(jmesh_appkey[i].netkey_index==netkey_index && jmesh_appkey[i].appkey_index==appkey_index){
                break;
            }
        }
        else if(j<0){
            j=i;
        }
    }
    if(i<JMESH_APPKEY_MAX_NUM){
        j=i;
    }
    if(j>=0){
        jmesh_appkey[j].appkey_index=appkey_index;
        jmesh_appkey[j].netkey_index=netkey_index;
        jmesh_appkey[j].is_valid=1;
        memcpy(jmesh_appkey[j].key,key,JMESH_KEY_SIZE);
        jmesh_appkey[j].aid=jmesh_security_cal_aid(key);
        jmesh_save_buffer_write(JMESH_SAVE_APPKEY,j,sizeof(jmesh_appkey_t),(unsigned char*)&jmesh_appkey[j]);
        return JMESH_STATUS_SUCCESS;
    }
    else{
        return JMESH_STATUS_STORAGE_FAILURE;
    }
}
int jmesh_appkey_delete(unsigned short netkey_index,unsigned short appkey_index){
    int i;
    for(i=0;i<JMESH_APPKEY_MAX_NUM;i++){
        if(jmesh_appkey[i].is_valid){
            if(jmesh_appkey[i].appkey_index==appkey_index&& jmesh_appkey[i].netkey_index==netkey_index){
                jmesh_appkey[i].is_valid=0;
                jmesh_save_buffer_write(JMESH_SAVE_APPKEY,i,sizeof(jmesh_appkey_t),(unsigned char*)&jmesh_appkey[i]);
                return JMESH_STATUS_SUCCESS;
            }
        }
    }
		return JMESH_STATUS_INVALID_APPKEY_INDEX;
}

jmesh_appkey_t* jmesh_appkey_get_by_aid(unsigned short netkey_index,unsigned char aid,jmesh_appkey_t* prev_key)
{
    int i;
    if(prev_key==NULL){
        i=-1;
    }
    else{
        i=prev_key-jmesh_appkey;
    }
    for(i++;i<JMESH_APPKEY_MAX_NUM;i++){
        if( jmesh_appkey[i].is_valid&& jmesh_appkey[i].aid==aid&& jmesh_appkey[i].netkey_index==netkey_index){
            return &jmesh_appkey[i];
        }
    }
    return NULL;
}
jmesh_appkey_t* jmesh_appkey_get_by_key_index(unsigned short netkey_index,unsigned short appkey_index){
    int i;
    for(i=0;i<JMESH_APPKEY_MAX_NUM;i++){
        if(jmesh_appkey[i].is_valid&& jmesh_appkey[i].appkey_index==appkey_index&& jmesh_appkey[i].netkey_index==netkey_index){
            return &jmesh_appkey[i];
        }
    }
    return NULL;
}
jmesh_appkey_t* jmesh_appkey_get_by_index(unsigned char index){
    if(index>=JMESH_APPKEY_MAX_NUM){
        return NULL;
    }
    if(jmesh_appkey[index].is_valid==0){
        return NULL;
    }
    return &jmesh_appkey[index];
}
int jmesh_appkey_get_index(jmesh_appkey_t* appkey){
    if(appkey==NULL){
        return -1;
    }
    return appkey-jmesh_appkey;
}

int jmesh_appkey_list(unsigned short netkey_index,unsigned char buffer_size,unsigned char* pdu)
{
    int list_index,pdu_index;
    for(list_index=0,pdu_index=0;list_index<JMESH_APPKEY_MAX_NUM && (pdu_index+3<=buffer_size);list_index++){
				if(netkey_index == jmesh_appkey[list_index].netkey_index && jmesh_appkey[list_index].is_valid == 1){
					if((pdu_index%3)==0){
                pdu[pdu_index]=jmesh_appkey[list_index].appkey_index;
                pdu_index+=1;
                pdu[pdu_index]=jmesh_appkey[list_index].appkey_index>>8;
                pdu_index+=1;
            }
            else{
                pdu[pdu_index-1]|=(jmesh_appkey[list_index].appkey_index<<4);
                pdu[pdu_index]=jmesh_appkey[list_index].appkey_index>>4;
                pdu_index+=1;
            }
        }
    }
    return pdu_index;
}

int jmesh_appkey_update(unsigned short netkey_index,unsigned short appkey_index,jmesh_key_t key)
{
    int i;
    for(i=0;i<JMESH_APPKEY_MAX_NUM;i++){
        if(netkey_index==jmesh_appkey[i].netkey_index &&appkey_index==jmesh_appkey[i].appkey_index && jmesh_appkey[i].is_valid ==1)
        {
						memcpy(jmesh_appkey[i].key,key,JMESH_KEY_SIZE);
						jmesh_appkey[i].aid = jmesh_security_cal_aid(key);					
						return JMESH_STATUS_SUCCESS;
        }
    }
    return JMESH_STATUS_SUCCESS;
}
