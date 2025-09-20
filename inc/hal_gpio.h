#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Configura la dirección de un GPIO
 * @param port Puerto del GPIO
 * @param bit Bit del GPIO
 * @param output true para salida, false para entrada
 */
void hal_gpio_set_direction(uint8_t port, uint8_t bit, bool output);

/**
 * @brief Establece el estado de salida de un GPIO
 * @param port Puerto del GPIO
 * @param bit Bit del GPIO
 * @param state true para alto, false para bajo
 */
void hal_gpio_set_output(uint8_t port, uint8_t bit, bool state);

/**
 * @brief Lee el estado de entrada de un GPIO
 * @param port Puerto del GPIO
 * @param bit Bit del GPIO
 * @return true si está en alto, false si está en bajo
 */
bool hal_gpio_get_input(uint8_t port, uint8_t bit);

#ifdef __cplusplus
}
#endif

#endif /* HAL_GPIO_H */
