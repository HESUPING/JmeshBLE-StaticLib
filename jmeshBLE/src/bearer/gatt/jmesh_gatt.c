#include"../../jmesh/jmesh_pdu.h"
#include"jmesh_gatt.h"
#include"jmesh_gatt_callback.h"
#include"../../driver/jmesh_ble.h"
#include"string.h"
#include"jmesh_proxy.h"
#include"../../upper/routing/jmesh_routing_neighbor_table.h"
#include"../../upper/routing/jmesh_routing_table.h"
#include"../../upper/routing/jmesh_routing.h"
#include"../../onchip_system/os_timer_event.h"
#include"../../BLE/jmesh_prov_svc.h"
#include"../../jmesh/jmesh_print.h"
#include"../../driver/jmesh_system.h"
#include"../../foundation/state/jmesh_state.h"
static jmesh_gatt_t gatt_table[JMESH_GATT_SIZE];

void jmesh_gatt_init(void)
{
    int i;
    for(i=0;i<JMESH_GATT_SIZE;i++){
        gatt_table[i].flag=0;
        gatt_table[i].recv_cache=NULL;
    }
}
void jmesh_gatt_disconnect(jmesh_gatt_t* gatt){
    if(NULL==gatt){
        return;
    }
    else if(gatt->is_ready){
        jmesh_ble_gatt_disconnect(gatt->id);
        jmesh_gatt_disconnected(gatt->id);
    }
}
int jmesh_gatt_ready_num(void)
{
    int i,count;
    for(i=0,count=0;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_ready){
            count++;
        }
    }
    return count;
}

jmesh_gatt_t* jmesh_gatt_get_by_mac(unsigned char* mac){
    int i;
    for(i=0;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_valid){
            if(0==memcmp(mac,gatt_table[i].mac,6)){
                return &gatt_table[i];
            }
        }
    }
    return NULL;
}
jmesh_gatt_t* jmesh_gatt_get_by_id(unsigned char id)
{
    int i;
    for(i=0;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_ready){
            if(id==gatt_table[i].id){
                return &gatt_table[i];
            }
        }
    }
    return NULL;
}
jmesh_gatt_t* jmesh_gatt_get_by_interface(unsigned char interface){
    if(interface<JMESH_GATT_SIZE){
        if(gatt_table[interface].is_ready){
            return &gatt_table[interface];
        }
    }
    return NULL;
}
unsigned char jmesh_gatt_get_interface(jmesh_gatt_t* gatt){
    if(gatt!=NULL){
      return gatt - gatt_table;
    }
    return JMESH_GATT_SIZE;
}
jmesh_gatt_t* jmesh_gatt_next(jmesh_gatt_t* gatt){
    int i;
    if(gatt==NULL){
        i=-1;
    }
    else{
        i=gatt-gatt_table;
    }
    for(i++;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_valid){
            return &gatt_table[i];
        }
    }
    return NULL;
}
int jmesh_gatt_is_ready(jmesh_gatt_t* gatt){
    if(gatt!=NULL){
        return gatt->is_ready;
    }
    return 0;
}
void jmesh_gatt_connected(unsigned char* mac,unsigned char id,unsigned char is_server){
    int i,null_index;
    static unsigned char mesh_uuid[16]=JMESH_SVC_UUID;

    jmesh_neighbor_t* neighbor;

    jmesh_gatt_connected_callback(mac,id);
    
    for(i=0,null_index=-1;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_valid){
            if(0==memcmp(mac,gatt_table[i].mac,6)){
              break;
            }
         }
        else if(null_index==-1){
          null_index=i;
        }
    }
    if(i<JMESH_GATT_SIZE){
      null_index=i;
    }
    if(null_index>=0){
        memcpy(gatt_table[null_index].mac,mac,6);
        gatt_table[null_index].is_valid=1;
        gatt_table[null_index].is_ready=1;
        gatt_table[null_index].id=id;
        gatt_table[null_index].is_server=is_server;
        gatt_table[null_index].mtu=GATT_DEFAULT_MTU;
        gatt_table[null_index].svc_instance=jmesh_ble_get_local_svc_ins();//disc svc if a client,else get local svc instance
        //all node own the same svc instance.....
        if(NULL!=(neighbor=jmesh_neighbor_get_by_mac(mac)))
        {
            jmesh_route_add(null_index,neighbor->addr,neighbor->element_num,1,neighbor->seq);
        }
        //os_timer_event_set(&gatt_table[null_index].drop_timer,GATT_CON_ACTIVE_MS,(os_timer_event_caller_t)jmesh_gatt_disconnect,&gatt_table[null_index]);
    }
    else{
      jmesh_ble_gatt_disconnect(id);
    }
}
void jmesh_gatt_disconnected(unsigned char connect_id){
    jmesh_gatt_t* gatt;
    jmesh_neighbor_t* neighbor;
    jmesh_gatt_disconnected_callback(connect_id);
    if(NULL!=(gatt=jmesh_gatt_get_by_id(connect_id))){
        gatt->flag=0;
        if(NULL!=gatt->recv_cache){
            jmesh_pdu_free(gatt->recv_cache);
            gatt->recv_cache=NULL;
        }
        os_timer_event_remove(&gatt->drop_timer);
        if(NULL!=(neighbor=jmesh_neighbor_get_by_mac(gatt->mac)))
        {
            jmesh_route_del(neighbor->addr,neighbor->seq);
        }
    }
}
void jmesh_gatt_set_mtu(unsigned char id, unsigned short mtu){
    jmesh_gatt_t* gatt;
    if(NULL!=(gatt=jmesh_gatt_get_by_id(id))){
        gatt->mtu=mtu-3;
    }
}
void jmesh_gatt_set_svc_instance(unsigned char id,unsigned short instance)
{
    jmesh_gatt_t* gatt;
    if(NULL!=(gatt=jmesh_gatt_get_by_id(id))){
        gatt->svc_instance=instance;
    }
}

void jmesh_gatt_recv(unsigned char id,unsigned short instance,unsigned short length,unsigned char* data)
{
    jmesh_gatt_t* gatt;
    jmesh_gatt_recv_callback(id,instance,length,data);
    if(NULL==(gatt=jmesh_gatt_get_by_id(id))){
        return;
    }
    else{
				if(instance-gatt->svc_instance == JMESHS_IDX_MESH_MAC_VAL)
				{
						jmesh_mac_set(data);
						return ;
				}
        jmesh_proxy_recv(gatt,instance,length,data);
    }
}

void jmesh_gatt_send(jmesh_gatt_t* gatt,unsigned short instance,unsigned char length,unsigned char* data)
{
    if(NULL==gatt || !gatt->is_ready){
        return;
    }
    if(!gatt->is_server){
        jmesh_ble_gatt_notify(gatt->id,instance,length,data);
    }
    else{
        jmesh_ble_gatt_write(gatt->id,instance,length,data);
    }
}

