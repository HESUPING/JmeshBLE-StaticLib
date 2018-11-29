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
#include "config_server_events_api.h"
#include "model_servers_events_api.h"
#include "config_server.h"
#include "generic_onoff_server.h"

/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
/** define common server/client model*/
//define a server  model
#define DEF_SERVER_MODEL(model_type , model_name)                                                  \
        static mesh_addr_t             model_name##_subscription_list[MODEL_SUNSCRIPTION_LENGTH];  \
        static model_publish_state_t   model_name##_publish_state;                                 \
        static model_type              model_name;                                                 \
        static app_key_t*              model_name##_bound_key_buf[APPKEY_BOUND_NETKEY_MAX_NUM];



/** Init common server/client model*/
//init a server model
#define INIT_SERVER_MODEL(model_name , model_id , sig_model , callback)                     \
        mesh_model_init(&model_name.model.base, model_id, sig_model,                        \
                APPKEY_BOUND_NETKEY_MAX_NUM,model_name##_bound_key_buf);                    \
        model_publish_subscribe_bind(&model_name.model.base , &model_name##_publish_state,  \
                model_name##_subscription_list, ARRAY_LEN(model_name##_subscription_list)); \
        model_name.cb = callback;


///config server application
#ifdef ENABLE_CONFIG_SERVER

DEF_SERVER_MODEL(generic_onoff_server_t , generic_onoff_server_0);
DEF_SERVER_MODEL(generic_onoff_server_t , generic_onoff_server_1);


void user_onoff_0_evt_cb(const mesh_model_evt_t * p_evt)
{
    switch(p_evt->type)
    {
        case ONOFF_MODEL_EVT_SET:
            LOG(LOG_LVL_INFO,"!!!LED1=%d!!!\n",p_evt->params.onoff_set.target_state);
            hal_set_led1(p_evt->params.onoff_set.target_state);
            break;
        case ONOFF_MODEL_EVT_GET:
            LOG(LOG_LVL_INFO,"ONOFF_MODEL_EVT_GET!!!\n");
            break;
        default:
            LOG(LOG_LVL_INFO,"EVT NOT FOUND!!!\n");
            break;
    }
}
void user_onoff_1_evt_cb(const mesh_model_evt_t * p_evt)
{
    switch(p_evt->type)
    {
        case ONOFF_MODEL_EVT_SET:
            LOG(LOG_LVL_INFO,"!!!LED2=%d!!!\n",p_evt->params.onoff_set.target_state);
            hal_set_led2(p_evt->params.onoff_set.target_state);
            break;
        case ONOFF_MODEL_EVT_GET:
            LOG(LOG_LVL_INFO,"ONOFF_MODEL_EVT_GET!!!\n");
            break;
        default:
            LOG(LOG_LVL_INFO,"EVT NOT FOUND!!!\n");
            break;
    }
}

void user_config_server_evt_cb(const config_server_evt_t * p_evt)
{
    LOG(LOG_LVL_INFO , "user_config_server_evt_cb=%d\n",p_evt->type);
}



void mesh_app_server_init(void)
{
    //1.init model
    INIT_SERVER_MODEL(generic_onoff_server_0,GENERIC_ONOFF_SERVER_MODEL_ID,true,user_onoff_0_evt_cb);
    INIT_SERVER_MODEL(generic_onoff_server_1,GENERIC_ONOFF_SERVER_MODEL_ID,true,user_onoff_1_evt_cb);

    //2.init element
    mesh_element_init(0,&generic_onoff_server_0.model.base);
    mesh_element_init(1,&generic_onoff_server_1.model.base);

    //3.set initial state
    generic_onoff_server_0.message_format.present_onoff = 1;
    generic_onoff_server_1.message_format.present_onoff = 1;

    //4.Register config server event callbacks
    regisite_config_server_evt_cb(user_config_server_evt_cb);
}

#endif
///end of config server application


//TODO:THIS IS ONLY USED　FIX WARNINGS !!
void user_onoff_client_set(void *msg , uint8_t msg_length,uint16_t dst_addr,uint8_t need_ack)
{

}


//init user models
void mesh_app_init_user(void)
{
    #ifdef ENABLE_CONFIG_SERVER
        mesh_app_server_init();
    #endif
}


#endif /* OSAPP_MESH */
