
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

// 定义ADC通道数量
#define ADC_CHANNEL_COUNT 4

// 定义ADC采样率
#define ADC_SAMPLE_RATE 1000 // 1000Hz

// 定义ADC采样数据缓冲区大小
#define ADC_BUFFER_SIZE 100

// 定义ADC通道配置数组
const uint32_t adcChannels[ADC_CHANNEL_COUNT] = {
    ADC_CTL_CH0, // 通道0
    ADC_CTL_CH1, // 通道1
    ADC_CTL_CH2, // 通道2
    ADC_CTL_CH3  // 通道3
};

// 定义ADC数据缓冲区
uint32_t adcBuffer[ADC_CHANNEL_COUNT][ADC_BUFFER_SIZE];

// 初始化ADC
void ADC_Configuration(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // 使能GPIOE外设时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // 使能ADC0外设时钟

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0); // 配置PE3、PE2、PE1、PE0为模拟输入

    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, adcChannels[0] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, adcChannels[1] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, adcChannels[2] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, adcChannels[3] | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    ADCSequenceDMAEnable(ADC0_BASE, 1);
    ADCIntEnable(ADC0_BASE, 1);
}

// 获取ADC采样数据
void ADC_GetData(void) {
    ADCProcessorTrigger(ADC0_BASE, 1); // 启动ADC采样
}

// 处理ADC采样数据
void ADC_ProcessData(void) {
    uint32_t i, j;

    for (i = 0; i < ADC_CHANNEL_COUNT; i++) {
        for (j = 0; j < ADC_BUFFER_SIZE; j++) {
            // 处理adcBuffer[i][j]，例如打印到串口
        }
    }
}

