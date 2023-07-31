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

//extern uint16_t srcBuffer[4];   //ADC��ֵ
//char Key_Num=0;
//uint16_t AD_left,AD_right;
int16_t some=0;
uint16_t speed1,speed2;
uint8_t Data_xy_err[5];    //���ڴ���6���յ�����ͷ��С�������ĵ��������ݣ���һ����x�����ϣ��ڶ�����y�����ϵ�

PID_Controler Servo_PID_x=
{
    0,          //KP
    0,          //KI
    0,          //KD
    0,0,0,      //err
    0,          //Basic_Output
    0,0         //Output_range_min��Output_range_max
};
PID_Controler Servo_PID_y=
{
    0,          //KP
    0,          //KI
    0,          //KD
    0,0,0,      //err
    0,          //Basic_Output
    0,0         //Output_range_min��Output_range_max
};

//F2    right    L2L3
//F3    left     L0L1
int main(void)
{

    systemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          120000000);
    g_ui32SysClock=systemClock;

    OLED_Init();        	//OLED��ʼ��
    UART6_Init();           //UART6�ĳ�ʼ��
    PWM0_1_Init();      	//�����PWMͨ����ʼ��
//    Key_Init();         	//������ʼ��
//    PWM2_3_Init();      	//ֱ�������PWMͨ����ʼ��
//    Out_GPIO_Init();    	//����ֱ���������ת���ŵĳ�ʼ��
//    corotation_1();     	//���Ƶ��1��ת
//    corotation_2();     	//���Ƶ��2��ת
    TIM01_Init();       	//��ʱ��0��1���жϿ��ƺ�������ʱ��0���ڷſ��ƺ�������ʱ��1���ڱ������Ĳ��ٵ��ж�
//    ADC_Configuration();	//ADC0��ʼ��
//    Encode_Init();          //��������ʼ��

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

//�ſ��ƴ���
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

    //���ж����
    MAP_IntMasterEnable();
}

//���������٣�բ��ʱ�䣬��ʱ��һ���ٶ�
void
TIMER1A_IRQHandler(void)
{
    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    MAP_IntMasterDisable();

    speed1=Get_Speed(TIMER_A);
    speed2=Get_Speed(TIMER_B);

    //���ж����
    MAP_IntMasterEnable();
}
//���ڽ�������
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
        //MAP_UARTCharGetNonBlocking()  ��ȡָ���˿�FIFO�е��ַ�  ǿ��ת��Ϊuint32_t
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
                //��ȡ��Ч����
                Data_xy_err[Data_Index]=temp;
                Data_Index++;
            }
        }
        else if(Rx_State==3)
        {
             Rx_State=0;
             //��������
        }
        else
        {
            Data_Index=0;
            Rx_State=0;
        }

    }
}
