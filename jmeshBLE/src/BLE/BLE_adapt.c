#include "ble_adapt.h"
#include "osapp_config.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "gapc_task.h"
#include "jmesh_print.h"
#include"../../bearer/beacon/jmesh_device_beacon.h"
#include "diss_task.h"
#include"../onchip_system/os_time.h"
#include "set_adv_payload_31Byte_patch.h"
#include"semphr.h"
#include"../onchip_system/os_main.h"
#include"../driver/jmesh_ble_callback.h"
#include"jmesh_ble.h"
#include"jmesh_gpio.h"
#include"jmesh_gatt.h"
#include"../jmesh/jmesh_pdu.h"
#include"../bearer/adv/jmesh_adv.h"
#include "jmesh_prov_svc.h"
#define BLE_ADVERTISING_INTERVAL_MIN_MS 20
#define BLE_ADVERTISING_INTERVAL_MAX_MS 20
#define BLE_SCAN_INTERVAL_MS 20
#define BLE_SCAN_WINDOW_MS 20
#define JMESH_STATE_SCANNING 1
#define JMESH_STATE_ADVERTISING 2

SemaphoreHandle_t  ble_adv_xSemaphore=NULL;
SemaphoreHandle_t  ble_gatt_xSemaphore=NULL;
static int ble_update_advertise_data(unsigned char type,unsigned char length,unsigned char* data);
static void ble_adv_report_handler(ke_msg_id_t const msgid, struct adv_report *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
//		unsigned char mac[6] = {0x01,0x00,0x27,0x11,0x18,0x20};
//		if(memcmp(param->adv_addr.addr+2,mac+2,4) != 0)  return ;
    jmesh_ble_recv_adv_callback(param->adv_addr.addr, param->rssi,param->data[1], param->data[0]-1,(unsigned char *)(param->data+2));
			
    if(jmesh_gatt_ready_num()>=JMESH_GATT_CONNECT_LIMIT)
    {
        return;
    }
}
int ble_reset(void)
{
    struct gapm_reset_cmd *cmd = AHI_MSG_ALLOC(GAPM_RESET_CMD,TASK_ID_GAPM,gapm_reset_cmd);
    cmd->operation = GAPM_RESET;
    LOG(LOG_LVL_INFO,"ble_reset:cmd->operation = %x \n",cmd->operation);

    return osapp_msg_build_send(cmd, sizeof(struct gapm_reset_cmd));
}
int ble_config()
{
    // Set Device configuration
    struct gapm_set_dev_config_cmd* cmd = AHI_MSG_ALLOC(GAPM_SET_DEV_CONFIG_CMD,TASK_ID_GAPM,gapm_set_dev_config_cmd);
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_ALL;//;GAP_ROLE_PERIPHERAL;//
    cmd->att_cfg = GAPM_MASK_ATT_SVC_CHG_EN | GAPM_MASK_ATT_SLV_PREF_CON_PAR_EN; 
    // Set Data length parameters
    cmd->sugg_max_tx_octets = BLE_MIN_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MIN_TIME;
    cmd->addr_type = GAPM_CFG_ADDR_PUBLIC;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->max_mtu=GAP_MAX_LE_MTU;
    
    LOG(LOG_LVL_INFO,"ble_config: operation = %d,role =%d,sugg_max_tx_octets=%d,sugg_max_tx_time=%d,addr_type=%d,pairing_mode=%d,max_mtu = %d\n",
    cmd->operation,cmd->role,cmd->sugg_max_tx_octets,cmd->sugg_max_tx_time,cmd->addr_type,cmd->pairing_mode,cmd->max_mtu);  
    return osapp_msg_build_send(cmd, sizeof(struct gapm_set_dev_config_cmd) );
}

static int ble_update_advertise_data(unsigned char type,unsigned char length,unsigned char* data)
{
    struct gapm_update_advertise_data_cmd *cmd = AHI_MSG_ALLOC(GAPM_UPDATE_ADVERTISE_DATA_CMD,TASK_ID_GAPM, gapm_update_advertise_data_cmd);

    LOG(LOG_LVL_INFO,"undirect_advertising update\n");
    cmd->operation = GAPM_UPDATE_ADVERTISE_DATA;
    cmd->adv_data_len = 0;
    
    cmd->adv_data[0]=length;
    cmd->adv_data[1]=type;
    memcpy(cmd->adv_data+2,data,length);
    cmd->adv_data_len=length+2;//adv_data+flags
    return osapp_msg_build_send(cmd,sizeof(struct gapm_update_advertise_data_cmd));
}

