#include "osapp_config.h"
#ifdef OSAPP_MESH
//config and defines
#include <string.h>
#include "mesh_definitions.h"
#include "sdk_mesh_config.h"
#include "model_servers_events_api.h"
#include "foundation_models.h"
#include "access.h"
#include "sig_msg.h"
#include "device_manager_api.h"
#include "provision_base.h"
//features
#include "node_save.h"
//config server/client
#include "config_server.h"
#include "config_client.h"
//device manager
#include "device_keys_dm.h"
#include "network_keys_dm.h"
#include "app_keys_dm.h"
//key/iv  refresh
#include "mesh_kr_comm.h"
#include "mesh_kr_server.h"
#include "mesh_iv_operation.h"
#include "mesh_iv_operation_ex.h"
//config messages
#include "config_relay.h"
#include "config_composition_data.h"
//gatt
#include "mesh_gatt.h"
#include "provisioning_s.h"
#include "proxy_s.h"



/*
 * DEFINES
 ****************************************************************************************
 */
#define CONFIG_APPKEY_STATUS_PARAM_LENGTH 4

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    uint8_t devkey[MESH_KEY_LENGTH];
    dm_async_cb_t network_keys_generation_done_cb;
}config_server_owndata_t;
config_server_owndata_t m_server;


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */
static void config_server_network_keys_generation_done_cb(void* handle);
static void server_generate_device_key_by_ecdh_and_salt(void);
static void server_dev_key_gen_done(void);


/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static config_server_evt_cb_t   mesh_config_server_evt_cb;






/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 * @brief     Call config server action function
 * @param[in] type  Type of event.
 * @param[in] elmt  event parameters element.
 * @param[in] model event parameters model.
 * @param[in] pdu   event parameters contents.
 * @return    void
 */
void config_server_evt_act(config_server_evt_type_t type, mesh_elmt_t *elmt,  model_base_t  *model,  access_pdu_rx_t *pdu)
{
    config_server_evt_t evt={type , elmt , model , pdu};
    if(mesh_config_server_evt_cb)
    {
        mesh_config_server_evt_cb(&evt);
    }
}

/**
 * @brief     set config server event callback function.
 * @param[in] cb callback of config server.
 */
void regisite_config_server_evt_cb(config_server_evt_cb_t cb)
{
    mesh_config_server_evt_cb = cb;
}



static void config_model_two_octets_status_response_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t),uint8_t *payload,uint8_t length,uint16_t opcode_offset)
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

static void config_netkey_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_netkey_status_tx_done %d\n", status);
}


void config_server_add_netkey(uint8_t *netkey,uint16_t netkey_idx,uint8_t *status,dm_async_cb_t cb)
{
    err_t err;
    dm_netkey_handle_t l_handle;

    m_server.network_keys_generation_done_cb = cb;

    err = dm_netkey_add(netkey_idx,netkey,&l_handle,config_server_network_keys_generation_done_cb);
    if(MESH_CORE_SUCCESS == err)
    {
        *status = Config_Success;
        // TODO flash 
       // node_save_config_server_net_key(ptr,netkey_buf,save_keybuf_index);
    }else
    {
        *status = err;
    }
}



void config_server_update_netkey_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
     uint32_t payload_size  = pdu->base.total_length - 2 - 4;
     err_t status;
     config_msg_netkey_status_t netkey_status;
     if(payload_size != sizeof(config_msg_netkey_add_update_t))
     {
         return;
     }
     LOG(3,"config_server_update_netkey\n");
     config_msg_netkey_add_update_t *kr_netkey_set =(config_msg_netkey_add_update_t *) (pdu->access + 2 );
     status = mesh_kr_config_netkey_update(kr_netkey_set->netkey_index,kr_netkey_set->netkey);
     if(status != MESH_CORE_SUCCESS)
     {
         netkey_status.status = Invalid_NetKey_Index;
     }
     else 
     {
        netkey_status.status = Config_Success;
     }
     netkey_status.netkey_index = kr_netkey_set->netkey_index;
     config_model_two_octets_status_response_tx(model,pdu->base.src_addr,config_netkey_status_tx_done,(uint8_t *)&netkey_status,sizeof(config_msg_netkey_status_t),Config_NetKey_Status);
     //user callback
     config_server_evt_act(CONFIG_SERVER_EVT_NETKEY_UPDATE , elmt , model , pdu);
}


