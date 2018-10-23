#ifndef JMESH_BIND_H
#define JMESH_BIND_H


#include"jmesh_appkey.h"
#define JMESH_BIND_APP_SIZE 6

typedef struct st_jmesh_model_bind{
    unsigned char index[JMESH_BIND_APP_SIZE];
}jmesh_model_bind_t;

void jmesh_bind_init(jmesh_model_bind_t* model_bind);
int jmesh_bind_app(jmesh_model_bind_t* model_bind,jmesh_appkey_t* appkey);
int jmesh_unbind_app(jmesh_model_bind_t* model_bind,jmesh_appkey_t* appkey);
int jmesh_is_bind(jmesh_model_bind_t* model_bind,jmesh_appkey_t* appkey);
int jmesh_bind_list(jmesh_model_bind_t* model_bind,unsigned char buffer_size,unsigned char* buffer);
#endif // JMESH_BIND_H
