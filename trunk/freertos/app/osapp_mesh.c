#include "osapp_config.h"
#ifdef OSAPP_MESH
#include <stddef.h>
#include <stdbool.h>
#include "osapp_mesh.h"
#include "bx_ring_queue.h"
#include "bearer.h"
#include "security.h"
#include "co_utils.h"
#include "co_math.h"
#include "mesh_definitions.h"
#include "provision_base.h"
#include "mesh_env.h"
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#include "mesh_tools.h"

#ifdef OSAPP_UART_LOG_TEST
#include "uart_log_test.h"
#ifdef MESH_TEST_UART_PROVISION
#include "mesh_uart_ctrl.h"
#endif/* MESH_TEST_UART_PROVISION */
#endif/* OSAPP_UART_LOG_TEST */


#define MESH_MSG_CACHE_LENGTH           5
#define MESH_ADV_REPORT_QUEUE_LENGTH    15


enum{
    MESH_INIT,
    MESH_TX,
    MESH_STOP,
    MESH_ON_AIR_OP_CANCELED,
    MESH_CALLBACK,
};
enum
{
    IDLE,
    SCAN,
    ADV_AND_SCAN,
}mesh_stat;
typedef struct {
    uint8_t mesh_buf[ADV_DATA_BUF_SIZE];
    uint8_t length;
}adv_report_env_t;
//for msg cache
adv_report_env_t adv_report_env;

network_transmit_state_t nw_tx_state=
{
    .count = NETWORK_TRANSMIT_DEFAULT_COUNT,               //send 6 times
    .interval_steps = NETWORK_TRANSMIT_DEFAULT_INTERVAL,   //interval = step*10 ms
};

air_op_t air_op;



adv_report_env_t mesh_msg_cache[MESH_MSG_CACHE_LENGTH]={0};
uint8_t mesh_msg_cache_wr_index = 0;


QueueHandle_t meshQueue;
TimerHandle_t advDurationTimer;
TimerHandle_t nwTxIntvTimer;
TaskHandle_t handler_mesh_task;


uint8_t adv_report_queue_busy = 0;
DEF_RING_QUEUE(adv_report_q,MESH_ADV_REPORT_QUEUE_LENGTH,adv_report_env_t);


static void mesh_adv_start(uint8_t type)
{
    struct gapm_start_advertise_cmd_patch *cmd = AHI_MSG_ALLOC(GAPM_START_ADVERTISE_CMD,TASK_ID_GAPM,gapm_start_advertise_cmd_patch);
    if(type == BEARER_ADV)
    {
        cmd->op.code = GAPM_ADV_NON_CONN;
        cmd->info.host.mode = GAP_BROADCASTER_MODE;
    }else
    {
        cmd->op.code = GAPM_ADV_UNDIRECT;
        cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
    }
    cmd->op.addr_src = GAPM_STATIC_ADDR;
    cmd->op.state = 0;
    cmd->intv_min = MESH_ADV_INTERVAL;
    cmd->intv_max = MESH_ADV_INTERVAL;
    cmd->channel_map = ADV_ALL_CHNLS_EN;
    cmd->info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    cmd->info.host.adv_data_len = air_op.env->buf.length;
    memcpy(cmd->info.host.adv_data,air_op.env->buf.data,ADV_DATA_BUF_SIZE);
    cmd->info.host.scan_rsp_data_len = 0;
    //cmd->info.host.scan_rsp_data
    //cmd->info.host.peer_addr
    osapp_msg_build_send(cmd,sizeof(struct gapm_start_advertise_cmd_patch));
}

static void mesh_scan_start()
{
    struct gapm_start_scan_cmd *cmd = AHI_MSG_ALLOC(GAPM_START_SCAN_CMD,TASK_ID_GAPM,gapm_start_scan_cmd);
    cmd->op.code = GAPM_SCAN_PASSIVE;
    cmd->op.addr_src = GAPM_GEN_NON_RSLV_ADDR;
    cmd->op.state = 0;
    cmd->interval = MESH_SCAN_INTERVAL;
    cmd->window = MESH_SCAN_INTERVAL;
    cmd->mode = GAP_OBSERVER_MODE;
    cmd->filt_policy = SCAN_ALLOW_ADV_ALL;
    cmd->filter_duplic = SCAN_FILT_DUPLIC_DIS;
    osapp_msg_build_send(cmd,sizeof(struct gapm_start_scan_cmd));
}

