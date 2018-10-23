#ifndef JMESH_SECURE_BEACON_H
#define JMESH_SECURE_BEACON_H

#define BEACON_EXPECTED_INTERVAL 10
#define BEACON_OBSERVATION_PERIOD_S 60
#define BEACON_INTERVAL_MAX         120

#define BEACON_EXPECTED_NUMBER    (BEACON_OBSERVATION_PERIOD_S/BEACON_EXPECTED_INTERVAL)
#define BEACON_TIME_CACHE_SIZE  ((BEACON_INTERVAL_MAX*BEACON_EXPECTED_INTERVAL)/BEACON_OBSERVATION_PERIOD_S)


typedef struct st_jmesh_secure_beacon{
    unsigned char :6;
    unsigned char iv_update_flag    :1;//when IV updating(use IV and IV-1)
    unsigned char key_refresh_flag  :1;//when netkey phase =2
    unsigned char network_id[8];
    unsigned char iv_index[4];
    unsigned char authentication_value[8];
}jmesh_secure_beacon_t;

void jmesh_secure_beacon_start(int adv_time);
void jmesh_secure_beacon_stop(void);
void jmesh_secure_beacon_handler(jmesh_secure_beacon_t* beacon);
#endif // JMESH_SECURE_BEACON_H
