#include "ble_adapt.h"
#include "osapp_config.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "gapc_task.h"
#include "jmeshs_prov.h"
#include "jmeshc.h"
#include "jmeshc_task.h"
#include "jmesh_print.h"
#include "jmeshs_prov.h"
#include "jmeshs_prov_task.h"
#include "diss_task.h"
#include"../onchip_system/os_time.h"
#include "set_adv_payload_31Byte_patch.h"

#include"../driver/jmesh_ble_callback.h"
#include"jmesh_ble.h"
#include"jmesh_gpio.h"
#include"jmesh_gatt.h"
#include"../jmesh/jmesh_pdu.h"
#include"../bearer/adv/jmesh_adv.h"
#define BLE_ADVERTISING_INTERVAL_MIN_MS 20
#define BLE_ADVERTISING_INTERVAL_MAX_MS 20
#define BLE_SCAN_INTERVAL_MS 20
#define BLE_SCAN_WINDOW_MS 20
#define JMESH_STATE_SCANNING 1
#define JMESH_STATE_ADVERTISING 2
static TimerHandle_t scan_adv_timer;
static int scan_adv_state=0;

static int ble_update_advertise_data(unsigned char type,unsigned char length,unsigned char* data);
int ble_cancel(void);
int ble_scan(void);
 
extern void rf_reg_setting_adv(void);
extern void rf_reg_setting_scan(void);


//unsigned char peer_mac[6] = {0x92,0x22,0x33,0x44,0x55,0x66};
//unsigned char g_buf[31];
static void ble_adv_report_handler(ke_msg_id_t const msgid, struct adv_report *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    jmesh_ble_recv_adv_callback(param->adv_addr.addr, param->rssi,param->data[1], param->data[0]-1,(unsigned char *)(param->data+2));
    if(jmesh_gatt_ready_num()>=JMESH_GATT_CONNECT_LIMIT)
    {
        return;
    }
    driver_connect_adv_recv_cb(param->adv_addr.addr,param->data[0]-1,(unsigned char *)(param->data+2));
}

void os_timer_handler(TimerHandle_t xTimer){
    os_time_interrupt();
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
static int32_t osapp_add_jmeshs_app_server_task()
{
    struct diss_db_cfg* db_cfg;
    // Allocate the DISS_CREATE_DB_REQ
    struct gapm_profile_task_add_cmd *req = AHI_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,TASK_ID_GAPM, gapm_profile_task_add_cmd, sizeof(struct diss_db_cfg));
    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl = PERM(SVC_AUTH, NO_AUTH);
    req->prf_task_id = TASK_ID_JMESHS_APP;
    req->app_task = TASK_AHI;
    req->start_hdl = 0;

    // Set parameters
    db_cfg = (struct diss_db_cfg* ) req->param;
    db_cfg->features = DIS_ALL_FEAT_SUP;
    return osapp_msg_build_send(req,sizeof(struct gapm_profile_task_add_cmd)+sizeof(struct diss_db_cfg));
}
static int32_t osapp_add_jmeshs_prov_server_task()
{
    struct diss_db_cfg* db_cfg;
    // Allocate the DISS_CREATE_DB_REQ
    struct gapm_profile_task_add_cmd *req = AHI_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,TASK_ID_GAPM, gapm_profile_task_add_cmd, sizeof(struct diss_db_cfg));
    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl = PERM(SVC_AUTH, NO_AUTH);
    req->prf_task_id = TASK_ID_JMESHS_PROV;
    req->app_task = TASK_AHI;
    req->start_hdl = 0;

    // Set parameters
    db_cfg = (struct diss_db_cfg* ) req->param;
    db_cfg->features = DIS_ALL_FEAT_SUP;
    return osapp_msg_build_send(req,sizeof(struct gapm_profile_task_add_cmd)+sizeof(struct diss_db_cfg));
}

