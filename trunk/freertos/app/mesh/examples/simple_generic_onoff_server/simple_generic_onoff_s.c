/**
 ****************************************************************************************
 *
 * @file   simple_generic_onoff_s.c
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-25 16:18
 * @version <0.0.0.1>
 *
 * @license 
 *              Copyright (C) BlueX Microelectronics 2018
 *                         ALL Right Reserved.
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH

#include "simple_generic_onoff_s.h"
#include "mesh_app_hal.h"
#include "provision_api.h"
#include "mesh_core_api.h"
#include "gap.h"
/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
// user private key
#define  USER_UNPROV_PRIVATE_KEY        0x52,0x9a,0xa0,0x67,0x0d,0x72,0xcd,0x64,0x97,0x50,0x2e,0xd4,0x73,0x50,0x2b,0x03,\
                                        0x7e,0x88,0x03,0xb5,0xc6,0x08,0x29,0xa5,0xa3,0xca,0xa2,0x19,0x50,0x55,0x30,0xba
#define  USER_UNPROV_STATIC_AUTH_VAL    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff

#define  USER_UNPROV_CAPABILITIES_ALGORITHMS  0x0001

#define  USER_UNPROV_BEACON_UUID        0x70,0xCF,0x7C,0x97,0x32,0xA3,0x45,0xB6,0x91,0x49,0x48,0x10,0xD2,0xE9,0xCB,0xF4
#define  USER_UNPROV_BEACON_URL         0xD97478B3
#define  USER_UNPROV_BEACON_OOB         0x4020
/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */




/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static unprov_user_data_t m_unprov_user=
{
        .unprov_private_key = {USER_UNPROV_PRIVATE_KEY},
        .static_value = {USER_UNPROV_STATIC_AUTH_VAL},
        .dev_capabilities =
        {
            .algorithms = USER_UNPROV_CAPABILITIES_ALGORITHMS,
            .output_oob_action = 0,
            .input_oob_action = 0,
            .elements_num = ELEMENT_NUM,
            .public_key_type = 0,
            .static_oob_type = 0,
            .output_oob_size = 0,
            .input_oob_size = 0,
        },
        .beacon =
        {
            .dev_uuid = {USER_UNPROV_BEACON_UUID},
            .uri_hash = USER_UNPROV_BEACON_URL,
            .oob_info = USER_UNPROV_BEACON_OOB,
        }
};
/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
static void mesh_unprov_evt_cb(mesh_prov_evt_type_t type , mesh_prov_evt_param_t param);
static void user_role_init(void);
static void unprov_data_init(void);

/* user init*/
void simple_generic_onff_server_init(void)
{
    //hal init
    hal_init_leds();
    hal_init_buttons();
    //role init
    user_role_init();
    hal_heartbeat_init();

}

static void user_role_init(void)
{
    //1.role init
    provision_init(MESH_ROLE_UNPROV_DEVICE,mesh_unprov_evt_cb);
    //2. data init
    unprov_data_init();
}

static void unprov_data_init(void)
{
    volatile mesh_prov_evt_param_t evt_param;

    uint8_t  bd_addr[GAP_BD_ADDR_LEN];

    //get bd_addr
    mesh_core_params_t core_param;
    core_param.mac_address = bd_addr;
    mesh_core_params_get(MESH_CORE_PARAM_MAC_ADDRESS,&core_param);

    //1. Method of configuring network access
    evt_param.unprov.method = PROVISION_BY_GATT;
    provision_config(UNPROV_SET_PROVISION_METHOD,evt_param);
    //2. private key
    memcpy(m_unprov_user.unprov_private_key,bd_addr,GAP_BD_ADDR_LEN);
    evt_param.unprov.p_unprov_private_key = m_unprov_user.unprov_private_key;
    provision_config(UNPROV_SET_PRIVATE_KEY,evt_param);
    //3.static auth value
    evt_param.unprov.p_static_val = m_unprov_user.static_value;
    provision_config(UNPROV_SET_AUTH_STATIC,evt_param);
    //4.dev_capabilities
    evt_param.unprov.p_dev_capabilities = &m_unprov_user.dev_capabilities;
    provision_config(UNPROV_SET_OOB_CAPS,evt_param);
    //5.adv beacon
    memcpy(m_unprov_user.beacon.dev_uuid,bd_addr,GAP_BD_ADDR_LEN);
    evt_param.unprov.p_beacon = &m_unprov_user.beacon;
    provision_config(UNPROV_SET_BEACON,evt_param);
}


/* unprovision device event callback function */
static void mesh_unprov_evt_cb(mesh_prov_evt_type_t type , mesh_prov_evt_param_t param)
{
    LOG(LOG_LVL_INFO,"mesh_unprov_evt_cb type : %d\n",type);

    switch(type)
    {
        case  UNPROV_EVT_INVITE_MAKE_ATTENTION : //(NO ACTION)
        {
            //m_unprov_user.attention_duration = param.unprov.attention_duration;
        }
        break;
        case  UNPROV_EVT_EXPOSE_PUBLIC_KEY :  //(NO ACTION)
        {

        }
        break;
        case  UNPROV_EVT_AUTH_INPUT_NUMBER : //alert input dialog
        {

        }
        break;
        case  UNPROV_EVT_AUTH_DISPLAY_NUMBER : //unprov_device expose random number //(NO ACTION)
        {

        }
        break;
        case  UNPROV_EVT_PROVISION_DONE :  //(NO ACTION)
        {

        }
        break;
        default:break;
    }
}


#endif /* OSAPP_MESH */
