#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "ADC.h"
#include "OLED.h"
#include "DCMotor.h"
#include "Motor_Con.h"
#include "Key.h"
#include "Timer.h"
#include "Encoder.h"
#include "Sevor.h"
extern uint16_t srcBuffer[4];   //ADC
uint32_t systemClock;
uint32_t g_ui32SysClock;
char Key_Num=0;
uint16_t AD_left,AD_right;
int16_t err;
uint16_t speed1,speed2;
float xianfu(float x);

PID_Controler Gra_PID=
{
0.02,
0,
0,
0,0,0,
0
};

//F2    right    L2L3
//F3    left     L0L1
int main(void)
{

    systemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          120000000);
    g_ui32SysClock=systemClock;
    OLED_Init();

    PWM0_1_Init();
    Key_Init();
    PWM2_3_Init();
    Out_GPIO_Init();
    corotation_1();
    corotation_2();
    TIM01_Init();
    ADC_Configuration();
    Encode_Init();

    Set_PWM_Value_Angle(PWM0_BASE,PWM_OUT_1,PWM_GEN_0,135);
    /* Wait loop */
    while(1)
    {
        /*uint8_t Key_temp;
        Key_temp = Key_GetNum();
        if(Key_temp)
        {
            Key_Num = Key_temp;
        }*/
        OLED_ShowChar(0,0,'2');
    }
}

//放控制代码
void
TIMER0A_IRQHandler(void)
{
    //Clear the timer interrupt.
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //Update the interrupt status.
    MAP_IntMasterDisable();
    if (Key_Num==1)
    {
            Control_Mode1(&Gra_PID,err);
            Set_PWM_Value(PWM0_BASE,PWM_OUT_2,PWM_GEN_1,xianfu(0.5-Gra_PID.Output));
            Set_PWM_Value(PWM0_BASE,PWM_OUT_3,PWM_GEN_1,xianfu(0.5+Gra_PID.Output));
    }
    else if (Key_Num==2)
    {

    }
    MAP_IntMasterEnable();
}
float xianfu(float x)
{
    if(x>0.8)
        x=0.8;
    else if (x<0)
        x=0;
    else
        x=x;
    return x;
}
//编码器测速，闸门时间，定时测一次速度
void
TIMER1A_IRQHandler(void)
{


    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    MAP_IntMasterDisable();
    speed1=Get_Speed(TIMER_A);
    speed2=Get_Speed(TIMER_B);
    MAP_IntMasterEnable();
}
void
UART6_IRQHandler(void)
{
    uint32_t ui32Status;
    static uint8_t Rx_State=0;
    static uint8_t Data_Index=0;

    ui32Status = MAP_UARTIntStatus(UART6_BASE, true);
    MAP_UARTIntClear(UART6_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
    while(MAP_UARTCharsAvail(UART6_BASE))
    {
        // Read the next character from the UART and write it back to the UART.
        uint32_t temp;
        temp=MAP_UARTCharGetNonBlocking(UART6_BASE);
        //MAP_UARTCharGetNonBlocking()  读取指定端口FIFO中的字符  强制转化为uint32_t
        if(Rx_State==0&&temp==0xAD)
        {
            Rx_State=1;
        }
        else if(Rx_State==1&&temp==0xCC)
        {
            Rx_State=2;
        }
        else if(Rx_State==2)
        {
            if(temp==0xFF)
            {
                Rx_State=3;
                Data_Index=0;
            }
            else
            {
                //读取有效数据
                Data_Index++;
            }
        }
        else if(Rx_State==3)
        {
             Rx_State=0;
             //处理数据
        }
        else
        {
            Data_Index=0;
            Rx_State=0;
        }

    }
}
