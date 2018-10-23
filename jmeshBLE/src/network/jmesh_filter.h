#ifndef JMESH_FILTER_H
#define JMESH_FILTER_H

#define JMESH_FILTER_TYPE_WHITE_LIST 0
#define JMESH_FILTER_TYPE_BLACK_LIST 1
#define JMESH_FILTER_SIZE 10



typedef struct st_jmesh_filter{
    unsigned char type;
    unsigned char num;
    unsigned short addr[JMESH_FILTER_SIZE];
}jmesh_filter_t;

void jmesh_filter_init(jmesh_filter_t* filter);

void jmesh_filter_set_type(jmesh_filter_t* filter,unsigned char type);
void jmesh_filter_add_addr(jmesh_filter_t* filter,unsigned short addr);
void jmesh_filter_remove_addr(jmesh_filter_t* filter,unsigned short addr);
int jmesh_filter_status(jmesh_filter_t* filter,unsigned char buffer_size,unsigned char* buffer);
int jmesh_filter_get_type(jmesh_filter_t* filter);

/** \brief filtering a address
 *
 * \param filter ptr
 * \param address
 * \return 1=ok address,0=err address
 *
 */
int jmesh_filter_filtering(jmesh_filter_t* filter,unsigned short addr);

#endif // JMESH_FILTER_H
