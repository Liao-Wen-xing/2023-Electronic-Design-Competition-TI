/*
 * Motor_Con.c
 *
 *  Created on: 2023Äê7ÔÂ18ÈÕ
 *      Author: whb
 */
#include "Motor_Con.h"
void Control_Mode1(PID_Controler *PID,int16_t err)
{

    PID->err[2]=PID->err[1];
    PID->err[1]=PID->err[0];
    PID->err[0]=err;

    PID->Output=PID->KP*PID->err[0]+PID->KD*(PID->err[0]-PID->err[1]);


}

void Control_Mode2(void)
{

}



