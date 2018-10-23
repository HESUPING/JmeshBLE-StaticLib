
#include "dw_apb_ssi_typedef.h"
#include "reg_spim.h"
#include "adxl362.h"
#include "pshare.h"
#include "reg_sysc_per.h"
#include "log.h"
#include "oled.h"
#include "bx_config.h"
#include "clk_gate.h"

#define SPIM_CLK_IN	32000000
#define SPIM_SCLK_OUT	8000000
#define SLAVE_ID 1
#define adxl_high_thd   2.2
#define adxl_low_thd    0.9

static uint8_t current_state = 0;
TaskHandle_t handler_mems_task;

//#define HUAMI_ADXL362

typedef void (*callback_func)(uint8_t type, uint8_t *value);

void adxl362_init()
{
	#if HW_BX_VERSION == 2400
    #ifdef HUAMI_ADXL362                        //change REG_SPIM_1_BASE to 0x20141000
    pshare_pin_share_en(0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 1, 0);
    clk_gate_per_g0(PER_CLKG1_SET_SPIM0 | PER_CLKG0_SET_SPIM0);
    #else
    pshare_pin_share_en(0, 0, 0, 0, 0, 0, 
				0, 0, 1, 0, 0, 0);
    clk_gate_per_g0(PER_CLKG1_SET_SPIM1 | PER_CLKG0_SET_SPIM1);
    #endif
    
	#elif HW_BX_VERSION == 2401
    pshare_pin_share_en(0, 0, 0, 0, 
				0, 0, 1, 0, 0, 0);
    sysc_per_clkg0_set(0x100000);
	#else
	#error ERROR: ERROR to define HW_BX_VERSION
	#endif
    spim_ssi_en_setf(SSI_Disabled);
    spim_sckdv_setf(SPIM_CLK_IN/SPIM_SCLK_OUT);

    adxl362_reset();
}


static void adxl362_write(uint8_t slave_id, uint8_t *buff, uint16_t byte_num)
{
    uint8_t i;
    spim_ctrlr0_pack(DFS_32_8_bits,0,0,0,Transmit_Only,Inactive_Low,SCLK_Toggle_In_Middle,Motorola_SPI);

    spim_ctrlr1_pack(0);
	spim_ssi_en_setf(SSI_Enabled);

    
    for(i=0;i<byte_num+2;i++)
        spim_dr_set(*buff++);
    spim_ser_set(slave_id);

    while(spim_tfe_getf() == 0);
    
    spim_ssi_en_setf(SSI_Disabled);
}


static void adxl362_read(uint8_t slave_id, uint8_t *buff, uint16_t byte_num)
{
    uint8_t i = 0;
    spim_ctrlr0_pack(DFS_32_8_bits,0,0,0,EEPROM_Read,Inactive_Low,SCLK_Toggle_In_Middle,Motorola_SPI);
    spim_ctrlr1_pack(byte_num-1);
	spim_ssi_en_setf(SSI_Enabled);
    for(i=0;i<2;i++)
        spim_dr_set(*buff++);
    
    spim_ser_set(slave_id);

    for(i=0;i<byte_num;i++)
    {
        while(spim_rfne_getf()==Receive_FIFO_Empty);
        *buff++=spim_dr_get();
    }

    spim_ssi_en_setf(SSI_Disabled);
}





void adxl362_setregistervalue(unsigned char registerValue,
                              unsigned char  registerAddress,
                              uint16_t  bytesNumber)
{
    uint8_t buffer[4] = {0, 0, 0, 0};

    buffer[0] = ADXL362_WRITE_REG;
    buffer[1] = registerAddress;
    buffer[2] = registerValue;
    adxl362_write(SLAVE_ID, buffer, bytesNumber);
}



void adxl362_getregistervalue(unsigned char* pReadData,
                              unsigned char  registerAddress,
                              uint16_t  bytesNumber)
{
    uint8_t buffer[32];
    uint8_t index = 0;
    
    buffer[0] = ADXL362_READ_REG;
    buffer[1] = registerAddress;
    
    adxl362_read(SLAVE_ID, buffer, bytesNumber);
    for(index = 0; index < bytesNumber; index++)
    {
        pReadData[index] = buffer[index + 2];
    }
}

float adxl362_read_temperature(void)
{
    unsigned char rawTempData[2] = {0, 0};
    short         signedTemp     = 0;
    float         tempCelsius    = 0;
    adxl362_getregistervalue(rawTempData, ADXL362_REG_TEMP_L, 2);
    signedTemp = (short)(rawTempData[1] << 8) + rawTempData[0];
    tempCelsius = (float)signedTemp * 0.065;
    LOG(LOG_LVL_INFO, "after read temp %d-%x,%x\n",signedTemp, rawTempData[0],rawTempData[1]);
    return tempCelsius;
}