void handle_config_key_refresh_phase_get_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint32_t payload_size  = pdu->base.total_length - 2 - 4;
	err_t status;
	config_msg_key_refresh_phase_status_t phase_status;
	if(payload_size != sizeof(config_msg_key_refresh_phase_get_t))
	{
		return;
	}
	config_msg_key_refresh_phase_get_t *kr_phase_get =(config_msg_key_refresh_phase_get_t *) (pdu->access + 2 );
    mesh_key_refresh_phase_t kr_phase;
	status = mesh_kr_config_get_phase(kr_phase_get->netkey_index,&kr_phase);
     if(status != MESH_CORE_SUCCESS)
     {
         phase_status.status = Invalid_NetKey_Index;
     }
     else 
     {
        phase_status.status = Config_Success;
     }
     phase_status.netkey_index = kr_phase_get->netkey_index;
     phase_status.phase =  kr_phase;
     config_model_two_octets_status_response_tx(model,pdu->base.src_addr,config_netkey_status_tx_done,(uint8_t *)&phase_status,sizeof(config_msg_key_refresh_phase_status_t),Config_Key_Refresh_Phase_Status);
}

 void handle_config_key_refresh_phase_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
	uint32_t payload_size  = pdu->base.total_length - 2 - 4;
	err_t status;
	config_msg_key_refresh_phase_status_t phase_status;
	if(payload_size != sizeof(config_msg_key_refresh_phase_set_t))
	{
		return;
	}
    config_msg_key_refresh_phase_set_t *kr_phase_set =(config_msg_key_refresh_phase_set_t *) (pdu->access + 2 );
    mesh_key_refresh_transition_t trans =(mesh_key_refresh_transition_t) kr_phase_set->transition;
    status = mesh_kr_config_netkey_phase(kr_phase_set->netkey_index,trans);
    mesh_key_refresh_phase_t kr_phase;
	status = mesh_kr_config_get_phase(kr_phase_set->netkey_index,&kr_phase);
    if(status != MESH_CORE_SUCCESS)
    {
        phase_status.status = Invalid_NetKey_Index;
    }
    else 
    {
        phase_status.status = Config_Success;
    }
    phase_status.netkey_index = kr_phase_set->netkey_index;
    phase_status.phase = kr_phase;
    config_model_two_octets_status_response_tx(model,pdu->base.src_addr,config_netkey_status_tx_done,(uint8_t *)&phase_status,sizeof(config_msg_key_refresh_phase_status_t),Config_Key_Refresh_Phase_Status);
    //user callback
    config_server_evt_act(CONFIG_SERVER_EVT_KEY_REFRESH_PHASE_SET , elmt , model , pdu);
}

//TODO
net_key_t *get_netkey_by_global_idx(net_key_t *netkey,uint8_t key_buf_size,uint16_t idx)
{
    uint8_t i;
    for(i = 0; i<key_buf_size;++i)
    {
        if(netkey[i].global_idx == idx)
        {
            return &netkey[i];
        }
    }
    return NULL;
}

static void config_appkey_add_rx_aid_done(void* dm_handle)
{
    LOG(3,"config_appkey_add_rx_aid_done\n");
}




void config_appkey_status_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t),uint8_t *payload,uint8_t length)
{
    config_model_two_octets_status_response_tx(model,dst_addr,cb,payload,length,Config_AppKey_Status);
}

static void config_appkey_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_appkey_status_tx_done\n");
}

