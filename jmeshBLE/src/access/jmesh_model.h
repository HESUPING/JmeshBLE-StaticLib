#ifndef JMESH_MODEL_H
#define JMESH_MODEL_H
#include"jmesh_message.h"
#include"../foundation/state/jmesh_bind.h"
#include"../foundation/state/jmesh_subscription_list.h"

typedef struct st_jmesh_model_id{
    union{
        unsigned short sig_id;
        unsigned short company_id;
    };
    unsigned short model_id;

}jmesh_model_id_t;
typedef struct st_jmesh_model_info jmesh_model_info_t;
struct st_jmesh_model_info{
    jmesh_model_id_t model_id;
    unsigned char message_num;
    struct{
        jmesh_message_t message;
        jmesh_message_handler_t handler;
    }
    message[1];
};
typedef struct st_jmesh_model jmesh_model_t;
typedef struct st_jmesh_element jmesh_element_t;
typedef struct st_jmesh_model_para{
    jmesh_model_bind_t bind_app;
    jmesh_subscription_list_t subscription_list;
}jmesh_model_para_t;

struct st_jmesh_model{
    jmesh_model_t* next;
    const jmesh_model_info_t* info;
    jmesh_model_para_t para;
    jmesh_element_t* element;
    unsigned char id;
};

#define JMESH_MODEL_ID_INVALID 0xffff
#define JMESH_MODEL_COMPANY_ID 0xbcbd
#define JMESH_SIG_MODEL_CREATE_START(name,sig_id,messages)  \
    JMESH_MODEL_CREATE_START(name,sig_id,JMESH_MODEL_ID_INVALID,messages)

#define JMESH_VENDOR_MODEL_CREATE_START(name,company_id,model_id,messages)  \
    JMESH_MODEL_CREATE_START(name,company_id,model_id,messages)

#define JMESH_MODEL_CREATE_START(name,id1,id2,messages) \
 const struct st_jmesh_model_##name{                                \
    jmesh_model_id_t id;                                            \
    unsigned char message_num;                                      \
     struct{                                        \
        jmesh_message_t message;                    \
        jmesh_message_handler_t handler;            \
    }message[messages];                              \
}model_##name={{{id1},id2},messages,{

#define JMESH_MESSAGE_ADD(message,handler)  {message,(jmesh_message_handler_t)handler},

#define JMESH_MODEL_CREATE_END(name) }};jmesh_model_t name={0,(const jmesh_model_info_t*)&model_##name};

/*in use model name should be static protected*/
#define JMESH_MODEL_NAME(name) extern jmesh_model_t name



typedef struct st_jmesh_element jmesh_element_t;
jmesh_model_t* jmesh_model_get_by_sig_id(jmesh_element_t* element,unsigned short sig_id);
jmesh_model_t* jmesh_model_get_by_vendor_id(jmesh_element_t* element,unsigned short company_id,unsigned short model_id);

int jmesh_model_addr_check(jmesh_model_t* model,unsigned short element_addr,unsigned short addr);

void jmesh_model_subscription_list_init(jmesh_model_t* model);
int jmesh_model_subscription_list_add(jmesh_model_t* model,unsigned short addr);
int jmesh_model_subscription_list_remove(jmesh_model_t* model,unsigned short addr);
int jmesh_model_subscription_list_overwrite(jmesh_model_t* model,unsigned short addr);
int jmesh_model_subscription_list_delete_all(jmesh_model_t* model);
int jmesh_model_subscription_list_is_in(jmesh_model_t* model,unsigned short addr);
int jmesh_model_subscription_list(jmesh_model_t* model,unsigned char* ret_buffer);
void jmesh_model_bind_init(jmesh_model_t* model);
int jmesh_model_bind_app(jmesh_model_t* model,jmesh_appkey_t* appkey);
int jmesh_model_unbind_app(jmesh_model_t* model,jmesh_appkey_t* appkey);
int jmesh_model_is_bind(jmesh_model_t* model,jmesh_appkey_t* appkey);
int jmesh_model_bind_list(jmesh_model_t* model,unsigned char buffer_size,unsigned char* buffer);

#endif // JMESH_MODEL_H
