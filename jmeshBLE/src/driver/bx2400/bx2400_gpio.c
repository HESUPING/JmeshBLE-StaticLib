#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"../jmesh_gpio.h"
#include"stdio.h"
#include "io_ctrl.h"


void jmesh_gpio_init(JMESH_GPIO_NAME_T gpio, int mode){
    unsigned char pin_num;
    unsigned char dir;
    switch(gpio)
    {
        case JMESH_LED1:
            pin_num=4;
            break;
        case JMESH_LED2:
            pin_num=1;
            break;
        case JMESH_LED_GREEN:
            pin_num=1;
            break;
        case JMESH_LED_RED:
            pin_num=1;
            break;
        case JMESH_OUTPUT_5:
            pin_num=1;
            break;
        case JMESH_INPUT_6:
            pin_num=1;
            break;
        case POWER_LIGHT:
            pin_num=22;
            break;			
        default:
            return;
    }
    switch(mode)
    {
        case JMESH_GPIO_MODE_INPUT:
            dir=0;
            break;
        case JMESH_GPIO_MODE_OUTPUT:
            dir=1;
            break;
        default:
            return;
    }
    io_pin_dir_set(pin_num,dir);
}

extern void jmesh_gpio_interrupt_init(JMESH_GPIO_NAME_T gpio,int mode,jmesh_gpio_interrupt_callback_t interrupt_callback){
    unsigned char pin_num;
    ext_int_mode_t int_mode;
    switch(gpio)
    {
        case JMESH_LED1:
            pin_num=4;
            break;
        case JMESH_LED2:
            pin_num=1;
            break;
        case JMESH_LED_GREEN:
            pin_num=1;
            break;
        case JMESH_LED_RED:
            pin_num=1;
            break;
        case JMESH_OUTPUT_5:
            pin_num=1;
            break;
        case JMESH_INPUT_6:
            pin_num=1;
            break;
        case POWER_LIGHT:
            pin_num=22;
            break;			
        default:
            return;
    }
    switch(int_mode)
    {
        case GPIO_INT_TRIG_HIGH_LEVEL:
            int_mode=EXT_INT_TRIGGER_HIGH_LEVEL;
            break;
        case GPIO_INT_TRIG_LOW_LEVEL:
            int_mode=EXT_INT_TRIGGER_LOW_LEVEL;
            break;
        case GPIO_INT_TRIG_POS_EDGE:
            int_mode=EXT_INT_TRIGGER_POS_EDGE;
            break;
        case GPIO_INT_TRIG_NEG_EDGE:
            int_mode=EXT_INT_TRIGGER_NEG_EDGE;
            break;
        default:
            return;
    }
    io_ext_int_cfg(pin_num,int_mode,jmesh_gpio_int_callback);
    io_ext_int_en(pin_num,true);
}
void jmesh_gpio_set(JMESH_GPIO_NAME_T gpio, int value){
    unsigned char pin_num;
    //unsigned char val;
    switch(gpio)
    {
        case JMESH_LED1:
            pin_num=4;
            break;
        case JMESH_LED2:
            pin_num=1;
            break;
        case JMESH_LED_GREEN:
            pin_num=1;
            break;
        case JMESH_LED_RED:
            pin_num=1;
            break;
        case JMESH_OUTPUT_5:
            pin_num=1;
            break;
        case JMESH_INPUT_6:
            pin_num=1;
            break;
        case POWER_LIGHT:
            pin_num=22;
            break;				
        default:
            return;
    }
    switch(value)
    {
        case GPIO_VALUE_HIGH:
            //val=1;
            io_pin_set(pin_num);
            break;
        case GPIO_VALUE_LOW:
            //val=0;
            io_pin_clear(pin_num);
            break;
        default:
            return;
    }
    //io_pin_write(pin_num,val);
}
int jmesh_gpio_get(JMESH_GPIO_NAME_T gpio){
    unsigned char pin_num;
    switch(gpio)
    {
        case JMESH_LED1:
            pin_num=4;
            break;
        case JMESH_LED2:
            pin_num=1;
            break;
        case JMESH_LED_GREEN:
            pin_num=1;
            break;
        case JMESH_LED_RED:
            pin_num=1;
            break;
        case JMESH_OUTPUT_5:
            pin_num=1;
            break;
        case JMESH_INPUT_6:
            pin_num=1;
            break;
        case POWER_LIGHT:
            pin_num=22;
            break;				
        default:
            return -1;
    }
    return io_pin_read(pin_num);
}
#endif
