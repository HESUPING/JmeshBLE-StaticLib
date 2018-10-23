#ifndef __REG_SYSC_CPU_H__
#define __REG_SYSC_CPU_H__
#include "_reg_base_addr.h"
//clk_div_para
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              clk_sel_mdm_rx_sw :  3; /* 2: 0, clock select control signal for clk_mdm_rx*/
        uint32_t                     reserved_3 :  1; /* 3: 3,                             NA*/
        uint32_t           clk_sel_mdm_rx_by_hw :  1; /* 4: 4, high indicates that the clk_sel for the clk_mdm_rx is controlled by the hardware signal; low indicates that clk_sel for the clk_mdm_rx is controlled by the register named clk_sel_mdm_rx_sw*/
        uint32_t                     reserved_2 :  3; /* 7: 5,                             NA*/
        uint32_t         clk_div_mdm_rx_para_m1 :  2; /* 9: 8,                             NA*/
        uint32_t                     reserved_1 :  6; /*15:10,                             NA*/
        uint32_t          clk_div_timer_para_m1 :  8; /*23:16, divider parameter from clk_16mclk = clk_16m/(clk_div_*_para_m1+1)zero means divide by 2*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_CLK_DIV_PARA;

//clkg1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_2 :  4; /* 3: 0,                             NA*/
        uint32_t                   clkg_set_wdt :  1; /* 4: 4, for clk_pbus_wdt and clk_32k_wdt*/
        uint32_t                   clkg_clr_wdt :  1; /* 5: 5, for clk_pbus_wdt and clk_32k_wdt*/
        uint32_t                  clkg_set_dmac :  1; /* 6: 6,              for clk_hbus_dmac*/
        uint32_t                  clkg_clr_dmac :  1; /* 7: 7,              for clk_hbus_dmac*/
        uint32_t                 clkg_set_cache :  1; /* 8: 8,             for clk_hbus_cache*/
        uint32_t                 clkg_clr_cache :  1; /* 9: 9,             for clk_hbus_cache*/
        uint32_t                  clkg_set_qspi :  1; /*10:10,              for clk_hbus_qspi*/
        uint32_t                  clkg_clr_qspi :  1; /*11:11,              for clk_hbus_qspi*/
        uint32_t                clkg_set_timer0 :  1; /*12:12,                 for clk_timer1*/
        uint32_t                clkg_clr_timer0 :  1; /*13:13,                 for clk_timer1*/
        uint32_t                clkg_set_timer1 :  1; /*14:14,                 for clk_timer2*/
        uint32_t                clkg_clr_timer1 :  1; /*15:15,                 for clk_timer2*/
        uint32_t                     reserved_1 :  2; /*17:16,                             NA*/
        uint32_t                   clkg_set_ecc :  1; /*18:18,               for clk_pbus_ecc*/
        uint32_t                   clkg_clr_ecc :  1; /*19:19,               for clk_pbus_ecc*/
        uint32_t                   clkg_set_mdm :  1; /*20:20, for clk_ble_mdm, clk_hbus_mdm, clk_mdm_rx and clk_32m_mdm_tx*/
        uint32_t                   clkg_clr_mdm :  1; /*21:21, for clk_ble_mdm, clk_hbus_mdm, clk_mdm_rx and clk_32m_mdm_tx*/
        uint32_t                   clkg_set_ble :  1; /*22:22,   for clk_ble and clk_hbus_ble*/
        uint32_t                   clkg_clr_ble :  1; /*23:23, write 1 to clkg*_clr_* clear the corresponding clock gate control regwrite 1 to clkg*_set_* set the corresponding clock gate control regfor clk_ble and clk_hbus_ble*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_CLKG1;

//srst
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_2 :  4; /* 3: 0,                             NA*/
        uint32_t                srst_set_dmac_n :  1; /* 4: 4,                             NA*/
        uint32_t                srst_clr_dmac_n :  1; /* 5: 5,                             NA*/
        uint32_t               srst_set_cache_n :  1; /* 6: 6,                             NA*/
        uint32_t               srst_clr_cache_n :  1; /* 7: 7,                             NA*/
        uint32_t                 srst_set_wdt_n :  1; /* 8: 8,                             NA*/
        uint32_t                 srst_clr_wdt_n :  1; /* 9: 9,                             NA*/
        uint32_t               srst_set_timer_n :  1; /*10:10,                             NA*/
        uint32_t               srst_clr_timer_n :  1; /*11:11,                             NA*/
        uint32_t                srst_set_qspi_n :  1; /*12:12,                             NA*/
        uint32_t                srst_clr_qspi_n :  1; /*13:13,                             NA*/
        uint32_t                     reserved_1 :  8; /*21:14,                             NA*/
        uint32_t                 srst_set_ecc_n :  1; /*22:22,                             NA*/
        uint32_t                 srst_clr_ecc_n :  1; /*23:23,                             NA*/
        uint32_t                 srst_set_mdm_n :  1; /*24:24,                             NA*/
        uint32_t                 srst_clr_mdm_n :  1; /*25:25, write 1 to srst*_clr_* clear the corresponding soft reset control regwrite 1 to srst*_set_* set the corresponding soft reset control reg*/
        uint32_t                     reserved_0 :  6; /*31:26,                             NA*/
    } bit_field;
} T_SYSC_CPU_SRST;

//pin_share_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        qspi_en :  4; /* 3: 0,  please see the pin_share.docx*/
        uint32_t                       spim0_en :  1; /* 4: 4,  please see the pin_share.docx*/
        uint32_t                   spim0_cs1_en :  1; /* 5: 5,  please see the pin_share.docx*/
        uint32_t                       spim1_en :  1; /* 6: 6,  please see the pin_share.docx*/
        uint32_t                   spim1_cs1_en :  1; /* 7: 7,  please see the pin_share.docx*/
        uint32_t                        spis_en :  1; /* 8: 8,  please see the pin_share.docx*/
        uint32_t                      gpio00_en :  1; /* 9: 9,  please see the pin_share.docx*/
        uint32_t                      gpio01_en :  1; /*10:10,  please see the pin_share.docx*/
        uint32_t                     reserved_2 :  2; /*12:11,                             NA*/
        uint32_t                        rfif_en :  1; /*13:13,  please see the pin_share.docx*/
        uint32_t                     reserved_1 :  2; /*15:14,                             NA*/
        uint32_t                 ble_mac_dbg_en :  8; /*23:16,  please see the pin_share.docx*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_PIN_SHARE_EN;

//func_io_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     func_io_en : 22; /*21: 0,  please see the pin_share.docx*/
        uint32_t                     reserved_0 : 10; /*31:22,                             NA*/
    } bit_field;
} T_SYSC_CPU_FUNC_IO_EN;

//func_io_sel0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  func_io00_sel :  4; /* 3: 0,                             NA*/
        uint32_t                  func_io01_sel :  4; /* 7: 4,                             NA*/
        uint32_t                  func_io02_sel :  4; /*11: 8,                             NA*/
        uint32_t                  func_io03_sel :  4; /*15:12,                             NA*/
        uint32_t                  func_io04_sel :  4; /*19:16,                             NA*/
        uint32_t                  func_io05_sel :  4; /*23:20,                             NA*/
        uint32_t                  func_io06_sel :  4; /*27:24,                             NA*/
        uint32_t                  func_io07_sel :  4; /*31:28, The func_io is the function programmable IO which function is programmable. The function of the func_io is listed in the bx2401.xlsx(pin_share). The function of the func_io can be any function in the table depends on the func_io_selX control register in the sysc_cpu. refer to the pin_share.docx*/
    } bit_field;
} T_SYSC_CPU_FUNC_IO_SEL0;

