#include "ti/devices/msp432e4/driverlib/driverlib.h"
uint16_t Inter_Flag;
extern uint32_t g_ui32SysClock;
//定时器0和定时器1的定时中断，都为TimerA，全宽，
void TIM01_Init()
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    MAP_IntMasterEnable();  //使能中断，功能不明


   //配置两个32位定期定时器
   MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);  //第二个参数为半角计数的配置，半角
   MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);

   MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock/100);    //自动重装寄存器的值，整个定时器频率为100HZ，
   //g_ui32SysClock就是系统时钟的值，32位，g_ui32SysClock为120M，
   MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, g_ui32SysClock / 10);  //2Hz

   TimerPrescaleSet(TIMER0_BASE,TIMER_A,0);     //预分频器,不设置就为0

   // 设置计时器超时的中断。
   MAP_IntEnable(INT_TIMER0A);
   MAP_IntEnable(INT_TIMER1A);
   MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
   MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);


   // Enable the timers.
   MAP_TimerEnable(TIMER0_BASE, TIMER_A);
   MAP_TimerEnable(TIMER1_BASE, TIMER_A);

}



