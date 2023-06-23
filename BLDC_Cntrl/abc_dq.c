/*
 * abc_dq.c
 *
 *  Created on: 25 maj 2023
 *      Author: student
 */

#include "abc_dq.h"

void abc_dq_calc(struct ABC_DQ_STRUCT *abc, float x_a,float x_b,float x_c, float fi){
    abc->x_a = x_a;
    abc->x_b = x_b;
    abc->x_c = x_c;
    abc->fi = fi;

    abc->y_d = a*(abc->x_a*cos(fi) + abc->x_b*cos(fi-b) + abc->x_c*cos(fi+b));
    abc->y_q = a*(abc->x_a*(-sin(fi)) + abc->x_b*(-sin(fi-b)) + abc->x_c*(-sin(fi+b)));
}
