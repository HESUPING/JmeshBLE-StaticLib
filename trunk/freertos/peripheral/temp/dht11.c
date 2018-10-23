#include "dht11.h"
#include "gpio.h"
#include "log.h"
#include "timer.h"
#include "bx2400.h"
#include <string.h>

#include "rwip_task.h"
#include "osapp_task.h"
#include "clk_gate.h"
#include "bx_config.h"

//#define DHT_DEBUG

#define START_WAIT_18MS     1
#define START_WAIT_20US     2
#define WAIT_ACK        0
#define WAIT_ACK_DONE   1
#define WAIT_BIT_LOW    2
#define ONE_ZERO_THD    101


struct gpioConfigStruct cfg0_3;     //Cin
#ifdef DHT_DEBUG
    struct gpioConfigStruct cfg0_2;     // for debug : time of data get 
    static uint32_t dht_timer[40];
#endif

static uint8_t state;
static uint32_t bit40_i = 0;           //counter for the bit

struct dht_data_t
{
    uint64_t data;
};
static uint8_t databyte[3];         //temperature, humidity and checksum
static struct dht_data_t dht_data;
static uint8_t wait_bit_status = 0;
static uint32_t timer_cnt_old;
TaskHandle_t handler_dht_task;

#define TIMER_CLOCK_MHZ     10 


static void dht_gpioisr_callback(uint32_t no_use);


void dht_init()         // when use in gokit cfg0_3 should change to gpio10
{
    sysc_per_clkg1_set(PER_CLKG_SET_GPIO);      //set gate of gpio.
    #if HW_BX_VERSION == 2400
    sysc_cpu_clkg0_set(CPU_CLKG_SET_TIMER_DIV);
    #elif HW_BX_VERSION == 2401
    //nothing
    #else
    #error ERROR: ERROR to define HW_BX_VERSION
    #endif
    sysc_cpu_clkg1_set(CPU_CLKG_SET_TIMER0);    //set gate of timer.
    
    gpio_InitN(gpio0_3);

    memset(&cfg0_3, 0, sizeof(cfg0_3));

    cfg0_3.debounce = gpio_NoDeb;
    cfg0_3.dir = gpio_Output;
    cfg0_3.value = gpio_Low;

    cfg0_3.gpioCb = dht_gpioisr_callback;
    cfg0_3.irqLevel = gpio_Edge;
    cfg0_3.polarity = gpio_High_Rising;
    
    gpio_SetConfig(gpio0_3, &cfg0_3);

#ifdef DHT_DEBUG
    gpio_InitN(gpio0_2);

    memset(&cfg0_2, 0, sizeof(cfg0_2));

    cfg0_2.debounce = gpio_NoDeb;
    cfg0_2.dir = gpio_Output;
    cfg0_2.value = gpio_Low;

    gpio_SetConfig(gpio0_2, &cfg0_2);
#endif
    
    state = 0;
    bit40_i = 0;
    wait_bit_status = 0;

    NVIC_EnableIRQ(TIMER_IRQn);
    timer_Unmask(timerNum0);
    timer_SetMode(timerNum0, 1);


}

void dht_deinit()
{
    sysc_per_clkg1_set(PER_CLKG_CLR_GPIO);      //clear gate of gpio.
    #if HW_BX_VERSION == 2400
    sysc_cpu_clkg0_set(CPU_CLKG_CLR_TIMER_DIV);
    #elif HW_BX_VERSION == 2401
    //nothing
    #else
    #error ERROR: ERROR to define HW_BX_VERSION
    #endif
    sysc_cpu_clkg1_set(CPU_CLKG_CLR_TIMER0);    //clear gate of timer.
}


static __inline void dht_line_high(void)
{
    gpio_SetOutputValue(gpio0_3,gpio_High);
}

static __inline void dht_line_low(void)
{
    gpio_SetOutputValue(gpio0_3,gpio_Low);
}

static __inline void dht_line_readmode(void)
{
    cfg0_3.dir = gpio_Input;
    cfg0_3.debounce = gpio_NoDeb;
    gpio_SetConfig(gpio0_3, &cfg0_3);
}

#ifdef DHT_DEBUG
static __inline void dht_debug_high(void)
{
    gpio_SetOutputValue(gpio0_2,gpio_High);
}

static __inline void dht_debug_low(void)
{
    gpio_SetOutputValue(gpio0_2,gpio_Low);
}

#endif