//func_io_sel1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  func_io08_sel :  4; /* 3: 0,                             NA*/
        uint32_t                  func_io09_sel :  4; /* 7: 4,                             NA*/
        uint32_t                  func_io10_sel :  4; /*11: 8,                             NA*/
        uint32_t                  func_io11_sel :  4; /*15:12,                             NA*/
        uint32_t                  func_io12_sel :  4; /*19:16,                             NA*/
        uint32_t                  func_io13_sel :  4; /*23:20,                             NA*/
        uint32_t                  func_io14_sel :  4; /*27:24,                             NA*/
        uint32_t                  func_io15_sel :  4; /*31:28,                             NA*/
    } bit_field;
} T_SYSC_CPU_FUNC_IO_SEL1;

//func_io_sel2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  func_io16_sel :  4; /* 3: 0,                             NA*/
        uint32_t                  func_io17_sel :  4; /* 7: 4,                             NA*/
        uint32_t                  func_io18_sel :  4; /*11: 8,                             NA*/
        uint32_t                  func_io19_sel :  4; /*15:12,                             NA*/
        uint32_t                  func_io20_sel :  4; /*19:16,                             NA*/
        uint32_t                  func_io21_sel :  4; /*23:20,                             NA*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_FUNC_IO_SEL2;

//sys_ctrl0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 cache_has_sram :  1; /* 0: 0, high means the cache has the priority to access the SRAM6~9 of the system(0x130000~0x134000)*/
        uint32_t                    adc_has_dma :  1; /* 1: 1, high means the adc has the dma peripheral channel 15 instead of the RX of IIC1*/
        uint32_t                     reserved_3 :  2; /* 3: 2,                             NA*/
        uint32_t                   mdm_has_sram :  1; /* 4: 4, high means the rx_cap has the priority to access the SRAM4 of the system(0x120000~0x128000)*/
        uint32_t                     reserved_2 :  3; /* 7: 5,                             NA*/
        uint32_t                   adc_has_sram :  1; /* 8: 8, high means adc has the priority to access the SRAM4 of the system(0x120000~0x128000)*/
        uint32_t                     reserved_1 : 15; /*23: 9,                             NA*/
        uint32_t                       brom_rme :  1; /*24:24,           rme input of the ROM*/
        uint32_t                     reserved_0 :  3; /*27:25,                             NA*/
        uint32_t                        brom_rm :  4; /*31:28,            rm input of the ROM*/
    } bit_field;
} T_SYSC_CPU_SYS_CTRL0;

//sft_intr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       sft_intr :  1; /* 0: 0, software interrupt, high active*/
        uint32_t                     reserved_0 : 31; /*31: 1,                             NA*/
    } bit_field;
} T_SYSC_CPU_SFT_INTR;

//calb32
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  calb32k_start :  1; /* 0: 0,  32KHz clock calibration start*/
        uint32_t                     reserved_1 : 11; /*11: 1,                             NA*/
        uint32_t                   calb32k_rslt : 18; /*29:12, 32KHz clock calibration result; calb32k_rslt = 64*16MHz/32KHz*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_CALB32;

//pgspy_addr0_l
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  pgspy_addr0_l : 24; /*23: 0, min address of the address spy space0*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_ADDR0_L;

//pgspy_addr0_h
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  pgspy_addr0_h : 24; /*23: 0, max address of the address spy space0*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_ADDR0_H;

//pgspy_addr1_l
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  pgspy_addr1_l : 24; /*23: 0, min address of the address spy space1*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_ADDR1_L;

//pgspy_addr1_h
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  pgspy_addr1_h : 24; /*23: 0, max address of the address spy space1*/
        uint32_t                     reserved_0 :  8; /*31:24,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_ADDR1_H;

//pgspy_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       pgspy_en :  2; /* 1: 0,      page spy interrupt enable*/
        uint32_t                     reserved_0 : 30; /*31: 2,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_EN;

//pgspy_intr_mask
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                pgspy_intr_mask :  2; /* 1: 0,        page spy interrupt mask*/
        uint32_t                     reserved_0 : 30; /*31: 2,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_INTR_MASK;

//pgspy_intr_raw
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 pgspy_intr_raw :  2; /* 1: 0,         page spy raw interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_INTR_RAW;

//pgspy_intr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pgspy_intr :  2; /* 1: 0,             page spy interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                             NA*/
    } bit_field;
} T_SYSC_CPU_PGSPY_INTR;

//gpio_ds0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 24; /*23: 0,                             NA*/
        uint32_t                     gpio_h_ds0 :  6; /*29:24, bit 0 of the DS(drive strength) of the Ios in the CPU power domain.Each IO has two bits inputs for drive strength control(DS0 and DS1) and there are altogether 6 Ios in the CPU power domain. Each bit of this control register is connect the the DS0 input of the IOs in the CPU power domain*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_GPIO_DS0;

//gpio_ds1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 24; /*23: 0,                             NA*/
        uint32_t                     gpio_h_ds1 :  6; /*29:24, bit 1 of the DS(drive strength) of the Ios in the CPU power domainEach IO has two bits inputs for drive strength control(DS0 and DS1) and there are altogether 6 Ios in the CPU power domain. Each bit of this control register is connect the the DS1 input of the IOs in the CPU power domain*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_GPIO_DS1;

//gpio_ie
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 24; /*23: 0,                             NA*/
        uint32_t                      gpio_h_ie :  6; /*29:24, input enable of the IO, high active*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_GPIO_IE;

//gpio_is
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 24; /*23: 0,                             NA*/
        uint32_t                      gpio_h_is :  6; /*29:24, input schmitt enable of the IO, high active*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_GPIO_IS;

//gpio_pe
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 24; /*23: 0,                             NA*/
        uint32_t                      gpio_h_pe :  6; /*29:24, pull enable of the IO, high active*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_GPIO_PE;

//gpio_ps
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 24; /*23: 0,                             NA*/
        uint32_t                      gpio_h_ps :  6; /*29:24, pull select of the IO, if gpio_h_pe is high and gpio_h_ps is high, then the IO is pulled up. if gpio_h_pe is high and gpio_h_ps is low, then the IO is pulled down.*/
        uint32_t                     reserved_0 :  2; /*31:30,                             NA*/
    } bit_field;
} T_SYSC_CPU_GPIO_PS;

//Registers Mapping to the same address

