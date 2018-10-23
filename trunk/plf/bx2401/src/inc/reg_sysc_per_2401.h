#ifndef __REG_SYSC_PER_H__
#define __REG_SYSC_PER_H__
#include "_reg_base_addr.h"
//clk_sel
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   clk_sel_iic0 :  2; /* 1: 0, clock select:
        uint32_t                     reserved_3 :  2; /* 3: 2,                             NA*/
        uint32_t                   clk_sel_iic1 :  2; /* 5: 4, clock select:
        uint32_t                     reserved_2 :  2; /* 7: 6,                             NA*/
        uint32_t                  clk_sel_uart0 :  2; /* 9: 8, clock select:
        uint32_t                     reserved_1 :  2; /*11:10,                             NA*/
        uint32_t                  clk_sel_uart1 :  2; /*13:12, clock select:
        uint32_t                     reserved_0 : 18; /*31:14,                             NA*/
    } bit_field;
} T_SYSC_PER_CLK_SEL;

//clk_div_param0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           clk_div_iic0_para_m1 :  4; /* 3: 0, divider parameter for clk_pll and clk_32m
        uint32_t           clk_div_iic1_para_m1 :  4; /* 7: 4, divider parameter for clk_pll and clk_32m
        uint32_t                     reserved_0 : 16; /*23: 8,                             NA*/
        uint32_t            clk_div_pwm_para_m1 :  8; /*31:24, clk_pwm is divide from clk_32m
    } bit_field;
} T_SYSC_PER_CLK_DIV_PARAM0;

//clk_div_param1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t     clk_div_uart0_para_len0_m1 :  6; /* 5: 0,                             NA*/
        uint32_t                     reserved_3 :  2; /* 7: 6,                             NA*/
        uint32_t     clk_div_uart0_para_len1_m1 :  6; /*13: 8,                             NA*/
        uint32_t                     reserved_2 :  2; /*15:14,                             NA*/
        uint32_t     clk_div_uart0_para_num0_m1 :  4; /*19:16,                             NA*/
        uint32_t                     reserved_1 :  4; /*23:20,                             NA*/
        uint32_t     clk_div_uart0_para_num1_m1 :  4; /*27:24, for first (clk_div_uart0_para_num1_m1+1) uart clk cycles clk_uart=clk/(clk_div_uart0_para_len1_m1+1)
        uint32_t                     reserved_0 :  4; /*31:28,                             NA*/
    } bit_field;
} T_SYSC_PER_CLK_DIV_PARAM1;

//clk_div_param2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t     clk_div_uart1_para_len0_m1 :  6; /* 5: 0,                             NA*/
        uint32_t                     reserved_3 :  2; /* 7: 6,                             NA*/
        uint32_t     clk_div_uart1_para_len1_m1 :  6; /*13: 8,                             NA*/
        uint32_t                     reserved_2 :  2; /*15:14,                             NA*/
        uint32_t     clk_div_uart1_para_num0_m1 :  4; /*19:16,                             NA*/
        uint32_t                     reserved_1 :  4; /*23:20,                             NA*/
        uint32_t     clk_div_uart1_para_num1_m1 :  4; /*27:24, for first (clk_div_uart1_para_num1_m1+1) uart clk cycles clk_uart=clk/(clk_div_uart1_para_len1_m1+1)
        uint32_t                     reserved_0 :  4; /*31:28,                             NA*/
    } bit_field;
} T_SYSC_PER_CLK_DIV_PARAM2;

