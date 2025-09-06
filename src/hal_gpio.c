#include "hal_gpio.h"
#include <stdio.h>

// Implementaciones stub para las funciones HAL
// En un proyecto real, estas funciones se conectarían con el hardware específico

void hal_gpio_set_direction(uint8_t port, uint8_t bit, bool output) {
    printf("HAL: Configurando GPIO puerto %d, bit %d como %s\n", port, bit,
           output ? "salida" : "entrada");
}

void hal_gpio_set_output(uint8_t port, uint8_t bit, bool state) {
    printf("HAL: Estableciendo GPIO puerto %d, bit %d a %s\n", port, bit, state ? "alto" : "bajo");
}

bool hal_gpio_get_input(uint8_t port, uint8_t bit) {
    printf("HAL: Leyendo GPIO puerto %d, bit %d\n", port, bit);
    return false; // Valor por defecto
}
