/**
 *
 * @file adxl362.h
 *
 * @brief adxl362 driver may use in app layer as a peripheral of bx2400 system. adxl362 is an ultralow power , 3-axis MEMS accelerometer.
 * We can use adxl362 to make a intelligent pedometer to track steps.
 *
 * Copyright (C) Bluexmicro electronics 2015-2016
 *
 */

/**
 ****************************************************************************************
 * @addtogroup App Demo
 * @ingroup RTOS App
 * @brief Demo to show the capability of Bx2400.
 * @{
 ****************************************************************************************
 */
#ifndef ADXL_362_H
#define ADXL_362_H

#include "FreeRTOS.h"
#include "task.h"

/// command write to normal register
#define ADXL362_WRITE_REG           0x0A
/// command read from normal register
#define ADXL362_READ_REG            0x0B
/// command witer to fifo register
#define ADXL362_WRITE_FIFO          0x0D


/* Registers */
/// Register Address: Device ID Register. This register contains the Analog Devices device ID, 0xAD.
#define ADXL362_REG_DEVID_AD            0x00
/// Register Address: Device ID Register. This register contains the Analog Devices MEMS device ID, 0x1D.
#define ADXL362_REG_DEVID_MST           0x01
/// Register Address: PART ID Register. This register contains the device ID, 0xF2 (362 octal).
#define ADXL362_REG_PARTID              0x02
/// Register Address: SILICON REVISION ID Register. This register contains the product revision ID, beginning with 0x01 and incrementing for each subsequent revision.
#define ADXL362_REG_REVID               0x03
/**
 * @brief Register Address: X-AXIS DATA (8 MSB) REGISTER. This register holds the eight most significant bits of the x-axis acceleration data.
 * This limited resolution data register is used in power conscious applications where eight bits of data are sufficient:
 * energy can be conserved by reading only one byte of data per axis, rather than two.
*/
#define ADXL362_REG_XDATA               0x08
/**
 * @brief Register Address: Y-AXIS DATA (8 MSB) REGISTER. This register holds the eight most significant bits of the y-axis acceleration data.
 * This limited resolution data register is used in power conscious applications where eight bits of data are sufficient:
 * energy can be conserved by reading only one byte of data per axis, rather than two.
 */
#define ADXL362_REG_YDATA               0x09
/**
 * @brief Register Address: Z-AXIS DATA (8 MSB) REGISTER. This register holds the eight most significant bits of the z-axis acceleration data.
 * This limited resolution data register is used in power conscious applications where eight bits of data are sufficient:
 * energy can be conserved by reading only one byte of data per axis, rather than two.
 */
#define ADXL362_REG_ZDATA               0x0A
/// Register Address: STATUS REGISTER. This register includes the following bits that describe various conditions of the ADXL362.
#define ADXL362_REG_STATUS              0x0B
/**
 * @brief Register Address: FIFO ENTRIES REGISTERS. These registers indicate the number of valid data samples present in the FIFO buffer.
 * This number ranges from 0 to 512 or 0x00 to 0x200. FIFO_ENTRIES_L contains the least significant byte.
 */
#define ADXL362_REG_FIFO_L              0x0C
/**
 * @brief Register Address: FIFO ENTRIES REGISTERS. These registers indicate the number of valid data samples present in the FIFO buffer.
 * This number ranges from 0 to 512 or 0x00 to 0x200. FIFO_ENTRIES_H contains the two most significant bits. Bits[15:10] of FIFO_ENTRIES_H are unused
 */
#define ADXL362_REG_FIFO_H              0x0D
/**
 * @brief Register Address: X-AXIS DATA REGISTERS. The register contain the sign extended (SX) x-axis acceleration data.
 * XDATA_L contains the eight least significant bits (LSBs).
 */
#define ADXL362_REG_XDATA_L             0x0E
/**
 * @brief Register Address: X-AXIS DATA REGISTERS. The register contain the sign extended (SX) x-axis acceleration data.
 * XDATA_H contains the four most significant bits (MSBs) of the 12-bit value.
 */
#define ADXL362_REG_XDATA_H             0x0F
/**
 * @brief Register Address: Y-AXIS DATA REGISTERS. The register contain the sign extended (SX) y-axis acceleration data.
 * YDATA_L contains the eight least significant bits (LSBs).
 */
#define ADXL362_REG_YDATA_L             0x10
/**
 * @brief Register Address: Y-AXIS DATA REGISTERS. The register contain the sign extended (SX) y-axis acceleration data.
 * YDATA_H contains the four most significant bits (MSBs) of the 12-bit value.
 */
