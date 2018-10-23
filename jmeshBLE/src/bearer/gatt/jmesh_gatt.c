
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

#include"../../jmesh/jmesh_print.h"
#include"../../driver/jmesh_system.h"

static os_timer_event_t connect_schedule_timer;

static jmesh_gatt_t gatt_table[JMESH_GATT_SIZE];

static os_timer_event_t route_remove_timer;
static unsigned char route_remove_overtime=1;

static void route_remove_schedule(void)
{
    route_remove_overtime=1;
    os_timer_event_restart(&route_remove_timer);
}

#if 0
void jmesh_connect_schedule(void)
{
    static unsigned char mac[6] = {0x99,0x22,0x33,0x44,0x55,0xF0};
    os_timer_event_restart(&connect_schedule_timer);

    jmesh_gatt_connect_client(mac);
}

void gatt_connect_test(void)
{
    os_timer_event_set(&connect_schedule_timer,5000,(os_timer_event_caller_t)jmesh_connect_schedule,NULL);
}
#endif

#if 0
void jmesh_connect_schedule(void)
{
    jmesh_neighbor_t* neighbor;

    os_timer_event_restart(&connect_schedule_timer);

    if(jmesh_gatt_ready_num()<JMESH_GATT_CONNECT_LIMIT){
        if(NULL==(neighbor=jmesh_neighbor_pick_best())){
            return;
        }
        jmesh_gatt_connect_client(neighbor->mac);
    }
}
#endif
#if 1
extern jmesh_neighbor_t neighbor_table[JMESH_NEIGHBOR_TABLE_SIZE];

void jmesh_connect_schedule(void)
{
    jmesh_gatt_t* gatt;
    //jmesh_neighbor_t* neighbor;
    int neighbor_num;
    static int i=0;

    os_timer_event_restart(&connect_schedule_timer);
    neighbor_num=jmesh_get_neighbor_num();
    //i=jmesh_random_get(0,neighbor_num+1);


    if(jmesh_gatt_ready_num()<JMESH_GATT_CONNECT_LIMIT){
        if(i>=neighbor_num)
        {
            i=0;
        }
        for(;i<neighbor_num;i++)
        {
            if(neighbor_table[i].is_valid)
            {
                gatt=jmesh_gatt_get_by_mac(neighbor_table[i].mac);
                if(NULL==gatt)
                {
                    jmesh_gatt_connect_client(neighbor_table[i].mac);
                    return;
                }

            }

        }
    }
}
#endif // 0

void jmesh_gatt_init(void)
{
    int i;
    for(i=0;i<JMESH_GATT_SIZE;i++){
        gatt_table[i].flag=0;
        gatt_table[i].recv_cache=NULL;
    }
    os_timer_event_set(&route_remove_timer,JMESH_ROUTE_REMOVE_INTERVAL_S*1000,(os_timer_event_caller_t)route_remove_schedule,NULL);
    //os_timer_event_set(&connect_schedule_timer,JMESH_GATT_CONNECT_INTERVAL_S*1000,(os_timer_event_caller_t)jmesh_connect_schedule,NULL);
}

jmesh_gatt_t* jmesh_gatt_connect_server(unsigned char* mac)
{
    int i,null_index;

    for(i=0,null_index=-1;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_valid){
            if(0==memcmp(mac,gatt_table[i].mac,6)){
                return &gatt_table[i];
            }
        }
        else if(null_index<0){
            null_index=i;
        }
    }
    if(null_index>=0){
        if(0!=jmesh_ble_gatt_connect(mac)){
            return NULL;
        }
        print_note("connect server...mac[%02x]\n",mac[5]);
        memcpy(gatt_table[null_index].mac,mac,6);
        gatt_table[null_index].is_valid=1;
        gatt_table[null_index].is_ready=0;
        gatt_table[null_index].is_server=0;
        gatt_table[null_index].svc_instance=0;
        //os_timer_event_set(&gatt_table[null_index].drop_timer,JMESH_GATT_CONNECT_S*1000,(os_timer_event_caller_t)jmesh_gatt_disconnect,&gatt_table[null_index]);
        return &gatt_table[null_index];
    }
    else{//local connect num full,use default connect
        return NULL;
    }
}
jmesh_gatt_t* jmesh_gatt_connect_client(unsigned char* mac){

    int i,null_index;

    for(i=0,null_index=-1;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_valid){
            if(0==memcmp(mac,gatt_table[i].mac,6)){
                return &gatt_table[i];
            }
        }
        else if(null_index<0){
            null_index=i;
        }
    }
    if(null_index>=0){
        print_note("connect client...mac[%02x]\n",mac[5]);
        jmesh_ble_send_adv(ADV_MODE_CREATE_CONN,0xff,6,mac);// send a connect require adv with target mac
        memcpy(gatt_table[null_index].mac,mac,6);
        gatt_table[null_index].is_valid=1;
        gatt_table[null_index].is_ready=0;
        gatt_table[null_index].is_server=1;
        gatt_table[null_index].svc_instance=0;
        //os_timer_event_set(&gatt_table[null_index].drop_timer,JMESH_GATT_CONNECT_S*1000,(os_timer_event_caller_t)jmesh_gatt_disconnect,&gatt_table[null_index]);
        return &gatt_table[null_index];
    }
    else{//local connect num full,use default connect
        return NULL;
    }
}