void config_appkey_add_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    uint16_t netkey_idx;
    uint16_t appkey_idx;
    dm_netkey_handle_t netkey_handle;
    dm_appkey_handle_t appkey_handle;
    FETCH_2_KEY_IDX(&pdu->access[1],&appkey_idx,&netkey_idx);
    LOG(3,"netkey_idx=0x%x,appkey_idx=0x%x\n",netkey_idx,appkey_idx);
    err_t status;
    
    status = dm_netkey_index_to_netkey_handle(netkey_idx,&netkey_handle);
    if(status != MESH_CORE_SUCCESS)
    {
        status = Invalid_NetKey_Index;
    }else
    {
        status = dm_appkey_match(appkey_idx,&pdu->access[4]);
        if(status != MESH_CORE_SUCCESS)
        {
            status = dm_appkey_add(appkey_idx,&pdu->access[4],&appkey_handle,config_appkey_add_rx_aid_done);
            if(status == MESH_CORE_SUCCESS)
            {
                status = Config_Success;
                //TODO
                //node_save_config_server_app_key(ptr,buf,save_keybuf_index);
               // LOG(3,"Config_Success\nbuf=0x%x,netkey=0x%x\n",buf,netkey);
            }else
            {
                status = Insufficient_Resources;
                LOG(3,"Insufficient_Resources\n");
            }
        }
    }
    uint8_t resp_buf[CONFIG_APPKEY_STATUS_PARAM_LENGTH];
    resp_buf[0] = status;
    memcpy(resp_buf + 1,&pdu->access[1],3);
    config_appkey_status_tx(model,pdu->base.src_addr,config_appkey_status_tx_done,resp_buf,CONFIG_APPKEY_STATUS_PARAM_LENGTH);
    LOG(3,"config_appkey_add_rx->config_appkey_status_tx\n");
    //user callback
    config_server_evt_act(CONFIG_SERVER_EVT_APPKEY_ADD , elmt , model , pdu);
}

void config_appkey_update_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    uint16_t netkey_idx;
    uint16_t appkey_idx;
    dm_netkey_handle_t netkey_handle;
    dm_appkey_handle_t appkey_handle;
    mesh_key_refresh_phase_t phase;
    FETCH_2_KEY_IDX(&pdu->access[1],&appkey_idx,&netkey_idx);
    LOG(3,"netkey_idx=0x%x,appkey_idx=0x%x\n",netkey_idx,appkey_idx);
    err_t status;
    status = dm_netkey_index_to_netkey_handle(netkey_idx,&netkey_handle);
    if(status != MESH_CORE_SUCCESS)
    {
        status = Invalid_NetKey_Index;
    }else
    {
        dm_netkey_kr_phase_get(netkey_handle,&phase);
        if(phase == MESH_KEY_REFRESH_PHASE_1)
        {
             if(MESH_CORE_SUCCESS !=dm_appkey_index_to_appkey_handle(appkey_idx,&appkey_handle))
             {
			     status = Cannot_Update;
             }
             else
             {
                 dm_appkey_update(appkey_handle,&pdu->access[4],config_appkey_add_rx_aid_done);
                 status = Config_Success;
             }
        }
        else
        {
            status = Cannot_Update;
        }
    }
    uint8_t resp_buf[CONFIG_APPKEY_STATUS_PARAM_LENGTH];
    resp_buf[0] = status;
    memcpy(resp_buf + 1,&pdu->access[1],3);
    config_appkey_status_tx(model,pdu->base.src_addr,config_appkey_status_tx_done,resp_buf,CONFIG_APPKEY_STATUS_PARAM_LENGTH);
    LOG(3,"config_appkey_add_rx->config_appkey_status_tx\n");
    //user callback
    config_server_evt_act(CONFIG_SERVER_EVT_APPKEY_UPDATE , elmt , model , pdu);
}



uint8_t config_model_subscription_add(mesh_elmt_t *elmt,model_base_t *model,uint16_t addr)
{
    if(model->subscription_list == NULL)
    {
        return Not_a_Subscribe_Model;
    }
    uint8_t i;
    for(i=0;i<model->subscription_list_size;++i)
    {
        if(IS_MESH_ADDR_STRUCT_VALID(&model->subscription_list[i]) == false)
        {
            model->subscription_list[i].addr.addr = addr;
            model->subscription_list[i].is_virt = false;
            node_save_subscription_list(model , i);
            break;
        }
    }
    if(i == model->subscription_list_size)
    {
        return Insufficient_Resources;
    }else
    {
        return Config_Success;
    }
}