#define ADXL362_REG_YDATA_H             0x11
/**
 * @brief Register Address: Z-AXIS DATA REGISTERS. The register contain the sign extended (SX) z-axis acceleration data.
 * ZDATA_L contains the eight least significant bits (LSBs).
 */
#define ADXL362_REG_ZDATA_L             0x12
/**
 * @brief Register Address: Z-AXIS DATA REGISTERS. The register contain the sign extended (SX) z-axis acceleration data.
 * ZDATA_H contains the four most significant bits (MSBs) of the 12-bit value.
 */
#define ADXL362_REG_ZDATA_H             0x13
/**
 * @brief Register Address: TEMPERATURE DATA REGISTERS. The registers contain the sign extended (SX) tempera-ture sensor output data.
 * TEMP_L contains the eight LSBs
 */
#define ADXL362_REG_TEMP_L              0x14
/**
 * @brief Register Address: TEMPERATURE DATA REGISTERS. The registers contain the sign extended (SX) tempera-ture sensor output data.
 * TEMP_H contains the four MSBs of the 12-bit value. The value is sign extended.
 */
#define ADXL362_REG_TEMP_H              0x15
/// Register Address: SOFT RESET REGISTER. Writing Code 0x52 (representing the letter 'R' in ASCII or unicode) to this register immediately resets the ADXL362.
#define ADXL362_REG_SOFT_RESET          0x1F
/// Register Address: ACTIVITY THRESHOLD REGISTERS. THRESH_ACT, refers to an 11-bit unsigned value comprising the THRESH_ACT_L register, which holds its eight LSBs.
#define ADXL362_REG_THRESH_ACT_L        0x20
/// Register Address: ACTIVITY THRESHOLD REGISTERS. THRESH_ACT, refers to an 11-bit unsigned value comprising the THRESH_ACT_H register, which holds its three MSBs.
#define ADXL362_REG_THRESH_ACT_H        0x21
/// Register Address: ACTIVITY TIME REGISTER. The activity timer implements a robust activity detection that minimizes false positive motion triggers.
#define ADXL362_REG_TIME_ACT            0x22
/// Register Address: INACTIVITY THRESHOLD REGISTERS. To detect inactivity, THRESH_INACT, refers to an 11-bit unsigned value comprised of the THRESH_INACT_L registers, which holds its eight LSBs
#define ADXL362_REG_THRESH_INACT_L      0x23
/// Register Address: INACTIVITY THRESHOLD REGISTERS. To detect inactivity, THRESH_INACT, refers to an 11-bit unsigned value comprised of the THRESH_INACT_H register, which holds its three MSBs.
#define ADXL362_REG_THRESH_INACT_H      0x24
/**
 * @brief Register Address: INACTIVITY TIME REGISTERS. The 16-bit value in these registers sets the number of consecu-tive samples that must have all axes lower
 * than the inactivity threshold (set by THRESH_INACT) for an inactivity event to be detected. The TIME_INACT_L register holds the eight LSBs.
 */
#define ADXL362_REG_TIME_INACT_L        0x25
/**
 * @brief Register Address: INACTIVITY TIME REGISTERS. The 16-bit value in these registers sets the number of consecu-tive samples that must have all axes lower
 * than the inactivity threshold (set by THRESH_INACT) for an inactivity event to be detected. the TIME_INACT_H register holds the eight MSBs.
 */
#define ADXL362_REG_TIME_INACT_H        0x26
/// Register Address: ACTIVITY/INACTIVITY CONTROL REGISTER.
#define ADXL362_REG_ACT_INACT_CTL       0x27
/// Register Address: FIFO CONTROL REGISTER
#define ADXL362_REG_FIFO_CTL            0x28
/**
 * @brief Register Address: FIFO SAMPLES REGISTER. The value in this register specifies the number of samples to store in the FIFO.
 * The AH bit in the FIFO_CONTROL register (Address 0x28) is used as the MSB of this value. The full range of FIFO samples is 0 to 511.
 */
#define ADXL362_REG_FIFO_SAMPLES        0x29
/// Register Address: INT1 FUNCTION MAP REGISTERS. The INT1 register configure the INT1 interrupt pins, respectively.
#define ADXL362_REG_INTMAP1             0x2A
/// Register Address: INT2 FUNCTION MAP REGISTERS. The INT2 register configure the INT2 interrupt pins, respectively.
#define ADXL362_REG_INTMAP2             0x2B
/// Register Address: FILTER CONTROL REGISTER.
#define ADXL362_REG_FILTER_CTL          0x2C
/// Register Address: POWER CONTROL REGISTER.
#define ADXL362_REG_POWER_CTL           0x2D
/// Register Address: SELF TEST REGISTER.
#define ADXL362_REG_SELF_TEST           0x2E