int ble_set_att(unsigned short handler,const unsigned char* data,unsigned char length){
    struct gattm_att_set_value_req* addr_req=AHI_MSG_ALLOC_DYN(GATTM_ATT_SET_VALUE_REQ,TASK_ID_GATTM, gattm_att_set_value_req,length);
    addr_req->handle=handler;
    addr_req->length=length;
    memcpy(addr_req->value,data,length);
    osapp_msg_build_send(addr_req,sizeof(struct gattm_att_set_value_req)+length);  
		return 0;
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

int ble_cancel(void)
{
    struct gapm_cancel_cmd *cmd = AHI_MSG_ALLOC(GAPM_CANCEL_CMD,TASK_ID_GAPM,gapm_cancel_cmd);
    cmd->operation = GAPM_CANCEL;
    LOG(LOG_LVL_INFO,"ble_cancel\n");
    return osapp_msg_build_send(cmd,sizeof(struct gapm_cancel_cmd));
}

int ble_scan(void)
{
     struct gapm_start_scan_cmd *cmd = AHI_MSG_ALLOC(GAPM_START_SCAN_CMD,TASK_ID_GAPM,gapm_start_scan_cmd);

    cmd->op.code = GAPM_SCAN_PASSIVE;
    cmd->mode = GAP_OBSERVER_MODE;
    cmd->interval =BLE_SCAN_INTERVAL_MS*1.6;//N*0.625ms
    cmd->window = BLE_SCAN_WINDOW_MS*1.6;
    LOG(LOG_LVL_INFO,"ble_scan start:\n");     
    return osapp_msg_build_send(cmd, sizeof(struct gapm_start_scan_cmd));
}
int ble_connect(unsigned short timeflow_ms,unsigned char addr_type,unsigned char* addr)
{
    struct gapm_start_connection_cmd* cmd = AHI_MSG_ALLOC_DYN(GAPM_START_CONNECTION_CMD,
                                                                     TASK_ID_GAPM,
                                                                     gapm_start_connection_cmd, sizeof(struct gap_bdaddr));
    cmd->op.code = GAPM_CONNECTION_DIRECT;
    cmd->op.addr_src = addr_type;
    cmd->scan_interval = 32;
    cmd->scan_window = 32;
    
    cmd->con_intv_max = 0x6;
    cmd->con_intv_min = 0x6;
    cmd->con_latency = 0;
    cmd->superv_to = timeflow_ms*1.6;

    cmd->ce_len_max = 0x0;
    cmd->ce_len_min = 0x0;

    cmd->nb_peers = 1;

    cmd->peers[0].addr_type=ADDR_PUBLIC;
    cmd->peers[0].addr.addr[0] = addr[0];
    cmd->peers[0].addr.addr[1] = addr[1];
    cmd->peers[0].addr.addr[2] = addr[2];
    cmd->peers[0].addr.addr[3] = addr[3];
    cmd->peers[0].addr.addr[4] = addr[4];
    cmd->peers[0].addr.addr[5] = addr[5];
    LOG(LOG_LVL_INFO,"ble_connect:\n"); 
    return osapp_msg_build_send(cmd, sizeof(struct gapm_start_connection_cmd) + sizeof(struct gap_bdaddr) );
}


int ble_discover_service(unsigned char connect_id)
{
    struct gattc_sdp_svc_disc_cmd* svc_req=KE_MSG_ALLOC_DYN(GATTC_SDP_SVC_DISC_CMD,
                                                                                    KE_BUILD_ID(TASK_GATTC,connect_id),TASK_AHI,
                                                                                    gattc_sdp_svc_disc_cmd,ATT_UUID_16_LEN);
    svc_req->operation=GATTC_SDP_DISC_SVC_ALL;
    svc_req->start_hdl=0;
    svc_req->end_hdl=0xffff;
    svc_req->uuid_len=ATT_UUID_16_LEN;
    ke_msg_send(svc_req);
    LOG(LOG_LVL_INFO,"ble_discover_service:\n"); 
    return 0;
}
int ble_disconnect(unsigned char connect_id)
{
    struct gapc_disconnect_cmd *cmd = AHI_MSG_ALLOC(GAPC_DISCONNECT_CMD,connect_id,gapc_disconnect_cmd);
    
    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;
    LOG(LOG_LVL_INFO,"ble_disconnect:\n"); 
    
    scan_adv_state=JMESH_STATE_SCANNING;
    //ble_cancel();
    ble_scan();
    return osapp_msg_build_send(cmd,sizeof(struct gapc_disconnect_cmd));
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
						osapp_add_jmeshs_prov_server_task();
            break;
        case GAPM_SCAN_ACTIVE:
        case GAPM_SCAN_PASSIVE: 
            LOG(LOG_LVL_INFO,"%ld: scan passive ind %x\n",xTaskGetTickCount(),param->status);	
			
						if(param->status == GAP_ERR_CANCELED)
						{
								jmesh_pdu_t** pdu=os_queue_pop(adv_cache_queue);	
								if(NULL == pdu) return ;
						
									if((*pdu)->adv.ad_type == JMESH_ADV_TYPE_BEACON)
									{
											jmesh_ble_send_adv(ADV_MODE_CONN,JMESH_ADV_TYPE_BEACON,(*pdu)->adv.length,(*pdu)->adv.para);	
											os_timer_event_set(&adv_timer,5,(os_timer_event_caller_t)adv_scan_timer,NULL);											
									}else if((*pdu)->adv.ad_type == JMESH_ADV_TYPE_MESSAGE)
									{
											jmesh_ble_send_adv(ADV_MODE_NON_CONN,JMESH_ADV_TYPE_MESSAGE,(*pdu)->adv.length,(*pdu)->adv.para);																		
									}
									jmesh_pdu_free(*pdu);																													
						}
            break;
						
        case GAPM_ADV_NON_CONN:								
        case GAPM_ADV_UNDIRECT:
						LOG(LOG_LVL_INFO,"%ld: adv udirect ind %x\n",xTaskGetTickCount(),param->status);					              
						if(param->status == GAP_ERR_CANCELED)
						{							
								jmesh_ble_scan_adv();		
								os_timer_event_set(&adv_timer,(rand()%80+80)/20,(os_timer_event_caller_t)adv_scan_timer,NULL);							
						}else if(param->status  == GAP_ERR_NO_ERROR){
								jmesh_ble_scan_adv();									
						}
            break;
        case GAPM_CANCEL:
					  LOG(LOG_LVL_INFO,"gapm canceled %x\n",param->status);
            
            break;
        case GAPM_PROFILE_TASK_ADD:

            LOG(LOG_LVL_INFO,"create timer\n");
            //ble_scan();
            jmesh_ble_scan_adv();	        
            break;
        case GAPM_CONNECTION_DIRECT:
        default:

            break;
    }
}