//clkg0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 clkg0_set_iic0 :  1; /* 0: 0,                             NA*/
        uint32_t                 clkg0_clr_iic0 :  1; /* 1: 1,                             NA*/
        uint32_t                 clkg1_set_iic0 :  1; /* 2: 2,                             NA*/
        uint32_t                 clkg1_clr_iic0 :  1; /* 3: 3,                             NA*/
        uint32_t                 clkg0_set_iic1 :  1; /* 4: 4,                             NA*/
        uint32_t                 clkg0_clr_iic1 :  1; /* 5: 5,                             NA*/
        uint32_t                 clkg1_set_iic1 :  1; /* 6: 6,                             NA*/
        uint32_t                 clkg1_clr_iic1 :  1; /* 7: 7,                             NA*/
        uint32_t                clkg0_set_uart0 :  1; /* 8: 8,                             NA*/
        uint32_t                clkg0_clr_uart0 :  1; /* 9: 9,                             NA*/
        uint32_t                clkg1_set_uart0 :  1; /*10:10,                             NA*/
        uint32_t                clkg1_clr_uart0 :  1; /*11:11,                             NA*/
        uint32_t                clkg0_set_uart1 :  1; /*12:12,                             NA*/
        uint32_t                clkg0_clr_uart1 :  1; /*13:13,                             NA*/
        uint32_t                clkg1_set_uart1 :  1; /*14:14,                             NA*/
        uint32_t                clkg1_clr_uart1 :  1; /*15:15,                             NA*/
        uint32_t                 clkg_set_spim0 :  1; /*16:16,                             NA*/
        uint32_t                 clkg_clr_spim0 :  1; /*17:17,                             NA*/
        uint32_t                     reserved_2 :  2; /*19:18,                             NA*/
        uint32_t                 clkg_set_spim1 :  1; /*20:20,                             NA*/
        uint32_t                 clkg_clr_spim1 :  1; /*21:21,                             NA*/
        uint32_t                     reserved_1 :  2; /*23:22,                             NA*/
        uint32_t                  clkg_set_spis :  1; /*24:24,                             NA*/
        uint32_t                  clkg_clr_spis :  1; /*25:25, write 1 to clkg*_clr_* clear the corresponding clock gate control reg
        uint32_t                     reserved_0 :  6; /*31:26,                             NA*/
    } bit_field;
} T_SYSC_PER_CLKG0;

//clkg1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               clkg_set_pwm_div :  1; /* 0: 0,                             NA*/
        uint32_t               clkg_clr_pwm_div :  1; /* 1: 1,                             NA*/
        uint32_t                  clkg_set_pwm0 :  1; /* 2: 2,                             NA*/
        uint32_t                  clkg_clr_pwm0 :  1; /* 3: 3,                             NA*/
        uint32_t                  clkg_set_pwm1 :  1; /* 4: 4,                             NA*/
        uint32_t                  clkg_clr_pwm1 :  1; /* 5: 5,                             NA*/
        uint32_t                  clkg_set_pwm2 :  1; /* 6: 6,                             NA*/
        uint32_t                  clkg_clr_pwm2 :  1; /* 7: 7,                             NA*/
        uint32_t                  clkg_set_pwm3 :  1; /* 8: 8,                             NA*/
        uint32_t                  clkg_clr_pwm3 :  1; /* 9: 9,                             NA*/
        uint32_t                  clkg_set_pwm4 :  1; /*10:10,                             NA*/
        uint32_t                  clkg_clr_pwm4 :  1; /*11:11,                             NA*/
        uint32_t                  clkg_set_gpio :  1; /*12:12,                             NA*/
        uint32_t                  clkg_clr_gpio :  1; /*13:13, write 1 to clkg*_clr_* clear the corresponding clock gate control reg
        uint32_t                     reserved_0 : 18; /*31:14,                             NA*/
    } bit_field;
} T_SYSC_PER_CLKG1;

