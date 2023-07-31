/*
 * Encoder.c
 *
 *  Created on: 2023年7月29日
 *      Author: whb
 */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>

//定时器3，事件计数，上升沿，TimerA:PM2，TimerA:PM3
void Encode_Init(void)
{
    /* Enable the clock to the GPIO Port A and wait for it to be ready */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
    {
    }

    /* Configure the GPIO PA7 as Timer-3 CCP1 pin */
    MAP_GPIOPinConfigure(GPIO_PM3_T3CCP1);
    MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_3);

    MAP_GPIOPinConfigure(GPIO_PM2_T3CCP0);
    MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_2);


    /* Enable the Timer-3 in 16-bit Edge Count mode */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)))
    {
    }

    /* Configure the Timer-3B in Edge Count Mode. Load the internal counter to
     * count from 5 to 0, When the counter reaches 0, an interrupt is
     * generated */
    MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_COUNT_UP|TIMER_CFG_A_CAP_COUNT_UP );//定时器全宽半宽的配置
    //MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_COUNT);

    MAP_TimerControlEvent(TIMER3_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);//边沿捕获模式的配置
    MAP_TimerControlEvent(TIMER3_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);

    MAP_TimerLoadSet(TIMER3_BASE, TIMER_B, 65534);
    MAP_TimerLoadSet(TIMER3_BASE, TIMER_A, 65534);
    MAP_TimerEnable(TIMER3_BASE, TIMER_B);
    MAP_TimerEnable(TIMER3_BASE, TIMER_A);

}
uint32_t Get_Speed(uint32_t ui32Timer)
{
    uint32_t temp=0;
    temp=TimerValueGet(TIMER3_BASE,ui32Timer);
    (ui32Timer==TIMER_A)?(TIMER3->TAV=0x00):(TIMER3->TBV=0x00);
    return temp;
}


