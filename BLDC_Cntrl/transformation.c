/*
 * transformation.c
 *
 *  Created on: 18 maj 2023
 *      Author: student
 */

#include "transformation.h"

void initTransformation(struct TransformationData *Data, float a, float b){
    Data->a=a;
    Data->b=b;
    Data->input=0;
    Data->output=0;
}

void doTransformation(struct TransformationData *Data){
    Data->output = Data->input * Data->a + Data->b;
}
