/***********************************************
*            OLED�õ���ͷ�ļ����궨��ͺ�������
***********************************************/
#ifndef __OLED_H
#define __OLED_H
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>



//#include "sys.h"
//#include "stdlib.h"	  
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define GPIO_OLED_DAT_PORT_BASE     GPIO_PORTN_BASE  //OLED??D1?????
#define GPIO_OLED_DAT_PORT_SYSCTL   SYSCTL_PERIPH_GPION
#define GPIO_OLED_DAT_PIN           GPIO_PIN_4

#define GPIO_OLED_SCLK_PORT_BASE    GPIO_PORTN_BASE  //OLED?D0????
#define GPIO_OLED_SCLK_PORT_SYSCTL  SYSCTL_PERIPH_GPION
#define GPIO_OLED_SCLK_PIN          GPIO_PIN_5


#define SIZE 16
#define XLevelL     0x02
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64

//void delay_ms(unsigned int ms);

//OLED�����ú���
void init();
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len);
void DispADC_DATA(u8 x,u8 y,u32 DispData);
void OLED_ShowString(u8 x,u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
#endif
