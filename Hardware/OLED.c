/***********************************************
*            OLED锟矫碉拷锟侥猴拷锟斤拷锟斤拷锟斤拷
***********************************************/

//              ----------------------------------------------------------------
//              GND    锟斤拷源锟斤拷
//              VCC   锟斤拷3.3v锟斤拷源
//              SCL   P4.0锟斤拷时锟接ｏ拷
//              SDA   P3.2锟斤拷锟斤拷锟捷ｏ拷
//              ----------------------------------------------------------------
#include "oled.h"
//#include "stdlib.h"
#include "oledfont.h"
//#include "delay.h"
//OLED锟斤拷锟皆达拷
//锟斤拷鸥锟绞斤拷锟斤拷锟�.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
#define OLED_SCLK_Clr()  MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE,GPIO_OLED_SCLK_PIN,0)    //OLED_SCL=0
#define OLED_SCLK_Set()  MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE,GPIO_OLED_SCLK_PIN,0xFF) //OLED_SCL=1

#define OLED_SDIN_Clr()  MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE,GPIO_OLED_DAT_PIN,0)     //OLED_SDIN=0
#define OLED_SDIN_Set()  MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE,GPIO_OLED_DAT_PIN,0xFF) //OLED_SDIN=1;


void init()                                           //OLED锟剿口讹拷锟斤拷
{

}

/*void delay_ms(unsigned int ms)
{
    unsigned int a;
    while(ms)
    {
        a=1800;
        while(a--);
        ms--;
    }
    return;
}*/

//锟斤拷SSH1106写锟斤拷一锟斤拷锟街节★拷
//dat:要写锟斤拷锟斤拷锟斤拷锟�/锟斤拷锟斤拷
//cmd:锟斤拷锟斤拷/锟斤拷锟斤拷锟街� 0,锟斤拷示锟斤拷锟斤拷;1,锟斤拷示锟斤拷锟斤拷;

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

    OLED_SCLK_Set() ;
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
    OLED_SCLK_Set() ;
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void IIC_Wait_Ack()
{
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}

/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0;i<8;i++)
    {
            m=da;
        m=m&0x80;
        if(m==0x80)
        {OLED_SDIN_Set();}
        else OLED_SDIN_Clr();
            da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
        }


}

/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x00);            //write command
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
   IIC_Stop();
}

/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //D/C#=0; R/W#=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x40);            //write data
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
   IIC_Stop();
}

void OLED_WR_Byte(u8 dat,u8 cmd)
{
    if(cmd)
            {

   Write_IIC_Data(dat);

        }
    else {
   Write_IIC_Command(dat);

    }
}



//锟斤拷锟斤拷锟斤拷锟斤拷
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte((((x+2)&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte(((x+2)&0x0f),OLED_CMD);
}
//锟斤拷锟斤拷OLED锟斤拷示
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC锟斤拷锟斤拷
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//锟截憋拷OLED锟斤拷示
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC锟斤拷锟斤拷
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}
//锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷幕锟角猴拷色锟斤拷
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //锟斤拷锟斤拷页锟斤拷址锟斤拷0~7锟斤拷
        OLED_WR_Byte (0x02,OLED_CMD);      //锟斤拷锟斤拷锟斤拷示位锟矫★拷锟叫低碉拷址
        OLED_WR_Byte (0x10,OLED_CMD);      //锟斤拷锟斤拷锟斤拷示位锟矫★拷锟叫高碉拷址
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
    } //锟斤拷锟斤拷锟斤拷示
}