/* ADXL362_REG_STATUS definitions */
#define ADXL362_STATUS_ERR_USER_REGS        (1 << 7)
#define ADXL362_STATUS_AWAKE                (1 << 6)
#define ADXL362_STATUS_INACT                (1 << 5)
#define ADXL362_STATUS_ACT                  (1 << 4)
#define ADXL362_STATUS_FIFO_OVERRUN         (1 << 3)
#define ADXL362_STATUS_FIFO_WATERMARK       (1 << 2)
#define ADXL362_STATUS_FIFO_RDY             (1 << 1)
#define ADXL362_STATUS_DATA_RDY             (1 << 0)

/* ADXL362_REG_ACT_INACT_CTL definitions */
#define ADXL362_ACT_INACT_CTL_LINKLOOP(x)   (((x) & 0x3) << 4)
#define ADXL362_ACT_INACT_CTL_INACT_REF     (1 << 3)
#define ADXL362_ACT_INACT_CTL_INACT_EN      (1 << 2)
#define ADXL362_ACT_INACT_CTL_ACT_REF       (1 << 1)
#define ADXL362_ACT_INACT_CTL_ACT_EN        (1 << 0)

/* ADXL362_ACT_INACT_CTL_LINKLOOP(x) options */
#define ADXL362_MODE_DEFAULT        0
#define ADXL362_MODE_LINK           1
#define ADXL362_MODE_LOOP           3

/* ADXL362_REG_FIFO_CTL */
#define ADXL362_FIFO_CTL_AH                 (1 << 3)
#define ADXL362_FIFO_CTL_FIFO_TEMP          (1 << 2)
#define ADXL362_FIFO_CTL_FIFO_MODE(x)       (((x) & 0x3) << 0)

/* ADXL362_FIFO_CTL_FIFO_MODE(x) options */
#define ADXL362_FIFO_DISABLE              0
#define ADXL362_FIFO_OLDEST_SAVED         1
#define ADXL362_FIFO_STREAM               2
#define ADXL362_FIFO_TRIGGERED            3

/* ADXL362_REG_INTMAP1 */
#define ADXL362_INTMAP1_INT_LOW             (1 << 7)
#define ADXL362_INTMAP1_AWAKE               (1 << 6)
#define ADXL362_INTMAP1_INACT               (1 << 5)
#define ADXL362_INTMAP1_ACT                 (1 << 4)
#define ADXL362_INTMAP1_FIFO_OVERRUN        (1 << 3)
#define ADXL362_INTMAP1_FIFO_WATERMARK      (1 << 2)
#define ADXL362_INTMAP1_FIFO_READY          (1 << 1)
#define ADXL362_INTMAP1_DATA_READY          (1 << 0)

/* ADXL362_REG_INTMAP2 definitions */
#define ADXL362_INTMAP2_INT_LOW             (1 << 7)
#define ADXL362_INTMAP2_AWAKE               (1 << 6)
#define ADXL362_INTMAP2_INACT               (1 << 5)
#define ADXL362_INTMAP2_ACT                 (1 << 4)
#define ADXL362_INTMAP2_FIFO_OVERRUN        (1 << 3)
#define ADXL362_INTMAP2_FIFO_WATERMARK      (1 << 2)
#define ADXL362_INTMAP2_FIFO_READY          (1 << 1)
#define ADXL362_INTMAP2_DATA_READY          (1 << 0)

/* ADXL362_REG_FILTER_CTL definitions */
#define ADXL362_FILTER_CTL_RANGE(x)         (((x) & 0x3) << 6)
#define ADXL362_FILTER_CTL_RES              (1 << 5)
#define ADXL362_FILTER_CTL_HALF_BW          (1 << 4)
#define ADXL362_FILTER_CTL_EXT_SAMPLE       (1 << 3)
#define ADXL362_FILTER_CTL_ODR(x)           (((x) & 0x7) << 0)

/* ADXL362_FILTER_CTL_RANGE(x) options */
#define ADXL362_RANGE_2G                0 /* +-2 g */
#define ADXL362_RANGE_4G                1 /* +-4 g */
#define ADXL362_RANGE_8G                2 /* +-8 g */

