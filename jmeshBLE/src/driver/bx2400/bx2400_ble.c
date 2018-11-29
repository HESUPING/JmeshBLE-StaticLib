#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"../jmesh_ble.h"
#include"stdio.h"
#include"../../onchip_system/os_timer_event.h"
#include"../../onchip_system/os_timer.h"
#include"osapp_config.h"
#include"../../bearer/gatt/jmesh_gatt.h"
#include"set_adv_payload_31Byte_patch.h"
#include"../../jmesh/jmesh_print.h"
#include"../../bearer/adv/jmesh_adv.h"
#include"semphr.h"


extern SemaphoreHandle_t  ble_adv_xSemaphore;
extern SemaphoreHandle_t  ble_gatt_xSemaphore;


static os_timer_t ble_adv_wait_timer;
static os_timer_t ble_gatt_wait_timer;
static unsigned short local_svc_ins=0;

int ble_status=JMESH_BLE_STATUS_INIT;

int jmesh_ble_status(void)
{
    return ble_status;
}

void jmesh_ble_init(void)
{
  os_timer_set(&ble_adv_wait_timer,0);
  os_timer_set(&ble_gatt_wait_timer,0); 
  ble_adv_xSemaphore = xSemaphoreCreateBinary();
  xSemaphoreTake(ble_adv_xSemaphore,0);
  ble_gatt_xSemaphore = xSemaphoreCreateBinary();
  xSemaphoreTake(ble_gatt_xSemaphore,0);
}
int jmesh_ble_adv_is_free(void){
  return os_timer_is_flow(&ble_adv_wait_timer);
}
static void jmesh_ble_adv_waiting(void){
  if(0==os_timer_is_flow(&ble_adv_wait_timer)){
    vTaskDelay((os_timer_remain(&ble_adv_wait_timer)+portTICK_RATE_MS-1)/portTICK_RATE_MS);
  }
}
static void jmesh_ble_adv_set_wait(unsigned short ms){
  os_timer_set(&ble_adv_wait_timer,ms);
}


static void jmesh_ble_gatt_waiting(void){
  if(0==os_timer_is_flow(&ble_gatt_wait_timer)){
    xSemaphoreTake(ble_gatt_xSemaphore ,(os_timer_remain(&ble_gatt_wait_timer)+portTICK_RATE_MS-1)/portTICK_RATE_MS);
  }
}
static void jmesh_ble_gatt_set_wait(unsigned short ms){
  os_timer_set(&ble_gatt_wait_timer,ms);
}


void jmesh_ble_cancel(void)
{
    struct gapm_cancel_cmd *cmd = AHI_MSG_ALLOC(GAPM_CANCEL_CMD,TASK_ID_GAPM,gapm_cancel_cmd);
    cmd->operation = GAPM_CANCEL;
    if(ble_status==JMESH_BLE_STATUS_SCAN){
      print_info("ble cancel scan\n");
    }else if(ble_status==JMESH_BLE_STATUS_ADV){
      print_info("ble cancel adv\n");
    }else if(ble_status==JMESH_BLE_STATUS_CONNECT){
      print_info("ble cancel connect\n");
    }
    osapp_msg_build_send(cmd,sizeof(struct gapm_cancel_cmd));
    
    if(pdTRUE!=xSemaphoreTake(ble_adv_xSemaphore ,10)){
      print_info("ble cancel timeflow\n");
    }
}

