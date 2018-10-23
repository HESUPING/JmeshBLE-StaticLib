#ifndef __REG_SYSC_AWO_H__
#define __REG_SYSC_AWO_H__
#include "_reg_base_addr.h"

//clk_ctrl0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   clk_sel_abus :  1; /* 0: 0, clock select for abus:1'b0: clk_abus is from clk_32m1'b1: clk_abus is from clk_32k*/
        uint32_t                     reserved_2 :  3; /* 3: 1,                             NA*/
        uint32_t                  clk_sel_hbus0 :  3; /* 6: 4, clock select for hbus:3'b001: clk_hbus is from clk_32m3'b010: clk_hbus is from clk_pll/clk_pll_div/clk_32m_div3'b100: clk_hbus is from clk_32k*/
        uint32_t                     reserved_1 : 14; /*20: 7,                             NA*/
        uint32_t                wic_en_ack_sync :  1; /*21:21,                             NA*/
        uint32_t                     reserved_0 : 10; /*31:22,                             NA*/
    } bit_field;
} T_SYSC_AWO_CLK_CTRL0;

//clk_ctrl1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  clk_sel_hbus1 :  2; /* 1: 0, clock select control for clk_hbus*/
        uint32_t                     reserved_4 :  2; /* 3: 2,                             NA*/
        uint32_t                    clk_sel_ble :  1; /* 4: 4, clock select control for clk_ble:low means the clk_ble is from clk_hbus directlyhigh means the clk_ble is from a divide clock of clk_hbus*/
        uint32_t                     reserved_3 :  3; /* 7: 5,                             NA*/
        uint32_t           clk_div_pbus_para_up :  1; /* 8: 8, RWite 1 to this reg cause the register value invert. Toggle of the register indicates the update of the register clk_div_pbus_para_m1. this register must be toggled after clk_div_pbus_para_m1 changed.*/
        uint32_t                     reserved_2 :  3; /*11: 9,                             NA*/
        uint32_t              clk_div_ble_up_sw :  1; /*12:12, RWite 1 to this reg cause the register value invert. Toggle of the register indicates the update of the register clk_div_ble_para*_m1. this register must be toggled after clk_div_ble_para*_m1 changed.*/
        uint32_t                     reserved_1 :  3; /*15:13,                             NA*/
        uint32_t              clk_div_ble_by_hw :  1; /*16:16, high means clock divider parameter is selected by the harmonic function from clk_div_ble_para0_m1 and clk_div_para1_m1low means clock divider parameter of clk_ble is from control register: clk_div_ble_para0_m1*/
        uint32_t                     reserved_0 : 15; /*31:17,                             NA*/
    } bit_field;
} T_SYSC_AWO_CLK_CTRL1;

//clk_div_param
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           clk_div_hbus_para_m1 :  8; /* 7: 0, clock divide parameter, the output clock frequency is 1/(clk_div_hbus_para_m1+1) of the input clock frequency  */
        uint32_t           clk_div_pbus_para_m1 :  4; /*11: 8, clock divide parameter, the output clock frequency is 1/(clk_div_pbus_para_m1+1) of the input clock frequency  */
        uint32_t                     reserved_2 :  4; /*15:12,                             NA*/
        uint32_t           clk_div_ble_para0_m1 :  4; /*19:16, clock divide parameter, the output clock frequency is 1/(clk_div_ble_para0_m1+1) of the input clock frequency  */
        uint32_t                     reserved_1 :  4; /*23:20,                             NA*/
        uint32_t           clk_div_ble_para1_m1 :  4; /*27:24, clock divide parameter, the output clock frequency is 1/(clk_div_ble_para1_m1+1) of the input clock frequency  */
        uint32_t                     reserved_0 :  4; /*31:28,                             NA*/
    } bit_field;
} T_SYSC_AWO_CLK_DIV_PARAM;

//clk_gate
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              clkg_set_hbus_div :  1; /* 0: 0,                             NA*/
        uint32_t              clkg_clr_hbus_div :  1; /* 1: 1,                             NA*/
        uint32_t               clkg_set_ble_div :  1; /* 2: 2,                             NA*/
        uint32_t               clkg_clr_ble_div :  1; /* 3: 3,                             NA*/
        uint32_t                clkg_set_ble_lp :  1; /* 4: 4,                             NA*/
        uint32_t                clkg_clr_ble_lp :  1; /* 5: 5,                             NA*/
        uint32_t                   clkg_set_rtc :  1; /* 6: 6,                             NA*/
        uint32_t                   clkg_clr_rtc :  1; /* 7: 7,                             NA*/
        uint32_t                 clkg_set_touch :  1; /* 8: 8,                             NA*/
        uint32_t                 clkg_clr_touch :  1; /* 9: 9, RWite 1 to clkg*_clr_* clear the corresponding clock gate control regRWite 1 to clkg*_set_* set the corresponding clock gate control reg*/
        uint32_t                     reserved_0 : 22; /*31:10,                             NA*/
    } bit_field;
} T_SYSC_AWO_CLK_GATE;

//sft_rst
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 srst_set_all_n :  1; /* 0: 0,                             NA*/
        uint32_t                 srst_clr_all_n :  1; /* 1: 1,                             NA*/
        uint32_t                 srst_set_rtc_n :  1; /* 2: 2,                             NA*/
        uint32_t                 srst_clr_rtc_n :  1; /* 3: 3,                             NA*/
        uint32_t                 srst_set_ble_n :  1; /* 4: 4,                             NA*/
        uint32_t                 srst_clr_ble_n :  1; /* 5: 5,                             NA*/
        uint32_t               srst_set_touch_n :  1; /* 6: 6,                             NA*/
        uint32_t               srst_clr_touch_n :  1; /* 7: 7,                             NA*/
        uint32_t              srst_set_ble_lp_n :  1; /* 8: 8,                             NA*/
        uint32_t              srst_clr_ble_lp_n :  1; /* 9: 9,                             NA*/
        uint32_t                     reserved_0 : 22; /*31:10,                             NA*/
    } bit_field;
} T_SYSC_AWO_SFT_RST;

//pmu_ctrl0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                         pmu_en :  1; /* 0: 0,        pmu enable, high active*/
        uint32_t                     reserved_6 :  3; /* 3: 1,                             NA*/
        uint32_t                     cpu_ret_en :  1; /* 4: 4, CPU retention enable. High means all of the regs in the ARM cortexM0+ is retentioned when the system is in the deep sleep mode, and then when system wakeup, the program continuous from the position where it sleeps*/
        uint32_t                     reserved_5 :  3; /* 7: 5,                             NA*/
        uint32_t                 pd_cpu_voltage :  1; /* 8: 8, cpu power domain voltage. The voltage of CPU power domain can only be changed during deep mode of the system. before the system wakeup from  the deep sleep mode, the voltage of cpu power domain is set to the value indicated by this reg. high means 1.1V and low means 0.9V*/
        uint32_t                     reserved_4 :  3; /*11: 9,                             NA*/
        uint32_t                pd_sram_lslp_en :  1; /*12:12, SRAM light sleep enable, high active. High means the SRAMs are in light sleep mode druing system deep sleep*/
        uint32_t                     reserved_3 :  3; /*15:13,                             NA*/
        uint32_t              nml_ldo_force_sel :  1; /*16:16, high active, high force the normal ldo to be selected during sleep mode*/
        uint32_t                     reserved_2 :  3; /*19:17,                             NA*/
        uint32_t               nml_ldo_force_on :  1; /*20:20, high active, high force the normal ldo power on during sleep mode*/
        uint32_t                     reserved_1 :  3; /*23:21,                             NA*/
        uint32_t                 rc32m_force_on :  1; /*24:24, high active, high force the 32MHz RC power on during sleep mode*/
        uint32_t                     reserved_0 :  7; /*31:25,                             NA*/
    } bit_field;
} T_SYSC_AWO_PMU_CTRL0;

//pmu_ctrl1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              pd_sram_prw_dn_en :  7; /* 6: 0, sram power down enable, each bit represents one sram of the system. high means the corresponding sram will be power down during the following power down flow(WFI flow or software wakeup flow)*/
        uint32_t                     reserved_1 :  1; /* 7: 7,                             NA*/
        uint32_t              pd_sram_prw_up_en :  7; /*14: 8, sram power up enable, each bit represents one sram of the system. high means the corresponding sram will be power up during the following power up flow(deep sleep wakeup or software wakeup flow)*/
        uint32_t                     reserved_0 : 17; /*31:15,                             NA*/
    } bit_field;
} T_SYSC_AWO_PMU_CTRL1;

//pmu_ctrl2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    pmu_fsm_dly :  4; /* 3: 0, PMU fsm delay in 32MHz cycle which indicates the delay of general power up/down steps including: reset set/clear, clock gate set/clear, retention load/store, isolation enable/disable*/
        uint32_t                     reserved_2 :  4; /* 7: 4,                             NA*/
        uint32_t                cpu_ldo_stb_dly :  8; /*15: 8, CPU ldo stable delay in 32MHz cycle, when the cpu ldo is powered up*/
        uint32_t                nml_ldo_stb_dly :  6; /*21:16, normal ldo stable delay in 32KHz cycle when the normal ldo is powered up*/
        uint32_t                     reserved_1 :  2; /*23:22,                             NA*/
        uint32_t                     clk_sw_dly :  4; /*27:24, the latency of the clock switching between the 32KHz clock and the 32MHz clock of abus(in cycle number)*/
        uint32_t                     reserved_0 :  4; /*31:28,                             NA*/
    } bit_field;
} T_SYSC_AWO_PMU_CTRL2;

//pmu_ctrl3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     ldo_sw_dly :  4; /* 3: 0, switch delay between normal ldo and sleep ldo in 32KHz cycle*/
        uint32_t                     reserved_1 :  4; /* 7: 4,                             NA*/
        uint32_t                  rc32m_stb_dly :  6; /*13: 8, 32MHz RC stable delay in 32KHz cycle*/
        uint32_t                     reserved_0 : 18; /*31:14,                             NA*/
    } bit_field;
} T_SYSC_AWO_PMU_CTRL3;

//ana_clk_ctrl
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     xtal32m_en :  1; /* 0: 0, 32MHz xtal enable, high active*/
        uint32_t                     reserved_6 :  3; /* 3: 1,                             NA*/
        uint32_t                  clk32m_sel_rc :  1; /* 4: 4, clock select for 32MHz, 1 select 32M RC, 0 select 32M xtal*/
        uint32_t                     reserved_5 :  3; /* 7: 5,                             NA*/
        uint32_t                       rc32k_en :  1; /* 8: 8,   32KHz RC enable, high active*/
        uint32_t                     reserved_4 :  3; /*11: 9,                             NA*/
        uint32_t                     xtal32k_en :  1; /*12:12, 32KHz xtal enable, high active*/
        uint32_t                     reserved_3 :  3; /*15:13,                             NA*/
        uint32_t                clk32k_sel_xtal :  1; /*16:16, clock select for 32KHz, 1 select 32K xtal, 0 select 32K RC*/
        uint32_t                     reserved_2 :  3; /*19:17,                             NA*/
        uint32_t                  rc32m_prw_set :  1; /*20:20, RWite 1 to the reg will power up the 32MHz RC*/
        uint32_t                     reserved_1 :  3; /*23:21,                             NA*/
        uint32_t                  rc32m_prw_clr :  1; /*24:24, RWite 1 to the reg will power down the 32MHz RC*/
        uint32_t                     reserved_0 :  7; /*31:25,                             NA*/
    } bit_field;
} T_SYSC_AWO_ANA_CLK_CTRL;

//pmu_start
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                pd_sram_iso_set :  1; /* 0: 0,                             NA*/
        uint32_t                     reserved_3 :  3; /* 3: 1,                             NA*/
        uint32_t                pd_sram_iso_clr :  1; /* 4: 4,                             NA*/
        uint32_t                     reserved_2 :  3; /* 7: 5,                             NA*/
        uint32_t                pd_sram_prw_set :  1; /* 8: 8,                             NA*/
        uint32_t                     reserved_1 :  3; /*11: 9,                             NA*/
        uint32_t                pd_sram_prw_clr :  1; /*12:12, the soft ware flow of power up/down for the system srams is controlled by these four regs. pd_sram_pRW_clr power off the system sram. Pd_sram_pRW_set power up the system sram. Pd_sram_iso_clr dis-isolate the output of system sram. Pd_sram_iso_set isolate the output of the system sram. the four regs are RWite only and only then RWite 1 to the regs enable the function. the power up flow is RWite 1 to the pd_sram_pRW_set and then RWite 1 to the pd_sram_iso_clr. the power down flow is RWite 1 to the pd_sram_iso_set and then RWite 1 to the pd_sram_pRW_clr*/
        uint32_t                     reserved_0 : 19; /*31:13,                             NA*/
    } bit_field;
} T_SYSC_AWO_PMU_START;

//pin_share_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  8; /* 7: 0,                             NA*/
        uint32_t                    ext_intr_en :  8; /*15: 8,        refer to pin_share.docx*/
        uint32_t                     pmu_dbg_en :  8; /*23:16,        refer to pin_share.docx*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_PIN_SHARE_EN;

//dummy_ctrl
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     dummy_ctrl :  4; /* 3: 0,   dummy registers for software*/
        uint32_t                     reserved_0 : 28; /*31: 4,                             NA*/
    } bit_field;
} T_SYSC_AWO_DUMMY_CTRL;

//sram_ctrl
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   tgt_sram_rme :  1; /* 0: 0, rme of sram. Sram parameter is only changed to the value of this reg when system is in deep sleep mode. */
        uint32_t                     reserved_4 :  3; /* 3: 1,                             NA*/
        uint32_t                    tgt_sram_rm :  4; /* 7: 4, rm of sram. Sram parameter is only changed to the value of this reg when system is in deep sleep mode. */
        uint32_t                    tgt_sram_wa :  3; /*10: 8, wa of sram. Sram parameter is only changed to the value of this reg when system is in deep sleep mode. */
        uint32_t                     reserved_3 :  1; /*11:11,                             NA*/
        uint32_t                    tgt_sram_ra :  2; /*13:12, ra of sram. Sram parameter is only changed to the value of this reg when system is in deep sleep mode. */
        uint32_t                     reserved_2 :  2; /*15:14,                             NA*/
        uint32_t                tgt_sram_wpulse :  3; /*18:16, wpulse of sram. Sram parameter is only changed to the value of this reg when system is in deep sleep mode. */
        uint32_t                     reserved_1 :  1; /*19:19,                             NA*/
        uint32_t               sram_ret_voltage :  4; /*23:20, the voltage of the sleep ldo for the srams is determined by this reg*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_SRAM_CTRL;

//intr_ctrl
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  ext_intr_edge :  8; /* 7: 0, high means the external interrupt is triggered on the rising edge of the external interrupt pin. Low means triggered by the high of the external interrupt pin*/
        uint32_t                   ext_intr_pol :  8; /*15: 8, external interrupt signal polarity, high means the input external interrupt signal is inverted before used to trigger the external interrupt*/
        uint32_t                   ext_intr_msk :  8; /*23:16, interrupt mask for external interrupt, 0 means no interrupt to the system*/
        uint32_t                ble_lp_intr_msk :  2; /*25:24, interrupt mask for ble lp interrupt, 0 means no interrupt to the system*/
        uint32_t                 touch_intr_msk :  1; /*26:26, interrupt mask for touch interrupt, 0 means no interrupt to the system*/
        uint32_t                     reserved_0 :  5; /*31:27,                             NA*/
    } bit_field;
} T_SYSC_AWO_INTR_CTRL;

