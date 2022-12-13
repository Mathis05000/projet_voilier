#include "stm32f10x.h"
#include "MyTimer.h"
#include <math.h>
#include <stdlib.h>
void MyTimer_PWM( TIM_TypeDef * Timer, char Channel );
void PWM_init(TIM_TypeDef * Timer, int RAPCYC,int canal);