typedef struct
{
    volatile                        uint32_t                  reserved_0[2];
    volatile         T_SYSC_CPU_CLK_DIV_PARA                   clk_div_para; /*  0x8,    RW, 0x00000001,                             NA*/
    volatile                        uint32_t                  reserved_1[2];
    volatile                T_SYSC_CPU_CLKG1                          clkg1; /* 0x14,    RW, 0x00FCFFF0,                             NA*/
    volatile                 T_SYSC_CPU_SRST                           srst; /* 0x18,    RW, 0x03C03FF0,                             NA*/
    volatile                        uint32_t                     reserved_2;
    volatile         T_SYSC_CPU_PIN_SHARE_EN                   pin_share_en; /* 0x20,    RW, 0x00000000,                             NA*/
    volatile           T_SYSC_CPU_FUNC_IO_EN                     func_io_en; /* 0x24,    RW, 0x00000000,                             NA*/
    volatile                        uint32_t                  reserved_3[2];
    volatile         T_SYSC_CPU_FUNC_IO_SEL0                   func_io_sel0; /* 0x30,    RW, 0x00000000,                             NA*/
    volatile         T_SYSC_CPU_FUNC_IO_SEL1                   func_io_sel1; /* 0x34,    RW, 0x00000000,                             NA*/
    volatile         T_SYSC_CPU_FUNC_IO_SEL2                   func_io_sel2; /* 0x38,    RW, 0x00000000,                             NA*/
    volatile                        uint32_t                     reserved_4;
    volatile            T_SYSC_CPU_SYS_CTRL0                      sys_ctrl0; /* 0x40,    RW, 0x20000000,                             NA*/
    volatile             T_SYSC_CPU_SFT_INTR                       sft_intr; /* 0x44,    RW, 0x00000000,                             NA*/
    volatile                        uint32_t                     reserved_5;
    volatile               T_SYSC_CPU_CALB32                         calb32; /* 0x4c,    RW, 0x00000000,                             NA*/
    volatile        T_SYSC_CPU_PGSPY_ADDR0_L                  pgspy_addr0_l; /* 0x50,    RW, 0x00000000,                             NA*/
    volatile        T_SYSC_CPU_PGSPY_ADDR0_H                  pgspy_addr0_h; /* 0x54,    RW, 0x00000000,                             NA*/
    volatile        T_SYSC_CPU_PGSPY_ADDR1_L                  pgspy_addr1_l; /* 0x58,    RW, 0x00000000,                             NA*/
    volatile        T_SYSC_CPU_PGSPY_ADDR1_H                  pgspy_addr1_h; /* 0x5c,    RW, 0x00000000,                             NA*/
    volatile             T_SYSC_CPU_PGSPY_EN                       pgspy_en; /* 0x60,    RW, 0x00000000,                             NA*/
    volatile      T_SYSC_CPU_PGSPY_INTR_MASK                pgspy_intr_mask; /* 0x64,    RW, 0x00000000,                             NA*/
    volatile       T_SYSC_CPU_PGSPY_INTR_RAW                 pgspy_intr_raw; /* 0x68,    RO, 0x00000000,                             NA*/
    volatile           T_SYSC_CPU_PGSPY_INTR                     pgspy_intr; /* 0x6c,    RO, 0x00000000,                             NA*/
    volatile             T_SYSC_CPU_GPIO_DS0                       gpio_ds0; /* 0x70,    RW, 0x3F000000,                             NA*/
    volatile             T_SYSC_CPU_GPIO_DS1                       gpio_ds1; /* 0x74,    RW, 0x3F000000,                             NA*/
    volatile              T_SYSC_CPU_GPIO_IE                        gpio_ie; /* 0x78,    RW, 0x3F000000,                             NA*/
    volatile              T_SYSC_CPU_GPIO_IS                        gpio_is; /* 0x7c,    RW, 0x00000000,                             NA*/
    volatile              T_SYSC_CPU_GPIO_PE                        gpio_pe; /* 0x80,    RW, 0x00000000,                             NA*/
    volatile              T_SYSC_CPU_GPIO_PS                        gpio_ps; /* 0x84,    RW, 0x00000000,                             NA*/
} T_HWP_SYSC_CPU_T;

#define hwp_sysc_cpu ((T_HWP_SYSC_CPU_T*)REG_SYSC_CPU_BASE)


__STATIC_INLINE uint32_t sysc_cpu_clk_div_para_get(void)
{
    return hwp_sysc_cpu->clk_div_para.val;
}

__STATIC_INLINE void sysc_cpu_clk_div_para_set(uint32_t value)
{
    hwp_sysc_cpu->clk_div_para.val = value;
}

__STATIC_INLINE void sysc_cpu_clk_div_para_pack(uint8_t clk_div_timer_para_m1, uint8_t clk_div_mdm_rx_para_m1, uint8_t clk_sel_mdm_rx_by_hw, uint8_t clk_sel_mdm_rx_sw)
{
    hwp_sysc_cpu->clk_div_para.val = (((uint32_t)clk_div_timer_para_m1 << 16) | ((uint32_t)clk_div_mdm_rx_para_m1 << 8) | ((uint32_t)clk_sel_mdm_rx_by_hw << 4) | ((uint32_t)clk_sel_mdm_rx_sw << 0));
}

__STATIC_INLINE void sysc_cpu_clk_div_para_unpack(uint8_t* clk_div_timer_para_m1, uint8_t* clk_div_mdm_rx_para_m1, uint8_t* clk_sel_mdm_rx_by_hw, uint8_t* clk_sel_mdm_rx_sw)
{
    T_SYSC_CPU_CLK_DIV_PARA localVal = hwp_sysc_cpu->clk_div_para;

    *clk_div_timer_para_m1 = localVal.bit_field.clk_div_timer_para_m1;
    *clk_div_mdm_rx_para_m1 = localVal.bit_field.clk_div_mdm_rx_para_m1;
    *clk_sel_mdm_rx_by_hw = localVal.bit_field.clk_sel_mdm_rx_by_hw;
    *clk_sel_mdm_rx_sw = localVal.bit_field.clk_sel_mdm_rx_sw;
}

__STATIC_INLINE uint8_t sysc_cpu_clk_div_timer_para_m1_getf(void)
{
    return hwp_sysc_cpu->clk_div_para.bit_field.clk_div_timer_para_m1;
}

__STATIC_INLINE void sysc_cpu_clk_div_timer_para_m1_setf(uint8_t clk_div_timer_para_m1)
{
    hwp_sysc_cpu->clk_div_para.bit_field.clk_div_timer_para_m1 = clk_div_timer_para_m1;
}

__STATIC_INLINE uint8_t sysc_cpu_clk_div_mdm_rx_para_m1_getf(void)
{
    return hwp_sysc_cpu->clk_div_para.bit_field.clk_div_mdm_rx_para_m1;
}

__STATIC_INLINE void sysc_cpu_clk_div_mdm_rx_para_m1_setf(uint8_t clk_div_mdm_rx_para_m1)
{
    hwp_sysc_cpu->clk_div_para.bit_field.clk_div_mdm_rx_para_m1 = clk_div_mdm_rx_para_m1;
}

__STATIC_INLINE uint8_t sysc_cpu_clk_sel_mdm_rx_by_hw_getf(void)
{
    return hwp_sysc_cpu->clk_div_para.bit_field.clk_sel_mdm_rx_by_hw;
}

__STATIC_INLINE void sysc_cpu_clk_sel_mdm_rx_by_hw_setf(uint8_t clk_sel_mdm_rx_by_hw)
{
    hwp_sysc_cpu->clk_div_para.bit_field.clk_sel_mdm_rx_by_hw = clk_sel_mdm_rx_by_hw;
}

__STATIC_INLINE uint8_t sysc_cpu_clk_sel_mdm_rx_sw_getf(void)
{
    return hwp_sysc_cpu->clk_div_para.bit_field.clk_sel_mdm_rx_sw;
}

__STATIC_INLINE void sysc_cpu_clk_sel_mdm_rx_sw_setf(uint8_t clk_sel_mdm_rx_sw)
{
    hwp_sysc_cpu->clk_div_para.bit_field.clk_sel_mdm_rx_sw = clk_sel_mdm_rx_sw;
}

__STATIC_INLINE uint32_t sysc_cpu_clkg1_get(void)
{
    return hwp_sysc_cpu->clkg1.val;
}

__STATIC_INLINE void sysc_cpu_clkg1_set(uint32_t value)
{
    hwp_sysc_cpu->clkg1.val = value;
}