void jmesh_ble_reset(void){
    struct gapm_reset_cmd *cmd = AHI_MSG_ALLOC(GAPM_RESET_CMD,TASK_ID_GAPM,gapm_reset_cmd);
    cmd->operation = GAPM_RESET;
    print_info("ble reset\n");
    osapp_msg_build_send(cmd, sizeof(struct gapm_reset_cmd));
    ble_status=JMESH_BLE_STATUS_INIT;
    xSemaphoreTake(ble_adv_xSemaphore ,10);//just wait 10ticks
}
void jmesh_ble_scan_adv(void){
    struct gapm_start_scan_cmd *cmd;
    if(ble_status==JMESH_BLE_STATUS_SCAN){
      return;
    }
    jmesh_ble_adv_waiting();
    {
      cmd = AHI_MSG_ALLOC(GAPM_START_SCAN_CMD,TASK_ID_GAPM,gapm_start_scan_cmd);
      cmd->op.code = GAPM_SCAN_PASSIVE;
      cmd->mode = GAP_OBSERVER_MODE;
      cmd->interval =30*1.6;
      cmd->window = 20*1.6;
      
      if(ble_status!=JMESH_BLE_STATUS_INIT){
        jmesh_ble_cancel();
      }
      print_info("ble start scan\n");
      ble_status=JMESH_BLE_STATUS_SCAN;
      osapp_msg_build_send(cmd, sizeof(struct gapm_start_scan_cmd));
    }
    jmesh_ble_adv_set_wait(jmesh_random_get(SCAN_KEEP_MIN_MS,SCAN_KEEP_MAX_MS));
}
void jmesh_scan_no_wait(void){
  struct gapm_start_scan_cmd *cmd;
    cmd = AHI_MSG_ALLOC(GAPM_START_SCAN_CMD,TASK_ID_GAPM,gapm_start_scan_cmd);
    cmd->op.code = GAPM_SCAN_PASSIVE;
    cmd->mode = GAP_OBSERVER_MODE;
    cmd->interval =30*1.6;
    cmd->window = 20*1.6;

    ble_status=JMESH_BLE_STATUS_SCAN;
    osapp_msg_build_send(cmd, sizeof(struct gapm_start_scan_cmd));

    jmesh_ble_adv_set_wait(jmesh_random_get(SCAN_KEEP_MIN_MS,SCAN_KEEP_MAX_MS));
}

void jmesh_ble_send_adv(unsigned char ad_mode,unsigned char ad_type,unsigned char length,unsigned char *data){
    struct gapm_start_advertise_cmd_patch *cmd;
    if(length + 2 > 31)
    {
        return;
    }
    jmesh_ble_adv_waiting();
    {
      cmd = AHI_MSG_ALLOC(GAPM_START_ADVERTISE_CMD,TASK_ID_GAPM,gapm_start_advertise_cmd_patch);
      if(ble_status!=JMESH_BLE_STATUS_INIT){
        jmesh_ble_cancel();
      }
      print_buffer_info(length,data,"ble adv type=%x:",ad_type);
      ble_status=JMESH_BLE_STATUS_ADV;
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
    }
    jmesh_ble_adv_set_wait(ADV_KEEP_MIN_MS);
    
    jmesh_ble_scan_adv();
}

void jmesh_ble_gatt_connect(unsigned char *mac){
    struct gapm_start_connection_cmd* cmd;
    print_buffer_info(6,mac,"connect mac:");
    jmesh_ble_adv_waiting();
    {
      cmd = AHI_MSG_ALLOC_DYN(GAPM_START_CONNECTION_CMD,TASK_ID_GAPM,gapm_start_connection_cmd,sizeof(struct gap_bdaddr));
      cmd->op.code = GAPM_CONNECTION_DIRECT;
      cmd->op.addr_src = GAPM_STATIC_ADDR;
      cmd->scan_interval = 0x04;
      cmd->scan_window = 0x04;
      cmd->con_intv_max = 100;//1.25ms
      cmd->con_intv_min = 100;
      cmd->con_latency = 9;
      cmd->superv_to = 800;//10ms 600*10>(9+1)*100
      cmd->ce_len_max = 0x0;
      cmd->ce_len_min = 0x0;
      cmd->nb_peers = 1;
      cmd->peers[0].addr_type=ADDR_PUBLIC;
      memcpy(cmd->peers[0].addr.addr, mac, 6);
      if(ble_status!=JMESH_BLE_STATUS_INIT){
        jmesh_ble_cancel();
      }
      ble_status=JMESH_BLE_STATUS_CONNECT;
      osapp_msg_build_send(cmd, sizeof(struct gapm_start_connection_cmd) + sizeof(struct gap_bdaddr) );
    }
    jmesh_ble_adv_set_wait(ADV_KEEP_MIN_MS);
}