//srst
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                srst_set_iic0_n :  1; /* 0: 0,                             NA*/
        uint32_t                srst_clr_iic0_n :  1; /* 1: 1,                             NA*/
        uint32_t                srst_set_iic1_n :  1; /* 2: 2,                             NA*/
        uint32_t                srst_clr_iic1_n :  1; /* 3: 3,                             NA*/
        uint32_t               srst_set_uart0_n :  1; /* 4: 4,                             NA*/
        uint32_t               srst_clr_uart0_n :  1; /* 5: 5,                             NA*/
        uint32_t               srst_set_uart1_n :  1; /* 6: 6,                             NA*/
        uint32_t               srst_clr_uart1_n :  1; /* 7: 7,                             NA*/
        uint32_t               srst_set_spim0_n :  1; /* 8: 8,                             NA*/
        uint32_t               srst_clr_spim0_n :  1; /* 9: 9,                             NA*/
        uint32_t               srst_set_spim1_n :  1; /*10:10,                             NA*/
        uint32_t               srst_clr_spim1_n :  1; /*11:11,                             NA*/
        uint32_t                srst_set_spis_n :  1; /*12:12,                             NA*/
        uint32_t                srst_clr_spis_n :  1; /*13:13,                             NA*/
        uint32_t                 srst_set_pwm_n :  1; /*14:14,                             NA*/
        uint32_t                 srst_clr_pwm_n :  1; /*15:15,                             NA*/
        uint32_t                srst_set_gpio_n :  1; /*16:16,                             NA*/
        uint32_t                srst_clr_gpio_n :  1; /*17:17, write 1 to srst*_clr_* clear the corresponding soft reset control reg
        uint32_t                     reserved_0 : 14; /*31:18,                             NA*/
    } bit_field;
} T_SYSC_PER_SRST;

//uart_issir
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    uart_is_sir :  1; /* 0: 0,        high means uart0 is sir*/
        uint32_t                     reserved_0 : 31; /*31: 1,                             NA*/
    } bit_field;
} T_SYSC_PER_UART_ISSIR;

//Registers Mapping to the same address

typedef struct
{
    volatile              T_SYSC_PER_CLK_SEL                        clk_sel; /*  0x0,    RW, 0x00000000,                             NA*/
    volatile       T_SYSC_PER_CLK_DIV_PARAM0                 clk_div_param0; /*  0x4,    RW, 0x00000000,                             NA*/
    volatile       T_SYSC_PER_CLK_DIV_PARAM1                 clk_div_param1; /*  0x8,    RW, 0x00000000,                             NA*/
    volatile       T_SYSC_PER_CLK_DIV_PARAM2                 clk_div_param2; /*  0xc,    RW, 0x00000000,                             NA*/
    volatile                T_SYSC_PER_CLKG0                          clkg0; /* 0x10,    RW, 0x0333FFFF,                             NA*/
    volatile                T_SYSC_PER_CLKG1                          clkg1; /* 0x14,    RW, 0x00003FFF,                             NA*/
    volatile                 T_SYSC_PER_SRST                           srst; /* 0x18,    RW, 0x0003FFFF,                             NA*/
    volatile           T_SYSC_PER_UART_ISSIR                     uart_issir; /* 0x1c,    RW, 0x00000000,                             NA*/
} T_HWP_SYSC_PER_T;

#define hwp_sysc_per ((T_HWP_SYSC_PER_T*)REG_SYSC_PER_BASE)


__STATIC_INLINE uint32_t sysc_per_clk_sel_get(void)
{
    return hwp_sysc_per->clk_sel.val;
}

__STATIC_INLINE void sysc_per_clk_sel_set(uint32_t value)
{
    hwp_sysc_per->clk_sel.val = value;
}

__STATIC_INLINE void sysc_per_clk_sel_pack(uint8_t clk_sel_uart1, uint8_t clk_sel_uart0, uint8_t clk_sel_iic1, uint8_t clk_sel_iic0)
{
    hwp_sysc_per->clk_sel.val = (((uint32_t)clk_sel_uart1 << 12) | ((uint32_t)clk_sel_uart0 << 8) | ((uint32_t)clk_sel_iic1 << 4) | ((uint32_t)clk_sel_iic0 << 0));
}

__STATIC_INLINE void sysc_per_clk_sel_unpack(uint8_t* clk_sel_uart1, uint8_t* clk_sel_uart0, uint8_t* clk_sel_iic1, uint8_t* clk_sel_iic0)
{
    T_SYSC_PER_CLK_SEL localVal = hwp_sysc_per->clk_sel;

    *clk_sel_uart1 = localVal.bit_field.clk_sel_uart1;
    *clk_sel_uart0 = localVal.bit_field.clk_sel_uart0;
    *clk_sel_iic1 = localVal.bit_field.clk_sel_iic1;
    *clk_sel_iic0 = localVal.bit_field.clk_sel_iic0;
}

