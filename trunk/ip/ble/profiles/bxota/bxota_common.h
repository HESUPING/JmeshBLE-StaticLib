/**
 ****************************************************************************************
 *
 * @file bxota_common.h
 *
 * @brief Header File - BlueX BLE OTA common types.
 *
 * Copyright (C) BlueX Micro 2015-2016
 *
 * 
 ****************************************************************************************
 */

#ifndef BXOTA_COMMON_H_
#define BXOTA_COMMON_H_
/**
 ****************************************************************************************
 * @addtogroup BXOTA BlueX BLE OTA Profile
 * @ingroup PROFILE
 * @brief BlueX BLE OTA Profile
 *
 * The BlueX BLE OTA Profile is used to update the software run on a server by transmitting
 * a new software binary over the air from a authenticated client.
 *
 * This file contains all definitions that are common for the server and the client parts
 * of the profile.
 *****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>


/*
 * DEFINES
 ****************************************************************************************
 */

#define BXOTA_PROGRAM_MAX_SIZE 512

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

typedef enum
{
    CODE_DATA_SECTION,
    NVDS_SECTION,
}image_section_t;
typedef enum
{
    BXOTAS_DISABLED,
    BXOTAS_IDLE,
    BXOTAS_RX_CODE_DATA,
    BXOTAS_RX_NVDS_SECTION,
    BXOTAS_OVERRIDE_BOOT_INFO
}bxotas_stat_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
 
typedef struct
{
    uint32_t total_size;
    uint32_t offset;
    image_section_t section;
}bxotas_update_req_t;
typedef struct
{
    uint32_t sw_version;
}bxotas_sw_ver_t;
typedef struct
{
    uint32_t total_image_size;
}bxotas_flash_erase_req_t;
typedef struct
{
    uint32_t update_init;
}bxotas_update_init_t;
typedef struct
{
    uint32_t override_image_size;
}bxotas_boot_override_t;

/// }@ BXOTA_COMMON

#endif // BXOTA_COMMON_H_

