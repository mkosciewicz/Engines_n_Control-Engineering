/*
 * filtr.h
 *
 *  Created on: 1 cze 2023
 *      Author: student
 */

#ifndef FILTR_H_
#define FILTR_H_

#define PI 3.14159265359

struct Dyskretyzacja{ //definicja struktury PI
    float u;
    float u_prev;
    float y;
    float y_prev;   // poprzednia probka wyjscia
    float Ts; // okres probkowania
};

void Tustin_calc(struct Dyskretyzacja *w, float u, float Ts, float x_Tau);

#endif /* FILTR_H_ */
