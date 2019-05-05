#ifndef __MOTOR_H
#define __MOTOR_H

#include <math.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "setup.h"

void drive_break(void);
void drive_off(void);
uint32_t pwm_is_saturated(void);
int32_t power_pwm_saturation(int32_t left, int32_t right);
bool power_is_saturated(float power);
float power_limit(float power);
void power_left(int32_t power);
void power_right(int32_t power);
void reset_pwm_is_saturated(void);

#endif /* __MOTOR_H */