static void mesh_cancel_air_op()
{

    struct gapm_cancel_cmd *cmd = AHI_MSG_ALLOC(GAPM_CANCEL_CMD,TASK_ID_GAPM,gapm_cancel_cmd);
    cmd->operation = GAPM_CANCEL;
    osapp_msg_build_send(cmd,sizeof(struct gapm_cancel_cmd));
}

static void adv_timer_start()
{
    xTimerStart(advDurationTimer,portMAX_DELAY);
    uint8_t txIntvDelta = rand()%40;
    xTimerChangePeriod(nwTxIntvTimer,pdMS_TO_TICKS((nw_tx_state.interval_steps + 1)*10 + txIntvDelta),portMAX_DELAY);
}

static void mesh_adv_in_adv_and_scan_mode()
{
    ++air_op.adv_count;
    mesh_adv_start(air_op.env->type);
    adv_timer_start();
    if(air_op.env->callback)
    {
        void (*cb)() = air_op.env->callback;
        air_op.env->callback = NULL;
        cb();
    }
}



void user_app_mesh_test_init_done(void)
{
    air_op.adv_count = 0;
    co_list_init(&air_op.adv_env_list);
    mesh_stat = SCAN;
    mesh_scan_start();
}

static void mesh_tx(void *params)
{
    adv_env_t *tx = params;
    co_list_push_back(&air_op.adv_env_list,&tx->hdr);
    if(mesh_stat == SCAN)
    {
        mesh_cancel_air_op();
    }else
    {
        //LOG(LOG_LVL_INFO,"mesh_stat:%d\n",mesh_stat);
    }
}

static void mesh_stop(void *params)
{
    mesh_cancel_air_op();
}

static void mesh_on_air_op_canceled(void *params)
{
    uint8_t adv_or_scan = (uint32_t) params;
    switch(mesh_stat)
    {
    case ADV_AND_SCAN:
        if(adv_or_scan==GAPM_ADV_NON_CONN)
        {
            mesh_scan_start();
        }else
        {
            if(air_op.adv_count >= nw_tx_state.count + 1)
            {
                //FREE MEMORY
                if(DISPLAY_MALLOC_FREE) LOG(3,"F=0x%x\n",air_op.env);
                vPortFree(air_op.env);
                air_op.adv_count = 0;
                air_op.env = (adv_env_t *)co_list_pop_front(&air_op.adv_env_list);
                if(air_op.env)
                {
                    nw_tx_state = air_op.env->transmit_step_count;
                    mesh_adv_in_adv_and_scan_mode();
                }else
                {
                    mesh_stat = SCAN;
                    mesh_scan_start();
                }
            }else
            {
                mesh_adv_in_adv_and_scan_mode();    
            }
        }
        break;
    case SCAN:
        mesh_stat = ADV_AND_SCAN;
        air_op.env = (adv_env_t *)co_list_pop_front(&air_op.adv_env_list);
        nw_tx_state = air_op.env->transmit_step_count;
        BX_ASSERT(air_op.env);
        mesh_adv_in_adv_and_scan_mode();
        break;
    default:
        LOG(LOG_LVL_WARN,"on_cancel,mesh_stat:%d\n",mesh_stat);
        break;
    }
}

static void meshTimerCallback( TimerHandle_t xTimer )
{
    mesh_queue_t stop = {
        .data = NULL,
        .event_type = MESH_STOP,
    };
    if(xQueueSend(meshQueue,&stop,0)!=pdTRUE)
    {
        BX_ASSERT(0);
    }

}



static void mesh_bearer_rx()
{
    adv_report_env_t *ptr = bx_ring_queue_glance(&adv_report_q,0);
    uint8_t ad_type = ptr->mesh_buf[1];
    uint8_t *bearer_data = &ptr->mesh_buf[2];
    uint8_t bearer_length = ptr->mesh_buf[0] - 1;
    log_mesh_received_data(adv_report_env.mesh_buf , adv_report_env.length);
    bearer_rx(ad_type,bearer_data,bearer_length);
    //dequeue
    taskENTER_CRITICAL();
    adv_report_env_t *ptr0 = bx_dequeue(&adv_report_q);
    bool bool_queue_empty = bx_ring_queue_empty(&adv_report_q);
    if(bool_queue_empty==false)
    {
        taskEXIT_CRITICAL();
        mesh_run(mesh_bearer_rx,portMAX_DELAY,false);
    }
    else
    {
        adv_report_queue_busy = 0;
        taskEXIT_CRITICAL();
    }
}

