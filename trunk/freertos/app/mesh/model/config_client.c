#include "osapp_config.h"
#ifdef OSAPP_MESH
//config and defines
#include <stdbool.h>
#include "sdk_mesh_config_pro.h"
#include "access.h"
#include "sig_msg.h"
#include "log.h"
#include "foundation_models.h"
#include "config_client.h"
//device manager
#include "device_keys_dm.h"
#include "network_keys_dm.h"
#include "app_keys_dm.h"
//key/iv  refresh
#include "mesh_kr_comm.h"
#include "mesh_kr_client.h"
//config messages
#include "config_relay.h"
#include "config_composition_data.h"





#define CONFIG_APPKEY_ADD_PARAM_LENGTH 19
#define CONFIG_APPKEY_ADD_MSG_LENGTH (CONFIG_APPKEY_ADD_PARAM_LENGTH + 1)
void config_appkey_add_tx(model_base_t *model,app_key_t *appkey,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(CONFIG_APPKEY_ADD_MSG_LENGTH);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    buf[0] = ONE_OCTET_OPCODE_GEN(FOUNDATION_MODELS_ONE_OCTET_OPCODE_OFFSET,Config_AppKey_Add);
    uint16_t netkey_idx = appkey->bound_netkey->global_idx;
    uint16_t appkey_idx = appkey->global_idx;
    PACK_2_KEY_IDX(buf + 1,appkey_idx,netkey_idx);
    memcpy(buf+4,appkey->key[KEY_PRIMARY].appkey,MESH_KEY_LENGTH);
    access_pdu_param_t param = {
        .model = model,
        .cb = cb,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 4,//FOR TEST
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&param);
    access_pdu_tx(ptr,false);
}

void config_appkey_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"~~config_appkey_status_rx~~\n");
    //cb_config_client_config_appkey_status_rx(elmt,model,pdu);
}
void config_model_app_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"~~config_model_app_status_rx~~\n");
    //cb_config_client_config_model_app_status_rx(elmt,model,pdu);
}


void config_model_app_bind_tx(model_base_t *model,config_model_app_bind_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(param->sig_model? 8 : 10);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_App_Bind);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    buf[2] = param->elmt_addr & 0xff;
    buf[3] = (param->elmt_addr >>  8) & 0xff;
    buf[4] = (param->appkey_idx) & 0xff;
    buf[5] = (param->appkey_idx >> 8) & 0xff;
    memcpy(&buf[6],&param->model_id,param->sig_model ? sizeof(uint16_t) : sizeof(uint32_t));
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
}


void config_model_publication_set_tx(model_base_t *model,config_model_publish_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(param->sig_model? 12 : 14);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint8_t opcode = ONE_OCTET_OPCODE_GEN(FOUNDATION_MODELS_ONE_OCTET_OPCODE_OFFSET, Config_Model_Publication_Set);
    buf[0] = opcode;
    buf[1] = param->elmt_addr;
    buf[2] = param->elmt_addr >>8;
    buf[3] = param->publish_addr;
    buf[4] = param->publish_addr >>8;
    buf[5] = param->appkey_idx;
    buf[6] = (param->appkey_idx>>8 & 0xf) | param->credential_flag<< 4;
    buf[7] = param->publish_ttl;
    buf[8] = *(uint8_t *)&param->period;
    buf[9] = *(uint8_t *)&param->retransmit;
    memcpy(&buf[10],&param->model_id,param->sig_model ? sizeof(uint16_t) : sizeof(uint32_t));
    access_pdu_param_t access_param = {
        .model = model,
        .cb = cb,
        .virt_dst = NULL,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 0,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&access_param);
    access_pdu_tx(ptr,false);
}

void config_model_publication_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"~~config_model_publication_status_rx~~\n");
}

