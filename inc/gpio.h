
#ifndef GPIO_H
#define GPIO_H

/**
 * @file gpio.h
 * @author Gustavo Campero (gus.campero@gmail.com)
 * @brief API para manejo de GPIOs
 * @version 0.1
 * @date 2025-08-25
 *
 * @copyright Copyright (c) 2025
 *
 */

/* === Headers files inclusions ================================================================ */

#include <stdint.h>
#include <stdbool.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/**
 * @brief Puntero a estructura que representa un GPIO
 */
typedef struct gpio_s * gpio_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Crea y obtiene el manejador de un GPIO específico.
 *
 * @param port Puerto del GPIO
 * @param bit Indice del bit/pin del puerto GPIO
 * @return gpio_t Puntero a la estructura GPIO creada
 */
gpio_t gpioCreate(uint8_t port, uint8_t bit);

/**
 * @brief Configura la dirección del GPIO (entrada/salida).
 *
 * @param gpio Puntero al GPIO
 * @param output Direccion del pin: 'true' para salida, 'false' para entrada
 */
void gpioSetOutput(gpio_t gpio, bool output);

/**
 * @brief Configura el estado del GPIO cuando está configurado como salida.
 *
 * @param gpio Puntero al GPIO
 * @param state Estado: 'true' para alto, 'false' para bajo
 */
void gpioSetState(gpio_t gpio, bool state);

/**
 * @brief Lee el estado lógico actual del GPIO.
 *
 * @param gpio Puntero al GPIO
 * @return 'true' si el nivel es alto, 'false' si el nivel es bajo
 */
bool gpioGetState(gpio_t gpio);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */
