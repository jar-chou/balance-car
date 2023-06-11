#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
#include "Motor.h"
#include <stdio.h>
double Speed;

int main(void)
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	Motor_Init();
	OLED_ShowString(1, 1, "Speed:");
	Motor_SetSpeed(50);
	char string[16];
	while (1)
	{
		sprintf(string, "Speed:%.1f", Speed);
		OLED_Clear();
		OLED_ShowString(1, 1, string);
		OLED_ShowString(1, 1, "Speed:");
		Delay_ms(100);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Speed = Encoder_Get()*0.065*3.1415926*5/11;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
