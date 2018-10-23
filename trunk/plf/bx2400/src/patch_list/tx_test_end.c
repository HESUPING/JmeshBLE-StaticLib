#include <string.h>
#include "compiler.h"
#include "co_endian.h"
#include "co_error.h"
#include "ke_mem.h"
#include "reg_ble_em_rx_desc.h"
#include "reg_ble_em_tx_desc.h"
#include "reg_ble_em_cs.h"
#include "reg_blecore.h"
#include "llm.h"
#include "lld.h"
#if (HCI_PRESENT)
#include "hci.h"
#endif //(HCI_PRESENT)
#include "patch.h"
#include "bx_dbg.h"
void llm_util_chk_tst_mode_patch(void)
{
    //if the current state is not IDLE
    if((llm_le_env.test_mode.directtesttype != TEST_END) && (llm_le_env.test_mode.end_of_tst == true))
    {
        // structure type for the complete command event
        struct hci_test_end_cmd_cmp_evt *event;

        // allocate the complete event message
        event = KE_MSG_ALLOC(HCI_CMD_CMP_EVENT, 0, HCI_LE_TEST_END_CMD_OPCODE, hci_test_end_cmd_cmp_evt);

        llm_le_env.test_mode.end_of_tst = false;
        // enable the whitening
        ble_whit_dsb_setf(0);

        // Number_Of_Packets for a transmitter test is reported as NULL.
        if (llm_le_env.test_mode.directtesttype == TEST_TX)
        {
            event->nb_packet_received = ble_rftesttxstat_get();
        }
        else
        {
            event->nb_packet_received = ble_rxccmpktcnt0_get(LLD_ADV_HDL);
        }
        // set the env variable,
        llm_le_env.test_mode.directtesttype = TEST_END;
        // update the status
        event->status = CO_ERROR_NO_ERROR;
        // send the message
        hci_send_2_host(event);
        ke_msg_send_basic(LLM_STOP_IND, TASK_LLM, TASK_LLM);
    }
}
//#define PATCH_ON_V3
//#define PATCH_ON_V4
#define PATCH_ON_V5

#ifdef PATCH_ON_V3
void patch_tx_test_mode()
{
    uint32_t code = cal_patch_bl(0x00018f5c,(uint32_t)llm_util_chk_tst_mode_patch - 1);
    uint32_t *src_low = (uint32_t *)0x00018f5c;
//    uint32_t *src_high = (uint32_t *)0x191e8;
    uint8_t patch_no;
    if(patch_alloc(&patch_no)==false)
    {
        BX_ASSERT(0);
    }
    patch_entrance_exit_addr(patch_no,(uint32_t)src_low,code);
//    patch_entrance_exit_addr(1,(uint32_t)src_high,code&0xffff0000|*src_high&0xffff);
    patch_enable_set(1<<patch_no);
}
#elif defined PATCH_ON_V4
void patch_tx_test_mode()
{
    uint32_t code = cal_patch_bl(0x191e6,(uint32_t)llm_util_chk_tst_mode_patch - 1);
    uint32_t *src_low = (uint32_t *)0x191e4;
    uint32_t *src_high = (uint32_t *)0x191e8;
    uint8_t patch_no[2];
    if(patch_alloc(&patch_no[0])==false)
    {
        BX_ASSERT(0);
    }
    if(patch_alloc(&patch_no[1])==false)
    {
        BX_ASSERT(0);
    }
    patch_entrance_exit_addr(patch_no[0],(uint32_t)src_low,(code&0xffff)<<16|*src_low&0xffff);
    patch_entrance_exit_addr(patch_no[1],(uint32_t)src_high,(code&0xffff0000)>>16|*src_high&0xffff0000);
    patch_enable_set((1<<patch_no[0])|(1<<patch_no[1]));
}
#elif defined PATCH_ON_V5
void patch_tx_test_mode()
{
    uint32_t code = cal_patch_bl(0x19be6,(uint32_t)llm_util_chk_tst_mode_patch - 1);
    uint32_t *src_low = (uint32_t *)0x19be4;
    uint32_t *src_high = (uint32_t *)0x19be8;
    patch_entrance_exit_addr(0,(uint32_t)src_low,(code&0xffff)<<16|*src_low&0xffff);
    patch_entrance_exit_addr(1,(uint32_t)src_high,(code&0xffff0000)>>16|*src_high&0xffff0000);
    patch_enable_set(0x3);
}

#endif
