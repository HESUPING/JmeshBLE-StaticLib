#include"jmesh_addr.h"
#include"jmesh_save.h"
#include"../network/jmesh_interface.h"

int jmesh_addr_get_type(jmesh_addr_t addr)
{
    if(addr==JMESH_ADDR_UNASSIGNED){
        return JMESH_ADDR_UNASSIGNED;
    }
    if(addr<=JMESH_ADDR_UNICAST_MAX){
        return JMESH_ADDR_UNICAST;
    }
    if(addr<=JMESH_ADDR_VIRTUAL_MAX){
        return JMESH_ADDR_VIRTUAL;
    }
    if(addr<=JMESH_ADDR_GROUP_MAX){
        return JMESH_ADDR_GROUP;
    }
    return JMESH_ADDR_GROUP_ROUTING+addr-JMESH_ADDR_ALL_ROUTING;
}
static unsigned short jmesh_primary_addr;

void jmesh_addr_init(void){
    if(2!=jmesh_save_read(JMESH_SAVE_ADDR,2,(unsigned char*)&jmesh_primary_addr)){
        jmesh_primary_addr=JMESH_ADDR_UNASSIGNED;
    }
}
unsigned char jmesh_get_element_by_addr(unsigned short addr){
    if(addr < jmesh_primary_addr || addr > (jmesh_primary_addr+jmesh_get_element_num()) || (jmesh_primary_addr == JMESH_ADDR_UNASSIGNED)){
        return JMESH_INVALID_ELEMENT;
    }
    return addr-jmesh_primary_addr;
}
unsigned short jmesh_get_addr_by_element(unsigned char element){
    if(element>jmesh_get_element_num()||jmesh_primary_addr==JMESH_ADDR_UNASSIGNED){
        return JMESH_ADDR_UNASSIGNED;
    }
    return jmesh_primary_addr+element;
}
unsigned char jmesh_get_element_num(void){
    return 2;
}
int jmesh_set_primary_addr(unsigned short primary_addr){
    if(primary_addr==JMESH_ADDR_UNASSIGNED || primary_addr+jmesh_get_element_num()>JMESH_ADDR_UNICAST_MAX){
        return -1;
    }
    jmesh_primary_addr=primary_addr;
    jmesh_save_write(JMESH_SAVE_ADDR,2,(unsigned char*)&jmesh_primary_addr);
		jmesh_interface_init();
    return 0;
}
unsigned short jmesh_get_primary_addr(void){
    return jmesh_primary_addr;
}
int jmesh_is_my_addr(unsigned short addr){
    if(jmesh_primary_addr==JMESH_ADDR_UNASSIGNED||addr<jmesh_primary_addr||addr>=jmesh_primary_addr+jmesh_get_element_num()){
        return 0;
    }
    return 1;
}
