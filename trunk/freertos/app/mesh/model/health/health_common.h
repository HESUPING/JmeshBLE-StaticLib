#ifndef HEALTH_COMMON__H
#define HEALTH_COMMON__H
#include <stdint.h>

/** Model ID for the Health Server model. */
#define HEALTH_SERVER_MODEL_ID                              0x0002
/** Model ID for the Health Client model. */
#define HEALTH_CLIENT_MODEL_ID                              0x0003

/**
 * @defgroup HEALTH_MESSAGES Health model message definitions
 * @ingroup HEALTH_MODEL
 * Definitions of the various messages supported by the health model.
 * @{
 */

/*lint -align_max(push) -align_max(1) */

/** Health Fault Status message format. */
typedef struct 
{
    uint8_t  test_id;       /**< Test ID for the most recently run test */
    uint16_t company_id;    /**< Company identifier for the health model. */
    uint8_t  fault_array[]; /**< Fault array. */
}__attribute((packed)) health_msg_fault_status_t;

/** Health Period Status message format. */
typedef struct
{
    uint8_t fast_period_divisor; /**< Current fast period divisor. Permitted values are 0 - 15. */
}  __attribute((packed))health_msg_period_status_t;

/** Health Attention Status message format. */
typedef struct 
{
    uint8_t attention; /**< Current attention timer value, in seconds. */
}__attribute((packed)) health_msg_attention_status_t;

/** Health Fault Get message format. */
typedef struct  
{
    uint16_t company_id; /**< Company ID. */
}__attribute((packed)) health_msg_fault_get_t;

/** Health Fault Clear message format. */
typedef struct  
{
    uint16_t company_id; /**< Company ID. */
} __attribute((packed))health_msg_fault_clear_t;

/** Health Fault Test message format. */
typedef struct  
{
    uint8_t  test_id;    /**< Test ID. */
    uint16_t company_id; /**< Company ID. */
} __attribute((packed)) health_msg_fault_test_t;

/** Health Period Set message format. */
typedef struct  
{
    uint8_t fast_period_divisor; /**< Fast period divisor. Permitted values are 0 - 15. */
} __attribute((packed)) health_msg_period_set_t;

/** Health Attention Set message format. */
typedef struct  
{
    uint8_t attention; /**< Attention timer value, in seconds. */
} __attribute((packed)) health_msg_attention_set_t;

/*lint -align_max(pop) */
#endif


