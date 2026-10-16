

#ifndef EXTIN_H
#define EXTIN_H

#include "stm32f10x.h"

extern volatile uint32_t contador_interrupciones;

void EXTI_Config(void);
void EXTI_Procesar(void);

#endif
