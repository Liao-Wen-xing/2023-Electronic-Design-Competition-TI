
#include <stdint.h>
#include <stdbool.h>
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include "OLED.h"
/*#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "inc/hw_memmap.h"
*/

// ����ADCͨ������
#define ADC_CHANNEL_COUNT 4

// ����ADC������
#define ADC_SAMPLE_RATE 1000 // 1000Hz

// ����ADC�������ݻ�������С
#define ADC_BUFFER_SIZE 100

// ����ADCͨ����������
const uint32_t adcChannels[ADC_CHANNEL_COUNT] = {
    ADC_CTL_CH0, // ͨ��0
    ADC_CTL_CH1, // ͨ��1
    ADC_CTL_CH2, // ͨ��2
    ADC_CTL_CH3  // ͨ��3
};

// ����ADC���ݻ�����
uint32_t adcBuffer[ADC_CHANNEL_COUNT][ADC_BUFFER_SIZE];

// ��ʼ��ADC
void ADC_Configuration(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // ʹ��GPIOE����ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ʹ��ADC0����ʱ��

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0); // ����PE3��PE2��PE1��PE0Ϊģ������

    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, adcChannels[0] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, adcChannels[1] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, adcChannels[2] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, adcChannels[3] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    ADCSequenceDMAEnable(ADC0_BASE, 1);
    ADCIntEnable(ADC0_BASE, 1);
}

// ��ȡADC��������
void ADC_GetData(void) {
    ADCProcessorTrigger(ADC0_BASE, 1); // ����ADC����
}

// ����ADC��������
void ADC_ProcessData(void) {
    uint32_t i, j;

    for (i = 0; i < ADC_CHANNEL_COUNT; i++) {
        for (j = 0; j < ADC_BUFFER_SIZE; j++) {
            // ����adcBuffer[i][j]�������ӡ������
        }
    }
}

