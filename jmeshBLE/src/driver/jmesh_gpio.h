#ifndef JMESH_GPIO_H
#define JMESH_GPIO_H
#include"jmesh_gpio_int_callback.h"

typedef enum {
    JMESH_LED1,
    JMESH_LED2,
    JMESH_LED_GREEN,
    JMESH_LED_RED,
    JMESH_OUTPUT_5,
    JMESH_INPUT_6,
		POWER_LIGHT,
} JMESH_GPIO_NAME_T;
enum {
    JMESH_GPIO_MODE_INPUT,
    JMESH_GPIO_MODE_OUTPUT,
};
enum {
    GPIO_VALUE_HIGH,
    GPIO_VALUE_LOW,
};

enum {
    GPIO_INT_TRIG_HIGH_LEVEL,
    GPIO_INT_TRIG_LOW_LEVEL,
    GPIO_INT_TRIG_POS_EDGE,
    GPIO_INT_TRIG_NEG_EDGE,
};


extern void jmesh_gpio_init(JMESH_GPIO_NAME_T gpio, int mode);
extern void jmesh_gpio_interrupt_init(JMESH_GPIO_NAME_T gpio,int mode,jmesh_gpio_interrupt_callback_t interrupt_callback);
extern void jmesh_gpio_set(JMESH_GPIO_NAME_T gpio, int value);
extern int jmesh_gpio_get(JMESH_GPIO_NAME_T gpio);


#endif // JMESH_GPIO_H