static void ble_default_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"defualt handler,msgid: 0x%x, dest_id: 0x%x, src_id: 0x%x\n",msgid,dest_id,src_id);
}
static int32_t ble_gapc_update_handler(ke_msg_id_t const msgid, struct gapc_param_updated_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{  
    LOG(LOG_LVL_INFO,"param updated\n");
		return 0;
}
static int32_t ble_param_update_req_handler(ke_msg_id_t const msgid, struct gapm_cmp_evt const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{   struct gapc_param_update_cfm *cfm = AHI_MSG_ALLOC(GAPC_PARAM_UPDATE_CFM, src_id, gapc_param_update_cfm);
    cfm->accept = 0x01;
    cfm->ce_len_max = 0xffff;
    cfm->ce_len_min = 0xffff;
    LOG(LOG_LVL_INFO,"ble_param_update_req_handler\n");	
    return osapp_msg_build_send(cfm, sizeof(struct gapc_param_update_cfm));
}

static void ble_gapm_cmp_evt_handler(ke_msg_id_t const msgid, struct gapm_cmp_evt const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{    
    switch(param->operation)
    {
        case GAPM_RESET:
            BX_ASSERT(param->status==GAP_ERR_NO_ERROR);
            LOG(LOG_LVL_INFO,"reset\n");  
            ble_config();

            break;
        case GAPM_SET_DEV_CONFIG:
            LOG(LOG_LVL_INFO,"add profile\n");  
						jmesh_add_prov_svc();
            break;
        case GAPM_SCAN_ACTIVE:
        case GAPM_SCAN_PASSIVE: 
            LOG(LOG_LVL_INFO,"%ld: scan passive ind status = 0x%x\n",xTaskGetTickCount(),param->status);	
						if(param->status == GAP_ERR_CANCELED)
						{
              if(JMESH_BLE_STATUS_SCAN==jmesh_ble_status()){
                xSemaphoreGive(ble_adv_xSemaphore );
              }																													
						}
            break;
						
        case GAPM_ADV_NON_CONN:								
        case GAPM_ADV_UNDIRECT:
						LOG(LOG_LVL_INFO,"%ld: adv udirect ind status = 0x%x\n",xTaskGetTickCount(),param->status);					              
						if(param->status == GAP_ERR_CANCELED)
						{							
								if(JMESH_BLE_STATUS_ADV==jmesh_ble_status()){
                  xSemaphoreGive(ble_adv_xSemaphore );
                }								
						}else if(param->status  == GAP_ERR_NO_ERROR){
								jmesh_scan_no_wait();									
						}
            break;
        case GAPM_CANCEL:
					  LOG(LOG_LVL_INFO,"gapm canceled ind status = 0x%x\n",param->status);            
            break;
        case GAPM_PROFILE_TASK_ADD:
            jmesh_scan_no_wait();	   
            break;
        case GAPM_CONNECTION_DIRECT:
          if(param->status==GAP_ERR_CANCELED){
              if(JMESH_BLE_STATUS_CONNECT==jmesh_ble_status()){
                xSemaphoreGive(ble_adv_xSemaphore );
              }
          }
          else if(param->status  == GAP_ERR_NO_ERROR){
              LOG(LOG_LVL_INFO,"connect ok start scan\n");
							jmesh_scan_no_wait();								
						}
          break;
        default:
            break;
    }
}

static void ble_device_ready_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    jmesh_ble_init();
    ble_reset();
}
static int32_t osapp_gapc_conn_confirm(ke_task_id_t dest_id)
{
    struct gapc_connection_cfm *cfm = AHI_MSG_ALLOC(GAPC_CONNECTION_CFM, dest_id, gapc_connection_cfm);
    cfm->auth = GAP_AUTH_REQ_NO_MITM_NO_BOND;
    return osapp_msg_build_send(cfm,sizeof(struct gapc_connection_cfm));
}

static void ble_connect_req_handler(ke_msg_id_t const msgid, struct gapc_connection_req_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    struct gapc_connection_cfm *cfm = AHI_MSG_ALLOC(GAPC_CONNECTION_CFM, src_id, gapc_connection_cfm);
    cfm->auth = GAP_AUTH_REQ_NO_MITM_NO_BOND;
    jmesh_prov_svc_env.connect_id=src_id;
 
    osapp_msg_build_send(cfm,sizeof(struct gapc_connection_cfm));
  
    LOG(LOG_LVL_WARN,"%x %x %x %x %x %x connected id=%d\n",param->peer_addr.addr[0],param->peer_addr.addr[1],
      param->peer_addr.addr[2],param->peer_addr.addr[3],param->peer_addr.addr[4],param->peer_addr.addr[5],param->conhdl); 
    if(JMESH_BLE_STATUS_CONNECT==jmesh_ble_status()){
      jmesh_ble_gatt_connected_callback((unsigned char *)param->peer_addr.addr, param->conhdl,1);
      xSemaphoreGive(ble_gatt_xSemaphore );
    }
    else{
      jmesh_ble_gatt_connected_callback((unsigned char *)param->peer_addr.addr, param->conhdl,0);
    }
    jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_LOW);
}
static void ble_gapc_connection_confirm_handler(ke_msg_id_t const msgid, struct gapc_disconnect_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"connection[%x] confirmed\n",src_id);  
}
static void ble_disconnect_handler(ke_msg_id_t const msgid, struct gapc_disconnect_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_WARN,"%d disconnected reason %d\n",KE_IDX_GET(src_id),param->reason);	
    jmesh_ble_gatt_disconnected_callback(KE_IDX_GET(src_id),param->reason);
    jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_HIGH);
}
static void ble_mtu_change_handler(ke_msg_id_t const msgid, struct gattc_mtu_changed_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    jmesh_ble_exchange_mtu_callback(KE_IDX_GET(src_id), param->mtu);
}

