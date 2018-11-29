#include"jmesh_gatt_callback.h"
#include"../../jmesh/jmesh_print.h"
#include"jmesh_gatt.h"
void jmesh_gatt_connected_callback(unsigned char* mac,unsigned char id){
  print_buffer_info(6,mac,"gatt %d connected:",id);
}
void jmesh_gatt_disconnected_callback(unsigned char id){
	
	jmesh_gatt_t* gatt = jmesh_gatt_get_by_id(id);
	
  print_buffer_info(6,gatt->mac,"gatt %d disconnect\n,mac:",id);
}

void jmesh_gatt_recv_callback(unsigned char id,unsigned short instance,unsigned short length,unsigned char* data){

}