//intr_clr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 16; /*15: 0,                             NA*/
        uint32_t                   ext_intr_clr :  8; /*23:16,       external interrupt clear*/
        uint32_t                ble_lp_intr_clr :  2; /*25:24,         ble_lp interrupt clear*/
        uint32_t                 touch_intr_clr :  1; /*26:26,          touch interrupt clear*/
        uint32_t                     reserved_0 :  5; /*31:27,                             NA*/
    } bit_field;
} T_SYSC_AWO_INTR_CLR;

//intr_stat
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  ext_intr_stat :  8; /* 7: 0,      masked external interrupt*/
        uint32_t               ble_lp_intr_stat :  2; /* 9: 8,        masked ble_lp interrupt*/
        uint32_t                touch_intr_stat :  1; /*10:10,         masked touch interrupt*/
        uint32_t                     reserved_1 :  1; /*11:11,                             NA*/
        uint32_t                   ext_intr_raw :  8; /*19:12, raw interrupt of external interrupt*/
        uint32_t                ble_lp_intr_raw :  2; /*21:20,        raw interrupt of ble_lp*/
        uint32_t                 touch_intr_raw :  1; /*22:22,         raw interrupt of touch*/
        uint32_t                     reserved_0 :  1; /*23:23,                             NA*/
        uint32_t              ext_intr_trig_val :  8; /*31:24,   external interrupt pin level*/
    } bit_field;
} T_SYSC_AWO_INTR_STAT;

//touch_ctrl0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       touch_en :  1; /* 0: 0, continuous scan of the touch controller*/
        uint32_t                     reserved_1 :  3; /* 3: 1,                             NA*/
        uint32_t                   touch_single :  1; /* 4: 4, single scan enable of the touch controller*/
        uint32_t                     reserved_0 :  3; /* 7: 5,                             NA*/
        uint32_t                      touch_itv : 16; /*23: 8, the cycle number(minus 1) of the 32KHz clock between two continous scan of the touch ADC. The actual cycle number is touch_itv+1*/
        uint32_t                touch_ready_idx :  8; /*31:24, the number of touch adc data which will be dropped before the data is captured. 0 means no data is dropped and all of the data from the adc is valid*/
    } bit_field;
} T_SYSC_AWO_TOUCH_CTRL0;

//touch_ctrl1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 touch_scan_num : 10; /* 9: 0, the valid data number(minus 1) from the touch adc during one times of touch scan. The actual number is touch_scan_num+1*/
        uint32_t                     reserved_1 :  6; /*15:10,                             NA*/
        uint32_t                 touch_scan_dly : 10; /*25:16, the cycle number(minus 1) of the 32kHz clock for the time of single scan process, the actual cycle number is touch_scan_dly+1*/
        uint32_t                     reserved_0 :  6; /*31:26,                             NA*/
    } bit_field;
} T_SYSC_AWO_TOUCH_CTRL1;

//touch_ctrl2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      touch_thr : 20; /*19: 0, touch interrupt threshold value. When one time of scan finishes and the scan output value is bigger than the threshold, then the touch interrupt will be triggerred.*/
        uint32_t             touch_clk_div_para :  4; /*23:20,  touch clock divider parameter*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_TOUCH_CTRL2;

//touch_out
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      touch_val : 20; /*19: 0, the output value of the touch scan*/
        uint32_t                     reserved_1 :  4; /*23:20,                             NA*/
        uint32_t                      touch_fsm :  2; /*25:24,                      touch FSM*/
        uint32_t                     reserved_0 :  6; /*31:26,                             NA*/
    } bit_field;
} T_SYSC_AWO_TOUCH_OUT;

//rf_reg_0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_0 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_0;

//rf_reg_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_1 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_1;

//rf_reg_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_2 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_2;

//rf_reg_3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_3 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_3;

//rf_reg_4
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_4 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_4;

//rf_reg_5
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_5 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_5;

//rf_reg_6
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_6 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_6;

//rf_reg_7
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_7 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_7;

//rf_reg_8
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_8 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_8;

//rf_reg_9
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_9 : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_9;

//rf_reg_a
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_a : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_A;

//rf_reg_b
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_b : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_B;

//rf_reg_c
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_c : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_C;

//rf_reg_d
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_d : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_D;

//rf_reg_e
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_e : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_E;

//rf_reg_f
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_f : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_F;

//rf_reg_rd
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    i_rf_reg_ro : 32; /*31: 0,                             NA*/
    } bit_field;
} T_SYSC_AWO_RF_REG_RD;

//prw_pwm_wid0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 prw_pwm0_wid_l : 16; /*15: 0, power pwm0 low pulse width in 32KHz clock*/
        uint32_t                 prw_pwm0_wid_h : 16; /*31:16, power pwm0 high pulse width in 32KHz clock*/
    } bit_field;
} T_SYSC_AWO_PRW_PWM_WID0;

//prw_pwm_wid1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 prw_pwm1_wid_l : 16; /*15: 0, power pwm1 low pulse width in 32KHz clock*/
        uint32_t                 prw_pwm1_wid_h : 16; /*31:16, power pwm1 high pulse width in 32KHz clock*/
    } bit_field;
} T_SYSC_AWO_PRW_PWM_WID1;

//prw_pwm_wid2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 prw_pwm2_wid_l : 16; /*15: 0, power pwm2 low pulse width in 32KHz clock*/
        uint32_t                 prw_pwm2_wid_h : 16; /*31:16, power pwm2 high pulse width in 32KHz clock*/
    } bit_field;
} T_SYSC_AWO_PRW_PWM_WID2;

//prw_pwm_ctrl
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  prw_pwm0_fc_h :  1; /* 0: 0, power pwm0 output force high, high active, high means the output is forced to high*/
        uint32_t                     reserved_5 :  3; /* 3: 1,                             NA*/
        uint32_t                    prw_pwm0_en :  1; /* 4: 4, power pwm0 enable, high active*/
        uint32_t                     reserved_4 :  3; /* 7: 5,                             NA*/
        uint32_t                  prw_pwm1_fc_h :  1; /* 8: 8, power pwm1 output force high, high active, high means the output is forced to high*/
        uint32_t                     reserved_3 :  3; /*11: 9,                             NA*/
        uint32_t                    prw_pwm1_en :  1; /*12:12, power pwm1 enable, high active*/
        uint32_t                     reserved_2 :  3; /*15:13,                             NA*/
        uint32_t                  prw_pwm2_fc_h :  1; /*16:16, power pwm2 output force high, high active, high means the output is forced to high*/
        uint32_t                     reserved_1 :  3; /*19:17,                             NA*/
        uint32_t                    prw_pwm2_en :  1; /*20:20, power pwm2 enable, high active*/
        uint32_t                     reserved_0 : 11; /*31:21,                             NA*/
    } bit_field;
} T_SYSC_AWO_PRW_PWM_CTRL;

//boot_mode
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      boot_mode :  2; /* 1: 0, low of bit0 means boot from qspi, high of bit0 means boot from uart0low of bit1 means the boot IO voltage is 1.8v, high of bit1 means the  boot IO voltage is 3.3V*/
        uint32_t                     reserved_0 : 30; /*31: 2,                             NA*/
    } bit_field;
} T_SYSC_AWO_BOOT_MODE;

//awo_gpo_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     awo_gpo_en : 24; /*23: 0, awo_gpo pin share enable, high active*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_AWO_GPO_EN;

//awo_gpo
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        awo_gpo : 24; /*23: 0, general output of awo, this is the PGIO function implemented in AWO with only output function*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_AWO_GPO;

//gpio_ds0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       gpio_ds0 : 24; /*23: 0, bit 0 of the DS(drive strength) of the Ios in the AWO power domain.Each IO has two bits inputs for drive strength control(DS0 and DS1) and there are altogether 24 Ios in the AWO power domain. Each bit of this control register is connect the the DS0 input of the IOs in the AWO power domain*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_GPIO_DS0;

//gpio_ds1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       gpio_ds1 : 24; /*23: 0, bit 1 of the DS(drive strength) of the Ios in the AWO power domain.Each IO has two bits inputs for drive strength control(DS0 and DS1) and there are altogether 24 Ios in the AWO power domain. Each bit of this control register is connect the the DS1 input of the IOs in the AWO power domain*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_GPIO_DS1;

//gpio_ie
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        gpio_ie : 24; /*23: 0, input enable of the IO, high active*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_GPIO_IE;

//gpio_is
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        gpio_is : 24; /*23: 0, input schmitt enable of the IO, high active*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_GPIO_IS;

//gpio_pe
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        gpio_pe : 24; /*23: 0, pull enable of the IO, high active*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_GPIO_PE;

//gpio_ps
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        gpio_ps : 24; /*23: 0, pull select of the IO, if gpio_h_pe is high and gpio_h_ps is high, then the IO is pulled up. if gpio_h_pe is high and gpio_h_ps is low, then the IO is pulled down.*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_AWO_GPIO_PS;

//prw_stat0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    pd_sram_rme :  1; /* 0: 0,                    rme of sram*/
        uint32_t                     reserved_4 :  3; /* 3: 1,                             NA*/
        uint32_t                     pd_sram_rm :  4; /* 7: 4,                     rm of sram*/
        uint32_t                     pd_sram_wa :  3; /*10: 8,                     wa of sram*/
        uint32_t                     reserved_3 :  1; /*11:11,                             NA*/
        uint32_t                     pd_sram_ra :  2; /*13:12,                     ra of sram*/
        uint32_t                     reserved_2 :  2; /*15:14,                             NA*/
        uint32_t                 pd_sram_wpulse :  3; /*18:16,               wpulse of sram. */
        uint32_t                     reserved_1 :  1; /*19:19,                             NA*/
        uint32_t            pd_cpu_voltage_stat :  1; /*20:20, cpu domain voltage, 1 means 1.1V and 0 means 0.9V*/
        uint32_t                     reserved_0 : 11; /*31:21,                             NA*/
    } bit_field;
} T_SYSC_AWO_PRW_STAT0;

//prw_stat1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t            pd_sram_prw_on_stat :  7; /* 6: 0, SRAM power state, high means power up*/
        uint32_t                     reserved_0 : 25; /*31: 7,                             NA*/
    } bit_field;
} T_SYSC_AWO_PRW_STAT1;

//Registers Mapping to the same address
typedef union
{
    T_SYSC_AWO_TOUCH_CTRL2           touch_ctrl2; /*RW   ,NA                            */
    T_SYSC_AWO_TOUCH_OUT             touch_out; /*RO   ,NA                            */
}T_SYSC_AWO_TOUCH_CTRL2_TOUCH_OUT;

typedef struct
{
    volatile            T_SYSC_AWO_CLK_CTRL0                      clk_ctrl0; /*  0x0,    RW, 0x00000010,                             NA*/
    volatile            T_SYSC_AWO_CLK_CTRL1                      clk_ctrl1; /*  0x4,    RW, 0x00000000,                             NA*/
    volatile        T_SYSC_AWO_CLK_DIV_PARAM                  clk_div_param; /*  0x8,    RW, 0x00000000,                             NA*/
    volatile                        uint32_t                     reserved_0;
    volatile             T_SYSC_AWO_CLK_GATE                       clk_gate; /* 0x10,    RW, 0x000003FF,                             NA*/
    volatile              T_SYSC_AWO_SFT_RST                        sft_rst; /* 0x14,    RW, 0x000003FF,                             NA*/
    volatile                        uint32_t                  reserved_1[2];
    volatile            T_SYSC_AWO_PMU_CTRL0                      pmu_ctrl0; /* 0x20,    RW, 0x00001111,                             NA*/
    volatile            T_SYSC_AWO_PMU_CTRL1                      pmu_ctrl1; /* 0x24,    RW, 0x00000000,                             NA*/
    volatile            T_SYSC_AWO_PMU_CTRL2                      pmu_ctrl2; /* 0x28,    RW, 0x0A10A008,                             NA*/
    volatile                        uint32_t                     reserved_2;
    volatile            T_SYSC_AWO_PMU_CTRL3                      pmu_ctrl3; /* 0x30,    RW, 0x00001A05,                             NA*/
    volatile         T_SYSC_AWO_ANA_CLK_CTRL                   ana_clk_ctrl; /* 0x34,    RW, 0x00000101,                             NA*/
    volatile            T_SYSC_AWO_PMU_START                      pmu_start; /* 0x38,    RW, 0x00000001,                             NA*/
    volatile                        uint32_t                     reserved_3;
    volatile         T_SYSC_AWO_PIN_SHARE_EN                   pin_share_en; /* 0x40,    RW, 0x00000000,                             NA*/
    volatile           T_SYSC_AWO_DUMMY_CTRL                     dummy_ctrl; /* 0x44,    RW, 0x00000000,                             NA*/
    volatile                        uint32_t                     reserved_4;
    volatile            T_SYSC_AWO_SRAM_CTRL                      sram_ctrl; /* 0x4c,    RW, 0x00700621,                             NA*/
    volatile            T_SYSC_AWO_INTR_CTRL                      intr_ctrl; /* 0x50,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_INTR_CLR                       intr_clr; /* 0x54,    RW, 0x00000000,                             NA*/
    volatile            T_SYSC_AWO_INTR_STAT                      intr_stat; /* 0x58,    RO, 0x00000000,                             NA*/
    volatile                        uint32_t                     reserved_5;
    volatile          T_SYSC_AWO_TOUCH_CTRL0                    touch_ctrl0; /* 0x60,    RW, 0x00000000,                             NA*/
    volatile          T_SYSC_AWO_TOUCH_CTRL1                    touch_ctrl1; /* 0x64,    RW, 0x00000000,                             NA*/
    volatile T_SYSC_AWO_TOUCH_CTRL2_TOUCH_OUT          touch_ctrl2_touch_out; /* 0x68,  NULL, 0x00000000, union type of touch_ctrl2_touch_out*/
    volatile                        uint32_t                     reserved_6;
    volatile             T_SYSC_AWO_RF_REG_0                       rf_reg_0; /* 0x70,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_1                       rf_reg_1; /* 0x74,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_2                       rf_reg_2; /* 0x78,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_3                       rf_reg_3; /* 0x7c,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_4                       rf_reg_4; /* 0x80,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_5                       rf_reg_5; /* 0x84,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_6                       rf_reg_6; /* 0x88,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_7                       rf_reg_7; /* 0x8c,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_8                       rf_reg_8; /* 0x90,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_9                       rf_reg_9; /* 0x94,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_A                       rf_reg_a; /* 0x98,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_B                       rf_reg_b; /* 0x9c,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_C                       rf_reg_c; /* 0xa0,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_D                       rf_reg_d; /* 0xa4,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_E                       rf_reg_e; /* 0xa8,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_RF_REG_F                       rf_reg_f; /* 0xac,    RW, 0x00000000,                             NA*/
    volatile            T_SYSC_AWO_RF_REG_RD                      rf_reg_rd; /* 0xb0,    RO, 0x00000000,                             NA*/
    volatile                        uint32_t                  reserved_7[3];
    volatile         T_SYSC_AWO_PRW_PWM_WID0                   prw_pwm_wid0; /* 0xc0,    RW, 0x00000000,                             NA*/
    volatile         T_SYSC_AWO_PRW_PWM_WID1                   prw_pwm_wid1; /* 0xc4,    RW, 0x00000000,                             NA*/
    volatile         T_SYSC_AWO_PRW_PWM_WID2                   prw_pwm_wid2; /* 0xc8,    RW, 0x00000000,                             NA*/
    volatile         T_SYSC_AWO_PRW_PWM_CTRL                   prw_pwm_ctrl; /* 0xcc,    RW, 0x00010101,                             NA*/
    volatile            T_SYSC_AWO_BOOT_MODE                      boot_mode; /* 0xd0,    RO, 0x00000000,                             NA*/
    volatile                        uint32_t                  reserved_8[3];
    volatile           T_SYSC_AWO_AWO_GPO_EN                     awo_gpo_en; /* 0xe0,    RW, 0x00000000,                             NA*/
    volatile              T_SYSC_AWO_AWO_GPO                        awo_gpo; /* 0xe4,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_AWO_GPIO_DS0                       gpio_ds0; /* 0xe8,    RW, 0x00FFFFFF,                             NA*/
    volatile             T_SYSC_AWO_GPIO_DS1                       gpio_ds1; /* 0xec,    RW, 0x00FFFFFF,                             NA*/
    volatile              T_SYSC_AWO_GPIO_IE                        gpio_ie; /* 0xf0,    RW, 0x00FFFFFF,                             NA*/
    volatile              T_SYSC_AWO_GPIO_IS                        gpio_is; /* 0xf4,    RW, 0x00000000,                             NA*/
    volatile              T_SYSC_AWO_GPIO_PE                        gpio_pe; /* 0xf8,    RW, 0x00000000,                             NA*/
    volatile              T_SYSC_AWO_GPIO_PS                        gpio_ps; /* 0xfc,    RW, 0x00000000,                             NA*/
    volatile                        uint32_t                     reserved_9;
    volatile            T_SYSC_AWO_PRW_STAT0                      prw_stat0; /*0x104,    RO, 0x00100621,                             NA*/
    volatile            T_SYSC_AWO_PRW_STAT1                      prw_stat1; /*0x108,    RO, 0x0000007F,                             NA*/
} T_HWP_SYSC_AWO_T;