static void ble_gapc_cmp_evt_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
}
static void ble_disc_incl_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"incl");
}
static void ble_disc_char_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"char");
}
static void ble_disc_desc_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"desc");
}
static void ble_sdp_svc_handler(ke_msg_id_t const msgid, struct gattc_sdp_svc_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    jmesh_ble_disc_svc_callback(KE_IDX_GET(src_id),NULL,param->start_hdl);
    xSemaphoreGive(ble_gatt_xSemaphore );
}
static mesh_env_t mesh_env;
void mesh_env_init(void){
    ;
}
const unsigned char* ble_get_mac(void)
{
    return mesh_env.MAC;
}
const unsigned char* ble_get_uri(void)
{
    return mesh_env.URI;
}
const unsigned char* ble_get_net_id(void)
{
    return mesh_env.net_ID;
}
void ble_set_net_id(const unsigned char* net_id)
{
    memcpy(mesh_env.net_ID,net_id,6);
}
static void ble_gapc_bond_req_ind_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    struct gapc_bond_req_ind const *ind = param;
    LOG(LOG_LVL_INFO,"gapc_bond_req_ind_%d\n",ind->request);
    switch(ind->request)
    {
        case GAPC_PAIRING_REQ:
        {
            LOG(LOG_LVL_INFO,"GAPC_PAIRING_REQ\n");
            struct gapc_bond_cfm *cfm = AHI_MSG_ALLOC(GAPC_BOND_CFM, jmesh_prov_svc_env.connect_id, gapc_bond_cfm);
            cfm->request = GAPC_PAIRING_RSP;
            cfm->accept = 0x01;
            cfm->data.pairing_feat.iocap = 0x03;
            cfm->data.pairing_feat.oob = 0x00;
            cfm->data.pairing_feat.auth = 0x09;
            cfm->data.pairing_feat.key_size = 0x10;
            cfm->data.pairing_feat.ikey_dist = 0x04;
            cfm->data.pairing_feat.rkey_dist = 0x03;
            cfm->data.pairing_feat.sec_req = 0x00;
            osapp_msg_build_send(cfm, sizeof(struct gapc_bond_cfm));
            break;
        }
        case GAPC_LTK_EXCH:
        {
            uint8_t i;
            LOG(LOG_LVL_INFO,"GAPC_LTK_EXCH\n");
            struct gapc_bond_cfm *cfm = AHI_MSG_ALLOC(GAPC_BOND_CFM, jmesh_prov_svc_env.connect_id, gapc_bond_cfm);
            cfm->accept = 0x1;
            cfm->request = GAPC_LTK_EXCH;
            cfm->data.ltk.ediv = 0xA6A4;
            for(i=0;i<KEY_LEN;i++)
            {
                cfm->data.ltk.ltk.key[i] = (uint8_t)co_rand_word();
            }
//                memcpy(cfm->data.ltk.ltk.key, ltk_key, sizeof(ltk_key));
            for(i=0;i<RAND_NB_LEN;i++)
            {
                cfm->data.ltk.randnb.nb[i] = (uint8_t)co_rand_word();
            }
//                memcpy(cfm->data.ltk.randnb.nb, ltk_randnb, sizeof(ltk_randnb));
            cfm->data.ltk.key_size = KEY_LEN;
            osapp_msg_build_send(cfm, sizeof(struct gapc_bond_cfm));
            break;
        }
        default:
            break;
    }
}
static void osapp_gattm_add_svc_rsp_handler(ke_msg_id_t const msgid, struct gattm_add_svc_rsp const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    if(param->status == ATT_ERR_NO_ERROR)
    {
				jmesh_ble_set_local_svc_ins(param->start_hdl + 1);
    }else
    {
        LOG(LOG_LVL_ERROR,"add svc fail\n");
				LOG(3,"SVC fail num = 0x%x\n",param->status);
    }
		jmesh_ble_scan_adv();
}

