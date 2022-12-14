#include "setup.h"
#include "Driver_GPIO.h"
#include "pwm.h"

void bordage_process(int cnt) {
	
	if (cnt > AVDP || cnt < AVGP) {
		PWM_init(TIM3,2,1);
	}
	
	if (cnt > AVGP && cnt < AVGF) {
		PWM_init(TIM3,1,1);
	}
	
	if (cnt > AVGF && cnt < ARGF) {
		PWM_init(TIM3,4,1);
	}
	
	if (cnt > ARGF && cnt < ARGP) {
		PWM_init(TIM3,6,1);
	}
	
	if (cnt > ARGP && cnt < ARDP) {
		PWM_init(TIM3,8,1);
	}
	
	if (cnt > ARDP && cnt < ARDF) {
		PWM_init(TIM3,6,1);
	}
	
	if (cnt > ARDF && cnt < AVDF) {
		PWM_init(TIM3,4,1);
	}
	
	if (cnt > AVDF && cnt < AVDP) {
		PWM_init(TIM3,1,1);
	}
}
