#include "MyTimer.h"
#include "stm32f10x.h"

void (* pfunc) (void);

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ) {
	
	Timer->Timer->PSC = Timer->PSC; 
	Timer->Timer->ARR = Timer->ARR;
}

void MyTimer_Base_Start ( MyTimer_Struct_TypeDef * Timer ) {
	
	
	Timer->Timer->CR1 |= 0x01;
	
	
}
void MyTimer_Base_Stop ( MyTimer_Struct_TypeDef * Timer ) {
	Timer->Timer->CR1 |= 0x01;
	Timer->Timer->CR1 ^= 0x01;
	
	Timer->Timer->DIER |= 0x01;
	Timer->Timer->DIER ^= 0x01;
}

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (* IT_function ) ( void ) ) {
	
	pfunc = IT_function;
	if (Timer == TIM1) {
		//TODO
	}
	
	if (Timer == TIM2) {
		NVIC->ISER[0] = 0x01 << 28;
		
		NVIC->IP[28] = Prio << 4;
	}
	
	if (Timer == TIM3) {
		NVIC->ISER[0] = 0x01 << 29;
		
		NVIC->IP[29] = Prio << 4;
	}
	
	if (Timer == TIM4) {
		NVIC->ISER[0] = 0x01 << 30;
		
		NVIC->IP[30] = Prio << 4;
	}
	
	Timer->DIER |= 0x01;
}

void TIM2_IRQHandler () {
	TIM2->SR ^= 0x01;
	pfunc();
}

void TIM3_IRQHandler () {
	TIM3->SR ^= 0x01;
	pfunc();
}

void TIM4_IRQHandler () {
	TIM4->SR ^= 0x01;
	pfunc();
}

// Incremental counter

void config_incremental(TIM_TypeDef * Timer, int ARR) {
	Timer->CCMR1 |= 0x01;
	Timer->CCMR1 |= 0x01 << 8;
	
	Timer->CCER &= ~(0x01 << 1);
	Timer->CCMR1 &= ~(0x1111 << 4);
	
	Timer->CCER &= ~(0x01 << 5);
	Timer->CCMR1 &= ~(0x1111 << 12);
	
	Timer->SMCR &= ~(0x0111);
	Timer->SMCR |= 0x011;
	
	Timer->CR1 |= 0x01;
	
	Timer->ARR = ARR;
}

void set_CNT(TIM_TypeDef * timer, int CNT) {
	timer->CNT = CNT;
}

void get_cnt(TIM_TypeDef * timer, int * val_cnt) {
	*val_cnt = timer->CNT;
}