static void ble_gapc_bond_ind_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{    
    struct gapc_bond_ind const *ind = param;
    LOG(LOG_LVL_INFO,"bond_ind_%d\n",ind->info);
    switch(ind->info)
    {
        case GAPC_CSRK_EXCH:
            LOG(LOG_LVL_INFO,"Csrk = %x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x\n",
                ind->data.csrk.key[15],ind->data.csrk.key[14],ind->data.csrk.key[13],ind->data.csrk.key[12],
                ind->data.csrk.key[11],ind->data.csrk.key[10],ind->data.csrk.key[9],ind->data.csrk.key[8],
                ind->data.csrk.key[7],ind->data.csrk.key[6],ind->data.csrk.key[5],ind->data.csrk.key[4],
                ind->data.csrk.key[3],ind->data.csrk.key[2],ind->data.csrk.key[1],ind->data.csrk.key[0]);
            break;
        case GAPC_PAIRING_SUCCEED:
            LOG(LOG_LVL_INFO,"Auth_%d,Ltk Present_%d\n",ind->data.auth.info,ind->data.auth.ltk_present);
            break;
    }
}

void jmesh_connect_num_answer(unsigned char id, unsigned short length, unsigned char *data);
static void osapp_gattc_event_ind_handler(ke_msg_id_t const msgid, struct gattc_event_ind const *param, ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    jmesh_ble_gatt_notified_callback(KE_IDX_GET(src_id),param->handle,param->length,(unsigned char *)param->value);
}

