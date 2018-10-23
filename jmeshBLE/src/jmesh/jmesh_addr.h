#ifndef JMESH_ADDR_H
#define JMESH_ADDR_H

#define JMESH_ADDR_ALL_ROUTING  0xfffb
#define JMESH_ADDR_ALL_PROXIES  0xfffc
#define JMESH_ADDR_ALL_FRIENDS  0xfffd
#define JMESH_ADDR_ALL_RELAYS   0xfffe
#define JMESH_ADDR_ALL          0xffff

#define JMESH_ADDR_UNICAST_MAX 0x7fff
#define JMESH_ADDR_VIRTUAL_MAX 0xbfff
#define JMESH_ADDR_GROUP_MAX 0xfffa


#define JMESH_INVALID_ELEMENT 0xff
typedef enum{
    JMESH_ADDR_UNASSIGNED=0,
    JMESH_ADDR_UNICAST,
    JMESH_ADDR_VIRTUAL,
    JMESH_ADDR_GROUP,
    JMESH_ADDR_GROUP_ROUTING,
    JMESH_ADDR_GROUP_PROXIES,
    JMESH_ADDR_GROUP_FRIENDS,
    JMESH_ADDR_GROUP_RELAYS,
    JMESH_ADDR_GROUP_ALL,
}JMESH_ADDR_T;
typedef unsigned short jmesh_addr_t;


int jmesh_addr_get_type(jmesh_addr_t addr);

void jmesh_addr_init(void);
unsigned char jmesh_get_element_by_addr(unsigned short addr);
unsigned short jmesh_get_addr_by_element(unsigned char element);
unsigned char jmesh_get_element_num(void);
int jmesh_set_primary_addr(unsigned short primary_addr);
unsigned short jmesh_get_primary_addr(void);
int jmesh_is_my_addr(unsigned short addr);



#endif // MESH_ADDRESS_H
