#include"../jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"../../../../trunk/plf/peripheral/app_pwm/app_pwm.h"
#include"../../../../trunk/plf/bx_debug/bx_dbg.h"
#include"../jmesh_pwm.h"
#include"stdio.h"
static app_pwm_inst_t pwm_inst[5] = {PWM_INSTANCE(0),PWM_INSTANCE(1),PWM_INSTANCE(2),
																			PWM_INSTANCE(3),PWM_INSTANCE(4)};
void jmesh_pwm_start(unsigned char pin_num,jmesh_pwm_channel_t channel, unsigned short high_ms, unsigned short low_ms)
{
		if(channel >4)	BX_ASSERT(0);	
    pwm_inst[channel].param.pin_num=pin_num;
    pwm_inst[channel].param.high_time=high_ms;
    pwm_inst[channel].param.low_time=low_ms;
    app_pwm_init(&pwm_inst[channel].inst);
    app_pwm_start(&pwm_inst[channel].inst);
}
void jmesh_pwm_stop(jmesh_pwm_channel_t channel){
	
		if(channel >4)	BX_ASSERT(0);							
    app_pwm_stop(&pwm_inst[channel].inst);
}
#endif