void config_model_subscription_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_model_subscription_status_tx\n");
}

void config_model_subscription_status_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t),uint8_t *payload,uint8_t length)
{
    config_model_two_octets_status_response_tx(model,dst_addr,cb,payload,length,Config_Model_Subscription_Status);
}

void config_model_subscription_update_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    uint16_t elmt_addr;
    uint16_t subscribe_addr;
    memcpy(&elmt_addr,&pdu->access[2],2);
    memcpy(&subscribe_addr,&pdu->access[4],2);
    bool sig_model;
    uint32_t model_id;

    if(pdu->base.total_length == 10)
    {
        sig_model = false;
        memcpy(&model_id,&pdu->access[6],4);
    }else
    {
        sig_model = true;
        model_id= pdu->access[6] | (pdu->access[7]<<8);
    }
    uint16_t opcode = pdu->access[0] << 8 | pdu->access[1];
    uint8_t status;
    do
    {
        mesh_elmt_t *dst_elmt = get_elmt_by_uni_addr(elmt_addr);
        if(dst_elmt == NULL)
        {
            status = Invalid_Address;
            break;
        }
        model_base_t *dst_model = get_model_inst_from_elmt(dst_elmt, model_id, sig_model);
        if(dst_model == NULL)
        {
            status = Invalid_Model;
            break;
        }
        switch(opcode & 0x3fff)
        {
            case Config_Model_Subscription_Add:
                status = config_model_subscription_add(dst_elmt,dst_model,subscribe_addr);
                //user callback
                config_server_evt_act(CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_ADD,elmt , model , pdu);
                break;
            case Config_Model_Subscription_Delete:
                //user callback
                config_server_evt_act(CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_DELETE,elmt , model , pdu);
                break;
            case Config_Model_Subscription_Overwrite:
                //user callback
                config_server_evt_act(CONFIG_SERVER_EVT_MODEL_SUBSCRIPTION_OVERWRITE,elmt , model , pdu);
                break;
            default:
                BX_ASSERT(0);
                break;
        }
    }while (0);
    uint8_t resp_buf[9];
    resp_buf[0] = status;
    memcpy(&resp_buf[1],&pdu->access[2],sig_model ? 6 : 8);
    config_model_subscription_status_tx(model,pdu->base.src_addr,config_model_subscription_status_tx_done,resp_buf,sig_model?7:9);
}



app_key_t **alloc_bound_appkey_buf(app_key_t **buf,uint8_t size,uint8_t *save_keybuf_index)
{
    uint8_t i;
    for(i =0 ;i<size;++i)
    {
        if(buf[i]== NULL)
        {
            *save_keybuf_index = i;
            return &buf[i];
        }
    }
    return NULL;
}



bool appkey_is_bound(app_key_t **buf,uint8_t size,app_key_t *appkey)
{
    uint8_t i;
    for(i =0 ;i<size;++i)
    {
        if(buf[i]== appkey)
        {
             return true;
        }
    }
    return false;
}





void config_model_app_status_tx(model_base_t *model,uint8_t status,uint8_t *data,uint8_t size,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t))
{
    access_pdu_tx_t *ptr= alloc_access_tx_pdu(size + 3);
    if(ptr == NULL) return;
    uint8_t *buf = access_tx_pdu_get_data_buf(ptr);
    uint16_t opcode  = TWO_OCTETS_OPCODE_GEN(FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET,Config_Model_App_Status);
    buf[0] = (opcode >> 8) & 0xff;
    buf[1] = opcode & 0xff;
    buf[2] = status;
    memcpy(buf + 3,data,size);
    access_pdu_param_t param = {
        .model = model,
        .cb = cb,
        .src_addr = model->elmt->uni_addr,
        .dst_addr = dst_addr,
        .ttl = 0,
        .szmic = 0,
        .seg = 0,
    };
    access_tx_pdu_set(ptr,&param);
    access_pdu_tx(ptr,true);
    
}

void config_model_app_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_model_app_status_tx_done\n");
}