mesh_tx_buf_t *mesh_alloc_tx_adv_buf(uint8_t type)
{
    adv_env_t *env = pvPortMalloc(sizeof(adv_env_t));
    if(!env)
    {
        BX_ASSERT(0);
    }
    env->transmit_step_count = mesh_node.properties.network_transmit;
    env->type = type;
    if(DISPLAY_MALLOC_FREE) LOG(3,"M=0x%x\n",env);
    return &env->buf;
}

void mesh_send_tx_cmd(mesh_tx_buf_t * buf,void (*callback)())
{
    adv_env_t *tx = CONTAINER_OF(buf,adv_env_t,buf);
    tx->callback = callback;
    mesh_queue_t tx_cmd = {
        .data = tx,
        .event_type = MESH_TX,
    };
    if(xQueueSend(meshQueue,&tx_cmd,portMAX_DELAY)!=pdTRUE)
    {
        BX_ASSERT(0);
    }
}

void mesh_run(void (*cb)(),uint32_t xTicksToWait,bool inISR)
{
    mesh_queue_t send_cb = {
        .data = cb,
        .event_type = MESH_CALLBACK,
    };
    if(inISR)
    {
        if(xQueueSendFromISR(meshQueue,&send_cb,NULL)!=pdTRUE)
        {
            BX_ASSERT(0);
        }
    }else
    {
        if(xQueueSend(meshQueue,&send_cb,xTicksToWait)!=pdTRUE)
        {
            BX_ASSERT(0);
        }
    }
}

void mesh_task(void *params)
{
    meshQueue = xQueueCreate(MESH_QUEUE_LENGTH,sizeof(mesh_queue_t));
    BX_ASSERT(meshQueue!=NULL);
    advDurationTimer = xTimerCreate("advDurationTimer",pdMS_TO_TICKS(MESH_ADV_DURATION),pdFALSE,(void *)0,meshTimerCallback);
    nwTxIntvTimer = xTimerCreate("nwTxIntvTimer",1,pdFALSE,(void *)1,meshTimerCallback);
    
    BX_ASSERT(advDurationTimer!=NULL);
    BX_ASSERT(nwTxIntvTimer!=NULL);
    while(1)
    {
        mesh_queue_t queue_item;
        xQueueReceive(meshQueue,&queue_item,portMAX_DELAY);
        switch(queue_item.event_type)
        {
        case MESH_INIT:
            app_mesh_test_init();
            break;
        case MESH_TX:
            mesh_tx(queue_item.data);
            break;
        case MESH_STOP:
            mesh_stop(queue_item.data);
            break;
        case MESH_ON_AIR_OP_CANCELED:
            mesh_on_air_op_canceled(queue_item.data);
            break;
        case MESH_CALLBACK:
            {
                void(*callback)() = (void (*)())queue_item.data;
                callback();
            }
            break;
        default:
            LOG(LOG_LVL_ERROR,"unknown event_type:%d\n",queue_item.event_type);
            BX_ASSERT(0);
            break;
        }
    }
     
}

int32_t osapp_gapm_use_enc_block_cmd(uint8_t const *key,uint8_t const *data)
{
    struct gapm_use_enc_block_cmd *cmd = AHI_MSG_ALLOC(GAPM_USE_ENC_BLOCK_CMD,TASK_ID_GAPM,gapm_use_enc_block_cmd);
    cmd->operation = GAPM_USE_ENC_BLOCK;
    memcpy(cmd->operand_1,key,sizeof(cmd->operand_1));
    memcpy(cmd->operand_2,data,sizeof(cmd->operand_2));
    return osapp_msg_build_send(cmd,sizeof(struct gapm_use_enc_block_cmd));
}
    
