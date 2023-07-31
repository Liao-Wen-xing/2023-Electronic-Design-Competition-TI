#include <ti/devices/msp432e4/driverlib/driverlib.h>

//初始化Gen0下的两个PWM通道，PF0，PF1  但是PF0在板卡上找不到。。。
//注意设置的PWM控制器时钟频率是否和其他的冲突******!!!!!!!!!!!!!
void PWM0_1_Init()
{
    /* The PWM peripheral must be enabled for use. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);  //使能PWM0时钟，为什么只开一个时钟？
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));

    /* Set the PWM clock to the system clock. */
    MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_64);  //选择PWM0时钟源，系统时钟64分频,1.875MMHz
    //此函数作用于整个PWM控制器；****************************************************

    /* Enable the clock to the GPIO Port F for PWM pins */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0);
    MAP_GPIOPinConfigure(GPIO_PF1_M0PWM1);
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    /* 配置PWM0为向上/向下计数，不进行同步。 */
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
                            PWM_GEN_MODE_NO_SYNC);  //配置 PWM 发生器

    /* 设置PWM周期为50Hz。计算合适的参数N=(1/ f) * SysClk.
               N = (1 / f)其中N是函数参数，
               f为所需频率，SysClk为PWM0_BASE系统时钟频率1.875M。在这种情况下，
               你得到:(1 / 50Hz) * 1.875MHz = 37500周期。请注意,
               您可以设置的 最大周期是2^16 - 1。*/
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 37500);

/*
     //设置25%的占空比，PWM0
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                         MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);

    //设置75%的占空比，PWM1
     MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                             MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
*/
    MAP_IntMasterEnable();  //功能不明

    /* This timer is in up-down mode.  Interrupts will occur when the
     * counter for this PWM counts to the load value (64000), when the
     * counter counts up to 64000/4 (PWM A Up), counts down to 64000/4
     * (PWM A Down), and counts to 0. */
    MAP_PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0,
                    PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |
                    PWM_INT_CNT_AU | PWM_INT_CNT_AD);

    /* Enable the PWM0 Bit 0 (PF0) and Bit 1 (PF1) output signals. */
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);

    /* Enables the counter for a PWM generator block. */
    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}

/*
@参数：u32Base：PWM基址，PWM0_BASE
      ui32PWNOUT：PWM通道：PWM_OUT_x,  x  属于 0-7
      ui32Gen：PWM发生器，一个发生器对应两个PWM通道，PWM_GEN_x, x为0-3
      Angle：角度，值为0-270；
@简介：设置指定通道的占空比
        对于50Hz,脉宽为0.5ms--2.5ms的舵机来说，占空比应当控制在0.025-0.125之间
        但此函数直接将角度封装，适用于270度舵机，Angle对应舵机的角度
*/
void
Set_PWM_Value_Angle(uint32_t u32Base,uint32_t ui32PWNOUT,uint32_t ui32Gen,float Angle)
{
    float Value=Angle*0.1/270+0.025;
    MAP_PWMPulseWidthSet(u32Base, ui32PWNOUT,
                             MAP_PWMGenPeriodGet(u32Base, ui32Gen)*Value);

}


