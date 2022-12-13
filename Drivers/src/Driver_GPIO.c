#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	
	int pin = GPIOStructPtr->GPIO_Pin;
	
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 2) | (0x01 << 2);
	
	if (GPIOStructPtr->GPIO_Pin < 8) {
		GPIOStructPtr->GPIO->CRL &= ~(0x0F << (pin * 4));
		GPIOStructPtr->GPIO->CRL |= GPIOStructPtr->GPIO_Conf << (pin * 4);
		
	}
	else {
		pin = pin - 8;
		GPIOStructPtr->GPIO->CRH &= ~(0x0F << (pin * 4) );
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << pin * 4);
	}
};

int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { // renvoie 0 ou autre chose different de 0
	uint32_t testIDR;
	testIDR = GPIO->IDR & (0x01 << GPIO_Pin);
	
	if (testIDR == (0x01<<GPIO_Pin)) {
		return 1;
	}
	else {
		return 0;
	}
}
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->BSRR = (0x01 << GPIO_Pin);
}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->BRR = (0x01 << GPIO_Pin);
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= 0x01 << GPIO_Pin;
}