/* ADXL362_FILTER_CTL_ODR(x) options */
#define ADXL362_ODR_12_5_HZ             0 /* 12.5 Hz */
#define ADXL362_ODR_25_HZ               1 /* 25 Hz */
#define ADXL362_ODR_50_HZ               2 /* 50 Hz */
#define ADXL362_ODR_100_HZ              3 /* 100 Hz */
#define ADXL362_ODR_200_HZ              4 /* 200 Hz */
#define ADXL362_ODR_400_HZ              5 /* 400 Hz */

/* ADXL362_REG_POWER_CTL definitions */
#define ADXL362_POWER_CTL_RES               (1 << 7)
#define ADXL362_POWER_CTL_EXT_CLK           (1 << 6)
#define ADXL362_POWER_CTL_LOW_NOISE(x)      (((x) & 0x3) << 4)
#define ADXL362_POWER_CTL_WAKEUP            (1 << 3)
#define ADXL362_POWER_CTL_AUTOSLEEP         (1 << 2)
#define ADXL362_POWER_CTL_MEASURE(x)        (((x) & 0x3) << 0)

/* ADXL362_POWER_CTL_LOW_NOISE(x) options */
#define ADXL362_NOISE_MODE_NORMAL           0
#define ADXL362_NOISE_MODE_LOW              1
#define ADXL362_NOISE_MODE_ULTRALOW         2

/* ADXL362_POWER_CTL_MEASURE(x) options */
#define ADXL362_MEASURE_STANDBY         0
#define ADXL362_MEASURE_ON              2

/* ADXL362_REG_SELF_TEST */
#define ADXL362_SELF_TEST_ST            (1 << 0)

/* ADXL362 device information */
#define ADXL362_DEVICE_AD               0xAD
#define ADXL362_DEVICE_MST              0x1D
#define ADXL362_PART_ID                 0xF2

/* ADXL362 Reset settings */
#define ADXL362_RESET_KEY               0x52


/// define a micro to identify the message type.
#define MEMS_STEP_MSG                   0x1
/// extern the handler of mems task which can be use when create mems task.
extern TaskHandle_t handler_mems_task;

/**
 * @brief initialize the adxl362. Define pinshare and spi interface here.
 */
void adxl362_init(void);
/**
 * @brief set the register of adxl362.
 * @param registerValue: value need to be written into the register.
 * @param registerAddress: address to write value.
 * @param bytesNumber: length of the value, only the length of the value itself.
 */
void adxl362_setregistervalue(unsigned char registerValue,
                              unsigned char  registerAddress,
                              uint16_t  bytesNumber);
/**
 * @brief get value from register of adxl362.
 * @param pReadData: pointer to the data storage buffer.
 * @param registerAddress: address to read the data from.
 * @param bytesNumber: length of the data, only the length of the data itself.
 */
void adxl362_getregistervalue(unsigned char* pReadData,
                              unsigned char  registerAddress,
                              uint16_t  bytesNumber);
/**
 * @brief ADXL362 has a temperature sensor which mainly use to calibrate the acceleration output.
 * To use the temperature sensor to monitor absolute temperature, it is recommended that its initial bias
 *  (its output at some known temperature) is measured and calibrated.
 * @return temperature output.
 */
float adxl362_read_temperature(void);
/**
 * @brief reset adxl362
 */
void adxl362_reset(void);
/**
 * @brief read current xyz(without reading fifo)
 * @param x: pointer to the output of x-axis acceleration
 * @param y: pointer to the output of y-axis acceleration
 * @param z: pointer to the output of z-axis acceleration
 */
void adxl362_getxyz(short* x, short* y, short* z);
/**
 * @brief normal settings of adxl362.
 */
void adxl362_normal_setting(void);
/**
 * @brief count steps. There is a simple algorithm in this function.
 * @param current_g: current_g = gx_f*gx_f + gy_f*gy_f + gz_f*gz_f
 * @return return 1 means 1 step. return 0 means no step.
 */
uint8_t adxl362_count_steps(float current_g);

/**
 * @brief get data from fifo.
 * @param x: pointer to the output of x-axis acceleration
 * @param y: pointer to the output of y-axis acceleration
 * @param z: pointer to the output of z-axis acceleration
 * @return return 0 when data array has error.
 */
uint8_t adxl362_fifoxyz(short *x, short *y, short *z);
/**
 * @brief mems task, use adxl362 to count steps.
 * @param params: pointer to the input parameter.
 */
void mems_task(void *params);



#endif

