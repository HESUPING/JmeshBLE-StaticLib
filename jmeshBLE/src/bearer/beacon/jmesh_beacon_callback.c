#include"jmesh_beacon_callback.h"


void jmesh_device_beacon_usr_info_set_callback(unsigned char len,unsigned char* info){
    int i;
    for(i=0;i<len;i++){
        info[i]='0'+i;
    }
}
