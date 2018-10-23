#include"jmesh_beacon.h"
//#include "log.h"


void jmesh_beacon_handler(unsigned char *mac,unsigned char rssi,jmesh_beacon_t* beacon)
{
    switch(beacon->type){
    case(JMESH_BEACON_TYPE_DEVICE):
        //LOG(LOG_LVL_INFO,"\nmac:...%02x receive device beacon\n",mac[5]);
        jmesh_device_beacon_handler(&beacon->device_beacon);
        break;

    case(JMESH_BEACON_TYPE_SECURE):
        //LOG(LOG_LVL_INFO,"\nmac:...%02x receive secure beacon\n",mac[5]);
        jmesh_secure_beacon_handler(&beacon->secure_beacon);
        break;

    case(JMESH_BEACON_TYPE_ROUTING):
        //LOG(LOG_LVL_INFO,"\nmac:...%02x receive routing beacon\n",mac[5]);
        jmesh_routing_beacon_handler(mac,rssi,&beacon->routing_beacon);
        break;
    }
}
