//Binome : Paul Chabert, Thomas Perez
//Groupe : B2
#include "stm32f10x.h"
#define MODE_FLOATING_INPUT (4)
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche){
				
			if (Port == GPIOA	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; //led
			}
			
			if (Port == GPIOB	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ; //led
			}
			
			if (Port == GPIOC	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; //led
			}
			
			if (Port == GPIOD	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPDEN ; //led
			}
	
		
			if(Broche < 8){
				Port->CRL &= ~(0xF<<Broche*4) ;
				Port->CRL |=  1 << (Broche*4)   ; 
			}
			else {
				Port->CRH &= ~(0xF<<(Broche-8)*4);
				Port->CRH |=  0b0001 << ((Broche-8)*4)  ; 
			}
			return 0;
		}


char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche){
			if (Port == GPIOA	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ; //led
			}
			
			if (Port == GPIOB	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ; //led
			}
			
			if (Port == GPIOC	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ; //led
			}
			
			if (Port == GPIOD	) {
				RCC->APB2ENR |= RCC_APB2ENR_IOPDEN ; //led
			}
			
			if(Broche < 8){
				Port->CRL &= ~(0xF<<Broche*4);
				Port->CRL |=  MODE_FLOATING_INPUT << (Broche*4)   ; 
			}
			else {
				Port->CRH &= ~(0xF<<(Broche-8)*4);
				Port->CRH |= MODE_FLOATING_INPUT << (2+(Broche-8)*4)  ; 
			}
			return 0;
		}



void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche){
		Port->BSRR= 1<< Broche;
	}


void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche){
		Port->BSRR= (1<<Broche) <<16;
}

unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche) {
	return (Port->IDR & 1<<Broche)>> Broche;
}

void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche) {
	/*	if ( Port_IO_Read(Port,Broche) ==1) {
			Port_IO_Reset(Port, Broche);
		}
		else {
			Port_IO_Set(Port, Broche);
		}	*/
	 Port->ODR ^= 0x1<<Broche;
}
