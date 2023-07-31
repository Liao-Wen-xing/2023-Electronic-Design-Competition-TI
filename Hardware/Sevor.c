#include <ti/devices/msp432e4/driverlib/driverlib.h>

//��ʼ��Gen0�µ�����PWMͨ����PF0��PF1  ����PF0�ڰ忨���Ҳ���������
//ע�����õ�PWM������ʱ��Ƶ���Ƿ�������ĳ�ͻ******!!!!!!!!!!!!!
void PWM0_1_Init()
{
    /* The PWM peripheral must be enabled for use. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);  //ʹ��PWM0ʱ�ӣ�Ϊʲôֻ��һ��ʱ�ӣ�
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));

    /* Set the PWM clock to the system clock. */
    MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_64);  //ѡ��PWM0ʱ��Դ��ϵͳʱ��64��Ƶ,1.875MMHz
    //�˺�������������PWM��������****************************************************

    /* Enable the clock to the GPIO Port F for PWM pins */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0);
    MAP_GPIOPinConfigure(GPIO_PF1_M0PWM1);
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    /* ����PWM0Ϊ����/���¼�����������ͬ���� */
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
                            PWM_GEN_MODE_NO_SYNC);  //���� PWM ������

    /* ����PWM����Ϊ50Hz��������ʵĲ���N=(1/ f) * SysClk.
               N = (1 / f)����N�Ǻ���������
               fΪ����Ƶ�ʣ�SysClkΪPWM0_BASEϵͳʱ��Ƶ��1.875M������������£�
               ��õ�:(1 / 50Hz) * 1.875MHz = 37500���ڡ���ע��,
               ���������õ� ���������2^16 - 1��*/
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 37500);

/*
     //����25%��ռ�ձȣ�PWM0
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                         MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);

    //����75%��ռ�ձȣ�PWM1
     MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                             MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
*/
    MAP_IntMasterEnable();  //���ܲ���

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
@������u32Base��PWM��ַ��PWM0_BASE
      ui32PWNOUT��PWMͨ����PWM_OUT_x,  x  ���� 0-7
      ui32Gen��PWM��������һ����������Ӧ����PWMͨ����PWM_GEN_x, xΪ0-3
      Angle���Ƕȣ�ֵΪ0-270��
@��飺����ָ��ͨ����ռ�ձ�
        ����50Hz,����Ϊ0.5ms--2.5ms�Ķ����˵��ռ�ձ�Ӧ��������0.025-0.125֮��
        ���˺���ֱ�ӽ��Ƕȷ�װ��������270�ȶ����Angle��Ӧ����ĽǶ�
*/
void
Set_PWM_Value_Angle(uint32_t u32Base,uint32_t ui32PWNOUT,uint32_t ui32Gen,float Angle)
{
    float Value=Angle*0.1/270+0.025;
    MAP_PWMPulseWidthSet(u32Base, ui32PWNOUT,
                             MAP_PWMGenPeriodGet(u32Base, ui32Gen)*Value);

}


