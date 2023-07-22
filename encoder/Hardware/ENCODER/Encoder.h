#ifndef __ENCODER_H
#define __ENCODER_H
#include "stm32f10x.h"                  // Device header

void Encoder_Init(void);
void Encoder_Get(int16_t*);

#endif
