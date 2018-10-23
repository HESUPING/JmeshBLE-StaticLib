#include "motor.h"
#include "pshare.h"
#include "pwm.h"
#include "log.h"
#include "plf.h"
#include "clk_gate.h"
void motor_init(void)
{
    sysc_per_clkg1_set(PER_CLKG_SET_PWM_DIV | PER_CLKG_SET_PWM0 | PER_CLKG_SET_PWM1);       // open pwm 
    pshare_funcio_set(FUNC_IO_4, IO_PWM_0, ENABLE);
    pshare_funcio_set(FUNC_IO_5, IO_PWM_1, ENABLE);


/*/////////////// for real chip on gokit ////////////////////    
    pshare_funcio_set(FUNC_IO_0, IO_PWM_0, ENABLE);
    pshare_funcio_set(FUNC_IO_5, IO_PWM_1, ENABLE);
*////////////////////////////////////////////////////////////////////
}

void motor_deinit(void)
{
    sysc_per_clkg1_set(PER_CLKG_CLR_PWM0 | PER_CLKG_CLR_PWM1);       // open pwm 
    sysc_per_clkg1_set(PER_CLKG_CLR_PWM_DIV);                       // depends on whether there are other pwm devices.
}

void motor_set(uint8_t direction,uint16_t pwm)
{
    pwm_Disable(pwm_Chn0);
    pwm_Disable(pwm_Chn1);
    LOG(LOG_LVL_INFO,"dir = %d, speed = %d\n",direction,pwm);
    if(pwm != 0)
    {
        if(direction == CLOCKWISE)
        {
            pwm_SetHighPeriod(pwm_Chn0, pwm);
            pwm_SetLowPeriod(pwm_Chn0, 0xFFFF-pwm);
            pwm_Enable(pwm_Chn0);
        }
        else if(direction == COUNTER_CLOCKWISE)
        {
            pwm_SetHighPeriod(pwm_Chn1, pwm);
            pwm_SetLowPeriod(pwm_Chn1, 0xFFFF-pwm);
            pwm_Enable(pwm_Chn1);
        }
        else
        {

        }
    }

}



