#ifndef JMESH_NETKEY_H
#define JMESH_NETKEY_H
#include"../jmesh/jmesh_types.h"
#include"../jmesh/jmesh_config.h"
#define JMESH_NETKEY_SAVE_LENGTH 40

#define JMESH_IV_INDEX_UPDATE_LASTING_HOUR 96
#define JMESH_IV_INDEX_UPDATE_INTERVAL_HOUR 96
#define JMESH_IV_INDEX_RECOVER_INTERVAL_HOUR 192
#define JMESH_IV_INDEX_RECOVER_GREATER_MAX   42

/**
    phase description
    0
    1     receive update message,send with old key receive with old and new key
    2     receive key refresh flag =1,secured with new key,send with new key receive with old and new key
    3     receive key refresh flag =0,secured with new key,
 */

typedef struct st_jmesh_netkey_cache{
    jmesh_key_t encryption_key[2];
    jmesh_key_t privacy_key[2];
    jmesh_key_t identity_key[2];
    jmesh_key_t beacon_key[2];
    jmesh_netid_t netid[2];
    unsigned char nid[2];
}jmesh_netkey_cache_t;

typedef struct st_jmesh_netkey{
    unsigned short index:12;
    unsigned short phase:2;
    unsigned short node_identity:1;
    unsigned short new_key_index:1;
    unsigned short iv_update_flag:1;
    unsigned short min_count_timer:15;//record run time
    unsigned long iv_index;
    jmesh_key_t key[2];
    jmesh_netkey_cache_t cache;
}jmesh_netkey_t;

#define JMESH_NETKEY_GET_IV_INDEX(netkey)   ((netkey)->iv_index)
#define JMESH_NETKEY_SET_INVALID(netkey)    do{((netkey)->iv_index=0);}while(0)
#define JMESH_NETKEY_SET_VALID(netkey)      do{((netkey)->iv_index=JMESH_INIT_IV_INDEX;}while(0)
#define JMESH_NETKEY_IS_VALID(netkey)       ((netkey)->iv_index!=0)
#define JMESH_NETKEY_GET_INDEX(netkey)      ((netkey)->index)
#define JMESH_NETKEY_GET_KEY(netkey)        ((netkey)->key[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_KEY(netkey)    ((netkey)->key[1-(netkey)->new_key_index])

#define JMESH_NETKEY_GET_NID(netkey)                ((netkey)->cache.nid[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_NID(netkey)            ((netkey)->cache.nid[~(netkey)->new_key_index])
#define JMESH_NETKEY_GET_ENCRYPTION_KEY(netkey)     ((netkey)->cache.encryption_key[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_ENCRYPTION_KEY(netkey) ((netkey)->cache.encryption_key[1-(netkey)->new_key_index])
#define JMESH_NETKEY_GET_PRIVACY_KEY(netkey)        ((netkey)->cache.privacy_key[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_PRIVACY_KEY(netkey)    ((netkey)->cache.privacy_key[1-(netkey)->new_key_index])
#define JMESH_NETKEY_GET_IDENTITY_KEY(netkey)       ((netkey)->cache.identity_key[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_IDENTITY_KEY(netkey)   ((netkey)->cache.identity_key[1-(netkey)->new_key_index])
#define JMESH_NETKEY_GET_BEACON_KEY(netkey)         ((netkey)->cache.beacon_key[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_BEACON_KEY(netkey)     ((netkey)->cache.beacon_key[1-(netkey)->new_key_index])
#define JMESH_NETKEY_GET_NETID(netkey)              ((netkey)->cache.netid[(netkey)->new_key_index])
#define JMESH_NETKEY_GET_OLD_NETID(netkey)          ((netkey)->cache.netid[~(netkey)->new_key_index])


#define jmesh_netkey_get_index(netkey)  ((netkey)->index)
#define jmesh_netkey_get_phase(netkey)  ((netkey)->phase)



void jmesh_netkey_1min_schedule(void);
void jmesh_netkey_init(void);
int jmesh_netkey_state_set(unsigned short index,unsigned char* key);
int jmesh_netkey_state_get(unsigned short index,unsigned char* key);
int jmesh_netkey_state_update(unsigned short index,unsigned char* key);
int jmesh_netkey_state_del(unsigned short index);

jmesh_netkey_t* jmesh_netkey_get_by_nid(unsigned char nid,jmesh_netkey_t* prev_key);
jmesh_netkey_t* jmesh_netkey_get_by_index(unsigned short index);
/*
 * list netkey index
 *
 * Description: each index 12bit
 * Arguments  :
 * Returns    : key index format:
                --------------------------
                |key1       |    key2    |
                --------------------------
                |octet0 | octet1 | octet2|
                --------------------------

 * Note       : config netkey list
 */
int jmesh_netkey_state_list(unsigned char buffer_size,unsigned char * buffer);
/*
 * refresh netkey phase
 *
 * Description: the key refresh phase state indicates and controls the key refresh procedure for each netkey
                in the netkey list. below table defines all possible transitions of the key refresh phase state
                that can be controlled using this state
                --------------------------------------------------------------
                old state |transition | new state | description
                0         |           | 1         | transition 1 from 0 when receive a new key
                0         | 3         | 0         | transition 3 from 0 does not cause any state change
                1         | 2         | 2         | transition 2 from 1 moves to phase 2
                1         | 3         } 0         | transition 3 from 1 invokes key refresh 3 and move to phase 0
                2         | 2         | 2         | transition 2 from 2 does not cause any state change
                2         | 3         | 0         | transition 3 from 2 invokes key refresh phase 3 and then move to phase 0

 * Arguments  : netkey index
 * Returns    : JMESH_STATUS_CODE
 * Note       : config key refresh phase get
                config key refresh phase set
                config key refresh phase status
 */
int jmesh_netkey_state_transtion(unsigned short index,unsigned char transition);
int jmesh_netkey_state_set_node_identity(unsigned short index,unsigned char identity);
int jmesh_netkey_state_get_node_identity(unsigned short index,unsigned char *identity);

/** IV Update procedure summary
    IV Index  | IV Update Flag | state    | IV Index Accepted | IV Index used
    n         | 0              | normal   | n-1,n             | n
    m(m=n+1)  | 1              | progress | m-1,m             | m-1
    m         | 0              | normal   | m-1,m             | m
 */


unsigned char jmesh_netkey_get_iv_update_flag(unsigned short netkey_index);
unsigned long jmesh_netkey_get_iv_index(unsigned short netkey_index);

void jmesh_netkey_start_update_iv_index(unsigned short netkey_index);
void jmesh_netkey_stop_update_iv_index(unsigned short netkey_index);
void jmesh_netkey_recover_iv_index(unsigned short netkey_index,unsigned long iv_index);

void jmesh_netkey_test_set_iv_index(unsigned short netkey_index,unsigned long iv_index);
void jmesh_netkey_test_start_update_iv_index(unsigned short netkey_index);
void jmesh_netkey_test_stop_update_iv_index(unsigned short netkey_index );



#endif // JMESH_NETKEY_H
