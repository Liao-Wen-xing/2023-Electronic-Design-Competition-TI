#include <ti/devices/msp432e4/driverlib/driverlib.h>


//��ʼ��Gen1�µ�����PWMͨ����PF2��PF3
//ע�����õ�PWM������ʱ��Ƶ���Ƿ�������ĳ�ͻ******!!!!!!!!!!!!!
void PWM2_3_Init()
{
    /* The PWM peripheral must be enabled for use. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);  //ʹ��PWM0ʱ�ӣ�Ϊʲôֻ��һ��ʱ�ӣ�
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));
   // MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //ʹ��PWM0ʱ�ӣ�Ϊʲôֻ��һ��ʱ�ӣ�
   // while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)));

    /* Set the PWM clock to the system clock. */
    //MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_1);  //ѡ��PWMʱ��Դ��ϵͳʱ�Ӳ���Ƶ��16MHz


    /* Enable the clock to the GPIO Port F for PWM pins */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    MAP_GPIOPinConfigure(GPIO_PF2_M0PWM2);
    MAP_GPIOPinConfigure(GPIO_PF3_M0PWM3);
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_2 | GPIO_PIN_3));

    /* ����PWM0Ϊ����/���¼�����������ͬ���� */
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN |
                            PWM_GEN_MODE_NO_SYNC);  //���� PWM ������

    /* ����PWM����Ϊ250Hz��������ʵĲ���N=(1/ f) * SysClk.
               N = (1 / f)����N�Ǻ���������
               fΪ����Ƶ�ʣ�SysClkΪϵͳʱ��Ƶ�ʡ�����������£�
               ��õ�:(1 / 250Hz) * 16MHz = 64000���ڡ���ע��,
               ���������õ� ���������2^16 - 1��*/
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 64000);

/*
     //����25%��ռ�ձȣ�PWM0
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                         MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);

    //����75%��ռ�ձȣ�PWM1
     MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                             MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);
*/
    MAP_IntMasterEnable();  //���ܲ���

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
 * ��������ת���ŵĳ�ʼ��
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
@������u32Base��PWM��ַ��PWM0_BASE
      ui32PWNOUT��PWMͨ����PWM_OUT_x,  x  ���� 0-7
      ui32Gen��PWM��������һ����������Ӧ����PWMͨ����PWM_GEN_x, xΪ0-3
      Value��ռ�ձȣ�ֵΪ0-1��
@��飺����ָ��ͨ����ռ�ձ�
*/
void
Set_PWM_Value(uint32_t u32Base,uint32_t ui32PWNOUT,uint32_t ui32Gen,float Value)
{
    MAP_PWMPulseWidthSet(u32Base, ui32PWNOUT,
                             MAP_PWMGenPeriodGet(u32Base, ui32Gen)*Value);

}
//����һ�������ת��PL0��PL1
void corotation_1(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, 0);
}
//����һ�������ת PL0��PL1
void reverse_1(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_PIN_1);
}
//����һ�������ת��PL2 PL3
void corotation_2(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, 0);
}

//����һ�������ת PL2 PL3
void reverse_2(void)
{
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, GPIO_PIN_3);
}