__STATIC_INLINE void sysc_cpu_clkg1_pack(uint8_t clkg_clr_ble, uint8_t clkg_set_ble, uint8_t clkg_clr_mdm, uint8_t clkg_set_mdm, uint8_t clkg_clr_ecc, uint8_t clkg_set_ecc, uint8_t clkg_clr_timer1, uint8_t clkg_set_timer1, uint8_t clkg_clr_timer0, uint8_t clkg_set_timer0, uint8_t clkg_clr_qspi, uint8_t clkg_set_qspi, uint8_t clkg_clr_cache, uint8_t clkg_set_cache, uint8_t clkg_clr_dmac, uint8_t clkg_set_dmac, uint8_t clkg_clr_wdt, uint8_t clkg_set_wdt)
{
    hwp_sysc_cpu->clkg1.val = (((uint32_t)clkg_clr_ble << 23) | ((uint32_t)clkg_set_ble << 22) | ((uint32_t)clkg_clr_mdm << 21) | ((uint32_t)clkg_set_mdm << 20) | ((uint32_t)clkg_clr_ecc << 19) | ((uint32_t)clkg_set_ecc << 18) | ((uint32_t)clkg_clr_timer1 << 15) | ((uint32_t)clkg_set_timer1 << 14) | ((uint32_t)clkg_clr_timer0 << 13) | ((uint32_t)clkg_set_timer0 << 12) | ((uint32_t)clkg_clr_qspi << 11) | ((uint32_t)clkg_set_qspi << 10) | ((uint32_t)clkg_clr_cache << 9) | ((uint32_t)clkg_set_cache << 8) | ((uint32_t)clkg_clr_dmac << 7) | ((uint32_t)clkg_set_dmac << 6) | ((uint32_t)clkg_clr_wdt << 5) | ((uint32_t)clkg_set_wdt << 4));
}

__STATIC_INLINE uint32_t sysc_cpu_srst_get(void)
{
    return hwp_sysc_cpu->srst.val;
}

__STATIC_INLINE void sysc_cpu_srst_set(uint32_t value)
{
    hwp_sysc_cpu->srst.val = value;
}

__STATIC_INLINE void sysc_cpu_srst_pack(uint8_t srst_clr_mdm_n, uint8_t srst_set_mdm_n, uint8_t srst_clr_ecc_n, uint8_t srst_set_ecc_n, uint8_t srst_clr_qspi_n, uint8_t srst_set_qspi_n, uint8_t srst_clr_timer_n, uint8_t srst_set_timer_n, uint8_t srst_clr_wdt_n, uint8_t srst_set_wdt_n, uint8_t srst_clr_cache_n, uint8_t srst_set_cache_n, uint8_t srst_clr_dmac_n, uint8_t srst_set_dmac_n)
{
    hwp_sysc_cpu->srst.val = (((uint32_t)srst_clr_mdm_n << 25) | ((uint32_t)srst_set_mdm_n << 24) | ((uint32_t)srst_clr_ecc_n << 23) | ((uint32_t)srst_set_ecc_n << 22) | ((uint32_t)srst_clr_qspi_n << 13) | ((uint32_t)srst_set_qspi_n << 12) | ((uint32_t)srst_clr_timer_n << 11) | ((uint32_t)srst_set_timer_n << 10) | ((uint32_t)srst_clr_wdt_n << 9) | ((uint32_t)srst_set_wdt_n << 8) | ((uint32_t)srst_clr_cache_n << 7) | ((uint32_t)srst_set_cache_n << 6) | ((uint32_t)srst_clr_dmac_n << 5) | ((uint32_t)srst_set_dmac_n << 4));
}

__STATIC_INLINE uint32_t sysc_cpu_pin_share_en_get(void)
{
    return hwp_sysc_cpu->pin_share_en.val;
}

__STATIC_INLINE void sysc_cpu_pin_share_en_set(uint32_t value)
{
    hwp_sysc_cpu->pin_share_en.val = value;
}

__STATIC_INLINE void sysc_cpu_pin_share_en_pack(uint8_t ble_mac_dbg_en, uint8_t rfif_en, uint8_t gpio01_en, uint8_t gpio00_en, uint8_t spis_en, uint8_t spim1_cs1_en, uint8_t spim1_en, uint8_t spim0_cs1_en, uint8_t spim0_en, uint8_t qspi_en)
{
    hwp_sysc_cpu->pin_share_en.val = (((uint32_t)ble_mac_dbg_en << 16) | ((uint32_t)rfif_en << 13) | ((uint32_t)gpio01_en << 10) | ((uint32_t)gpio00_en << 9) | ((uint32_t)spis_en << 8) | ((uint32_t)spim1_cs1_en << 7) | ((uint32_t)spim1_en << 6) | ((uint32_t)spim0_cs1_en << 5) | ((uint32_t)spim0_en << 4) | ((uint32_t)qspi_en << 0));
}

__STATIC_INLINE void sysc_cpu_pin_share_en_unpack(uint8_t* ble_mac_dbg_en, uint8_t* rfif_en, uint8_t* gpio01_en, uint8_t* gpio00_en, uint8_t* spis_en, uint8_t* spim1_cs1_en, uint8_t* spim1_en, uint8_t* spim0_cs1_en, uint8_t* spim0_en, uint8_t* qspi_en)
{
    T_SYSC_CPU_PIN_SHARE_EN localVal = hwp_sysc_cpu->pin_share_en;

    *ble_mac_dbg_en = localVal.bit_field.ble_mac_dbg_en;
    *rfif_en = localVal.bit_field.rfif_en;
    *gpio01_en = localVal.bit_field.gpio01_en;
    *gpio00_en = localVal.bit_field.gpio00_en;
    *spis_en = localVal.bit_field.spis_en;
    *spim1_cs1_en = localVal.bit_field.spim1_cs1_en;
    *spim1_en = localVal.bit_field.spim1_en;
    *spim0_cs1_en = localVal.bit_field.spim0_cs1_en;
    *spim0_en = localVal.bit_field.spim0_en;
    *qspi_en = localVal.bit_field.qspi_en;
}

__STATIC_INLINE uint8_t sysc_cpu_ble_mac_dbg_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.ble_mac_dbg_en;
}

__STATIC_INLINE void sysc_cpu_ble_mac_dbg_en_setf(uint8_t ble_mac_dbg_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.ble_mac_dbg_en = ble_mac_dbg_en;
}

__STATIC_INLINE uint8_t sysc_cpu_rfif_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.rfif_en;
}

__STATIC_INLINE void sysc_cpu_rfif_en_setf(uint8_t rfif_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.rfif_en = rfif_en;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio01_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.gpio01_en;
}

__STATIC_INLINE void sysc_cpu_gpio01_en_setf(uint8_t gpio01_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.gpio01_en = gpio01_en;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio00_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.gpio00_en;
}

__STATIC_INLINE void sysc_cpu_gpio00_en_setf(uint8_t gpio00_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.gpio00_en = gpio00_en;
}

__STATIC_INLINE uint8_t sysc_cpu_spis_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spis_en;
}

__STATIC_INLINE void sysc_cpu_spis_en_setf(uint8_t spis_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spis_en = spis_en;
}

__STATIC_INLINE uint8_t sysc_cpu_spim1_cs1_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim1_cs1_en;
}

__STATIC_INLINE void sysc_cpu_spim1_cs1_en_setf(uint8_t spim1_cs1_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim1_cs1_en = spim1_cs1_en;
}

__STATIC_INLINE uint8_t sysc_cpu_spim1_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim1_en;
}

__STATIC_INLINE void sysc_cpu_spim1_en_setf(uint8_t spim1_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim1_en = spim1_en;
}

__STATIC_INLINE uint8_t sysc_cpu_spim0_cs1_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim0_cs1_en;
}

__STATIC_INLINE void sysc_cpu_spim0_cs1_en_setf(uint8_t spim0_cs1_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim0_cs1_en = spim0_cs1_en;
}

__STATIC_INLINE uint8_t sysc_cpu_spim0_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim0_en;
}

__STATIC_INLINE void sysc_cpu_spim0_en_setf(uint8_t spim0_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim0_en = spim0_en;
}

__STATIC_INLINE uint8_t sysc_cpu_qspi_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.qspi_en;
}

__STATIC_INLINE void sysc_cpu_qspi_en_setf(uint8_t qspi_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.qspi_en = qspi_en;
}