#define hwp_sysc_awo ((T_HWP_SYSC_AWO_T*)REG_SYSC_AWO_BASE)


__STATIC_INLINE uint32_t sysc_awo_clk_ctrl0_get(void)
{
    return hwp_sysc_awo->clk_ctrl0.val;
}

__STATIC_INLINE void sysc_awo_clk_ctrl0_set(uint32_t value)
{
    hwp_sysc_awo->clk_ctrl0.val = value;
}

__STATIC_INLINE void sysc_awo_clk_ctrl0_pack(uint8_t clk_sel_hbus0, uint8_t clk_sel_abus)
{
    hwp_sysc_awo->clk_ctrl0.val = (((uint32_t)clk_sel_hbus0 << 4) | ((uint32_t)clk_sel_abus << 0));
}

__STATIC_INLINE void sysc_awo_clk_ctrl0_unpack(uint8_t* wic_en_ack_sync, uint8_t* clk_sel_hbus0, uint8_t* clk_sel_abus)
{
    T_SYSC_AWO_CLK_CTRL0 localVal = hwp_sysc_awo->clk_ctrl0;

    *wic_en_ack_sync = localVal.bit_field.wic_en_ack_sync;
    *clk_sel_hbus0 = localVal.bit_field.clk_sel_hbus0;
    *clk_sel_abus = localVal.bit_field.clk_sel_abus;
}

__STATIC_INLINE uint8_t sysc_awo_wic_en_ack_sync_getf(void)
{
    return hwp_sysc_awo->clk_ctrl0.bit_field.wic_en_ack_sync;
}

__STATIC_INLINE uint8_t sysc_awo_clk_sel_hbus0_getf(void)
{
    return hwp_sysc_awo->clk_ctrl0.bit_field.clk_sel_hbus0;
}

__STATIC_INLINE void sysc_awo_clk_sel_hbus0_setf(uint8_t clk_sel_hbus0)
{
    hwp_sysc_awo->clk_ctrl0.bit_field.clk_sel_hbus0 = clk_sel_hbus0;
}

__STATIC_INLINE uint8_t sysc_awo_clk_sel_abus_getf(void)
{
    return hwp_sysc_awo->clk_ctrl0.bit_field.clk_sel_abus;
}

__STATIC_INLINE void sysc_awo_clk_sel_abus_setf(uint8_t clk_sel_abus)
{
    hwp_sysc_awo->clk_ctrl0.bit_field.clk_sel_abus = clk_sel_abus;
}

__STATIC_INLINE uint32_t sysc_awo_clk_ctrl1_get(void)
{
    return hwp_sysc_awo->clk_ctrl1.val;
}

__STATIC_INLINE void sysc_awo_clk_ctrl1_set(uint32_t value)
{
    hwp_sysc_awo->clk_ctrl1.val = value;
}

__STATIC_INLINE void sysc_awo_clk_ctrl1_pack(uint8_t clk_div_ble_by_hw, uint8_t clk_div_ble_up_sw, uint8_t clk_div_pbus_para_up, uint8_t clk_sel_ble, uint8_t clk_sel_hbus1)
{
    hwp_sysc_awo->clk_ctrl1.val = (((uint32_t)clk_div_ble_by_hw << 16) | ((uint32_t)clk_div_ble_up_sw << 12) | ((uint32_t)clk_div_pbus_para_up << 8) | ((uint32_t)clk_sel_ble << 4) | ((uint32_t)clk_sel_hbus1 << 0));
}

__STATIC_INLINE void sysc_awo_clk_ctrl1_unpack(uint8_t* clk_div_ble_by_hw, uint8_t* clk_sel_ble, uint8_t* clk_sel_hbus1)
{
    T_SYSC_AWO_CLK_CTRL1 localVal = hwp_sysc_awo->clk_ctrl1;

    *clk_div_ble_by_hw = localVal.bit_field.clk_div_ble_by_hw;
    *clk_sel_ble = localVal.bit_field.clk_sel_ble;
    *clk_sel_hbus1 = localVal.bit_field.clk_sel_hbus1;
}

__STATIC_INLINE uint8_t sysc_awo_clk_div_ble_by_hw_getf(void)
{
    return hwp_sysc_awo->clk_ctrl1.bit_field.clk_div_ble_by_hw;
}

__STATIC_INLINE void sysc_awo_clk_div_ble_by_hw_setf(uint8_t clk_div_ble_by_hw)
{
    hwp_sysc_awo->clk_ctrl1.bit_field.clk_div_ble_by_hw = clk_div_ble_by_hw;
}

__STATIC_INLINE uint8_t sysc_awo_clk_sel_ble_getf(void)
{
    return hwp_sysc_awo->clk_ctrl1.bit_field.clk_sel_ble;
}

__STATIC_INLINE void sysc_awo_clk_sel_ble_setf(uint8_t clk_sel_ble)
{
    hwp_sysc_awo->clk_ctrl1.bit_field.clk_sel_ble = clk_sel_ble;
}

__STATIC_INLINE uint8_t sysc_awo_clk_sel_hbus1_getf(void)
{
    return hwp_sysc_awo->clk_ctrl1.bit_field.clk_sel_hbus1;
}

__STATIC_INLINE void sysc_awo_clk_sel_hbus1_setf(uint8_t clk_sel_hbus1)
{
    hwp_sysc_awo->clk_ctrl1.bit_field.clk_sel_hbus1 = clk_sel_hbus1;
}

__STATIC_INLINE uint32_t sysc_awo_clk_div_param_get(void)
{
    return hwp_sysc_awo->clk_div_param.val;
}

__STATIC_INLINE void sysc_awo_clk_div_param_set(uint32_t value)
{
    hwp_sysc_awo->clk_div_param.val = value;
}

__STATIC_INLINE void sysc_awo_clk_div_param_pack(uint8_t clk_div_ble_para1_m1, uint8_t clk_div_ble_para0_m1, uint8_t clk_div_pbus_para_m1, uint8_t clk_div_hbus_para_m1)
{
    hwp_sysc_awo->clk_div_param.val = (((uint32_t)clk_div_ble_para1_m1 << 24) | ((uint32_t)clk_div_ble_para0_m1 << 16) | ((uint32_t)clk_div_pbus_para_m1 << 8) | ((uint32_t)clk_div_hbus_para_m1 << 0));
}

__STATIC_INLINE void sysc_awo_clk_div_param_unpack(uint8_t* clk_div_ble_para1_m1, uint8_t* clk_div_ble_para0_m1, uint8_t* clk_div_pbus_para_m1, uint8_t* clk_div_hbus_para_m1)
{
    T_SYSC_AWO_CLK_DIV_PARAM localVal = hwp_sysc_awo->clk_div_param;

    *clk_div_ble_para1_m1 = localVal.bit_field.clk_div_ble_para1_m1;
    *clk_div_ble_para0_m1 = localVal.bit_field.clk_div_ble_para0_m1;
    *clk_div_pbus_para_m1 = localVal.bit_field.clk_div_pbus_para_m1;
    *clk_div_hbus_para_m1 = localVal.bit_field.clk_div_hbus_para_m1;
}

__STATIC_INLINE uint8_t sysc_awo_clk_div_ble_para1_m1_getf(void)
{
    return hwp_sysc_awo->clk_div_param.bit_field.clk_div_ble_para1_m1;
}

__STATIC_INLINE void sysc_awo_clk_div_ble_para1_m1_setf(uint8_t clk_div_ble_para1_m1)
{
    hwp_sysc_awo->clk_div_param.bit_field.clk_div_ble_para1_m1 = clk_div_ble_para1_m1;
}

__STATIC_INLINE uint8_t sysc_awo_clk_div_ble_para0_m1_getf(void)
{
    return hwp_sysc_awo->clk_div_param.bit_field.clk_div_ble_para0_m1;
}

__STATIC_INLINE void sysc_awo_clk_div_ble_para0_m1_setf(uint8_t clk_div_ble_para0_m1)
{
    hwp_sysc_awo->clk_div_param.bit_field.clk_div_ble_para0_m1 = clk_div_ble_para0_m1;
}

__STATIC_INLINE uint8_t sysc_awo_clk_div_pbus_para_m1_getf(void)
{
    return hwp_sysc_awo->clk_div_param.bit_field.clk_div_pbus_para_m1;
}

__STATIC_INLINE void sysc_awo_clk_div_pbus_para_m1_setf(uint8_t clk_div_pbus_para_m1)
{
    hwp_sysc_awo->clk_div_param.bit_field.clk_div_pbus_para_m1 = clk_div_pbus_para_m1;
}

__STATIC_INLINE uint8_t sysc_awo_clk_div_hbus_para_m1_getf(void)
{
    return hwp_sysc_awo->clk_div_param.bit_field.clk_div_hbus_para_m1;
}

__STATIC_INLINE void sysc_awo_clk_div_hbus_para_m1_setf(uint8_t clk_div_hbus_para_m1)
{
    hwp_sysc_awo->clk_div_param.bit_field.clk_div_hbus_para_m1 = clk_div_hbus_para_m1;
}

__STATIC_INLINE uint32_t sysc_awo_clk_gate_get(void)
{
    return hwp_sysc_awo->clk_gate.val;
}

__STATIC_INLINE void sysc_awo_clk_gate_set(uint32_t value)
{
    hwp_sysc_awo->clk_gate.val = value;
}

__STATIC_INLINE void sysc_awo_clk_gate_pack(uint8_t clkg_clr_touch, uint8_t clkg_set_touch, uint8_t clkg_clr_rtc, uint8_t clkg_set_rtc, uint8_t clkg_clr_ble_lp, uint8_t clkg_set_ble_lp, uint8_t clkg_clr_ble_div, uint8_t clkg_set_ble_div, uint8_t clkg_clr_hbus_div, uint8_t clkg_set_hbus_div)
{
    hwp_sysc_awo->clk_gate.val = (((uint32_t)clkg_clr_touch << 9) | ((uint32_t)clkg_set_touch << 8) | ((uint32_t)clkg_clr_rtc << 7) | ((uint32_t)clkg_set_rtc << 6) | ((uint32_t)clkg_clr_ble_lp << 5) | ((uint32_t)clkg_set_ble_lp << 4) | ((uint32_t)clkg_clr_ble_div << 3) | ((uint32_t)clkg_set_ble_div << 2) | ((uint32_t)clkg_clr_hbus_div << 1) | ((uint32_t)clkg_set_hbus_div << 0));
}

__STATIC_INLINE uint32_t sysc_awo_sft_rst_get(void)
{
    return hwp_sysc_awo->sft_rst.val;
}

__STATIC_INLINE void sysc_awo_sft_rst_set(uint32_t value)
{
    hwp_sysc_awo->sft_rst.val = value;
}

__STATIC_INLINE void sysc_awo_sft_rst_pack(uint8_t srst_clr_ble_lp_n, uint8_t srst_set_ble_lp_n, uint8_t srst_clr_touch_n, uint8_t srst_set_touch_n, uint8_t srst_clr_ble_n, uint8_t srst_set_ble_n, uint8_t srst_clr_rtc_n, uint8_t srst_set_rtc_n, uint8_t srst_clr_all_n, uint8_t srst_set_all_n)
{
    hwp_sysc_awo->sft_rst.val = (((uint32_t)srst_clr_ble_lp_n << 9) | ((uint32_t)srst_set_ble_lp_n << 8) | ((uint32_t)srst_clr_touch_n << 7) | ((uint32_t)srst_set_touch_n << 6) | ((uint32_t)srst_clr_ble_n << 5) | ((uint32_t)srst_set_ble_n << 4) | ((uint32_t)srst_clr_rtc_n << 3) | ((uint32_t)srst_set_rtc_n << 2) | ((uint32_t)srst_clr_all_n << 1) | ((uint32_t)srst_set_all_n << 0));
}

