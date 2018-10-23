#include"jmesh_bind.h"
#include"jmesh_appkey.h"
#include"../../jmesh/jmesh_types.h"

void jmesh_bind_init(jmesh_model_bind_t* model_bind){
    int i;
    for(i=0;i<JMESH_BIND_APP_SIZE;i++){
        model_bind->index[i]=0xff;
    }
}
int jmesh_bind_app(jmesh_model_bind_t* model_bind,jmesh_appkey_t* appkey)
{
    int i;
    unsigned char index=jmesh_appkey_get_index(appkey);
    for(i=0;i<JMESH_BIND_APP_SIZE;i++){
        if(model_bind->index[i]==index){
            return JMESH_STATUS_SUCCESS;
        }
    }
    for(i=0;i<JMESH_BIND_APP_SIZE;i++){
        if(model_bind->index[i]==0xff){
            model_bind->index[i]=index;
            return JMESH_STATUS_SUCCESS;
        }
    }
    return JMESH_STATUS_CANNOT_BIND;
}
int jmesh_unbind_app(jmesh_model_bind_t* model_bind,jmesh_appkey_t* appkey)
{
    int i;
    unsigned char index;
    index=jmesh_appkey_get_index(appkey);
    for(i=0;i<JMESH_BIND_APP_SIZE;i++){
        if(model_bind->index[i]==index){
            model_bind->index[i]=0xff;
            return JMESH_STATUS_SUCCESS;
        }
    }
    return JMESH_STATUS_CANNOT_REMOVE;
}
int jmesh_is_bind(jmesh_model_bind_t* model_bind,jmesh_appkey_t* appkey){
    unsigned char index,i;
    index=jmesh_appkey_get_index(appkey);
    for(i=0;i<JMESH_BIND_APP_SIZE;i++){
        if(model_bind->index[i]==index){
            return 1;
        }
    }
    return 0;
}
int jmesh_bind_list(jmesh_model_bind_t* model_bind,unsigned char buffer_size,unsigned char* buffer){
    int i,index=0,length = 0;
    for(i=0;i<JMESH_BIND_APP_SIZE;i++){
				index = model_bind->index[i];
				if(index!= 0xff)
				{
						jmesh_appkey_t* appkey = jmesh_appkey_get_by_index(index);
						if((length %3) == 0)
						{
								buffer[length] = (appkey->appkey_index)&0xff;
								length++;
								buffer[length] = (appkey->appkey_index)>>8;
								length++;
						}else
						{
							  buffer[length-1] |= (appkey->appkey_index)<<4;
							  buffer[length]  = (appkey->appkey_index)>>4;
							  length++;
						}
				}
	 }	
	 return length;
}






