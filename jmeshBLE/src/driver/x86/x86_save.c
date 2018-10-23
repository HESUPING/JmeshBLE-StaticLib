#include"../jmesh_driver_config.h"
#if(JMESH_DRIVER_X86)

#include"../jmesh_save.h"
#include"stdio.h"


int jmesh_save_write(signed short name, unsigned short length, unsigned char *data){
    int i;
    printf("save write name %d,length %d,data:",name,length);
    for(i=0;i<length;i++){
        printf("%x",data[i]);
    }
    printf("\n");
    return length;
}
int jmesh_save_read(signed short name, unsigned short length, unsigned char *data){
    printf("save read name %d,length %d\n",name,length);
    return 0;
}
void jmesh_save_delete(signed short name){
    printf("save delete name %d\n",name);
}
#endif
