#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM7_Int_Init(u16 arr,u16 psc);

void TIM14_PWM_Init(u32 arr,u32 psc);
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);

#endif























