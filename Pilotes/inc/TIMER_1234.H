#include "stm32f10x.h"

float Timer_1234_Init(TIM_TypeDef *Timer, u32 frequence ) ;

void Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority,void (*IT_function) (void)) ;

void callback_TIM (void)  ;
