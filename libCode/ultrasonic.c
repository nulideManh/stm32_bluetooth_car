#include "ultrasonic.h"

HCSR04_State hc04_state = HCSR04_IDLE_STATE;

float distance;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(hc04_state)
	{
		case HCSR04_WAIT_RISING_STATE:
			if(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin) == 1)
			{
				htim3.Instance->CNT =0;
				hc04_state = HCSR04_WAIT_FALLING_STATE;
				HAL_TIM_Base_Start(&htim3);
			}
			else
			{
				hc04_state = HCSR04_IDLE_STATE;
			}
			break;
		case HCSR04_WAIT_FALLING_STATE:
			if(HAL_GPIO_ReadPin(ECHO_GPIO_Port,ECHO_Pin) == 0)
			{
				HAL_TIM_Base_Stop(&htim3);
				hc04_state = HCSR04_COMPLETE_STATE;
			}
			else
			{
				hc04_state = HCSR04_IDLE_STATE;
			}
			break;
		default:
			break;
	}	
}
/*void HC04_Start()
{
	if(hc04_state == HCSR04_IDLE_STATE)
	{
		HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,(GPIO_PinState)1);
		HAL_Delay(1);
		HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,(GPIO_PinState)0);
		
		hc04_state = HCSR04_WAIT_RISING_STATE;
	}
}
float distance;
void HC04_Complete_Callback(float kc)
{

	distance = kc;
} 
void HC04_Handle()
{
	if(hc04_state == HCSR04_COMPLETE_STATE)
	{
		//tinh toan khoang cach
		float kc = 0.017*htim3.Instance->CNT;
		HC04_Complete_Callback(kc);
		hc04_state = HCSR04_IDLE_STATE;
	}
} */

float UltrasonicDetect(void)
{
	if(hc04_state == HCSR04_IDLE_STATE)
	{
		HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,(GPIO_PinState)1);
		HAL_Delay(1);
		HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,(GPIO_PinState)0);
		
		hc04_state = HCSR04_WAIT_RISING_STATE;
	}
	
	if(hc04_state == HCSR04_COMPLETE_STATE)
	{
		distance = 0.017*htim3.Instance->CNT;
		hc04_state = HCSR04_IDLE_STATE;
	}
	return distance;
	
}

