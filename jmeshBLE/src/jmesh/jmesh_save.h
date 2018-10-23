#ifndef JMESH_SAVE_H
#define JMESH_SAVE_H



int jmesh_save_read(signed short name,unsigned char length,unsigned char* data);
int jmesh_save_write(signed short name,unsigned char length,unsigned char* data);
int jmesh_save_delete(signed short name);

#define jmesh_save_buffer_read(name,index,length,data)  jmesh_save_read(name+index,length,data)
#define jmesh_save_buffer_write(name,index,length,data) jmesh_save_write(name+index,length,data)
#define jmesh_save_buffer_delete(name,index)            jmesh_save_delete(name+index)





#include"jmesh_save_define.h"

#define JMESH_SAVE_DEFINE
#define JMESH_SAVE_CREATE(name) name,
#define JMESH_SAVE_BUFFER_CREATE(name,num) name,name##_tail=name+num-1,
enum{
    #include"jmesh_save_define.h"
    JMESH_SAVE_SIZE
};
#undef JMESH_SAVE_CREATE
#undef JMESH_SAVE_BUFFER_CREATE
#undef JMESH_SAVE_DEFINE



#endif

