#include "ti/devices/msp432e4/driverlib/driverlib.h"
uint16_t Inter_Flag;
extern uint32_t g_ui32SysClock;
//��ʱ��0�Ͷ�ʱ��1�Ķ�ʱ�жϣ���ΪTimerA��ȫ��
void TIM01_Init()
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    MAP_IntMasterEnable();  //ʹ���жϣ����ܲ���


   //��������32λ���ڶ�ʱ��
   MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);  //�ڶ�������Ϊ��Ǽ��������ã����
   MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);

   MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock/100);    //�Զ���װ�Ĵ�����ֵ��������ʱ��Ƶ��Ϊ100HZ��
   //g_ui32SysClock����ϵͳʱ�ӵ�ֵ��32λ��g_ui32SysClockΪ120M��
   MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, g_ui32SysClock / 10);  //2Hz

   TimerPrescaleSet(TIMER0_BASE,TIMER_A,0);     //Ԥ��Ƶ��,�����þ�Ϊ0

   // ���ü�ʱ����ʱ���жϡ�
   MAP_IntEnable(INT_TIMER0A);
   MAP_IntEnable(INT_TIMER1A);
   MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
   MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);


   // Enable the timers.
   MAP_TimerEnable(TIMER0_BASE, TIMER_A);
   MAP_TimerEnable(TIMER1_BASE, TIMER_A);

}



