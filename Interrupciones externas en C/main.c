
#include "stm32f10x.h"
#include "gpios.h"
#include "leds.h"
#include "extin.h"

int main(void) {

    GPIO_Config();
    led_control(0);
    EXTI_Config();

    while(1) {
        EXTI_Procesar();
    }
}