__STATIC_INLINE uint8_t sysc_per_clk_sel_uart1_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_uart1;
}

__STATIC_INLINE void sysc_per_clk_sel_uart1_setf(uint8_t clk_sel_uart1)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_uart1 = clk_sel_uart1;
}

__STATIC_INLINE uint8_t sysc_per_clk_sel_uart0_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_uart0;
}

__STATIC_INLINE void sysc_per_clk_sel_uart0_setf(uint8_t clk_sel_uart0)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_uart0 = clk_sel_uart0;
}

__STATIC_INLINE uint8_t sysc_per_clk_sel_iic1_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_iic1;
}

__STATIC_INLINE void sysc_per_clk_sel_iic1_setf(uint8_t clk_sel_iic1)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_iic1 = clk_sel_iic1;
}

__STATIC_INLINE uint8_t sysc_per_clk_sel_iic0_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_iic0;
}

__STATIC_INLINE void sysc_per_clk_sel_iic0_setf(uint8_t clk_sel_iic0)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_iic0 = clk_sel_iic0;
}

__STATIC_INLINE uint32_t sysc_per_clk_div_param0_get(void)
{
    return hwp_sysc_per->clk_div_param0.val;
}

__STATIC_INLINE void sysc_per_clk_div_param0_set(uint32_t value)
{
    hwp_sysc_per->clk_div_param0.val = value;
}

__STATIC_INLINE void sysc_per_clk_div_param0_pack(uint8_t clk_div_pwm_para_m1, uint8_t clk_div_iic1_para_m1, uint8_t clk_div_iic0_para_m1)
{
    hwp_sysc_per->clk_div_param0.val = (((uint32_t)clk_div_pwm_para_m1 << 24) | ((uint32_t)clk_div_iic1_para_m1 << 4) | ((uint32_t)clk_div_iic0_para_m1 << 0));
}

__STATIC_INLINE void sysc_per_clk_div_param0_unpack(uint8_t* clk_div_pwm_para_m1, uint8_t* clk_div_iic1_para_m1, uint8_t* clk_div_iic0_para_m1)
{
    T_SYSC_PER_CLK_DIV_PARAM0 localVal = hwp_sysc_per->clk_div_param0;

    *clk_div_pwm_para_m1 = localVal.bit_field.clk_div_pwm_para_m1;
    *clk_div_iic1_para_m1 = localVal.bit_field.clk_div_iic1_para_m1;
    *clk_div_iic0_para_m1 = localVal.bit_field.clk_div_iic0_para_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_pwm_para_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param0.bit_field.clk_div_pwm_para_m1;
}

__STATIC_INLINE void sysc_per_clk_div_pwm_para_m1_setf(uint8_t clk_div_pwm_para_m1)
{
    hwp_sysc_per->clk_div_param0.bit_field.clk_div_pwm_para_m1 = clk_div_pwm_para_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_iic1_para_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic1_para_m1;
}

__STATIC_INLINE void sysc_per_clk_div_iic1_para_m1_setf(uint8_t clk_div_iic1_para_m1)
{
    hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic1_para_m1 = clk_div_iic1_para_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_iic0_para_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic0_para_m1;
}

__STATIC_INLINE void sysc_per_clk_div_iic0_para_m1_setf(uint8_t clk_div_iic0_para_m1)
{
    hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic0_para_m1 = clk_div_iic0_para_m1;
}

__STATIC_INLINE uint32_t sysc_per_clk_div_param1_get(void)
{
    return hwp_sysc_per->clk_div_param1.val;
}

__STATIC_INLINE void sysc_per_clk_div_param1_set(uint32_t value)
{
    hwp_sysc_per->clk_div_param1.val = value;
}

__STATIC_INLINE void sysc_per_clk_div_param1_pack(uint8_t clk_div_uart0_para_num1_m1, uint8_t clk_div_uart0_para_num0_m1, uint8_t clk_div_uart0_para_len1_m1, uint8_t clk_div_uart0_para_len0_m1)
{
    hwp_sysc_per->clk_div_param1.val = (((uint32_t)clk_div_uart0_para_num1_m1 << 24) | ((uint32_t)clk_div_uart0_para_num0_m1 << 16) | ((uint32_t)clk_div_uart0_para_len1_m1 << 8) | ((uint32_t)clk_div_uart0_para_len0_m1 << 0));
}