void jmesh_ble_gatt_disconnect(unsigned char connect_id){
    struct gapc_disconnect_cmd *cmd = AHI_MSG_ALLOC(GAPC_DISCONNECT_CMD,KE_BUILD_ID(TASK_ID_GAPC,connect_id),gapc_disconnect_cmd);
    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;
    osapp_msg_build_send(cmd,sizeof(struct gapc_disconnect_cmd));
}

void jmesh_ble_disc_svc(unsigned char *uuid,unsigned char connect_id){
		struct gattc_sdp_svc_disc_cmd* svc_req=AHI_MSG_ALLOC(GATTC_SDP_SVC_DISC_CMD, (connect_id<<8)|KE_TYPE_GET(TASK_ID_GATTC),gattc_sdp_svc_disc_cmd);
    svc_req->operation        = GATTC_SDP_DISC_SVC;
    svc_req->start_hdl        = 1;
    svc_req->end_hdl          = ATT_1ST_REQ_END_HDL;
    svc_req->uuid_len = ATT_UUID_128_LEN;
    memcpy(svc_req->uuid, uuid, 16);
    osapp_msg_build_send(svc_req,sizeof(struct gattc_sdp_svc_disc_cmd));
}

void jmesh_ble_set_local_svc_ins(unsigned short instance)
{
    local_svc_ins=instance;
}

unsigned short jmesh_ble_get_local_svc_ins(void)
{
    return local_svc_ins;
}

void jmesh_ble_exchange_mtu(unsigned char connect_id){
    static uint16_t seq_num = 0;
    struct gattc_exc_mtu_cmd *cmd = AHI_MSG_ALLOC(GATTC_EXC_MTU_CMD, (connect_id<<8)|KE_TYPE_GET(TASK_ID_GATTC), gattc_exc_mtu_cmd);
    cmd->operation = GATTC_MTU_EXCH;
    cmd->seq_num = seq_num++;
    osapp_msg_build_send(cmd, sizeof(struct gattc_exc_mtu_cmd));
}

void jmesh_ble_gatt_write(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
    if(char_handler != ATT_INVALID_HANDLE)
    {      
        jmesh_ble_gatt_waiting(); 
        {      
           struct gattc_write_cmd *wr_char = AHI_MSG_ALLOC_DYN(GATTC_WRITE_CMD,KE_BUILD_ID(TASK_ID_GATTC, connect_id),gattc_write_cmd,length);
        
           // Offset
            wr_char->offset         = 0x0000;
            // cursor always 0
            wr_char->cursor         = 0x0000;
            // Write Type
            wr_char->operation      = GATTC_WRITE_NO_RESPONSE;
            // Characteristic Value attribute handle
            wr_char->handle         = char_handler;
            // Value Length
            wr_char->length         = length;
            // Auto Execute
            wr_char->auto_execute   = true;
            // Value
            memcpy(&wr_char->value[0], data, length);
            // Send the message
            osapp_msg_build_send(wr_char,sizeof(struct gattc_write_cmd)+length);
            print_buffer_info(length,data,"ble %d write %d:",connect_id,char_handler);
        }
        jmesh_ble_gatt_set_wait(GATT_WAIT_MIN_MS);
    }
}
void jmesh_ble_gatt_notify(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data){
    if(char_handler != ATT_INVALID_HANDLE)
    {
      jmesh_ble_gatt_waiting();
      {
        static uint16_t notify_seq_num = 0;
        struct gattc_send_evt_cmd *cmd = AHI_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,KE_BUILD_ID(TASK_ID_GATTC, connect_id),gattc_send_evt_cmd,length);
        cmd->operation = GATTC_NOTIFY;
        cmd->seq_num = notify_seq_num++;
        cmd->handle = char_handler;
        cmd->length = length;
        memcpy(cmd->value,data,length);
        osapp_msg_build_send(cmd,sizeof(struct gattc_send_evt_cmd)+length);
        print_buffer_info(length,data,"ble %d notify %d,seq=%d:",connect_id,char_handler,cmd->seq_num);
      }
      jmesh_ble_gatt_set_wait(GATT_WAIT_MIN_MS);
    }
}

#endif
