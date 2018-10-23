#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"../jmesh_ble.h"
#include"stdio.h"
#include"../../onchip_system/os_timer_event.h"
#include"osapp_config.h"
#include"../../bearer/gatt/jmesh_gatt.h"
#include"set_adv_payload_31Byte_patch.h"
#include"../../jmesh/jmesh_print.h"
#include"../../bearer/adv/jmesh_adv.h"
extern os_timer_event_t adv_timer;

static os_timer_event_t gatt_con_timer;
static os_timer_event_t mtu_exc_timer;
static os_timer_event_t svc_dis_timer;
static unsigned char peer_mac[6];

static unsigned short local_svc_ins=0;

static unsigned char gattc_write_cmp = 0;
static unsigned char gattc_notify_cmp = 0;

int ble_status=JMESH_BLE_STATUS_INIT;

int jmesh_ble_status(void)
{
    return ble_status;
}
void jmesh_ble_cancel(void)
{
    struct gapm_cancel_cmd *cmd = AHI_MSG_ALLOC(GAPM_CANCEL_CMD,TASK_ID_GAPM,gapm_cancel_cmd);
    cmd->operation = GAPM_CANCEL;
    LOG(LOG_LVL_INFO,"ble_cancel\n");
    osapp_msg_build_send(cmd,sizeof(struct gapm_cancel_cmd));
}

void jmesh_ble_reset(void){
    struct gapm_reset_cmd *cmd = AHI_MSG_ALLOC(GAPM_RESET_CMD,TASK_ID_GAPM,gapm_reset_cmd);
    cmd->operation = GAPM_RESET;
    osapp_msg_build_send(cmd, sizeof(struct gapm_reset_cmd));
}
void jmesh_ble_scan_adv(void){
    struct gapm_start_scan_cmd *cmd;
    ble_status=JMESH_BLE_STATUS_SCAN;
    cmd = AHI_MSG_ALLOC(GAPM_START_SCAN_CMD,TASK_ID_GAPM,gapm_start_scan_cmd);
    cmd->op.code = GAPM_SCAN_PASSIVE;
    cmd->mode = GAP_OBSERVER_MODE;
    cmd->interval =20*1.6;
    cmd->window = 20*1.6;
    osapp_msg_build_send(cmd, sizeof(struct gapm_start_scan_cmd));
}

static void gatt_con_overtime_caller(os_data_t data)
{
    jmesh_gatt_t* gatt_con;
    os_timer_event_remove(&gatt_con_timer);
    if(JMESH_BLE_STATUS_CONNECT==ble_status)
    {
        jmesh_ble_cancel();
    }
    gatt_con=jmesh_gatt_get_by_mac((unsigned char *)data);
    if(NULL!=gatt_con && !gatt_con->is_ready)
    {
        gatt_con->is_valid=0;
        print_note("connect overtime!!!mac[%02x]\n",((unsigned char *)data)[5]);
    }
    ble_status=JMESH_BLE_STATUS_INIT;
    jmesh_ble_scan_adv();
}

void jmesh_ble_send_adv(unsigned char ad_mode,unsigned char ad_type,unsigned char length,unsigned char *data){
    struct gapm_start_advertise_cmd_patch *cmd;
    if(length + 2 > 31)
    {
        return;
    }
    ble_status=JMESH_BLE_STATUS_ADV;
    cmd = AHI_MSG_ALLOC(GAPM_START_ADVERTISE_CMD,TASK_ID_GAPM,gapm_start_advertise_cmd_patch);
    switch(ad_mode)
    {
        case ADV_MODE_NON_CONN:
            cmd->op.code = GAPM_ADV_NON_CONN;
            cmd->intv_min = 160;
            cmd->intv_max = 160;
						cmd->info.host.mode = GAP_NON_DISCOVERABLE;
            break;
        case ADV_MODE_CONN:
            cmd->op.code = GAPM_ADV_UNDIRECT;
            cmd->intv_min = 32;
            cmd->intv_max = 32;
						cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
            break;
        case ADV_MODE_CREATE_CONN:
            cmd->op.code = GAPM_ADV_UNDIRECT;
            cmd->intv_min = 32;
            cmd->intv_max = 32;
						cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
            break;
        default:
            cmd->op.code = GAPM_ADV_NON_CONN;
            cmd->intv_min = 160;
            cmd->intv_max = 160;
						cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
    }
    cmd->op.addr_src    = GAPM_STATIC_ADDR;
    cmd->channel_map    = ADV_ALL_CHNLS_EN;
    cmd->info.host.scan_rsp_data_len = 0;
    cmd->info.host.adv_data_len      = 2 + length;
    cmd->info.host.adv_data[0]  = 1 + length;
    cmd->info.host.adv_data[1]  = ad_type;
    memcpy(cmd->info.host.adv_data+2,data,length);
    osapp_msg_build_send(cmd,sizeof(struct gapm_start_advertise_cmd_patch));
    if(ADV_MODE_CREATE_CONN==ad_mode)
    {
        ble_status=JMESH_BLE_STATUS_CONNECT;
        memcpy(peer_mac,data,6);
        os_timer_event_set(&gatt_con_timer,GATT_CON_TIMEOUT_MS,gatt_con_overtime_caller,(os_data_t)peer_mac);

    }
}



