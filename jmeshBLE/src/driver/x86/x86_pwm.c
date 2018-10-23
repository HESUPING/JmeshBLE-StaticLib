#include"../jmesh_driver_config.h"
#if(JMESH_DRIVER_X86)

#include"../jmesh_pwm.h"
#include"stdio.h"


void jmesh_pwm_start(unsigned char pin_num,jmesh_pwm_channel_t channel, unsigned short high_ms, unsigned short low_ms)
{
    printf("start pwm channel %d,high %d ms low %d ms\n",channel,high_ms,low_ms);
}
void jmesh_pwm_stop(jmesh_pwm_channel_t channel){
    printf("stop pwm %d\n",channel);
}
#endif
