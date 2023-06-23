/*
 * modulator2.c
 *
 * Created on: May 29, 2023
 * Author: student
 */

#include "modulator2.h"

// Initializing a structure to perform comparisons
struct Comparison min_max_1;

/*
 * Function to find the minimum and maximum values among three floats.
 * The results are stored in the struct pointed to by w2.
 */
void Min_Max(struct Comparison *w2, float sin_a, float sin_b, float sin_c) {

    // Finding the minimum value
    w2->min = sin_a;  // assign the first value to min and compare with others
    if (sin_b < w2->min) {
        w2->min = sin_b;
    }
    if (sin_c < w2->min) {
        w2->min = sin_c;
    }

    // Finding the maximum value
    w2->max = sin_a;  // assign the first value to max and compare with others
    if (sin_b > w2->max) {
        w2->max = sin_b;
    }
    if (sin_c > w2->max) {
        w2->max = sin_c;
    }
}

/*
 * Function to sum the sine values and perform modulation.
 * The results are stored in the struct pointed to by w.
 */
void Sum(struct Modulacja *w, float sin_a, float sin_b, float sin_c) {
    // Store sine values in the struct
    w->sin_a = sin_a;
    w->sin_b = sin_b;
    w->sin_c = sin_c;

    // Call the comparison function
    Min_Max(&min_max_1, sin_a, sin_b, sin_c);

    // Perform modulation
    float modulation_factor = 0.5 * (min_max_1.min + min_max_1.max);
    w->y_a = w->sin_a - modulation_factor;
    w->y_b = w->sin_b - modulation_factor;
    w->y_c = w->sin_c - modulation_factor;
}
