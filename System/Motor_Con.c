/*
 * Motor_Con.c
 *
 *  Created on: 2023��7��18��
 *      Author: whb
 */
#include "Motor_Con.h"
#include "Sevor.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>

void Control_Mode1(PID_Controler *PID1,PID_Controler *PID2,int16_t err_x,int16_t err_y)
{
    /*PID1���ڿ��Ƶ��µĶ��������ˮƽ������Ѱ��Ŀ�ꡣPID2���ڿ����ϱߵĶ����������ֱ������Ѱ��Ŀ��*/
    //������
    PID1->err[2]=PID1->err[1];
    PID1->err[1]=PID1->err[0];
    PID1->err[0]=err_x;
    PID2->err[2]=PID2->err[1];
    PID2->err[1]=PID2->err[0];
    PID2->err[0]=err_y;
    //����PID���ֵ
    PID1->Output += PID1->KP*PID1->err[0]+PID1->KD*(PID1->err[0]-PID1->err[1]) + PID1->Basic_Output;
    PID2->Output += PID2->KP*PID2->err[0]+PID2->KD*(PID2->err[0]-PID2->err[1]) + PID2->Basic_Output;
    //��PID_Output�޷�
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
    //���ƶ��
    Set_PWM_Value_Angle(PWM0_BASE,PWM_OUT_0,PWM_GEN_0,PID1->Output);
    Set_PWM_Value_Angle(PWM0_BASE,PWM_OUT_1,PWM_GEN_0,PID2->Output);
}

void Control_Mode2(void)
{

}
