#include"../../jmesh/jmesh_print.h"

#include"light_config_callback.h"

void light_config_client_button_status_callback(unsigned short src,light_config_client_button_t* config){
    print_info("light config button status %d\n",config->button_id);
}
void light_config_server_scene_status_callback(unsigned short src,light_config_server_scene_t* config){

    print_info("light config scene status %d\n",config->scene_id);
}