void jmesh_gatt_disconnect(jmesh_gatt_t* gatt){
    if(NULL==gatt){
        return;
    }
    else if(gatt->is_ready){
        jmesh_ble_gatt_disconnect(gatt->id);
        //jmesh_gatt_disconnected_callback(gatt->id);
        //jmesh_pdu_free(gatt->recv_cache);
        //gatt->recv_cache=NULL;
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
        return &gatt_table[interface];
    }
    return NULL;
}
unsigned char jmesh_gatt_get_interface(jmesh_gatt_t* gatt){

    return gatt - gatt_table;
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
    return gatt->is_ready;
}

void jmesh_gatt_connected(unsigned char* mac,unsigned char id){
    int i,null_index;
    static unsigned char mesh_uuid[16]=JMESH_SVC_UUID;

    jmesh_neighbor_t* neighbor;

    driver_ble_gatt_connected();
    jmesh_gatt_connected_callback(mac,id);

    for(i=0,null_index=-1;i<JMESH_GATT_SIZE;i++){
        if(gatt_table[i].is_valid){
            if(0==memcmp(mac,gatt_table[i].mac,6)){
                gatt_table[i].is_ready=1;
                gatt_table[i].id=id;
                gatt_table[i].mtu=0;

                if(gatt_table[i].is_server == 0){
                    jmesh_ble_exchange_mtu(id);
                    jmesh_ble_disc_svc(mesh_uuid,id);
                }
                else{
                    gatt_table[i].svc_instance=jmesh_ble_get_local_svc_ins();
                }

                if(NULL!=(neighbor=jmesh_neighbor_get_by_mac(mac)))
                {
                    jmesh_route_add(i,neighbor->addr,neighbor->element_num,1,neighbor->seq);
                }

                //os_timer_event_set(&gatt_table[null_index].drop_timer,JMESH_GATT_ACTIVE_S*1000,(os_timer_event_caller_t)jmesh_gatt_disconnect,&gatt_table[i]);
                return;
            }
        }
        else if(null_index < 0){
            null_index=i;
        }
    }
    if(null_index>=0)
    {
        memcpy(gatt_table[null_index].mac,mac,6);
        gatt_table[null_index].is_valid=1;
        gatt_table[null_index].is_ready=1;
        gatt_table[null_index].id=id;
        gatt_table[null_index].is_server=1;
        gatt_table[null_index].mtu=0;
        gatt_table[null_index].svc_instance=jmesh_ble_get_local_svc_ins();//disc svc if a client,else get local svc instance

        if(NULL!=(neighbor=jmesh_neighbor_get_by_mac(mac)))
        {
            jmesh_route_add(null_index,neighbor->addr,neighbor->element_num,1,neighbor->seq);
        }

        //os_timer_event_set(&gatt_table[null_index].drop_timer,JMESH_GATT_ACTIVE_S*1000,(os_timer_event_caller_t)jmesh_gatt_disconnect,&gatt_table[null_index]);
    }
    else{
        jmesh_ble_gatt_disconnect(id);
        //jmesh_gatt_disconnected_callback(id);
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
        }
        os_timer_event_remove(&gatt->drop_timer);
        if(NULL!=(neighbor=jmesh_neighbor_get_by_mac(gatt->mac)))
        {
            jmesh_route_del(neighbor->addr,neighbor->seq);
            if(route_remove_overtime)
            {
                route_remove_overtime=0;
                os_timer_event_restart(&route_remove_timer);
                jmesh_route_remove(neighbor->addr,neighbor->seq);
            }

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
        jmesh_proxy_recv(gatt,instance,length,data);
    }
}

void jmesh_gatt_send(jmesh_gatt_t* gatt,unsigned short instance,unsigned char length,unsigned char* data)
{
    if(NULL==gatt || !gatt->is_ready){
        return;
    }
    else if(gatt->is_server){
        jmesh_ble_gatt_notify(gatt->id,instance,length,data);
    }
    else{
        jmesh_ble_gatt_write(gatt->id,instance,length,data);
    }
}

