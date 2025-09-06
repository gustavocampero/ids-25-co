/************************************************************************************************
Copyright (c) 2023, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/**
 * @file gpio.c
 * @author Gustavo Campero (gus.campero@gmail.com)
 * @brief Definicion de la funcion GPIO del programa
 * @version 0.1
 * @date 2025-08-25
 *
 * @copyright Copyright (c) 2025
 *
 */

/* === Headers files inclusions =============================================================== */

#include "gpio.h"
#include "hal_gpio.h"
#include <string.h>
#include <stddef.h>

/* === Macros definitions ====================================================================== */

/**
 * @brief Cantidad máxima de instancias de GPIO que se pueden crear
 */
#ifndef GPIO_MAX_INSTANCES
#define GPIO_MAX_INSTANCES 10
#endif

/* === Private data type declarations ========================================================== */

/**
 * @brief Estructura interna que representa un GPIO.
 */
struct gpio_s {
    uint8_t port; /**< Número de puerto físico del GPIO */
    uint8_t bit;  /**< Índice del pin dentro del puerto GPIO */
    bool output;  /**< Dirección del pin: true = salida, false = entrada */
#ifndef USE_DYNAMIC_MEM
    bool used; /**< Indicador de uso de la instancia. 'true' si esta en uso */
#endif
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

#ifndef USE_DYNAMIC_MEM
/**
 * @brief Asigna una instancia libre de GPIO en el pool estático.
 *
 * Esta función recorre el arreglo interno de instancias estáticas y devuelve
 * asigna la primera libre disponible. Una vez asignada, el campo used se
 * marca en 'true' para indicar que la posición está ocupada.
 *
 * @return gpio_t Puntero a la instancia de GPIO asignada. NULL si no hay instancias disponibles.
 */
static gpio_t allocateInstance() {
    static struct gpio_s instances[GPIO_MAX_INSTANCES] = {0};

    gpio_t result = NULL;
    for (int index = 0; index < GPIO_MAX_INSTANCES; index++) {
        if (!instances[index].used) {
            result = &instances[index];
            result->used = true;
            break;
        }
    }
    return result;
}

/**
 * @brief Libera una instancia GPIO creada.
 *
 * @param gpio Puntero al GPIO
 */
void gpioFree(gpio_t gpio) {
    if (gpio) {
        gpio->used = false;
        gpio->port = 0;
        gpio->bit = 0;
    }
}
#endif

/* === Public function implementation ========================================================== */

gpio_t gpioCreate(uint8_t port, uint8_t bit) {
#ifdef USE_DYNAMIC_MEM
    gpio_t self = malloc(sizeof(struct gpio_s));
#else
    gpio_t self = allocateInstance();
#endif

    if (self) {
        self->port = port;
        self->bit = bit;
        self->output = false;
    }
    return self;
}

void gpioSetOutput(gpio_t self, bool output) {
    self->output = output;
    hal_gpio_set_direction(self->port, self->bit, output);
}

void gpioSetState(gpio_t self, bool state) {
    if (self->output) {
        hal_gpio_set_output(self->port, self->bit, state);
    }
}

bool gpioGetState(gpio_t self) {
    return hal_gpio_get_input(self->port, self->bit);
}

/* === End of documentation ==================================================================== */
