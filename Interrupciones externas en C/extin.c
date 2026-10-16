
#include "extin.h"
#include "leds.h"

// Contador de interrupciones
volatile uint32_t contador_interrupciones = 0;

void EXTI_Config(void) {

    // 1. Habilitar reloj GPIOA y AFIO
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 0);

    // 2. Configurar PA0 como entrada Pull-Up
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0x8 << 0);
    GPIOA->ODR |=  (1 << 0);

    // 3. Seleccionar PA0 para EXTI0
    AFIO->EXTICR[0] &= ~(0xF << 0);

    // 4. Configurar flanco descendente
    EXTI->RTSR &= ~(1 << 0);
    EXTI->FTSR |=  (1 << 0);

    // 5. Limpiar bandera pendiente
    EXTI->PR = (1 << 0);

    // 6. Habilitar EXTI0
    EXTI->IMR |= (1 << 0);

    // 7. Configurar NVIC
    NVIC_ClearPendingIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// Procesar las interrupciones registradas
void EXTI_Procesar(void) {

    static uint32_t ultimo_contador = 0;

    uint32_t contador_actual = contador_interrupciones;

    if (contador_actual != ultimo_contador) {

        ultimo_contador = contador_actual;

        // Cambiar estado del LED segun el contador
        led_control(contador_actual & 1);
    }
}

// Rutina de interrupcion EXTI0
void EXTI0_IRQHandler(void) {

    if (EXTI->PR & (1 << 0)) {

        // Registrar interrupcion
        contador_interrupciones++;

        // Limpiar bandera pendiente
        EXTI->PR = (1 << 0);
    }
}

