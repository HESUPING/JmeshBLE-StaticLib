#include"../../jmesh/jmesh_types.h"
#include"jmesh_subscription_list.h"


void jmesh_subscription_list_init(jmesh_subscription_list_t* sub_list){
    int i;
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE;i++){
        sub_list->addr[i]=0;
    }
}
int jmesh_subscription_list_add(jmesh_subscription_list_t* sub_list,unsigned short addr)
{
    int i;
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE;i++){
        if(sub_list->addr[i]==addr){
            return JMESH_STATUS_SUCCESS;
        }
    }
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE;i++){
        if(sub_list->addr[i]==0){
            sub_list->addr[i]=addr;
            return JMESH_STATUS_SUCCESS;
        }
    }
    return JMESH_STATUS_STORAGE_FAILURE;
}
int jmesh_subscription_list_remove(jmesh_subscription_list_t* sub_list,unsigned short addr){
    int i;
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE;i++){
        if(sub_list->addr[i]==addr){
            sub_list->addr[i]=0;
            return JMESH_STATUS_SUCCESS;
        }
    }
    return JMESH_STATUS_CANNOT_REMOVE;
}
int jmesh_subscription_list_overwrite(jmesh_subscription_list_t* sub_list,unsigned short addr){
    int i;
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE;i++){
        sub_list->addr[i]=0;
    }
    sub_list->addr[i]=addr;
    return JMESH_STATUS_SUCCESS;
}
int jmesh_subscription_list_delete_all(jmesh_subscription_list_t* sub_list){
    int i;
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE;i++){
        sub_list->addr[i]=0;
    }
    return JMESH_STATUS_SUCCESS;
}

int jmesh_subscription_list_is_in(jmesh_subscription_list_t* sub_list,unsigned short addr){
    int i;
    for(i=0;i<JMESH_SUBSCRIPTION_LIST_SIZE&&sub_list->addr[i]!=0;i++){
        if(sub_list->addr[i]==addr){
            return 1;
        }
    }
    return 0;
}
int jmesh_subscription_list(jmesh_subscription_list_t* sub_list,unsigned char* ret_buffer)
{
		unsigned char index = 0;
		for(int i=0;i< JMESH_SUBSCRIPTION_LIST_SIZE;i++)
		{
				if(sub_list->addr[i] !=0)
				{
						memcpy(ret_buffer+index,sub_list->addr+i,2);
						index+=2;
				}
		}
		return index;
}
