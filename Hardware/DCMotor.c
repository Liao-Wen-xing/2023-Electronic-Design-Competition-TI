#include <ti/devices/msp432e4/driverlib/driverlib.h>


//初始化Gen1下的两个PWM通道，PF2，PF3
//注意设置的PWM控制器时钟频率是否和其他的冲突******!!!!!!!!!!!!!
void PWM2_3_Init()
{
    /* The PWM peripheral must be enabled for use. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);  //使能PWM0时钟，为什么只开一个时钟？
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));
   // MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //使能PWM0时钟，为什么只开一个时钟？
   // while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)));

    /* Set the PWM clock to the system clock. */
    //MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_1);  //选择PWM时钟源，系统时钟不分频，16MHz


    /* Enable the clock to the GPIO Port F for PWM pins */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    MAP_GPIOPinConfigure(GPIO_PF2_M0PWM2);
    MAP_GPIOPinConfigure(GPIO_PF3_M0PWM3);
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_2 | GPIO_PIN_3));

    /* 配置PWM0为向上/向下计数，不进行同步。 */
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN |
                            PWM_GEN_MODE_NO_SYNC);  //配置 PWM 发生器

    /* 设置PWM周期为250Hz。计算合适的参数N=(1/ f) * SysClk.
               N = (1 / f)其中N是函数参数，
               f为所需频率，SysClk为系统时钟频率。在这种情况下，
               你得到:(1 / 250Hz) * 16MHz = 64000周期。请注意,
               您可以设置的 最大周期是2^16 - 1。*/
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 64000);

/*
     //设置25%的占空比，PWM0
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                         MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);

    //设置75%的占空比，PWM1
     MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                             MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);
*/
    MAP_IntMasterEnable();  //功能不明

    /* This timer is in up-down mode.  Interrupts will occur when the
     * counter for this PWM counts to the load value (64000), when the
     * counter counts up to 64000/4 (PWM A Up), counts down to 64000/4
     * (PWM A Down), and counts to 0. */
    MAP_PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_1,
                    PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |
                    PWM_INT_CNT_AU | PWM_INT_CNT_AD);

    /* Enable the PWM0 Bit 0 (PF0) and Bit 1 (PF1) output signals. */
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT  | PWM_OUT_3_BIT , true);

    /* Enables the counter for a PWM generator block. */
    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}

/*
 * 控制正反转引脚的初始化
 * L0 L1 ------
 * L2 L3-----
 * */
void Out_GPIO_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
        while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL));
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_2);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_3);
}
/*
@参数：u32Base：PWM基址，PWM0_BASE
      ui32PWNOUT：PWM通道：PWM_OUT_x,  x  属于 0-7
      ui32Gen：PWM发生器，一个发生器对应两个PWM通道，PWM_GEN_x, x为0-3
      Value：占空比，值为0-1；
@简介：设置指定通道的占空比
*/
void
Set_PWM_Value(uint32_t u32Base,uint32_t ui32PWNOUT,uint32_t ui32Gen,float Value)
{
    MAP_PWMPulseWidthSet(u32Base, ui32PWNOUT,
                             MAP_PWMGenPeriodGet(u32Base, ui32Gen)*Value);

}
//控制一个电机正转，PL0，PL1
void corotation_1(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, 0);
}
//控制一个电机反转 PL0，PL1
void reverse_1(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_PIN_1);
}
//控制一个电机正转，PL2 PL3
void corotation_2(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, 0);
}

//控制一个电机反转 PL2 PL3
void reverse_2(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, GPIO_PIN_3);
}