void adxl362_reset()
{
    adxl362_setregistervalue(0x52,ADXL362_REG_SOFT_RESET,1);
}


/***************************************************************************//**
 * @brief Reads multiple bytes from the device's FIFO buffer.
 *
 * @param pBuffer - Stores the read bytes.
 * @param bytesNumber - Number of bytes to read.
 *
 * @return None.
*******************************************************************************/
static void adxl362_getfifovalue(uint8_t *buf, unsigned short bytesNumber)
{

    uint8_t i = 0;

    *buf = ADXL362_WRITE_FIFO;

    spim_ctrlr0_pack(DFS_32_8_bits,0,0,0,EEPROM_Read,Inactive_Low,SCLK_Toggle_In_Middle,Motorola_SPI);
    spim_ctrlr1_pack(bytesNumber-1);
	spim_ssi_en_setf(SSI_Enabled);
    for(i=0;i<1;i++)
        spim_dr_set(*buf++);
    
    spim_ser_set(SLAVE_ID);

    for(i=0;i<bytesNumber;i++)
    {
        while(spim_rfne_getf()==Receive_FIFO_Empty);
        *buf++=spim_dr_get();
    }

    spim_ssi_en_setf(SSI_Disabled);

}



/***************************************************************************//**
 * @brief Places the device into standby/measure mode.
 *
 * @param pwrMode - Power mode.
 *                  Example: 0 - standby mode.
 *		                     1 - measure mode.
 *
 * @return None.
*******************************************************************************/
void adxl362_setpowermode(unsigned char pwrMode)
{
    unsigned char oldPowerCtl = 0;
    unsigned char newPowerCtl = 0;

    adxl362_getregistervalue(&oldPowerCtl, ADXL362_REG_POWER_CTL, 1);
    newPowerCtl = oldPowerCtl & (~ ADXL362_POWER_CTL_MEASURE(0x3));
    newPowerCtl = newPowerCtl |
                  (pwrMode * ADXL362_POWER_CTL_MEASURE(ADXL362_MEASURE_ON));
    adxl362_setregistervalue(newPowerCtl, ADXL362_REG_POWER_CTL, 1);
}

/***************************************************************************//**
 * @brief Selects the measurement range.
 *
 * @param gRange - Range option.
 *                  Example: ADXL362_RANGE_2G  -  +-2 g
 *                           ADXL362_RANGE_4G  -  +-4 g
 *                           ADXL362_RANGE_8G  -  +-8 g
 *                           
 * @return None.
*******************************************************************************/
void adxl362_setrange(unsigned char gRange)
{
    unsigned char oldFilterCtl = 0;
    unsigned char newFilterCtl = 0;

    adxl362_getregistervalue(&oldFilterCtl, ADXL362_REG_FILTER_CTL, 1);
    newFilterCtl = oldFilterCtl & (~ ADXL362_FILTER_CTL_RANGE(0x3));
    newFilterCtl = newFilterCtl | ADXL362_FILTER_CTL_RANGE(gRange);
    adxl362_setregistervalue(newFilterCtl, ADXL362_REG_FILTER_CTL, 1);
}

/***************************************************************************//**
 * @brief Selects the Output Data Rate of the device.
 *
 * @param outRate - Output Data Rate option.
 *                  Example: ADXL362_ODR_12_5_HZ  -  12.5Hz
 *                           ADXL362_ODR_25_HZ    -  25Hz
 *                           ADXL362_ODR_50_HZ    -  50Hz
 *                           ADXL362_ODR_100_HZ   -  100Hz
 *                           ADXL362_ODR_200_HZ   -  200Hz
 *                           ADXL362_ODR_400_HZ   -  400Hz
 *
 * @return None.
*******************************************************************************/
void adxl362_setoutputrate(unsigned char outRate)
{
    unsigned char oldFilterCtl = 0;
    unsigned char newFilterCtl = 0;

    adxl362_getregistervalue(&oldFilterCtl, ADXL362_REG_FILTER_CTL, 1);
    newFilterCtl = oldFilterCtl & (~ ADXL362_FILTER_CTL_ODR(0x7));
    newFilterCtl = newFilterCtl | ADXL362_FILTER_CTL_ODR(outRate);
    adxl362_setregistervalue(newFilterCtl, ADXL362_REG_FILTER_CTL, 1);
}

