/*
 * filtr.c
 *
 *  Created on: 1 cze 2023
 *      Author: student
 */
#include "filtr.h"

void Tustin_calc(struct Dyskretyzacja *w, float u, float Ts, float x_Tau){
    w->Ts=Ts;
    w->u=u;
    float Tau = x_Tau*w->Ts;

    if(w->u<-PI){
        w->u += 2*PI;
    }
    if(w->u>PI){
        w->u -= 2*PI;
    }

    w->y = w->u*w->Ts/(2*Tau + w->Ts) + w->u_prev*w->Ts/(2*Tau + w->Ts) + w->y_prev*(2*Tau - w->Ts)/(2*Tau + w->Ts);

    w->y_prev = w->y;
    w->u_prev = w->u;
}
