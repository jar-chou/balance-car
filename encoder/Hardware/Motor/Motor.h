#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"   
#include "sys.h"

//the define of Motor direction pin
#define 			Forward_LeftMotor_Port																	GPIOA
#define 			Forward_LeftMotor_Direction_pin													GPIO_Pin_4

#define 			Backward_LeftMotor_Port																	GPIOA
#define 			Backward_LeftMotor_Direction_pin												GPIO_Pin_5

#define 			Forward_RightMotor_Port																	GPIOA
#define 			Forward_RightMotor_Direction_pin												GPIO_Pin_2

#define 			Backward_RightMotor_Port																GPIOA
#define 			Backward_RightMotor_Direction_pin												GPIO_Pin_3

//the define used to operate Motor direction GPIO
#define				Forward_LeftMotor_Direction_GPIO												PAout(4)
#define				Backward_LeftMotor_Direction_GPIO												PAout(5)

#define				Forward_RightMotor_Direction_GPIO												PAout(2)
#define				Backward_RightMotor_Direction_GPIO											PAout(3)


void Motor_Init(void);
void Motor_SetSpeed(int16_t* Speed);

#endif
