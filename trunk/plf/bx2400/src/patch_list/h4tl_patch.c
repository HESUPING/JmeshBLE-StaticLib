#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "patch.h"
#include "bx_dbg.h"
#include "log.h"
#include "ahi.h"
#include "rwip.h"
#include "periph_mngt.h"
#define RX_TMP_BUFF_SIZE     AHI_RESET_MSG_LEN

#define WR_MEM_CMD 0x06
#define RD_MEM_CMD 0x07
#define SLEEP_EN_CMD 0x08
#define ADDR_SIZE 4
#define VAL_SIZE 4

///H4TL RX states
enum H4TL_STATE_RX
{
    ///H4TL RX Start State - receive message type
    H4TL_STATE_RX_START,
    ///H4TL RX Header State - receive message header
    H4TL_STATE_RX_HDR,
    ///H4TL RX Header State - receive (rest of) message payload
    H4TL_STATE_RX_PAYL,
    ///H4TL RX Out Of Sync state - receive message type
    H4TL_STATE_RX_OUT_OF_SYNC
};

/// H4TL Environment context structure
struct h4tl_env_tag
{
    /// pointer to External interface api
    const struct rwip_eif_api* ext_if;
    ///Pointer to space reserved for received payload.
    uint8_t *curr_payl_buff;
    ///TX callback for indicating the end of transfer
    void (*tx_callback)(void);
    /// Ensure that array is 32bits alligned
    /// Latest received message header, or used to receive a message alowing to exit from out of sync
    uint8_t rx_buf[RX_TMP_BUFF_SIZE];

    ///Rx state - can be receiving message type, header, payload or error
    uint8_t rx_state;
    ///Tx state - either transmitting, done or error.
    uint8_t tx_state;
    ///Latest received message type: CMD/EVT/ACL.
    uint8_t rx_type;
    /// Transport layer type
    uint8_t tl_type;
};

struct rwip_env_tag
{
    /// Power_up delay
    uint32_t lp_cycle_wakeup_delay;
    /// Contains sleep duration accumulated timing error
    uint32_t sleep_acc_error;
    /// Duration of sleep and wake-up algorithm (depends on CPU speed) expressed in us.
    uint16_t sleep_algo_dur;
    /// Prevent sleep bit field
    uint16_t prevent_sleep;
    /// Sleep algorithm enabled
    bool sleep_enable;
    /// External wake-up support
    bool     ext_wakeup_enable;
};

typedef void (*h4tl_read_hdr_fp)(struct h4tl_env_tag* env, uint8_t len);
typedef void (*h4tl_read_payl_fp)(struct h4tl_env_tag* env, uint16_t len);
typedef void (*h4tl_read_start_fp)(struct h4tl_env_tag* env);

enum resp_status{
    RESP_OK,
    RESP_ERR,
};
typedef struct{
    uint8_t cmd;
    uint8_t status;
    uint8_t param_len;
    uint8_t param[];
}resp_msg_t;

#if defined(V4_ROM)
#define H4TL_PATCH_ADDR 0xa6ac
#define H4TL_RETURN_ADDR 0xa79f
#define H4TL_READ_HDR ((h4tl_read_hdr_fp)0xa605)
#define H4TL_READ_PAYL ((h4tl_read_payl_fp)0xa645)
#define H4TL_READ_START ((h4tl_read_start_fp)0xa661)

#elif defined(MP_ROM) 
#define H4TL_PATCH_ADDR 0xb0ac
#define H4TL_RETURN_ADDR 0xb19f
#define H4TL_READ_HDR ((h4tl_read_hdr_fp)0xb005)
#define H4TL_READ_PAYL ((h4tl_read_payl_fp)0xb045)
#define H4TL_READ_START ((h4tl_read_start_fp)0xb061)
#else
#error patch version not defined

#endif


extern uint8_t H4TL_PATCH(uint8_t);
static uint8_t custom_cmd_payl[VAL_SIZE];
static uint8_t resp_buff[10];

void rd_mem_rsp_done(void *dummy,uint8_t status)
{
    LOG(LOG_LVL_INFO,"rd_mem_rsp,status:%d\n",status);
    
}

