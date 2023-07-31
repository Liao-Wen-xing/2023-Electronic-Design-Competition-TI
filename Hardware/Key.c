#include "KEY.h"
#include "ti/devices/msp432e4/driverlib/driverlib.h"
extern uint32_t g_ui32SysClock;
void Key_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOH)))
    {
      }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK)))
    {
      }
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_0|GPIO_PIN_1);
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTK_BASE, GPIO_PIN_6|GPIO_PIN_7);
    GPIOH->PUR |= GPIO_PIN_0|GPIO_PIN_1;
    GPIOK->PUR |= GPIO_PIN_6|GPIO_PIN_7;
}

char Key_GetNum(void)
{
    uint8_t Key_Num=0;
   if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_0)==0)
   {
       SysCtlDelay(g_ui32SysClock/50);
       while(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_0)==0);
       SysCtlDelay(g_ui32SysClock/50);
       Key_Num=1;
   }
    if(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_1)==0)
   {
        SysCtlDelay(g_ui32SysClock/50);
        while(GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_1)==0);
        SysCtlDelay(g_ui32SysClock/50);
   }
    if(GPIOPinRead(GPIO_PORTK_BASE,GPIO_PIN_6)==0)
   {
       SysCtlDelay(g_ui32SysClock/50);
       while(GPIOPinRead(GPIO_PORTK_BASE,GPIO_PIN_6)==0);
       SysCtlDelay(g_ui32SysClock/50);
    }
    if(GPIOPinRead(GPIO_PORTK_BASE,GPIO_PIN_7)==0)
   {
       SysCtlDelay(g_ui32SysClock/50);
       while(GPIOPinRead(GPIO_PORTK_BASE,GPIO_PIN_7)==0);
       SysCtlDelay(g_ui32SysClock/50);
       Key_Num=4;
   }
   return Key_Num;
}