static void ble_device_ready_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    ble_reset();
}
static int32_t osapp_gapc_conn_confirm(ke_task_id_t dest_id)
{
    struct gapc_connection_cfm *cfm = AHI_MSG_ALLOC(GAPC_CONNECTION_CFM, dest_id, gapc_connection_cfm);
    cfm->auth = GAP_AUTH_REQ_NO_MITM_NO_BOND;
    return osapp_msg_build_send(cfm,sizeof(struct gapc_connection_cfm));
}
static int ble_disc_all_svc(unsigned char connect_id)
{
     struct gattc_sdp_svc_disc_cmd * svc_req = KE_MSG_ALLOC_DYN(GATTC_SDP_SVC_DISC_CMD,
            KE_BUILD_ID(TASK_GATTC, connect_id), TASK_AHI,
            gattc_sdp_svc_disc_cmd, ATT_UUID_16_LEN);

    svc_req->operation = GATTC_SDP_DISC_SVC_ALL;
    svc_req->start_hdl = 0x0001;
    svc_req->end_hdl = 0xffff;
    svc_req->uuid_len = ATT_UUID_16_LEN;
    LOG(LOG_LVL_WARN,"jmesh svc discover startconidx:%d,src:%d,dest:%d !\n",connect_id,KE_BUILD_ID(TASK_GATTC, connect_id),TASK_AHI);
    ke_msg_send(svc_req);
		return 0;
}

static void ble_connect_req_handler(ke_msg_id_t const msgid, struct gapc_connection_req_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    struct gapc_connection_cfm *cfm = AHI_MSG_ALLOC(GAPC_CONNECTION_CFM, src_id, gapc_connection_cfm);
    cfm->auth = GAP_AUTH_REQ_NO_MITM_NO_BOND;
    jmeshs_prov_env.connect_id=src_id;
 
    osapp_msg_build_send(cfm,sizeof(struct gapc_connection_cfm));
	
    jmesh_ble_gatt_connected_callback((unsigned char *)param->peer_addr.addr, param->conhdl);
    print_note("mac[%02x] connected!id=%d\n",param->peer_addr.addr[5],param->conhdl);
    jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_LOW);
    
}
static void ble_gapc_connection_confirm_handler(ke_msg_id_t const msgid, struct gapc_disconnect_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"connection[%x] confirmed\n",src_id);  
}
static void ble_disconnect_handler(ke_msg_id_t const msgid, struct gapc_disconnect_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    //ble_undirect_advertising(0xff,sizeof("hello world!"),"hello world!");
    //ble_scan();
		
		//driver_gatt_disconnected_cb(KE_IDX_GET(src_id));
    jmesh_ble_gatt_disconnected_callback(KE_IDX_GET(src_id));
    print_note("\n!!!!!!!!!!!!!!disconnect:%d,reason:%02x!!!!!!!!!!!!!!!!!!!!\n",param->conhdl,param->reason);
    jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_HIGH);
}
static void ble_mtu_change_handler(ke_msg_id_t const msgid, struct gattc_mtu_changed_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
	  //LOG(LOG_LVL_INFO,"\nmtu_exc_success,time:%d ms\n",20*xTaskGetTickCount());
    //LOG(LOG_LVL_INFO,"mtu = %d,%d\n",param->mtu, param->seq_num);
		//driver_set_mtu_cb(KE_IDX_GET(src_id), param->mtu);
    //print_note("mtu exchange success,mtu:%d,src_id:%d!!!\n",param->mtu,KE_IDX_GET(src_id));
    jmesh_ble_exchange_mtu_callback(KE_IDX_GET(src_id), param->mtu);
}

