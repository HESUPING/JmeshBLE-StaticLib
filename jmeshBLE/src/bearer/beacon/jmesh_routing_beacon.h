#ifndef JMESH_ROUTING_BEACON_H
#define JMESH_ROUTING_BEACON_H

#define JMESH_ROUTING_BEACON_INTERVAL_S 5
#define ROUTE_SEQ_REFRESH_INTERVAL_S 3



typedef struct st_jmesh_routing_beacon{
    unsigned char :3;
    unsigned char is_relay:1;
    unsigned char connect_num:4;
    unsigned char addr[2];
    unsigned char element_num;
    unsigned char route_seq[2];
    unsigned char neighbor_num;
    unsigned char authentication_value[8];
}jmesh_routing_beacon_t;

void jmesh_start_routing_seq_count(void);
unsigned short jmesh_get_routing_seq(void);

void jmesh_routing_beacon_start(int adv_time);
void jmesh_routing_beacon_stop(void);
void jmesh_routing_beacon_handler(unsigned char *mac,unsigned char rssi,jmesh_routing_beacon_t* beacon);

#endif // JMESH_ROUTING_BEACON_H
