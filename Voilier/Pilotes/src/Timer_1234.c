#include "stm32f10x.h"
#include "math.h"
#include "clock.h"
#include "gpio.h"

void (*ptrfct)(void) ;

float Timer_1234_Init(TIM_TypeDef *Timer, u32 frequence ) {
	
	float frequence_dentree;
	if (Timer == TIM1) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;
		frequence_dentree = CLOCK_GetTIMCLK (Timer);
	}
	if (Timer == TIM2) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		frequence_dentree = CLOCK_GetTIMCLK (Timer);

	}
	if (Timer == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		frequence_dentree = CLOCK_GetTIMCLK (Timer);
	}
	if (Timer == TIM4) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		frequence_dentree = CLOCK_GetTIMCLK (Timer);
	}
	
	Timer->CR1 |= TIM_CR1_CEN;
	
	double psc = (frequence_dentree/frequence) / 0xFFFF ;
	if (psc - floor(psc) > 0) {
		psc = floor(psc)+1;
	}
		
	float ARR = (frequence_dentree / psc) ;
	
	
	Timer->PSC = psc-1;
	Timer->ARR = ARR-1;
	
	return 0;
}

void TIM2_IRQHandler(void){
	TIM2->SR &= ~ (TIM_SR_UIF);
	if(ptrfct!=_NULL){
		(*ptrfct)();
	}
}

void TIM3_IRQHandler(void){
	TIM3->SR &= ~ (TIM_SR_UIF);
	if(ptrfct!=_NULL){
		(*ptrfct)();
	}
}

void TIM4_IRQHandler(void){
	TIM4->SR &= ~ (TIM_SR_UIF);
	if(ptrfct!=_NULL){
		(*ptrfct)();
	}
}


void  Timer_Active_IT( TIM_TypeDef *Timer, u8 Priority ,void (*IT_function) (void)) {
		
	if (Timer == TIM2) {
		
		NVIC->IP[28]= Priority << 4 ;
		ptrfct=IT_function;
		NVIC->ISER[0] |= NVIC_ISER_SETENA_28 ;
	}
	
	if (Timer == TIM3) {
	
		NVIC->IP[29]= Priority << 4 ;
		ptrfct=IT_function;
			NVIC->ISER[0] |= NVIC_ISER_SETENA_29 ;
	}
	if (Timer == TIM4) {
	
		NVIC->IP[30]= Priority << 4;	
		ptrfct=IT_function;
			NVIC->ISER[0] |= NVIC_ISER_SETENA_30 ;
	}
	Timer->DIER |= TIM_DIER_UIE;
	
	
}