__STATIC_INLINE void sysc_per_clk_div_param1_unpack(uint8_t* clk_div_uart0_para_num1_m1, uint8_t* clk_div_uart0_para_num0_m1, uint8_t* clk_div_uart0_para_len1_m1, uint8_t* clk_div_uart0_para_len0_m1)
{
    T_SYSC_PER_CLK_DIV_PARAM1 localVal = hwp_sysc_per->clk_div_param1;

    *clk_div_uart0_para_num1_m1 = localVal.bit_field.clk_div_uart0_para_num1_m1;
    *clk_div_uart0_para_num0_m1 = localVal.bit_field.clk_div_uart0_para_num0_m1;
    *clk_div_uart0_para_len1_m1 = localVal.bit_field.clk_div_uart0_para_len1_m1;
    *clk_div_uart0_para_len0_m1 = localVal.bit_field.clk_div_uart0_para_len0_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_num1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num1_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart0_para_num1_m1_setf(uint8_t clk_div_uart0_para_num1_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num1_m1 = clk_div_uart0_para_num1_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_num0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num0_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart0_para_num0_m1_setf(uint8_t clk_div_uart0_para_num0_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num0_m1 = clk_div_uart0_para_num0_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_len1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len1_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart0_para_len1_m1_setf(uint8_t clk_div_uart0_para_len1_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len1_m1 = clk_div_uart0_para_len1_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_len0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len0_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart0_para_len0_m1_setf(uint8_t clk_div_uart0_para_len0_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len0_m1 = clk_div_uart0_para_len0_m1;
}

__STATIC_INLINE uint32_t sysc_per_clk_div_param2_get(void)
{
    return hwp_sysc_per->clk_div_param2.val;
}

__STATIC_INLINE void sysc_per_clk_div_param2_set(uint32_t value)
{
    hwp_sysc_per->clk_div_param2.val = value;
}

__STATIC_INLINE void sysc_per_clk_div_param2_pack(uint8_t clk_div_uart1_para_num1_m1, uint8_t clk_div_uart1_para_num0_m1, uint8_t clk_div_uart1_para_len1_m1, uint8_t clk_div_uart1_para_len0_m1)
{
    hwp_sysc_per->clk_div_param2.val = (((uint32_t)clk_div_uart1_para_num1_m1 << 24) | ((uint32_t)clk_div_uart1_para_num0_m1 << 16) | ((uint32_t)clk_div_uart1_para_len1_m1 << 8) | ((uint32_t)clk_div_uart1_para_len0_m1 << 0));
}

__STATIC_INLINE void sysc_per_clk_div_param2_unpack(uint8_t* clk_div_uart1_para_num1_m1, uint8_t* clk_div_uart1_para_num0_m1, uint8_t* clk_div_uart1_para_len1_m1, uint8_t* clk_div_uart1_para_len0_m1)
{
    T_SYSC_PER_CLK_DIV_PARAM2 localVal = hwp_sysc_per->clk_div_param2;

    *clk_div_uart1_para_num1_m1 = localVal.bit_field.clk_div_uart1_para_num1_m1;
    *clk_div_uart1_para_num0_m1 = localVal.bit_field.clk_div_uart1_para_num0_m1;
    *clk_div_uart1_para_len1_m1 = localVal.bit_field.clk_div_uart1_para_len1_m1;
    *clk_div_uart1_para_len0_m1 = localVal.bit_field.clk_div_uart1_para_len0_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_num1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num1_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart1_para_num1_m1_setf(uint8_t clk_div_uart1_para_num1_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num1_m1 = clk_div_uart1_para_num1_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_num0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num0_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart1_para_num0_m1_setf(uint8_t clk_div_uart1_para_num0_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num0_m1 = clk_div_uart1_para_num0_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_len1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len1_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart1_para_len1_m1_setf(uint8_t clk_div_uart1_para_len1_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len1_m1 = clk_div_uart1_para_len1_m1;
}

__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_len0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len0_m1;
}

__STATIC_INLINE void sysc_per_clk_div_uart1_para_len0_m1_setf(uint8_t clk_div_uart1_para_len0_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len0_m1 = clk_div_uart1_para_len0_m1;
}

__STATIC_INLINE uint32_t sysc_per_clkg0_get(void)
{
    return hwp_sysc_per->clkg0.val;
}

__STATIC_INLINE void sysc_per_clkg0_set(uint32_t value)
{
    hwp_sysc_per->clkg0.val = value;
}

__STATIC_INLINE void sysc_per_clkg0_pack(uint8_t clkg_clr_spis, uint8_t clkg_set_spis, uint8_t clkg_clr_spim1, uint8_t clkg_set_spim1, uint8_t clkg_clr_spim0, uint8_t clkg_set_spim0, uint8_t clkg1_clr_uart1, uint8_t clkg1_set_uart1, uint8_t clkg0_clr_uart1, uint8_t clkg0_set_uart1, uint8_t clkg1_clr_uart0, uint8_t clkg1_set_uart0, uint8_t clkg0_clr_uart0, uint8_t clkg0_set_uart0, uint8_t clkg1_clr_iic1, uint8_t clkg1_set_iic1, uint8_t clkg0_clr_iic1, uint8_t clkg0_set_iic1, uint8_t clkg1_clr_iic0, uint8_t clkg1_set_iic0, uint8_t clkg0_clr_iic0, uint8_t clkg0_set_iic0)
{
    hwp_sysc_per->clkg0.val = (((uint32_t)clkg_clr_spis << 25) | ((uint32_t)clkg_set_spis << 24) | ((uint32_t)clkg_clr_spim1 << 21) | ((uint32_t)clkg_set_spim1 << 20) | ((uint32_t)clkg_clr_spim0 << 17) | ((uint32_t)clkg_set_spim0 << 16) | ((uint32_t)clkg1_clr_uart1 << 15) | ((uint32_t)clkg1_set_uart1 << 14) | ((uint32_t)clkg0_clr_uart1 << 13) | ((uint32_t)clkg0_set_uart1 << 12) | ((uint32_t)clkg1_clr_uart0 << 11) | ((uint32_t)clkg1_set_uart0 << 10) | ((uint32_t)clkg0_clr_uart0 << 9) | ((uint32_t)clkg0_set_uart0 << 8) | ((uint32_t)clkg1_clr_iic1 << 7) | ((uint32_t)clkg1_set_iic1 << 6) | ((uint32_t)clkg0_clr_iic1 << 5) | ((uint32_t)clkg0_set_iic1 << 4) | ((uint32_t)clkg1_clr_iic0 << 3) | ((uint32_t)clkg1_set_iic0 << 2) | ((uint32_t)clkg0_clr_iic0 << 1) | ((uint32_t)clkg0_set_iic0 << 0));
}

__STATIC_INLINE uint32_t sysc_per_clkg1_get(void)
{
    return hwp_sysc_per->clkg1.val;
}

__STATIC_INLINE void sysc_per_clkg1_set(uint32_t value)
{
    hwp_sysc_per->clkg1.val = value;
}

__STATIC_INLINE void sysc_per_clkg1_pack(uint8_t clkg_clr_gpio, uint8_t clkg_set_gpio, uint8_t clkg_clr_pwm4, uint8_t clkg_set_pwm4, uint8_t clkg_clr_pwm3, uint8_t clkg_set_pwm3, uint8_t clkg_clr_pwm2, uint8_t clkg_set_pwm2, uint8_t clkg_clr_pwm1, uint8_t clkg_set_pwm1, uint8_t clkg_clr_pwm0, uint8_t clkg_set_pwm0, uint8_t clkg_clr_pwm_div, uint8_t clkg_set_pwm_div)
{
    hwp_sysc_per->clkg1.val = (((uint32_t)clkg_clr_gpio << 13) | ((uint32_t)clkg_set_gpio << 12) | ((uint32_t)clkg_clr_pwm4 << 11) | ((uint32_t)clkg_set_pwm4 << 10) | ((uint32_t)clkg_clr_pwm3 << 9) | ((uint32_t)clkg_set_pwm3 << 8) | ((uint32_t)clkg_clr_pwm2 << 7) | ((uint32_t)clkg_set_pwm2 << 6) | ((uint32_t)clkg_clr_pwm1 << 5) | ((uint32_t)clkg_set_pwm1 << 4) | ((uint32_t)clkg_clr_pwm0 << 3) | ((uint32_t)clkg_set_pwm0 << 2) | ((uint32_t)clkg_clr_pwm_div << 1) | ((uint32_t)clkg_set_pwm_div << 0));
}

__STATIC_INLINE uint32_t sysc_per_srst_get(void)
{
    return hwp_sysc_per->srst.val;
}

__STATIC_INLINE void sysc_per_srst_set(uint32_t value)
{
    hwp_sysc_per->srst.val = value;
}

__STATIC_INLINE void sysc_per_srst_pack(uint8_t srst_clr_gpio_n, uint8_t srst_set_gpio_n, uint8_t srst_clr_pwm_n, uint8_t srst_set_pwm_n, uint8_t srst_clr_spis_n, uint8_t srst_set_spis_n, uint8_t srst_clr_spim1_n, uint8_t srst_set_spim1_n, uint8_t srst_clr_spim0_n, uint8_t srst_set_spim0_n, uint8_t srst_clr_uart1_n, uint8_t srst_set_uart1_n, uint8_t srst_clr_uart0_n, uint8_t srst_set_uart0_n, uint8_t srst_clr_iic1_n, uint8_t srst_set_iic1_n, uint8_t srst_clr_iic0_n, uint8_t srst_set_iic0_n)
{
    hwp_sysc_per->srst.val = (((uint32_t)srst_clr_gpio_n << 17) | ((uint32_t)srst_set_gpio_n << 16) | ((uint32_t)srst_clr_pwm_n << 15) | ((uint32_t)srst_set_pwm_n << 14) | ((uint32_t)srst_clr_spis_n << 13) | ((uint32_t)srst_set_spis_n << 12) | ((uint32_t)srst_clr_spim1_n << 11) | ((uint32_t)srst_set_spim1_n << 10) | ((uint32_t)srst_clr_spim0_n << 9) | ((uint32_t)srst_set_spim0_n << 8) | ((uint32_t)srst_clr_uart1_n << 7) | ((uint32_t)srst_set_uart1_n << 6) | ((uint32_t)srst_clr_uart0_n << 5) | ((uint32_t)srst_set_uart0_n << 4) | ((uint32_t)srst_clr_iic1_n << 3) | ((uint32_t)srst_set_iic1_n << 2) | ((uint32_t)srst_clr_iic0_n << 1) | ((uint32_t)srst_set_iic0_n << 0));
}

__STATIC_INLINE uint32_t sysc_per_uart_issir_get(void)
{
    return hwp_sysc_per->uart_issir.val;
}

__STATIC_INLINE void sysc_per_uart_issir_set(uint32_t value)
{
    hwp_sysc_per->uart_issir.val = value;
}

__STATIC_INLINE void sysc_per_uart_issir_pack(uint8_t uart_is_sir)
{
    hwp_sysc_per->uart_issir.val = (((uint32_t)uart_is_sir << 0));
}

__STATIC_INLINE void sysc_per_uart_issir_unpack(uint8_t* uart_is_sir)
{
    T_SYSC_PER_UART_ISSIR localVal = hwp_sysc_per->uart_issir;

    *uart_is_sir = localVal.bit_field.uart_is_sir;
}

__STATIC_INLINE uint8_t sysc_per_uart_is_sir_getf(void)
{
    return hwp_sysc_per->uart_issir.bit_field.uart_is_sir;
}

__STATIC_INLINE void sysc_per_uart_is_sir_setf(uint8_t uart_is_sir)
{
    hwp_sysc_per->uart_issir.bit_field.uart_is_sir = uart_is_sir;
}
#endif

