#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
#include "Motor.h"
int16_t Speed;

int main(void)
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	Motor_Init();
	OLED_ShowString(1, 1, "Speed:");
	Motor_SetSpeed(50);
	while (1)
	{
		OLED_ShowSignedNum(1, 7, Speed, 3);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Speed = Encoder_Get()*60/660;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