__STATIC_INLINE uint32_t sysc_cpu_func_io_en_get(void)
{
    return hwp_sysc_cpu->func_io_en.val;
}

__STATIC_INLINE void sysc_cpu_func_io_en_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_en.val = value;
}

__STATIC_INLINE void sysc_cpu_func_io_en_pack(uint32_t func_io_en)
{
    hwp_sysc_cpu->func_io_en.val = (((uint32_t)func_io_en << 0));
}

__STATIC_INLINE void sysc_cpu_func_io_en_unpack(uint32_t* func_io_en)
{
    T_SYSC_CPU_FUNC_IO_EN localVal = hwp_sysc_cpu->func_io_en;

    *func_io_en = localVal.bit_field.func_io_en;
}

__STATIC_INLINE uint32_t sysc_cpu_func_io_en_getf(void)
{
    return hwp_sysc_cpu->func_io_en.bit_field.func_io_en;
}

__STATIC_INLINE void sysc_cpu_func_io_en_setf(uint32_t func_io_en)
{
    hwp_sysc_cpu->func_io_en.bit_field.func_io_en = func_io_en;
}

__STATIC_INLINE uint32_t sysc_cpu_func_io_sel0_get(void)
{
    return hwp_sysc_cpu->func_io_sel0.val;
}

__STATIC_INLINE void sysc_cpu_func_io_sel0_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_sel0.val = value;
}

__STATIC_INLINE void sysc_cpu_func_io_sel0_pack(uint8_t func_io07_sel, uint8_t func_io06_sel, uint8_t func_io05_sel, uint8_t func_io04_sel, uint8_t func_io03_sel, uint8_t func_io02_sel, uint8_t func_io01_sel, uint8_t func_io00_sel)
{
    hwp_sysc_cpu->func_io_sel0.val = (((uint32_t)func_io07_sel << 28) | ((uint32_t)func_io06_sel << 24) | ((uint32_t)func_io05_sel << 20) | ((uint32_t)func_io04_sel << 16) | ((uint32_t)func_io03_sel << 12) | ((uint32_t)func_io02_sel << 8) | ((uint32_t)func_io01_sel << 4) | ((uint32_t)func_io00_sel << 0));
}

__STATIC_INLINE void sysc_cpu_func_io_sel0_unpack(uint8_t* func_io07_sel, uint8_t* func_io06_sel, uint8_t* func_io05_sel, uint8_t* func_io04_sel, uint8_t* func_io03_sel, uint8_t* func_io02_sel, uint8_t* func_io01_sel, uint8_t* func_io00_sel)
{
    T_SYSC_CPU_FUNC_IO_SEL0 localVal = hwp_sysc_cpu->func_io_sel0;

    *func_io07_sel = localVal.bit_field.func_io07_sel;
    *func_io06_sel = localVal.bit_field.func_io06_sel;
    *func_io05_sel = localVal.bit_field.func_io05_sel;
    *func_io04_sel = localVal.bit_field.func_io04_sel;
    *func_io03_sel = localVal.bit_field.func_io03_sel;
    *func_io02_sel = localVal.bit_field.func_io02_sel;
    *func_io01_sel = localVal.bit_field.func_io01_sel;
    *func_io00_sel = localVal.bit_field.func_io00_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io07_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io07_sel;
}

__STATIC_INLINE void sysc_cpu_func_io07_sel_setf(uint8_t func_io07_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io07_sel = func_io07_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io06_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io06_sel;
}

__STATIC_INLINE void sysc_cpu_func_io06_sel_setf(uint8_t func_io06_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io06_sel = func_io06_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io05_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io05_sel;
}

__STATIC_INLINE void sysc_cpu_func_io05_sel_setf(uint8_t func_io05_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io05_sel = func_io05_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io04_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io04_sel;
}

__STATIC_INLINE void sysc_cpu_func_io04_sel_setf(uint8_t func_io04_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io04_sel = func_io04_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io03_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io03_sel;
}

__STATIC_INLINE void sysc_cpu_func_io03_sel_setf(uint8_t func_io03_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io03_sel = func_io03_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io02_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io02_sel;
}

__STATIC_INLINE void sysc_cpu_func_io02_sel_setf(uint8_t func_io02_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io02_sel = func_io02_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io01_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io01_sel;
}

__STATIC_INLINE void sysc_cpu_func_io01_sel_setf(uint8_t func_io01_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io01_sel = func_io01_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io00_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io00_sel;
}

__STATIC_INLINE void sysc_cpu_func_io00_sel_setf(uint8_t func_io00_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io00_sel = func_io00_sel;
}

__STATIC_INLINE uint32_t sysc_cpu_func_io_sel1_get(void)
{
    return hwp_sysc_cpu->func_io_sel1.val;
}

__STATIC_INLINE void sysc_cpu_func_io_sel1_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_sel1.val = value;
}

__STATIC_INLINE void sysc_cpu_func_io_sel1_pack(uint8_t func_io15_sel, uint8_t func_io14_sel, uint8_t func_io13_sel, uint8_t func_io12_sel, uint8_t func_io11_sel, uint8_t func_io10_sel, uint8_t func_io09_sel, uint8_t func_io08_sel)
{
    hwp_sysc_cpu->func_io_sel1.val = (((uint32_t)func_io15_sel << 28) | ((uint32_t)func_io14_sel << 24) | ((uint32_t)func_io13_sel << 20) | ((uint32_t)func_io12_sel << 16) | ((uint32_t)func_io11_sel << 12) | ((uint32_t)func_io10_sel << 8) | ((uint32_t)func_io09_sel << 4) | ((uint32_t)func_io08_sel << 0));
}

__STATIC_INLINE void sysc_cpu_func_io_sel1_unpack(uint8_t* func_io15_sel, uint8_t* func_io14_sel, uint8_t* func_io13_sel, uint8_t* func_io12_sel, uint8_t* func_io11_sel, uint8_t* func_io10_sel, uint8_t* func_io09_sel, uint8_t* func_io08_sel)
{
    T_SYSC_CPU_FUNC_IO_SEL1 localVal = hwp_sysc_cpu->func_io_sel1;

    *func_io15_sel = localVal.bit_field.func_io15_sel;
    *func_io14_sel = localVal.bit_field.func_io14_sel;
    *func_io13_sel = localVal.bit_field.func_io13_sel;
    *func_io12_sel = localVal.bit_field.func_io12_sel;
    *func_io11_sel = localVal.bit_field.func_io11_sel;
    *func_io10_sel = localVal.bit_field.func_io10_sel;
    *func_io09_sel = localVal.bit_field.func_io09_sel;
    *func_io08_sel = localVal.bit_field.func_io08_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io15_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io15_sel;
}

__STATIC_INLINE void sysc_cpu_func_io15_sel_setf(uint8_t func_io15_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io15_sel = func_io15_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io14_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io14_sel;
}

__STATIC_INLINE void sysc_cpu_func_io14_sel_setf(uint8_t func_io14_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io14_sel = func_io14_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io13_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io13_sel;
}

__STATIC_INLINE void sysc_cpu_func_io13_sel_setf(uint8_t func_io13_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io13_sel = func_io13_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io12_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io12_sel;
}

__STATIC_INLINE void sysc_cpu_func_io12_sel_setf(uint8_t func_io12_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io12_sel = func_io12_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io11_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io11_sel;
}

__STATIC_INLINE void sysc_cpu_func_io11_sel_setf(uint8_t func_io11_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io11_sel = func_io11_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io10_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io10_sel;
}

__STATIC_INLINE void sysc_cpu_func_io10_sel_setf(uint8_t func_io10_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io10_sel = func_io10_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io09_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io09_sel;
}