void wr_mem_rsp_done(void *dummy,uint8_t status)
{
    LOG(LOG_LVL_INFO,"wr_mem_rsp,status:%d\n",status);
    
}

void uart0_write(uint8_t * bufptr, uint32_t size, void(* callback)(void *, uint8_t), void * dummy);

static void cmd_respond_ok(uint8_t cmd,uint8_t *data,uint8_t data_length,void (*callback) (void*,uint8_t))
{
    resp_msg_t *rsp_ptr = (resp_msg_t *)resp_buff;
    rsp_ptr->cmd = cmd;
    rsp_ptr->status = RESP_OK;
    rsp_ptr->param_len = data_length;
    if(data_length)
    {
        memcpy(rsp_ptr->param,data,rsp_ptr->param_len);
    }
    uart0_write((uint8_t *)rsp_ptr,sizeof(resp_msg_t)+rsp_ptr->param_len,callback,NULL);
                
}

uint32_t h4tl_patch_c(struct h4tl_env_tag* env,uint32_t lr_reg)
{
    bool dealt = false;
    switch(env->rx_state)
    {
    case H4TL_STATE_RX_START:
    {
        env->rx_type = env->rx_buf[RX_TMP_BUFF_SIZE-1];
        switch(env->rx_type)
        {
        case WR_MEM_CMD:
        case RD_MEM_CMD:
            H4TL_READ_HDR(env, ADDR_SIZE);
            dealt = true;
        break;
        case SLEEP_EN_CMD:
            rwip_sleep_enable_set(true);
            *(uint32_t *)&periph_domain_stat = 0;
            *(uint32_t *)&cpu_domain_stat = 0;
            dealt = true;
        default:
        break;
        }
    }
    break;
    case H4TL_STATE_RX_HDR:
    {
        switch(env->rx_type)
        {
        case WR_MEM_CMD:
            env->curr_payl_buff = custom_cmd_payl;
            H4TL_READ_PAYL(env, VAL_SIZE);
            dealt = true;
        break;
        case RD_MEM_CMD:
        {
            uint32_t *rd_addr;
            memcpy(&rd_addr,env->rx_buf,sizeof(rd_addr));
            uint32_t rd_val = *rd_addr;
            cmd_respond_ok(RD_MEM_CMD,(uint8_t *)&rd_val,sizeof(rd_val),rd_mem_rsp_done);
            H4TL_READ_START(env);
            dealt = true;
        }
        break;
        default:
        break;
        }
    }
    break;
    case H4TL_STATE_RX_PAYL:
    {
        uint32_t *wr_addr;
        uint32_t wr_val;
        switch(env->rx_type)
        {
        case WR_MEM_CMD:
        {
            memcpy(&wr_addr,env->rx_buf,sizeof(wr_addr));
            memcpy(&wr_val,env->curr_payl_buff,sizeof(wr_val));
            *wr_addr = wr_val;
            cmd_respond_ok(WR_MEM_CMD,NULL,0,wr_mem_rsp_done);
            H4TL_READ_START(env);
            dealt = true;           
        }
        break;
        case RD_MEM_CMD:
        {
            BX_ASSERT(0);
        }
        break;
        default:
        break;
        }
    }
    break;
    case H4TL_STATE_RX_OUT_OF_SYNC:
    {

    }
    break;
    default:
        BX_ASSERT(0);
    }
    if(dealt)
    {
        return H4TL_RETURN_ADDR;
    }else
    {
        return env->rx_state ? lr_reg : lr_reg + 0x1c;
    }
}

void set_h4tl_patch()
{
    uint32_t code = cal_patch_bl(H4TL_PATCH_ADDR,(uint32_t)H4TL_PATCH - 1);
    uint8_t patch_no;
    if(patch_alloc(&patch_no)==false)
    {
        BX_ASSERT(0);
    }    
    patch_entrance_exit_addr(patch_no,H4TL_PATCH_ADDR,code);
    PATCH_ENABLE(patch_no);
}
