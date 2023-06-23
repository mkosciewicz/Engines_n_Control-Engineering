/*
 * regulator_PI.c
 *
 *  Created on: June 5, 2023
 *      Author: student
 */

#include "regulator_PI.h"

void IntegratorInit(struct PI_STRUCT *controller, float gain, float samplingTime, float integralGain, float maxLimit, float minLimit, float feedbackGain)
{
    controller->state = 0;
    controller->output = 0;
    controller->samplingTime = samplingTime;
    controller->gain = gain;
    controller->feedbackGain = feedbackGain;
    controller->integralGain = integralGain;
    controller->maxLimit = maxLimit;
    controller->minLimit = minLimit;

    controller->previousOutput = 0;
    controller->integratorSum = 0;
    controller->previousIntegratorSum = 0;
    controller->proportionalValue = 0;
    controller->adjustedProportionalValue = 0;
    controller->controllerOutput = 0;
    controller->limitedOutput = 0;
    controller->integratorInput = 0;
    controller->previousIntegratorInput = 0;
}

void IntegratorCalc(struct PI_STRUCT *controller, float input)
{
    controller->state = input;

    // Proportional part
    controller->proportionalValue = controller->state * controller->gain;
    controller->adjustedProportionalValue = controller->proportionalValue - (controller->feedbackGain * controller->output);

    // Integral part
    controller->integratorInput = controller->adjustedProportionalValue * controller->integralGain;
    controller->integratorSum = (controller->samplingTime * controller->integratorInput + controller->samplingTime * controller->previousIntegratorInput) / 2 + controller->previousIntegratorSum;

    controller->previousIntegratorInput = controller->integratorInput;
    controller->previousIntegratorSum = controller->integratorSum;

    // Combine proportional and integral parts
    controller->controllerOutput = controller->proportionalValue + controller->integratorSum;

    // Limit output value
    if(controller->controllerOutput > controller->maxLimit){
        controller->limitedOutput = controller->maxLimit;
    }
    else if(controller->controllerOutput < controller->minLimit){
        controller->limitedOutput = controller->minLimit;
    }
    else{
        controller->limitedOutput = controller->controllerOutput;
    }

    // Calculate the difference between the output and its limited value
    controller->output = controller->controllerOutput - controller->limitedOutput;
}