static int32_t osapp_reset()
{
    struct gapm_reset_cmd *cmd = AHI_MSG_ALLOC(GAPM_RESET_CMD,TASK_ID_GAPM,gapm_reset_cmd);
    cmd->operation = GAPM_RESET;
    return osapp_msg_build_send(cmd, sizeof(struct gapm_reset_cmd));
}
static void unresolvable_addr_generate(uint8_t *dst)
{
    uint32_t addr_low = co_rand_word();
    uint16_t addr_high = co_rand_hword();
    memcpy(dst,&addr_low,sizeof(addr_low));
    memcpy(dst+sizeof(addr_low),&addr_high,sizeof(addr_high));
    dst[5]&=0x3f; //set two MSB to 0
}
static int32_t osapp_set_dev_config()
{
    struct gapm_set_dev_config_cmd* cmd = AHI_MSG_ALLOC(GAPM_SET_DEV_CONFIG_CMD,TASK_ID_GAPM,gapm_set_dev_config_cmd);
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_ALL;
    cmd->renew_dur = 0;
    unresolvable_addr_generate(cmd->addr.addr);
    //cmd->irk
    cmd->addr_type = GAPM_CFG_ADDR_PUBLIC;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->gap_start_hdl = 0;
    cmd->gatt_start_hdl = 0;
    //cmd->att_cfg
    cmd->sugg_max_tx_octets = BLE_MIN_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MIN_TIME;
    cmd->max_mtu = GAP_MAX_LE_MTU;
    cmd->max_mps = GAP_MAX_LE_MTU;
    //cmd->max_nb_lecb
    //cmd->audio_cfg
    cmd->tx_pref_rates = GAP_RATE_LE_1MBPS;
    cmd->rx_pref_rates = GAP_RATE_LE_1MBPS;
    return osapp_msg_build_send(cmd, sizeof(struct gapm_set_dev_config_cmd) );
    
}

static void osapp_defualt_msg_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    LOG(LOG_LVL_INFO,"default handler,msgid: 0x%x, dest_id: 0x%x, src_id: 0x%x\n",msgid,dest_id,src_id);
}

static void osapp_gapm_use_enc_block_ind(ke_msg_id_t const msgid, struct gapm_use_enc_block_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    extern uint8_t *get_aes_128_result_buf(void);
    uint8_t *buf = get_aes_128_result_buf();
    reverse_strings(param->result, buf, AES_BLOCK_SIZE);
    mesh_run(aes_128_result_ind,portMAX_DELAY,false);
}

static void osapp_gapm_cmp_evt_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    struct gapm_cmp_evt const *cmp_evt = param;
    switch(cmp_evt->operation)
    {
    case GAPM_RESET:
        BX_ASSERT(cmp_evt->status==GAP_ERR_NO_ERROR);
        osapp_set_dev_config();
        break;
    case GAPM_SET_DEV_CONFIG:
        LOG(LOG_LVL_INFO,"set_dev_config_cmp\n");
        {
            mesh_queue_t init =
            {
                .data = NULL,
                .event_type = MESH_INIT,
            };
            if(xQueueSend(meshQueue,&init,0)!=pdTRUE)
            {
                BX_ASSERT(0);
            }
        }
        break;
    case GAPM_ADV_NON_CONN:
    case GAPM_SCAN_PASSIVE:
        if(cmp_evt->status == GAP_ERR_CANCELED)
        {
            mesh_queue_t on_cancel={
                .data = (void *)cmp_evt->operation,
                .event_type = MESH_ON_AIR_OP_CANCELED,
            };
            if(xQueueSend(meshQueue,&on_cancel,0)!=pdTRUE)
            {
                BX_ASSERT(0);
            }
        }
        break;
    case GAPM_USE_ENC_BLOCK:
        //LOG(LOG_LVL_INFO,"gapm_cmp_evt: use_enc_block\n");
        break;
    default:
        LOG(LOG_LVL_WARN,"gapm_cmp_evt operation:0x%x\n",cmp_evt->operation);
        break;
    }
}

static uint8_t const *get_mesh_adv_data_ptr(uint8_t const *buf,uint8_t length)
{
    uint8_t const *ptr;
    uint8_t ad_length;
    for(ptr=buf,ad_length=ptr[0]; ptr-buf<length; ptr += ad_length+1,ad_length=ptr[0])
    {
        uint8_t ad_type = ptr[1];
        if(ad_type==MESH_PROVISIONING_AD_TYPE||ad_type==MESH_MESSAGE_AD_TYPE||ad_type==MESH_BEACON_AD_TYPE)
        {
            return ptr;
        }
    }
    return NULL;
}





void mesh_flush_msg_cache(void)
{
    memset(mesh_msg_cache , 0 , sizeof(adv_report_env_t) * MESH_MSG_CACHE_LENGTH);
    mesh_msg_cache_wr_index = 0;
    mesh_flush_beacon_msg_cache();
}