void driver_ble_gatt_connected(void)
{
    if(JMESH_BLE_STATUS_CONNECT==ble_status)
    {
        os_timer_event_remove(&gatt_con_timer);
        ble_status=JMESH_BLE_STATUS_INIT;
        jmesh_ble_scan_adv();
    }
}
#if 1
int jmesh_ble_gatt_connect(unsigned char *mac){
    struct gapm_start_connection_cmd* cmd;
    if(JMESH_BLE_STATUS_CONNECT==ble_status || JMESH_BLE_STATUS_INIT==ble_status)
    {
        return -1;
    }
    else
    {
        jmesh_ble_cancel();
    }
    ble_status = JMESH_BLE_STATUS_CONNECT;
    cmd = AHI_MSG_ALLOC_DYN(GAPM_START_CONNECTION_CMD,TASK_ID_GAPM,gapm_start_connection_cmd,sizeof(struct gap_bdaddr));
    cmd->op.code = GAPM_CONNECTION_DIRECT;
    cmd->op.addr_src = GAPM_STATIC_ADDR;
    cmd->scan_interval = 0x04;
    cmd->scan_window = 0x04;
    cmd->con_intv_max = 80;
    cmd->con_intv_min = 80;
    cmd->con_latency = 9;
    cmd->superv_to = 600;
    cmd->ce_len_max = 0x0;
    cmd->ce_len_min = 0x0;
    cmd->nb_peers = 1;
    cmd->peers[0].addr_type=ADDR_PUBLIC;
    memcpy(cmd->peers[0].addr.addr, mac, 6);
    osapp_msg_build_send(cmd, sizeof(struct gapm_start_connection_cmd) + sizeof(struct gap_bdaddr) );
    memcpy(peer_mac,mac,6);
    os_timer_event_set(&gatt_con_timer,GATT_CON_TIMEOUT_MS,gatt_con_overtime_caller,(os_data_t)peer_mac);
    return 0;
}
#endif
#if 0
int jmesh_ble_gatt_connect(unsigned char *mac){
    struct gapm_start_connection_cmd* cmd;
    if(JMESH_BLE_STATUS_CONNECT==ble_status || JMESH_BLE_STATUS_INIT==ble_status)
    {
        return -1;
    }
    else
    {
        jmesh_ble_cancel();
    }
    ble_status = JMESH_BLE_STATUS_CONNECT;
    cmd = AHI_MSG_ALLOC_DYN(GAPM_START_CONNECTION_CMD,TASK_ID_GAPM,gapm_start_connection_cmd,sizeof(struct gap_bdaddr));
    cmd->op.code = GAPM_CONNECTION_DIRECT;
    cmd->op.addr_src = GAPM_STATIC_ADDR;
    cmd->scan_interval = 0x04;
    cmd->scan_window = 0x04;
    cmd->con_intv_max = 80;
    cmd->con_intv_min = 80;
    cmd->con_latency = 0;
    cmd->superv_to = 0x2a;
    cmd->ce_len_max = 0x0;
    cmd->ce_len_min = 0x0;
    cmd->nb_peers = 1;
    cmd->peers[0].addr_type=ADDR_PUBLIC;
    memcpy(cmd->peers[0].addr.addr, mac, 6);
    osapp_msg_build_send(cmd, sizeof(struct gapm_start_connection_cmd) + sizeof(struct gap_bdaddr) );
    memcpy(peer_mac,mac,6);
    os_timer_event_set(&gatt_con_timer,GATT_CON_TIMEOUT_MS,gatt_con_overtime_caller,(os_data_t)peer_mac);
    return 0;
}
#endif
void jmesh_ble_gatt_disconnect(unsigned char connect_id){
    struct gapc_disconnect_cmd *cmd = AHI_MSG_ALLOC(GAPC_DISCONNECT_CMD,KE_BUILD_ID(TASK_ID_GAPC,connect_id),gapc_disconnect_cmd);
    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;
    osapp_msg_build_send(cmd,sizeof(struct gapc_disconnect_cmd));
}

