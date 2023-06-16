#include "stm32f10x.h"                  // Device header

static u32 fac_us;	//定义 1 个微秒的值
static u32 fac_ms;	//定义 1 个毫秒的值

/**
 * 初始化系统的嘀嗒定时器
 */
void delay_init(){
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟，将 72MHz 的频率 8 分频，把系统嘀嗒定时器的变化定位在 1s
	fac_us = SystemCoreClock / 8000000;			//将 fac_us 设置为系统时钟的 1 / 8000000，SystemCoreClock = 72MHz，9MHz <=> 1s
	fac_ms = fac_us * 1000;						//将 fac_ms 设置为 fac_us 的 1000 倍
}
/**
 * 微秒延迟计数
 * temp & 0x01 && !(temp & (1 << 16)) 详解：
 * temp & 0x01 通过定时器状态值的最小位（1位）判断定时器是否处于使能状态
 * !(temp & (1 << 16)) 通过定时器状态值的最大位（16位）判断定时器是否处于归零状态
 */
void delay_us(u32 nus){
	u32 temp;
	SysTick -> LOAD = nus * fac_us;		//设置重装载值
	SysTick -> VAL |= 0x00;		//将定时器归零
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;		//开启定时器
	//这里通过循环判断定时器的状态位值来确认定时器是否已归零
	do{
		temp = SysTick -> CTRL;	//获取定时器的状态值
	}while(temp & 0x01 && !(temp & (1 << 16)));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭定时器
	SysTick -> VAL |= 0x00;		//将定时器归零
}
/**
 * 毫秒延时计数
 */
void delay_ms(u32 nms){
	u32 temp;
	SysTick -> LOAD = nms * fac_ms;		//设置重装载值
	SysTick -> VAL |= 0x00;		//将定时器归零
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;		//开启定时器
	//这里通过循环判断定时器的状态位值来确认定时器是否已归零
	do{
		temp = SysTick -> CTRL;	//获取定时器的状态值
	}while(temp & 0x01 && !(temp & (1 << 16)));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭定时器
	SysTick -> VAL |= 0x00;		//将定时器归零
}
