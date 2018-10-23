#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"../jmesh_save.h"
#include"stdio.h"
#include"nvds.h"


int jmesh_save_write(signed short name, unsigned short length, unsigned char *data){
    if(NVDS_OK==nvds_put(name+NVDS_TAG_APP_SPECIFIC_FIRST,length,data))
    {
        return 0;
    }
    return -1;
}
int jmesh_save_read(signed short name, unsigned short length, unsigned char *data){
    nvds_tag_len_t len=length;
    if(NVDS_OK==nvds_get(name+NVDS_TAG_APP_SPECIFIC_FIRST,&len,data))
    {
        return len;
    }
    return 0;
}
void jmesh_save_delete(signed short name){
    nvds_del(name+NVDS_TAG_APP_SPECIFIC_FIRST);
}

#endif
