#ifndef __PWM_H
#define __PWM_H
# include "stm32f10x.h"
void PWM_Init(void);

static inline void LeftMotor_PWM_SetCompare(uint16_t Compare)
{
	TIM_SetCompare1(TIM1, Compare);
}

static inline void RightMotor_PWM_SetCompare(uint16_t Compare)
{
	TIM_SetCompare4(TIM1, Compare);
}

#endif
