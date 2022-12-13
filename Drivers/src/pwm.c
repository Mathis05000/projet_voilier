#include "stm32f10x.h"
#include "MyTimer.h"
#include <math.h>
#include <stdlib.h>
#define PWM_RAPPORT_FREQ 1440000
#define PWM_ARR 99
#define PWM_PSC	(PWM_RAPPORT_FREQ / PWM_ARR ) -1

void MyTimer_PWM( TIM_TypeDef * Timer ,  char Channel ) {
	
	switch(Channel){
	
		case 1:
			Timer ->CCMR1 &= ~(1<<4);
			Timer ->CCMR1 |= (6<<4);
			Timer->CCER |= 1;
			Timer -> CCR1=0;
			break;
		
		case 2:
			Timer ->CCMR1 &= ~(6<<12);
			Timer ->CCMR1 |= (6<<12);
			Timer->CCER &= ~(0<<4);
			Timer->CCER |= (1<<4);
			Timer -> CCR2=0;
			break;
		
		case 3:
			Timer ->CCMR2 &= ~(6<<4);
			Timer ->CCMR1 |= (6<<4);
			Timer->CCER &= ~(0<<8);
			Timer->CCER |= (1<<8);
			Timer -> CCR3=0;
			break;
		
		case 4:
			Timer ->CCMR2 &= ~(6<<12);
			Timer ->CCMR2 |= (6<<12);
			Timer->CCER &= ~(0<<12);
			Timer->CCER |= (1<<12);
			Timer -> CCR4=0;
			break;
		
		default:
			break;
	}
	
}

int CCR;
void PWM_init(TIM_TypeDef * Timer, int RAPCYC,int canal){
		
	MyTimer_PWM (Timer,canal);
	CCR = (PWM_ARR*RAPCYC)/100;
	Timer->PSC = PWM_PSC;
	Timer->ARR= PWM_ARR;
	switch(canal) {
		case 1  :
			Timer->CCR1 = CCR;
			break;
		case 2 :
			Timer->CCR2 = CCR;
			break;
		case 3 :
			Timer->CCR3 = CCR;
			break;
		case 4 : 
			Timer->CCR4 = CCR;
			break;
	}
}

/*
int PWM_RAPCYCL( int angle){
	int result;
	
	if (angle <= 45 ) { 
		result=5;
	}
	else if (angle > 45 && angle < 67) {
		result=6;
	}
	else if (angle >= 67 && angle <90){
		result=7;
	}
	else if (angle >= 90 && angle <112){
		result =8;
	}
	else if (angle >= 112 && angle < 135){
		result=9;
	}
	
} */
