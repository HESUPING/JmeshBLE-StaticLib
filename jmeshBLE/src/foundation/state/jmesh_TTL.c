#include"jmesh_TTL.h"
#include"../../jmesh/jmesh_save.h"
static unsigned char default_TTL;
void jmesh_TTL_init(void){
    default_TTL=0;
    jmesh_save_read(JMESH_SAVE_DEFAULT_TTL,1,&default_TTL);
}
void jmesh_TTL_set_default(unsigned char ttl){
    if(default_TTL!=ttl&& default_TTL<127){
        default_TTL=ttl;
        jmesh_save_write(JMESH_SAVE_DEFAULT_TTL,1,&default_TTL);
    }

}
unsigned char jmesh_TTL_get_default(){
    return default_TTL;
}