void config_model_app_bind_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    LOG(3,"config_model_app_bind_rx\n");
    config_server_model_t *ptr = GET_SERVER_MODEL_PTR(config_server_model_t,model);
    uint16_t elmt_addr;
    uint16_t appkey_idx;
    memcpy(&elmt_addr,&pdu->access[2],2);
    memcpy(&appkey_idx,&pdu->access[4],2);
    mesh_elmt_t *dst_elmt = get_elmt_by_uni_addr(elmt_addr);
    LOG(3,"dst_elmt=0x%x\n",dst_elmt);
    uint32_t model_id = 0;
    bool sig_model;
    if((pdu->access[0] & 0xc0)!=0xc0)
    {
        sig_model = true;
        model_id = pdu->access[6] + pdu->access[7]<<8;
    }else if(pdu->base.total_length == 10)
    {
        sig_model = false;
        model_id = pdu->access[6] + pdu->access[7]<<8 + pdu->access[8]<<16 + pdu->access[9]<<24;
    }else
    {
        LOG(LOG_LVL_WARN,"model app bind length error\n");
    }
    LOG(3,"model_id=0x%x\n",model_id);
    uint8_t status;
    model_base_t *dst_model = get_model_inst_from_elmt(dst_elmt, model_id, sig_model);
    LOG(3,"dst_model=0x%x\n",dst_model);
    if(dst_model)
    {
        LOG(3,"config_model_app_bind_rx:bind_appkey_to_model\n");
        bind_appkey_to_model(dst_model,appkey_idx,&status);
    }else
    {
        status = Invalid_Model;
        LOG(3,"config_model_app_bind_rx:Invalid_Model\n");
    }
    config_model_app_status_tx(model,status,&pdu->access[2],sig_model?6:8,pdu->base.src_addr,config_model_app_status_tx_done);
    LOG(3,"config_model_app_status_tx\n");
    //user callback
    config_server_evt_act(CONFIG_SERVER_EVT_MODEL_APP_BIND,elmt , model , pdu);
}


void config_model_publication_status_tx(model_base_t *model,uint16_t dst_addr,void (*cb)(access_pdu_tx_t *,uint8_t),uint8_t *payload,uint8_t length)
{
    config_model_two_octets_status_response_tx(model,dst_addr,cb,payload,length,Config_Model_Publication_Status);
}

void config_model_publication_status_tx_done(access_pdu_tx_t *ptr,uint8_t status)
{
    LOG(3,"config_model_publication_status_tx_done\n");

}

void config_model_publication_set_rx(mesh_elmt_t *elmt,model_base_t *model,access_pdu_rx_t *pdu)
{
    uint32_t model_id = 0;
    uint16_t elmt_addr;
    uint16_t publish_addr;
    uint16_t appkey_idx;
    uint8_t credential_flag;
    dm_appkey_handle_t appkey_handle;
    
    memcpy(&elmt_addr,&pdu->access[1],2);
    memcpy(&model_id,&pdu->access[10],model->sig_model ? sizeof(uint16_t) : sizeof(uint32_t));
    bool sig_model = pdu->base.total_length == 16 ? true : false;
    uint8_t status;
    do
    {
        mesh_elmt_t *dst_elmt = get_elmt_by_uni_addr(elmt_addr);
        if(dst_elmt == NULL)
        {
            status = Invalid_Address;
            LOG(3,"config_model_publication_status_tx_Invalid_Address\n");
            break;
        }
        model_base_t *dst_model = get_model_inst_from_elmt(dst_elmt,model_id,sig_model);
        if(dst_model == NULL)
        {
            status = Invalid_Model;
            LOG(3,"config_model_publication_status_tx_Invalid_Model\n");
            break;
        }
        if(dst_model->publish == NULL)
        {
            status = Invalid_Publish_Parameters;
            LOG(3,"config_model_publication_status_tx_Invalid_Publish_Parameters\n");
            break;
        }
        memcpy(&appkey_idx,&pdu->access[5],sizeof(uint16_t));
        appkey_idx &= 0xfff;
        if(dm_appkey_find(appkey_idx,&appkey_handle)!=MESH_CORE_SUCCESS)
        {
        
		    LOG(3,"config_model_publication_status_tx_Invalid_AppKey_Index\n");
            status = Invalid_AppKey_Index;
            break;
        }
        dst_model->publish->appkey_idx = appkey_idx;
        dst_model->publish->addr.is_virt = false;
        memcpy(&publish_addr,&pdu->access[3],2);
        dst_model->publish->addr.addr.addr = publish_addr;
        credential_flag = pdu->access[6]>>4 & 0x1;
        dst_model->publish->credential_flag = credential_flag;
        dst_model->publish->ttl = pdu->access[7];
        dst_model->publish->period = *(publish_period_t *)&pdu->access[8];
        dst_model->publish->retransmit = *(transmit_state_t *)&pdu->access[9];      
		LOG(3,"config_model_publication_status_tx_Config_Success\n");
        status = Config_Success;
    }while (0);
    uint8_t resp_buf[14];
    resp_buf[0] = status;
    memcpy(&resp_buf[1],&elmt_addr,sizeof(uint16_t));
    memcpy(&resp_buf[10],&model_id,sig_model ? sizeof(uint16_t) : sizeof(uint32_t));
    if(status != Config_Success)
    {
        memset(&resp_buf[3],0,7);
    }else
    {
        memcpy(&resp_buf[3],&pdu->access[3],7);
    }
    config_model_publication_status_tx(model,pdu->base.src_addr,config_model_publication_status_tx_done,resp_buf,sig_model ? 12 : 14);
    //user callback
    config_server_evt_act(CONFIG_SERVER_EVT_MODEL_PUBLICATION_VIRTUAL_ADDRESS_SET,elmt , model , pdu);
}