static __inline void set_timer_us(uint16_t us)      //max 65.535ms
{
    timer_Disable(timerNum0);
    timer_LoadValue(timerNum0, us*TIMER_CLOCK_MHZ);
    timer_Enable(timerNum0);
}


static void dht_timer_callback(void *param)
{
    timer_Disable(timerNum0);

    switch(state)
    {
        case START_WAIT_18MS:
            set_timer_us(20);
            state = START_WAIT_20US;
            dht_line_high();
            break;
        case START_WAIT_20US:
            dht_line_readmode();
            gpio_SetPly(gpio0_3,gpio_Low_Falling);
            gpio_EnableIrq(gpio0_3);

#ifdef DHT_DEBUG
            dht_debug_high();
#endif             
            break;
    }
}


static void dht_gpioisr_callback(uint32_t no_use)
{
    uint32_t timer_cnt; 

    timer_GetValue(timerNum0, &timer_cnt);
    switch(wait_bit_status)
    {
        case WAIT_ACK:                     //DHT give ack and pull low, start counter
        { 
            wait_bit_status = WAIT_ACK_DONE;  
            break;
        }
        case WAIT_ACK_DONE:                     //DHT give ack and pull low, start counter
        { 
            set_timer_us(50000);
            timer_cnt_old = 500000;
            wait_bit_status = WAIT_BIT_LOW;
            bit40_i = 0;

            break;
        }
        case WAIT_BIT_LOW:
        {       
            if(bit40_i >= 40)
            {
                gpio_DisableIrq(gpio0_3);
                timer_Disable(timerNum0);
                dht_data.data = dht_data.data >> 1;
                databyte[0] = (dht_data.data & 0xFF00000000) >> 32;
                databyte[1] = (dht_data.data & 0x0000FF0000) >> 16;
                databyte[2] = (dht_data.data & 0x00000000FF);
#ifdef DHT_DEBUG 
                LOG(LOG_LVL_INFO,"%x,%x,%x\n",databyte[0],databyte[1],databyte[2]);
#endif
                break;
            }
#ifdef DHT_DEBUG            
            dht_timer[bit40_i] = timer_cnt_old - timer_cnt;
#endif
            if((timer_cnt_old - timer_cnt)> (ONE_ZERO_THD*TIMER_CLOCK_MHZ))        //get 1        
            {
                timer_cnt_old = timer_cnt;
#ifdef DHT_DEBUG
                dht_debug_high();
#endif  
                dht_data.data = dht_data.data | 1; 
                dht_data.data = dht_data.data << 1;
            }
            else
            {
                timer_cnt_old = timer_cnt;
                dht_data.data = (dht_data.data << 1);
#ifdef DHT_DEBUG
                dht_debug_low();
#endif  
            }
            bit40_i++;
            break;
        }
    }

}


uint8_t dht_get_result(uint8_t *temperature, uint8_t *humidity)
{
    if((databyte[0] + databyte[1]) == databyte[2])
    {
        if(databyte[2] == 0)
            return 0;
        *humidity = databyte[0];
        *temperature = databyte[1];
        return 1;
    }
    else
    {
        return 0;
    }
}


void dht_start()
{
    timer_Disable(timerNum0);
    dht_line_high();
    dht_line_low();
    memset(&dht_data,0,sizeof(dht_data));

    state = START_WAIT_18MS;
    timer_SetCallback(timerNum0, dht_timer_callback);
    set_timer_us(20000);
#ifdef DHT_DEBUG    
    dht_debug_high();
    dht_debug_low();
#endif
}

void dht_trigger_read()
{
    xTaskNotifyGive( handler_dht_task );
}

struct dht_result_t *result;

typedef void (*osapp_taskmsg_handler)(uint16_t,void const *);

void dht_task(void *params)
{
    uint8_t data[2];
    osapp_taskmsg_handler msg_handler = (osapp_taskmsg_handler)params;
    
    while(1)
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY ); /* Block indefinitely. */
        dht_init(); 
        dht_start();
        vTaskDelay(4);      //delay 80ms
        while(1)
        {
            if(dht_get_result(&data[0], &data[1]))
            {
                result->value[0] = data[0];
                result->value[1] = data[1];
                
                msg_handler(TEMPERATURE_AVALIABLE_IND,result);

                LOG(LOG_LVL_INFO," temperature = %d, humidity = %d\n",data[0],data[1]);
                break;
            }
        }
    }

}
    