//锟斤拷指锟斤拷位锟斤拷锟斤拷示一锟斤拷锟街凤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟街凤拷
//x:0~127
//y:0~63
//mode:0,锟斤拷锟斤拷锟斤拷示;1,锟斤拷锟斤拷锟斤拷示
//size:选锟斤拷锟斤拷锟斤拷 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{
    unsigned char c=0,i=0;
        c=chr-' ';//锟矫碉拷偏锟狡猴拷锟街�
        if(x>Max_Column-1){x=0;y=y+2;}
        if(SIZE ==16)
            {
            OLED_Set_Pos(x,y);
            for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
            OLED_Set_Pos(x,y+1);
            for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
            }
            else {
                OLED_Set_Pos(x,y+1);
                for(i=0;i<6;i++)
                OLED_WR_Byte(F6x8[c][i],OLED_DATA);

            }
}
//m^n锟斤拷锟斤拷
u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}
//锟斤拷示2锟斤拷锟斤拷锟斤拷
//x,y :锟斤拷锟斤拷锟斤拷锟�
//len :锟斤拷锟街碉拷位锟斤拷
//size:锟斤拷锟斤拷锟叫�
//mode:模式   0,锟斤拷锟侥Ｊ�;1,锟斤拷锟斤拷模式
//num:锟斤拷值(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len)
{
    u8 t,temp,m=0;
        for(t=0;t<len;t++)
        {
            temp=(num/oled_pow(10,len-t-1))%10;
                if(temp==0)
                {
                    OLED_ShowChar(x+(16/2+m)*t,y,'0');
          }
                else
                {
                  OLED_ShowChar(x+(16/2+m)*t,y,temp+'0');
                }
      }
}

void OLED_ShowSignedNum(u8 x,u8 y,int32_t num,u8 len)
{
    u8 t,temp,m=0;
    if(num>0)
    {
        OLED_ShowChar(x,y,'+');
        num=num;
    }
    else
    {
        OLED_ShowChar(x,y,'-');
        num=-num;
    }
        for(t=0;t<len;t++)
        {
            temp=(num/oled_pow(10,len-t-1))%10;
                if(temp==0)
                {
                    OLED_ShowChar(x+8+(16/2+m)*t,y,'0');
                }
                else
                {
                  OLED_ShowChar(x+8+(16/2+m)*t,y,temp+'0');
                }
        }
}
/******************************************************************************
* ??:Disp---AD
* ??:??????
* ????:?
* ????:?
******************************************************************************/
void DispADC_DATA(u8 x,u8 y,u32 DispData)
{
	u32 time;
	u8  bit4,bit3,bit2,bit1;
	time=DispData*1000*3.3/4096;
	bit4=time/1000;
	bit3=time%1000/100;
	bit2=time%1000%100/10;
	bit1=time%10;
	
	OLED_ShowNum(x,y,bit4,1);
	OLED_ShowChar(x+8,y,'.');
	OLED_ShowNum(x+16,y,bit3,1);
	OLED_ShowNum(x+24,y,bit2,1);
	OLED_ShowNum(x+32,y,bit1,1);
	
   }
//锟斤拷示一锟斤拷锟街凤拷锟脚达拷
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {       OLED_ShowChar(x,y,chr[j]);
            x+=8;
        if(x>120){x=0;y+=2;}
            j++;
    }
}
//锟斤拷示锟斤拷锟斤拷
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{
    u8 t,adder=0;
    OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
        {
                OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
                adder+=1;
     }
        OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
            {
                OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
                adder+=1;
      }
}
//锟斤拷示锟斤拷示BMP图片128锟斤拷64锟斤拷始锟斤拷锟斤拷锟斤拷(x,y),x锟侥凤拷围0锟斤拷127锟斤拷y为页锟侥凤拷围0锟斤拷7
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
 unsigned int j=0;
 unsigned char x,y;

  if(y1%8==0) y=y1/8;
  else y=y1/8+1;
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}
//锟斤拷锟斤拷始锟斤拷锟疥（x锟斤拷y锟斤拷锟斤拷始锟斤拷示锟街凤拷锟斤拷
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;

  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>120){x=0;y++;}
    OLED_Set_Pos(x,y);
    for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
    OLED_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    x+=8;
    j++;
  }
}

//锟斤拷始锟斤拷SSH1106
void OLED_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
            while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)))
            {
              }
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_4);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTN_BASE,  (GPIO_PIN_0 |GPIO_PIN_4 | GPIO_PIN_5), (0));

    OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
    OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
    OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0锟斤拷锟揭凤拷锟斤拷 0xa1锟斤拷锟斤拷
    OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0锟斤拷锟铰凤拷锟斤拷 0xc8锟斤拷锟斤拷
    OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset   Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00,OLED_CMD);//-not offset
    OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
    OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
    OLED_WR_Byte(0x12,OLED_CMD);
    OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
    OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
    OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
    OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel

    OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/
    OLED_Clear();
    OLED_Set_Pos(0,0);
}

