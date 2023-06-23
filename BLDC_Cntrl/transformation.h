/*
 * transformation.h
 *
 *  Created on: 18 maj 2023
 *      Author: student
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

struct TransformationData{
    float input;
    float output;
    float a;
    float b;
};

void initTransformation(struct TransformationData *Data, float a, float b);
void doTransformation(struct TransformationData *Data);

#endif /* TRANSFORMATION_H_ */
