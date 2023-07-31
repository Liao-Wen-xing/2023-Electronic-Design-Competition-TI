#include "_UART.h"
#include "OLED.h"
uint32_t str;
void UART6_Init(void){
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PP1_U6TX);
    GPIOPinConfigure(GPIO_PP0_U6RX);
    MAP_GPIOPinTypeUART(GPIO_PORTP_BASE, GPIO_PIN_1 | GPIO_PIN_0);
    //
    // Enable the UART interrupt.
    //
   MAP_UARTConfigSetExpClk(UART6_BASE, g_ui32SysClock, 9600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
   MAP_IntEnable(INT_UART6);
   MAP_UARTIntEnable(UART6_BASE, UART_INT_RX | UART_INT_RT);
}

void UART2_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    MAP_IntMasterEnable();


    GPIOPinConfigure(GPIO_PD4_U2RX);
    GPIOPinConfigure(GPIO_PD5_U2TX);
    MAP_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    //
    // Enable the UART interrupt.
    //
   MAP_UARTConfigSetExpClk(UART2_BASE, g_ui32SysClock, 9600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
   MAP_IntEnable(INT_UART2);
   MAP_UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
}
//@参数：ui32Base，串口基址，UARTx_BASE,x为0-7
//       pui8Buffer,字符串
void
UARTSends(uint32_t ui32Base,const char *pui8Buffer)
{
    //
    // Loop while there are more characters to send.
    //
    while(*pui8Buffer)
    {
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPutNonBlocking(ui32Base, *pui8Buffer++);
    }
}
void
UARTSend(uint32_t ui32Base,const char c)
{
    UARTCharPut(ui32Base, c);
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************

/**
  * @brief  接收蓝牙数据，三个有效数据；
            有效数据放在Data_Pack_Blue数组中
  * @param  无
  * @retval 无
  */
void
UART2_IRQHandler(void)
{
    static uint8_t RxState = 0;
    static uint8_t pRxPacket = 0;
    uint32_t ui32Status;
    ui32Status = MAP_UARTIntStatus(UART2_BASE, true);
    MAP_UARTIntClear(UART2_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
    while(MAP_UARTCharsAvail(UART2_BASE))
    {
       // Read the next character from the UART and write it back to the UART.
       uint32_t  RxData=MAP_UARTCharGetNonBlocking(UART2_BASE);
       //MAP_UARTCharGetNonBlocking()  读取指定端口FIFO中的字符  强制转化为uint32_t
       if (RxState == 0&&RxData==0xAD)
           {
               RxState = 1;
           }
           else if (RxState == 1&&RxData==0xCC)
           {
               RxState = 2;
               pRxPacket=0;
           }
           else if (RxState ==2)
           {
               if (RxData == 0xFD)
               {
                   RxState=3;
               }
               else if(pRxPacket<=2)
               {
                   //存放数据位
                   pRxPacket++;
               }
               else RxState=3;
           }
           else RxState=3;
           if(RxState==3)
           {
               RxState=0;
               pRxPacket=0;
           }
        SysCtlDelay(g_ui32SysClock / (1000 * 3));
    }
}

