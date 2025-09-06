#include "leds.h"
#include "errores.h"

#define ALL_LED_OFF       0x0000
#define FIRST_BIT         1
#define LED_TO_BIT_OFFSET 1

static uint16_t * puerto;
static uint16_t LedToMask(int led) {
    return FIRST_BIT << (led - LED_TO_BIT_OFFSET);
}

void LedsInitDriver(uint16_t * puerto_virtual) {
    puerto = puerto_virtual;
    *puerto = ALL_LED_OFF;
}

void LedsTurnOn(int led) {
    if (led < 1 || led > 16) {
        RegistrarMensaje(ALERTA, __func__, __LINE__, "El led no es valido");
        return;
    }
    *puerto |= LedToMask(led);
}

void LedsTurnOff(int led) {
    if (led < 1 || led > 16) {
        RegistrarMensaje(ALERTA, __func__, __LINE__, "El led no es valido");
        return;
    }
    *puerto &= ~LedToMask(led);
}
