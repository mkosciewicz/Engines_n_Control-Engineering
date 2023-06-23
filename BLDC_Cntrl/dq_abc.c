/*
 * dq_abc.c
 *
 *  Created on: 25 maj 2023
 *      Author: student
 */

#include "dq_abc.h"

void dq_abc_calc(struct DQ_ABC_STRUCT *dq, float x_d,float x_q,float fi){
    dq->x_d = x_d;
    dq->x_q = x_q;
    dq->fi = fi;

    dq->y_a = (dq->x_d*cos(fi) + dq->x_q*(-sin(fi)));
    dq->y_b = (dq->x_d*cos(fi-b) + dq->x_q*(-sin(fi-b)));
    dq->y_c = (dq->x_d*cos(fi+b) + dq->x_q*(-sin(fi+b)));
}
