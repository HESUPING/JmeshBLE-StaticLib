#ifndef JMESH_SEQ_H
#define JMESH_SEQ_H

#include"../jmesh/jmesh_types.h"
#define JMESH_SEQ_LIST_SIZE 100

typedef struct st_jmesh_seq_list{
    unsigned short addr :15;
    unsigned long ivi   :1;
    unsigned short seq_high;
}jmesh_seq_list_t;

unsigned long jmesh_seq_get(void);
void jmesh_seq_add(void);
void jmesh_seq_init(void);
void jmesh_seq_clear(void);
void jmesh_seq_remove(unsigned short src);
void jmesh_seq_list_init(void);
void jmesh_seq_set(unsigned short src,unsigned char ivi,unsigned long seq);
int jmesh_seq_is_valid(unsigned short src,unsigned char ivi,unsigned char active_ivi,unsigned long seq);
void jmesh_seq_set_local(unsigned long seq);


#endif // JMESH_SEQ_LIST_H