static void svc_dis_overtime_caller(os_data_t data)
{
    jmesh_gatt_t *gatt_con=(jmesh_gatt_t *)data;
    os_timer_event_remove(&svc_dis_timer);
    if(NULL!=gatt_con && 0==gatt_con->svc_instance)
    {
        print_note("svc dis overtime!!!\n");
        jmesh_gatt_disconnect(gatt_con);
    }
}
void jmesh_ble_disc_svc(unsigned char *uuid,unsigned char connect_id){
    struct gattc_sdp_svc_disc_cmd* svc_req=KE_MSG_ALLOC_DYN(GATTC_SDP_SVC_DISC_CMD,KE_BUILD_ID(TASK_GATTC,connect_id),TASK_AHI,gattc_sdp_svc_disc_cmd,ATT_UUID_128_LEN);
    svc_req->operation        = GATTC_SDP_DISC_SVC;
    svc_req->start_hdl        = 1;
    svc_req->end_hdl          = ATT_1ST_REQ_END_HDL;
    svc_req->uuid_len = ATT_UUID_128_LEN;
    memcpy(svc_req->uuid, uuid, 16);
    ke_msg_send(svc_req);
    //os_timer_event_set(&svc_dis_timer,SVC_DIS_TIMEOUT_MS,svc_dis_overtime_caller,(os_data_t)jmesh_gatt_get_by_id(connect_id));
    //LOG(LOG_LVL_INFO,"\nsvc_dis_start,time:%d ms\n",20*xTaskGetTickCount());
}

void jmesh_ble_set_local_svc_ins(unsigned short instance)
{
    local_svc_ins=instance;
}

unsigned short jmesh_ble_get_local_svc_ins(void)
{
    return local_svc_ins;
}

static void mtu_exc_overtime_caller(os_data_t data)
{
    jmesh_gatt_t *gatt_con=(jmesh_gatt_t *)data;
    os_timer_event_remove(&mtu_exc_timer);
    if(NULL!=gatt_con && 0==gatt_con->mtu)
    {
        print_note("mtu exc overtime!!!\n");
        jmesh_gatt_disconnect(gatt_con);
    }
}
void jmesh_ble_exchange_mtu(unsigned char connect_id){
    static uint16_t seq_num = 0;
    struct gattc_exc_mtu_cmd *cmd = AHI_MSG_ALLOC(GATTC_EXC_MTU_CMD, KE_BUILD_ID(TASK_ID_GATTC, connect_id), gattc_exc_mtu_cmd);
    cmd->operation = GATTC_MTU_EXCH;
    cmd->seq_num = seq_num++;
    osapp_msg_build_send(cmd, sizeof(struct gattc_exc_mtu_cmd));
    //os_timer_event_set(&mtu_exc_timer,MTU_EXC_TIMEOUT_MS,mtu_exc_overtime_caller,(os_data_t)jmesh_gatt_get_by_id(connect_id));
    //LOG(LOG_LVL_INFO,"\nmtu_exc_start,time:%d ms\n",20*xTaskGetTickCount());
}

int jmesh_ble_gatt_write(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
    if(char_handler != ATT_INVALID_HANDLE)
    {
        struct gattc_write_cmd *wr_char = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD,KE_BUILD_ID(TASK_GATTC,connect_id),TASK_AHI,gattc_write_cmd,length);
        // Offset
        wr_char->offset         = 0x0000;
        // cursor always 0
        wr_char->cursor         = 0x0000;
        // Write Type
        wr_char->operation      = GATTC_WRITE;
        // Characteristic Value attribute handle
        wr_char->handle         = char_handler;
        // Value Length
        wr_char->length         = length;
        // Auto Execute
        wr_char->auto_execute   = true;
        // Value
        memcpy(&wr_char->value[0], data, length);
        // Send the message
        ke_msg_send(wr_char);
        gattc_write_cmp = 0;
        for(int i=0; i<50; i++)
        {
            vTaskDelay(1);
            if(gattc_write_cmp)
            {
                return 0;
            }
        }
    }
    return -1;
}
int jmesh_ble_gatt_notify(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
    if(char_handler != ATT_INVALID_HANDLE)
    {
        static uint16_t notify_seq_num = 0;
        struct gattc_send_evt_cmd *cmd = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,KE_BUILD_ID(TASK_GATTC,connect_id),TASK_AHI,gattc_send_evt_cmd,length);
        cmd->operation = GATTC_NOTIFY;
        cmd->seq_num = notify_seq_num++;
        cmd->handle = char_handler;
        cmd->length = length;
        memcpy(cmd->value,data,length);
        ke_msg_send(cmd);
        gattc_notify_cmp = 0;
        for(int i=0; i<50; i++)
        {
            vTaskDelay(1);
            if(gattc_notify_cmp)
            {
                return 0;
            }
        }
    }
    return -1;
}

void driver_gattc_cmp_evt_callback(unsigned char operation)
{
    switch(operation)
    {
        case GATTC_WRITE:
            gattc_write_cmp = 1;
            break;
        case GATTC_NOTIFY:
            gattc_notify_cmp = 1;
            break;
        default:
            break;
    }
}

void driver_connect_adv_recv_cb(unsigned char *mac, unsigned short length, unsigned char *data)
{
		static unsigned char bx_dev_addr[6] = BX_DEV_ADDR;
		//print_buffer_note(length,data,"receive adv:\n");
		//print_note("mac[%02x]\n",mac[5]);
		if(length != 6)
		{
				return;
		}
		else if(memcmp(bx_dev_addr, data, length) != 0)
		{
				return;
		}
		jmesh_gatt_connect_server(mac);
}
#endif
