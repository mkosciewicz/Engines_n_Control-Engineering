/*
 * abc_dq.h
 *
 *  Created on: 25 maj 2023
 *      Author: student
 */

#ifndef ABC_DQ_H_
#define ABC_DQ_H_

#include <math.h>
#define pi 3.141593
#define b (2.0/3.0)*pi
#define a (2.0/3.0)

struct ABC_DQ_STRUCT{
    float y_d;
    float y_q;
    float fi;
    float x_a;
    float x_b;
    float x_c;
};

void abc_dq_calc(struct ABC_DQ_STRUCT *abc, float x_a,float x_b,float x_c, float fi);

#endif /* ABC_DQ_H_ */