__STATIC_INLINE uint32_t sysc_awo_pmu_ctrl0_get(void)
{
    return hwp_sysc_awo->pmu_ctrl0.val;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl0_set(uint32_t value)
{
    hwp_sysc_awo->pmu_ctrl0.val = value;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl0_pack(uint8_t rc32m_force_on, uint8_t nml_ldo_force_on, uint8_t nml_ldo_force_sel, uint8_t pd_sram_lslp_en, uint8_t pd_cpu_voltage, uint8_t cpu_ret_en, uint8_t pmu_en)
{
    hwp_sysc_awo->pmu_ctrl0.val = (((uint32_t)rc32m_force_on << 24) | ((uint32_t)nml_ldo_force_on << 20) | ((uint32_t)nml_ldo_force_sel << 16) | ((uint32_t)pd_sram_lslp_en << 12) | ((uint32_t)pd_cpu_voltage << 8) | ((uint32_t)cpu_ret_en << 4) | ((uint32_t)pmu_en << 0));
}

__STATIC_INLINE void sysc_awo_pmu_ctrl0_unpack(uint8_t* rc32m_force_on, uint8_t* nml_ldo_force_on, uint8_t* nml_ldo_force_sel, uint8_t* pd_sram_lslp_en, uint8_t* pd_cpu_voltage, uint8_t* cpu_ret_en, uint8_t* pmu_en)
{
    T_SYSC_AWO_PMU_CTRL0 localVal = hwp_sysc_awo->pmu_ctrl0;

    *rc32m_force_on = localVal.bit_field.rc32m_force_on;
    *nml_ldo_force_on = localVal.bit_field.nml_ldo_force_on;
    *nml_ldo_force_sel = localVal.bit_field.nml_ldo_force_sel;
    *pd_sram_lslp_en = localVal.bit_field.pd_sram_lslp_en;
    *pd_cpu_voltage = localVal.bit_field.pd_cpu_voltage;
    *cpu_ret_en = localVal.bit_field.cpu_ret_en;
    *pmu_en = localVal.bit_field.pmu_en;
}

__STATIC_INLINE uint8_t sysc_awo_rc32m_force_on_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.rc32m_force_on;
}

__STATIC_INLINE void sysc_awo_rc32m_force_on_setf(uint8_t rc32m_force_on)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.rc32m_force_on = rc32m_force_on;
}

__STATIC_INLINE uint8_t sysc_awo_nml_ldo_force_on_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.nml_ldo_force_on;
}

__STATIC_INLINE void sysc_awo_nml_ldo_force_on_setf(uint8_t nml_ldo_force_on)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.nml_ldo_force_on = nml_ldo_force_on;
}

__STATIC_INLINE uint8_t sysc_awo_nml_ldo_force_sel_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.nml_ldo_force_sel;
}

__STATIC_INLINE void sysc_awo_nml_ldo_force_sel_setf(uint8_t nml_ldo_force_sel)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.nml_ldo_force_sel = nml_ldo_force_sel;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_lslp_en_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.pd_sram_lslp_en;
}

__STATIC_INLINE void sysc_awo_pd_sram_lslp_en_setf(uint8_t pd_sram_lslp_en)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.pd_sram_lslp_en = pd_sram_lslp_en;
}

__STATIC_INLINE uint8_t sysc_awo_pd_cpu_voltage_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.pd_cpu_voltage;
}

__STATIC_INLINE void sysc_awo_pd_cpu_voltage_setf(uint8_t pd_cpu_voltage)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.pd_cpu_voltage = pd_cpu_voltage;
}

__STATIC_INLINE uint8_t sysc_awo_cpu_ret_en_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.cpu_ret_en;
}

__STATIC_INLINE void sysc_awo_cpu_ret_en_setf(uint8_t cpu_ret_en)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.cpu_ret_en = cpu_ret_en;
}

__STATIC_INLINE uint8_t sysc_awo_pmu_en_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl0.bit_field.pmu_en;
}

__STATIC_INLINE void sysc_awo_pmu_en_setf(uint8_t pmu_en)
{
    hwp_sysc_awo->pmu_ctrl0.bit_field.pmu_en = pmu_en;
}

__STATIC_INLINE uint32_t sysc_awo_pmu_ctrl1_get(void)
{
    return hwp_sysc_awo->pmu_ctrl1.val;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl1_set(uint32_t value)
{
    hwp_sysc_awo->pmu_ctrl1.val = value;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl1_pack(uint8_t pd_sram_prw_up_en, uint8_t pd_sram_prw_dn_en)
{
    hwp_sysc_awo->pmu_ctrl1.val = (((uint32_t)pd_sram_prw_up_en << 8) | ((uint32_t)pd_sram_prw_dn_en << 0));
}

__STATIC_INLINE void sysc_awo_pmu_ctrl1_unpack(uint8_t* pd_sram_prw_up_en, uint8_t* pd_sram_prw_dn_en)
{
    T_SYSC_AWO_PMU_CTRL1 localVal = hwp_sysc_awo->pmu_ctrl1;

    *pd_sram_prw_up_en = localVal.bit_field.pd_sram_prw_up_en;
    *pd_sram_prw_dn_en = localVal.bit_field.pd_sram_prw_dn_en;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_prw_up_en_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl1.bit_field.pd_sram_prw_up_en;
}

__STATIC_INLINE void sysc_awo_pd_sram_prw_up_en_setf(uint8_t pd_sram_prw_up_en)
{
    hwp_sysc_awo->pmu_ctrl1.bit_field.pd_sram_prw_up_en = pd_sram_prw_up_en;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_prw_dn_en_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl1.bit_field.pd_sram_prw_dn_en;
}

__STATIC_INLINE void sysc_awo_pd_sram_prw_dn_en_setf(uint8_t pd_sram_prw_dn_en)
{
    hwp_sysc_awo->pmu_ctrl1.bit_field.pd_sram_prw_dn_en = pd_sram_prw_dn_en;
}

__STATIC_INLINE uint32_t sysc_awo_pmu_ctrl2_get(void)
{
    return hwp_sysc_awo->pmu_ctrl2.val;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl2_set(uint32_t value)
{
    hwp_sysc_awo->pmu_ctrl2.val = value;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl2_pack(uint8_t clk_sw_dly, uint8_t nml_ldo_stb_dly, uint8_t cpu_ldo_stb_dly, uint8_t pmu_fsm_dly)
{
    hwp_sysc_awo->pmu_ctrl2.val = (((uint32_t)clk_sw_dly << 24) | ((uint32_t)nml_ldo_stb_dly << 16) | ((uint32_t)cpu_ldo_stb_dly << 8) | ((uint32_t)pmu_fsm_dly << 0));
}

__STATIC_INLINE void sysc_awo_pmu_ctrl2_unpack(uint8_t* clk_sw_dly, uint8_t* nml_ldo_stb_dly, uint8_t* cpu_ldo_stb_dly, uint8_t* pmu_fsm_dly)
{
    T_SYSC_AWO_PMU_CTRL2 localVal = hwp_sysc_awo->pmu_ctrl2;

    *clk_sw_dly = localVal.bit_field.clk_sw_dly;
    *nml_ldo_stb_dly = localVal.bit_field.nml_ldo_stb_dly;
    *cpu_ldo_stb_dly = localVal.bit_field.cpu_ldo_stb_dly;
    *pmu_fsm_dly = localVal.bit_field.pmu_fsm_dly;
}

__STATIC_INLINE uint8_t sysc_awo_clk_sw_dly_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl2.bit_field.clk_sw_dly;
}

__STATIC_INLINE void sysc_awo_clk_sw_dly_setf(uint8_t clk_sw_dly)
{
    hwp_sysc_awo->pmu_ctrl2.bit_field.clk_sw_dly = clk_sw_dly;
}

__STATIC_INLINE uint8_t sysc_awo_nml_ldo_stb_dly_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl2.bit_field.nml_ldo_stb_dly;
}

__STATIC_INLINE void sysc_awo_nml_ldo_stb_dly_setf(uint8_t nml_ldo_stb_dly)
{
    hwp_sysc_awo->pmu_ctrl2.bit_field.nml_ldo_stb_dly = nml_ldo_stb_dly;
}

__STATIC_INLINE uint8_t sysc_awo_cpu_ldo_stb_dly_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl2.bit_field.cpu_ldo_stb_dly;
}

__STATIC_INLINE void sysc_awo_cpu_ldo_stb_dly_setf(uint8_t cpu_ldo_stb_dly)
{
    hwp_sysc_awo->pmu_ctrl2.bit_field.cpu_ldo_stb_dly = cpu_ldo_stb_dly;
}

__STATIC_INLINE uint8_t sysc_awo_pmu_fsm_dly_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl2.bit_field.pmu_fsm_dly;
}

__STATIC_INLINE void sysc_awo_pmu_fsm_dly_setf(uint8_t pmu_fsm_dly)
{
    hwp_sysc_awo->pmu_ctrl2.bit_field.pmu_fsm_dly = pmu_fsm_dly;
}

__STATIC_INLINE uint32_t sysc_awo_pmu_ctrl3_get(void)
{
    return hwp_sysc_awo->pmu_ctrl3.val;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl3_set(uint32_t value)
{
    hwp_sysc_awo->pmu_ctrl3.val = value;
}

__STATIC_INLINE void sysc_awo_pmu_ctrl3_pack(uint8_t rc32m_stb_dly, uint8_t ldo_sw_dly)
{
    hwp_sysc_awo->pmu_ctrl3.val = (((uint32_t)rc32m_stb_dly << 8) | ((uint32_t)ldo_sw_dly << 0));
}

__STATIC_INLINE void sysc_awo_pmu_ctrl3_unpack(uint8_t* rc32m_stb_dly, uint8_t* ldo_sw_dly)
{
    T_SYSC_AWO_PMU_CTRL3 localVal = hwp_sysc_awo->pmu_ctrl3;

    *rc32m_stb_dly = localVal.bit_field.rc32m_stb_dly;
    *ldo_sw_dly = localVal.bit_field.ldo_sw_dly;
}

__STATIC_INLINE uint8_t sysc_awo_rc32m_stb_dly_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl3.bit_field.rc32m_stb_dly;
}

__STATIC_INLINE void sysc_awo_rc32m_stb_dly_setf(uint8_t rc32m_stb_dly)
{
    hwp_sysc_awo->pmu_ctrl3.bit_field.rc32m_stb_dly = rc32m_stb_dly;
}

__STATIC_INLINE uint8_t sysc_awo_ldo_sw_dly_getf(void)
{
    return hwp_sysc_awo->pmu_ctrl3.bit_field.ldo_sw_dly;
}

__STATIC_INLINE void sysc_awo_ldo_sw_dly_setf(uint8_t ldo_sw_dly)
{
    hwp_sysc_awo->pmu_ctrl3.bit_field.ldo_sw_dly = ldo_sw_dly;
}

__STATIC_INLINE uint32_t sysc_awo_ana_clk_ctrl_get(void)
{
    return hwp_sysc_awo->ana_clk_ctrl.val;
}

__STATIC_INLINE void sysc_awo_ana_clk_ctrl_set(uint32_t value)
{
    hwp_sysc_awo->ana_clk_ctrl.val = value;
}

__STATIC_INLINE void sysc_awo_ana_clk_ctrl_pack(uint8_t rc32m_prw_clr, uint8_t rc32m_prw_set, uint8_t clk32k_sel_xtal, uint8_t xtal32k_en, uint8_t rc32k_en, uint8_t clk32m_sel_rc, uint8_t xtal32m_en)
{
    hwp_sysc_awo->ana_clk_ctrl.val = (((uint32_t)rc32m_prw_clr << 24) | ((uint32_t)rc32m_prw_set << 20) | ((uint32_t)clk32k_sel_xtal << 16) | ((uint32_t)xtal32k_en << 12) | ((uint32_t)rc32k_en << 8) | ((uint32_t)clk32m_sel_rc << 4) | ((uint32_t)xtal32m_en << 0));
}

__STATIC_INLINE void sysc_awo_ana_clk_ctrl_unpack(uint8_t* clk32k_sel_xtal, uint8_t* xtal32k_en, uint8_t* rc32k_en, uint8_t* clk32m_sel_rc, uint8_t* xtal32m_en)
{
    T_SYSC_AWO_ANA_CLK_CTRL localVal = hwp_sysc_awo->ana_clk_ctrl;

    *clk32k_sel_xtal = localVal.bit_field.clk32k_sel_xtal;
    *xtal32k_en = localVal.bit_field.xtal32k_en;
    *rc32k_en = localVal.bit_field.rc32k_en;
    *clk32m_sel_rc = localVal.bit_field.clk32m_sel_rc;
    *xtal32m_en = localVal.bit_field.xtal32m_en;
}

__STATIC_INLINE uint8_t sysc_awo_clk32k_sel_xtal_getf(void)
{
    return hwp_sysc_awo->ana_clk_ctrl.bit_field.clk32k_sel_xtal;
}

__STATIC_INLINE void sysc_awo_clk32k_sel_xtal_setf(uint8_t clk32k_sel_xtal)
{
    hwp_sysc_awo->ana_clk_ctrl.bit_field.clk32k_sel_xtal = clk32k_sel_xtal;
}

__STATIC_INLINE uint8_t sysc_awo_xtal32k_en_getf(void)
{
    return hwp_sysc_awo->ana_clk_ctrl.bit_field.xtal32k_en;
}

__STATIC_INLINE void sysc_awo_xtal32k_en_setf(uint8_t xtal32k_en)
{
    hwp_sysc_awo->ana_clk_ctrl.bit_field.xtal32k_en = xtal32k_en;
}

__STATIC_INLINE uint8_t sysc_awo_rc32k_en_getf(void)
{
    return hwp_sysc_awo->ana_clk_ctrl.bit_field.rc32k_en;
}

__STATIC_INLINE void sysc_awo_rc32k_en_setf(uint8_t rc32k_en)
{
    hwp_sysc_awo->ana_clk_ctrl.bit_field.rc32k_en = rc32k_en;
}

__STATIC_INLINE uint8_t sysc_awo_clk32m_sel_rc_getf(void)
{
    return hwp_sysc_awo->ana_clk_ctrl.bit_field.clk32m_sel_rc;
}

__STATIC_INLINE void sysc_awo_clk32m_sel_rc_setf(uint8_t clk32m_sel_rc)
{
    hwp_sysc_awo->ana_clk_ctrl.bit_field.clk32m_sel_rc = clk32m_sel_rc;
}