/***************************************************************************//**
 * @brief Reads the 3-axis raw data from the accelerometer.
 *
 * @param x - Stores the X-axis data(as two's complement).
 * @param y - Stores the X-axis data(as two's complement).
 * @param z - Stores the X-axis data(as two's complement).
 *
 * @return None.
*******************************************************************************/
void adxl362_getxyz(short* x, short* y, short* z)
{
    unsigned char xyzValues[6] = {0, 0, 0, 0, 0, 0};

    adxl362_getregistervalue(xyzValues, ADXL362_REG_XDATA_L, 6);

    *x = ((short)xyzValues[1] << 8) + xyzValues[0];
    *y = ((short)xyzValues[3] << 8) + xyzValues[2];
    *z = ((short)xyzValues[5] << 8) + xyzValues[4];
}

/***************************************************************************//**
 * @brief Reads the temperature of the device.
 *
 * @return tempCelsius - The value of the temperature(degrees Celsius).
*******************************************************************************/
float adxl362_readtemperature(void)
{
    unsigned char rawTempData[2] = {0, 0};
    short         signedTemp     = 0;
    float         tempCelsius    = 0;

    adxl362_getregistervalue(&rawTempData[0], ADXL362_REG_TEMP_L, 1);

    adxl362_getregistervalue(&rawTempData[1], ADXL362_REG_TEMP_H, 1);

    signedTemp = (short)(rawTempData[1] << 8) + rawTempData[0];
    tempCelsius = (float)signedTemp * 0.065;
    
    return tempCelsius;
}

/***************************************************************************//**
 * @brief Configures the FIFO feature.
 *
 * @param mode - Mode selection.
 *               Example: ADXL362_FIFO_DISABLE        -  FIFO is disabled.
 *                        ADXL362_FIFO_OLDEST_SAVED   -  Oldest saved mode.
 *                        ADXL362_FIFO_STREAM         -  Stream mode.
 *                        ADXL362_FIFO_TRIGGERED      -  Triggered mode.
 * @param waterMarkLvl - Specifies the number of samples to store in the FIFO.
 * @param enTempRead - Store Temperature Data to FIFO.
 *                     Example: 1 - temperature data is stored in the FIFO
 *                                  together with x-, y- and x-axis data.
 *                              0 - temperature data is skipped.
 *
 * @return None.
*******************************************************************************/
void adxl362_fifosetup(unsigned char  mode,
                       unsigned short waterMarkLvl,
                       unsigned char  enTempRead)
{
    unsigned char writeVal = 0;

    writeVal = ADXL362_FIFO_CTL_FIFO_MODE(mode) |
               (enTempRead * ADXL362_FIFO_CTL_FIFO_TEMP) |
               ADXL362_FIFO_CTL_AH;
    adxl362_setregistervalue(writeVal, ADXL362_REG_FIFO_CTL, 1);
    adxl362_setregistervalue(waterMarkLvl, ADXL362_REG_FIFO_SAMPLES, 2);
}

/***************************************************************************//**
 * @brief Configures activity detection.
 *
 * @param refOrAbs - Referenced/Absolute Activity Select.
 *                   Example: 0 - absolute mode.
 *                            1 - referenced mode.
 * @param threshold - 11-bit unsigned value that the adxl362 samples are
 *                    compared to.
 * @param time - 8-bit value written to the activity timer register. The amount
 *               of time (in seconds) is: time / ODR, where ODR - is the output 
 *               data rate.
 *
 * @return None.
*******************************************************************************/
void adxl362_setupactivitydetection(unsigned char  refOrAbs,
                                    unsigned short threshold,
                                    unsigned char  time)
{
    unsigned char oldActInactReg = 0;
    unsigned char newActInactReg = 0;

    /* Configure motion threshold and activity timer. */
    adxl362_setregistervalue((threshold & 0x7FF), ADXL362_REG_THRESH_ACT_L, 2);
    adxl362_setregistervalue(time, ADXL362_REG_TIME_ACT, 1);
    /* Enable activity interrupt and select a referenced or absolute
       configuration. */
    adxl362_getregistervalue(&oldActInactReg, ADXL362_REG_ACT_INACT_CTL, 1);
    newActInactReg = oldActInactReg & ~ADXL362_ACT_INACT_CTL_ACT_REF;
    newActInactReg |= ADXL362_ACT_INACT_CTL_ACT_EN |
                     (refOrAbs * ADXL362_ACT_INACT_CTL_ACT_REF);
    adxl362_setregistervalue(newActInactReg, ADXL362_REG_ACT_INACT_CTL, 1);
}

