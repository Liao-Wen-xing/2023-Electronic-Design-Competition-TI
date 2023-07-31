#ifndef __UART_H
#define __UART_H
#include "ti/devices/msp432e4/driverlib/driverlib.h"
extern uint32_t g_ui32SysClock;
void UART6_Init(void);
void UART2_Init(void);
void UARTSends(uint32_t ui32Base,const char *pui8Buffer);
void UARTSend(uint32_t ui32Base,const char c);

#endif
