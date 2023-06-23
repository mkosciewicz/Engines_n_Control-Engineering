/*
 * dq_abc.h
 *
 *  Created on: 25 maj 2023
 *      Author: student
 */

#ifndef DQ_ABC_H_
#define DQ_ABC_H_

#include <math.h>
#define pi 3.141593
#define b (2.0/3.0)*pi
#define a (2.0/3.0)

struct DQ_ABC_STRUCT{
    float x_d;
    float x_q;
    float fi;
    float y_a;
    float y_b;
    float y_c;
};

void dq_abc_calc(struct DQ_ABC_STRUCT *dq, float x_d,float x_q,float fi);

#endif /* DQ_ABC_H_ */
