#ifndef BX_SYS_CONFIG_H_
#define BX_SYS_CONFIG_H_

#define CFG_APP
#define CFG_APP_DIS

#define CFG_HW_ECC
#define CFG_FREERTOS_SUPPORT
#define CFG_RF_BLUEX
//#define CFG_RF_ATLAS
#define CFG_ON_CHIP
#define CFG_SYS_LOG

#define CFG_PERI_RETENTION
#define CFG_DYNAMIC_UPDATE
#define ENABLE_ADV_PAYLOD_31BYTE_PATCH

//#define BX_VERF
#define VBAT_MILLIVOLT 3300
#define VDD_AWO_SLEEP_MILLIVOLT 800 // 950/900/850/800
#define VDD_SRAM_SLEEP_MILLIVOLT 650 // 950/900/850/800/750/700/650/600
#define FLASH_XIP

//#define MAIN_CLOCK 96000000
#define MAIN_CLOCK 32000000
//#define MAIN_CLOCK 16000000

/*------------- NVDS ---------- */
#define BX_DEV_NAME {'B','X','2','4','0','0'}
#define BX_DEV_ADDR {0x00,0x00,0x07,0x11,0x18,0x20}
#ifdef FLASH_XIP
#define BLE_WAKEUP_TIME {1200}
#else
#define BLE_WAKEUP_TIME {1060}
#endif
#define DEEP_SLEEP_ENABLE {0}
#define EXT_WAKE_UP_ENABLE {1}

/*------------- Debug ---------- */
//#define DEBUGGER_ATTACHED
//#define DO_NOT_WAKEUP
#define FREERTOS_WAKEUP_DELAY 900
#define XTAL_STARTUP_TIME 10

#define LDO_OUTPUT_SLEEP_RET
#define VDD_1V8_SLEEP_LDO1
//#define PWR_PWM_LEGACY //should be enabled before V4M
#define DIG_VOLTAGE_CTRL_BY_RF_REG
//#define DCDC_BYPASS_VOLTAGE_LEGACY //Must be ON for V4MB ,V4 ...
//#define RUN_WITHOUT_SLEEP
#ifdef RUN_WITHOUT_SLEEP
#undef DEEP_SLEEP_ENABLE
#define DEEP_SLEEP_ENABLE {0}
#endif
#if (MAIN_CLOCK>32000000)
#define CPU_LDO_BYPASS
#endif
#ifdef CFG_DYNAMIC_UPDATE
#define BATTERY_VOLTAGE_UPDATE_SECONDS 10
#define TEMPERATURE_UPDATE_SECONDS 10
#endif
#define BYPASS_VOLTAGE 3400

//define for BX2400 Version
#define BX2400_V1A 0x0
#define BX2400_V1B 0x1
#define BX2400_V2A 0x2
#define BX2400_V2B 0x3
#define BX2400_V3A 0x4
#define BX2400_V3B 0x5
#define BX2400_V4A_V4AMC 0x6
#define BX2400_V4B_V4BMC 0x7
#define BX2400_A01 0x8
#define BX2400_A02 0x9
#define BX2400_A03 0xA
#define BX2400_A04 0xB
#define BX2400_A05 0xC
#define BX2400_A06 0xD
#define BX2400_A07 0xE
#define BX2400_A08 0xF
#define BX2400_A09 0x10
#define BX2400_A10 0x11
#define BX2400_A11 0x12
#define BX2400_A12 0x13
#define BX2400_B1  0x14
#define BX2400_B2  0x15
#define BX2400_B3  0x16
#endif
