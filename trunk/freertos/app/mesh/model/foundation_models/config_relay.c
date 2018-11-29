/*
 * config_relay.c
 *
 *  Created on: 2018-7-27
 *      Author: jiachuang
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "sdk_mesh_config.h"
#include "config_relay.h"
#include "sig_msg.h"
#include "access.h"
#include "LOG.h"
#include "config_server.h"
#include "mesh_env.h"
#include "mesh_core_api.h"

////////////////////////////////////////////////////////////////
////////////////          tool box          ////////////////////
////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////
////////////////       config client        ////////////////////
////////////////////////////////////////////////////////////////





void config_relay_get_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(2);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Relay_Get);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    access_pdu_param_t access_param = {
        .model = model,
        .cb = cb,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 0,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&access_param);
    access_pdu_tx(ptr,false);
    LOG(3,"config_relay_get_tx\n");
}

void config_relay_set_tx(model_base_t *model,config_relay_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(4);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Relay_Set);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    memcpy(&buf[2] , param , 2);
    access_pdu_param_t access_param = {
        .model = model,
        .cb = cb,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 0,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&access_param);
    access_pdu_tx(ptr,false);
    LOG(3,"config_relay_set_tx\n");
}


void config_relay_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    config_relay_param_t param;
    memcpy(&param , &pdu->access[2] , 2);
    LOG(3,"config_relay_status_rx\n");
    LOG(3,"Relay=0x%x,RelayRetransmitCount=0x%x,RelayRetransmitIntervalSteps=0x%x\n",param.relay,param.retransmit.count,param.retransmit.interval_steps);
    //cb_config_relay_status_rx(elmt,model,pdu);
}







////////////////////////////////////////////////////////////////
////////////////       config server        ////////////////////
////////////////////////////////////////////////////////////////




void config_relay_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_relay_status_tx_done\n");
}

void config_relay_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    config_relay_param_t param;
    //get feature
    mesh_core_params_t param_feature_relay , param_property_relay_transmit;
    mesh_core_params_get(MESH_CORE_PARAM_FEATURE_RELAY           , &param_feature_relay);
    mesh_core_params_get(MESH_CORE_PARAM_PROPERTY_RELAY_TRANSMIT , &param_property_relay_transmit);
    //set value
    param.relay      = param_feature_relay.relay;
    param.retransmit = param_property_relay_transmit.relay_transmit;
    config_relay_status_tx(model , &param , pdu->base.src_addr , config_relay_status_tx_done);
    LOG(3,"config_relay_get_rx\n");
}

void config_relay_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    config_relay_param_t param;
    mesh_core_params_t param_core_relay , param_core_transmit;
    memcpy(&param , &pdu->access[2] , 2);
    //set to core
    param_core_relay.relay              = param.relay;
    param_core_transmit.relay_transmit  = param.retransmit;
    mesh_core_params_set(MESH_CORE_PARAM_FEATURE_RELAY           , &param_core_relay);
    mesh_core_params_set(MESH_CORE_PARAM_PROPERTY_RELAY_TRANSMIT , &param_core_transmit);
    //send status message
    config_relay_status_tx(model , &param , pdu->base.src_addr , config_relay_status_tx_done);
    LOG(3,"config_relay_set_rx\n");
    //user callback
    config_server_evt_act(CONFIG_SERVER_EVT_RELAY_SET,elmt , model , pdu);
}

void config_relay_status_tx(model_base_t *model,config_relay_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(4);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Relay_Status);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    memcpy(&buf[2] , param , 2);
    access_pdu_param_t access_param = {
        .model = model,
        .cb = cb,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 0,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&access_param);
    access_pdu_tx(ptr,false);
    LOG(3,"config_relay_status_tx\n");
}



////////////////////////////////////////////////////////////////

#endif


