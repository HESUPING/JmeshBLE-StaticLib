#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "sdk_mesh_config.h"
#include "config_composition_data.h"
#include "sig_msg.h"
#include "access.h"
#include "mesh_tools.h"
#include "LOG.h"
#include "mesh_env.h"
#include "mesh_core_api.h"

////////////////////////////////////////////////////////////////
////////////////          tool box          ////////////////////
////////////////////////////////////////////////////////////////


uint8_t composition_data_get_length(void)
{
    uint8_t len , i;
    mesh_elmt_t *elmt = get_mesh_elmt();
    len = 10;//CID,PID,VID,CRPL,Feature
    //every element in node
    for(i=0;i<ELEMENT_NUM;++i)
    {
        len += 4;//LOC,NumS,NumV
        struct co_list_hdr *hdr = co_list_pick(&elmt[i].model_list);
        while(hdr)
        {
            len += 2;
            hdr = co_list_next(hdr);
        }
    }
    LOG(3,"composition_data_get_length=%d\n",composition_data_get_length);
    return len;
}


void composition_data_fill_buff(uint8_t * buf , uint8_t verify_length)
{
    uint16_t features = 0;
    uint8_t i,offset,numS,numV;
    mesh_elmt_t *elmt = get_mesh_elmt();
    mesh_core_params_t param1,param2,param3,param4;//get feature

    //CID,PID,VID,CRPL
    buf[0] = (MESH_PARAM_CID  >> 0) & 0xFF;
    buf[1] = (MESH_PARAM_CID  >> 8) & 0xFF;
    buf[2] = (MESH_PARAM_PID  >> 0) & 0xFF;
    buf[3] = (MESH_PARAM_PID  >> 8) & 0xFF;
    buf[4] = (MESH_PARAM_VID  >> 0) & 0xFF;
    buf[5] = (MESH_PARAM_VID  >> 8) & 0xFF;
    buf[6] = (MESH_PARAM_CRPL >> 0) & 0xFF;
    buf[7] = (MESH_PARAM_CRPL >> 8) & 0xFF;
    //features
    mesh_core_params_get(MESH_CORE_PARAM_FEATURE_RELAY     , &param1);
    mesh_core_params_get(MESH_CORE_PARAM_FEATURE_PROXY     , &param2);
    mesh_core_params_get(MESH_CORE_PARAM_FEATURE_FRIENT    , &param3);
    mesh_core_params_get(MESH_CORE_PARAM_FEATURE_LOW_POWER , &param4);
    features |= (param1.relay     == MESH_FEATURE_NOT_SUPPORT) ? 0 : 1<<0;
    features |= (param2.proxy     == MESH_FEATURE_NOT_SUPPORT) ? 0 : 1<<1;
    features |= (param3.friend    == MESH_FEATURE_NOT_SUPPORT) ? 0 : 1<<2;
    features |= (param4.low_power == MESH_FEATURE_NOT_SUPPORT) ? 0 : 1<<3;
    buf[8] = (features >> 0) & 0xFF;
    buf[9] = (features >> 8) & 0xFF;
    //Elements
    offset = 10;
    
    //every element in node
    for(i=0;i<ELEMENT_NUM;++i)
    {
        //Calculate NumS and NumV
        numS = numV = 0;
        struct co_list_hdr *hdr = co_list_pick(&elmt[i].model_list);
        while(hdr)
        {
            //every model in element
            model_base_t *model = CONTAINER_OF(hdr, model_base_t, hdr);
            if((model->sig_model) == true ) numS ++;
            if((model->sig_model) == false) numV ++;
            hdr = co_list_next(hdr);
        }
        //Fill LOC,NumS,NumV
        buf[offset++] = (MESH_PARAM_LOC >> 0) & 0xFF;
        buf[offset++] = (MESH_PARAM_LOC >> 8) & 0xFF;
        buf[offset++] = numS;
        buf[offset++] = numV;
        //Fill SIG Models
        hdr = co_list_pick(&elmt[i].model_list);
        while(hdr)
        {
            //every model in element
            model_base_t *model = CONTAINER_OF(hdr, model_base_t, hdr);
            if((model->sig_model) == true)
            {
                buf[offset++] = (model->model_id >> 0) & 0xFF;
                buf[offset++] = (model->model_id >> 8) & 0xFF;
            }
            hdr = co_list_next(hdr);
        }
        //Fill Vendor Models
        hdr = co_list_pick(&elmt[i].model_list);
        while(hdr)
        {
            //every model in element
            model_base_t *model = CONTAINER_OF(hdr, model_base_t, hdr);
            if((model->sig_model) == false)
            {
                buf[offset++] = (model->model_id >> 0) & 0xFF;
                buf[offset++] = (model->model_id >> 8) & 0xFF;
            }
            hdr = co_list_next(hdr);
        }
    }    
    LOG(3,"verify_length=%d,offset = %d\n",verify_length,offset);
    BX_ASSERT(offset == verify_length);
}




////////////////////////////////////////////////////////////////
////////////////       config client        ////////////////////
////////////////////////////////////////////////////////////////


void config_composition_data_get_tx(model_base_t *model,uint16_t dst_addr,uint8_t page_number , void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(3);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Composition_Data_Get);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    buf[2] = page_number;
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
    LOG(3,"config_composition_data_get_tx\n");
}



void config_composition_data_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    uint8_t payload_size = pdu->base.total_length - 2 - 4; // opcode=2byte , transmic=4byte
    
    LOG(3,"config_composition_data_status_rx\n");
    log_hex_data(&pdu->access[2] , payload_size);

    //cb_config_composition_data_status_rx(elmt,model,pdu);
}





////////////////////////////////////////////////////////////////
////////////////       config server        ////////////////////
////////////////////////////////////////////////////////////////




void config_composition_data_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_composition_data_status_tx_done\n");
}

void config_composition_data_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"config_composition_data_get_rx\n");
    config_composition_data_status_tx(model , pdu->base.src_addr , 0 , config_composition_data_status_tx_done);
}


void config_composition_data_status_tx(model_base_t *model,uint16_t dst_addr,uint8_t page,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    uint8_t payload_size = composition_data_get_length();
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(payload_size + 2);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    buf[0] = ONE_OCTET_OPCODE_GEN(FOUNDATION_MODELS_ONE_OCTET_OPCODE_OFFSET,Config_Composition_Data_Status);
    buf[1] = page;
    composition_data_fill_buff(&buf[2] , payload_size);
    log_hex_data(buf , payload_size + 2);
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
    LOG(3,"config_composition_data_status_tx\n");
}



////////////////////////////////////////////////////////////////

#endif

