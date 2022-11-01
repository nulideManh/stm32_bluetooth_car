#include "Servo.h"
#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo

//0 ->180
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t servo_read(Servo *sv)
{
	return sv->angle;
}

void servo_write(Servo *sv, uint8_t angle)
{
	uint16_t ccr = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	sv->angle = angle;
	switch(sv->channel)
	{
		case TIM_CHANNEL_1:
			sv->htim->Instance->CCR1 = ccr;
			break;
		case TIM_CHANNEL_2:
			sv->htim->Instance->CCR2 = ccr;
			break;
		case TIM_CHANNEL_3:
			sv->htim->Instance->CCR3 = ccr;
			break;
		case TIM_CHANNEL_4:
			sv->htim->Instance->CCR4 = ccr;
			break;
	}
	
}
void servo_init(Servo *sv,TIM_HandleTypeDef *htim,uint16_t channel)
{
	sv->htim = htim;
	sv->channel = channel;
	sv->angle =0;
	
	htim->Instance->PSC = 71;
	htim->Instance->ARR = 19999;
	HAL_TIM_PWM_Start(htim,channel);
	
	servo_write(sv, 90); // front
}
