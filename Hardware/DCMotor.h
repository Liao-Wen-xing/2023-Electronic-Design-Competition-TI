#ifndef __DCMOTOR_H__
#define __DCMOTOR_H__

void PWM2_3_Init();
void Set_PWM_Value(uint32_t u32Base,uint32_t ui32PWNOUT,uint32_t ui32Gen,float Value);

void corotation_1(void);
void reverse_1(void);
void corotation_2(void);
void reverse_2(void);

void Out_GPIO_Init(void);

#endif