/***************************************************************************//**
 * @brief Configures inactivity detection.
 *
 * @param refOrAbs - Referenced/Absolute Inactivity Select.
 *                   Example: 0 - absolute mode.
 *                            1 - referenced mode.
 * @param threshold - 11-bit unsigned value that the adxl362 samples are
 *                    compared to.
 * @param time - 16-bit value written to the inactivity timer register. The 
 *               amount of time (in seconds) is: time / ODR, where ODR - is the 
 *               output  data rate.
 *
 * @return None.
*******************************************************************************/
void adxl362_setupinactivitydetection(unsigned char  refOrAbs,
                                      unsigned short threshold,
                                      unsigned short time)
{
    unsigned char oldActInactReg = 0;
    unsigned char newActInactReg = 0;
    
    /* Configure motion threshold and inactivity timer. */
    adxl362_setregistervalue((threshold & 0x7FF),
                              ADXL362_REG_THRESH_INACT_L,
                              2);
    adxl362_setregistervalue(time, ADXL362_REG_TIME_INACT_L, 2);
    /* Enable inactivity interrupt and select a referenced or absolute
       configuration. */
    adxl362_getregistervalue(&oldActInactReg, ADXL362_REG_ACT_INACT_CTL, 1);
    newActInactReg = oldActInactReg & ~ADXL362_ACT_INACT_CTL_INACT_REF;
    newActInactReg |= ADXL362_ACT_INACT_CTL_INACT_EN |
                     (refOrAbs * ADXL362_ACT_INACT_CTL_INACT_REF);
    adxl362_setregistervalue(newActInactReg, ADXL362_REG_ACT_INACT_CTL, 1);
}



void adxl362_normal_setting()
{
    adxl362_setpowermode(1);
    adxl362_setrange(ADXL362_RANGE_2G);
    adxl362_setoutputrate(ADXL362_ODR_100_HZ);
    adxl362_fifosetup(ADXL362_FIFO_STREAM,0x80,0);

}



uint8_t adxl362_count_steps(float current_g)
{
    
    if(current_g > adxl_high_thd)
    {
        if(current_state == 0)
        {
            current_state = 1;
            return 1;
        }
    }

    if(current_g < adxl_low_thd)
    {
        if(current_state == 1)
        {
            current_state = 0;
        }
    }
        
    return 0;

}



static uint8_t adxl362_get_2byte_fifo(short *value, uint8_t *type)     // type 0-x 1-y 2-z 3-temp
{
    uint8_t buff[3];
    adxl362_getfifovalue(buff, 2);
    if((buff[1]==0) && (buff[2]==0))
    {
        return 0;           // error value because fifo is empty
    }
    else
    {
        switch (buff[2]>>6)
        {
            case 0:
                *type = 0;
                break;
            case 1:
                *type = 1;
                break;
            case 2:
                *type = 2;
                break;
            case 3:
                *type = 3;
                break;
        }
        if(((buff[2] >> 4) & 1) == 1)
        {
            buff[2] |= 0xC0;
        }
        else
        {
            buff[2] &= 0x3F;
        }
        *value = buff[1] + (int16_t)((buff[2]) << 8);

        return 1;
    }
}

uint8_t adxl362_fifoxyz(short *x, short *y, short *z)
{
    short value;
    uint8_t type;
    //find first x

    while(1)
    {
        if(adxl362_get_2byte_fifo(&value,&type))
        {
            if(type == 0)
            {
                *x = value;
                break;
            }
        }
    }

    if(adxl362_get_2byte_fifo(&value,&type))
    {
        if(type == 1)
        {
            *y = value;
        }
        else
        {
            return 0;
        }
    }

    if(adxl362_get_2byte_fifo(&value,&type))
    {
        if(type == 2)
        {
            *z = value;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}


void mems_task(void *params)
{
    int16_t gx,gy,gz;
    float gx_f,gy_f,gz_f;
    float total_g;
//    char str[50];
    uint8_t value[4];
    uint32_t count = 0;
    uint8_t i;
    callback_func report_func = (callback_func)params;

    adxl362_init();
    vTaskDelay(1);
    adxl362_normal_setting();
    
    while(1)
    {
        vTaskDelay(10);         //about 200ms      

        for(i = 0; i < 20; i++)                 // 100HZ sample rate in 200ms makes 20 results
        {
            adxl362_fifoxyz(&gx,&gy,&gz);
            gx_f = (((int16_t)gx)/1000.0);
    		gy_f = (((int16_t)gy)/1000.0);
    		gz_f = (((int16_t)gz)/1000.0);

            total_g = gx_f*gx_f + gy_f*gy_f + gz_f*gz_f;

            count += adxl362_count_steps(total_g);
                           
//    	    sprintf(str,"%d-%f,%f,%f,%f,%d\n",i,gx_f,gy_f,gz_f,total_g,count);   
        }
//        oled_printf(10,1,"Step = %d",count);

        value[0] = count & 0xff;
        value[1] = (count >> 8) & 0xff;
        value[2] = (count >> 16) & 0xff;
        value[3] = (count >> 24) & 0xff;
        report_func(MEMS_STEP_MSG,value); 

    }


}

