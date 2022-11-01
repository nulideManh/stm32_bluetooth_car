#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

typedef enum
{
	HCSR04_IDLE_STATE,
	HCSR04_WAIT_RISING_STATE,
	HCSR04_WAIT_FALLING_STATE,
	HCSR04_COMPLETE_STATE
	
}HCSR04_State;

//void HC04_Complete_Callback(float kc);
//void HC04_Start();
//void HC04_Handle();
float UltrasonicDetect(void);

#endif
