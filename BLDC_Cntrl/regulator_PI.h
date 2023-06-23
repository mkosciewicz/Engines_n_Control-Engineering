/*
 * regulator_PI.h
 *
 *  Created on: 5 cze 2023
 *      Author: student
 */

#ifndef REGULATOR_PI_H_
#define REGULATOR_PI_H_

struct PI_STRUCT
{
    float X;
    float Y;
    float Y_prev;
    float Ts;
    float Kr;
    float Ka;
    float Ki;
    float max;
    float min;
    float cal;
    float cal_prev;
    float prop;
    float prop_1;
    float prop_cal;
    float y_limit;  //wyjscie
    float cal_input;
    float cal_input_prev;

};

void IntegratorInit(struct PI_STRUCT *w, float Kr, float Ts, float Ti, float max, float min, float Ka);
void IntegratorCalc(struct PI_STRUCT *w, float X);

#endif /* REGULATOR_PI_H_ */
