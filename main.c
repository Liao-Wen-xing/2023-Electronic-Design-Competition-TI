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
#include "_UART.h"
uint32_t systemClock;
uint32_t g_ui32SysClock;

//extern uint16_t srcBuffer[4];   //ADC的值
//char Key_Num=0;
//uint16_t AD_left,AD_right;
int16_t some=0;
uint16_t speed1,speed2;
uint8_t Data_xy_err[5];    //用于串口6接收的摄像头的小球离中心点的误差数据，第一个是x方向上，第二个是y方向上的

PID_Controler Servo_PID_x=
{
    0,          //KP
    0,          //KI
    0,          //KD
    0,0,0,      //err
    0,          //Basic_Output
    0,0         //Output_range_min和Output_range_max
};
PID_Controler Servo_PID_y=
{
    0,          //KP
    0,          //KI
    0,          //KD
    0,0,0,      //err
    0,          //Basic_Output
    0,0         //Output_range_min和Output_range_max
};

//F2    right    L2L3
//F3    left     L0L1
int main(void)
{

    systemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          120000000);
    g_ui32SysClock=systemClock;

    OLED_Init();        	//OLED初始化
    UART6_Init();           //UART6的初始化
    PWM0_1_Init();      	//舵机的PWM通道初始化
//    Key_Init();         	//按键初始化
//    PWM2_3_Init();      	//直流电机的PWM通道初始化
//    Out_GPIO_Init();    	//控制直流电机正反转引脚的初始化
//    corotation_1();     	//控制电机1正转
//    corotation_2();     	//控制电机2正转
    TIM01_Init();       	//定时器0和1的中断控制函数，定时器0用于放控制函数，定时器1用于编码器的测速的中断
//    ADC_Configuration();	//ADC0初始化
//    Encode_Init();          //编码器初始化

    /* Wait loop */
    while(1)
    {
//        uint8_t Key_temp;
//        Key_temp = Key_GetNum();
//        if(Key_temp)
//        {
//            Key_Num = Key_temp;
//        }
//        OLED_ShowChar(0,0,'1');
        OLED_ShowSignedNum(0,0,some,5);
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

    Control_Mode1(&Servo_PID_x,&Servo_PID_y,Data_xy_err[0],Data_xy_err[1]);
    some++;
//    if (Key_Num==1)
//    {
//
//    }
//    else if (Key_Num==2)
//    {
//
//    }

    //与中断相关
    MAP_IntMasterEnable();
}

//编码器测速，闸门时间，定时测一次速度
void
TIMER1A_IRQHandler(void)
{
    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    MAP_IntMasterDisable();

    speed1=Get_Speed(TIMER_A);
    speed2=Get_Speed(TIMER_B);

    //与中断相关
    MAP_IntMasterEnable();
}
//串口接收数据
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
                Data_xy_err[Data_Index]=temp;
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
