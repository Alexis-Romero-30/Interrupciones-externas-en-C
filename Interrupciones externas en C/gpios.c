#include "gpios.h"

void GPIO_Config(void) {
    // 1. Habilitar la señal de reloj para el Puerto C
    RCC->APB2ENR |= (1 << 4);

    // 2. Configurar el Pin 13 del Puerto C como salida Push-Pull 

    GPIOC->CRH &= ~(0xF << 20); 
    // Colocamos el valor 0010 (2) para indicarle que es salida a 2MHz
    GPIOC->CRH |= (0x2 << 20); 
}

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < (ms * 800); i++);
}