static void gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                       struct gattc_write_req_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    struct gattc_write_cfm *cfm = AHI_MSG_ALLOC(GATTC_WRITE_CFM,src_id,gattc_write_cfm);
		cfm->handle = param->handle;
		cfm->status = ATT_ERR_NO_ERROR;
		osapp_msg_build_send(cfm,sizeof(struct gattc_write_cfm));
		LOG(LOG_LVL_INFO,"param gattc_write_ind:%d,%d,%s\n", param->length, param->handle, param->value);
    jmesh_ble_gatt_writed_callback(KE_IDX_GET(src_id),param->handle,param->length,(unsigned char *)param->value);
}
static void ble_gattc_cmp_evt_handler(ke_msg_id_t const msgid, struct gattc_cmp_evt const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{    
    switch(param->operation)
    {
        case GATTC_WRITE:
            LOG(LOG_LVL_WARN,"ble write complete %d\n",param->status);
            if(param->status==GAP_ERR_NO_ERROR)
              xSemaphoreGive(ble_gatt_xSemaphore );
            break;
        case GATTC_NOTIFY:
            LOG(LOG_LVL_WARN,"ble notify complete %d,%d,%d\n",param->status,param->seq_num,dest_id);
            if(param->status==GAP_ERR_NO_ERROR){
              xSemaphoreGive(ble_gatt_xSemaphore );
            }
            else{
              jmesh_gatt_disconnect(jmesh_gatt_get_by_id(dest_id>>8));
            }
            
            break;
        case GATTC_WRITE_NO_RESPONSE:
            LOG(LOG_LVL_WARN,"ble write no response complete %d,%d %d\n",param->status,param->seq_num,dest_id);
            if(param->status==GAP_ERR_NO_ERROR){
              xSemaphoreGive(ble_gatt_xSemaphore );
            }
            else{
              jmesh_gatt_disconnect(jmesh_gatt_get_by_id(dest_id>>8));
            }
          break;
        default:
            break;
    }
}

#ifdef OSAPP_JMESH
extern void os_start(void);
static const osapp_msg_handler_table_t handler_table[]=
{
    [0] =   {KE_MSG_DEFAULT_HANDLER,  (osapp_msg_handler_t)ble_default_handler},
            {GAPC_CONNECTION_REQ_IND,       (osapp_msg_handler_t)ble_connect_req_handler},
            {GAPC_CONNECTION_CFM,   (osapp_msg_handler_t)ble_gapc_connection_confirm_handler},
            {GAPC_PARAM_UPDATED_IND,    (osapp_msg_handler_t)ble_gapc_update_handler},
            {GAPC_DISCONNECT_IND,   (osapp_msg_handler_t)ble_disconnect_handler},
            {GAPM_CMP_EVT,  (osapp_msg_handler_t)ble_gapm_cmp_evt_handler},
            {GAPM_DEVICE_READY_IND, (osapp_msg_handler_t)ble_device_ready_handler},
            {GATTC_MTU_CHANGED_IND, (osapp_msg_handler_t)ble_mtu_change_handler},
            {GAPC_CMP_EVT,  (osapp_msg_handler_t)ble_gapc_cmp_evt_handler},
            {GAPM_ADV_REPORT_IND,   (osapp_msg_handler_t)ble_adv_report_handler},
            {GATTM_ADD_SVC_RSP,(osapp_msg_handler_t)osapp_gattm_add_svc_rsp_handler},

            {GATTC_DISC_SVC_INCL_IND,   (osapp_msg_handler_t)ble_disc_incl_handler},
            {GATTC_DISC_CHAR_IND,   (osapp_msg_handler_t)ble_disc_char_handler},
            {GATTC_DISC_CHAR_DESC_IND,  (osapp_msg_handler_t)ble_disc_desc_handler},
            {GATTC_SDP_SVC_IND, (osapp_msg_handler_t)ble_sdp_svc_handler},
            {GAPC_PARAM_UPDATE_REQ_IND, (osapp_msg_handler_t)ble_param_update_req_handler},
            {GATTC_MTU_CHANGED_IND, (osapp_msg_handler_t)ble_mtu_change_handler},
//            {GAPM_PROFILE_ADDED_IND,    (osapp_msg_handler_t)ble_profile_added_handler},
            {GAPC_BOND_REQ_IND,             (osapp_msg_handler_t)ble_gapc_bond_req_ind_handler},
            {GAPC_BOND_IND,                 (osapp_msg_handler_t)ble_gapc_bond_ind_handler},
						{GATTC_EVENT_IND,(osapp_msg_handler_t)osapp_gattc_event_ind_handler},
            {GATTC_CMP_EVT,(osapp_msg_handler_t)ble_gattc_cmp_evt_handler},
						{GATTC_WRITE_REQ_IND,       (osapp_msg_handler_t)gattc_write_req_ind_handler},						
};
TaskHandle_t jmesh_handler;
const osapp_msg_handler_info_t handler_info = ARRAY_INFO(handler_table);
extern void os_main(void);
static const task_table_t task_table[]={
    {true,"jmesh_task",4,1600,NULL,os_main,&jmesh_handler},
};
const task_table_info_t extra_task_table_info=ARRAY_INFO(task_table);

#endif