void config_model_subscription_update_tx(model_base_t *model,config_model_subscribe_param_t *param,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    uint16_t length;
    uint16_t opcode;
    switch(param->op_mode)
    {
    case Subscription_Add:
        length = param->sig_model ? 8 : 10;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Add);
    break;
    case Subscription_Delete:
        length = param->sig_model ? 8 : 10;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Delete);
    break;
    case Subscription_Overwrite:
        length = param->sig_model ? 8 : 10;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Overwrite);
    break;
    case Subscription_Virtual_Addr_Add:
        length = param->sig_model ? 22 : 24;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Virtual_Address_Add);
    break;
    case Subscription_Virtual_Addr_Delete:
        length = param->sig_model ? 22 : 24;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Virtual_Address_Delete);
    break;
    case Subscription_Virtual_Addr_Overwrite:
        length = param->sig_model ? 22 : 24;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Virtual_Address_Overwrite);
    break;
    case Subscription_Delete_All:
        length = param->sig_model ? 6 : 8;
        opcode = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET, Config_Model_Subscription_Delete_All);
    break;
    default:
        BX_ASSERT(0);
    break;
    }
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(length);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    buf[0] = opcode >> 8 & 0xff;
    buf[1] = opcode & 0xff;
    buf[2] = param->elmt_addr & 0xff;
    buf[3] = param->elmt_addr >> 8 & 0xff;
    uint8_t i = 4;
    if(param->op_mode != Subscription_Delete_All)
    {
        if(param->subscribe_addr.is_virt)
        {
            memcpy(&buf[i],param->subscribe_addr.addr.virt->label_uuid,LABEL_UUID_SIZE);
            i += LABEL_UUID_SIZE;
        }else
        {
            memcpy(&buf[i],&param->subscribe_addr.addr.addr,sizeof(uint16_t));
            i += sizeof(uint16_t);
        }
    }
    memcpy(&buf[i],&param->model_id,param->sig_model ? 2 : 4);
    access_pdu_param_t access_param = {
        .model = model,
        .cb = cb,
        .virt_dst = NULL,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 0,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&access_param);
    access_pdu_tx(ptr,false);
}


void config_model_subscription_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"~~config_model_subscription_status_rx~~\n");
}



void config_model_two_octets_item_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t),uint8_t *payload,uint8_t length,uint16_t opcode_offset)
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(length + 2);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode  = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET,opcode_offset);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    memcpy(&buf[2],payload,length);
    access_pdu_param_t param = {
        .model = model,
        .cb = cb,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 2,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&param);
    access_pdu_tx(ptr,true);
}


void config_client_net_key_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint32_t payload_size  = pdu->base.total_length - 2 - 4;
	uint16_t dev_addr;
    LOG(LOG_LVL_INFO,"config_client_net_key_status \n");
	if(payload_size != sizeof(config_msg_netkey_status_t))
	{
		return;
	}
	config_msg_netkey_status_t *netkey_status =(config_msg_netkey_status_t *) (pdu->access + 2 );
	dev_addr = pdu->base.src_addr;
	LOG(LOG_LVL_INFO,"config_client_net_key_status done %d \n",netkey_status ->status);
	if(netkey_status ->status == Config_Success)
	{
	    config_client_kr_netkey_status_ack(netkey_status->netkey_index, dev_addr);
	}
}

 void config_key_refresh_phase_status_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint32_t payload_size  = pdu->base.total_length - 2 - 4;
	uint16_t dev_addr;
    LOG(LOG_LVL_INFO,"config_key_refresh_phase_status_rx \n");
	if(payload_size != sizeof(config_msg_key_refresh_phase_status_t))
	{
		return;
	}
	
	config_msg_key_refresh_phase_status_t *phase_status =(config_msg_key_refresh_phase_status_t *) (pdu->access + 2 );
	dev_addr = pdu->base.src_addr;
	LOG(LOG_LVL_INFO,"config_key_refresh_phase_status_rx  %d \n",phase_status ->status);
	if(phase_status->status == Config_Success)
	{
	    config_client_kr_phase_status_ack(phase_status->netkey_index, dev_addr);
	}
}



#endif