__STATIC_INLINE uint8_t sysc_awo_xtal32m_en_getf(void)
{
    return hwp_sysc_awo->ana_clk_ctrl.bit_field.xtal32m_en;
}

__STATIC_INLINE void sysc_awo_xtal32m_en_setf(uint8_t xtal32m_en)
{
    hwp_sysc_awo->ana_clk_ctrl.bit_field.xtal32m_en = xtal32m_en;
}

__STATIC_INLINE uint32_t sysc_awo_pmu_start_get(void)
{
    return hwp_sysc_awo->pmu_start.val;
}

__STATIC_INLINE void sysc_awo_pmu_start_set(uint32_t value)
{
    hwp_sysc_awo->pmu_start.val = value;
}

__STATIC_INLINE void sysc_awo_pmu_start_pack(uint8_t pd_sram_prw_clr, uint8_t pd_sram_prw_set, uint8_t pd_sram_iso_clr, uint8_t pd_sram_iso_set)
{
    hwp_sysc_awo->pmu_start.val = (((uint32_t)pd_sram_prw_clr << 12) | ((uint32_t)pd_sram_prw_set << 8) | ((uint32_t)pd_sram_iso_clr << 4) | ((uint32_t)pd_sram_iso_set << 0));
}

__STATIC_INLINE uint32_t sysc_awo_pin_share_en_get(void)
{
    return hwp_sysc_awo->pin_share_en.val;
}

__STATIC_INLINE void sysc_awo_pin_share_en_set(uint32_t value)
{
    hwp_sysc_awo->pin_share_en.val = value;
}

__STATIC_INLINE void sysc_awo_pin_share_en_pack(uint8_t pmu_dbg_en, uint8_t ext_intr_en)
{
    hwp_sysc_awo->pin_share_en.val = (((uint32_t)pmu_dbg_en << 16) | ((uint32_t)ext_intr_en << 8));
}

__STATIC_INLINE void sysc_awo_pin_share_en_unpack(uint8_t* pmu_dbg_en, uint8_t* ext_intr_en)
{
    T_SYSC_AWO_PIN_SHARE_EN localVal = hwp_sysc_awo->pin_share_en;

    *pmu_dbg_en = localVal.bit_field.pmu_dbg_en;
    *ext_intr_en = localVal.bit_field.ext_intr_en;
}

__STATIC_INLINE uint8_t sysc_awo_pmu_dbg_en_getf(void)
{
    return hwp_sysc_awo->pin_share_en.bit_field.pmu_dbg_en;
}

