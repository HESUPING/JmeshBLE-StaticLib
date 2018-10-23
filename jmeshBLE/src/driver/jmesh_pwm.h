#ifndef JMESH_PWM_H
#define JMESH_PWM_H


typedef enum {
    JMESH_PWM_CHANNEL_0,
    JMESH_PWM_CHANNEL_1,
    JMESH_PWM_CHANNEL_2,
    JMESH_PWM_CHANNEL_3,
    JMESH_PWM_CHANNEL_4,
}jmesh_pwm_channel_t;


extern void jmesh_pwm_start(unsigned char pin_num,jmesh_pwm_channel_t channel, unsigned short high_ms, unsigned short low_ms);
extern void jmesh_pwm_stop(jmesh_pwm_channel_t channel);



#endif // JMESH_PWM_H
