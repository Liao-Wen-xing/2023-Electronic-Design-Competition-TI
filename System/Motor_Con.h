/*
 * Motor_Con.h
 *
 *  Created on: 2023Äê7ÔÂ18ÈÕ
 *      Author: whb
 */

#ifndef SYSTEM_MOTOR_CON_H_
#define SYSTEM_MOTOR_CON_H_
#include <stdint.h>
#include <stdbool.h>
typedef struct
{
    float KP;
    float KI;
    float KD;
    int16_t err[3];
    float Output;
} PID_Controler;

void Control_Mode1(PID_Controler *PID,int16_t Angle);
void Control_Mode2(void);

#endif /* SYSTEM_MOTOR_CON_H_ */
