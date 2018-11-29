#ifndef BEACON_H_
#define BEACON_H_
#include <stdint.h>
#include "sdk_mesh_config.h"

#define NET_BEACON_CMAC_SIZE   (8)

#define BEACON_TYPE_LENGTH 1
#define BEACON_DATA_OFFSET BEACON_TYPE_LENGTH
#define DEVICE_UUID_OFFSET 0
#define DEVICE_UUID_LENGTH MESH_DEVICE_UUID_LENGTH
#define OOB_INFO_OFFSET (DEVICE_UUID_OFFSET + DEVICE_UUID_LENGTH)
#define OOB_INFO_LENGTH 2
#define URI_HASH_OFFSET (OOB_INFO_OFFSET + OOB_INFO_LENGTH)
#define URI_HASH_LENGTH 4


#define BEACON_IV_INDEX_LENGTH 4
#define BEACON_FLAG_LENGTH 1

#define BEACON_SEC_PKT_LENGTH (NET_BEACON_CMAC_SIZE + NETWORK_ID_LENGTH +  BEACON_IV_INDEX_LENGTH + BEACON_FLAG_LENGTH + BEACON_TYPE_LENGTH)

#define MESH_SEC_BEACON_TICK   (2000) //unit: ms/ 10s
#define MESH_SEC_OBE_TICK      (10000) //unit: ms/ 10s


#define MAX_BEACON_NETKEY_SEARCH_SIZE (DM_CFG_NETKEY_MAX_NUM)

#define MAX_BEACON_NETKEY_INVALID_POS (MAX_BEACON_NETKEY_SEARCH_SIZE+1)

#define MAX_BEACON_RX_COUNTER (MESH_SEC_OBE_TICK/MESH_SEC_BEACON_TICK)

#define  MESH_SEC_BEACON_FLAG_TICK  (10*60)


/** Number of periods to keep beacon observations of. */
#define MESH_BEACON_OBSERVATION_PERIODS 2


typedef struct
{
    uint8_t key_refresh        : 1; /**< Key refresh procedure initiated. */
    uint8_t iv_update          : 1; /**< IV update active. */
    uint8_t _rfu               : 6; /**< Reserved for future use. */
}__attribute((packed)) net_beacon_sec_flags_t;


typedef struct
{
    net_beacon_sec_flags_t flags;                           /**< Beacon flags. */
    uint8_t                network_id[NETWORK_ID_LENGTH];   /**< Network identifier. */
    uint32_t               iv_index;                        /**< Current IV index. */
}__attribute((packed)) net_beacon_payload_t;

/**
 * Secure Network Broadcast Beacon.
 */
typedef struct
{
    net_beacon_payload_t payload;                    /**< Payload of the secure network beacon. */
    uint8_t              cmac[NET_BEACON_CMAC_SIZE]; /**< CMAC authentication value. */
}__attribute((packed)) net_beacon_t;



typedef struct
{
    /** received number of beacons in each preceding period. */
    uint16_t rx_count[MESH_BEACON_OBSERVATION_PERIODS];
    uint32_t tx_timecounter;
} mesh_beacon_tx_info_t;

void stop_current_beacon(void);
void unprovisioned_dev_beacon_start(uint8_t *dev_uuid,uint16_t OOB_info,uint32_t *URI_hash);
void beacon_rx(uint8_t *data,uint8_t length);
void iv_update_beacon_send_immediately(void);
void mesh_sec_beacon_rx_pkt_inc(uint8_t *network_id);
void mesh_sec_beacon_init(void);
bool is_sec_beacon(uint8_t *data,uint8_t length);

extern void (*unprovisioned_dev_beacon_rx_callback)(uint8_t *,uint16_t ,uint32_t *);
#endif

