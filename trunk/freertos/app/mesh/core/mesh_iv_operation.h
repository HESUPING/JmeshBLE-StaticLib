
#ifndef MESH_IV_OPERATION_H_
#define MESH_IV_OPERATION_H_


#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "mesh_definitions.h"

/** Maximum difference in sequence numbers between two SAR segments of the same sessio */
#define TRANSPORT_SAR_SEQNUM_DIFF_MAX                           (8191)

/** The minimum time between IV updates, in minutes. */
#define MESH_MIN_IV_UPDATE_INTERVAL_MINUTES (96 * 60)

/** Limit for silence recover. */
#define MESH_IV_RECOVERY_LIMIT 42

#define MESH_IV_UPDATE_TIMER_INTERVAL_US     (60000000) /**< 60 seconds. */

/** Longest time we're allowed to stay in an IV update state */
#define MESH_MAX_IV_UPDATE_INTERVAL_MINUTES  (144 * 60)
/** The minimum time between IV Recovery, in minutes. */
#define MESH_MIN_IV_RECOVERY_INTERVAL_MINUTES  (192 * 60)
/** Margin to ensure we're inside of the Mesh Profile Specification v1.0 time limits */
#define MESH_IV_UPDATE_TIME_MARGIN_MINUTES   (10)

#define MESH_IV_UPDATE_TICK   (1000*60) //unit: ms

#define MESH_IV_MS_TO_MINUTES   (MESH_IV_UPDATE_TICK/1000/60)
/** ms to tick. */

#define IV_UPDATE_TIMEOUT (MESH_MIN_IV_UPDATE_INTERVAL_MINUTES/MESH_IV_MS_TO_MINUTES)

#define IV_RECOVERY_TIMEOUT (MESH_MIN_IV_RECOVERY_INTERVAL_MINUTES/MESH_IV_MS_TO_MINUTES)

#define IV_UPDATE_IN_PROGRESS_MAX_TIME (MESH_MAX_IV_UPDATE_INTERVAL_MINUTES/MESH_IV_MS_TO_MINUTES - MESH_IV_UPDATE_TIME_MARGIN_MINUTES/MESH_IV_MS_TO_MINUTES)


#ifndef NETWORK_SEQNUM_IV_UPDATE_START_THRESHOLD
#define NETWORK_SEQNUM_IV_UPDATE_START_THRESHOLD (NETWORK_SEQNUM_MAX / 2)
#endif

/**
 * The sequence number value that triggers the end of an IV update procedure.
 * This value should be set so that there are enough sequence numbers left for finishing any ongoing Transport SAR sessions.
 */
#ifndef NETWORK_SEQNUM_IV_UPDATE_END_THRESHOLD
#define NETWORK_SEQNUM_IV_UPDATE_END_THRESHOLD (NETWORK_SEQNUM_MAX - TRANSPORT_SAR_SEQNUM_DIFF_MAX)
#endif

#define NETWORK_IVI_MASK     (0x00000001)
/** Number of bits in the sequence number. */
#define NETWORK_SEQNUM_BITS         24

/** Maximum allowed sequence number. */
#define NETWORK_SEQNUM_MAX          ((1 << NETWORK_SEQNUM_BITS) - 1)

#define MESH_NAX_SEQNUM ( NETWORK_SEQNUM_MAX + 1)




#define NET_BEACON_CMAC_SIZE   (8) 


#define MESH_OK 0
#define MESH_FAIL 1


typedef enum
{
    /** In normal operation. */
    MESH_IV_UPDATE_NORMAL,
    /** IV update procedure in progress. */
    MESH_IV_UPDATE_IN_PROGRESS,
} mesh_iv_update_t;


typedef struct
{
    uint32_t seqnum_max_available; /**< The highest sequence number available for use. */
    uint32_t iv_index; /**< IV index. */
    struct
    {
        mesh_iv_update_t state;   /**< IV update state. */
        bool pending; /**< An IV update state change has been triggered, awaiting timer. */
        bool locked; /**< Changes to IV index or update state has been locked by an external module. */
        uint16_t timeout_counter; /**< Counter for IV update procedure timeout, in minutes. */
        uint16_t ivr_timeout_counter; /**< Counter for IV recovery procedure timeout, in minutes. */
    } iv_update;
} network_state_t;



void mesh_beacon_iv_index_set(uint32_t val);




#endif