__STATIC_INLINE void sysc_cpu_func_io09_sel_setf(uint8_t func_io09_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io09_sel = func_io09_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io08_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io08_sel;
}

__STATIC_INLINE void sysc_cpu_func_io08_sel_setf(uint8_t func_io08_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io08_sel = func_io08_sel;
}

__STATIC_INLINE uint32_t sysc_cpu_func_io_sel2_get(void)
{
    return hwp_sysc_cpu->func_io_sel2.val;
}

__STATIC_INLINE void sysc_cpu_func_io_sel2_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_sel2.val = value;
}

__STATIC_INLINE void sysc_cpu_func_io_sel2_pack(uint8_t func_io21_sel, uint8_t func_io20_sel, uint8_t func_io19_sel, uint8_t func_io18_sel, uint8_t func_io17_sel, uint8_t func_io16_sel)
{
    hwp_sysc_cpu->func_io_sel2.val = (((uint32_t)func_io21_sel << 20) | ((uint32_t)func_io20_sel << 16) | ((uint32_t)func_io19_sel << 12) | ((uint32_t)func_io18_sel << 8) | ((uint32_t)func_io17_sel << 4) | ((uint32_t)func_io16_sel << 0));
}

__STATIC_INLINE void sysc_cpu_func_io_sel2_unpack(uint8_t* func_io21_sel, uint8_t* func_io20_sel, uint8_t* func_io19_sel, uint8_t* func_io18_sel, uint8_t* func_io17_sel, uint8_t* func_io16_sel)
{
    T_SYSC_CPU_FUNC_IO_SEL2 localVal = hwp_sysc_cpu->func_io_sel2;

    *func_io21_sel = localVal.bit_field.func_io21_sel;
    *func_io20_sel = localVal.bit_field.func_io20_sel;
    *func_io19_sel = localVal.bit_field.func_io19_sel;
    *func_io18_sel = localVal.bit_field.func_io18_sel;
    *func_io17_sel = localVal.bit_field.func_io17_sel;
    *func_io16_sel = localVal.bit_field.func_io16_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io21_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io21_sel;
}

__STATIC_INLINE void sysc_cpu_func_io21_sel_setf(uint8_t func_io21_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io21_sel = func_io21_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io20_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io20_sel;
}

__STATIC_INLINE void sysc_cpu_func_io20_sel_setf(uint8_t func_io20_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io20_sel = func_io20_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io19_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io19_sel;
}

__STATIC_INLINE void sysc_cpu_func_io19_sel_setf(uint8_t func_io19_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io19_sel = func_io19_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io18_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io18_sel;
}

__STATIC_INLINE void sysc_cpu_func_io18_sel_setf(uint8_t func_io18_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io18_sel = func_io18_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io17_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io17_sel;
}

__STATIC_INLINE void sysc_cpu_func_io17_sel_setf(uint8_t func_io17_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io17_sel = func_io17_sel;
}

__STATIC_INLINE uint8_t sysc_cpu_func_io16_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io16_sel;
}

__STATIC_INLINE void sysc_cpu_func_io16_sel_setf(uint8_t func_io16_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io16_sel = func_io16_sel;
}

__STATIC_INLINE uint32_t sysc_cpu_sys_ctrl0_get(void)
{
    return hwp_sysc_cpu->sys_ctrl0.val;
}

__STATIC_INLINE void sysc_cpu_sys_ctrl0_set(uint32_t value)
{
    hwp_sysc_cpu->sys_ctrl0.val = value;
}

__STATIC_INLINE void sysc_cpu_sys_ctrl0_pack(uint8_t brom_rm, uint8_t brom_rme, uint8_t adc_has_sram, uint8_t mdm_has_sram, uint8_t adc_has_dma, uint8_t cache_has_sram)
{
    hwp_sysc_cpu->sys_ctrl0.val = (((uint32_t)brom_rm << 28) | ((uint32_t)brom_rme << 24) | ((uint32_t)adc_has_sram << 8) | ((uint32_t)mdm_has_sram << 4) | ((uint32_t)adc_has_dma << 1) | ((uint32_t)cache_has_sram << 0));
}

__STATIC_INLINE void sysc_cpu_sys_ctrl0_unpack(uint8_t* brom_rm, uint8_t* brom_rme, uint8_t* adc_has_sram, uint8_t* mdm_has_sram, uint8_t* adc_has_dma, uint8_t* cache_has_sram)
{
    T_SYSC_CPU_SYS_CTRL0 localVal = hwp_sysc_cpu->sys_ctrl0;

    *brom_rm = localVal.bit_field.brom_rm;
    *brom_rme = localVal.bit_field.brom_rme;
    *adc_has_sram = localVal.bit_field.adc_has_sram;
    *mdm_has_sram = localVal.bit_field.mdm_has_sram;
    *adc_has_dma = localVal.bit_field.adc_has_dma;
    *cache_has_sram = localVal.bit_field.cache_has_sram;
}

__STATIC_INLINE uint8_t sysc_cpu_brom_rm_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.brom_rm;
}

__STATIC_INLINE void sysc_cpu_brom_rm_setf(uint8_t brom_rm)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.brom_rm = brom_rm;
}

__STATIC_INLINE uint8_t sysc_cpu_brom_rme_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.brom_rme;
}

__STATIC_INLINE void sysc_cpu_brom_rme_setf(uint8_t brom_rme)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.brom_rme = brom_rme;
}

__STATIC_INLINE uint8_t sysc_cpu_adc_has_sram_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.adc_has_sram;
}

__STATIC_INLINE void sysc_cpu_adc_has_sram_setf(uint8_t adc_has_sram)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.adc_has_sram = adc_has_sram;
}

__STATIC_INLINE uint8_t sysc_cpu_mdm_has_sram_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.mdm_has_sram;
}

__STATIC_INLINE void sysc_cpu_mdm_has_sram_setf(uint8_t mdm_has_sram)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.mdm_has_sram = mdm_has_sram;
}

__STATIC_INLINE uint8_t sysc_cpu_adc_has_dma_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.adc_has_dma;
}

__STATIC_INLINE void sysc_cpu_adc_has_dma_setf(uint8_t adc_has_dma)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.adc_has_dma = adc_has_dma;
}

__STATIC_INLINE uint8_t sysc_cpu_cache_has_sram_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.cache_has_sram;
}

__STATIC_INLINE void sysc_cpu_cache_has_sram_setf(uint8_t cache_has_sram)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.cache_has_sram = cache_has_sram;
}

__STATIC_INLINE uint32_t sysc_cpu_sft_intr_get(void)
{
    return hwp_sysc_cpu->sft_intr.val;
}

__STATIC_INLINE void sysc_cpu_sft_intr_set(uint32_t value)
{
    hwp_sysc_cpu->sft_intr.val = value;
}

__STATIC_INLINE void sysc_cpu_sft_intr_pack(uint8_t sft_intr)
{
    hwp_sysc_cpu->sft_intr.val = (((uint32_t)sft_intr << 0));
}

__STATIC_INLINE void sysc_cpu_sft_intr_unpack(uint8_t* sft_intr)
{
    T_SYSC_CPU_SFT_INTR localVal = hwp_sysc_cpu->sft_intr;

    *sft_intr = localVal.bit_field.sft_intr;
}

__STATIC_INLINE uint8_t sysc_cpu_sft_intr_getf(void)
{
    return hwp_sysc_cpu->sft_intr.bit_field.sft_intr;
}

__STATIC_INLINE void sysc_cpu_sft_intr_setf(uint8_t sft_intr)
{
    hwp_sysc_cpu->sft_intr.bit_field.sft_intr = sft_intr;
}

