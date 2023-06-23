/*
 * modulator2.h
 *
 *  Created on: 29 maj 2023
 *      Author: student
 */

#ifndef MODULATOR2_H_
#define MODULATOR2_H_

struct Modulacja{
    // input
    float sin_a;
    float sin_b;
    float sin_c;
    // output
    float y_a;
    float y_b;
    float y_c;
};

struct Comparison{ // oddzielna struktura do porownywania, zeby mozna bylo wywolywac funkcje w funkcji :D
    float min;
    float max;
};

void Min_Max(struct Comparison *w2, float sin_a, float sin_b, float sin_c);
void Sum(struct Modulacja *w, float sin_a, float sin_b, float sin_c);


#endif /* MODULATOR2_H_ */
