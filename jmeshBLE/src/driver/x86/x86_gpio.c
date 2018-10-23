#include"../jmesh_driver_config.h"
#if(JMESH_DRIVER_X86)

#include"../jmesh_gpio.h"
#include"stdio.h"

void jmesh_gpio_init(JMESH_GPIO_NAME_T gpio, int mode){
    printf("init gpio %d mode %d\n",gpio,mode);
}

extern void jmesh_gpio_interrupt_init(JMESH_GPIO_NAME_T gpio,int mode,jmesh_gpio_interrupt_callback_t interrupt_callback){
    printf("init gpio %d as a input interrupt\n",gpio);
}
void jmesh_gpio_set(JMESH_GPIO_NAME_T gpio, int value){
    printf("set gpio %d value %d\n",gpio,value);
}
int jmesh_gpio_get(JMESH_GPIO_NAME_T gpio){
    printf("get gpio %d value 0\n",gpio);
    return 0;
}
#endif