__STATIC_INLINE uint32_t sysc_cpu_calb32_get(void)
{
    return hwp_sysc_cpu->calb32.val;
}

__STATIC_INLINE void sysc_cpu_calb32_set(uint32_t value)
{
    hwp_sysc_cpu->calb32.val = value;
}

__STATIC_INLINE void sysc_cpu_calb32_pack(uint8_t calb32k_start)
{
    hwp_sysc_cpu->calb32.val = (((uint32_t)calb32k_start << 0));
}

__STATIC_INLINE void sysc_cpu_calb32_unpack(uint32_t* calb32k_rslt, uint8_t* calb32k_start)
{
    T_SYSC_CPU_CALB32 localVal = hwp_sysc_cpu->calb32;

    *calb32k_rslt = localVal.bit_field.calb32k_rslt;
    *calb32k_start = localVal.bit_field.calb32k_start;
}

__STATIC_INLINE uint32_t sysc_cpu_calb32k_rslt_getf(void)
{
    return hwp_sysc_cpu->calb32.bit_field.calb32k_rslt;
}

__STATIC_INLINE uint8_t sysc_cpu_calb32k_start_getf(void)
{
    return hwp_sysc_cpu->calb32.bit_field.calb32k_start;
}

__STATIC_INLINE void sysc_cpu_calb32k_start_setf(uint8_t calb32k_start)
{
    hwp_sysc_cpu->calb32.bit_field.calb32k_start = calb32k_start;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_l_get(void)
{
    return hwp_sysc_cpu->pgspy_addr0_l.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr0_l.val = value;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_pack(uint32_t pgspy_addr0_l)
{
    hwp_sysc_cpu->pgspy_addr0_l.val = (((uint32_t)pgspy_addr0_l << 0));
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_unpack(uint32_t* pgspy_addr0_l)
{
    T_SYSC_CPU_PGSPY_ADDR0_L localVal = hwp_sysc_cpu->pgspy_addr0_l;

    *pgspy_addr0_l = localVal.bit_field.pgspy_addr0_l;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_l_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr0_l.bit_field.pgspy_addr0_l;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_setf(uint32_t pgspy_addr0_l)
{
    hwp_sysc_cpu->pgspy_addr0_l.bit_field.pgspy_addr0_l = pgspy_addr0_l;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_h_get(void)
{
    return hwp_sysc_cpu->pgspy_addr0_h.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr0_h.val = value;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_pack(uint32_t pgspy_addr0_h)
{
    hwp_sysc_cpu->pgspy_addr0_h.val = (((uint32_t)pgspy_addr0_h << 0));
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_unpack(uint32_t* pgspy_addr0_h)
{
    T_SYSC_CPU_PGSPY_ADDR0_H localVal = hwp_sysc_cpu->pgspy_addr0_h;

    *pgspy_addr0_h = localVal.bit_field.pgspy_addr0_h;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_h_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr0_h.bit_field.pgspy_addr0_h;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_setf(uint32_t pgspy_addr0_h)
{
    hwp_sysc_cpu->pgspy_addr0_h.bit_field.pgspy_addr0_h = pgspy_addr0_h;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_l_get(void)
{
    return hwp_sysc_cpu->pgspy_addr1_l.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr1_l.val = value;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_pack(uint32_t pgspy_addr1_l)
{
    hwp_sysc_cpu->pgspy_addr1_l.val = (((uint32_t)pgspy_addr1_l << 0));
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_unpack(uint32_t* pgspy_addr1_l)
{
    T_SYSC_CPU_PGSPY_ADDR1_L localVal = hwp_sysc_cpu->pgspy_addr1_l;

    *pgspy_addr1_l = localVal.bit_field.pgspy_addr1_l;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_l_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr1_l.bit_field.pgspy_addr1_l;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_setf(uint32_t pgspy_addr1_l)
{
    hwp_sysc_cpu->pgspy_addr1_l.bit_field.pgspy_addr1_l = pgspy_addr1_l;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_h_get(void)
{
    return hwp_sysc_cpu->pgspy_addr1_h.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr1_h.val = value;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_pack(uint32_t pgspy_addr1_h)
{
    hwp_sysc_cpu->pgspy_addr1_h.val = (((uint32_t)pgspy_addr1_h << 0));
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_unpack(uint32_t* pgspy_addr1_h)
{
    T_SYSC_CPU_PGSPY_ADDR1_H localVal = hwp_sysc_cpu->pgspy_addr1_h;

    *pgspy_addr1_h = localVal.bit_field.pgspy_addr1_h;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_h_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr1_h.bit_field.pgspy_addr1_h;
}

__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_setf(uint32_t pgspy_addr1_h)
{
    hwp_sysc_cpu->pgspy_addr1_h.bit_field.pgspy_addr1_h = pgspy_addr1_h;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_en_get(void)
{
    return hwp_sysc_cpu->pgspy_en.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_en_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_en.val = value;
}

__STATIC_INLINE void sysc_cpu_pgspy_en_pack(uint8_t pgspy_en)
{
    hwp_sysc_cpu->pgspy_en.val = (((uint32_t)pgspy_en << 0));
}

__STATIC_INLINE void sysc_cpu_pgspy_en_unpack(uint8_t* pgspy_en)
{
    T_SYSC_CPU_PGSPY_EN localVal = hwp_sysc_cpu->pgspy_en;

    *pgspy_en = localVal.bit_field.pgspy_en;
}

__STATIC_INLINE uint8_t sysc_cpu_pgspy_en_getf(void)
{
    return hwp_sysc_cpu->pgspy_en.bit_field.pgspy_en;
}

__STATIC_INLINE void sysc_cpu_pgspy_en_setf(uint8_t pgspy_en)
{
    hwp_sysc_cpu->pgspy_en.bit_field.pgspy_en = pgspy_en;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_intr_mask_get(void)
{
    return hwp_sysc_cpu->pgspy_intr_mask.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_intr_mask.val = value;
}

__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_pack(uint8_t pgspy_intr_mask)
{
    hwp_sysc_cpu->pgspy_intr_mask.val = (((uint32_t)pgspy_intr_mask << 0));
}

__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_unpack(uint8_t* pgspy_intr_mask)
{
    T_SYSC_CPU_PGSPY_INTR_MASK localVal = hwp_sysc_cpu->pgspy_intr_mask;

    *pgspy_intr_mask = localVal.bit_field.pgspy_intr_mask;
}

__STATIC_INLINE uint8_t sysc_cpu_pgspy_intr_mask_getf(void)
{
    return hwp_sysc_cpu->pgspy_intr_mask.bit_field.pgspy_intr_mask;
}

__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_setf(uint8_t pgspy_intr_mask)
{
    hwp_sysc_cpu->pgspy_intr_mask.bit_field.pgspy_intr_mask = pgspy_intr_mask;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_intr_raw_get(void)
{
    return hwp_sysc_cpu->pgspy_intr_raw.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_intr_raw_unpack(uint8_t* pgspy_intr_raw)
{
    T_SYSC_CPU_PGSPY_INTR_RAW localVal = hwp_sysc_cpu->pgspy_intr_raw;

    *pgspy_intr_raw = localVal.bit_field.pgspy_intr_raw;
}

__STATIC_INLINE uint8_t sysc_cpu_pgspy_intr_raw_getf(void)
{
    return hwp_sysc_cpu->pgspy_intr_raw.bit_field.pgspy_intr_raw;
}

__STATIC_INLINE uint32_t sysc_cpu_pgspy_intr_get(void)
{
    return hwp_sysc_cpu->pgspy_intr.val;
}

__STATIC_INLINE void sysc_cpu_pgspy_intr_unpack(uint8_t* pgspy_intr)
{
    T_SYSC_CPU_PGSPY_INTR localVal = hwp_sysc_cpu->pgspy_intr;

    *pgspy_intr = localVal.bit_field.pgspy_intr;
}

__STATIC_INLINE uint8_t sysc_cpu_pgspy_intr_getf(void)
{
    return hwp_sysc_cpu->pgspy_intr.bit_field.pgspy_intr;
}

__STATIC_INLINE uint32_t sysc_cpu_gpio_ds0_get(void)
{
    return hwp_sysc_cpu->gpio_ds0.val;
}

__STATIC_INLINE void sysc_cpu_gpio_ds0_set(uint32_t value)
{
    hwp_sysc_cpu->gpio_ds0.val = value;
}

__STATIC_INLINE void sysc_cpu_gpio_ds0_pack(uint8_t gpio_h_ds0)
{
    hwp_sysc_cpu->gpio_ds0.val = (((uint32_t)gpio_h_ds0 << 24));
}

__STATIC_INLINE void sysc_cpu_gpio_ds0_unpack(uint8_t* gpio_h_ds0)
{
    T_SYSC_CPU_GPIO_DS0 localVal = hwp_sysc_cpu->gpio_ds0;

    *gpio_h_ds0 = localVal.bit_field.gpio_h_ds0;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio_h_ds0_getf(void)
{
    return hwp_sysc_cpu->gpio_ds0.bit_field.gpio_h_ds0;
}

__STATIC_INLINE void sysc_cpu_gpio_h_ds0_setf(uint8_t gpio_h_ds0)
{
    hwp_sysc_cpu->gpio_ds0.bit_field.gpio_h_ds0 = gpio_h_ds0;
}

__STATIC_INLINE uint32_t sysc_cpu_gpio_ds1_get(void)
{
    return hwp_sysc_cpu->gpio_ds1.val;
}

__STATIC_INLINE void sysc_cpu_gpio_ds1_set(uint32_t value)
{
    hwp_sysc_cpu->gpio_ds1.val = value;
}

__STATIC_INLINE void sysc_cpu_gpio_ds1_pack(uint8_t gpio_h_ds1)
{
    hwp_sysc_cpu->gpio_ds1.val = (((uint32_t)gpio_h_ds1 << 24));
}

__STATIC_INLINE void sysc_cpu_gpio_ds1_unpack(uint8_t* gpio_h_ds1)
{
    T_SYSC_CPU_GPIO_DS1 localVal = hwp_sysc_cpu->gpio_ds1;

    *gpio_h_ds1 = localVal.bit_field.gpio_h_ds1;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio_h_ds1_getf(void)
{
    return hwp_sysc_cpu->gpio_ds1.bit_field.gpio_h_ds1;
}

__STATIC_INLINE void sysc_cpu_gpio_h_ds1_setf(uint8_t gpio_h_ds1)
{
    hwp_sysc_cpu->gpio_ds1.bit_field.gpio_h_ds1 = gpio_h_ds1;
}

__STATIC_INLINE uint32_t sysc_cpu_gpio_ie_get(void)
{
    return hwp_sysc_cpu->gpio_ie.val;
}

__STATIC_INLINE void sysc_cpu_gpio_ie_set(uint32_t value)
{
    hwp_sysc_cpu->gpio_ie.val = value;
}

__STATIC_INLINE void sysc_cpu_gpio_ie_pack(uint8_t gpio_h_ie)
{
    hwp_sysc_cpu->gpio_ie.val = (((uint32_t)gpio_h_ie << 24));
}

__STATIC_INLINE void sysc_cpu_gpio_ie_unpack(uint8_t* gpio_h_ie)
{
    T_SYSC_CPU_GPIO_IE localVal = hwp_sysc_cpu->gpio_ie;

    *gpio_h_ie = localVal.bit_field.gpio_h_ie;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio_h_ie_getf(void)
{
    return hwp_sysc_cpu->gpio_ie.bit_field.gpio_h_ie;
}

__STATIC_INLINE void sysc_cpu_gpio_h_ie_setf(uint8_t gpio_h_ie)
{
    hwp_sysc_cpu->gpio_ie.bit_field.gpio_h_ie = gpio_h_ie;
}

__STATIC_INLINE uint32_t sysc_cpu_gpio_is_get(void)
{
    return hwp_sysc_cpu->gpio_is.val;
}

__STATIC_INLINE void sysc_cpu_gpio_is_set(uint32_t value)
{
    hwp_sysc_cpu->gpio_is.val = value;
}

__STATIC_INLINE void sysc_cpu_gpio_is_pack(uint8_t gpio_h_is)
{
    hwp_sysc_cpu->gpio_is.val = (((uint32_t)gpio_h_is << 24));
}

__STATIC_INLINE void sysc_cpu_gpio_is_unpack(uint8_t* gpio_h_is)
{
    T_SYSC_CPU_GPIO_IS localVal = hwp_sysc_cpu->gpio_is;

    *gpio_h_is = localVal.bit_field.gpio_h_is;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio_h_is_getf(void)
{
    return hwp_sysc_cpu->gpio_is.bit_field.gpio_h_is;
}

__STATIC_INLINE void sysc_cpu_gpio_h_is_setf(uint8_t gpio_h_is)
{
    hwp_sysc_cpu->gpio_is.bit_field.gpio_h_is = gpio_h_is;
}

__STATIC_INLINE uint32_t sysc_cpu_gpio_pe_get(void)
{
    return hwp_sysc_cpu->gpio_pe.val;
}

__STATIC_INLINE void sysc_cpu_gpio_pe_set(uint32_t value)
{
    hwp_sysc_cpu->gpio_pe.val = value;
}

__STATIC_INLINE void sysc_cpu_gpio_pe_pack(uint8_t gpio_h_pe)
{
    hwp_sysc_cpu->gpio_pe.val = (((uint32_t)gpio_h_pe << 24));
}

__STATIC_INLINE void sysc_cpu_gpio_pe_unpack(uint8_t* gpio_h_pe)
{
    T_SYSC_CPU_GPIO_PE localVal = hwp_sysc_cpu->gpio_pe;

    *gpio_h_pe = localVal.bit_field.gpio_h_pe;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio_h_pe_getf(void)
{
    return hwp_sysc_cpu->gpio_pe.bit_field.gpio_h_pe;
}

__STATIC_INLINE void sysc_cpu_gpio_h_pe_setf(uint8_t gpio_h_pe)
{
    hwp_sysc_cpu->gpio_pe.bit_field.gpio_h_pe = gpio_h_pe;
}

__STATIC_INLINE uint32_t sysc_cpu_gpio_ps_get(void)
{
    return hwp_sysc_cpu->gpio_ps.val;
}

__STATIC_INLINE void sysc_cpu_gpio_ps_set(uint32_t value)
{
    hwp_sysc_cpu->gpio_ps.val = value;
}

__STATIC_INLINE void sysc_cpu_gpio_ps_pack(uint8_t gpio_h_ps)
{
    hwp_sysc_cpu->gpio_ps.val = (((uint32_t)gpio_h_ps << 24));
}

__STATIC_INLINE void sysc_cpu_gpio_ps_unpack(uint8_t* gpio_h_ps)
{
    T_SYSC_CPU_GPIO_PS localVal = hwp_sysc_cpu->gpio_ps;

    *gpio_h_ps = localVal.bit_field.gpio_h_ps;
}

__STATIC_INLINE uint8_t sysc_cpu_gpio_h_ps_getf(void)
{
    return hwp_sysc_cpu->gpio_ps.bit_field.gpio_h_ps;
}

__STATIC_INLINE void sysc_cpu_gpio_h_ps_setf(uint8_t gpio_h_ps)
{
    hwp_sysc_cpu->gpio_ps.bit_field.gpio_h_ps = gpio_h_ps;
}
#endif


