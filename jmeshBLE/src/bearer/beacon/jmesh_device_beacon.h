#ifndef JMESH_DEVICE_BEACON_H
#define JMESH_DEVICE_BEACON_H



typedef enum{
    BEACON_OOB_OTHER=0x0001,
    BEACON_OOB_URI=0x0002,
    BEACON_OOB_2D_CODE=0x0004,
    BEACON_OOB_BAR_CODE=0x0008,
    BEACON_OOB_NFC=0x0010,
    BEACON_OOB_NUMBER=0x0020,
    BEACON_OOB_STRING=0x0040,
    BEACON_OOB_RESERVED=0x0080,
    BEACON_OOB_ON_BOX=0x0800,
    BEACON_OOB_INSIDE_BOX=0x1000,
    BEACON_OOB_ON_PAPER=0x2000,
    BEACON_OOB_INSIDE_MANUAL=0x4000,
    BEACON_OOB_ON_DEVICE=0x8000,
}BEACON_OOB_T;


#define JMESH_DEVICE_BEACON_INTERVAL_S 3


#define JMESH_DEVICE_OOB BEACON_OOB_ON_PAPER
#define JMESH_DEVICE_URI "bcmeter light controller"
#define JMESH_DEVICE_URI_HASH 0x12345678

typedef struct st_jmesh_device_beacon{
    union{
        unsigned char UUID[16];
        struct{
            unsigned char mac[6];
            unsigned char usr_info[10];
        };
    };
    unsigned char OOB[2];
    unsigned char URI[4];
}jmesh_device_beacon_t;

void jmesh_device_beacon_start(unsigned short times);
void jmesh_device_beacon_stop(void);
void jmesh_device_beacon_handler(jmesh_device_beacon_t* beacon);
#endif // JMESH_DEVICE_BEACON_H