bool check_exist_in_mesh_msg_cache(void)
{
    uint8_t i=0;
    bool exist_in_cache = false;
    for(i=0;i<MESH_MSG_CACHE_LENGTH;i++)
    {
        if(memcmp(adv_report_env.mesh_buf , mesh_msg_cache[i].mesh_buf , adv_report_env.length) == 0)
        {
            exist_in_cache = true;
            break;
        }
    }
    if(exist_in_cache == false)
    {
        mesh_msg_cache_wr_index ++;
        if(mesh_msg_cache_wr_index >= MESH_MSG_CACHE_LENGTH) mesh_msg_cache_wr_index = 0;
        mesh_msg_cache[mesh_msg_cache_wr_index] = adv_report_env;
    }
    return exist_in_cache;
}



static void osapp_gapm_adv_report_ind_handler(ke_msg_id_t const msgid, struct gapm_adv_report_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    if(param->report.evt_type!=ADV_NONCONN_UNDIR)
    {
        //LOG(LOG_LVL_INFO,"not non-conn adv\n");
        return;
    }
    uint8_t const *mesh_data_ptr = get_mesh_adv_data_ptr(param->report.data,param->report.data_len);
    if(mesh_data_ptr)
    {
        uint8_t mesh_data_length = param->report.data_len + param->report.data - mesh_data_ptr;
        adv_report_env.length = mesh_data_length ;
        memcpy(adv_report_env.mesh_buf,mesh_data_ptr,mesh_data_length);
        
        if(check_exist_in_mesh_msg_cache() == false)
        {
            //add to queue
            taskENTER_CRITICAL();
                bool bool_queue_full = bx_ring_queue_full(&adv_report_q);
            taskEXIT_CRITICAL();
            if(bool_queue_full)
            {
                LOG(3,"adv_report_q full!\n");
                BX_ASSERT(0);
            }
            adv_report_env_t *ptr = bx_enqueue_position(&adv_report_q);
            memcpy(ptr->mesh_buf , adv_report_env.mesh_buf , mesh_data_length);
            ptr->length = adv_report_env.length;
            taskENTER_CRITICAL();
            bx_enqueue_nocopy(&adv_report_q);
            //execute
            if(adv_report_queue_busy == 0)
            {
                adv_report_queue_busy = 1;//make sure change state quickly.
                taskEXIT_CRITICAL();
                mesh_run(mesh_bearer_rx,portMAX_DELAY,false);
            }
            else
            {
                taskEXIT_CRITICAL();
            }
        }
        else
        {
            LOG(LOG_LVL_INFO,".");
        }
    }
}

static void osapp_device_ready_ind_handler(ke_msg_id_t const msgid, void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    //reset cmd
    LOG(LOG_LVL_INFO,"Device Ready\n");
    osapp_reset();
}

static const osapp_msg_handler_table_t handler_table[]=
{
        [0] =   {KE_MSG_DEFAULT_HANDLER,(osapp_msg_handler_t)osapp_defualt_msg_handler},
                {GAPM_ADV_REPORT_IND,(osapp_msg_handler_t)osapp_gapm_adv_report_ind_handler},
                {GAPM_CMP_EVT,(osapp_msg_handler_t)osapp_gapm_cmp_evt_handler},
                {GAPM_USE_ENC_BLOCK_IND,(osapp_msg_handler_t)osapp_gapm_use_enc_block_ind},
                {GAPM_DEVICE_READY_IND,(osapp_msg_handler_t)osapp_device_ready_ind_handler},
};
const osapp_msg_handler_info_t handler_info = ARRAY_INFO(handler_table);

static const task_table_t mesh_task_table[]=
{
    {true,"MESH_TASK",OS_PRIORITY_APP_TASK,MESH_TASK_STACK_SIZE,NULL,mesh_task,&handler_mesh_task},
#ifdef OSAPP_UART_LOG_TEST
	{true,"UARTLOG_TASK",OS_PRIORITY_UART_LOG_TASK,UART_LOG_TASK_STACK_SIZE,NULL,uart_log_task,&handler_uart_log_task},
#ifdef MESH_TEST_UART_PROVISION
	{true,"UARTPROV_TASK",OS_PRIORITY_UART_PROV_TASK,UART_PROV_TASK_STACK_SIZE,NULL,uart_prov_task,&handler_uart_prov_task},
#endif/* MESH_TEST_UART_PROVISION */
#endif/* OSAPP_UART_LOG_TEST */

};
const task_table_info_t extra_task_table_info = ARRAY_INFO(mesh_task_table);
#endif
