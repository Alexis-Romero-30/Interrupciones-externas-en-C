#include "leds.h"

void led_control(uint8_t state) {
    if (state) {
        // Encender LED 
        GPIOC->BSRR = GPIO_BSRR_BR13; 
    } else {
        // Apagar LED
        GPIOC->BSRR = GPIO_BSRR_BS13; 
    }
}