__STATIC_INLINE void sysc_awo_pmu_dbg_en_setf(uint8_t pmu_dbg_en)
{
    hwp_sysc_awo->pin_share_en.bit_field.pmu_dbg_en = pmu_dbg_en;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_en_getf(void)
{
    return hwp_sysc_awo->pin_share_en.bit_field.ext_intr_en;
}

__STATIC_INLINE void sysc_awo_ext_intr_en_setf(uint8_t ext_intr_en)
{
    hwp_sysc_awo->pin_share_en.bit_field.ext_intr_en = ext_intr_en;
}

__STATIC_INLINE uint32_t sysc_awo_dummy_ctrl_get(void)
{
    return hwp_sysc_awo->dummy_ctrl.val;
}

__STATIC_INLINE void sysc_awo_dummy_ctrl_set(uint32_t value)
{
    hwp_sysc_awo->dummy_ctrl.val = value;
}

__STATIC_INLINE void sysc_awo_dummy_ctrl_pack(uint8_t dummy_ctrl)
{
    hwp_sysc_awo->dummy_ctrl.val = (((uint32_t)dummy_ctrl << 0));
}

__STATIC_INLINE void sysc_awo_dummy_ctrl_unpack(uint8_t* dummy_ctrl)
{
    T_SYSC_AWO_DUMMY_CTRL localVal = hwp_sysc_awo->dummy_ctrl;

    *dummy_ctrl = localVal.bit_field.dummy_ctrl;
}

__STATIC_INLINE uint8_t sysc_awo_dummy_ctrl_getf(void)
{
    return hwp_sysc_awo->dummy_ctrl.bit_field.dummy_ctrl;
}

__STATIC_INLINE void sysc_awo_dummy_ctrl_setf(uint8_t dummy_ctrl)
{
    hwp_sysc_awo->dummy_ctrl.bit_field.dummy_ctrl = dummy_ctrl;
}

__STATIC_INLINE uint32_t sysc_awo_sram_ctrl_get(void)
{
    return hwp_sysc_awo->sram_ctrl.val;
}

__STATIC_INLINE void sysc_awo_sram_ctrl_set(uint32_t value)
{
    hwp_sysc_awo->sram_ctrl.val = value;
}

__STATIC_INLINE void sysc_awo_sram_ctrl_pack(uint8_t sram_ret_voltage, uint8_t tgt_sram_wpulse, uint8_t tgt_sram_ra, uint8_t tgt_sram_wa, uint8_t tgt_sram_rm, uint8_t tgt_sram_rme)
{
    hwp_sysc_awo->sram_ctrl.val = (((uint32_t)sram_ret_voltage << 20) | ((uint32_t)tgt_sram_wpulse << 16) | ((uint32_t)tgt_sram_ra << 12) | ((uint32_t)tgt_sram_wa << 8) | ((uint32_t)tgt_sram_rm << 4) | ((uint32_t)tgt_sram_rme << 0));
}

__STATIC_INLINE void sysc_awo_sram_ctrl_unpack(uint8_t* sram_ret_voltage, uint8_t* tgt_sram_wpulse, uint8_t* tgt_sram_ra, uint8_t* tgt_sram_wa, uint8_t* tgt_sram_rm, uint8_t* tgt_sram_rme)
{
    T_SYSC_AWO_SRAM_CTRL localVal = hwp_sysc_awo->sram_ctrl;

    *sram_ret_voltage = localVal.bit_field.sram_ret_voltage;
    *tgt_sram_wpulse = localVal.bit_field.tgt_sram_wpulse;
    *tgt_sram_ra = localVal.bit_field.tgt_sram_ra;
    *tgt_sram_wa = localVal.bit_field.tgt_sram_wa;
    *tgt_sram_rm = localVal.bit_field.tgt_sram_rm;
    *tgt_sram_rme = localVal.bit_field.tgt_sram_rme;
}

__STATIC_INLINE uint8_t sysc_awo_sram_ret_voltage_getf(void)
{
    return hwp_sysc_awo->sram_ctrl.bit_field.sram_ret_voltage;
}

__STATIC_INLINE void sysc_awo_sram_ret_voltage_setf(uint8_t sram_ret_voltage)
{
    hwp_sysc_awo->sram_ctrl.bit_field.sram_ret_voltage = sram_ret_voltage;
}

__STATIC_INLINE uint8_t sysc_awo_tgt_sram_wpulse_getf(void)
{
    return hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_wpulse;
}

__STATIC_INLINE void sysc_awo_tgt_sram_wpulse_setf(uint8_t tgt_sram_wpulse)
{
    hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_wpulse = tgt_sram_wpulse;
}

__STATIC_INLINE uint8_t sysc_awo_tgt_sram_ra_getf(void)
{
    return hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_ra;
}

__STATIC_INLINE void sysc_awo_tgt_sram_ra_setf(uint8_t tgt_sram_ra)
{
    hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_ra = tgt_sram_ra;
}

__STATIC_INLINE uint8_t sysc_awo_tgt_sram_wa_getf(void)
{
    return hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_wa;
}

__STATIC_INLINE void sysc_awo_tgt_sram_wa_setf(uint8_t tgt_sram_wa)
{
    hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_wa = tgt_sram_wa;
}

__STATIC_INLINE uint8_t sysc_awo_tgt_sram_rm_getf(void)
{
    return hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_rm;
}

__STATIC_INLINE void sysc_awo_tgt_sram_rm_setf(uint8_t tgt_sram_rm)
{
    hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_rm = tgt_sram_rm;
}

__STATIC_INLINE uint8_t sysc_awo_tgt_sram_rme_getf(void)
{
    return hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_rme;
}

__STATIC_INLINE void sysc_awo_tgt_sram_rme_setf(uint8_t tgt_sram_rme)
{
    hwp_sysc_awo->sram_ctrl.bit_field.tgt_sram_rme = tgt_sram_rme;
}

__STATIC_INLINE uint32_t sysc_awo_intr_ctrl_get(void)
{
    return hwp_sysc_awo->intr_ctrl.val;
}

__STATIC_INLINE void sysc_awo_intr_ctrl_set(uint32_t value)
{
    hwp_sysc_awo->intr_ctrl.val = value;
}

__STATIC_INLINE void sysc_awo_intr_ctrl_pack(uint8_t touch_intr_msk, uint8_t ble_lp_intr_msk, uint8_t ext_intr_msk, uint8_t ext_intr_pol, uint8_t ext_intr_edge)
{
    hwp_sysc_awo->intr_ctrl.val = (((uint32_t)touch_intr_msk << 26) | ((uint32_t)ble_lp_intr_msk << 24) | ((uint32_t)ext_intr_msk << 16) | ((uint32_t)ext_intr_pol << 8) | ((uint32_t)ext_intr_edge << 0));
}

__STATIC_INLINE void sysc_awo_intr_ctrl_unpack(uint8_t* touch_intr_msk, uint8_t* ble_lp_intr_msk, uint8_t* ext_intr_msk, uint8_t* ext_intr_pol, uint8_t* ext_intr_edge)
{
    T_SYSC_AWO_INTR_CTRL localVal = hwp_sysc_awo->intr_ctrl;

    *touch_intr_msk = localVal.bit_field.touch_intr_msk;
    *ble_lp_intr_msk = localVal.bit_field.ble_lp_intr_msk;
    *ext_intr_msk = localVal.bit_field.ext_intr_msk;
    *ext_intr_pol = localVal.bit_field.ext_intr_pol;
    *ext_intr_edge = localVal.bit_field.ext_intr_edge;
}

__STATIC_INLINE uint8_t sysc_awo_touch_intr_msk_getf(void)
{
    return hwp_sysc_awo->intr_ctrl.bit_field.touch_intr_msk;
}

__STATIC_INLINE void sysc_awo_touch_intr_msk_setf(uint8_t touch_intr_msk)
{
    hwp_sysc_awo->intr_ctrl.bit_field.touch_intr_msk = touch_intr_msk;
}

__STATIC_INLINE uint8_t sysc_awo_ble_lp_intr_msk_getf(void)
{
    return hwp_sysc_awo->intr_ctrl.bit_field.ble_lp_intr_msk;
}

__STATIC_INLINE void sysc_awo_ble_lp_intr_msk_setf(uint8_t ble_lp_intr_msk)
{
    hwp_sysc_awo->intr_ctrl.bit_field.ble_lp_intr_msk = ble_lp_intr_msk;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_msk_getf(void)
{
    return hwp_sysc_awo->intr_ctrl.bit_field.ext_intr_msk;
}

__STATIC_INLINE void sysc_awo_ext_intr_msk_setf(uint8_t ext_intr_msk)
{
    hwp_sysc_awo->intr_ctrl.bit_field.ext_intr_msk = ext_intr_msk;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_pol_getf(void)
{
    return hwp_sysc_awo->intr_ctrl.bit_field.ext_intr_pol;
}

__STATIC_INLINE void sysc_awo_ext_intr_pol_setf(uint8_t ext_intr_pol)
{
    hwp_sysc_awo->intr_ctrl.bit_field.ext_intr_pol = ext_intr_pol;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_edge_getf(void)
{
    return hwp_sysc_awo->intr_ctrl.bit_field.ext_intr_edge;
}

__STATIC_INLINE void sysc_awo_ext_intr_edge_setf(uint8_t ext_intr_edge)
{
    hwp_sysc_awo->intr_ctrl.bit_field.ext_intr_edge = ext_intr_edge;
}

__STATIC_INLINE uint32_t sysc_awo_intr_clr_get(void)
{
    return hwp_sysc_awo->intr_clr.val;
}

__STATIC_INLINE void sysc_awo_intr_clr_set(uint32_t value)
{
    hwp_sysc_awo->intr_clr.val = value;
}

__STATIC_INLINE void sysc_awo_intr_clr_pack(uint8_t touch_intr_clr, uint8_t ble_lp_intr_clr, uint8_t ext_intr_clr)
{
    hwp_sysc_awo->intr_clr.val = (((uint32_t)touch_intr_clr << 26) | ((uint32_t)ble_lp_intr_clr << 24) | ((uint32_t)ext_intr_clr << 16));
}

__STATIC_INLINE void sysc_awo_intr_clr_unpack(uint8_t* touch_intr_clr, uint8_t* ble_lp_intr_clr, uint8_t* ext_intr_clr)
{
    T_SYSC_AWO_INTR_CLR localVal = hwp_sysc_awo->intr_clr;

    *touch_intr_clr = localVal.bit_field.touch_intr_clr;
    *ble_lp_intr_clr = localVal.bit_field.ble_lp_intr_clr;
    *ext_intr_clr = localVal.bit_field.ext_intr_clr;
}

__STATIC_INLINE uint8_t sysc_awo_touch_intr_clr_getf(void)
{
    return hwp_sysc_awo->intr_clr.bit_field.touch_intr_clr;
}

__STATIC_INLINE void sysc_awo_touch_intr_clr_setf(uint8_t touch_intr_clr)
{
    hwp_sysc_awo->intr_clr.bit_field.touch_intr_clr = touch_intr_clr;
}

__STATIC_INLINE uint8_t sysc_awo_ble_lp_intr_clr_getf(void)
{
    return hwp_sysc_awo->intr_clr.bit_field.ble_lp_intr_clr;
}

__STATIC_INLINE void sysc_awo_ble_lp_intr_clr_setf(uint8_t ble_lp_intr_clr)
{
    hwp_sysc_awo->intr_clr.bit_field.ble_lp_intr_clr = ble_lp_intr_clr;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_clr_getf(void)
{
    return hwp_sysc_awo->intr_clr.bit_field.ext_intr_clr;
}

__STATIC_INLINE void sysc_awo_ext_intr_clr_setf(uint8_t ext_intr_clr)
{
    hwp_sysc_awo->intr_clr.bit_field.ext_intr_clr = ext_intr_clr;
}

__STATIC_INLINE uint32_t sysc_awo_intr_stat_get(void)
{
    return hwp_sysc_awo->intr_stat.val;
}

__STATIC_INLINE void sysc_awo_intr_stat_unpack(uint8_t* ext_intr_trig_val, uint8_t* touch_intr_raw, uint8_t* ble_lp_intr_raw, uint8_t* ext_intr_raw, uint8_t* touch_intr_stat, uint8_t* ble_lp_intr_stat, uint8_t* ext_intr_stat)
{
    T_SYSC_AWO_INTR_STAT localVal = hwp_sysc_awo->intr_stat;

    *ext_intr_trig_val = localVal.bit_field.ext_intr_trig_val;
    *touch_intr_raw = localVal.bit_field.touch_intr_raw;
    *ble_lp_intr_raw = localVal.bit_field.ble_lp_intr_raw;
    *ext_intr_raw = localVal.bit_field.ext_intr_raw;
    *touch_intr_stat = localVal.bit_field.touch_intr_stat;
    *ble_lp_intr_stat = localVal.bit_field.ble_lp_intr_stat;
    *ext_intr_stat = localVal.bit_field.ext_intr_stat;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_trig_val_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.ext_intr_trig_val;
}

__STATIC_INLINE uint8_t sysc_awo_touch_intr_raw_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.touch_intr_raw;
}

__STATIC_INLINE uint8_t sysc_awo_ble_lp_intr_raw_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.ble_lp_intr_raw;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_raw_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.ext_intr_raw;
}

__STATIC_INLINE uint8_t sysc_awo_touch_intr_stat_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.touch_intr_stat;
}

__STATIC_INLINE uint8_t sysc_awo_ble_lp_intr_stat_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.ble_lp_intr_stat;
}

__STATIC_INLINE uint8_t sysc_awo_ext_intr_stat_getf(void)
{
    return hwp_sysc_awo->intr_stat.bit_field.ext_intr_stat;
}

__STATIC_INLINE uint32_t sysc_awo_touch_ctrl0_get(void)
{
    return hwp_sysc_awo->touch_ctrl0.val;
}

__STATIC_INLINE void sysc_awo_touch_ctrl0_set(uint32_t value)
{
    hwp_sysc_awo->touch_ctrl0.val = value;
}

__STATIC_INLINE void sysc_awo_touch_ctrl0_pack(uint8_t touch_ready_idx, uint16_t touch_itv, uint8_t touch_single, uint8_t touch_en)
{
    hwp_sysc_awo->touch_ctrl0.val = (((uint32_t)touch_ready_idx << 24) | ((uint32_t)touch_itv << 8) | ((uint32_t)touch_single << 4) | ((uint32_t)touch_en << 0));
}

__STATIC_INLINE void sysc_awo_touch_ctrl0_unpack(uint8_t* touch_ready_idx, uint16_t* touch_itv, uint8_t* touch_single, uint8_t* touch_en)
{
    T_SYSC_AWO_TOUCH_CTRL0 localVal = hwp_sysc_awo->touch_ctrl0;

    *touch_ready_idx = localVal.bit_field.touch_ready_idx;
    *touch_itv = localVal.bit_field.touch_itv;
    *touch_single = localVal.bit_field.touch_single;
    *touch_en = localVal.bit_field.touch_en;
}

__STATIC_INLINE uint8_t sysc_awo_touch_ready_idx_getf(void)
{
    return hwp_sysc_awo->touch_ctrl0.bit_field.touch_ready_idx;
}

__STATIC_INLINE void sysc_awo_touch_ready_idx_setf(uint8_t touch_ready_idx)
{
    hwp_sysc_awo->touch_ctrl0.bit_field.touch_ready_idx = touch_ready_idx;
}

__STATIC_INLINE uint16_t sysc_awo_touch_itv_getf(void)
{
    return hwp_sysc_awo->touch_ctrl0.bit_field.touch_itv;
}

__STATIC_INLINE void sysc_awo_touch_itv_setf(uint16_t touch_itv)
{
    hwp_sysc_awo->touch_ctrl0.bit_field.touch_itv = touch_itv;
}

__STATIC_INLINE uint8_t sysc_awo_touch_single_getf(void)
{
    return hwp_sysc_awo->touch_ctrl0.bit_field.touch_single;
}

__STATIC_INLINE void sysc_awo_touch_single_setf(uint8_t touch_single)
{
    hwp_sysc_awo->touch_ctrl0.bit_field.touch_single = touch_single;
}

__STATIC_INLINE uint8_t sysc_awo_touch_en_getf(void)
{
    return hwp_sysc_awo->touch_ctrl0.bit_field.touch_en;
}

__STATIC_INLINE void sysc_awo_touch_en_setf(uint8_t touch_en)
{
    hwp_sysc_awo->touch_ctrl0.bit_field.touch_en = touch_en;
}

__STATIC_INLINE uint32_t sysc_awo_touch_ctrl1_get(void)
{
    return hwp_sysc_awo->touch_ctrl1.val;
}

__STATIC_INLINE void sysc_awo_touch_ctrl1_set(uint32_t value)
{
    hwp_sysc_awo->touch_ctrl1.val = value;
}

__STATIC_INLINE void sysc_awo_touch_ctrl1_pack(uint16_t touch_scan_dly, uint16_t touch_scan_num)
{
    hwp_sysc_awo->touch_ctrl1.val = (((uint32_t)touch_scan_dly << 16) | ((uint32_t)touch_scan_num << 0));
}

__STATIC_INLINE void sysc_awo_touch_ctrl1_unpack(uint16_t* touch_scan_dly, uint16_t* touch_scan_num)
{
    T_SYSC_AWO_TOUCH_CTRL1 localVal = hwp_sysc_awo->touch_ctrl1;

    *touch_scan_dly = localVal.bit_field.touch_scan_dly;
    *touch_scan_num = localVal.bit_field.touch_scan_num;
}

__STATIC_INLINE uint16_t sysc_awo_touch_scan_dly_getf(void)
{
    return hwp_sysc_awo->touch_ctrl1.bit_field.touch_scan_dly;
}

__STATIC_INLINE void sysc_awo_touch_scan_dly_setf(uint16_t touch_scan_dly)
{
    hwp_sysc_awo->touch_ctrl1.bit_field.touch_scan_dly = touch_scan_dly;
}

__STATIC_INLINE uint16_t sysc_awo_touch_scan_num_getf(void)
{
    return hwp_sysc_awo->touch_ctrl1.bit_field.touch_scan_num;
}

__STATIC_INLINE void sysc_awo_touch_scan_num_setf(uint16_t touch_scan_num)
{
    hwp_sysc_awo->touch_ctrl1.bit_field.touch_scan_num = touch_scan_num;
}

__STATIC_INLINE uint32_t sysc_awo_touch_ctrl2_get(void)
{
    return hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.val;
}

__STATIC_INLINE void sysc_awo_touch_ctrl2_set(uint32_t value)
{
    hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.val = value;
}

__STATIC_INLINE void sysc_awo_touch_ctrl2_pack(uint8_t touch_clk_div_para, uint32_t touch_thr)
{
    hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.val = (((uint32_t)touch_clk_div_para << 20) | ((uint32_t)touch_thr << 0));
}

__STATIC_INLINE void sysc_awo_touch_ctrl2_unpack(uint8_t* touch_clk_div_para, uint32_t* touch_thr)
{
    T_SYSC_AWO_TOUCH_CTRL2 localVal = hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2;

    *touch_clk_div_para = localVal.bit_field.touch_clk_div_para;
    *touch_thr = localVal.bit_field.touch_thr;
}

__STATIC_INLINE uint8_t sysc_awo_touch_clk_div_para_getf(void)
{
    return hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.bit_field.touch_clk_div_para;
}

__STATIC_INLINE void sysc_awo_touch_clk_div_para_setf(uint8_t touch_clk_div_para)
{
    hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.bit_field.touch_clk_div_para = touch_clk_div_para;
}

__STATIC_INLINE uint32_t sysc_awo_touch_thr_getf(void)
{
    return hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.bit_field.touch_thr;
}

__STATIC_INLINE void sysc_awo_touch_thr_setf(uint32_t touch_thr)
{
    hwp_sysc_awo->touch_ctrl2_touch_out.touch_ctrl2.bit_field.touch_thr = touch_thr;
}

__STATIC_INLINE uint32_t sysc_awo_touch_out_get(void)
{
    return hwp_sysc_awo->touch_ctrl2_touch_out.touch_out.val;
}

__STATIC_INLINE void sysc_awo_touch_out_unpack(uint8_t* touch_fsm, uint32_t* touch_val)
{
    T_SYSC_AWO_TOUCH_OUT localVal = hwp_sysc_awo->touch_ctrl2_touch_out.touch_out;

    *touch_fsm = localVal.bit_field.touch_fsm;
    *touch_val = localVal.bit_field.touch_val;
}

__STATIC_INLINE uint8_t sysc_awo_touch_fsm_getf(void)
{
    return hwp_sysc_awo->touch_ctrl2_touch_out.touch_out.bit_field.touch_fsm;
}

__STATIC_INLINE uint32_t sysc_awo_touch_val_getf(void)
{
    return hwp_sysc_awo->touch_ctrl2_touch_out.touch_out.bit_field.touch_val;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_0_get(void)
{
    return hwp_sysc_awo->rf_reg_0.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_0_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_0.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_0_pack(uint32_t rf_reg_0)
{
    hwp_sysc_awo->rf_reg_0.val = (((uint32_t)rf_reg_0 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_0_unpack(uint32_t* rf_reg_0)
{
    T_SYSC_AWO_RF_REG_0 localVal = hwp_sysc_awo->rf_reg_0;

    *rf_reg_0 = localVal.bit_field.rf_reg_0;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_0_getf(void)
{
    return hwp_sysc_awo->rf_reg_0.bit_field.rf_reg_0;
}

__STATIC_INLINE void sysc_awo_rf_reg_0_setf(uint32_t rf_reg_0)
{
    hwp_sysc_awo->rf_reg_0.bit_field.rf_reg_0 = rf_reg_0;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_1_get(void)
{
    return hwp_sysc_awo->rf_reg_1.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_1_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_1.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_1_pack(uint32_t rf_reg_1)
{
    hwp_sysc_awo->rf_reg_1.val = (((uint32_t)rf_reg_1 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_1_unpack(uint32_t* rf_reg_1)
{
    T_SYSC_AWO_RF_REG_1 localVal = hwp_sysc_awo->rf_reg_1;

    *rf_reg_1 = localVal.bit_field.rf_reg_1;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_1_getf(void)
{
    return hwp_sysc_awo->rf_reg_1.bit_field.rf_reg_1;
}

__STATIC_INLINE void sysc_awo_rf_reg_1_setf(uint32_t rf_reg_1)
{
    hwp_sysc_awo->rf_reg_1.bit_field.rf_reg_1 = rf_reg_1;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_2_get(void)
{
    return hwp_sysc_awo->rf_reg_2.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_2_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_2.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_2_pack(uint32_t rf_reg_2)
{
    hwp_sysc_awo->rf_reg_2.val = (((uint32_t)rf_reg_2 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_2_unpack(uint32_t* rf_reg_2)
{
    T_SYSC_AWO_RF_REG_2 localVal = hwp_sysc_awo->rf_reg_2;

    *rf_reg_2 = localVal.bit_field.rf_reg_2;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_2_getf(void)
{
    return hwp_sysc_awo->rf_reg_2.bit_field.rf_reg_2;
}

__STATIC_INLINE void sysc_awo_rf_reg_2_setf(uint32_t rf_reg_2)
{
    hwp_sysc_awo->rf_reg_2.bit_field.rf_reg_2 = rf_reg_2;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_3_get(void)
{
    return hwp_sysc_awo->rf_reg_3.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_3_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_3.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_3_pack(uint32_t rf_reg_3)
{
    hwp_sysc_awo->rf_reg_3.val = (((uint32_t)rf_reg_3 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_3_unpack(uint32_t* rf_reg_3)
{
    T_SYSC_AWO_RF_REG_3 localVal = hwp_sysc_awo->rf_reg_3;

    *rf_reg_3 = localVal.bit_field.rf_reg_3;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_3_getf(void)
{
    return hwp_sysc_awo->rf_reg_3.bit_field.rf_reg_3;
}

__STATIC_INLINE void sysc_awo_rf_reg_3_setf(uint32_t rf_reg_3)
{
    hwp_sysc_awo->rf_reg_3.bit_field.rf_reg_3 = rf_reg_3;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_4_get(void)
{
    return hwp_sysc_awo->rf_reg_4.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_4_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_4.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_4_pack(uint32_t rf_reg_4)
{
    hwp_sysc_awo->rf_reg_4.val = (((uint32_t)rf_reg_4 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_4_unpack(uint32_t* rf_reg_4)
{
    T_SYSC_AWO_RF_REG_4 localVal = hwp_sysc_awo->rf_reg_4;

    *rf_reg_4 = localVal.bit_field.rf_reg_4;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_4_getf(void)
{
    return hwp_sysc_awo->rf_reg_4.bit_field.rf_reg_4;
}

__STATIC_INLINE void sysc_awo_rf_reg_4_setf(uint32_t rf_reg_4)
{
    hwp_sysc_awo->rf_reg_4.bit_field.rf_reg_4 = rf_reg_4;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_5_get(void)
{
    return hwp_sysc_awo->rf_reg_5.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_5_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_5.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_5_pack(uint32_t rf_reg_5)
{
    hwp_sysc_awo->rf_reg_5.val = (((uint32_t)rf_reg_5 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_5_unpack(uint32_t* rf_reg_5)
{
    T_SYSC_AWO_RF_REG_5 localVal = hwp_sysc_awo->rf_reg_5;

    *rf_reg_5 = localVal.bit_field.rf_reg_5;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_5_getf(void)
{
    return hwp_sysc_awo->rf_reg_5.bit_field.rf_reg_5;
}

__STATIC_INLINE void sysc_awo_rf_reg_5_setf(uint32_t rf_reg_5)
{
    hwp_sysc_awo->rf_reg_5.bit_field.rf_reg_5 = rf_reg_5;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_6_get(void)
{
    return hwp_sysc_awo->rf_reg_6.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_6_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_6.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_6_pack(uint32_t rf_reg_6)
{
    hwp_sysc_awo->rf_reg_6.val = (((uint32_t)rf_reg_6 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_6_unpack(uint32_t* rf_reg_6)
{
    T_SYSC_AWO_RF_REG_6 localVal = hwp_sysc_awo->rf_reg_6;

    *rf_reg_6 = localVal.bit_field.rf_reg_6;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_6_getf(void)
{
    return hwp_sysc_awo->rf_reg_6.bit_field.rf_reg_6;
}

__STATIC_INLINE void sysc_awo_rf_reg_6_setf(uint32_t rf_reg_6)
{
    hwp_sysc_awo->rf_reg_6.bit_field.rf_reg_6 = rf_reg_6;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_7_get(void)
{
    return hwp_sysc_awo->rf_reg_7.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_7_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_7.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_7_pack(uint32_t rf_reg_7)
{
    hwp_sysc_awo->rf_reg_7.val = (((uint32_t)rf_reg_7 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_7_unpack(uint32_t* rf_reg_7)
{
    T_SYSC_AWO_RF_REG_7 localVal = hwp_sysc_awo->rf_reg_7;

    *rf_reg_7 = localVal.bit_field.rf_reg_7;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_7_getf(void)
{
    return hwp_sysc_awo->rf_reg_7.bit_field.rf_reg_7;
}

__STATIC_INLINE void sysc_awo_rf_reg_7_setf(uint32_t rf_reg_7)
{
    hwp_sysc_awo->rf_reg_7.bit_field.rf_reg_7 = rf_reg_7;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_8_get(void)
{
    return hwp_sysc_awo->rf_reg_8.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_8_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_8.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_8_pack(uint32_t rf_reg_8)
{
    hwp_sysc_awo->rf_reg_8.val = (((uint32_t)rf_reg_8 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_8_unpack(uint32_t* rf_reg_8)
{
    T_SYSC_AWO_RF_REG_8 localVal = hwp_sysc_awo->rf_reg_8;

    *rf_reg_8 = localVal.bit_field.rf_reg_8;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_8_getf(void)
{
    return hwp_sysc_awo->rf_reg_8.bit_field.rf_reg_8;
}

__STATIC_INLINE void sysc_awo_rf_reg_8_setf(uint32_t rf_reg_8)
{
    hwp_sysc_awo->rf_reg_8.bit_field.rf_reg_8 = rf_reg_8;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_9_get(void)
{
    return hwp_sysc_awo->rf_reg_9.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_9_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_9.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_9_pack(uint32_t rf_reg_9)
{
    hwp_sysc_awo->rf_reg_9.val = (((uint32_t)rf_reg_9 << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_9_unpack(uint32_t* rf_reg_9)
{
    T_SYSC_AWO_RF_REG_9 localVal = hwp_sysc_awo->rf_reg_9;

    *rf_reg_9 = localVal.bit_field.rf_reg_9;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_9_getf(void)
{
    return hwp_sysc_awo->rf_reg_9.bit_field.rf_reg_9;
}

__STATIC_INLINE void sysc_awo_rf_reg_9_setf(uint32_t rf_reg_9)
{
    hwp_sysc_awo->rf_reg_9.bit_field.rf_reg_9 = rf_reg_9;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_a_get(void)
{
    return hwp_sysc_awo->rf_reg_a.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_a_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_a.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_a_pack(uint32_t rf_reg_a)
{
    hwp_sysc_awo->rf_reg_a.val = (((uint32_t)rf_reg_a << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_a_unpack(uint32_t* rf_reg_a)
{
    T_SYSC_AWO_RF_REG_A localVal = hwp_sysc_awo->rf_reg_a;

    *rf_reg_a = localVal.bit_field.rf_reg_a;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_a_getf(void)
{
    return hwp_sysc_awo->rf_reg_a.bit_field.rf_reg_a;
}

__STATIC_INLINE void sysc_awo_rf_reg_a_setf(uint32_t rf_reg_a)
{
    hwp_sysc_awo->rf_reg_a.bit_field.rf_reg_a = rf_reg_a;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_b_get(void)
{
    return hwp_sysc_awo->rf_reg_b.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_b_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_b.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_b_pack(uint32_t rf_reg_b)
{
    hwp_sysc_awo->rf_reg_b.val = (((uint32_t)rf_reg_b << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_b_unpack(uint32_t* rf_reg_b)
{
    T_SYSC_AWO_RF_REG_B localVal = hwp_sysc_awo->rf_reg_b;

    *rf_reg_b = localVal.bit_field.rf_reg_b;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_b_getf(void)
{
    return hwp_sysc_awo->rf_reg_b.bit_field.rf_reg_b;
}

__STATIC_INLINE void sysc_awo_rf_reg_b_setf(uint32_t rf_reg_b)
{
    hwp_sysc_awo->rf_reg_b.bit_field.rf_reg_b = rf_reg_b;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_c_get(void)
{
    return hwp_sysc_awo->rf_reg_c.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_c_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_c.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_c_pack(uint32_t rf_reg_c)
{
    hwp_sysc_awo->rf_reg_c.val = (((uint32_t)rf_reg_c << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_c_unpack(uint32_t* rf_reg_c)
{
    T_SYSC_AWO_RF_REG_C localVal = hwp_sysc_awo->rf_reg_c;

    *rf_reg_c = localVal.bit_field.rf_reg_c;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_c_getf(void)
{
    return hwp_sysc_awo->rf_reg_c.bit_field.rf_reg_c;
}

__STATIC_INLINE void sysc_awo_rf_reg_c_setf(uint32_t rf_reg_c)
{
    hwp_sysc_awo->rf_reg_c.bit_field.rf_reg_c = rf_reg_c;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_d_get(void)
{
    return hwp_sysc_awo->rf_reg_d.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_d_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_d.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_d_pack(uint32_t rf_reg_d)
{
    hwp_sysc_awo->rf_reg_d.val = (((uint32_t)rf_reg_d << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_d_unpack(uint32_t* rf_reg_d)
{
    T_SYSC_AWO_RF_REG_D localVal = hwp_sysc_awo->rf_reg_d;

    *rf_reg_d = localVal.bit_field.rf_reg_d;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_d_getf(void)
{
    return hwp_sysc_awo->rf_reg_d.bit_field.rf_reg_d;
}

__STATIC_INLINE void sysc_awo_rf_reg_d_setf(uint32_t rf_reg_d)
{
    hwp_sysc_awo->rf_reg_d.bit_field.rf_reg_d = rf_reg_d;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_e_get(void)
{
    return hwp_sysc_awo->rf_reg_e.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_e_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_e.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_e_pack(uint32_t rf_reg_e)
{
    hwp_sysc_awo->rf_reg_e.val = (((uint32_t)rf_reg_e << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_e_unpack(uint32_t* rf_reg_e)
{
    T_SYSC_AWO_RF_REG_E localVal = hwp_sysc_awo->rf_reg_e;

    *rf_reg_e = localVal.bit_field.rf_reg_e;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_e_getf(void)
{
    return hwp_sysc_awo->rf_reg_e.bit_field.rf_reg_e;
}

__STATIC_INLINE void sysc_awo_rf_reg_e_setf(uint32_t rf_reg_e)
{
    hwp_sysc_awo->rf_reg_e.bit_field.rf_reg_e = rf_reg_e;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_f_get(void)
{
    return hwp_sysc_awo->rf_reg_f.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_f_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_f.val = value;
}

__STATIC_INLINE void sysc_awo_rf_reg_f_pack(uint32_t rf_reg_f)
{
    hwp_sysc_awo->rf_reg_f.val = (((uint32_t)rf_reg_f << 0));
}

__STATIC_INLINE void sysc_awo_rf_reg_f_unpack(uint32_t* rf_reg_f)
{
    T_SYSC_AWO_RF_REG_F localVal = hwp_sysc_awo->rf_reg_f;

    *rf_reg_f = localVal.bit_field.rf_reg_f;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_f_getf(void)
{
    return hwp_sysc_awo->rf_reg_f.bit_field.rf_reg_f;
}

__STATIC_INLINE void sysc_awo_rf_reg_f_setf(uint32_t rf_reg_f)
{
    hwp_sysc_awo->rf_reg_f.bit_field.rf_reg_f = rf_reg_f;
}

__STATIC_INLINE uint32_t sysc_awo_rf_reg_rd_get(void)
{
    return hwp_sysc_awo->rf_reg_rd.val;
}

__STATIC_INLINE void sysc_awo_rf_reg_rd_unpack(uint32_t* i_rf_reg_ro)
{
    T_SYSC_AWO_RF_REG_RD localVal = hwp_sysc_awo->rf_reg_rd;

    *i_rf_reg_ro = localVal.bit_field.i_rf_reg_ro;
}

__STATIC_INLINE uint32_t sysc_awo_i_rf_reg_ro_getf(void)
{
    return hwp_sysc_awo->rf_reg_rd.bit_field.i_rf_reg_ro;
}

__STATIC_INLINE uint32_t sysc_awo_prw_pwm_wid0_get(void)
{
    return hwp_sysc_awo->prw_pwm_wid0.val;
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid0_set(uint32_t value)
{
    hwp_sysc_awo->prw_pwm_wid0.val = value;
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid0_pack(uint16_t prw_pwm0_wid_h, uint16_t prw_pwm0_wid_l)
{
    hwp_sysc_awo->prw_pwm_wid0.val = (((uint32_t)prw_pwm0_wid_h << 16) | ((uint32_t)prw_pwm0_wid_l << 0));
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid0_unpack(uint16_t* prw_pwm0_wid_h, uint16_t* prw_pwm0_wid_l)
{
    T_SYSC_AWO_PRW_PWM_WID0 localVal = hwp_sysc_awo->prw_pwm_wid0;

    *prw_pwm0_wid_h = localVal.bit_field.prw_pwm0_wid_h;
    *prw_pwm0_wid_l = localVal.bit_field.prw_pwm0_wid_l;
}

__STATIC_INLINE uint16_t sysc_awo_prw_pwm0_wid_h_getf(void)
{
    return hwp_sysc_awo->prw_pwm_wid0.bit_field.prw_pwm0_wid_h;
}

__STATIC_INLINE void sysc_awo_prw_pwm0_wid_h_setf(uint16_t prw_pwm0_wid_h)
{
    hwp_sysc_awo->prw_pwm_wid0.bit_field.prw_pwm0_wid_h = prw_pwm0_wid_h;
}

__STATIC_INLINE uint16_t sysc_awo_prw_pwm0_wid_l_getf(void)
{
    return hwp_sysc_awo->prw_pwm_wid0.bit_field.prw_pwm0_wid_l;
}

__STATIC_INLINE void sysc_awo_prw_pwm0_wid_l_setf(uint16_t prw_pwm0_wid_l)
{
    hwp_sysc_awo->prw_pwm_wid0.bit_field.prw_pwm0_wid_l = prw_pwm0_wid_l;
}

__STATIC_INLINE uint32_t sysc_awo_prw_pwm_wid1_get(void)
{
    return hwp_sysc_awo->prw_pwm_wid1.val;
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid1_set(uint32_t value)
{
    hwp_sysc_awo->prw_pwm_wid1.val = value;
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid1_pack(uint16_t prw_pwm1_wid_h, uint16_t prw_pwm1_wid_l)
{
    hwp_sysc_awo->prw_pwm_wid1.val = (((uint32_t)prw_pwm1_wid_h << 16) | ((uint32_t)prw_pwm1_wid_l << 0));
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid1_unpack(uint16_t* prw_pwm1_wid_h, uint16_t* prw_pwm1_wid_l)
{
    T_SYSC_AWO_PRW_PWM_WID1 localVal = hwp_sysc_awo->prw_pwm_wid1;

    *prw_pwm1_wid_h = localVal.bit_field.prw_pwm1_wid_h;
    *prw_pwm1_wid_l = localVal.bit_field.prw_pwm1_wid_l;
}

__STATIC_INLINE uint16_t sysc_awo_prw_pwm1_wid_h_getf(void)
{
    return hwp_sysc_awo->prw_pwm_wid1.bit_field.prw_pwm1_wid_h;
}

__STATIC_INLINE void sysc_awo_prw_pwm1_wid_h_setf(uint16_t prw_pwm1_wid_h)
{
    hwp_sysc_awo->prw_pwm_wid1.bit_field.prw_pwm1_wid_h = prw_pwm1_wid_h;
}

__STATIC_INLINE uint16_t sysc_awo_prw_pwm1_wid_l_getf(void)
{
    return hwp_sysc_awo->prw_pwm_wid1.bit_field.prw_pwm1_wid_l;
}

__STATIC_INLINE void sysc_awo_prw_pwm1_wid_l_setf(uint16_t prw_pwm1_wid_l)
{
    hwp_sysc_awo->prw_pwm_wid1.bit_field.prw_pwm1_wid_l = prw_pwm1_wid_l;
}

__STATIC_INLINE uint32_t sysc_awo_prw_pwm_wid2_get(void)
{
    return hwp_sysc_awo->prw_pwm_wid2.val;
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid2_set(uint32_t value)
{
    hwp_sysc_awo->prw_pwm_wid2.val = value;
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid2_pack(uint16_t prw_pwm2_wid_h, uint16_t prw_pwm2_wid_l)
{
    hwp_sysc_awo->prw_pwm_wid2.val = (((uint32_t)prw_pwm2_wid_h << 16) | ((uint32_t)prw_pwm2_wid_l << 0));
}

__STATIC_INLINE void sysc_awo_prw_pwm_wid2_unpack(uint16_t* prw_pwm2_wid_h, uint16_t* prw_pwm2_wid_l)
{
    T_SYSC_AWO_PRW_PWM_WID2 localVal = hwp_sysc_awo->prw_pwm_wid2;

    *prw_pwm2_wid_h = localVal.bit_field.prw_pwm2_wid_h;
    *prw_pwm2_wid_l = localVal.bit_field.prw_pwm2_wid_l;
}

__STATIC_INLINE uint16_t sysc_awo_prw_pwm2_wid_h_getf(void)
{
    return hwp_sysc_awo->prw_pwm_wid2.bit_field.prw_pwm2_wid_h;
}

__STATIC_INLINE void sysc_awo_prw_pwm2_wid_h_setf(uint16_t prw_pwm2_wid_h)
{
    hwp_sysc_awo->prw_pwm_wid2.bit_field.prw_pwm2_wid_h = prw_pwm2_wid_h;
}

__STATIC_INLINE uint16_t sysc_awo_prw_pwm2_wid_l_getf(void)
{
    return hwp_sysc_awo->prw_pwm_wid2.bit_field.prw_pwm2_wid_l;
}

__STATIC_INLINE void sysc_awo_prw_pwm2_wid_l_setf(uint16_t prw_pwm2_wid_l)
{
    hwp_sysc_awo->prw_pwm_wid2.bit_field.prw_pwm2_wid_l = prw_pwm2_wid_l;
}

__STATIC_INLINE uint32_t sysc_awo_prw_pwm_ctrl_get(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.val;
}

__STATIC_INLINE void sysc_awo_prw_pwm_ctrl_set(uint32_t value)
{
    hwp_sysc_awo->prw_pwm_ctrl.val = value;
}

__STATIC_INLINE void sysc_awo_prw_pwm_ctrl_pack(uint8_t prw_pwm2_en, uint8_t prw_pwm2_fc_h, uint8_t prw_pwm1_en, uint8_t prw_pwm1_fc_h, uint8_t prw_pwm0_en, uint8_t prw_pwm0_fc_h)
{
    hwp_sysc_awo->prw_pwm_ctrl.val = (((uint32_t)prw_pwm2_en << 20) | ((uint32_t)prw_pwm2_fc_h << 16) | ((uint32_t)prw_pwm1_en << 12) | ((uint32_t)prw_pwm1_fc_h << 8) | ((uint32_t)prw_pwm0_en << 4) | ((uint32_t)prw_pwm0_fc_h << 0));
}

__STATIC_INLINE void sysc_awo_prw_pwm_ctrl_unpack(uint8_t* prw_pwm2_en, uint8_t* prw_pwm2_fc_h, uint8_t* prw_pwm1_en, uint8_t* prw_pwm1_fc_h, uint8_t* prw_pwm0_en, uint8_t* prw_pwm0_fc_h)
{
    T_SYSC_AWO_PRW_PWM_CTRL localVal = hwp_sysc_awo->prw_pwm_ctrl;

    *prw_pwm2_en = localVal.bit_field.prw_pwm2_en;
    *prw_pwm2_fc_h = localVal.bit_field.prw_pwm2_fc_h;
    *prw_pwm1_en = localVal.bit_field.prw_pwm1_en;
    *prw_pwm1_fc_h = localVal.bit_field.prw_pwm1_fc_h;
    *prw_pwm0_en = localVal.bit_field.prw_pwm0_en;
    *prw_pwm0_fc_h = localVal.bit_field.prw_pwm0_fc_h;
}

__STATIC_INLINE uint8_t sysc_awo_prw_pwm2_en_getf(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm2_en;
}

__STATIC_INLINE void sysc_awo_prw_pwm2_en_setf(uint8_t prw_pwm2_en)
{
    hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm2_en = prw_pwm2_en;
}

__STATIC_INLINE uint8_t sysc_awo_prw_pwm2_fc_h_getf(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm2_fc_h;
}

__STATIC_INLINE void sysc_awo_prw_pwm2_fc_h_setf(uint8_t prw_pwm2_fc_h)
{
    hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm2_fc_h = prw_pwm2_fc_h;
}

__STATIC_INLINE uint8_t sysc_awo_prw_pwm1_en_getf(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm1_en;
}

__STATIC_INLINE void sysc_awo_prw_pwm1_en_setf(uint8_t prw_pwm1_en)
{
    hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm1_en = prw_pwm1_en;
}

__STATIC_INLINE uint8_t sysc_awo_prw_pwm1_fc_h_getf(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm1_fc_h;
}

__STATIC_INLINE void sysc_awo_prw_pwm1_fc_h_setf(uint8_t prw_pwm1_fc_h)
{
    hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm1_fc_h = prw_pwm1_fc_h;
}

__STATIC_INLINE uint8_t sysc_awo_prw_pwm0_en_getf(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm0_en;
}

__STATIC_INLINE void sysc_awo_prw_pwm0_en_setf(uint8_t prw_pwm0_en)
{
    hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm0_en = prw_pwm0_en;
}

__STATIC_INLINE uint8_t sysc_awo_prw_pwm0_fc_h_getf(void)
{
    return hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm0_fc_h;
}

__STATIC_INLINE void sysc_awo_prw_pwm0_fc_h_setf(uint8_t prw_pwm0_fc_h)
{
    hwp_sysc_awo->prw_pwm_ctrl.bit_field.prw_pwm0_fc_h = prw_pwm0_fc_h;
}

__STATIC_INLINE uint32_t sysc_awo_boot_mode_get(void)
{
    return hwp_sysc_awo->boot_mode.val;
}

__STATIC_INLINE void sysc_awo_boot_mode_unpack(uint8_t* boot_mode)
{
    T_SYSC_AWO_BOOT_MODE localVal = hwp_sysc_awo->boot_mode;

    *boot_mode = localVal.bit_field.boot_mode;
}

__STATIC_INLINE uint8_t sysc_awo_boot_mode_getf(void)
{
    return hwp_sysc_awo->boot_mode.bit_field.boot_mode;
}

__STATIC_INLINE uint32_t sysc_awo_awo_gpo_en_get(void)
{
    return hwp_sysc_awo->awo_gpo_en.val;
}

__STATIC_INLINE void sysc_awo_awo_gpo_en_set(uint32_t value)
{
    hwp_sysc_awo->awo_gpo_en.val = value;
}

__STATIC_INLINE void sysc_awo_awo_gpo_en_pack(uint32_t awo_gpo_en)
{
    hwp_sysc_awo->awo_gpo_en.val = (((uint32_t)awo_gpo_en << 0));
}

__STATIC_INLINE void sysc_awo_awo_gpo_en_unpack(uint32_t* awo_gpo_en)
{
    T_SYSC_AWO_AWO_GPO_EN localVal = hwp_sysc_awo->awo_gpo_en;

    *awo_gpo_en = localVal.bit_field.awo_gpo_en;
}

__STATIC_INLINE uint32_t sysc_awo_awo_gpo_en_getf(void)
{
    return hwp_sysc_awo->awo_gpo_en.bit_field.awo_gpo_en;
}

__STATIC_INLINE void sysc_awo_awo_gpo_en_setf(uint32_t awo_gpo_en)
{
    hwp_sysc_awo->awo_gpo_en.bit_field.awo_gpo_en = awo_gpo_en;
}

__STATIC_INLINE uint32_t sysc_awo_awo_gpo_get(void)
{
    return hwp_sysc_awo->awo_gpo.val;
}

__STATIC_INLINE void sysc_awo_awo_gpo_set(uint32_t value)
{
    hwp_sysc_awo->awo_gpo.val = value;
}

__STATIC_INLINE void sysc_awo_awo_gpo_pack(uint32_t awo_gpo)
{
    hwp_sysc_awo->awo_gpo.val = (((uint32_t)awo_gpo << 0));
}

__STATIC_INLINE void sysc_awo_awo_gpo_unpack(uint32_t* awo_gpo)
{
    T_SYSC_AWO_AWO_GPO localVal = hwp_sysc_awo->awo_gpo;

    *awo_gpo = localVal.bit_field.awo_gpo;
}

__STATIC_INLINE uint32_t sysc_awo_awo_gpo_getf(void)
{
    return hwp_sysc_awo->awo_gpo.bit_field.awo_gpo;
}

__STATIC_INLINE void sysc_awo_awo_gpo_setf(uint32_t awo_gpo)
{
    hwp_sysc_awo->awo_gpo.bit_field.awo_gpo = awo_gpo;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ds0_get(void)
{
    return hwp_sysc_awo->gpio_ds0.val;
}

__STATIC_INLINE void sysc_awo_gpio_ds0_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ds0.val = value;
}

__STATIC_INLINE void sysc_awo_gpio_ds0_pack(uint32_t gpio_ds0)
{
    hwp_sysc_awo->gpio_ds0.val = (((uint32_t)gpio_ds0 << 0));
}

__STATIC_INLINE void sysc_awo_gpio_ds0_unpack(uint32_t* gpio_ds0)
{
    T_SYSC_AWO_GPIO_DS0 localVal = hwp_sysc_awo->gpio_ds0;

    *gpio_ds0 = localVal.bit_field.gpio_ds0;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ds0_getf(void)
{
    return hwp_sysc_awo->gpio_ds0.bit_field.gpio_ds0;
}

__STATIC_INLINE void sysc_awo_gpio_ds0_setf(uint32_t gpio_ds0)
{
    hwp_sysc_awo->gpio_ds0.bit_field.gpio_ds0 = gpio_ds0;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ds1_get(void)
{
    return hwp_sysc_awo->gpio_ds1.val;
}

__STATIC_INLINE void sysc_awo_gpio_ds1_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ds1.val = value;
}

__STATIC_INLINE void sysc_awo_gpio_ds1_pack(uint32_t gpio_ds1)
{
    hwp_sysc_awo->gpio_ds1.val = (((uint32_t)gpio_ds1 << 0));
}

__STATIC_INLINE void sysc_awo_gpio_ds1_unpack(uint32_t* gpio_ds1)
{
    T_SYSC_AWO_GPIO_DS1 localVal = hwp_sysc_awo->gpio_ds1;

    *gpio_ds1 = localVal.bit_field.gpio_ds1;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ds1_getf(void)
{
    return hwp_sysc_awo->gpio_ds1.bit_field.gpio_ds1;
}

__STATIC_INLINE void sysc_awo_gpio_ds1_setf(uint32_t gpio_ds1)
{
    hwp_sysc_awo->gpio_ds1.bit_field.gpio_ds1 = gpio_ds1;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ie_get(void)
{
    return hwp_sysc_awo->gpio_ie.val;
}

__STATIC_INLINE void sysc_awo_gpio_ie_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ie.val = value;
}

__STATIC_INLINE void sysc_awo_gpio_ie_pack(uint32_t gpio_ie)
{
    hwp_sysc_awo->gpio_ie.val = (((uint32_t)gpio_ie << 0));
}

__STATIC_INLINE void sysc_awo_gpio_ie_unpack(uint32_t* gpio_ie)
{
    T_SYSC_AWO_GPIO_IE localVal = hwp_sysc_awo->gpio_ie;

    *gpio_ie = localVal.bit_field.gpio_ie;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ie_getf(void)
{
    return hwp_sysc_awo->gpio_ie.bit_field.gpio_ie;
}

__STATIC_INLINE void sysc_awo_gpio_ie_setf(uint32_t gpio_ie)
{
    hwp_sysc_awo->gpio_ie.bit_field.gpio_ie = gpio_ie;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_is_get(void)
{
    return hwp_sysc_awo->gpio_is.val;
}

__STATIC_INLINE void sysc_awo_gpio_is_set(uint32_t value)
{
    hwp_sysc_awo->gpio_is.val = value;
}

__STATIC_INLINE void sysc_awo_gpio_is_pack(uint32_t gpio_is)
{
    hwp_sysc_awo->gpio_is.val = (((uint32_t)gpio_is << 0));
}

__STATIC_INLINE void sysc_awo_gpio_is_unpack(uint32_t* gpio_is)
{
    T_SYSC_AWO_GPIO_IS localVal = hwp_sysc_awo->gpio_is;

    *gpio_is = localVal.bit_field.gpio_is;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_is_getf(void)
{
    return hwp_sysc_awo->gpio_is.bit_field.gpio_is;
}

__STATIC_INLINE void sysc_awo_gpio_is_setf(uint32_t gpio_is)
{
    hwp_sysc_awo->gpio_is.bit_field.gpio_is = gpio_is;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_pe_get(void)
{
    return hwp_sysc_awo->gpio_pe.val;
}

__STATIC_INLINE void sysc_awo_gpio_pe_set(uint32_t value)
{
    hwp_sysc_awo->gpio_pe.val = value;
}

__STATIC_INLINE void sysc_awo_gpio_pe_pack(uint32_t gpio_pe)
{
    hwp_sysc_awo->gpio_pe.val = (((uint32_t)gpio_pe << 0));
}

__STATIC_INLINE void sysc_awo_gpio_pe_unpack(uint32_t* gpio_pe)
{
    T_SYSC_AWO_GPIO_PE localVal = hwp_sysc_awo->gpio_pe;

    *gpio_pe = localVal.bit_field.gpio_pe;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_pe_getf(void)
{
    return hwp_sysc_awo->gpio_pe.bit_field.gpio_pe;
}

__STATIC_INLINE void sysc_awo_gpio_pe_setf(uint32_t gpio_pe)
{
    hwp_sysc_awo->gpio_pe.bit_field.gpio_pe = gpio_pe;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ps_get(void)
{
    return hwp_sysc_awo->gpio_ps.val;
}

__STATIC_INLINE void sysc_awo_gpio_ps_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ps.val = value;
}

__STATIC_INLINE void sysc_awo_gpio_ps_pack(uint32_t gpio_ps)
{
    hwp_sysc_awo->gpio_ps.val = (((uint32_t)gpio_ps << 0));
}

__STATIC_INLINE void sysc_awo_gpio_ps_unpack(uint32_t* gpio_ps)
{
    T_SYSC_AWO_GPIO_PS localVal = hwp_sysc_awo->gpio_ps;

    *gpio_ps = localVal.bit_field.gpio_ps;
}

__STATIC_INLINE uint32_t sysc_awo_gpio_ps_getf(void)
{
    return hwp_sysc_awo->gpio_ps.bit_field.gpio_ps;
}

__STATIC_INLINE void sysc_awo_gpio_ps_setf(uint32_t gpio_ps)
{
    hwp_sysc_awo->gpio_ps.bit_field.gpio_ps = gpio_ps;
}

__STATIC_INLINE uint32_t sysc_awo_prw_stat0_get(void)
{
    return hwp_sysc_awo->prw_stat0.val;
}

__STATIC_INLINE void sysc_awo_prw_stat0_unpack(uint8_t* pd_cpu_voltage_stat, uint8_t* pd_sram_wpulse, uint8_t* pd_sram_ra, uint8_t* pd_sram_wa, uint8_t* pd_sram_rm, uint8_t* pd_sram_rme)
{
    T_SYSC_AWO_PRW_STAT0 localVal = hwp_sysc_awo->prw_stat0;

    *pd_cpu_voltage_stat = localVal.bit_field.pd_cpu_voltage_stat;
    *pd_sram_wpulse = localVal.bit_field.pd_sram_wpulse;
    *pd_sram_ra = localVal.bit_field.pd_sram_ra;
    *pd_sram_wa = localVal.bit_field.pd_sram_wa;
    *pd_sram_rm = localVal.bit_field.pd_sram_rm;
    *pd_sram_rme = localVal.bit_field.pd_sram_rme;
}

__STATIC_INLINE uint8_t sysc_awo_pd_cpu_voltage_stat_getf(void)
{
    return hwp_sysc_awo->prw_stat0.bit_field.pd_cpu_voltage_stat;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_wpulse_getf(void)
{
    return hwp_sysc_awo->prw_stat0.bit_field.pd_sram_wpulse;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_ra_getf(void)
{
    return hwp_sysc_awo->prw_stat0.bit_field.pd_sram_ra;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_wa_getf(void)
{
    return hwp_sysc_awo->prw_stat0.bit_field.pd_sram_wa;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_rm_getf(void)
{
    return hwp_sysc_awo->prw_stat0.bit_field.pd_sram_rm;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_rme_getf(void)
{
    return hwp_sysc_awo->prw_stat0.bit_field.pd_sram_rme;
}

__STATIC_INLINE uint32_t sysc_awo_prw_stat1_get(void)
{
    return hwp_sysc_awo->prw_stat1.val;
}

__STATIC_INLINE void sysc_awo_prw_stat1_unpack(uint8_t* pd_sram_prw_on_stat)
{
    T_SYSC_AWO_PRW_STAT1 localVal = hwp_sysc_awo->prw_stat1;

    *pd_sram_prw_on_stat = localVal.bit_field.pd_sram_prw_on_stat;
}

__STATIC_INLINE uint8_t sysc_awo_pd_sram_prw_on_stat_getf(void)
{
    return hwp_sysc_awo->prw_stat1.bit_field.pd_sram_prw_on_stat;
}
#endif


