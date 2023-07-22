#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"
#include "Motor.h"
#include <stdio.h>
#include "mpu6050.h"										//MPU6050 library
#include "inv_mpu.h"

//variable declare
float pitch,roll,yaw; 		//Euler angle
short aacx,aacy,aacz;		//angular acceleration
short gyrox,gyroy,gyroz;	//gyroscope
short temp;					//temperture
double Speed[2];
int16_t Set_Speed[2]={50,0};
int16_t Encoder_Num[2];

/*
name: mpu_init_function
*/
void mpu_init_function(void)
{
	MPU_Init();	                                     //initial MPU6050
	while(mpu_dmp_init())                            //make sure successfully initial mpu_dmo 
 	{
		OLED_ShowString(1,1,"                ");		//print error message on oled
		OLED_ShowString(1,1,"error:init");
	}
	
	OLED_ShowString(1,1,"                ");		//print success message on oled
	OLED_ShowString(1,1,"succeed:init");
	delay_ms(999);									//delay one second
}



int main(void)
{
	delay_init();
	OLED_Init();
	Encoder_Init();
	Motor_SetSpeed(Set_Speed);
	mpu_init_function();
	Motor_Init();
	//Timer_Init();
	char str[17];
	while (1)
	{
		sprintf(str, "Speed:%.1f %.1f", Speed[1], Speed[0]);
		OLED_Clear();
		OLED_ShowString(1, 1, str);
		
		sprintf(str, "pitch:%.1f ",(float)pitch);
		OLED_ShowString(2,1,"                ");
		OLED_ShowString(2,1,str);
		
		
		sprintf(str, "roll:%.1f ",(float)roll);
		OLED_ShowString(3,1,"                ");
		OLED_ShowString(3,1,str);
		
		
		sprintf(str, "yaw:%.1f ",(float)yaw);
		OLED_ShowString(4,1,"                ");
		OLED_ShowString(4,1,str);
		
		delay_ms(100);
	}
}

//interrupt callback function of TIM2
void TIM1_UP_IRQHandler(void)
{
	//char str[17];
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		Encoder_Get(Encoder_Num);
		Speed[0] = Encoder_Num[0]*0.065*3.1415926*50/11;
		Speed[0] = Encoder_Num[0]*0.065*3.1415926*50/11;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		
		
		
		
		/*
		mpu6050
		*/
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//getting data that were processed by dmp
			{
				
				
			}
		
		
	}
}