static void ble_gapc_cmp_evt_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
}
static void ble_profile_added_handler(ke_msg_id_t const msgid, struct gapm_profile_added_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
		//svc_handler = param->start_hdl;
    //LOG(LOG_LVL_INFO,"profile added\n");
    //print_note("local svc:%d\n",param->start_hdl);
	
    if(param->prf_task_id == TASK_ID_JMESHS_PROV)
    {
			    jmesh_ble_set_local_svc_ins(param->start_hdl);
//        osapp_add_jmeshs_app_server_task();
    }
    if(param->prf_task_id==TASK_ID_JMESHS_APP)
    {

    }	
}
static void jmesh_trans_handler(ke_msg_id_t const msgid, struct jmeshs_trans_req_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    struct jmeshs_trans_cfm *cfm=(struct jmeshs_trans_cfm*)AHI_MSG_ALLOC(JMESHS_TRANS_CFM,src_id,jmeshs_trans_cfm);
    cfm->src_id=param->src_id;
    cfm->len=5;
    cfm->handle=param->handle; 
    memcpy(cfm->data,"test0",5);

    LOG(LOG_LVL_INFO,"jmesh trans handle %d,src %d,dest %d\n",param->handle,src_id,dest_id);
    osapp_msg_build_send(cfm,sizeof(struct jmeshs_trans_cfm));
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
    //int i,j;
	  //LOG(LOG_LVL_INFO,"\nsvc_dis_success,time:%d ms\n",20*xTaskGetTickCount());
    //LOG(LOG_LVL_INFO,"svc find uuid: %x %x %x %x,start %d,end %d\n",param->uuid[0],param->uuid[1],param->uuid[2],param->uuid[3],param->start_hdl,param->end_hdl);
//    for(i=param->start_hdl;i<param->end_hdl;i++){
//        for(j=0;j<sizeof(union gattc_sdp_att_info);j++){
//            LOG(LOG_LVL_INFO,"svc",((unsigned char*)&param->info[i-param->start_hdl])[j]);
//        }
//        LOG(LOG_LVL_INFO,"\n");
//    }
		//driver_set_svc_handler_cb(KE_IDX_GET(src_id),param->start_hdl);
    jmesh_ble_disc_svc_callback(KE_IDX_GET(src_id),NULL,param->start_hdl);
    //print_note("service discover success,handle:%d!!!\n",param->start_hdl);
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
            struct gapc_bond_cfm *cfm = AHI_MSG_ALLOC(GAPC_BOND_CFM, jmeshs_prov_env.connect_id, gapc_bond_cfm);
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
            struct gapc_bond_cfm *cfm = AHI_MSG_ALLOC(GAPC_BOND_CFM, jmeshs_prov_env.connect_id, gapc_bond_cfm);
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

static void ble_gattc_cmp_evt_handler(ke_msg_id_t const msgid, struct gattc_cmp_evt const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{    
    driver_gattc_cmp_evt_callback(param->operation);
}

//#define OSAPP_JMESH
#ifdef OSAPP_JMESH

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

            {GATTC_DISC_SVC_INCL_IND,   (osapp_msg_handler_t)ble_disc_incl_handler},
            {GATTC_DISC_CHAR_IND,   (osapp_msg_handler_t)ble_disc_char_handler},
            {GATTC_DISC_CHAR_DESC_IND,  (osapp_msg_handler_t)ble_disc_desc_handler},
            {GATTC_SDP_SVC_IND, (osapp_msg_handler_t)ble_sdp_svc_handler},
            {GAPC_PARAM_UPDATE_REQ_IND, (osapp_msg_handler_t)ble_param_update_req_handler},
            {GATTC_MTU_CHANGED_IND, (osapp_msg_handler_t)ble_mtu_change_handler},
            {GAPM_PROFILE_ADDED_IND,    (osapp_msg_handler_t)ble_profile_added_handler},
            {JMESHS_TRANS_REQ_IND,  (osapp_msg_handler_t)jmesh_trans_handler},

            {GAPC_BOND_REQ_IND,             (osapp_msg_handler_t)ble_gapc_bond_req_ind_handler},
            {GAPC_BOND_IND,                 (osapp_msg_handler_t)ble_gapc_bond_ind_handler},
						{GATTC_EVENT_IND,(osapp_msg_handler_t)osapp_gattc_event_ind_handler},
            {GATTC_CMP_EVT,(osapp_msg_handler_t)ble_gattc_cmp_evt_handler},
};
const osapp_msg_handler_info_t handler_info = ARRAY_INFO(handler_table);

#endif

