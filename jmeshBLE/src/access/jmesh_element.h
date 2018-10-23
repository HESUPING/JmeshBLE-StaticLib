#ifndef JMESH_ELEMENT_H
#define JMESH_ELEMENT_H
#include"jmesh_model.h"

typedef struct st_jmesh_element jmesh_element_t;
struct st_jmesh_element{
    jmesh_element_t* next;
    jmesh_model_t* model_list;
};

#define JMESH_ELEMENT_NAME(name) extern jmesh_element_t name;
#define JMESH_ELEMENT_CREATE(name) jmesh_element_t name={0,0};
void jmesh_element_add_model(jmesh_element_t *element,jmesh_model_t* model);
int jmesh_list_model_id(jmesh_element_t* element,unsigned char* buffer);

#endif // JMESH_ELEMENT_H
