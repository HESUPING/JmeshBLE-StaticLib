#ifndef JMESH_ROUTING_NEIGHBOR_TABLE_H
#define JMESH_ROUTING_NEIGHBOR_TABLE_H

#define JMESH_NEIGHBOR_MAX_SIZE 30
#define JMESH_NEIGHBOR_TABLE_SIZE JMESH_NEIGHBOR_MAX_SIZE

#define JMESH_NEIGHBOR_LIFE_TIME_S 2*60
#define JMESH_NEIGHBOR_PROTECT_TIME_S 1*60

typedef struct st_jmesh_neighbor{
    unsigned char mac[6];
    unsigned char rssi;
    union{
        unsigned char flag;
        struct{
            unsigned char is_valid:1;
            unsigned char is_mesh:1;
            unsigned char is_relay:1;
            unsigned char rfu:5;
        };
    };

    union{
        unsigned char name[8];
        struct{
            unsigned short addr;
            unsigned char element_num;
            unsigned char relay_connect_num;
            unsigned char neighbor_num;
            unsigned short seq;
        };
    };

    unsigned short life_time;
    unsigned short inactive_time;

}jmesh_neighbor_t;

void jmesh_neighbor_init(void);

void jmesh_neighbor_del(jmesh_neighbor_t* neighbor);

jmesh_neighbor_t* jmesh_neighbor_add_mesh(unsigned char* mac,unsigned short addr,unsigned char element_num,unsigned char connect_num,
                                          unsigned char neighbor_num,unsigned char is_relay,unsigned short seq,unsigned char rssi);
jmesh_neighbor_t* jmesh_neighbor_get_by_mac(unsigned char* mac);
int jmesh_get_neighbor_num(void);

jmesh_neighbor_t* jmesh_neighbor_pick_best(void);

#endif // JMESH_ROUTING_NEIGHBOR_TABLE_H
