#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "setup.h"
#include "bordage.h"
#include "MyUsart.h"
#include "pwm.h"
#include <math.h>
#include <stdlib.h>


int main ( void )
{
	int * val_cnt;
	int test = 0;
	
	MyGPIO_Struct_TypeDef * GPIOStructPtr;
	
	MyTimer_Struct_TypeDef * Timer;
	MyGPIO_Struct_TypeDef * gpio_struct;
	
	// Clock enable
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	// Alloc
	
	GPIOStructPtr = malloc(sizeof(MyGPIO_Struct_TypeDef));
	val_cnt = malloc(sizeof(int));
	
	// Setup GPIO
	
	GPIOStructPtr->GPIO = GPIOA;
	GPIOStructPtr->GPIO_Pin = PA8;
	GPIOStructPtr->GPIO_Conf = In_Floating;
	
	MyGPIO_Init ( GPIOStructPtr );
	
	GPIOStructPtr->GPIO = GPIOA;
	GPIOStructPtr->GPIO_Pin = 5;
	GPIOStructPtr->GPIO_Conf = Out_Ppull;
	
	MyGPIO_Init ( GPIOStructPtr );
	
	// Setup timer
	
	config_incremental(TIM2, ARR_IC);
	
	// Reset Incremental counter
	while(test == 0) {
		test = MyGPIO_Read(GPIOA, PA8);
	}
	set_CNT(TIM2, Reset_IC);
	
	// Setup servo moteur
	
	
	gpio_struct = malloc(sizeof(MyGPIO_Struct_TypeDef));
	
	gpio_struct->GPIO = GPIOA;
	gpio_struct->GPIO_Conf = AltOut_Ppull;
	gpio_struct->GPIO_Pin = 6;
	
	MyGPIO_Init(gpio_struct);
	
	Timer = malloc(sizeof(MyTimer_Struct_TypeDef));
	Timer->Timer = TIM3;
	MyTimer_Base_Init(Timer);
	
	MyTimer_Base_Start(Timer);
	
	// Bordage
	
	while (1) {
		get_cnt(TIM2, val_cnt);
		bordage_process(*val_cnt);
	}	
}


/////// USART
 /*
	char s = 'A';
	int cpt = 0;
	
	MyGPIO_Struct_TypeDef * GPIOStructPtr;
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOStructPtr = malloc(sizeof(MyGPIO_Struct_TypeDef));
	
	GPIOStructPtr->GPIO = GPIOA;
	GPIOStructPtr->GPIO_Conf = AltOut_Ppull;
	GPIOStructPtr->GPIO_Pin = 9;
	
	MyGPIO_Init(GPIOStructPtr);

	

	
	
		
	myUsartInit(USART1);
	myUsartWrite(USART1, 'a');
}
	
	
	/*while(cpt < 20) {
		
		myUsartWrite(USART1, s+cpt);
		cpt++;
	
	}
	myUsartWrite(USART1, '\n');*/
