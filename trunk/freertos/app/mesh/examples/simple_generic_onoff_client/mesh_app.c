/**
 ****************************************************************************************
 *
 * @file   mesh_app.c
 *
 * @brief  .
 *
 * @author  Hui Chen
 * @date    2018-09-25 17:20
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
//mesh platform
#include "mesh_errors.h"
#include "sdk_mesh_config.h"
#include "sdk_mesh_definitions.h"
//app
#include "mesh_app.h"
#include "mesh_app_hal.h"
//tools
#include "co_utils.h"
#include <stdbool.h>
#include "string.h"
//feature
#include "sig_msg.h"
#include "node_save.h"
//model
#include "config_client.h"

/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
/** define common server/client model*/
//define a client model
#define DEF_CLIENT_MODEL(model_type , model_name)                                               \
        static model_type              model_name;                                              \
        static app_key_t*              model_name##_bound_key_buf[APPKEY_BOUND_NETKEY_MAX_NUM];



/** Init common server/client model*/
//init a client model
#define INIT_CLIENT_MODEL(model_name , model_id , sig_model)                                \
        mesh_model_init(&model_name.model.base, model_id, sig_model,                        \
                APPKEY_BOUND_NETKEY_MAX_NUM,model_name##_bound_key_buf);

///config client application
#ifdef ENABLE_CONFIG_CLIENT

DEF_CLIENT_MODEL(generic_onoff_client_t , generic_onoff_client_0);

void mesh_app_client_init(void)
{
    //1.init model
    INIT_CLIENT_MODEL(generic_onoff_client_0, GENERIC_ONOFF_CLIENT_MODEL_ID, true);

    //2.init element
    mesh_element_init(0,&generic_onoff_client_0.model.base);
}


void user_onoff_client_set(void *msg , uint8_t msg_length,uint16_t dst_addr,uint8_t need_ack)
{
    if(need_ack)
    {
        generic_onoff_set_tx(&generic_onoff_client_0,msg,msg_length,dst_addr);
    }
    else
    {
        generic_onoff_set_unacknowledged_tx(&generic_onoff_client_0,msg,msg_length,dst_addr);
    }

}

//add app keys to onoff_client mode.called when appkey is added.
void user_init_client_model_appkeys(void)
{
    uint8_t status;
    bind_appkey_to_model(&generic_onoff_client_0.model.base , 0x0000 , &status);
}

#endif
///end of config client application


//init user models
void mesh_app_init_user(void)
{
    #ifdef ENABLE_CONFIG_CLIENT
        mesh_app_client_init();
    #endif
}


#endif /* OSAPP_MESH */
