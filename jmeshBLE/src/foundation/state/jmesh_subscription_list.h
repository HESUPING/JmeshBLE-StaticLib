#ifndef JMESH_SUBSCRIPTION_LIST_H
#define JMESH_SUBSCRIPTION_LIST_H

#define JMESH_SUBSCRIPTION_LIST_SIZE 5

typedef struct st_jmesh_subscription_list{
    unsigned short addr[JMESH_SUBSCRIPTION_LIST_SIZE];
}jmesh_subscription_list_t;

void jmesh_subscription_list_init(jmesh_subscription_list_t* sub_list);
int jmesh_subscription_list_add(jmesh_subscription_list_t* sub_list,unsigned short addr);
int jmesh_subscription_list_remove(jmesh_subscription_list_t* sub_list,unsigned short addr);
int jmesh_subscription_list_overwrite(jmesh_subscription_list_t* sub_list,unsigned short addr);
int jmesh_subscription_list_delete_all(jmesh_subscription_list_t* sub_list);
int jmesh_subscription_list(jmesh_subscription_list_t* sub_list,unsigned char* ret_buffer);
int jmesh_subscription_list_is_in(jmesh_subscription_list_t* sub_list,unsigned short addr);

#endif // JMESH_SUBSCRIPTION_LIST_H
