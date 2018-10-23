#ifndef JMESH_CONFIG_H
#define JMESH_CONFIG_H
#include"jmesh_types.h"


#define JMESH_NETKEY_MAX_NUM 5
#define JMESH_APPKEY_MAX_NUM 5
#define JMESH_DEVICE_MAX_NUM 100
#define JMESH_MODEL_MAX_NUM  10

#define JMESH_FEATURE_RELAY    JMESH_FEATURE_ENABLE
#define JMESH_FEATURE_PROXY    JMESH_FEATURE_ENABLE
#define JMESH_FEATURE_FRIEND   JMESH_FEATURE_ENABLE
#define JMESH_FEATURE_LOWPOWER JMESH_FEATURE_UNSUPPORTED
#if((JMESH_FEATURE_FRIEND==JMESH_FEATURE_ENABLE)&&(JMESH_FEATURE_LOWPOWER==JMESH_FEATURE_ENABLE))
//    #error feature friend and lowpower cannot be bose support
#endif

#define JMESH_CMD_PRINTABLE 0
#define JMESH_INFO_PRINTABLE 0
#define JMESH_NOTE_PRINTABLE 0
#define JMESH_WARNING_PRINTABLE 0
#define JMESH_ERROR_PRINTABLE 0


/**< use for jmesh pdu.c */
#define JMESH_LONG_PDU_CACHE_SIZE 10
#define JMESH_SHORT_PDU_CACHE_SIZE 50

/**< use for jmesh_adv.c */
#define JMESH_ADV_MAX_MS 20
#define JMESH_ADV_MIN_MS 100
#define JMESH_SCAN_MAX_MS 300
#define JMESH_SCAN_MIN_MS 100
#define JMESH_ADV_CACHE_SIZE 40



//friend node and low power node
#define JMESH_FRIEND_NETKEY_INDEX 0

//friend node macro
#define JMESH_FRIENDSHIP_MAX_NUM 5/**< a friend establish friendship num ,a low power node cache friend offer num*/
#define JMESH_FRIEND_CACHE_QUEUE_SIZE 10/**< a friendship cache pdu num */
#define JMESH_FRIEND_RECEIVE_WINDOW 100/**< 1-256 ms */

//low power node macro
/**< 0=1,1=1.5,2=2,3=2.5 */
#define JMESH_FRIEND_FACTOR_1_0 0
#define JMESH_FRIEND_FACTOR_1_5 1
#define JMESH_FRIEND_FACTOR_2_0 2
#define JMESH_FRIEND_FACTOR_2_5 3

#define JMESH_FRIEND_RSSI_FACTOR JMESH_FRIEND_FACTOR_2_0
#define JMESH_FRIEND_RECEIVE_WINDOW_FACTOR JMESH_FRIEND_FACTOR_2_0
#define JMESH_FRIEND_MIN_QUEUE_SIZE_LOG 3/**< 2^3=8 */
#define JMESH_FRIEND_RECEIVE_DELAY 100/**<  */
#define JMESH_FRIEND_POLL_TIMEOUT  100UL/**< 9-34bbff,100*100ms=10s */
#define JMESH_FRIEND_REQUEST_INTERVAL_MS 10000/**< must be larger than 1.1s */



#endif // JMESH_CONFIG_H
