/*
 * modulacja.c
 *
 *  Created on: 22 maj 2023
 *      Author: student
 */

#include "modulator.h"

float find_max(float a,float b,float c){
    float max;
    if(a>=b && a>=c){
        max=a;
    }
    if(b>=a && b>=c){
            max=b;
        }
    if(c>=a && c>=b){
            max=c;
        }
    return max;
}

float find_min(float a,float b,float c){
    float min;
    if(a<=b && a<=c){
            min=a;
        }
    if(b<=a && b<=c){
                min=b;
            }
    if(c<=a && c<=b){
                min=c;
            }
    return min;

}

void pwm_calc(struct MODULATOR_PWM_STRUCT *pwm, float u_a,float u_b,float u_c){
    pwm->u_a = u_a;
    pwm->u_b = u_b;
    pwm->u_c = u_c;

    pwm->y_a = -0.5 * ( find_max(pwm->u_a, pwm->u_b, pwm->u_c) + find_min(pwm->u_a, pwm->u_b, pwm->u_c) ) + pwm->u_a;
    pwm->y_b = -0.5 * ( find_max(pwm->u_a, pwm->u_b, pwm->u_c) + find_min(pwm->u_a, pwm->u_b, pwm->u_c) ) + pwm->u_b;
    pwm->y_c = -0.5 * ( find_max(pwm->u_a, pwm->u_b, pwm->u_c) + find_min(pwm->u_a, pwm->u_b, pwm->u_c) ) + pwm->u_c;

}

