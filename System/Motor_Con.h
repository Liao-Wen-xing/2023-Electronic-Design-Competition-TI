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
    float Basic_Output;
    float Output;
    float Output_range_min;
    float Output_range_max;
} PID_Controler;

void Control_Mode1(PID_Controler *PID1,PID_Controler *PID2,int16_t err_x,int16_t err_y);
void Control_Mode2(void);

#endif /* SYSTEM_MOTOR_CON_H_ */