/**
 ****************************************************************************************
 * @brief  config server get network key list.
 *
 * @return Pointer to the net key list data.
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief  config server network keys generation done cb.
 *
 * @param[out] p_list  Pointer to the net key list data.
 *
 ****************************************************************************************
 */
static void config_server_network_keys_generation_done_cb(void* handle)
{
    LOG(3,"config_server_network_keys_generation_done_cb \n");

#ifdef OSAPP_MESH_GATT_PROVISIONING_TEST
    ble_mesh_gatt_evt_update(BLE_MESH_EVT_PROVISIONING_DONE,0);
#endif/* OSAPP_MESH_GATT_PROVISIONING_TEST */

    if(m_server.network_keys_generation_done_cb !=0 && m_server.network_keys_generation_done_cb != config_server_network_keys_generation_done_cb)
    {
        m_server.network_keys_generation_done_cb(handle);
    }
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* temp*/
//TODO : change
void config_server_unprov_dev_done_cb(uint8_t success , uint8_t reason)
{
    if(success == 1)
    {
        LOG(LOG_LVL_INFO,"config_server_unprov_dev_done_cb \n");

        //generate device key
        server_generate_device_key_by_ecdh_and_salt();
    }
}
///---------------------------- server
static void server_generate_device_key_by_ecdh_and_salt(void)
{
    ecdh_prov_salt_to_devkey(provision_key.ecdh_secret.x , session_info.provisioning_salt ,m_server.devkey, server_dev_key_gen_done);
}
static void server_dev_key_gen_done(void)
{
    ///<1>. save devkey
        dm_devkey_handle_t l_handle;
        if(MESH_CORE_SUCCESS !=dm_devkey_add(provision_data.unicast_addr,m_server.devkey,&l_handle))
        {
            BX_ASSERT(0);
        }
    ///<2>. set server data
        //set iv index
        mesh_beacon_iv_index_set(provision_data.current_iv_index);
        //init self
        uint8_t add_key_statue = 0;
        init_elmt_addr(provision_data.unicast_addr);
        //config_server_add_netkey(provision_data.network_key , provision_data.key_index , &add_key_statue,server_network_keys_generation_done_cb);
        config_server_add_netkey(provision_data.network_key , provision_data.key_index , &add_key_statue,NULL);//NULL is callback function reserved for user
    ///<2>. send pc devkey
        node_save_element_uni_adddr();
        node_save_misc_iv_index();

        //node data save data done.
        ble_mesh_gatt_evt_update(BLE_MESH_EVT_FLASHSAVE_DONE,0);
}

#endif

