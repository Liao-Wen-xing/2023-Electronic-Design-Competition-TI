/*
 * Motor_Con.c
 *
 *  Created on: 2023年7月18日
 *      Author: whb
 */
#include "Motor_Con.h"
#include "Sevor.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>

void Control_Mode1(PID_Controler *PID1,PID_Controler *PID2,int16_t err_x,int16_t err_y)
{
    /*PID1用于控制底下的舵机，即在水平方向上寻找目标。PID2用于控制上边的舵机，即在竖直方向上寻找目标*/
    //误差迭代
    PID1->err[2]=PID1->err[1];
    PID1->err[1]=PID1->err[0];
    PID1->err[0]=err_x;
    PID2->err[2]=PID2->err[1];
    PID2->err[1]=PID2->err[0];
    PID2->err[0]=err_y;
    //计算PID输出值
    PID1->Output += PID1->KP*PID1->err[0]+PID1->KD*(PID1->err[0]-PID1->err[1]) + PID1->Basic_Output;
    PID2->Output += PID2->KP*PID2->err[0]+PID2->KD*(PID2->err[0]-PID2->err[1]) + PID2->Basic_Output;
    //对PID_Output限幅
    if(PID1->Output > PID1->Output_range_max)
    {
        PID1->Output = PID1->Output_range_max;
    }
    else if(PID1->Output < PID1->Output_range_min)
    {
        PID1->Output = PID1->Output_range_max;
    }
    if(PID2->Output > PID2->Output_range_max)
    {
        PID2->Output = PID2->Output_range_max;
    }
    else if(PID2->Output < PID2->Output_range_min)
    {
        PID2->Output = PID2->Output_range_max;
    }
    //控制舵机
    Set_PWM_Value_Angle(PWM0_BASE,PWM_OUT_0,PWM_GEN_0,PID1->Output);
    Set_PWM_Value_Angle(PWM0_BASE,PWM_OUT_1,PWM_GEN_0,PID2->Output);
}

void Control_Mode2(void)
{

}
