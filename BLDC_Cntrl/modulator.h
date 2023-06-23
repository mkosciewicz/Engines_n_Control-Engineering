/*
 * modulacja.h
 *
 *  Created on: 22 maj 2023
 *      Author: student
 */

#ifndef MODULATOR_H_
#define MODULATOR_H_

struct MODULATOR_PWM_STRUCT{
    float u_a;
    float u_b;
    float u_c;
    float y_a;
    float y_b;
    float y_c;
};

float find_max(float a,float b,float c);
float find_min(float a,float b,float c);
void pwm_calc(struct MODULATOR_PWM_STRUCT *pwm, float u_a,float u_b,float u_c);

#endif /* MODULACJA_H_ */
