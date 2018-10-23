
#include "rgb_led.h"
#include "gpio.h"
#include "log.h"
#include <stdint.h>
#include <string.h>
#include "clk_gate.h"

struct gpioConfigStruct cfg0_4;     //Cin
struct gpioConfigStruct cfg0_5;     //Din


/* use example */
/*
 * rgb_led_init();
 * while(1)
 *	{
 *		rgb_led_set_color(0,128,0);
 *
 *		rgb_led_set_color(128,0,0);
 *
 *		rgb_led_set_color(0,0,128);
 *
 *		rgb_led_set_color(0,0,0);
 *	}
 */


void rgb_led_init()         // when use in realchip on gokit, we use gpio8,9
{
    sysc_per_clkg1_set(PER_CLKG_SET_GPIO);      //set gate of gpio.
    
    gpio_InitN(gpio0_4);
    gpio_InitN(gpio0_5);

    memset(&cfg0_4, 0, sizeof(cfg0_4));
    memset(&cfg0_5, 0, sizeof(cfg0_5));

    cfg0_5.debounce = gpio_Deb;
    cfg0_5.dir = gpio_Output;
    cfg0_5.value = gpio_Low;

    cfg0_4.debounce = gpio_Deb;
    cfg0_4.dir = gpio_Output;
    cfg0_4.value = gpio_Low;

    gpio_SetConfig(gpio0_5, &cfg0_5);
    gpio_SetConfig(gpio0_4, &cfg0_4);
    
}

void rgb_led_deinit()
{
    sysc_per_clkg1_set(PER_CLKG_CLR_GPIO);      //clear gate of gpio.

}

static __inline void set_cin_high(void)
{
    cfg0_4.value = gpio_High;
    gpio_SetConfig(gpio0_4, &cfg0_4);
}

static __inline void set_cin_low(void)
{
    cfg0_4.value = gpio_Low;
    gpio_SetConfig(gpio0_4, &cfg0_4);
    
}

static __inline void set_din_high(void)
{
    cfg0_5.value = gpio_High;
    gpio_SetConfig(gpio0_5, &cfg0_5);
}

static __inline void set_din_low(void)
{
    cfg0_5.value = gpio_Low;
    gpio_SetConfig(gpio0_5, &cfg0_5);
    
}

static void rgb_delay()
{
	uint16_t i;
	set_cin_low();
	for(i=0;i<16*40;i++);
	set_cin_high();
	for(i=0;i<16*40;i++);
}
static void rgb_led_send_data(uint32_t data)
{
    uint8_t i;
    uint32_t tmp;
    set_din_low();
    set_cin_low();

    for(i=0;i<32;i++)               //32bit for start
    {
    	/*
    	set_cin_high();
        set_cin_low();*/
    	rgb_delay();
    }
    tmp = 0x80000000;

    for(i=0;i<32;i++)
    {
        if(data & tmp)
        {
            set_din_high();
        }
        else
        {
            set_din_low();
        }
        tmp = tmp >> 1;
        /*
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        set_cin_high();
        set_cin_low();*/
        rgb_delay();
    }

    tmp = 0x80000000;

    for(i=0;i<32;i++)
    {
        if(data & tmp)
        {
            set_din_high();
        }
        else
        {
            set_din_low();
        }
        tmp = tmp >> 1;
        /*
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        set_cin_high();
        set_cin_low();*/
        rgb_delay();
    }

}

void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    volatile uint8_t data[4];
    volatile uint32_t rgb_data;

    data[3] = red;        //red
    data[2] = green;        //green
    data[1] = blue;        //blue

    data[0] = 0xC0 + (((~data[1] & 0xFF) >> 6)<<4) | (((~data[2] & 0xFF) >> 6)<<2) | (((~data[3] & 0xFF) >> 6));


    LOG(LOG_LVL_INFO,"%x\n",((~data[1] & 0xFF) >> 6)<<4);

    rgb_data = ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8) | (uint32_t)data[3];

    LOG(LOG_LVL_INFO,"%x,%x,%x,%x,%x",data[0],data[1],data[2],data[3],rgb_data);
    rgb_led_send_data(rgb_data);
    

}

