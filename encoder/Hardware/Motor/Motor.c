#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Initialize the motor direction pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Forward_LeftMotor_Direction_pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Forward_LeftMotor_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Backward_LeftMotor_Direction_pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Backward_LeftMotor_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Forward_RightMotor_Direction_pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Forward_RightMotor_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Backward_RightMotor_Direction_pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Backward_RightMotor_Port, &GPIO_InitStructure);
	
	//Initialize the motor pwm signal
	PWM_Init();
}

void Motor_SetSpeed(int16_t* Speed)
{
	if (Speed[0] >= 0)										//turn left motor forward
	{
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Forward_LeftMotor_Direction_GPIO	=	1;
		Backward_LeftMotor_Direction_GPIO	=	0;
		LeftMotor_PWM_SetCompare(Speed[0]);
	}
	else																	//turn left motor backward
	{
//	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//	GPIO_SetBits(GPIOA, GPIO_Pin_5);
		Forward_LeftMotor_Direction_GPIO	=0;
		Backward_LeftMotor_Direction_GPIO	=1;
		LeftMotor_PWM_SetCompare(-Speed[0]);
	}
	
	if (Speed[1] >= 0)										//turn right motor forward
	{
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		Forward_RightMotor_Direction_GPIO	=1;
		Backward_RightMotor_Direction_GPIO=0;
		RightMotor_PWM_SetCompare(Speed[1]);
	}
	else																	//turn right motor backward
	{
//	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//	GPIO_SetBits(GPIOA, GPIO_Pin_5);
		Forward_RightMotor_Direction_GPIO	=0;
		Backward_RightMotor_Direction_GPIO=1;
		RightMotor_PWM_SetCompare(-Speed[1]);
	}
}
